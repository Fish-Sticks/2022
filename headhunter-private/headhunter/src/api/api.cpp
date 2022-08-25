#include <intrin.h>
#include "addresses/addresses.hpp"
#include "api/api.h"
#include "console/console.h"
#include "bypasses/bypasses.h"


func_defs::rbx_getscheduler_t rbx_getscheduler = reinterpret_cast<func_defs::rbx_getscheduler_t>(addresses::rbx_getscheduler_addy);
func_defs::rbx_getstate_t rbx_getstate = reinterpret_cast<func_defs::rbx_getstate_t>(addresses::rbx_getstate_addy);
func_defs::rbx_output_t rbx_output = reinterpret_cast<func_defs::rbx_output_t>(addresses::rbx_output_addy);
func_defs::rbx_pushvfstring_t rbx_pushvfstring = reinterpret_cast<func_defs::rbx_pushvfstring_t>(addresses::rbx_pushvfstring_addy);
func_defs::rbx_index2psuedo_t rbx_index2psuedo = reinterpret_cast<func_defs::rbx_index2psuedo_t>(addresses::index2psuedo_addy);
func_defs::rbx_luam_newgcoblock_t rbx_luam_newgcoblock = reinterpret_cast<func_defs::rbx_luam_newgcoblock_t>(addresses::rbx_luam_newgcoblock);
func_defs::rbx_luam_toobig_t rbx_luam_toobig = reinterpret_cast<func_defs::rbx_luam_toobig_t>(addresses::rbx_luam_toobig);
func_defs::rbx_luag_runerror_t rbx_luag_runerror = reinterpret_cast<func_defs::rbx_luag_runerror_t>(addresses::rbx_luag_runerror);

bypasses::retcheck<func_defs::rbx_calltm_t> rbx_calltm{ addresses::rbx_calltm };
bypasses::retcheck<func_defs::rbx_calltmres_t> rbx_calltmres{ addresses::rbx_calltmres };

func_defs::rbx_luac_barriertable_t rbx_luac_barriertable = reinterpret_cast<func_defs::rbx_luac_barriertable_t>(addresses::rbx_luac_barriertable);

class replacer_t // simple patching class I made to make patching easy
{
private:
	std::uintptr_t addy = NULL;
	std::size_t stolen_len = NULL;
	byte* stolen = nullptr;
public:
	replacer_t(std::uintptr_t addy)
		: addy{ addy } {}

	~replacer_t()
	{
		if (stolen != nullptr)
		{
			delete[] this->stolen;
		}
	}

	void write(const void* mem, std::size_t size)
	{
		this->stolen_len = size;
		this->stolen = new byte[size];

		DWORD old;
		VirtualProtect(reinterpret_cast<void*>(this->addy), size, PAGE_EXECUTE_READWRITE, &old);
		memcpy(this->stolen, reinterpret_cast<void*>(this->addy), size);
		memcpy(reinterpret_cast<void*>(this->addy), mem, size);
		VirtualProtect(reinterpret_cast<void*>(this->addy), size, old, &old);
	}

	void revert()
	{
		DWORD old;
		VirtualProtect(reinterpret_cast<void*>(this->addy), this->stolen_len, PAGE_EXECUTE_READWRITE, &old);
		memcpy(reinterpret_cast<void*>(this->addy), this->stolen, this->stolen_len);
		VirtualProtect(reinterpret_cast<void*>(this->addy), this->stolen_len, old, &old);
	}
};

void rbx_spawn(std::uintptr_t rl)
{
	__asm {
		mov edi, finished
		push rl
		push addresses::fake_ret_addy
		jmp addresses::spawn_func_addy
	finished:
		add esp, 4
	}
}

void rbx_deserialize(std::uintptr_t rl, const char* chunk_name, const char* bytecode, int byte_len)
{
	__asm {
		mov edi, finished
		mov ecx, rl
		mov edx, chunk_name
		push 0
		push byte_len
		push bytecode
		push addresses::fake_ret_addy
		jmp addresses::deserializer_func_addy
	finished:
		add esp, 0xC
	}
}

