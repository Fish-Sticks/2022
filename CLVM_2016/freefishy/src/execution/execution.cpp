#include "execution.h"
#include "addresses.hpp"

execution_t::execution_t(std::uintptr_t rL) : r_L{rL}
{
	g_L = luaL_newstate();

    g_L->r_L = rL;

	std::printf("Successfully created execution class!\n");
}

void execution_t::run_script(const std::string& script, const std::string& script_name)
{
    lua_State* L = lua_newthread(g_L);
    luaL_ref(g_L, LUA_REGISTRYINDEX); // prevent garbage collecting it

    std::uintptr_t rL = rbx_newthread(g_L->r_L);
    rbx_lual_ref(g_L->r_L, LUA_REGISTRYINDEX); // copy for roblox

    // Roblox also does this exact method in the function 0x003922C0

    std::printf("New thread: 0x%08X\n", rL);

    rbx_getglobal(rL, "print");
    rbx_pushstring(rL, "a new message from the new thread! hello!");
    // rbx_pcall(rL, 1, 0, 0);

    L->r_L = rL;

	if (!luaL_loadbuffer(L, script.c_str(), script.size(), script_name.c_str()))
	{
	    lua_pcall(L, 0, 0, 0);
	}
	else
	{
		const char* error = lua_tostring(L, -1);
		std::printf("%s\n", error);
		lua_pop(L, 1);
	}
}










#define runtime_check(L, c)	{ if (!(c)) break; }

#define RA(i)	(base+GETARG_A(i))
/* to be used after possible stack reallocation */
#define RB(i)	check_exp(getBMode(GET_OPCODE(i)) == OpArgR, base+GETARG_B(i))
#define RC(i)	check_exp(getCMode(GET_OPCODE(i)) == OpArgR, base+GETARG_C(i))
#define RKB(i)	check_exp(getBMode(GET_OPCODE(i)) == OpArgK, \
	ISK(GETARG_B(i)) ? k+INDEXK(GETARG_B(i)) : base+GETARG_B(i))
#define RKC(i)	check_exp(getCMode(GET_OPCODE(i)) == OpArgK, \
	ISK(GETARG_C(i)) ? k+INDEXK(GETARG_C(i)) : base+GETARG_C(i))
#define KBx(i)	check_exp(getBMode(GET_OPCODE(i)) == OpArgK, k+GETARG_Bx(i))


#define dojump(L,pc,i)	{(pc) += (i); luai_threadyield(L);}


#define Protect(x)	{ L->savedpc = pc; {x;}; base = L->base; }


#define arith_op(op,tm) { \
        TValue *rb = RKB(i); \
        TValue *rc = RKC(i); \
        if (ttisnumber(rb) && ttisnumber(rc)) { \
          lua_Number nb = nvalue(rb), nc = nvalue(rc); \
          setnvalue(ra, op(nb, nc)); \
        } \
        else \
          Protect(Arith(L, ra, rb, rc, tm)); \
      }


/*
0 - nil
1 - userdata
2 - number
3 - boolean
4 - string
5 - thread
6 - function
7 - table
8 - userdata
9 - proto
*/


// needs a patch so that my roblox stack is also initialized (so that I don't fucking crash)
extern "C" void fish_realloc_stack_check(unsigned int, int);
void fish_realloc_stack_check(unsigned int r_L, int newsize)
{
    std::printf("realloc stack check called!\n");

    if (*reinterpret_cast<std::uintptr_t*>(r_L + offsets::lua_state::stack_last) - *reinterpret_cast<std::uintptr_t*>(r_L + offsets::lua_state::top) <= 16 * newsize)
    {
        std::printf("reallocating the stack!\n");

        std::uintptr_t stacksize = *reinterpret_cast<std::uintptr_t*>(r_L + offsets::lua_state::stacksize);
        if (newsize <= stacksize)
            rbx_luad_reallocstack(r_L, 2 * stacksize);
        else
            rbx_luad_reallocstack(r_L, newsize + stacksize);
    }
}

