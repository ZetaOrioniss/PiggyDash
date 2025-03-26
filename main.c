#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_PLAYERS 10
#define WIN_SCORE 100

typedef struct {

    char name[20];

    int score;

} Player;

int playRound(Player *player) {

    char choice;

    int roundScore = 0;

    while (1) {

        printf("\n%s, you have %d points in this round. Press 'r' to roll or 'b' to bank: ", player->name, roundScore);

        scanf(" %c", &choice);

        if (choice == 'r') {

            int dice = (rand() % 6) + 1;

            printf("%s rolled a %d!\n", player->name, dice);

            if (dice == 1) {

                printf("Oh no! You lost all points for this round.\n");
                return player->score;

            }

            roundScore += dice;

            if (player->score + roundScore >= WIN_SCORE) {

                player->score += roundScore;

                printf("\n🎉 %s wins with %d points! 🎉\n", player->name, player->score);

                exit(0);
            }


        } 
        else if (choice == 'b') {

            player->score += roundScore;

            printf("%s saved their points! Total: %d\n", player->name, player->score);

            return player->score;

        } 

        else {

            printf("Invalid choice! Try again.\n");

        }

    }

}

int main() {

    srand(time(NULL));

    int numPlayers;
    printf("Enter the number of players (max %d): ", MAX_PLAYERS);
    scanf("%d", &numPlayers);

    if (numPlayers < 2 || numPlayers > MAX_PLAYERS) {

        printf("Invalid number of players. Choose between 2 and %d.\n", MAX_PLAYERS);

        return 1;
    }

    Player players[MAX_PLAYERS];

    for (int i = 0; i < numPlayers; i++) {

        printf("Enter the name of player %d: ", i + 1);

        scanf("%19s", players[i].name);

        players[i].score = 0;
    }

    printf("\n🎲 Let the game begin! 🎲\n");

    int currentPlayer = 0;

    while (1) {

        printf("\n=== SCORE ===\n");

        for (int i = 0; i < numPlayers; i++) {

            printf("%s: %d pts\n", players[i].name, players[i].score);

        }

        sleep(1);

        players[currentPlayer].score = playRound(&players[currentPlayer]); // IA

        currentPlayer = (currentPlayer + 1) % numPlayers; // IA
    }

    return 0;
}