void inline rbx_increment_top(std::uintptr_t rl, std::int32_t amount)
{
	*reinterpret_cast<rbx_TValue**>(rl + offsets::luastate::top) += amount;
}

void inline rbx_decrement_top(std::uintptr_t rl, std::int32_t amount)
{
	*reinterpret_cast<rbx_TValue**>(rl + offsets::luastate::top) -= amount;
}

void inline rbx_setidentity(std::uintptr_t rl, std::int8_t identity)
{
	*reinterpret_cast<std::int8_t*>(*reinterpret_cast<std::uintptr_t*>(rl + offsets::identity::extra_space) + offsets::identity::identity) = identity;
}

double xor_number(double num)
{
	__m128d a = _mm_load_sd(&num);
	__m128d b = _mm_load_pd(reinterpret_cast<double*>(addresses::xor_const));
	__m128d res = _mm_xor_pd(a, b);
	double done = _mm_cvtsd_f64(res);

	return done;
}

void rbx_pushnumber(std::uintptr_t rl, double num)
{
	rbx_TValue& top = **reinterpret_cast<rbx_TValue**>(rl + offsets::luastate::top);
	top.Value.n = xor_number(num);
	top.tt = ttypes["number"];

	rbx_increment_top(rl, 1);
}

double rbx_tonumber(std::uintptr_t rl, std::int32_t idx)
{
	rbx_TValue* spot = rbx_index2adr(rl, idx);
	return xor_number(spot->Value.n);
}

void rbx_pushboolean(std::uintptr_t rl, bool b)
{
	rbx_TValue& top = **reinterpret_cast<rbx_TValue**>(rl + offsets::luastate::top);
	top.Value.b = b;
	top.tt = ttypes["boolean"];

	rbx_increment_top(rl, 1);
}

bool rbx_toboolean(std::uintptr_t rl, std::int32_t idx)
{
	rbx_TValue* spot = rbx_index2adr(rl, idx);
	return spot->Value.b;
}

void rbx_pushstring(std::uintptr_t rl, const std::string& str)
{
	std::uintptr_t lstr = rbx_luas_newlstr(rl, str.c_str(), str.length());

	rbx_TValue& top = **reinterpret_cast<rbx_TValue**>(rl + offsets::luastate::top);
	top.Value.p = lstr;
	top.tt = ttypes["string"];

	rbx_increment_top(rl, 1);
}

const char* rbx_tostring(std::uintptr_t rl, std::int32_t idx)
{
	rbx_TValue* spot = rbx_index2adr(rl, idx);
	return reinterpret_cast<const char*>(spot->Value.p + offsets::string::data);
}

std::uintptr_t old_esp = 0;
void patching_cleanup();

void rbx_pushcclosure(std::uintptr_t rl, void* closure)
{
	bypasses::callcheck();
	byte patch[5]{ 0xE9 };
	*reinterpret_cast<std::uintptr_t*>(patch + 1) = reinterpret_cast<std::uintptr_t>(patching_cleanup) - addresses::pushcclosure_exit_addy - 5;
	replacer_t func{ addresses::pushcclosure_exit_addy };

	func.write(patch, 5);

	const char* dummystring = "";

	__asm {
		pusha
		push after
		mov old_esp, esp

		mov edi, after
		mov ecx, rl
		mov edx, dummystring
		push closure
		push addresses::callcheck_addy_2
		push addresses::fake_ret_addy
		jmp addresses::pushcclosure_addy
	after:
		popa
	}

	func.revert();
}

void __declspec(naked) patching_cleanup() // callback for patched shit
{
	__asm {
		mov esp, old_esp
		ret
	}
}


rbx_TValue* rbx_index2adr(std::uintptr_t rl, int idx)
{
	if (idx > 0)
	{
		return *reinterpret_cast<rbx_TValue**>(rl + offsets::luastate::base) + (idx - 1);
	}
	else if (idx > -10000)
	{
		return *reinterpret_cast<rbx_TValue**>(rl + offsets::luastate::top) + idx;
	}
	else
	{
		return reinterpret_cast<rbx_TValue*>(rbx_index2psuedo(rl, idx));
	}
}