extern "C" void fish_execute(lua_State* L, int nexeccalls); // declaration for C to understand
void fish_execute(lua_State* L, int nexeccalls) // lua calls back to this, preform CLVM operations, fishy clvm winning
{
    std::uintptr_t r_L = L->r_L;
    std::printf("Got thread: 0x%08X\n", r_L);

    LClosure* cl;
    StkId base;
    TValue* k;
    const Instruction* pc;

    TValue* r_base = *reinterpret_cast<TValue**>(r_L + offsets::lua_state::base);

reentry:  /* entry point */
    lua_assert(isLua(L->ci));
    pc = L->savedpc;
    cl = &clvalue(L->ci->func)->l;
    base = L->base;
    k = cl->p->k;
    /* main loop of interpreter */
    for (;;) {
        const Instruction i = *pc++;
        StkId ra;

        /* warning!! several calls may realloc the stack and invalidate `ra' */
        ra = RA(i);
        lua_assert(base == L->base && L->base == L->ci->base);
        lua_assert(base <= L->top && L->top <= L->stack + L->stacksize);
        lua_assert(L->top == L->ci->top || luaG_checkopenop(i));

        std::printf("Running instruction: %s\n", luaP_opnames[GET_OPCODE(i)]);

        switch (GET_OPCODE(i)) {

            case OP_GETGLOBAL:
            {
                TValue* lua_constant = KBx(i);

                if (lua_constant->tt == LUA_TSTRING)
                {
                    TValue rbx_constant{};

                    std::printf("string: \"%s\" length: %zu\n", svalue(lua_constant), lua_constant->value.gc->ts.tsv.len);

                    rbx_constant.value.gc = reinterpret_cast<GCObject*>(rbx_luas_newlstr(r_L, svalue(lua_constant), lua_constant->value.gc->ts.tsv.len));
                    rbx_constant.tt = 4;

                    rbx_luav_gettable(r_L, reinterpret_cast<std::uintptr_t*>(r_L + offsets::lua_state::gt), reinterpret_cast<std::uintptr_t*>(&rbx_constant), reinterpret_cast<std::uintptr_t*>(&r_base[GETARG_A(i)]));
                }
                else
                {
                    std::printf("OP_GETGLOBAL conversion to Roblox TValue failed, haulting!\n");
                    return;
                }
                continue;
            }

            case OP_SETGLOBAL:
            {
                TValue* lua_constant = KBx(i);

                if (lua_constant->tt == LUA_TSTRING)
                {
                    TValue rbx_constant{};
                    rbx_constant.value.gc = reinterpret_cast<GCObject*>(rbx_luas_newlstr(r_L, svalue(lua_constant), lua_constant->value.gc->ts.tsv.len));
                    rbx_constant.tt = 4;

                    rbx_luav_settable(r_L, reinterpret_cast<std::uintptr_t*>(r_L + offsets::lua_state::gt), reinterpret_cast<std::uintptr_t*>(&rbx_constant), reinterpret_cast<std::uintptr_t*>(&r_base[GETARG_A(i)]));
                }
                else
                {
                    std::printf("OP_GETGLOBAL conversion to Roblox TValue failed, haulting!\n");
                    return;
                }
                continue;
            }

            case OP_GETTABLE:
            {
                if (ISK(GETARG_C(i)))
                {
                    TValue* lua_constant = RKC(i);

                    TValue rbx_constant{};
                    rbx_constant.value.gc = reinterpret_cast<GCObject*>(rbx_luas_newlstr(r_L, svalue(lua_constant), lua_constant->value.gc->ts.tsv.len));
                    rbx_constant.tt = 4;

                    rbx_luav_gettable(r_L, reinterpret_cast<std::uintptr_t*>(&r_base[GETARG_B(i)]), reinterpret_cast<std::uintptr_t*>(&rbx_constant), reinterpret_cast<std::uintptr_t*>(&r_base[GETARG_A(i)]));
                }
                else
                    rbx_luav_gettable(r_L, reinterpret_cast<std::uintptr_t*>(&r_base[GETARG_B(i)]), reinterpret_cast<std::uintptr_t*>(&r_base[GETARG_C(i)]), reinterpret_cast<std::uintptr_t*>(&r_base[GETARG_A(i)]));

                continue;
            }

            case OP_SETTABLE:
            {
                std::uintptr_t* key = 0;
                std::uintptr_t* val = 0;

                if (ISK(GETARG_B(i)))
                {
                    TValue* lua_constant = RKB(i);

                    TValue rbx_constant{};
                    rbx_constant.value.gc = reinterpret_cast<GCObject*>(rbx_luas_newlstr(r_L, svalue(lua_constant), lua_constant->value.gc->ts.tsv.len));
                    rbx_constant.tt = 4;

                    key = reinterpret_cast<std::uintptr_t*>(&rbx_constant);
                }
                else
                    key = reinterpret_cast<std::uintptr_t*>(&r_base[GETARG_B(i)]);

                if (ISK(GETARG_C(i)))
                {
                    TValue* lua_constant = RKC(i);

                    if (lua_constant->tt == LUA_TSTRING)
                    {
                        TValue rbx_constant{};
                        rbx_constant.value.gc = reinterpret_cast<GCObject*>(rbx_luas_newlstr(r_L, svalue(lua_constant), lua_constant->value.gc->ts.tsv.len));
                        rbx_constant.tt = 4;

                        val = reinterpret_cast<std::uintptr_t*>(&rbx_constant);
                    }
                    else if (lua_constant->tt == LUA_TNUMBER)
                    {
                        double num = lua_constant->value.n;
                        double output = 0;
                        __asm
                        {
                            movsd xmm1, num
                            xorpd xmm1, xor_const_addy
                            movsd output, xmm1
                        }

                        TValue rbx_constant{};
                        rbx_constant.value.n = output;
                        rbx_constant.tt = 2;

                        val = reinterpret_cast<std::uintptr_t*>(&rbx_constant);
                    }
                    else
                    {
                        std::printf("OP_SETTABLE - failed to convert constant, haulting!\n");
                        return;
                    }
                }
                else
                    val = reinterpret_cast<std::uintptr_t*>(&r_base[GETARG_B(i)]);

                rbx_luav_settable(r_L, reinterpret_cast<std::uintptr_t*>(&r_base[GETARG_A(i)]), key, val);

                continue;
            }

            case OP_LOADK: 
            {
                TValue* lua_constant = KBx(i);

                if (lua_constant->tt == LUA_TSTRING)
                {
                    TValue rbx_constant{};
                    rbx_constant.value.gc = reinterpret_cast<GCObject*>(rbx_luas_newlstr(r_L, svalue(lua_constant), lua_constant->value.gc->ts.tsv.len));
                    rbx_constant.tt = 4;

                    memcpy(&r_base[GETARG_A(i)], &rbx_constant, 16);
                }
                else if (lua_constant->tt == LUA_TNUMBER)
                {
                    double num = lua_constant->value.n;
                    double output = 0;
                    __asm
                    {
                        movsd xmm1, num
                        xorpd xmm1, xor_const_addy
                        movsd output, xmm1
                    }

                    TValue rbx_constant{};
                    rbx_constant.value.n = output;
                    rbx_constant.tt = 2;

                    memcpy(&r_base[GETARG_A(i)], &rbx_constant, 16);
                }
                else
                {
                    std::printf("OP_LOADK - unknown constant, cannot convert, haulting!\n");
                    return;
                }
                continue;
            }

            case OP_LOADNIL:
            {
                TValue* rb = &r_base[GETARG_B(i)];
                do
                {
                    memset(--rb, 0, 16);
                } while (rb >= &r_base[GETARG_A(i)]);
                continue;
            }

            case OP_LOADBOOL:
            {
                TValue* a = &r_base[GETARG_A(i)];
                a->value.b = GETARG_B(i);
                a->tt = 3;

                if (GETARG_C(i)) ++pc;
                continue;
            }

            case OP_NOT:
            {
                TValue new_value{};
                new_value.tt = 3;

                TValue roblox_val = r_base[GETARG_B(i)];

                if (roblox_val.tt == LUA_TNIL || (roblox_val.tt == 3 && !roblox_val.value.b))
                    new_value.value.b = true;

                memcpy(&r_base[GETARG_A(i)], &new_value, 16);

                continue;
            }

            case OP_MOVE:
            {
                memcpy(&r_base[GETARG_A(i)], &r_base[GETARG_B(i)], 16);
                continue;
            }

            case OP_CALL: // should be using savedpc but there's gonna be conflicts due to encryption
            {
                int b = GETARG_B(i);
                int nresults = GETARG_C(i) - 1;

                if (b)
                    *reinterpret_cast<TValue**>(r_L + offsets::lua_state::top) = &r_base[GETARG_A(i)] + b;

                L->savedpc = pc;

                switch (rbx_luad_precall(r_L, reinterpret_cast<std::uintptr_t*>(&r_base[GETARG_A(i)]), nresults))
                {
                    case PCRLUA:
                    {
                        nexeccalls++;
                        goto reentry;
                    }

                    case PCRC:
                    {
                        if (nresults >= 0) *reinterpret_cast<std::uintptr_t*>(r_L + offsets::lua_state::top) = *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>(r_L + offsets::lua_state::ci) + offsets::lua_state::ci_top);
                        r_base = *reinterpret_cast<TValue**>(r_L + offsets::lua_state::base);
                        continue;
                    }

                    default:
                    {
                        return;
                    }
                }
            }

            case OP_RETURN:
            {
                std::printf("this shit aint even made coprrectly but who cares!\n");
                return;
            }

            default:
            {
                std::printf("Attempt to run unknown opcode: %s\n", luaP_opnames[GET_OPCODE(i)]);
                return;
            }
        }
    }
}


/*
    I need these for a print script

    Running script!
    Running instruction: GETGLOBAL
    Running instruction: LOADK
    Running instruction: CALL
    Running instruction: RETURN
*/
