#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include <map>
#include <ctime>
#include <set>

using namespace std;

#define FOREGROUND(color, text) "\x1B[" << static_cast<int>(color) << "m" << text << "\033[0m"
#define BACKGROUND(color, text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"

enum class ForegroundColor : int {
	Green = 32,
	Yellow = 33,
	BrightBlack = 90,
	Red = 31,
	Black = 30
};

enum class BackgroundColor : int {
	Green = 42,
	Yellow = 43,
	BrightBlack = 100,
};

class Word
{
	const string M_EXIT = "EXIT";

public:
	string m_word;
	set<string> m_words_set;
	map<int, BackgroundColor> m_index_color_map;
	map<char, int> m_word_map;

	Word();
	void read_words_to_set();
	void get_random_word_from_file();
	void print_instructions();
	void create_map_letter_occurrence();
	bool is_valid_input(const string& input);
	bool is_exit(const string& input);
	void make_uppercase(string& input);
	void print_input_result(string& input);
	void assign_green_to_indices(string& input);
	void assign_yellow_to_indices(string& input);
	void clear_maps();
};