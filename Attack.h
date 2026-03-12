#ifndef PLAYER_ATTACK_H
#define PLAYER_ATTACK_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class Attack {
public:
	void ShowAttackInfo();
	Attack();
	Attack(string name, int damage, string description, int assignNum);
	Attack(string name, int damage, int assignNum);
	void SetName(string name);
	void SetDamage(int damage);
	void SetDesc(string desc);
	void SetAssignedNum(int assignNum);
	int GetAssignedNum();
	int GetAttackDamage();
	string GetAttackName();
	string GetAttackDesc();

	// New damage range
	void SetMinDamage(int min);
	void SetMaxDamage(int max);
	int GetMinDamage();
	int GetMaxDamage();

	// Crit and miss
	void SetCritChance(float chance);
	void SetCritMultiplier(float mult);
	void SetMissChance(float chance);
	float GetCritChance();
	float GetCritMultiplier();
	float GetMissChance();

	// Cooldown
	void SetCooldownTurns(int turns);
	int GetCooldownTurns();
	void SetCurrentCooldown(int turns);
	int GetCurrentCooldown();
	void TickCooldown();
	bool IsReady();

	// Status effects
	void SetStatusEffect(string effect);
	void SetStatusDuration(int turns);
	void SetStatusDamagePerTurn(int dmg);
	string GetStatusEffect();
	int GetStatusDuration();
	int GetStatusDamagePerTurn();

	// Lightning tag for final boss
	void SetIsLightning(bool val);
	bool GetIsLightning();

	// Damage calculation with variance, crit, miss
	int CalculateDamage();
	bool WasCrit();
	bool WasMiss();

private:
	int assignedNum;
	string attackName;
	string attackDesc;
	int attackDamage;

	// Damage range
	int minDamage = 0;
	int maxDamage = 0;

	// Crit and miss
	float critChance = 0.15f;
	float critMultiplier = 1.5f;
	float missChance = 0.05f;

	// Cooldown
	int cooldownTurns = 0;
	int currentCooldown = 0;

	// Status effects
	string statusEffect = "none";
	int statusDuration = 0;
	int statusDmgPerTurn = 0;

	// Lightning tag
	bool isLightning = false;

	// Last attack flags
	bool lastAttackWasCrit = false;
	bool lastAttackMissed = false;
};

#endif // PLAYER_ATTACK_H