unsigned int rbx_luas_hash(const char* str, size_t len)
{
	// Note that this hashing algorithm is replicated in BytecodeBuilder.cpp, BytecodeBuilder::getStringHash
	unsigned int a = 0, b = 0;
	unsigned int h = unsigned(len);

	// hash prefix in 12b chunks (using aligned reads) with ARX based hash (LuaJIT v2.1, lookup3)
	// note that we stop at length<32 to maintain compatibility with Lua 5.1
	while (len >= 32)
	{
#define rol(x, s) ((x >> s) | (x << (32 - s)))
#define mix(u, v, w) a ^= h, a -= rol(h, u), b ^= a, b -= rol(a, v), h ^= b, h -= rol(b, w)

		// should compile into fast unaligned reads
		uint32_t block[3];
		memcpy(block, str, 12);

		a += block[0];
		b += block[1];
		h += block[2];
		mix(14, 11, 7);
		str += 12;
		len -= 12;

#undef mix
#undef rol
	}

	// original Lua 5.1 hash for compatibility (exact match when len<32)
	for (size_t i = len; i > 0; --i)
	{
		h ^= (h << 5) + (h >> 2) + (uint8_t)str[i - 1];
	}
	return h;
}

#define sizestring(len) offsets::string::data + len + 1

std::uintptr_t rbx_luam_newgco_(std::uintptr_t rl, size_t nsize, std::uint8_t memcat)
{
	std::uintptr_t globalstate = encryption::rbx_globalstate(rl);
	std::uintptr_t allocated = NULL;

	if (nsize > 512 || reinterpret_cast<byte*>(offsets::gc::classforsize)[nsize] < 0)
	{
		//allocated = reinterpret_cast<std::uintptr_t(__cdecl*)(std::uintptr_t, std::uintptr_t, int, int, size_t)>(*reinterpret_cast<std::uintptr_t*>(globalstate + offsets::globalstate::frealloc))(rl, *reinterpret_cast<std::uintptr_t*>(globalstate + offsets::globalstate::ud), 0, 0, nsize);
		allocated = rbx_luam_newgcoblock(rl, reinterpret_cast<byte*>(offsets::gc::classforsize)[nsize]);
	}
	else
	{
		std::uintptr_t page = reinterpret_cast<std::uintptr_t(__fastcall*)(std::uintptr_t, std::uintptr_t, int, int, int)>(addresses::rbx_newpage)(rl, globalstate + offsets::globalstate::allgcopages, nsize + 40, nsize, 1);
		allocated = page + 0x28;

		*reinterpret_cast<std::uintptr_t*>(page + 0x1C) -= *reinterpret_cast<std::uintptr_t*>(page + 0x14);
		++*reinterpret_cast<std::uintptr_t*>(page + 0x20);
	}

	*reinterpret_cast<size_t*>(globalstate + offsets::globalstate::totalbytes) += nsize;
	*reinterpret_cast<size_t*>(globalstate + 4 * memcat + offsets::globalstate::memcatbytes) += nsize;

	return allocated;
}


// STRINGS


