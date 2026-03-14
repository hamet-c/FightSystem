#pragma once
#include "Game.h"
int attempts = 0;
bool TrialTwo() {
    Game space;
    vector<string> MazeDirections = { "right", "left", "left", "right", "right", "left", "right", "right", "left", "left" };
    string playerDirection;
    cout << "Trial Two...." << endl;
    cout << "Welcome to the second trial. In this trial you must navigate through a maze." << endl;
    cout << "Only by reaching the end of the maze may you proceed to trial three." << endl;
    cout << "Be careful though, if you make a wrong turn you will be sent back to the start." << endl;
    Game::NarratePause("Be careful though, if you make a wrong turn you will be sent back to the start.");
    cout << "*You find yourself at the entrance of a dark maze. You can barely see anything*" << endl;
    Game::NarratePause("You find yourself at the entrance of a dark maze. You can barely see anything");
    cout << "To navigate the maze, type 'left' or 'right' to choose your direction at each turn." << endl;
    Game::NarratePause("To navigate the maze, type left or right to choose your direction at each turn.");
    for (int i = 0; i < MazeDirections.size(); ) {
        cout << "Which direction do you choose? (left/right): ";
        cin >> playerDirection;
        playerDirection.at(0) = tolower(playerDirection.at(0));
        if (playerDirection == MazeDirections.at(i)) {
            cout << "You move " << playerDirection << " and continue deeper into the maze." << endl;
            i++;
        }
        else {
            attempts++;
            space.SpaceMax();
            cout << "Wrong turn! You blink and find yourself back at the entrance of the maze." << endl;
            i = 0;
        }
        Game::FightPause(700);
    }
    if (attempts > 20) {
        return false;
    }
    return true;
}