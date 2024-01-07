
#define _CRT_SECURE_NO_WARNINGS

#define MAX_LIVES 10
#define MIN_PATH_LENGTH 10
#define MAX_PATH_LENGTH 70
#define PATH_MULTIPLES 5

#include <stdio.h>

struct PlayerInfo
{
    int lives, treasures, moveHistory[MAX_PATH_LENGTH];
    char character;
};

struct GameInfo
{
    int maxMoves, pathLength, bombBuried[MAX_PATH_LENGTH], treasureBuried[MAX_PATH_LENGTH];
};

int main(void)
{
    int index, multiplesDisplayRange, multiplesInputInARow, finInput = 0, gameOver = 0, round = 1, nextMove = 1, map[MAX_PATH_LENGTH], printPosition; //multiplesDisplayRange is for displaying the range e.g: 1-5, 6-10, multiplesDisplayRange = 2 when range = 10; multiplesInputInARow is to take inputs in a row dependent on the PATH_MULTIPLES; printPosition is for pringing the map, and the number indicators
    struct PlayerInfo player;
    struct GameInfo game;
    printf("================================\n");
    printf("         Treasure Hunt!\n");
    printf("================================\n\n");

    printf("PLAYER Configuration\n");
    printf("--------------------\n");
    printf("Enter a single character to represent the player: ");
    scanf(" %c", &player.character);

    while (finInput == 0)
    {
        printf("Set the number of lives: ");
        scanf("%d", &player.lives);
        if (player.lives < 1 || player.lives > MAX_LIVES)
        {
            printf("     Must be between 1 and %d!\n", MAX_LIVES);
        }
        else
        {
            printf("Player configuration set-up is complete\n\n");
            finInput = 1;
        }
    }
    finInput = 0;
    player.treasures = 0;
    for (index = 0; index < MAX_PATH_LENGTH; index++)
    {
        player.moveHistory[index] = 0;
    }

    printf("GAME Configuration\n");
    printf("------------------\n");
    while (finInput == 0)
    {
        printf("Set the path length (a multiple of %d between %d-%d): ", PATH_MULTIPLES, MIN_PATH_LENGTH, MAX_PATH_LENGTH);
        scanf("%d", &game.pathLength);
        if (game.pathLength < MIN_PATH_LENGTH || game.pathLength > MAX_PATH_LENGTH || (game.pathLength % PATH_MULTIPLES) != 0)
        {
            printf("     Must be a multiple of %d and between %d-%d!!!\n", PATH_MULTIPLES, MIN_PATH_LENGTH, MAX_PATH_LENGTH);
        }
        else
        {
            finInput = 1;
        }
    }
    finInput = 0;

    while (finInput == 0)
    {
        printf("Set the limit for number of moves allowed: ");
        scanf("%d", &game.maxMoves);
        if (game.maxMoves < player.lives || game.maxMoves >(int)(game.pathLength * 0.75))
        {
            printf("    Value must be between %d and %d\n", player.lives, (int)(game.pathLength * 0.75));
        }
        else
        {
            finInput = 1;
        }
    }
    printf("\n");
    finInput = 0;

    printf("BOMB Placement\n");
    printf("--------------\n");
    printf("Enter the bomb positions in sets of %d where a value\n", PATH_MULTIPLES);
    printf("of 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n");
    printf("(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", game.pathLength);
    for (index = 0, multiplesDisplayRange = 1; index < game.pathLength; index += PATH_MULTIPLES, multiplesDisplayRange++)
    {
        printf("   Positions [%2d-%2d]: ", index + 1, multiplesDisplayRange * PATH_MULTIPLES); //multiplesDisplayRange is for displaying positions correctly corresponding to PATH_MULTIPLE
        for (multiplesInputInARow = PATH_MULTIPLES * (multiplesDisplayRange - 1); multiplesInputInARow < PATH_MULTIPLES * multiplesDisplayRange; multiplesInputInARow++)
        {
            scanf("%d", &game.bombBuried[multiplesInputInARow]);
        }
    }
    printf("BOMB placement set\n\n");

    printf("TREASURE Placement\n");
    printf("------------------\n");
    printf("Enter the treasure placements in sets of %d where a value\n", PATH_MULTIPLES);
    printf("of 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n");
    printf("(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", game.pathLength);
    for (index = 0, multiplesDisplayRange = 1; index < game.pathLength; index += PATH_MULTIPLES, multiplesDisplayRange++)
    {
        printf("   Positions [%2d-%2d]: ", index + 1, multiplesDisplayRange * PATH_MULTIPLES); //multiples is for displaying positions correctly corresponding to PATH_MULTIPLES
        for (multiplesInputInARow = PATH_MULTIPLES * (multiplesDisplayRange - 1); multiplesInputInARow < PATH_MULTIPLES * multiplesDisplayRange; multiplesInputInARow++)
        {
            scanf("%d", &game.treasureBuried[multiplesInputInARow]);
        }
    }
    printf("TREASURE placement set\n\n");

    printf("GAME configuration set-up is complete...\n\n");

    printf("------------------------------------\n");
    printf("TREASURE HUNT Configuration Settings\n");
    printf("------------------------------------\n");
    printf("Player:\n");
    printf("   Symbol     : %c\n", player.character);
    printf("   Lives      : %d\n", player.lives);
    printf("   Treasure   : [ready for gameplay]\n");
    printf("   History    : [ready for gameplay]\n\n");

    printf("Game:\n");
    printf("   Path Length: %d\n", game.pathLength);
    printf("   Bombs      : ");
    for (index = 0; index < game.pathLength; index++)
    {
        printf("%d", game.bombBuried[index]);
    }
    printf("\n");
    printf("   Treasure   : ");
    for (index = 0; index < game.pathLength; index++)
    {
        printf("%d", game.treasureBuried[index]);
    }
    printf("\n\n");

    printf("====================================\n");
    printf("~ Get ready to play TREASURE HUNT! ~\n");
    printf("====================================\n\n");

    for (index = 0; index < game.pathLength; index++)
    {
        map[index] = '-';
    }

    while (gameOver == 0)
    {
        if (nextMove >= 1 && nextMove <= game.pathLength) //Avoids reprinting map if out of range nextMove is inputted
        {
            if (round != 1)
            {

                printf("  ");
                for (index = 1; index <= nextMove; index++)
                {
                    if (index == nextMove)
                    {
                        printf("%c\n", player.character);
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
            round += 1; //Round is only used for when it's = 1 so the map doesn't print player's character to fit the format

            printf("  ");
            for (index = 0; index < game.pathLength; index++)
            {
                printf("%c", map[index]);
                
            }

            printf("\n  ");
            for (printPosition = 1; printPosition <= game.pathLength; printPosition++)
            {
                if (printPosition % 10 == 0)
                {
                    printf("%d", printPosition / 10);
                }
                else
                {
                    printf("|");
                }
            }

            printf("\n  ");
            for (printPosition = 1; printPosition <= game.pathLength; printPosition++)
            {
                if (printPosition >= 10)
                {
                    printf("%d", printPosition - (10 * (printPosition / 10)));
                }
                else
                {
                    printf("%d", printPosition);
                }
            }

            printf("\n+---------------------------------------------------+\n");
            printf("  Lives: %2d  | Treasures: %2d  |  Moves Remaining: %2d\n", player.lives, player.treasures, game.maxMoves);
            printf("+---------------------------------------------------+\n");
        }

        if (player.lives != 0 && game.maxMoves != 0)
        {
            printf("Next Move [1-%2d]: ", game.pathLength);
            scanf("%d", &nextMove);
            if (nextMove < 1 || nextMove > game.pathLength)
                printf("  Out of Range!!!\n");
            else
            {
                if (player.moveHistory[nextMove - 1] == 1)
                {
                    printf("\n===============> Dope! You've been here before!\n\n");
                    game.maxMoves += 1; //Counteracts movement subtraction if visited before
                }
                else if (game.bombBuried[nextMove - 1] == 1 && game.treasureBuried[nextMove - 1] == 1)
                {
                    printf("\n===============> [&] !!! BOOOOOM !!! [&]\n");
                    printf("===============> [&] $$$ Life Insurance Payout!!! [&]\n\n");
                    player.lives -= 1;
                    player.treasures += 1;
                    map[nextMove - 1] = '&';
                }
                else if (game.bombBuried[nextMove - 1] == 1)
                {
                    printf("\n===============> [!] !!! BOOOOOM !!! [!]\n\n");
                    player.lives -= 1;
                    map[nextMove - 1] = '!';
                }
                else if (game.treasureBuried[nextMove - 1] == 1)
                {
                    printf("\n===============> [$] $$$ Found Treasure! $$$ [$]\n\n");
                    player.treasures += 1;
                    map[nextMove - 1] = '$';
                }
                else
                {
                    printf("\n===============> [.] ...Nothing found here... [.]\n\n");
                    map[nextMove - 1] = '.';
                }

                game.maxMoves -= 1;
                player.moveHistory[nextMove - 1] = 1;
            }
            if (player.lives == 0)
            {
                printf("No more LIVES remaining!\n\n");
            }
            if (game.maxMoves == 0)
            {
                printf("No more MOVES remaining!\n\n");
            }
        }
        else
        {
            printf("\n##################\n");
            printf("#   Game over!   #\n");
            printf("##################\n\n");

            printf("You should play again and try to beat your score!\n");

            gameOver = 1;
        }
    }
    return 0;
}