#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game_functions.h"

int main(int argc, char* argv[])
{
    int no_of_bombs = 2;
    struct locations* bombs = (struct locations*)
        malloc(sizeof(struct locations)*no_of_bombs);

    char clues = argv[1][0];
    bombs[0].x = 1;
    bombs[0].y = 1;
    bombs[0].found = false;

    bombs[1].x = 2;
    bombs[1].y = 3;
    bombs[1].found = false;

    int bomb_location_info[4][4] = {1,1,1,0,
                        1,0,2,1,
                        1,1,2,0,
                        0,0,1,1};
    int known_location_info[4][4] = {UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
                                UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
                                UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
                                UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN};

    start_game(bombs,bomb_location_info,DIM,
               known_location_info,no_of_bombs, clues);

    free(bombs);
}
