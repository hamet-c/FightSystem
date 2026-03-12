#include "Game.h"
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

Game::Game() {
	Players defaults = Players();
	heroes = defaults.GetDefaultHeroes();
	villains = defaults.GetDefaultVillains();

	rounds = 4;
}

Game::Game(int fightingRounds) {
	Players defaults = Players();
	heroes = defaults.GetDefaultHeroes();
	villains = defaults.GetDefaultVillains();

	rounds = fightingRounds;
}

Game::Game(vector<Player> heroesList, vector<Player> villainsList, int fightingRounds) {
	heroes = heroesList;
	villains = villainsList;
	rounds = fightingRounds;
}

void Game::FightingScenario1() {
	// MODIFY : STILL DECIDING IF INCLUDING SCENARIOS OR NOT //
}

void Game::PlayGame() {
	enemySpares = rand() % 2; //  0  OR 1  //
	this_thread::sleep_for(chrono::seconds(1));
	//enemyPleads = rand() % 2;
	//cout << enemySpares << endl;

	Intro();

	SpaceMax();

	RunTheFights();

	SpaceMax();

	if (chosenPlayer.GetHealth() <= 0) {
		WriteSentenceNoEndl("You died. Game Over.");
		cout << endl;
	}
	else if (enemy.GetHealth() <= 0) {
		WriteSentenceNoEndl("You Defeated The Enemy.");
		cout << endl;
	}
	else if ( (youSpare && enemyPleads) || (youPlead && enemySpares) ) {
		WriteSentenceNoEndl("The battle only brought about the realization that conflict was never necessary,");
		cout << endl;
		WriteSentenceNoEndl("only the result of evil intents and lack of understanding.");
		cout << endl;
	}
	else if ( (youSpare && !enemyPleads) || (enemyPleads && !youSpare)) {
		WriteSentenceNoEndl("...Not the best ending I'd say.");
		cout << endl;
	}
	cout << endl << endl << endl << endl;
	cout << endl << endl << endl << endl;
}

void Game::Intro() {
	cout << "Choose your hero by number" << endl;

	this_thread::sleep_for(chrono::seconds(3));
	cout << "---------------------------" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << endl;

	for (int i = 0; i < heroes.size() - 1; ++i) {// this allows us to not show the hidden characters

		cout << "\t\t   { " << i << " }";
		heroes.at(i).ShowPlayerInfo();
		this_thread::sleep_for(chrono::seconds(1));
		cout << "---------";
		this_thread::sleep_for(chrono::seconds(1));
		cout << "------------";
		this_thread::sleep_for(chrono::seconds(1));
		cout << "------" << endl;
		this_thread::sleep_for(chrono::seconds(2));

	}

	int choice = -1;
	while (true) {
		cout << "Enter Selection (number): ";
		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Please enter a valid number." << endl;
			continue;
		}
		if (choice >= 0 && choice < (int)(heroes.size() - 1)) {
			break;
		}
		cout << "Invalid choice. Please pick a number between 0 and " << (heroes.size() - 2) << "." << endl;
	}

	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;

	chosenPlayer = heroes.at(choice);


	int villianChoice = rand() % villains.size();
	enemy = villains.at(villianChoice);
	//enemy = villains.at(0);// for testing

	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;

	// MODIFY : ADD SCENARIO HERE : BEFORE FIGHTING //
	// BeforeFightEscenario(); // story before fighting

	cout << "...................................................." << endl;
	cout << endl;

	cout << "| YOUR CHOICE |" << endl;
	chosenPlayer.ShowPlayerInfo();

	cout << endl;

	cout << "  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~" << endl;
	cout << endl;

	cout << "| MATCHUP |" << endl;
	enemy.ShowPlayerInfo();
	cout << endl;
	cout << "...................................................." << endl;
	cout << endl;
	cout << endl << endl;
	
	this_thread::sleep_for(chrono::seconds(6));
}

