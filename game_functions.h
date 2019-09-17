#ifndef GAME_FUNCTIONS_H_INCLUDED
#define GAME_FUNCTIONS_H_INCLUDED
#define DIM 4
#define UNKNOWN -1
#define BOMB -2

struct locations {
    int x;
    int y;
    bool found;
};
void display(int known_location_info[DIM][DIM], int size);

void update_known_info(char row, char col, int bomb_info[DIM][DIM],
                       int known[DIM][DIM]);

char get_user_char();

void check_found(char row, char col, struct locations bombs[],
                 int size, bool* found);

void start_game(struct locations* bombs, int bomb_location_info[DIM][DIM],
                int size, int players_info[DIM][DIM], int no_of_bombs, char clues);

#endif // GAME_FUNCTIONS_H_INCLUDED
