#pragma once
#include <Windows.h>
#include <cstdint>
#include <unordered_map>

const std::uintptr_t current_module = reinterpret_cast<std::uintptr_t>(GetModuleHandle(NULL));

struct rbx_TValue;
struct rbx_TNode;

namespace func_defs
{
	using rbx_getscheduler_t = std::uintptr_t(__cdecl*)();
	using rbx_output_t = void(__fastcall*)(std::int16_t output_type, const char* str);
	using rbx_getstate_t = std::uintptr_t(__thiscall*)(std::uintptr_t SC, int* state_type);
	using rbx_pushvfstring_t = int(__cdecl*)(std::uintptr_t rl, const char* fmt, ...);
	using rbx_index2psuedo_t = std::uintptr_t*(__fastcall*)(std::uintptr_t rl, int idx);

	using rbx_luam_newgcoblock_t = std::uintptr_t(__fastcall*)(std::uintptr_t rl, int sz);
	using rbx_luam_toobig_t = void(__fastcall*)(std::uintptr_t rl);
	using rbx_luag_runerror_t = void(__cdecl*)(std::uintptr_t rl, ...);
	using rbx_calltm_t = rbx_TValue*(__fastcall*)(std::uintptr_t rl, rbx_TValue* f, rbx_TValue* p1, rbx_TValue* p2, rbx_TValue* p3);
	using rbx_calltmres_t = rbx_TValue*(__fastcall*)(std::uintptr_t rl, rbx_TValue* res, rbx_TValue* f, rbx_TValue* p1, rbx_TValue* p2);
	using rbx_luac_barriertable_t = void(__fastcall*)(std::uintptr_t rl, std::uintptr_t t, std::uintptr_t v);
}

namespace addresses
{
	const std::uintptr_t rbx_getscheduler_addy = current_module + 0x00E11950;
	const std::uintptr_t rbx_output_addy = current_module + 0x00220A00;
	const std::uintptr_t rbx_getstate_addy = current_module + 0x003ADFA0;
	const std::uintptr_t rbx_pushvfstring_addy = current_module + 0x01320060;

	const std::uintptr_t spawn_func_addy = current_module + 0x003C67A0;
	const std::uintptr_t deserializer_func_addy = current_module + 0x01324340;

	const std::uintptr_t pushcclosure_addy = current_module + 0x01343610;
	const std::uintptr_t pushcclosure_exit_addy = current_module + 0x01343891;

	const std::uintptr_t index2psuedo_addy = current_module + 0x1320220;
	const std::uintptr_t typename_addy = current_module + 0x1321000;

	const std::uintptr_t fake_ret_addy = current_module + 0x0022A46A; // reg jmp

	const std::uintptr_t callcheck_addy_1 = current_module + 0x2E4B1D4; // data ptr
	const std::uintptr_t callcheck_addy_2 = current_module + 0x002270D7; // code ptr
	const std::uintptr_t callcheck_addy_3 = current_module + 0x01393D8E; // VM callcheck

	const std::uintptr_t xor_const = current_module + 0x2C28BB0;

	const std::uintptr_t rbx_luam_newgcoblock = current_module + 0x13A5FE0;
	const std::uintptr_t rbx_luam_toobig = current_module + 0x13A5D90;

	const std::uintptr_t rbx_luag_runerror = current_module + 0x136D330;
	const std::uintptr_t rbx_calltm = current_module + 0x139E330;
	const std::uintptr_t rbx_calltmres = current_module + 0;

	const std::uintptr_t rbx_luac_barriertable = current_module + 0;

	static const rbx_TNode* rbx_dummynode = reinterpret_cast<rbx_TNode*>(current_module + 0x1DF4F90);
	static rbx_TValue* rbx_luao_nilobject = reinterpret_cast<rbx_TValue*>(current_module + 0);

	const std::uintptr_t rbx_newpage = current_module + 0x13A5DC0;
}

namespace offsets
{
	namespace scheduler
	{
		constexpr std::uintptr_t jobs_start = 0x12C;
		constexpr std::uintptr_t jobs_end = 0x130;
		constexpr std::uintptr_t fps = 0x110;
	}

	namespace job
	{
		constexpr std::uintptr_t name = 0x10;
	}