void Game::RunTheFights() {
	while (chosenPlayer.GetHealth() > 0 && enemy.GetHealth() > 0) {

		if (youPlead && enemySpares && chosenPlayer.GetHealth() <= 15) {
			break;
		}
		if (enemyPleads && youSpare && enemy.GetHealth() <= 15) {
			break;
		}

		TimeToAttack();
		if (enemy.GetHealth() <= 0) break;
		if (enemy.GetHealth() <= 15) {
			enemyPleads = true;
			enemy.GetCharacterAttacks().AssignAttack("Plead", 0, "Maybe he'll let me live", chosenPlayer.GetTotalAttacksCount() + 1); // makes a new attack
			this_thread::sleep_for(chrono::seconds(3));
		}


		EnemyAttacks();
		if (chosenPlayer.GetHealth() <= 0) break;
		if (chosenPlayer.GetHealth() <= 15) {
			SpaceMed();

			cout << "'Will you plead for your life?'" << endl;
			this_thread::sleep_for(chrono::seconds(4));
			WriteSentenceNoEndl("Enter (1) - Yes or (0) - No: ");

			int decision;
			cin >> decision;

			SpaceMax();
			if (decision == 1) {
				chosenPlayer.GetCharacterAttacks().AssignAttack("* Plead *", 0, "Maybe I'll survive this at least", chosenPlayer.GetTotalAttacksCount() + 1); // makes a new attack
			}
		}

	}
}

void Game::TimeToAttack() {
	// Process status effects at start of turn
	chosenPlayer.ProcessStatusEffects();
	if (chosenPlayer.GetHealth() <= 0) return;
	if (chosenPlayer.IsStunned()) return;

	// Tick cooldowns
	chosenPlayer.TickAllCooldowns();

	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "\t     |  Your Health: " << chosenPlayer.GetHealth() << "  ||  " << enemy.GetName() << "'s Health: " << enemy.GetHealth() << "  | " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	if (chosenPlayer.GetActiveStatusEffect() != "none") {
		cout << "\t     [" << chosenPlayer.GetActiveStatusEffect() << " - " << chosenPlayer.GetStatusTurnsRemaining() << " turns left]" << endl;
	}
	if (enemy.GetActiveStatusEffect() != "none") {
		cout << "\t     [" << enemy.GetName() << ": " << enemy.GetActiveStatusEffect() << " - " << enemy.GetStatusTurnsRemaining() << " turns left]" << endl;
	}
	cout << endl;

	this_thread::sleep_for(chrono::seconds(1));

	cout << endl;
	cout << "    *[ It's your turn to attack, pick one of your available actions ]*" << endl;
	cout << endl << endl;
	this_thread::sleep_for(chrono::seconds(3));

	cout << "    Available actions" << endl << endl;
	cout << "\t  1) Default Attack" << endl;
	cout << "\t  - Damage: " << chosenPlayer.GetAttackDamage() << endl;
	chosenPlayer.ShowAttacksInfo();

	int actionChoice;
	cout << "Your selection: ";
	cin >> actionChoice;

	// Check if attack is on cooldown
	if (actionChoice > 1 && !chosenPlayer.IsAttackReady(actionChoice)) {
		cout << endl << "That attack is on cooldown! You hesitate and lose your turn." << endl;
		this_thread::sleep_for(chrono::seconds(2));
		return;
	}

	int heroDmg;
	if (actionChoice == 1) {
		heroDmg = chosenPlayer.GetAttackDamage();
		Waiting();

		cout << "You attack them with your basic attack and deal " << heroDmg << " damage to " << enemy.GetName() << " " << endl;
		enemy.TakeDamage(heroDmg);
		this_thread::sleep_for(chrono::seconds(4));

		cout << endl;
		cout << "Now " << enemy.GetName() << " has " << enemy.GetHealth() << " health left" << endl;
		this_thread::sleep_for(chrono::seconds(3));
	}
	else if (actionChoice > 1) {
		Attack& chosenAttack = chosenPlayer.GetCharacterAttacks().GetAttackRef(actionChoice);

		Waiting();
		cout << endl << endl;

		if (actionChoice == 2) {
			cout << "You run away" << endl;
			chosenPlayer.HealUp(rand() % 40 + 10);
		}
		else if (enemyPleads && enemy.GetHealth() <= 15) {
			if (youSpare) {
				cout << endl;
				this_thread::sleep_for(chrono::seconds(2));
				cout << "You tell " << enemy.GetName() << ", 'Don't worry, it was never that serious to begin with'" << endl;
			}
			else {
				cout << endl;
				this_thread::sleep_for(chrono::seconds(2));
				cout << "You say to " << enemy.GetName() << ", 'Really bruh'" << endl;
			}
		}
		else {
			if (actionChoice == chosenPlayer.GetTotalAttacksCount() && chosenPlayer.GetHealth() <= 15) {
				this_thread::sleep_for(chrono::seconds(2));
				cout << "You plead to " << enemy.GetName() << " hoping for a second chance at life." << endl;
				youPlead = true;
			}
			else {
				// Use new damage calculation
				heroDmg = chosenAttack.CalculateDamage();

				if (chosenAttack.WasMiss()) {
					this_thread::sleep_for(chrono::seconds(1));
					cout << "You try the " << chosenAttack.GetAttackName() << " but... MISS!" << endl;
					this_thread::sleep_for(chrono::seconds(2));
				}
				else {
					this_thread::sleep_for(chrono::seconds(1));
					if (chosenAttack.WasCrit()) {
						cout << endl;
						cout << "\t*** CRITICAL HIT! ***" << endl;
						this_thread::sleep_for(chrono::seconds(1));
					}
					cout << "You do the " << chosenAttack.GetAttackName() << " -> " << chosenAttack.GetAttackDesc() << " and deal " << heroDmg << " damage to " << enemy.GetName() << " " << endl;
					enemy.TakeDamage(heroDmg);

					// Apply status effect if attack has one
					if (chosenAttack.GetStatusEffect() != "none") {
						int effectRoll = rand() % 100;
						if (effectRoll < 60) {
							cout << "\t* " << enemy.GetName() << " is afflicted with " << chosenAttack.GetStatusEffect() << "! *" << endl;
							enemy.ApplyStatusEffect(chosenAttack.GetStatusEffect(), chosenAttack.GetStatusDuration(), chosenAttack.GetStatusDamagePerTurn());
							this_thread::sleep_for(chrono::seconds(1));
						}
					}

					cout << endl;
					this_thread::sleep_for(chrono::seconds(3));
					cout << "Now " << enemy.GetName() << " has " << enemy.GetHealth() << " health left" << endl;
				}

				// Put attack on cooldown
				chosenPlayer.PutAttackOnCooldown(actionChoice);
			}
		}

		if (enemy.GetHealth() <= 20 && enemy.GetHealth() > 15) {
			EnemyInDisdainLevel1();
		}
		else if (enemy.GetHealth() <= 15 && enemy.GetHealth() >= 5) {
			enemyPleads = true;
			EnemyInDisdainLevel2();
		}
	}
	else {
		this_thread::sleep_for(chrono::seconds(1));
		cout << "You do nothing" << endl;
	}
	cout << endl;
	cout << endl;
	Waiting();
	cout << endl;
	cout << endl;
}

