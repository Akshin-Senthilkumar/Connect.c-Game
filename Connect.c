#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // for sleep function
// Global variables for the board Game.
char tokens[6][7] = {{' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' '}};

int baseLevel[7] = {5, 5, 5, 5, 5, 5, 5};
// Function to print the current situation.
void printGame() {
    for (int i = 0; i < 6; i++) {
        printf("|");
        for (int j = 0; j < 7; j++) {
            printf("%c", tokens[i][j]);
            printf("|");
        }
        printf("\n");
    }
    printf("===============");
    printf("\n");
}
// Function to modify the game board based on user input.
int modifier(int a) {
    int column;
    if (a % 2 == 0) {
        printf("Red's turn. Pick a Column (1-7):");
    } else {
        printf("Yellow's turn. Pick a Column (1-7):");
    }
    scanf("%d", &column);
    printf("\n");
    while ((column > 7) || (column < 1)) {
        printf("The Column should be between 1 and 7, please re-enter (1-7):");
        scanf("%d", &column);
        printf("\n");
    }
    column = column - 1;
    if (baseLevel[column] == -1) {
        printf("Choose another column as the chosen column is full\n");
        modifier(a);
        return 0;
    }
    if (a % 2 == 0) {
        tokens[baseLevel[column]][column] = 'R';
    } else {
        tokens[baseLevel[column]][column] = 'Y';
    }
    baseLevel[column] = baseLevel[column] - 1;
    return 0;
}

// Function to check for a vertical win
int verticalChecker(int tokenstreaks) {
    for (int i = 0; i < 7; i++) {
        int count = 0;
        char prevChar = ' ';
        for (int j = 5; j >= 0; j--) {
            if (tokens[j][i] != ' ' && tokens[j][i] == prevChar) {
                count++;
                if (count == tokenstreaks) return 1;
            } else {
                count = (tokens[j][i] != ' ') ? 1 : 0;
                prevChar = tokens[j][i];
            }
        }
    }
    return 0;
}

// Function to check for a horizontal win
int horizontalChecker(int tokenstreaks) {
    for (int j = 5; j >= 0; j--) {
        int count = 0;
        char prevChar = ' ';
        for (int i = 0; i < 7; i++) {
            if (tokens[j][i] != ' ' && tokens[j][i] == prevChar) {
                count++;
                if (count == tokenstreaks) return 1;
            } else {
                count = (tokens[j][i] != ' ') ? 1 : 0;
                prevChar = tokens[j][i];
            }
        }
    }
    return 0;
}
// Function to check diagonal.
int diagonalChecker(int tokenstreaks) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (tokens[i][j] == ' ') continue;

            int count1 = 1;
            int count2 = 1;

            for (int k = 1; k < tokenstreaks; k++) {
                if (i + k < 6 && j + k < 7 && tokens[i][j] == tokens[i + k][j + k]) {
                    count1++;
                } else {
                    break;
                }
            }

            for (int k = 1; k < tokenstreaks; k++) {
                if (i + k < 6 && j - k >= 0 && tokens[i][j] == tokens[i + k][j - k]) {
                    count2++;
                } else {
                    break;
                }
            }

            if (count1 == tokenstreaks || count2 == tokenstreaks) return 1;
        }
    }

    return 0;
}

int replay() {
    char choice;
    printf("Press 'q' to quit, 'r' to replay, or any other key to continue:\n");
    scanf(" %c", &choice);

    if (choice == 'q') {
        exit(0);
    } else if (choice == 'r') {
        return 1;
    } else {
        return 0;
    }
}
// Main Function.
int main() {
    int tokenstreaks;

    while (1) {
        printf("Welcome to Connect Four Game!\n");
        printf("Choose the number of tokens in a streak needed to win (3-5): ");
        scanf("%d", &tokenstreaks);

        while (tokenstreaks < 3 || tokenstreaks > 5) {
            printf("Invalid choice. Choose between 3, 4, or 5: ");
            scanf("%d", &tokenstreaks);
        }

        for (int i = 0; i < 43; i++) {
            modifier(i);
            printGame();
            if (verticalChecker(tokenstreaks) || horizontalChecker(tokenstreaks) || diagonalChecker(tokenstreaks)) {
                if (i % 2 == 0) {
                    printf("Red has won the game!\n");
                } else {
                    printf("Yellow has won the game!\n");
                }

                if (replay()) {
                    // Reset the game
                    for (int row = 0; row < 6; row++) {
                        for (int col = 0; col < 7; col++) {
                            tokens[row][col] = ' ';
                        }
                    }
                    for (int col = 0; col < 7; col++) {
                        baseLevel[col] = 5;
                    }
                    break;
                } else {
                    exit(0);
                }
            } else {
                printf("Continue the game!\n");
                usleep(500000); // Sleep for 0.5 seconds
            }
        }
    }

    return 0;
}
