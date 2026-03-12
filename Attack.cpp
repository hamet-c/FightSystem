#include "Attack.h"

Attack::Attack() {
	attackName = "Run Away";
	attackDesc = "You run from the enemy to recuperate some health";
	attackDamage = 0;
	assignedNum = 2;
	minDamage = 0;
	maxDamage = 0;
	critChance = 0.0f;
	missChance = 0.0f;
}

Attack::Attack(string name, int damage, string description, int assignNum) {
	attackName = name;
	attackDamage = damage;
	attackDesc = description;
	assignedNum = assignNum;
	minDamage = (int)(damage * 0.8);
	maxDamage = (int)(damage * 1.2);
}

Attack::Attack(string name, int damage, int assignNum) {
	attackName = name;
	attackDamage = damage;
	attackDesc = "...";
	assignedNum = assignNum;
	minDamage = (int)(damage * 0.8);
	maxDamage = (int)(damage * 1.2);
}

void Attack::ShowAttackInfo() {
	cout << "\t " << assignedNum << " ) " << attackName << endl;
	if (minDamage > 0 || maxDamage > 0) {
		cout << "\t  - Damage: " << minDamage << " - " << maxDamage << endl;
	}
	else {
		cout << "\t  - Damage: " << attackDamage << endl;
	}
	if (cooldownTurns > 0)
		cout << "\t  - Cooldown: " << cooldownTurns << " turns" << endl;
	if (statusEffect != "none")
		cout << "\t  - Effect: " << statusEffect << " (" << statusDuration << " turns)" << endl;
	cout << "\t  - Description: " << attackDesc << endl;
	cout << endl;
}

// Setters
void Attack::SetName(string name) { attackName = name; }
void Attack::SetDamage(int damage) {
	attackDamage = damage;
	minDamage = (int)(damage * 0.8);
	maxDamage = (int)(damage * 1.2);
}
void Attack::SetDesc(string desc) { attackDesc = desc; }
void Attack::SetAssignedNum(int assignNum) { assignedNum = assignNum; }
void Attack::SetMinDamage(int min) { minDamage = min; }
void Attack::SetMaxDamage(int max) { maxDamage = max; }
void Attack::SetCritChance(float chance) { critChance = chance; }
void Attack::SetCritMultiplier(float mult) { critMultiplier = mult; }
void Attack::SetMissChance(float chance) { missChance = chance; }
void Attack::SetCooldownTurns(int turns) { cooldownTurns = turns; }
void Attack::SetCurrentCooldown(int turns) { currentCooldown = turns; }
void Attack::SetStatusEffect(string effect) { statusEffect = effect; }
void Attack::SetStatusDuration(int turns) { statusDuration = turns; }
void Attack::SetStatusDamagePerTurn(int dmg) { statusDmgPerTurn = dmg; }
void Attack::SetIsLightning(bool val) { isLightning = val; }

// Getters
int Attack::GetAssignedNum() { return assignedNum; }
int Attack::GetAttackDamage() { return attackDamage; }
string Attack::GetAttackName() { return attackName; }
string Attack::GetAttackDesc() { return attackDesc; }
int Attack::GetMinDamage() { return minDamage; }
int Attack::GetMaxDamage() { return maxDamage; }
float Attack::GetCritChance() { return critChance; }
float Attack::GetCritMultiplier() { return critMultiplier; }
float Attack::GetMissChance() { return missChance; }
int Attack::GetCooldownTurns() { return cooldownTurns; }
int Attack::GetCurrentCooldown() { return currentCooldown; }
string Attack::GetStatusEffect() { return statusEffect; }
int Attack::GetStatusDuration() { return statusDuration; }
int Attack::GetStatusDamagePerTurn() { return statusDmgPerTurn; }
bool Attack::GetIsLightning() { return isLightning; }
bool Attack::WasCrit() { return lastAttackWasCrit; }
bool Attack::WasMiss() { return lastAttackMissed; }

// Cooldown management
void Attack::TickCooldown() {
	if (currentCooldown > 0) currentCooldown--;
}
bool Attack::IsReady() {
	return currentCooldown <= 0;
}

// Core damage calculation with variance, crit, and miss
int Attack::CalculateDamage() {
	lastAttackWasCrit = false;
	lastAttackMissed = false;

	// Miss check
	if (missChance > 0.0f) {
		float roll = (float)(rand() % 100) / 100.0f;
		if (roll < missChance) {
			lastAttackMissed = true;
			return 0;
		}
	}

	// Base damage in range [minDamage, maxDamage]
	int dmg;
	int range = maxDamage - minDamage;
	if (range > 0) {
		dmg = minDamage + (rand() % (range + 1));
	}
	else {
		dmg = attackDamage;
	}

	// Crit check
	if (critChance > 0.0f) {
		float roll = (float)(rand() % 100) / 100.0f;
		if (roll < critChance) {
			lastAttackWasCrit = true;
			dmg = (int)(dmg * critMultiplier);
		}
	}

	return dmg;
}
