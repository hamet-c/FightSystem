#include "SwordArt.h"
#include <iostream>
#include "Attack.h"
#include "Player.h"
#include "Game.h"
#include "Players.h"
#include "Intro.h"
#include "TrialOne.h"
#include "TrialTwo.h"
#include "TrialThree.h"
#include "FinalBoss.h"
#include <ctime>
#include <cstdlib>
using namespace std;

int WorthinessScore = 0;
int main() {
    srand(time(0));
    Game space;
    cout << "Hello Player this game is a turned based fighting game where you choose a hero and fight against villains." << endl;
    cout << "You can also play the story mode if you want more than just the fighting aspect." << endl;
    cout << endl;
    cout << endl;
    cout << "Which would you like to do \n\n 1. Fighting Mode \n 2. Story Mode" << endl;
    cout << endl;
    cout << "Enter choice number: ";

    int modeChoice;
    cin >> modeChoice;
    if (modeChoice == 1) {
        bool playAgain = true;
        Game fightingGame = Game();

        fightingGame.SpaceMax();
        cout << "You have chosen Fighting Mode" << endl;
        fightingGame.SpaceMed();

        this_thread::sleep_for(chrono::seconds(2));

        while (playAgain) {
            fightingGame.SpaceMed();
            fightingGame.PlayGame();
            cout << "Would you like to play again? (1 for yes, 2 for no)" << endl;
            int Replay;
            cin >> Replay;
            if (Replay == 1) {
                playAgain = true;
            }
            else {
                playAgain = false;
            }
        }
        return 0;
    }
    else if (modeChoice == 2) {
        cout << "You have chosen the Story Mode" << endl;
        cout << "Before you start your adventure what would you like to be called? " << endl;
        string playerName;
        cin >> playerName;

        int Choice;
        Choice = Prologue(playerName);
        Player customPlayer = Player(playerName, 100, 2, 0, 0);
        if (Choice == 1) {
            // Thunder Fang (Sword) path
            Attacks customAttacks;
            Attack runAway = Attack();
            customAttacks.AssignAttack(runAway);

            Attack punch("Punch", 5, "A quick punch", 3);
            punch.SetMinDamage(4); punch.SetMaxDamage(6);
            customAttacks.AssignAttack(punch);

            Attack sparkSlash("Spark Slash", 12, "A lightning-charged sword slash that sears the enemy", 4);
            sparkSlash.SetMinDamage(10); sparkSlash.SetMaxDamage(15);
            sparkSlash.SetIsLightning(true);
            sparkSlash.SetStatusEffect("bleed"); sparkSlash.SetStatusDuration(2); sparkSlash.SetStatusDamagePerTurn(3);
            customAttacks.AssignAttack(sparkSlash);

            Attack chainLightning("Chain Lightning", 18, "A bolt of lightning that arcs between foes, chance to stun", 5);
            chainLightning.SetMinDamage(15); chainLightning.SetMaxDamage(22);
            chainLightning.SetIsLightning(true);
            chainLightning.SetCooldownTurns(1);
            chainLightning.SetStatusEffect("stun"); chainLightning.SetStatusDuration(1);
            customAttacks.AssignAttack(chainLightning);

            Attack thunderNova("Thunder Nova", 25, "A massive burst of storm energy radiates from the blade", 6);
            thunderNova.SetMinDamage(22); thunderNova.SetMaxDamage(30);
            thunderNova.SetIsLightning(true);
            thunderNova.SetCooldownTurns(2);
            thunderNova.SetCritChance(0.20f);
            customAttacks.AssignAttack(thunderNova);

            customPlayer.AssignPlayerAttacks(customAttacks);

            cout << endl << "NEW MOVES" << endl;
            cout << "\t  1) Default Attack" << endl;
            cout << "\t  - Damage: " << customPlayer.GetAttackDamage() << endl;
            customPlayer.ShowAttacksInfo();
        }
        else if (Choice == 2) {
            // Sky Piercers (Daggers) path
            Attacks customAttacks;
            Attack runAway = Attack();
            customAttacks.AssignAttack(runAway);

            Attack punch("Punch", 5, "A quick jab", 3);
            punch.SetMinDamage(4); punch.SetMaxDamage(6);
            customAttacks.AssignAttack(punch);

            Attack piercingStab("Piercing Stab", 10, "A rapid dual-dagger thrust", 4);
            piercingStab.SetMinDamage(8); piercingStab.SetMaxDamage(13);
            piercingStab.SetCritChance(0.20f);
            customAttacks.AssignAttack(piercingStab);

            Attack lightningOverdriver("Lightning Overdriver", 15, "Channel lightning through the daggers into the ground, shocking the enemy", 5);
            lightningOverdriver.SetMinDamage(12); lightningOverdriver.SetMaxDamage(20);
            lightningOverdriver.SetIsLightning(true);
            lightningOverdriver.SetCooldownTurns(1);
            lightningOverdriver.SetStatusEffect("stun"); lightningOverdriver.SetStatusDuration(1);
            customAttacks.AssignAttack(lightningOverdriver);

            Attack shadowStep("Shadow Step", 22, "Vanish and strike from behind with electrified blades", 6);
            shadowStep.SetMinDamage(18); shadowStep.SetMaxDamage(26);
            shadowStep.SetIsLightning(true);
            shadowStep.SetCooldownTurns(2);
            shadowStep.SetCritChance(0.25f);
            shadowStep.SetStatusEffect("bleed"); shadowStep.SetStatusDuration(2); shadowStep.SetStatusDamagePerTurn(4);
            customAttacks.AssignAttack(shadowStep);

            customPlayer.AssignPlayerAttacks(customAttacks);

            cout << endl << "NEW MOVES" << endl;
            cout << "\t  1) Default Attack" << endl;
            cout << "\t  - Damage: " << customPlayer.GetAttackDamage() << endl;
            customPlayer.ShowAttacksInfo();
        }
    cout << "Shadow Being: In order to prove your worthiness you must go through 3 trials that will test your skills" << endl;
    this_thread::sleep_for(chrono::seconds(2));
        cout << "To begin walk through that door" << endl;
        cout << "*The being bangs his staff on the ground again and a door materializes in front of you*" << endl;
        this_thread::sleep_for(chrono::seconds(4));
        space.SpaceMax();
        cout << "Trial One...." << endl;
        bool check1 = TrialOne();
        if (check1) {
            WorthinessScore += 30;
        }
        bool check = TrialTwo();
        if (check) {
            WorthinessScore += 30;
        }
        cout << "Welcome to the third and final trial. In this trial you will face... yourself." << endl;
        Game T3;
        bool trial3result = TrialThree(T3, customPlayer);
        if  (trial3result) {
            cout << "Well done hero, you have succeeded in defeating your shadow self." << endl;
            cout << "Return to the Shadow Being to see if you're worthy." << endl;
            WorthinessScore += 40;
        }
        else {
            cout << "You have failed to beat your shadow self." << endl;
            cout << "Return to the Shadow Being to see if you're worthy." << endl;
        }

        cout << "Shadow Being: You have completed the trials." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        if (WorthinessScore < 70) {
            cout << "Shadow Being: You are not a worthy successor of the Thunderborn name " << endl;
            cout << "Shadow Being: Begone from my sight." << endl;
            cout << "*The being raises his staff and a the floor opens up below of you, you fall for what seems to be an eternity*" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "You wake up in a forest with no memory of how you got there..." << endl;
            cout << "GAME OVER" << endl;
        }
        else {
            FinalBossSequence(T3, customPlayer, Choice);
        }
    }



    return 0;
};
