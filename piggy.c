#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define MAX_PLAYERS 10
#define WIN_SCORE 100
#define MAX_USERNAME_LEN 20

typedef struct {

    char name[MAX_USERNAME_LEN];
    int isBot;
    int score;

} Player;

int playRound(Player *player, int roundNumber) { // function for human player round

    char choice;
    int roundScore = 0;

    printf("\n\n\e[1;94m========== ROUND %d - PLAYER %s ==========\e[0m\n\n", roundNumber, player->name);
    sleep(1);

    while (1) {

        printf("\n%s, you have \e[1;93m%d\e[0m points in this round. Press '\e[1;96mr\e[0m' to roll or '\e[1;92mb\e[0m' to bank: ", player->name, roundScore);
        scanf(" %c", &choice);

        if (choice == 'r') {

            int dice = (rand() % 6) + 1; // dice between 1 and 6

            printf("%s \e[1;92mrolled a %d!\e[0m\n", player->name, dice);
            
            if (dice == 1) { // in case of fail, the player lose his points for the current round

                printf("\e[1;91mOh no! You lost all points for this round.\e[0m\n");
                return player->score;
            }

            roundScore += dice; // while he does not roll a 1, he win the number rolled.

            if (player->score + roundScore >= WIN_SCORE) { // condition of winning

                player->score += roundScore;
                printf("\n🎉 %s \e[1;92mwins with %d points!\e[0m\n", player->name, player->score);
                exit(0);
            }
        } 
        else if (choice == 'b') {

            player->score += roundScore;
            printf("%s \e[1;94msaved their points! Total: \e[1;93m%d\e[0m\n", player->name, player->score);

            return player->score; // if the player choose to save the points, he keep them in the bank for the whole game

        } 
        else {

            printf("\e[1;91mInvalid choice! Try again.\e[0m\n");
        }
    }
}

int botPlayRound(Player *bot, int roundNumber) { // function for bot player round (same logic than the human function but with rdm)

    int roundScore = 0;

    printf("\n\n\e[1;94m========== ROUND %d - PLAYER %s==========\e[0m\n\n", roundNumber, bot->name);
    sleep(1);

    while (1) {

        printf("\nAI %s has \e[1;93m%d\e[0m points in this round.\n", bot->name, roundScore);

        char choice = (rand() % 2 == 0) ? 'r' : 'b'; // the bot has 1/2 chance to choose r or b (i have to improve this function cause it's too simple and not very smart)

        // the other part of the function is the same than playRound() but for bot

        printf("Bot chooses: %c\n", choice);
        sleep(1);

        if (choice == 'r') {

            int dice = (rand() % 6) + 1; // dice of 6.

            printf("%s \e[1;92mrolled a %d!\e[0m\n", bot->name, dice);

            if (dice == 1) {

                printf("\e[1;91mOh no! You lost all points for this round.\e[0m\n");

                return bot->score;
            }

            roundScore += dice;

            if (bot->score + roundScore >= WIN_SCORE) {

                bot->score += roundScore;
                printf("\n%s \e[1;92mwins with %d points!\e[0m\n", bot->name, bot->score);
                exit(0);
            }
        } 
        else {

            bot->score += roundScore;
            printf("%s \e[1;94msaved their points! Total: \e[1;93m%d\e[0m\n", bot->name, bot->score);
            
            return bot->score;
        }
    }
}

int main() { // main function

    srand(time(NULL));

    int numPlayers;
    int numBots;

    printf("Enter the number of human players (max %d): ", MAX_PLAYERS);
    scanf("%d", &numPlayers);

    if (numPlayers > MAX_PLAYERS) {

        printf("\e[1;91mInvalid number of players. Choose between 1 and %d.\e[0m\n", MAX_PLAYERS);
        return 1;
    }

    printf("Enter the number of bot players (max %d): ", MAX_PLAYERS);
    scanf("%d", &numBots);

    // error exception managment for invalid player number (have to be improved)

    if (numBots + numPlayers > MAX_PLAYERS) {

        printf("\e[1;91mInvalid number of players. Max total is %d.\e[0m\n", MAX_PLAYERS);
        return 1;
    }

    if (numBots + numPlayers == 0){

        printf("\e[1;91mThere is not player. Aborting...\e[0m\n");
        return 1;

    }

    if ((numPlayers == 1 && numBots == 0) || (numPlayers == 0 && numBots == 1)){

        printf("\e[1;91mA player can't play alone. Aborting...\e[0m\n");
        return 1;

    }

    // end of error mngmt 

    // now, we stock the players infos

    Player allPlayers[MAX_PLAYERS];

    for (int i = 0; i < numPlayers; i++) {

        printf("Enter the name of human player %d: ", i + 1);
        scanf("%s", allPlayers[i].name);
        printf("%zu\n", strlen(allPlayers[i].name));


        if (strlen(allPlayers[i].name) > MAX_USERNAME_LEN){ // this condition is not verified, have to fix this

            printf("\nPlease choose a username of 20 characteres max.\n\n");
            return 1;

        }

        allPlayers[i].score = 0;
        allPlayers[i].isBot = 0;
    }

    for (int i = 0; i < numBots; i++) {
        sprintf(allPlayers[numPlayers + i].name, "Bot%d", i + 1);
        allPlayers[numPlayers + i].score = 0;
        allPlayers[numPlayers + i].isBot = 1;
    }

    printf("\n🎲 \e[1;96mLet the game begin!\e[0m 🎲\n"); // game start

    int currentPlayer = 0; // for knowing which player is playing during the round
    int currentRound = 1;
    int totalPlayers = numPlayers + numBots;

    while (1) {

        printf("\e[1;93m\n=== ROUND %d - SCORE ===\e[0m\n", currentRound); // at the begin of a round, displaying the players score 

        for (int i = 0; i < totalPlayers; i++) {

            if (allPlayers[i].isBot) {

                printf("\e[1;94m%s (AI): \e[1;93m%d pts\e[0m\n", allPlayers[i].name, allPlayers[i].score);
                
            } 

            else{
                
                printf("\e[1;94m%s: \e[1;93m%d pts\e[0m\n", allPlayers[i].name, allPlayers[i].score);
            }
        }

        sleep(1);

        if (allPlayers[currentPlayer].isBot == 1) {

            allPlayers[currentPlayer].score = botPlayRound(&allPlayers[currentPlayer], currentRound); // if the current player is bot1 in the order, botPlayRound(bot1)

        } 
        else{
            allPlayers[currentPlayer].score = playRound(&allPlayers[currentPlayer], currentRound); // the same but for humans
        }

        currentPlayer = (currentPlayer + 1) % totalPlayers; // switching to the next player in the order

        if (currentPlayer == 0) {
            currentRound++;
            
        }
    }

    return 0;
}