void Game::EnemyAttacks() {
	// Process status effects at start of turn
	enemy.ProcessStatusEffects();
	if (enemy.GetHealth() <= 0) return;
	if (enemy.IsStunned()) return;

	// Tick cooldowns
	enemy.TickAllCooldowns();

	if (!enemyPleads) {
		int attackChoice = ChooseEnemyAttack(enemy, chosenPlayer);

		if (attackChoice == 1) {
			int enemyDmg = enemy.GetAttackDamage();
			cout << enemy.GetName() << " hits you with their default and deals " << enemyDmg << " damage" << endl;
			this_thread::sleep_for(chrono::seconds(4));
			cout << endl;

			chosenPlayer.TakeDamage(enemyDmg);
			cout << "You now have " << chosenPlayer.GetHealth() << " health left" << endl;
			this_thread::sleep_for(chrono::seconds(3));
		}
		else if (attackChoice == 2) {
			cout << enemy.GetName() << " runs..." << endl;
			enemy.HealUp(rand() % 40 + 10);
		}
		else if (youPlead && chosenPlayer.GetHealth() <= 15) {
			if (enemySpares) {
				cout << endl;
				cout << enemy.GetName() << " spares you and says: '";
				WriteSentenceNoEndl("I never intended to kill you in the first place");
				cout << "'" << endl;
				this_thread::sleep_for(chrono::seconds(4));
			}
			else {
				cout << endl;
				cout << enemy.GetName() << " says: '";
				WriteSentenceNoEndl("WOMP WOMP...");
				cout << "'" << endl;
				this_thread::sleep_for(chrono::seconds(3));
			}
		}
		else {
			Attack& enemyAttack = enemy.GetCharacterAttacks().GetAttackRef(attackChoice);
			int enemyDmg = enemyAttack.CalculateDamage();

			if (enemyAttack.WasMiss()) {
				cout << enemy.GetName() << " tries " << enemyAttack.GetAttackName() << " but... MISS!" << endl;
				this_thread::sleep_for(chrono::seconds(2));
			}
			else {
				if (enemyAttack.WasCrit()) {
					cout << endl;
					cout << "\t*** " << enemy.GetName() << " lands a CRITICAL HIT! ***" << endl;
					this_thread::sleep_for(chrono::seconds(1));
				}
				cout << enemy.GetName() << " attacks you with " << enemyAttack.GetAttackName() << " -> " << enemyAttack.GetAttackDesc() << " and deals " << enemyDmg << " damage" << endl;
				this_thread::sleep_for(chrono::seconds(3));
				cout << endl;

				chosenPlayer.TakeDamage(enemyDmg);

				// Apply status effect
				if (enemyAttack.GetStatusEffect() != "none") {
					int effectRoll = rand() % 100;
					if (effectRoll < 60) {
						cout << "\t* You are afflicted with " << enemyAttack.GetStatusEffect() << "! *" << endl;
						chosenPlayer.ApplyStatusEffect(enemyAttack.GetStatusEffect(), enemyAttack.GetStatusDuration(), enemyAttack.GetStatusDamagePerTurn());
						this_thread::sleep_for(chrono::seconds(1));
					}
				}

				cout << "Now you have " << chosenPlayer.GetHealth() << " health left" << endl;
				this_thread::sleep_for(chrono::seconds(3));
			}

			// Put attack on cooldown
			enemy.PutAttackOnCooldown(attackChoice);
		}
	}
	else if (enemyPleads && youSpare) {
		cout << endl << endl << endl;
		cout << endl << endl << endl;
		cout << enemy.GetName() << " Pleads to you and you spare them" << endl;
		cout << endl;
		this_thread::sleep_for(chrono::seconds(2));
		cout << endl;
		cout << endl;
		cout << "You decide to spare who was once considered your enemy" << endl;
		cout << endl;
		this_thread::sleep_for(chrono::seconds(4));
		cout << endl;
		cout << "    * " << enemy.GetName() << " Is forever grateful for your mercy" << endl;
		this_thread::sleep_for(chrono::seconds(3));
	}
	else if (enemyPleads && !youSpare) {
		cout << endl << endl << endl;
		cout << endl << endl << endl;
		cout << enemy.GetName() << " falls down and cries" << endl;
		this_thread::sleep_for(chrono::seconds(2));
	}

	cout << endl;
	cout << endl;
	Waiting();
	cout << endl;
	cout << endl;
}

