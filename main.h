// CONSTANTS

// General
#define SPRITE_QTY 4

// "REAL" refers to the first visible pixels of the screen.
#define REAL_LEFT 8
#define REAL_TOP 16
#define REAL_WIDTH 160
#define REAL_HEIGHT 152
#define SPRITE_SIZE 8

#define MAP_SIZE 256

// So that a sprite can be placed mid-screen.
#define MIDDLE_X 84 // (REAL_WIDTH - SPRITESIZE / 2) + SPRITESIZE;
#define MIDDLE_Y 80 // (REAL_HEIGHT - SPRITESIZE / 2) + SPRITESIZE;

#define MIDDLE_X2 180 // MAP_SIZE - MIDDLE_X + REAL_LEFT
#define MIDDLE_Y2 192 // MAP_SIZE - MIDDLE_Y + REAL_TOP