std::uintptr_t rbx_newlstr(std::uintptr_t rl, const char* str, size_t len, unsigned int hash)
{
	if (len > (1 << 30))
		rbx_luam_toobig(rl);

	std::uintptr_t memory = rbx_luam_newgco_(rl, sizestring(len), *reinterpret_cast<byte*>(rl + offsets::luastate::memcat));
	std::uintptr_t globalstate = encryption::rbx_globalstate(rl);

	encryption::rbx_encrypt_length(memory, len);
	encryption::rbx_encrypt_hash(memory, hash);
	*reinterpret_cast<byte*>(memory + offsets::string::marked) = *reinterpret_cast<byte*>(globalstate + offsets::globalstate::currentwhite) & 3;
	*reinterpret_cast<byte*>(memory + offsets::string::tt) = ttypes["string"];
	*reinterpret_cast<byte*>(memory + offsets::string::memcat) = *reinterpret_cast<byte*>(rl + offsets::luastate::memcat);
	memcpy(reinterpret_cast<void*>(memory + offsets::string::data), str, len);
	*reinterpret_cast<char*>(memory + offsets::string::data + len) = '\0';

	std::int16_t atom;
	std::uintptr_t func = *reinterpret_cast<std::uintptr_t*>(globalstate + offsets::globalstate::useratom);

	if (func)
		atom = reinterpret_cast<std::int16_t(__cdecl*)(std::uintptr_t, size_t)>(func)(memory + offsets::string::data, len);
	else
		atom = -1;

	*reinterpret_cast<std::int16_t*>(memory + offsets::string::atom) = atom;

	hash = 4 * rbx_lmod(hash, *reinterpret_cast<std::uintptr_t*>(globalstate + offsets::globalstate::tbsize));

	*reinterpret_cast<std::uintptr_t*>(memory + 8) = *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>(globalstate + 4) + hash);
	*reinterpret_cast<std::uintptr_t*>(hash + *reinterpret_cast<std::uintptr_t*>(globalstate + 4)) = memory;
	++*reinterpret_cast<size_t*>(globalstate);

	return memory;
}

std::uintptr_t rbx_luas_newlstr(std::uintptr_t rl, const char* str, size_t len)
{
	unsigned int hash = rbx_luas_hash(str, len);
	//std::uintptr_t el = *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>(*global + rl + offsets::globalstate::strt_hash) + 4 * lmod(hash, *reinterpret_cast<std::uintptr_t*>(*global + global)));

	std::uintptr_t el = *reinterpret_cast<std::uintptr_t*>( // please, don't look
		*reinterpret_cast<std::uintptr_t*>(
			*reinterpret_cast<std::uintptr_t*>(rl + offsets::luastate::global) - rl - offsets::table::node
		)
		+ 4 * (hash & (*reinterpret_cast<std::uintptr_t*>(encryption::rbx_globalstate(rl) + offsets::globalstate::tbsize) - 1))
	);

	if (el)
	{
		while (true)
		{
			if (encryption::rbx_decrypt_length(el) == len && !strcmp(str, reinterpret_cast<const char*>(el + offsets::string::data)))
			{
				byte b = *reinterpret_cast<byte*>(el + 0);
				if (((b ^ ~*reinterpret_cast<byte*>(*reinterpret_cast<std::uintptr_t*>(rl + 0x1C) - (rl + 0x14)) & 3) & 0xB) == 0)
					*reinterpret_cast<byte*>(el + 0) = b ^ 3;

				std::cout << "Using cached string!\n";
				return el;
			}

			el = *reinterpret_cast<std::uintptr_t*>(el + 8);
			if (!el)
				break;
		}
	}

	if (len > INT_MAX / 2)
		rbx_luam_toobig(rl);

	return rbx_newlstr(rl, str, len, hash);
}

#define rbx_luas_new(rl, a) rbx_luas_newlstr(rl, a, strlen(a))


// TABLES


static rbx_TNode* mainposition(std::uintptr_t t, const rbx_TValue* key)
{
	if (key->tt == ttypes["string"])
	{
		std::cout << "MP called, getting string!\n";
		return rbx_hashstr(t, key->Value.p);
	}
	else
	{
		std::cout << "Only strings are supported at the moment for mainposition lmao, enjoy your crash- biiiiiiiiiiiiiiiitch!\n";
		return const_cast<rbx_TNode*>(addresses::rbx_dummynode);
	}
}

static rbx_TNode* getfreepos(std::uintptr_t t)
{
	std::int32_t lastfree = *reinterpret_cast<std::int32_t*>(t + offsets::table::lastfree);

	while (lastfree > 0)
	{
		*reinterpret_cast<std::int32_t*>(t + offsets::table::lastfree) -= 1;

		rbx_TNode* n = rbx_gnode(t, *reinterpret_cast<std::int32_t*>(t + offsets::table::lastfree));
		if (rbx_gkey(n)->tt == ttypes["nil"])
			return n;

		lastfree = *reinterpret_cast<std::int32_t*>(t + offsets::table::lastfree);
	}

	return nullptr;
}