int Game::ChooseEnemyAttack(Player& attacker, Player& target) {
	int attackerHP = attacker.GetHealth();
	int attackerMaxHP = attacker.GetMaxHealth();
	int targetHP = target.GetHealth();
	float hpPercent = (float)attackerHP / (float)attackerMaxHP;

	// Defensive: heal when below 30% HP (70% chance)
	if (hpPercent < 0.30f && (rand() % 100) < 70) {
		return 2; // Run Away / heal
	}

	// Aggressive: when target is low, use strongest available attack
	if (targetHP < target.GetMaxHealth() * 0.25) {
		vector<Attack> attacks = attacker.GetCharacterAttacks().GetAttacks();
		int bestAssign = 1;
		int bestDmg = attacker.GetAttackDamage();
		for (int i = 0; i < (int)attacks.size(); i++) {
			if (attacks[i].GetAssignedNum() != 2 && attacker.IsAttackReady(attacks[i].GetAssignedNum())) {
				if (attacks[i].GetMaxDamage() > bestDmg) {
					bestDmg = attacks[i].GetMaxDamage();
					bestAssign = attacks[i].GetAssignedNum();
				}
			}
		}
		return bestAssign;
	}

	// Normal: pick a random ready attack
	int totalAttacks = attacker.GetTotalAttacksCount();
	int choice = (rand() % totalAttacks) + 1;

	// If on cooldown, fall back to default
	if (choice > 1 && !attacker.IsAttackReady(choice)) {
		choice = 1;
	}

	return choice;
}

