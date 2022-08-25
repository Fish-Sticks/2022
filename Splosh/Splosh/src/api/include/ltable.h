#pragma once
#include "api/include/structs.h"

extern const FishValue* fishH_getstr(std::uintptr_t t, std::uintptr_t key);
extern const FishValue* fishH_get(std::uintptr_t t, const FishValue* key);
extern FishValue* fishH_set(std::uintptr_t rL, std::uintptr_t t, const FishValue* key);


#define fish_gnode(t, i) (get_encrypted(t + offsets::table::node, encryption::table::node) + sizeof(FishNode) * i)
#define fish_gkey(n) (&(n)->key)
#define fish_gval(n) (&(n)->val)
#define fish_gnext(n) ((n)->key.next)

#define fish_lmod(s, size) (static_cast<int>(s & (size - 1)))

#define fish_twoto(x) (static_cast<int>(1 << x))
#define fish_sizenode(t) (fish_twoto( *reinterpret_cast<char*>(t + offsets::table::lsizenode) ))

#define fish_hashpow2(t, n) (fish_gnode(t, fish_lmod((n), fish_sizenode(t))))
#define fish_hashstr(t, str) (reinterpret_cast<FishNode*>(fish_hashpow2(t, get_encrypted(str + offsets::string::hash, encryption::string::hash))))