static rbx_TValue* newkey(std::uintptr_t rl, std::uintptr_t t, const rbx_TValue* key)
{
	rbx_TNode* mp = mainposition(t, key);

	if (rbx_gval(mp)->tt != ttypes["nil"] || mp == addresses::rbx_dummynode)
	{
		rbx_TNode* othern;
		rbx_TNode* n = getfreepos(t);

		if (n == nullptr)
		{
			std::cout << "no way in hell your big bodied ass finna rehash & resize, gtfo\n";
			return nullptr;
		}
		else
		{
			std::cout << "its not nullptr, time to make key yum!\n";
		}

		rbx_TValue mk;
		rbx_getnodekey(&mk, mp);

		othern = mainposition(t, &mk);

		if (othern != mp)
		{
			while (othern + rbx_gnext(othern) != mp)
				othern += rbx_gnext(othern);

			rbx_gnext(othern) = n - othern;
			*n = *mp;

			if (rbx_gnext(mp) != 0)
			{
				rbx_gnext(n) = mp - n;
				rbx_gnext(mp) = 0;
			}

			rbx_gval(mp)->tt = ttypes["nil"];
		}
		else
		{
			if (rbx_gnext(mp) != 0)
				rbx_gnext(n) = ((mp + rbx_gnext(mp)) - n);

			rbx_gnext(mp) = (n - mp);
			mp = n;
		}
	}

	setnodekey(mp, key);

	rbx_luac_barriert(rl, t, key);
	std::cout << "finished newkey!\n";
	return rbx_gval(mp);
}


rbx_TValue* rbx_luah_getstr(std::uintptr_t t, std::uintptr_t key)
{
	rbx_TNode* n = reinterpret_cast<rbx_TNode*>(rbx_hashstr(t, key));

	for (;;)
	{
		if (rbx_gkey(n)->tt == ttypes["string"] && rbx_gkey(n)->Value.p == key)
			return rbx_gval(n);

		if (!rbx_gnext(n))
			break;
		
		n += rbx_gnext(n);
	}

	return addresses::rbx_luao_nilobject;
}

rbx_TValue* rbx_luah_get(std::uintptr_t t, const rbx_TValue* key)
{
	if (key->tt == ttypes["nil"]) // can't use switch since its a map lmao
	{
		std::cout << "no nil\n";
	}
	else if (key->tt == ttypes["string"])
	{
		std::cout << "getting string!\n";
		return rbx_luah_getstr(t, key->Value.p);
	}
	else if (key->tt == ttypes["number"])
	{
		std::cout << "number\n";
	}
	else
	{
		std::cout << "your keys tt is fucked!\n";
	}

	return addresses::rbx_luao_nilobject;
}

rbx_TValue* rbx_luah_set(std::uintptr_t rl, std::uintptr_t t, const rbx_TValue* key)
{
	rbx_TValue* val = rbx_luah_get(t, key);
	if (val != addresses::rbx_luao_nilobject)
		return val;

	if (key->tt == ttypes["nil"])
		rbx_luag_runerror(rl, "table index is nil");

	std::cout << "doing newkey method!\n";

	return newkey(rl, t, key);
}


std::uintptr_t rbx_getmetatable(const rbx_TValue* t)
{
	if (t->tt != ttypes["table"] && t->tt != ttypes["userdata"]) return NULL;
	std::uintptr_t enc_mt = t->Value.p + (t->tt == ttypes["table"] ? offsets::table::metatable : offsets::userdata::metatable);
	return encryption::rbx_decrypt_metatable(enc_mt);
}

const rbx_TValue* rbx_luat_gettm(std::uintptr_t events, std::uintptr_t ename)
{
	const rbx_TValue* tm = rbx_luah_getstr(events, ename);

	if (tm->tt == ttypes["nil"])
		return addresses::rbx_luao_nilobject;

	return tm;
}

