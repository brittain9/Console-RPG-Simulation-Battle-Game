#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <random>
#include <chrono>
#include <set>
#include <array>
#include <ctime>
#include <cmath>

#include "timer.h"
#include "rng.h"
#include "Entity.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

// GLOBALS
// make easier to balance
const int MAX_POINTS = 10;
// Base damage dealt. Attack member will increase this
const float BASE_ATTACK_MULTIPLIER = 1.0f;
const int BASE_ATTACK_MAX = 10;
const float CRITICAL_HIT_CHANCE = 0.05f;

const float LEVEL_ATT_MULT = 0.5f;
const int LEVEL_ATT_MAX = 1;
const float LEVEL_CRIT_CHANCE = 0.01f;

const float CRITICAL_HIT_DAMAGE_MULTI = .5f;


// Base multiplier for damage dealt.
const float BASE_DEFENSE_MUTLIPLIER = 1.0f;
const int BASE_DEFENSE_DAMAGE_MAX = 3;
const float REFLECT_DAMAGE_CHANCE = 0.05f;

const float REFLECT_DAMAGE_MULTI = 1.0f;

const float LEVEL_DEF_MULT = 0.5f;
const int LEVEL_DEF_MAX = 1;
const float LEVEL_REFLECT_CHANCE = 0.015f;