void Game::Waiting() {
	cout << endl;
	this_thread::sleep_for(chrono::milliseconds(400));
	cout << "..";
	this_thread::sleep_for(chrono::milliseconds(400));
	cout << "..";
	this_thread::sleep_for(chrono::milliseconds(400));
	cout << "..";
	cout << endl << endl;
}

void Game::SpaceMax() {
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
}

void Game::SpaceMed() {
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << endl;
}

void Game::EnemyInDisdainLevel1() {
	this_thread::sleep_for(chrono::seconds(1));
	cout << endl;
	cout << endl;
	cout << "   * " << enemy.GetName() << " Is losing enough health to question the fight" << endl;
	this_thread::sleep_for(chrono::seconds(3));

}

void Game::EnemyInDisdainLevel2() {
	this_thread::sleep_for(chrono::seconds(1));
	cout << endl;
	cout << "   * " << enemy.GetName() << " says he gives up. WILL YOU SPARE HIM???" << endl;
	cout << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << "YES (1), NO (0): ";

	int decision;
	cin >> decision;
	if (decision == 0 || decision == 1) {
		youSpare = decision;
	}
	else {
		youSpare = true;
	}
}

void Game::WriteSentenceNoEndl(string sentence) {
	for (int i = 0; i < sentence.size(); i++) {
		cout << sentence.at(i);

		if (i % 21 == 0) {
			this_thread::sleep_for(chrono::milliseconds(700));
		}
		else {
			this_thread::sleep_for(chrono::milliseconds(150));
		}
	}
}