const rbx_TValue* rbx_luat_gettmbyobj(std::uintptr_t rl, const rbx_TValue* o, const char* event) // to find event use ttypes
{
	std::uintptr_t mt = rbx_getmetatable(o);

	return (mt ? rbx_luat_gettm(mt, rbx_luas_new(rl, event)) : addresses::rbx_luao_nilobject);
}

void rbx_luav_gettable(std::uintptr_t rl, const rbx_TValue* t, rbx_TValue* key, rbx_TValue* val)
{
	for (int loop = 0; loop < 100; ++loop)
	{
		const rbx_TValue* tm = addresses::rbx_luao_nilobject;

		if (t->tt == ttypes["table"])
		{
			std::uintptr_t h = t->Value.p;
			const rbx_TValue* res = rbx_luah_get(h, key);

			if (res->tt != ttypes["nil"] || (tm = rbx_luat_gettmbyobj(rl, t, "__index"))->tt == ttypes["nil"])
			{
				std::cout << "found value in table!\n";
				setobj(val, res);
				return;
			}
		}
		else if ((tm = rbx_luat_gettmbyobj(rl, t, "__index"))->tt == ttypes["nil"])
			rbx_luag_runerror(rl, "you indexing a fucking userdata without __index");

		if (tm->tt == ttypes["function"])
		{
			rbx_calltmres(rl, val, const_cast<rbx_TValue*>(tm), const_cast<rbx_TValue*>(t), key);
			return;
		}

		t = tm;
	}

	rbx_luag_runerror(rl, "loop in gettable");
}

void rbx_luav_settable(std::uintptr_t rl, const rbx_TValue* t, rbx_TValue* key, rbx_TValue* val)
{
	std::cout << "settable called!\n";
	rbx_TValue temp{};
	for (int loop = 0; loop < 100; ++loop)
	{
		const rbx_TValue* tm = addresses::rbx_luao_nilobject;

		if (t->tt == ttypes["table"])
		{
			std::uintptr_t h = t->Value.p;
			rbx_TValue* oldval = rbx_luah_set(rl, h, key);

			if (oldval->tt != ttypes["nil"] || (tm = rbx_luat_gettmbyobj(rl, t, "__newindex"))->tt == ttypes["nil"])
			{
				std::cout << "overwriting :sans:\n";
				setobj(oldval, val);
				rbx_luac_barriert(rl, h, key);
				return;
			}
		}
		else if ((tm = rbx_luat_gettmbyobj(rl, t, "__newindex"))->tt == ttypes["nil"])
			rbx_luag_runerror(rl, "you indexing fucking userdatas that don't have __newindex on them");

		if (tm->tt == ttypes["function"])
		{
			rbx_calltm(rl, const_cast<rbx_TValue*>(tm), const_cast<rbx_TValue*>(t), key, val);
			return;
		}

		setobj(&temp, tm);
		t = &temp;
	}

	rbx_luag_runerror(rl, "loop in settable");
}

void rbx_getfield(std::uintptr_t rl, int idx, const char* k)
{
	rbx_TValue* table = rbx_index2adr(rl, idx);

	rbx_TValue key{};
	key.Value.p = rbx_luas_new(rl, k);
	key.tt = ttypes["string"];

	rbx_luav_gettable(rl, table, &key, *reinterpret_cast<rbx_TValue**>(rl + offsets::luastate::top));
	rbx_increment_top(rl, 1);
}

void rbx_setfield(std::uintptr_t rl, int idx, const char* k)
{
	rbx_TValue* t = rbx_index2adr(rl, idx);
	rbx_TValue key{};
	key.Value.p = rbx_luas_new(rl, k);
	key.tt = ttypes["string"];

	rbx_luav_settable(rl, t, &key, *reinterpret_cast<rbx_TValue**>(rl + offsets::luastate::top) - 1);
	rbx_decrement_top(rl, 1);
}




