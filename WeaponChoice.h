#pragma once
#include <chrono>
#include <thread>
#include "Game.h"

int WeaponChoice() {
    cout << "PEDESTAL 1: A Shining Sword with sparks of lightning around the blade." << endl;
    cout << "Thunder Fang: A sword that uses the power of the storm to strike enemies with lightning." << endl << endl;
    Game::NarratePause("Thunder Fang: A sword that uses the power of the storm to strike enemies with lightning.");
    cout << "PEDESTAL 2: Twin daggers that sound as if your in the heart of a storm" << endl;
    cout << "Sky Piercers: Two daggers that allow the user to strike with the speed of lightning." << endl << endl;
    Game::NarratePause("Sky Piercers: Two daggers that allow the user to strike with the speed of lightning.");
    cout << "Which weapon would you like to choose? \n 1) Thunder Fang \n 2) Sky Piercers?" << endl;
    int weapon = 0;
    cin >> weapon;
    if (weapon == 1) {
        cout << "You have chosen Thunder Fang..." << endl;
        cout << "You grab the sword and feel a powerful surge of electricity flow through your body." << endl;
        cout << "You feel as if you can command the power of the storm itself..." << endl;
        Game::NarratePause("You feel as if you can command the power of the storm itself...");
    }
    else if (weapon == 2) {
        cout << "You have chosen Sky Piercers..." << endl;
        cout << "As you pick up the daggers, you feel a surge of energy coursing through your veins." << endl;
        cout << "You feel as if you can move with the speed of lightning itself..." << endl;
    }
    return weapon;
}
