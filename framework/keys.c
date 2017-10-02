#include "keys.h"

void initKeyboard() {
	//Initializes all keyboard values to 0
	for (int i = 0; i < KEYS_ARR_SIZE; i++) {
		keysPressed[i] = 0;
		keyUps[i] = 0;
		keyDowns[i] = 0;
	}

	//Reset all the special key events
	for (int i = 0; i < SPECIAL_KEYS_ARR_SIZE; i++) {
		specKeysPressed[i] = 0;
		specKeyUps[i] = 0;
		specKeyDowns[i] = 0;
	}
}

void resetKeyEvents() {
	//Resets all the key events, should be called once at the end of each frame
	for (int i = 0; i < KEYS_ARR_SIZE; i++) {
		keyUps[i] = 0;
		keyDowns[i] = 0;
	}

	//Reset all the special key events
	for (int i = 0; i < SPECIAL_KEYS_ARR_SIZE; i++) {
		specKeyUps[i] = 0;
		specKeyDowns[i] = 0;
	}
}

static void setKey(unsigned short* keys, int key, bool val) {
	//Get the index where the bit falls in the array
	const unsigned short arrIndex = key / 16;
	//Get the bitmask for setting the value
	const unsigned short mask = 1 << (key % 16);

	if (val)
		//If the value is true then set the bit
		keys[arrIndex] = keys[arrIndex] | mask;
	else
		//if the value is false then unset the bit
		keys[arrIndex] = keys[arrIndex] & ~mask;
}

static bool getKey(unsigned short* keys, int key) {
	//Get the index where the bit falls in the array
	const unsigned short arrIndex = key / 16;
	//Get the bitmask for setting the value
	const unsigned short mask = 1 << (key % 16);

	unsigned short val = keys[arrIndex] & mask;

	//Return value of bit
	return (keys[arrIndex] & mask) != 0;
}

static int getSpecialKeyVal(int key) {
	//The integer that holds the key value
	int keyVal = -1;

	//Determine which key value the given key has
	switch (key) {
	case GLUT_KEY_F1: keyVal = SPECIAL_KEY_F1; break;
	case GLUT_KEY_F2: keyVal = SPECIAL_KEY_F2; break;
	case GLUT_KEY_F3: keyVal = SPECIAL_KEY_F3; break;
	case GLUT_KEY_F4: keyVal = SPECIAL_KEY_F4; break;
	case GLUT_KEY_F5: keyVal = SPECIAL_KEY_F5; break;
	case GLUT_KEY_F6: keyVal = SPECIAL_KEY_F6; break;
	case GLUT_KEY_F7: keyVal = SPECIAL_KEY_F7; break;
	case GLUT_KEY_F8: keyVal = SPECIAL_KEY_F8; break;
	case GLUT_KEY_F9: keyVal = SPECIAL_KEY_F9; break;
	case GLUT_KEY_F10: keyVal = SPECIAL_KEY_F10; break;
	case GLUT_KEY_F11: keyVal = SPECIAL_KEY_F11; break;
	case GLUT_KEY_F12: keyVal = SPECIAL_KEY_F12; break;
	case GLUT_KEY_LEFT: keyVal = SPECIAL_KEY_LEFT; break;
	case GLUT_KEY_RIGHT: keyVal = SPECIAL_KEY_RIGHT; break;
	case GLUT_KEY_DOWN: keyVal = SPECIAL_KEY_DOWN; break;
	case GLUT_KEY_UP: keyVal = SPECIAL_KEY_UP; break;
	case GLUT_KEY_PAGE_UP: keyVal = SPECIAL_KEY_PAGE_UP; break;
	case GLUT_KEY_PAGE_DOWN: keyVal = SPECIAL_KEY_PAGE_DOWN; break;
	case GLUT_KEY_HOME: keyVal = SPECIAL_KEY_HOME; break;
	case GLUT_KEY_END: keyVal = SPECIAL_KEY_END; break;
	case GLUT_KEY_INSERT: keyVal = SPECIAL_KEY_INSERT; break;
	}
	//Return the key value
	return keyVal;
}

void keyDownHandler(unsigned char key, int x, int y) {
	//Update pressed key to true in keys array
	setKey(keysPressed, (int)key, true);
	//Update key down event
	setKey(keyDowns, (int)key, true);

	//If the key is a lowercase key, also set the uppercase version
	if ((int)key >= 'a' && (int)key <= 'z') {
		//Update pressed key to true in keys array
		setKey(keysPressed, (int)key - 32, true);
		//Update key down event
		setKey(keyDowns, (int)key - 32, true);
	}
	//If the key is uppercase, also set the lowercase version
	else if ((int)key >= 'A' && (int)key <= 'Z') {
		//Update pressed key to true in keys array
		setKey(keysPressed, (int)key + 32, true);
		//Update key down event
		setKey(keyDowns, (int)key + 32, true);
	}
}

void keyUpHandler(unsigned char key, int x, int y) {
	//Update pressed key to true in keys array
	setKey(keysPressed, (int)key, false);
	//Update key down event
	setKey(keyUps, (int)key, true);

	//If the key is a lowercase key, also set the uppercase version
	if ((int)key >= 'a' && (int)key <= 'z') {
		//Update pressed key to true in keys array
		setKey(keysPressed, (int)key - 32, false);
		//Update key down event
		setKey(keyUps, (int)key - 32, true);
	}
	//If the key is uppercase, also set the lowercase version
	else if ((int)key >= 'A' && (int)key <= 'Z') {
		//Update pressed key to true in keys array
		setKey(keysPressed, (int)key + 32, false);
		//Update key down event
		setKey(keyUps, (int)key + 32, true);
	}
}

void specialKeysHandler(int key, int x, int y) {
	//Get the special key value
	int keyVal = getSpecialKeyVal(key);

	//Update pressed key to true in keys array
	setKey(specKeysPressed, keyVal, true);
	//Update key down event
	setKey(specKeyDowns, keyVal, true);
}

void specialKeyUpHandler(int key, int x, int y) {
	//Get the special key value
	int keyVal = getSpecialKeyVal(key);

	//Update pressed key to true in keys array
	setKey(specKeysPressed, keyVal, false);
	//Update key down event
	setKey(specKeyUps, keyVal, true);
}

bool isKeyPressed(unsigned char key) {
	return getKey(keysPressed, key);
}

bool onKeyDown(unsigned char key) {
	return getKey(keyDowns, key);
}

bool onKeyUp(unsigned char key) {
	return getKey(keyUps, key);
}

bool isSpecialKeyPressed(SPECIAL_KEYS key) {
	return getKey(specKeysPressed, key);
}

bool onSpecialKeyUp(SPECIAL_KEYS key) {
	return getKey(specKeyUps, key);
}

bool onSpecialKeyDown(SPECIAL_KEYS key) {
	return getKey(specKeyDowns, key);
}