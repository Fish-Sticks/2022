#pragma once
#include "structs.h"


extern void fishV_gettable(std::uintptr_t rL, const FishValue* t, FishValue* key, FishStk val);
extern void fishV_settable(std::uintptr_t rL, const FishValue* t, FishValue* key, FishStk val);

#define MAXTAGLOOP 100