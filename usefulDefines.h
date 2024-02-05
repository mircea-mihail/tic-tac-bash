#ifndef USEFUL_DEFINES_H
#define USEFUL_DEFINES_H
// generally useful defines that are needed throughout the project

// min is 0 max is X
// if on min, the turn boolean value is true
#define MIN true
#define MAX false

#define EMPTY 0
#define ZERO 1
#define EX 2  

#define ROWS 3
#define COLS 3

#define X_TURN 0
#define Z_TURN 1 // zero = true

enum menuOptions{multiPlayer, singlePlayer, exitGame};
enum aiMenuOptions{playWithX, playWith0, aiDifficulty, easy, medium, hard, impossible};

#endif