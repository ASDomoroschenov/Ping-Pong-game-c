#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>

//-lncurses

int FixCoordinatePlayer(int coordinate_player) {
    coordinate_player = coordinate_player < 4 ? 4 : coordinate_player;
    coordinate_player = coordinate_player > 24 ? 24 : coordinate_player;

    return coordinate_player;
}

void Score(int score_1 ,int score_2) {
    printf("                                     %d--:--%d\n", score_1, score_2);
}

void SetField(int player_1, int player_2, int BALL_X, int BALL_Y, int score_1, int score_2) {
    clear();

    Score(score_1, score_2);

    if ((player_1 > 0 && player_1 < 85) && (player_2 > 0 && player_2 < 85)) {
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 85; j++) {
                if (i == BALL_Y && j == BALL_X) {
                    mvaddch(BALL_Y, BALL_X, '*');
                } else {
                    if (i == 0 || i == 24) {
                        printw("-");
                    } else {
                        if (player_1 - i > 0 && player_1 - i <= 3 && j == 2) {
                            printw("|");
                        } else {
                            if (player_2 - i > 0 && player_2 - i <= 3 && j == 82) {
                                printw("|");
                            } else {
                                if (j == 0 || j == 84) {
                                    printw("|");
                                } else {
                                    printw(" ");
                                }
                            }
                        }
                    }
                }

                refresh();
            }

            printw("\n");
        }
    }
}

void Game(int player_1, int player_2) {
    char move = '\0';

    int score_1 = 0;
    int score_2 = 0;

    bool BALL_UP = false;
    bool BALL_RIGHT = true;
    bool BALL_DOWN = false;
    bool BALL_LEFT = false;

    int BALL_X = 42;
    int BALL_Y = 13;

    noecho();
    SetField(player_1, player_2, BALL_X, BALL_Y, score_1, score_2);
    nodelay(stdscr, TRUE);

    while (score_2 != 21 || score_1 != 21) {

        move = getch();

        if (BALL_UP) {
            BALL_Y--;
        }
        if (BALL_RIGHT) {
            BALL_X++;
        }
        if (BALL_DOWN) {
            BALL_Y++;
        }
        if (BALL_LEFT) {
            BALL_X--;
        }

        if (move == 'a') {
            player_1--;
            player_1 = FixCoordinatePlayer(player_1);
            SetField(player_1, player_2, BALL_X, BALL_Y, score_1, score_2);
        } else {
            if (move == 'z') {
                player_1++;
                player_1 = FixCoordinatePlayer(player_1);
                SetField(player_1, player_2, BALL_X, BALL_Y, score_1, score_2);
            } else {
                if (move == 'k') {
                    player_2--;
                    player_2 = FixCoordinatePlayer(player_2);
                    SetField(player_1, player_2, BALL_X, BALL_Y, score_1, score_2);
                } else {
                    if (move == 'm') {
                        player_2++;
                        player_2 = FixCoordinatePlayer(player_2);
                        SetField(player_1, player_2, BALL_X, BALL_Y, score_1, score_2);
                    } else {
                        SetField(player_1, player_2, BALL_X, BALL_Y, score_1, score_2);
                    }
                }
            }
        }

        if (BALL_X == 81 && BALL_Y == player_2 - 3) {
            BALL_UP = true;
            BALL_RIGHT = false;
            BALL_DOWN = false;
            BALL_LEFT = true;
        }

        if (BALL_X == 81 && BALL_Y == player_2 - 2) {
            BALL_UP = false;
            BALL_RIGHT = false;
            BALL_DOWN = false;
            BALL_LEFT = true;
        }

        if (BALL_X == 81 && BALL_Y == player_2 - 1) {
            BALL_UP = false;
            BALL_RIGHT = false;
            BALL_DOWN = true;
            BALL_LEFT = true;
        }

        if (BALL_X == 3 && BALL_Y == player_1 - 3) {
            BALL_UP = true;
            BALL_RIGHT = true;
            BALL_DOWN = false;
            BALL_LEFT = false;
        }

        if (BALL_X == 3 && BALL_Y == player_1 - 2) {
            BALL_UP = false;
            BALL_RIGHT = true;
            BALL_DOWN = false;
            BALL_LEFT = false;
        }

        if (BALL_X == 3 && BALL_Y == player_1 - 1) {
            BALL_UP = false;
            BALL_RIGHT = true;
            BALL_DOWN = true;
            BALL_LEFT = false;
        }

        if (BALL_Y == 24 && BALL_LEFT == true) {
            BALL_UP = true;
            BALL_RIGHT = false;
            BALL_DOWN = false;
            BALL_LEFT = true;
        }

        if (BALL_Y == 1 && BALL_LEFT == true) {
            BALL_UP = false;
            BALL_RIGHT = false;
            BALL_DOWN = true;
            BALL_LEFT = true;
        }

        if (BALL_Y == 24 && BALL_RIGHT == true) {
            BALL_UP = true;
            BALL_RIGHT = true;
            BALL_DOWN = false;
            BALL_LEFT = false;
        }

        if (BALL_Y == 1 && BALL_RIGHT == true) {
            BALL_UP = false;
            BALL_RIGHT = true;
            BALL_DOWN = true;
            BALL_LEFT = false;
        }

        if (BALL_X == 2 || BALL_X == 82) {
            if (BALL_X == 2) {
                score_2++;
            } else {
                score_1++;
            }

            BALL_UP = false;
            BALL_RIGHT = score_1 > score_2 ? true : false;
            BALL_DOWN = false;
            BALL_LEFT = score_1 > score_2 ? false : true;

            BALL_X = 42;
            BALL_Y = 13;
            if (score_1 == 21 || score_2 == 21) {
                score_1 == 21 ? printf("Player 1 - Winner!") : printf("Player 2 - Winner!");
            } else {
                SetField(player_1, player_2, BALL_X, BALL_Y, score_1, score_2);
            }
        }

        usleep(60000);
    }
}

int main() {
    initscr();

    int coordinate_player_1 = 13;
    int coordinate_player_2 = 13;

    Game(coordinate_player_1, coordinate_player_2);

    endwin();

    return 0;
}
