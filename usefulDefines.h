#ifndef USEFUL_DEFINES_H
#define USEFUL_DEFINES_H

// min is 0 max is X
// if on min, the turn boolean value is true
#define MIN true
#define MAX false

#define EMPTY 0
#define ZERO 1
#define EX 2  

#define ROWS 3
#define COLS 3

enum menuOptions{multiPlayer, singlePlayer, exitGame};
enum aiMenuOptions{playWithX, playWith0, aiDifficulty, easy, medium, hard, impossible};

#endif