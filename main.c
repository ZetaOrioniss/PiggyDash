#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_PLAYERS 10
#define WIN_SCORE 100

typedef struct {

    char name[20];
    char bot[5];
    int score;

} Player;

int playRound(Player *player, int roundNumber) {
    char choice;
    int roundScore = 0;
    
    printf("\n\n\e[1;94m========== ROUND %d - PLAYER %s ==========\e[0m\n\n", roundNumber, player->name);
    sleep(1);
    
    while (1) {
        printf("\n%s, you have \e[1;93m%d\e[0m points in this round. Press '\e[1;96mr\e[0m' to roll or '\e[1;92mb\e[0m' to bank: ", player->name, roundScore);
        scanf(" %c", &choice);
        
        if (choice == 'r') {
            int dice = (rand() % 6) + 1;
            printf("%s \e[1;92mrolled a %d!\e[0m\n", player->name, dice);
            
            if (dice == 1) {
                printf("\e[1;91mOh no! You lost all points for this round.\e[0m\n");
                return player->score;
            }
            
            roundScore += dice;
            
            if (player->score + roundScore >= WIN_SCORE) {
                player->score += roundScore;
                printf("\n🎉 %s \e[1;92mwins with %d points!\e[0m 🎉\n", player->name, player->score);
                exit(0);
            }
        } 
        else if (choice == 'b') {

            player->score += roundScore;
            printf("%s \e[1;94msaved their points! Total: \e[1;93m%d\e[0m\n", player->name, player->score);
            return player->score;
        } 
        else {
            printf("\e[1;91mInvalid choice! Try again.\e[0m\n");
        }
    }
}

int botPlayRound(Player *bots, int roundNumber) {
    char choice;
    int roundScore = 0;
    
    printf("\n\n\e[1;94m========== ROUND %d - PLAYER %s ==========\e[0m\n\n", roundNumber, bots->name);
    sleep(1);
    
    while (1) {

        printf("\nAI %s has \e[1;93m%d\e[0m points in this round.", bots->name, roundScore);

        choice = (rand() % 4 == 0) ? 'r' : 'b';
        printf("\nBot chooses: %c\n", choice);

        sleep(1);
        
        if (choice == 'r') {
            int dice = (rand() % 6) + 1;
            printf("%s \e[1;92mrolled a %d!\e[0m\n", bots->name, dice);
            
            if (dice == 1) {
                printf("\e[1;91mOh no! You lost all points for this round.\e[0m\n");
                return bots->score;
            }
            
            roundScore += dice;
            
            if (bots->score + roundScore >= WIN_SCORE) {
                bots->score += roundScore;
                printf("\n🎉 %s \e[1;92mwins with %d points!\e[0m 🎉\n", bots->name, bots->score);
                exit(0);
            }
        } 
        else if (choice == 'b') {
            
            bots->score += roundScore;
            printf("%s \e[1;94msaved their points! Total: \e[1;93m%d\e[0m\n", bots->name, bots->score);
            return bots->score;
        } 
        else {
            printf("\e[1;91mInvalid choice! Try again.\e[0m\n");
        }
    }
}

int main() {

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

    if (numBots > MAX_PLAYERS) {

        printf("\e[1;91mInvalid number of players. Choose between 1 and %d.\e[0m\n", MAX_PLAYERS);
        return 1;

    }
    
    
    Player players[MAX_PLAYERS];

    Player bots[MAX_PLAYERS];
    
    for (int i = 0; i < numPlayers; i++) {
        printf("Enter the name of player %d: ", i + 1);
        scanf("%19s", players[i].name);
        players[i].score = 0;
    }

    for (int i = 0; i < numBots; i++) {
        printf("Enter the name of bot player %d: ", i + 1);
        scanf("%19s", bots[i].name);
        bots[i].score = 0;
    }

    printf(" ..                .            ...               .    \n");
    printf("         @---=.                         .+--:@         \n");
    printf("      +.+--+###+@  .@+++--:..:-=+*@.  @+##@+--#:=.     \n");
    printf("     +--@-+#@***@++=----------------++@***@*+-@--=     \n");
    printf("    .---@++#@*@++++++++++++++++++==+++++@*@#++%---.    \n");
    printf("    @--++++#@@++++++++++*@#####++++++++=+@@#++++--@    \n");
    printf("    @-++++#@@+++@@@++=++#@#####+++++@@@+++@@#+*++-# .  \n");
    printf("  .@=+=+##@@+++%#@-=++++++###++++++:-#*#+++@@##+++=%.  \n");
    printf("  @+=+##% .#++##%#@@-+@++++#++++@+-%%#%##++#. @##+++@  \n");
    printf(" .%#%@.   @#*++####@@@++++@#@++++@@@##@#+++##   .@@##. \n");
    printf("         @####+#+*#####@@@@@@@@@######++++###.         \n");
    printf("        .##++++%#*##%+-#=--.-----+@###*@+#####.        \n");
    printf("        #+-----+++++++@---------++++++++----###        \n");
    printf("       .+.---+#%@++++@-*#%---%#@-*++++@%%+--.+#.       \n");
    printf("       .+----##@  %###=+#%---%#+++##@  @##---+#@       \n");
    printf("      ..+----+#@  @ %@+++----++++@@ ..@-#*---+#@ .. .  \n");
    printf("   ..  .+----++#. : :#@@+++++++@@@..  .#+----+#    ..  \n");
    printf(" ...    @+----+++##*#######+###*#+####+++++++#@   ..   \n");
    printf("         @#++++++++####+=-.:-=+*####++++++++#@         \n");
    printf("           ##+++++###+++------+++##++++++++#.          \n");
    printf("             @#######++++++++++++########@.            \n");
    printf("               .@######++++++++#######@@               \n");
    printf("                    @@@#########@@@.                   \n");

    
    printf("\n🎲 \e[1;96mLet the game begin!\e[0m 🎲\n");
    
    int currentPlayer = 0;
    int currentRound = 1;

    int totalPlayers = numPlayers + numBots;
    
    while (1) {

        printf("\e[1;93m\n=== ROUND %d - SCORE ===\e[0m\n", currentRound);
        
        for (int i = 0; i < numPlayers; i++) {

            printf("\e[1;94m%s: \e[1;93m%d pts\e[0m\n", players[i].name, players[i].score);

        }
        for (int i = 0; i < numBots; i++) {

            printf("\e[1;94m%s \e[1;93mAI: %d pts\e[0m\n", bots[i].name, bots[i].score);

        }
        
        sleep(1);

        if (numPlayers >= 1){

            players[currentPlayer].score = playRound(&players[currentPlayer], currentRound);

        }

        if (numBots >= 1){

            bots[currentPlayer].score = botPlayRound(&bots[currentPlayer], currentRound);

        }

        currentPlayer = (currentPlayer + 1) % totalPlayers;

        if (currentPlayer == 0) {

            currentRound++;

        }
        
    }
    
    return 0;
}