bool Game::StoryModeFight(Player PlayerCharacter, Player EnemyChar) {
	cout << "Starting fight between " << PlayerCharacter.GetName() << " and " << EnemyChar.GetName() << "\n";
	bool playersTurn = true;
	while (PlayerCharacter.GetHealth() > 0 && EnemyChar.GetHealth() > 0) {
		cout << "---------------------------------------------\n";
		cout << PlayerCharacter.GetName() << " HP: " << PlayerCharacter.GetHealth() << "  |  " << EnemyChar.GetName() << " HP: " << EnemyChar.GetHealth() << "\n";
		cout << "---------------------------------------------\n";

		if (playersTurn) {
			// Process status effects
			PlayerCharacter.ProcessStatusEffects();
			if (PlayerCharacter.GetHealth() <= 0) break;
			if (PlayerCharacter.IsStunned()) { playersTurn = !playersTurn; this_thread::sleep_for(chrono::seconds(1)); continue; }
			PlayerCharacter.TickAllCooldowns();

			cout << "It's " << PlayerCharacter.GetName() << "'s turn.\n";
			cout << "1) Default attack (damage: " << PlayerCharacter.GetAttackDamage() << ")\n";
			PlayerCharacter.ShowAttacksInfo();
			int choice = 1;
			cout << "Choose action (enter number, default 1): ";
			cin >> choice;

			if (choice <= 1) {
				int dmg = PlayerCharacter.GetAttackDamage();
				cout << PlayerCharacter.GetName() << " deals " << dmg << " damage to " << EnemyChar.GetName() << "\n";
				EnemyChar.TakeDamage(dmg);
			}
			else if (choice == 2) {
				cout << PlayerCharacter.GetName() << " runs to recuperate!" << endl;
				PlayerCharacter.HealUp(rand() % 40 + 10);
			}
			else {
				if (!PlayerCharacter.IsAttackReady(choice)) {
					cout << "That attack is on cooldown! Turn wasted.\n";
				}
				else {
					Attack& atk = PlayerCharacter.GetCharacterAttacks().GetAttackRef(choice);
					int dmg = atk.CalculateDamage();
					if (atk.WasMiss()) {
						cout << PlayerCharacter.GetName() << " tries " << atk.GetAttackName() << " but... MISS!\n";
					}
					else {
						if (atk.WasCrit()) cout << "\t*** CRITICAL HIT! ***\n";
						cout << PlayerCharacter.GetName() << " uses " << atk.GetAttackName() << " and deals " << dmg << " damage\n";
						EnemyChar.TakeDamage(dmg);
						if (atk.GetStatusEffect() != "none" && (rand() % 100) < 60) {
							cout << "\t* " << EnemyChar.GetName() << " is afflicted with " << atk.GetStatusEffect() << "! *\n";
							EnemyChar.ApplyStatusEffect(atk.GetStatusEffect(), atk.GetStatusDuration(), atk.GetStatusDamagePerTurn());
						}
					}
					PlayerCharacter.PutAttackOnCooldown(choice);
				}
			}
		}
		else {
			// Process status effects
			EnemyChar.ProcessStatusEffects();
			if (EnemyChar.GetHealth() <= 0) break;
			if (EnemyChar.IsStunned()) { playersTurn = !playersTurn; this_thread::sleep_for(chrono::seconds(1)); continue; }
			EnemyChar.TickAllCooldowns();

			cout << "It's " << EnemyChar.GetName() << "'s turn.\n";
			int choice = ChooseEnemyAttack(EnemyChar, PlayerCharacter);

			if (choice <= 1) {
				int dmg = EnemyChar.GetAttackDamage();
				cout << EnemyChar.GetName() << " deals " << dmg << " damage to " << PlayerCharacter.GetName() << "\n";
				PlayerCharacter.TakeDamage(dmg);
			}
			else if (choice == 2) {
				cout << EnemyChar.GetName() << " retreats to heal!\n";
				EnemyChar.HealUp(rand() % 40 + 10);
			}
			else {
				Attack& atk = EnemyChar.GetCharacterAttacks().GetAttackRef(choice);
				int dmg = atk.CalculateDamage();
				if (atk.WasMiss()) {
					cout << EnemyChar.GetName() << " tries " << atk.GetAttackName() << " but... MISS!\n";
				}
				else {
					if (atk.WasCrit()) cout << "\t*** " << EnemyChar.GetName() << " CRITICAL HIT! ***\n";
					cout << EnemyChar.GetName() << " uses " << atk.GetAttackName() << " and deals " << dmg << " damage\n";
					PlayerCharacter.TakeDamage(dmg);
					if (atk.GetStatusEffect() != "none" && (rand() % 100) < 60) {
						cout << "\t* " << PlayerCharacter.GetName() << " is afflicted with " << atk.GetStatusEffect() << "! *\n";
						PlayerCharacter.ApplyStatusEffect(atk.GetStatusEffect(), atk.GetStatusDuration(), atk.GetStatusDamagePerTurn());
					}
				}
				EnemyChar.PutAttackOnCooldown(choice);
			}
		}

		playersTurn = !playersTurn;
		this_thread::sleep_for(chrono::seconds(1));
	}

	cout << "\nFight ended.\n";
	if (PlayerCharacter.GetHealth() <= 0) {
		cout << PlayerCharacter.GetName() << " has been defeated.\n";
	}
	if (EnemyChar.GetHealth() <= 0) {
		cout << EnemyChar.GetName() << " has been defeated.\n";
	}
	cout << "\n";
	if (EnemyChar.GetHealth() <= 0 && PlayerCharacter.GetHealth() > 0) return true;
	return false;
}

