#ifndef TEXT_BASED_GAME_H
#define TEXT_BASED_GAME_H

#include "Players.h"
#include <chrono>
#include <thread>

class Game {
public:
	static void FightPause(int ms);
	static void NarratePause(const string& text, int extraMs = 0);
	Game();
	Game(int fightingRounds);
	Game(vector<Player> heroesList, vector<Player> villainsList, int fightingRounds = 4);
	void PlayGame();
	void Intro();
	void RunTheFights();
	void TimeToAttack();
	void EnemyAttacks();
	void FightingScenario1();
	void EnemyInDisdainLevel1();
	void EnemyInDisdainLevel2();
	void SpaceMax();
	void SpaceMed();
	void Waiting();
	void WriteSentenceNoEndl(string sentence);
	bool StoryModeFight(Player PlayerCharacter, Player EnemyChar);
	bool BossFight(Player& hero, Player& boss, bool lightningAbsorbed);
	int ChooseEnemyAttack(Player& attacker, Player& target);
private:
	Player chosenPlayer; // character choice of player
	Player enemy;
	vector<Player> heroes; // choose from
	vector<Player> villains; // fighting against
	bool enemySpares = false;
	bool youSpare = true;
	bool enemyPleads = false;
	bool youPlead = false;
	int rounds;

};

#endif // TEXT_BASED_GAME_H