	namespace waiting_scripts_job
	{
		constexpr std::uintptr_t datamodel = 0x28;
		constexpr std::uintptr_t script_context = 0x130;
	}

	namespace identity
	{
		constexpr std::uintptr_t extra_space = 0x48;
		constexpr std::uintptr_t identity = 0x18;
	}

	namespace closure
	{
		constexpr std::uintptr_t func = 16;
	}

	namespace userdata
	{
		constexpr std::uintptr_t metatable = 0;
	}

	namespace table
	{
		constexpr std::uintptr_t readonly = 0;
		constexpr std::uintptr_t metatable = 0;
		constexpr std::uintptr_t node = 0x18;
		constexpr std::uintptr_t sizenode = 7;
		constexpr std::uintptr_t lastfree = 0;
	}

	namespace string
	{
		constexpr std::uintptr_t marked = 0;
		constexpr std::uintptr_t tt = 1;
		constexpr std::uintptr_t memcat = 2;
		constexpr std::uintptr_t atom = 4;
		constexpr std::uintptr_t hash = 0xC;
		constexpr std::uintptr_t len = 0x10;
		constexpr std::uintptr_t data = 0x14;
	}

	namespace gc
	{
		const std::uintptr_t classforsize = current_module + 0x2A5F8D8;
	}

	namespace luastate
	{
		constexpr std::uintptr_t top = 0xC;
		constexpr std::uintptr_t base = 0x8;
		constexpr std::uintptr_t namecallmethod = 0;
		constexpr std::uintptr_t memcat = 4;
		constexpr std::uintptr_t global = 0x1C;
		constexpr std::uintptr_t cachedslot = 0;
	}

	namespace globalstate
	{
		constexpr std::uintptr_t frealloc = 0;
		constexpr std::uintptr_t ud = 0;
		constexpr std::uintptr_t totalbytes = 0x30;
		constexpr std::uintptr_t memcatbytes = 0x144;
		constexpr std::uintptr_t useratom = 0x860;
		constexpr std::uintptr_t currentwhite = 0x14;
		constexpr std::uintptr_t tbsize = 8;

		constexpr std::uintptr_t strt_hash = 0;
		constexpr std::uintptr_t strt_size = 0;

		constexpr std::uintptr_t allgcopages = 0x13C;
	}
}

namespace encryption // lmao i seriously need to get something figured out, this is a mess
{
	static inline std::uintptr_t rbx_decrypt_closure(std::uintptr_t func)
	{
		return *reinterpret_cast<std::uintptr_t*>(func + offsets::closure::func) + (func + offsets::closure::func);
	}
	
	static inline std::uintptr_t rbx_decrypt_metatable(std::uintptr_t enc_mt)
	{
		return *reinterpret_cast<std::uintptr_t*>(enc_mt) + enc_mt;
	}

	static inline void rbx_encrypt_length(std::uintptr_t tstring, size_t len)
	{
		*reinterpret_cast<size_t*>(tstring + offsets::string::len) = len - (tstring + offsets::string::len);
	}

	static inline size_t rbx_decrypt_length(std::uintptr_t tstring)
	{
		return *reinterpret_cast<size_t*>(tstring + offsets::string::len) + (tstring + offsets::string::len);
	}

	static inline void rbx_encrypt_hash(std::uintptr_t tstring, unsigned int hash)
	{
		*reinterpret_cast<unsigned int*>(tstring + offsets::string::hash) = hash ^ (tstring + offsets::string::hash);
	}

	static inline unsigned int rbx_decrypt_hash(std::uintptr_t tstring)
	{
		return *reinterpret_cast<unsigned int*>(tstring + offsets::string::hash) ^ (tstring + offsets::string::hash);
	}

	static inline std::uintptr_t rbx_globalstate(std::uintptr_t rl)
	{
		return *reinterpret_cast<std::uintptr_t*>(rl + offsets::luastate::global) - (rl + offsets::luastate::global);
	}

	static inline std::uintptr_t rbx_decryptnode(std::uintptr_t t)
	{
		return (t + offsets::table::node) + *reinterpret_cast<std::uintptr_t*>(t + offsets::table::node);
	}
}

typedef union // 8 bytes
{
	std::uintptr_t p;
	void* vp;

	bool b;
	double n;
} rbx_Value; // 0-8

