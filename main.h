// CONSTANTS / GLOBALS
extern UINT8 GameLoopState; // Bitmask for lives, pause and score bits.
extern UINT8 GameState; // Bitmask for pause menu selection, START HOLD bit, game context
extern UINT8 clock; // Used for events involving timing.
extern int xVel; // Player's x velocity
extern int yVel; // Player's y velocity
extern int xVels[25]; // x velocity for other moving entities/sprites
extern int yVels[25]; // y velocity for other moving entities/sprites

#define ENTITY_QTY 5

// "REAL" refers to the first visible pixels of the screen.
#define REAL_LEFT 8
#define REAL_TOP 16
#define REAL_WIDTH 160
#define REAL_HEIGHT 152
#define SPRITE_SIZE 8

#define MAP_SIZE 256
#define MAP_CENTER_X 132 // (MAP_SIZE / 2) + (REAL_LEFT - (SPRITESIZE / 2))
#define MAP_CENTER_Y 140 // (MAP_SIZE / 2) + 12 (REAL_TOP - (SPRITESIZE / 2))
#define SCROLL_OFFSET_X 48 // MAP_CENTER_X - MIDDLE_X
#define SCROLL_OFFSET_Y 60 // MAP_CENTER_Y - MIDDLE_Y

// So that a sprite can be placed mid-screen.
#define MIDDLE_X 84 // (REAL_WIDTH - SPRITESIZE / 2) + SPRITESIZE;
#define MIDDLE_Y 80 // (REAL_HEIGHT - SPRITESIZE / 2) + SPRITESIZE;

#define MIDDLE_X2 180 // MAP_SIZE - MIDDLE_X + REAL_LEFT
#define MIDDLE_Y2 192 // MAP_SIZE - MIDDLE_Y