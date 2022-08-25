#pragma once
#include <cstdint>


void fish_increment_top(std::uintptr_t rL, std::int32_t amount);
void fish_decrement_top(std::uintptr_t rL, std::int32_t amount);
std::int32_t fish_type(std::uintptr_t rL, std::int32_t idx);

#define fish_isfunction(L, n) (fish_type(L, (n)) == fish_TFUNCTION)
#define fish_istable(L, n) (fish_type(L, (n)) == fish_TTABLE)
#define fish_islightuserdata(L, n) (fish_type(L, (n)) == fish_TLIGHTUSERDATA)
#define fish_isnil(L, n) (fish_type(L, (n)) == fish_TNIL)
#define fish_isboolean(L, n) (fish_type(L, (n)) == fish_TBOOLEAN)
#define fish_isvector(L, n) (fish_type(L, (n)) == fish_TVECTOR)
#define fish_isthread(L, n) (fish_type(L, (n)) == fish_TTHREAD)
#define fish_isnone(L, n) (fish_type(L, (n)) == fish_TNONE)
#define fish_isnoneornil(L, n) (fish_type(L, (n)) <= fish_TNIL)


#define fish_ttype(o) (o->tt)
#define fish_ttisnil(o) (fish_ttype(o) == fish_TNIL)
#define fish_ttisnumber(o) (fish_ttype(o) == fish_TNUMBER)
#define fish_ttisstring(o) (fish_ttype(o) == fish_TSTRING)
#define fish_ttistable(o) (fish_ttype(o) == fish_TTABLE)
#define fish_ttisfunction(o) (fish_ttype(o) == fish_TFUNCTION)
#define fish_ttisboolean(o) (fish_ttype(o) == fish_TBOOLEAN)
#define fish_ttisuserdata(o) (fish_ttype(o) == fish_TUSERDATA)
#define fish_ttisthread(o) (fish_ttype(o) == fish_TTHREAD)
#define fish_ttislightuserdata(o) (fish_ttype(o) == fish_TLIGHTUSERDATA)
#define fish_ttisvector(o) (fish_ttype(o) == fish_TVECTOR)
#define fish_ttisupval(o) (fish_ttype(o) == fish_TUPVAL)

#define fish_setobj(obj1, obj2) \
    { \
        const FishValue* o2 = (obj2); \
        FishValue* o1 = (obj1); \
        *o1 = *o2; \
    }