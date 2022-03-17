#pragma once
#include "word.h"

#define WORD_SIZE 6
#define WORD_LENGTH 5
#define ROUNDS 6

extern Word word;

class Game
{
public:
	static void run_game_loop();
};