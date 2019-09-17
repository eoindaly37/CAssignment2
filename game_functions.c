//Eoin Daly R00161654
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "game_functions.h"

void display(int known_location_info[DIM][DIM], int size){
    int row = 0;
    int col = 0;
    int labels[] = {'A', 'B', 'C', 'D'};
    for(int i = 0; i<size; i++){
        printf("   %c ", labels[i]);
    }
    printf("\n");
    for(row=0; row<size; row++){
        printf("%c", labels[row]);
        for(col = 0; col<size; col++){
            if(known_location_info[row][col]==-1){
                printf("  *  ");
            }
            else if(known_location_info[row][col]==BOMB){
                printf("  B  ");
            }
            else {
                printf("  %d  ", known_location_info[row][col]);
            }
        }
        printf("\n");
    }
}

int get_random(int max){
    int r = rand() % max;
    return r;
}

char get_user_char() {
    //1. We create the output variable with the value the user has input by keyboard
    char res = 'e';
    bool ischar = false;
    while(ischar==false){
        res = getchar();
        if(res>='A'&&res<='D'){
            ischar = true;
        }
        else if(res=='\n'){
            //do nothing
        }
        else {
            printf("\nMust be from A-D\n");
        }
    }
    //2. We discard any extra character the user has input by keyboard
    bool finish = false;
    char dummy_char = ' ';

    while (finish == false) {
        dummy_char = getchar();
        if (dummy_char == '\n')
            finish = true;
    }

    //3. We return the output variable
    return res;
}

void update_known_info(char row, char col, int bomb_info[DIM][DIM],
                       int known[DIM][DIM]){
    int rowno = row - 'A';
    int colno = col - 'A';

    known[rowno][colno] = bomb_info[rowno][colno];


}
void check_found(char row, char col, struct locations bombs[],
                 int size, bool* found){
    int rowno = row - 'A';
    int colno = col - 'A';

    int i = 0;
    for(i = 0; i<size; i++){
       if((bombs[i].x==rowno)&&(bombs[i].y==colno)&&(bombs[i].found==false)){
            *found = true;
            bombs[i].found = true;
        }
    }
}

void start_game(struct locations* bombs, int bomb_location_info[DIM][DIM],
                int size, int known_location_info[DIM][DIM], int no_of_bombs, char clues){
    enum game_status {STILL_ALIVE, GAME_OVER};
    enum game_status status = STILL_ALIVE;

    //printf("Clues or no clues? [c/n]");
    //char clues = get_user_char();
    int cluesleft = 5;
    if(clues=='c'){
        printf("\nCLUES\n");
        cluesleft = 3;
        int r1 = get_random(DIM);
        int r2 = get_random(DIM);
        int r3 = get_random(DIM);
        int r4 = get_random(DIM);
        known_location_info[r1][r2] = bomb_location_info[r1][r2];
        known_location_info[r2][r3] = bomb_location_info[r2][r3];
    }
    if(clues=='n'){
        printf("\nNO CLUES\n");
        cluesleft = 5;
    }

    bool found = false;
    display(known_location_info, DIM);

    int i = 0;
    while(i<cluesleft&&found==false){
        printf("\nWhat letter row?");
        char row = get_user_char();
        printf("\nWhat letter column?");
        char col = get_user_char();
        update_known_info(row,col,bomb_location_info,known_location_info);
        display(known_location_info,DIM);
        check_found(row,col,bombs,no_of_bombs,&found);
        i++;
    }
    if(found==true){
        status = GAME_OVER;
        printf("GAME OVER");
    }
    else{
        printf("\nNOW GUESS BOMB LOCATIONS\n");
        int number_found = 0;
        while((status==STILL_ALIVE)&&(number_found<no_of_bombs)){
            printf("\nWhat letter row?");
            char row = get_user_char();
            printf("\nWhat letter column?");
            char col = get_user_char();
            int rowno = row - 'A';
            int colno = col - 'A';
            check_found(row,col,bombs,no_of_bombs,&found);
            if(found==true){
                known_location_info[rowno][colno] = BOMB;
                display(known_location_info,DIM);
                number_found++;
            }
            else{
                status = GAME_OVER;
                printf("\nGAME OVER-BOMB MISSED\n");
                display(known_location_info,DIM);
            }
        }
        if(status==STILL_ALIVE){
            printf("\nALL BOMBS FOUND-YOU WIN");
        }

    }
}