struct rbx_TValue
{
	rbx_Value Value; // 0-8
	int extra[1]; // 8-12
	int tt = 0; // 12-16
};

struct rbx_TKey // this uses bitmath to pack shit together tightly, restricts tt to only 4 bits (1/2 a byte), and next is 3 & 1/2 a byte, for a total of 4 bytes
{
	::rbx_Value Value; // 0-8
	int extra[1]; // 8-12

	// these 2 add up to a total of 4 bytes
	unsigned tt : 4; // 4 bits, 12-12.5
	int next : 28; // 12.5-32
};

struct rbx_TNode // 32 bytes in length
{
	rbx_TValue val; // 0-15
	rbx_TKey key; // 16-31
};


#define rbx_lmod(s, size) ((s) & ((size)-1))

#define rbx_twoto(x) ((1 << (x)))
#define rbx_sizenode(t) (rbx_twoto(*reinterpret_cast<std::uintptr_t*>(t + offsets::table::sizenode)))

#define rbx_gnode(t, spot) (reinterpret_cast<rbx_TNode*>(encryption::rbx_decryptnode(t)) + spot)
#define rbx_gkey(n) (&(n)->key)
#define rbx_gval(n) (&(n)->val)
#define rbx_gnext(n) (rbx_gkey(n)->next)

#define rbx_hashpow2(t, n) (rbx_gnode(t, rbx_lmod((n), rbx_sizenode(t))))
#define rbx_hashstr(t, str) rbx_hashpow2(t, encryption::rbx_decrypt_hash(str))

#define rbx_getnodekey(obj, node) \
    { \
        rbx_TValue* i_o = (obj); \
        const rbx_TNode* n_ = (node); \
        i_o->Value.p = n_->key.Value.p; \
        memcpy(i_o->extra, n_->key.extra, sizeof(i_o->extra)); \
        i_o->tt = n_->key.tt; \
    }

#define setnodekey(node, obj) \
    { \
        rbx_TNode* n_ = (node); \
        const rbx_TValue* i_o = (obj); \
        n_->key.Value = i_o->Value; \
        memcpy(n_->key.extra, i_o->extra, sizeof(n_->key.extra)); \
        n_->key.tt = i_o->tt; \
    }

/* obj1->Value = obj2->Value; obj1->tt = obj2->tt; memcpy(obj1->extra, obj2->extra, sizeof(obj1->extra)) */
#define setobj(obj1, obj2) \
	{ \
		rbx_TValue* o1 = (obj1); \
		const rbx_TValue* o2 = (obj2); \
		o1->Value = o2->Value; \
		o1->tt = o2->tt; \
		memcpy(o1->extra, o2->extra, sizeof(o1->extra)); \
	}

#define rbx_iscollectable(o) (o->tt >= ttypes["string"])

#define rbx_iswhite(x) (*reinterpret_cast<byte*>(x + offsets::string::marked) & 3)
#define rbx_isblack(x) (*reinterpret_cast<byte*>(x + offsets::string::marked) & 4)

#define rbx_luac_barriert(rl, t, key) \
	{ \
		if (rbx_iscollectable(key) && rbx_isblack(t) && rbx_iswhite(key->Value.p)) \
			rbx_luac_barriertable(rl, t, key->Value.p); \
	}


constexpr size_t tsize = sizeof(rbx_TValue);
extern std::unordered_map<std::string, int> ttypes;
extern std::unordered_map<std::string, int> ttms;

static void map_ttypes()
{
	for (int i = 0; i < 10; ++i)
	{
		static bool hit = false;
		const char* tt = reinterpret_cast<const char* (__fastcall*)(int, int)>(addresses::typename_addy)(NULL, i);

		if (!strcmp(tt, "userdata") && !hit)
		{
			hit = true;
			tt = "lightuserdata";
		}

		printf_s("%s - %d\n", tt, i);

		ttypes[tt] = i;
	}

	for (int i = 0; i < 18; ++i)
	{
		const char* tm = reinterpret_cast<const char* (__fastcall*)(int, int)>(addresses::typename_addy)(NULL, i + 10);

		printf_s("%s - %d\n", tm, i);
		ttms[tm] = i;
	}
}