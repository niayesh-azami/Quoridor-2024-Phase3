#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int Mx = 1e4 + 10;

struct game gameState;
int wallForEachCell[100][100][5];
enum opponentType {human = 0, computer} opponent;

#include "raylib.h"
#include "structures.c"
#include "starting.c"
#include "validwall.c"
#include "HumanAndComputer.c"
#include "graphicHuman.c"
#include "graphicComputer.c"
#include "chooseOpponent.c"

int main() {

    opponent = getOpponentType();

    switch (opponent) {
        case human:
            graphicHuman();
            break;
        case computer:
            graphicComputer();
            break;
    }

    return 0;
}

