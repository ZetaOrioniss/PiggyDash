#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int firstPlayerRound(char *player1, int bank1) {
    char player_choice;
    
    int total_round = 0;

    while (1) {

        printf("You have %d pts in this round!\nPress 'r' to get more or 'b' to save.\n%s > ", total_round, player1);
        scanf(" %c", &player_choice);
        

        if (player_choice == 'r') { 

            int dice = (rand() % 6) + 1;  

            printf("You picked %d !\n\n", dice);

            if (dice == 1) {
                printf("\nOh! It's a 1... You lose all points in the bank for this round!\n");
                return bank1 - total_round;
                break;
            } 

            total_round += dice;
            bank1 += dice;

            if(bank1 == 100 || bank1 > 100){

                printf("Congrats %s ! You won with %d in your bank !\n\n", player1, bank1);
                break;
                exit(0);
    
            }

        } 
        
        else if (player_choice == 'b') {
            printf("%s decided to save the points!\n", player1);
            return bank1;  
            break;
        } 
        
        else {
            printf("Invalid choice! Try again.\n");
            continue;
        }
    }
}

int secondPlayerRound(char *player2, int bank2) {
    char player_choice;
    int total_round = 0;


    if(bank2 >= 100 || bank2 > 100){

        printf("Congrats %s ! You won with %d in your bank !\n\n", player2, bank2);
        return 0;

    }

    while (1) {
        printf("\n\nYou have %d pts for this round!\nPress 'r' to get more or 'b' to save.\n\n%s > ", total_round, player2);
        scanf(" %c", &player_choice);

        if (player_choice == 'r') { 
            int dice = (rand() % 6) + 1;  

            if (dice == 1) {
                printf("\n\nOh! It's a 1... You lose all points in the bank!\n");
                return bank2 - total_round;
                break;
            } 
            
            total_round += dice;
            bank2 += dice;

            if(bank2 == 20 || bank2 > 20){

                printf("Congrats %s ! You won with %d in your bank !\n\n", player2, bank2);
                break;
                exit(0);
    
            }


            if (dice == 1) {
                printf("\n\nOh! It's a 1... You lose all points in the bank!\n");
                return bank2 - total_round;
                break;
            } 

        } 
        
        else if (player_choice == 'b') {
            printf("\n\n%s decided to save the points!\n", player2);
            return bank2;  
            break;
        } 
        
        else {
            printf("\n\nInvalid choice! Try again.\n\n");
            continue;
        }
    }
}


int main(void) {

    srand(time(NULL));

    char player1[20];
    char player2[20];


    printf("\nWarning ! Player 1 begins !\nPseudo for player n°1: ");
    scanf("%19s", player1);

    printf("Pseudo for player n°2: ");
    scanf("%19s", player2);

    int bank1 = 0;
    int bank2 = 0;

    printf("The first player to play is: %s\n", player1);

    while(1){

        printf("=== SCORE ===\n");
        printf("%d pts - %s\n%d pts - %s\n\n", bank1, player1, bank2, player2);

        bank1 = firstPlayerRound(player1, bank1);
        bank2 = secondPlayerRound(player2, bank2);

    }

    return 0;

}
