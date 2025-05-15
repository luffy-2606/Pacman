#include "Game.h"
#include <iostream>
using namespace std;


int main() {
    try {
        while (!exitedMain && !closed) {
            Game game;
            game.run();
        }
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
    
    return 0;
} 