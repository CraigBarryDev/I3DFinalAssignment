#include "utils.h"

#ifndef KEYS_H
#define KEYS_H

#define KEYS_ARR_SIZE 16
#define SPECIAL_KEYS_ARR_SIZE 2

typedef enum {
	SPECIAL_KEY_F1,
	SPECIAL_KEY_F2,
	SPECIAL_KEY_F3,
	SPECIAL_KEY_F4,
	SPECIAL_KEY_F5,
	SPECIAL_KEY_F6,
	SPECIAL_KEY_F7,
	SPECIAL_KEY_F8,
	SPECIAL_KEY_F9,
	SPECIAL_KEY_F10,
	SPECIAL_KEY_F11,
	SPECIAL_KEY_F12,
	SPECIAL_KEY_LEFT,
	SPECIAL_KEY_RIGHT,
	SPECIAL_KEY_UP,
	SPECIAL_KEY_DOWN,
	SPECIAL_KEY_INSERT,
	SPECIAL_KEY_PAGE_UP,
	SPECIAL_KEY_PAGE_DOWN,
	SPECIAL_KEY_HOME,
	SPECIAL_KEY_END
}SPECIAL_KEYS;

static unsigned short keysPressed[KEYS_ARR_SIZE];
static unsigned short keyUps[KEYS_ARR_SIZE];
static unsigned short keyDowns[KEYS_ARR_SIZE];
static unsigned short specKeysPressed[SPECIAL_KEYS_ARR_SIZE];
static unsigned short specKeyUps[SPECIAL_KEYS_ARR_SIZE];
static unsigned short specKeyDowns[SPECIAL_KEYS_ARR_SIZE];

void initKeyboard();
void resetKeyEvents();

static void setKey(unsigned short* keys, int key, bool val);
static bool getKey(unsigned short* keys, int key);

void keyDownHandler(unsigned char key, int x, int y);
void keyUpHandler(unsigned char key, int x, int y);
void specialKeysHandler(int key, int x, int y);
void specialKeyUpHandler(int key, int x, int y);

bool isKeyPressed(unsigned char key);
bool onKeyDown(unsigned char key);
bool onKeyUp(unsigned char key);

bool isSpecialKeyPressed(SPECIAL_KEYS key);
bool onSpecialKeyUp(SPECIAL_KEYS key);
bool onSpecialKeyDown(SPECIAL_KEYS key);

#endif