bool Game::BossFight(Player& hero, Player& boss, bool lightningAbsorbed) {
	cout << "Starting fight between " << hero.GetName() << " and " << boss.GetName() << "\n";
	this_thread::sleep_for(chrono::seconds(2));
	bool playersTurn = true;

	while (hero.GetHealth() > 0 && boss.GetHealth() > 0) {
		cout << "=============================================\n";
		cout << "  " << hero.GetName() << " HP: " << hero.GetHealth() << "  |  " << boss.GetName() << " HP: " << boss.GetHealth() << "\n";
		cout << "=============================================\n";
		if (hero.GetActiveStatusEffect() != "none")
			cout << "  [You: " << hero.GetActiveStatusEffect() << " - " << hero.GetStatusTurnsRemaining() << " turns]\n";
		if (boss.GetActiveStatusEffect() != "none")
			cout << "  [Boss: " << boss.GetActiveStatusEffect() << " - " << boss.GetStatusTurnsRemaining() << " turns]\n";
		cout << endl;

		if (playersTurn) {
			hero.ProcessStatusEffects();
			if (hero.GetHealth() <= 0) break;
			if (hero.IsStunned()) { playersTurn = !playersTurn; this_thread::sleep_for(chrono::seconds(1)); continue; }
			hero.TickAllCooldowns();

			cout << "Your turn.\n";
			cout << "1) Default attack (damage: " << hero.GetAttackDamage() << ")\n";
			hero.ShowAttacksInfo();
			int choice = 1;
			cout << "Choose action: ";
			cin >> choice;

			if (choice <= 1) {
				int dmg = hero.GetAttackDamage();
				cout << hero.GetName() << " strikes for " << dmg << " damage!\n";
				boss.TakeDamage(dmg);
			}
			else if (choice == 2) {
				cout << hero.GetName() << " retreats to recover!\n";
				hero.HealUp(rand() % 40 + 10);
			}
			else {
				if (!hero.IsAttackReady(choice)) {
					cout << "That attack is on cooldown! Turn lost.\n";
				}
				else {
					Attack& atk = hero.GetCharacterAttacks().GetAttackRef(choice);
					int dmg = atk.CalculateDamage();

					if (atk.WasMiss()) {
						cout << hero.GetName() << " tries " << atk.GetAttackName() << " but... MISS!\n";
					}
					else {
						// Lightning absorption mechanic
						if (lightningAbsorbed && atk.GetIsLightning()) {
							dmg = dmg / 4;
							if (atk.WasCrit()) cout << "\t*** CRITICAL HIT! ***\n";
							cout << hero.GetName() << " uses " << atk.GetAttackName() << " for " << dmg << " damage!\n";
							cout << "\t* The Voidstorm ABSORBS your lightning! It barely felt that! *\n";
							this_thread::sleep_for(chrono::seconds(2));
						}
						else {
							if (atk.WasCrit()) cout << "\t*** CRITICAL HIT! ***\n";
							cout << hero.GetName() << " uses " << atk.GetAttackName() << " and deals " << dmg << " damage!\n";
						}
						boss.TakeDamage(dmg);

						if (atk.GetStatusEffect() != "none" && (rand() % 100) < 60) {
							cout << "\t* " << boss.GetName() << " is afflicted with " << atk.GetStatusEffect() << "! *\n";
							boss.ApplyStatusEffect(atk.GetStatusEffect(), atk.GetStatusDuration(), atk.GetStatusDamagePerTurn());
						}
					}
					hero.PutAttackOnCooldown(choice);
				}
			}
		}
		else {
			boss.ProcessStatusEffects();
			if (boss.GetHealth() <= 0) break;
			if (boss.IsStunned()) { playersTurn = !playersTurn; this_thread::sleep_for(chrono::seconds(1)); continue; }
			boss.TickAllCooldowns();

			cout << boss.GetName() << "'s turn.\n";
			int choice = ChooseEnemyAttack(boss, hero);

			if (choice <= 1) {
				int dmg = boss.GetAttackDamage();
				cout << boss.GetName() << " strikes for " << dmg << " damage!\n";
				hero.TakeDamage(dmg);
			}
			else if (choice == 2) {
				cout << boss.GetName() << " retreats to absorb ambient energy!\n";
				boss.HealUp(rand() % 30 + 15);
			}
			else {
				Attack& atk = boss.GetCharacterAttacks().GetAttackRef(choice);
				int dmg = atk.CalculateDamage();

				if (atk.WasMiss()) {
					cout << boss.GetName() << " tries " << atk.GetAttackName() << " but MISSES!\n";
				}
				else {
					if (atk.WasCrit()) cout << "\t*** " << boss.GetName() << " CRITICAL HIT! ***\n";
					cout << boss.GetName() << " uses " << atk.GetAttackName() << " and deals " << dmg << " damage!\n";
					hero.TakeDamage(dmg);

					if (atk.GetStatusEffect() != "none" && (rand() % 100) < 60) {
						cout << "\t* You are afflicted with " << atk.GetStatusEffect() << "! *\n";
						hero.ApplyStatusEffect(atk.GetStatusEffect(), atk.GetStatusDuration(), atk.GetStatusDamagePerTurn());
					}
				}
				boss.PutAttackOnCooldown(choice);
			}
		}

		playersTurn = !playersTurn;
		this_thread::sleep_for(chrono::seconds(2));
	}

	cout << "\n";
	if (hero.GetHealth() <= 0) {
		cout << hero.GetName() << " has fallen...\n";
		return false;
	}
	if (boss.GetHealth() <= 0) {
		cout << boss.GetName() << " has been defeated!\n";
		return true;
	}
	return false;
}
