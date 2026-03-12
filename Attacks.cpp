#include "Attacks.h"

void Attacks::AssignAttacks(int attackAmount) {
	vector<Attack> attacksToAssign;
	Attack currAttack;
	string currName;
	string currDesc;
	int currDamage;


	for (int i = 0; i < attackAmount; i++) {
		cout << " | ASSIGN VALUES | " << endl << endl;

		cout << "\tAttack name: ";
		cin >> currName;
		cout << endl << endl;

		cout << "\tAttack damage: ";
		cin >> currDamage;
		cout << endl << endl;

		cout << "\tAttack description: ";
		cin >> currDesc;
		cout << endl << endl;

		currAttack.SetName(currName);
		currAttack.SetDamage(currDamage);
		currAttack.SetDesc(currDesc);

		attacks.push_back(currAttack);
	}

	numOfAttacks += attackAmount;
}

void Attacks::AssignAttacks(vector<Attack> attacksToAssign) {
	attacks = attacksToAssign;
	numOfAttacks = attacksToAssign.size();
}

/// <summary>
/// 
/// </summary>
/// <param name="attack"></param>
void Attacks::AssignAttack(Attack attack) {
	numOfAttacks++;
	attacks.push_back(attack);
}

/// <summary>
/// 
/// </summary>
/// <param name="name"></param>
/// <param name="damage"></param>
void Attacks::AssignAttack(string name, int damage, int assignedNum) {
	Attack attack;
	attack.SetName(name);
	attack.SetDamage(damage);
	attack.SetDesc("No description");
	attack.SetAssignedNum(assignedNum);

	numOfAttacks++;
	attacks.push_back(attack);
}

/// <summary>
/// 
/// </summary>
/// <param name="name"></param>
/// <param name="damage"></param>
/// <param name="desc"></param>
void Attacks::AssignAttack(string name, int damage, string desc, int assignedNum) {
	Attack attack;
	attack.SetName(name);
	attack.SetDamage(damage);
	attack.SetDesc(desc);
	attack.SetAssignedNum(assignedNum);

	numOfAttacks++;
	attacks.push_back(attack);
}

int Attacks::GetNumAttacks() {
	return numOfAttacks;
}

vector<Attack> Attacks::GetAttacks() {
	return attacks;
}

void Attacks::DisplayAttacksInfo() {

	cout << endl << endl;
	cout << "\t -- MOVESET --" << endl;
	cout << endl;
	for (int i = 0; i < GetNumAttacks(); i++) {
		attacks.at(i).ShowAttackInfo();
	}
	cout << endl << endl;
}

void Attacks::TickAllCooldowns() {
	for (int i = 0; i < (int)attacks.size(); i++) {
		attacks[i].TickCooldown();
	}
}

bool Attacks::IsAttackReady(int assignedNum) {
	for (int i = 0; i < (int)attacks.size(); i++) {
		if (attacks[i].GetAssignedNum() == assignedNum) {
			return attacks[i].IsReady();
		}
	}
	return true;
}

void Attacks::PutAttackOnCooldown(int assignedNum) {
	for (int i = 0; i < (int)attacks.size(); i++) {
		if (attacks[i].GetAssignedNum() == assignedNum) {
			attacks[i].SetCurrentCooldown(attacks[i].GetCooldownTurns());
			return;
		}
	}
}

Attack& Attacks::GetAttackRef(int assignedNum) {
	for (int i = 0; i < (int)attacks.size(); i++) {
		if (attacks[i].GetAssignedNum() == assignedNum) {
			return attacks[i];
		}
	}
	return attacks[0];
}
