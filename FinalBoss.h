#pragma once
#include "Game.h"
#include <chrono>
#include <thread>

Player CreateVoidstormPhase1();
Player CreateVoidstormPhase2();
void EvolveHeroAttacks(Player& hero, int weaponChoice);
void NarrateReveal(Game& game, Player& hero);
void NarrateEvolution(Game& game, Player& hero, int weaponChoice);
void NarrateVictory(Game& game, Player& hero);
void NarrateDefeat(Game& game);
void FinalBossSequence(Game& game, Player& hero, int weaponChoice);
