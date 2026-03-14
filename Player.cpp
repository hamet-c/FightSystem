#include "Player.h"
#include "Game.h"
#include <chrono>
#include <thread>

Player::Player() {
    playerName = "Fortnite Default";
    playerHealth = 100;
    playerMaxHealth = playerHealth;
    playerDamage = 8;
    playerCooldown = 0;
    characterChoice = 0;

}

Player::Player(string name, int health, int damage, int cooldown, int choice) {
    playerName = name;
    playerHealth = health;
    playerMaxHealth = playerHealth;
    playerDamage = damage;
    playerCooldown = cooldown;
    characterChoice = choice;
}

Player::Player(string name, int health, int damage, int cooldown, int choice, Attacks attacks) {
    playerName = name;
    playerHealth = health;
    playerMaxHealth = playerHealth;
    playerDamage = damage;
    playerCooldown = cooldown;
    characterChoice = choice;
    playerAttacks = attacks;
}

string Player::GetName() {
    return playerName;
}

int Player::GetPlayerChoice() {
    return characterChoice;
}

int Player::GetHealth() {
    return playerHealth;
}

int Player::GetMaxHealth() {
    return playerMaxHealth;
}

int Player::GetAttackDamage() {
    return playerDamage;
}

int Player::GetCooldown() {
    return playerCooldown;
}

Attacks& Player::GetCharacterAttacks() {
    return playerAttacks;
}

Attack Player::GetChosenAttack(int attackChoice) {
    vector<Attack> availableAttacks = playerAttacks.GetAttacks();
    Attack currAttack;

    for (int i = 0; i < playerAttacks.GetNumAttacks(); i++) {
        currAttack = availableAttacks.at(i);

        if (attackChoice == currAttack.GetAssignedNum()) {
            return currAttack;
        }
    }

    // for if none are found
    currAttack.SetAssignedNum(-1);
    return currAttack;
}

int Player::GetTotalAttacksCount() {
    return playerAttacks.GetNumAttacks() + 1;// to account for default character attack
}


void Player::ShowPlayerInfo() {
    cout << endl;
    //cout << playerName << " { " << characterChoice << " }" << endl;// player name and choice number //
    cout << playerName << endl;
    //this_thread::sleep_for(chrono::seconds(1));
    cout << endl;

    cout << "  Health: " << playerHealth << endl;
    //this_thread::sleep_for(chrono::seconds(1));

    cout << "  Damage: " << playerDamage << endl;
    //this_thread::sleep_for(chrono::seconds(1));

    cout << "  Cooldown: " << playerCooldown << endl;
    cout << endl;
}

void Player::ShowAttacksInfo() {
    playerAttacks.DisplayAttacksInfo();
}

void Player::AssignPlayerAttacks(Attacks attacks) {
    playerAttacks = attacks;
}

void Player::AssignPlayerHealth(int healthToAssign) {
    playerHealth = healthToAssign;
}

void Player::TakeDamage(int amount) {
    if (amount > 0)
        playerHealth -= amount;
    if (playerHealth < 0) 
        playerHealth = 0;
}

void Player::HealUp() {
    int healUp = 5;
    int currHealth = GetHealth();
    if (healUp + currHealth <= GetMaxHealth()) {
        AssignPlayerHealth(healUp + currHealth);
        cout << endl;
        cout << GetName() << "'s health recuperated to " << GetHealth() << " by " << healUp << " hp";
        Game::FightPause(1200);
        cout << endl;
    }
    else {
        AssignPlayerHealth(GetMaxHealth());
    }
}

void Player::HealUp(int healthToHeal) {
    if (healthToHeal > 0) {
        int currHealth = GetHealth();
        if (healthToHeal + currHealth <= GetMaxHealth()) {
            AssignPlayerHealth(healthToHeal + currHealth);
            cout << endl;
            cout << GetName() << "'s health recuperated to " << GetHealth() << " by " << healthToHeal << " hp";
            Game::FightPause(1200);
            cout << endl;
        }
        else {
            AssignPlayerHealth(GetMaxHealth());
        }
    }
}

// Status effects
void Player::ApplyStatusEffect(string effect, int duration, int dmgPerTurn) {
    activeStatusEffect = effect;
    statusTurnsRemaining = duration;
    statusDmgPerTurn = dmgPerTurn;
    if (effect == "stun") stunned = true;
}

void Player::ProcessStatusEffects() {
    stunned = false;
    if (activeStatusEffect == "none" || statusTurnsRemaining <= 0) {
        activeStatusEffect = "none";
        return;
    }

    if (activeStatusEffect == "bleed" || activeStatusEffect == "poison") {
        cout << "\t* " << playerName << " takes " << statusDmgPerTurn
             << " " << activeStatusEffect << " damage! *" << endl;
        TakeDamage(statusDmgPerTurn);
        Game::FightPause(800);
    }
    else if (activeStatusEffect == "stun") {
        cout << "\t* " << playerName << " is STUNNED and cannot act! *" << endl;
        stunned = true;
        Game::FightPause(1000);
    }

    statusTurnsRemaining--;
    if (statusTurnsRemaining <= 0) {
        cout << "\t* " << activeStatusEffect << " has worn off " << playerName << " *" << endl;
        activeStatusEffect = "none";
        Game::FightPause(800);
    }
}

bool Player::IsStunned() { return stunned; }

void Player::ClearStatusEffects() {
    activeStatusEffect = "none";
    statusTurnsRemaining = 0;
    statusDmgPerTurn = 0;
    stunned = false;
}

string Player::GetActiveStatusEffect() { return activeStatusEffect; }
int Player::GetStatusTurnsRemaining() { return statusTurnsRemaining; }

// Cooldown pass-throughs
void Player::TickAllCooldowns() { playerAttacks.TickAllCooldowns(); }
bool Player::IsAttackReady(int assignedNum) { return playerAttacks.IsAttackReady(assignedNum); }
void Player::PutAttackOnCooldown(int assignedNum) { playerAttacks.PutAttackOnCooldown(assignedNum); }
