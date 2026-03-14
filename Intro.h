#ifndef CS_FINAL_INTRO_H
#define CS_FINAL_INTRO_H
#include <iostream>
#include <chrono>
#include <thread>
#include "Game.h"
#include "WeaponChoice.h"
#include "SwordArt.h"

    int Prologue(string name) {
        Game space;
        cout << "You wake up in a dungeon with no memory of how you got there." << endl;
        cout << "And your head is bleeding..." << endl;
        cout << "When you finally come to your senses you see a giant creature with a cloak standing in front of you." << endl
        << endl << endl << endl;
        Game::NarratePause("When you finally come to your senses you see a giant creature with a cloak standing in front of you.", 500);

        cout << "                                         .""--..__" << endl;
        cout << "                     _                     []       ``-.._" << endl;
        cout << "                  .'` `'.                  ||__           `-._" << endl;
        cout << "                 /    ,-.\\                 ||_ ```---..__     `-." << endl;
        cout << "                /    /:::\\\\               /|//}          ``--._  `." << endl;
        cout << "                |    |:::||              |////}                `-. \\" << endl;
        cout << "                |    |:::||             //'///                    `.\\" << endl;
        cout << "                |    |:::||            //  ||'                      `|" << endl;
        cout << "        jgs     /    |:::|/        _,-//\\  ||" << endl;
        cout << "        hh     /`    |:::|`-,__,-'`  |/  \\ ||" << endl;
        cout << "             /`  |   |'' ||           \\   |||" << endl;
        cout << "           /`    \\   |   ||            |  /||" << endl;
        cout << "         |`       |  |   |)            \\ | ||" << endl;
        cout << "        |          \\ |   /      ,.__    \\| ||" << endl;
        cout << "        /           `         /`    `\\   | ||" << endl;
        cout << "       |                     /        \\  / ||" << endl;
        cout << "       |                     |        | /  ||" << endl;
        cout << "       /         /           |        `(   ||" << endl;
        cout << "      /          .           /          )  ||" << endl;
        cout << "     |            \\          |     ________||" << endl;
        cout << "    /             |          /     `-------.|" << endl;
        cout << "   |\\            /          |              ||" << endl;
        cout << "   \\/`-._       |           /              ||" << endl;
        cout << "    //   `.    /`           |              ||" << endl;
        cout << "   //`.    `. |             \\              ||" << endl;
        cout << "  ///\\ `-._  )/             |              ||" << endl;
        cout << " //// )   .(/               |              ||" << endl;
        cout << " ||||   ,'` )               /              //" << endl;
        cout << " ||||  /                    /             || " << endl;
        cout << " `\\\\` /`                    |             // " << endl;
        cout << "     |`                     \\            ||  " << endl;
        cout << "    /                        |           //  " << endl;
        cout << "  /`                          \\         //   " << endl;
        cout << "/`                            |        ||    " << endl;
        cout << "`-.___,-.      .-.        ___,'        (/    " << endl;
        cout << "         `---'`   `'----'`";
        Game::FightPause(1500);
        space.SpaceMax();
        cout << "You look at it and where its face should be, there is only darkness as well as a eerie feeling as you stare into it." << endl;
        cout << "Its so large that you have to look straight up to even see its head." << endl;
        Game::NarratePause("Its so large that you have to look straight up to even see its head.");
        cout << "Finally it speaks in a bellowing voice that seems to echo through the entire dungeon" << endl;
        cout << "Its voice sends chills down your spine..." << endl << endl;
        Game::NarratePause("Its voice sends chills down your spine...");
        cout << "Shadow Being: Welcome " << name << " I was wondering when you would wake up." << endl;
        Game::NarratePause("Shadow Being: Welcome I was wondering when you would wake up.");
        cout << name << ": Who... who are you? Where am I!" << endl;
        Game::NarratePause("Who... who are you? Where am I!");
        cout << "Shadow Being: Silence. You have been chosen for a great purpose." << endl;
        cout << name << ": Chosen? For what?" << endl << endl;
        Game::NarratePause("Chosen? For what?");
        cout << "You are the descendant of the ancient hero who once saved this world from destruction. Kael Thunderborn" << endl;
        cout << "And now it is your turn to save the world from the impending doom that is awaiting.\n But first you must prove yourself worthy." << endl << endl;
        Game::NarratePause("And now it is your turn to save the world from the impending doom that is awaiting. But first you must prove yourself worthy.");
        cout << "*The creature hits the ground with its staff, you fall over from the shaking of the ground but 2 pedestals rise from the ground, So bright that you would think they are the sun itself*" << endl;
        cout << "Shadow Being: On each pedestal lies a weapon from your ancestor. Choose wisely " << name << "." << endl << endl << endl;
        int weaponChosen = WeaponChoice();
        if (weaponChosen == 1) {
            cout << "Shadow Being: Ah, the Thunder Fang. A fine choice indeed." << endl << endl << endl;
            Sword();
        }
        else {
            cout << "Shadow Being: The Sky Piercers, swift and deadly. An excellent choice." << endl;
        }
        Game::NarratePause("Shadow Being: A fine choice indeed.");

        return weaponChosen;
    }




#endif //CS_FINAL_INTRO_H