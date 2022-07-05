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

// 50% cur health
const float SIT_BACK_HEALTH_MAX_ALL = .5f;
//  Max amount to heal if sit back.
const int SIT_BACK_HEAL_AMOUNT_MAX = 5;



const float HUMAN_SIT_BACK_RATE = .4f;
// replenishes 40% of max health
const float HUMAN_POTION_RATE = .4f;


// More aggresive than humans
const float GOBLIN_SIT_BACK_RATE = .2f;
// Chance goblin will attempt bribe if has coins
const float GOBLIN_BRIBE_RATE = .4f;
// Chance bribe is successful
const float GOBLIN_BRIBE_CHANCE = .25f;