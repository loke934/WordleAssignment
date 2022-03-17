#include "word.h"
#include "game.h"

Word::Word()
{
	read_words_to_set();
	get_random_word_from_file();
}

void Word::read_words_to_set()
{
	string line;
	ifstream file("words.txt"); //must be in same folder as exe
	if (!file.is_open())
	{
		cout << FOREGROUND(ForegroundColor::Red, "Unable to open words.txt") << endl;
		exit(1);
	}
	while (getline(file, line ))
	{
		m_words_set.insert(line);
	}
	file.close();
}

void Word::get_random_word_from_file()
{
	srand(time(nullptr));
	const int random_number = rand() % m_words_set.size() + 0;
	m_word = *next(m_words_set.begin(), random_number);
}

void Word::print_instructions()
{
	cout << "WELCOME TO CONSOLE WORDLE" << endl;
	cout << endl;
	cout << "Guess wordle in six tries. Hit enter button to submit." << endl;
	cout << "After each guess, the output color will change to show how close your guess was to the word." << endl;
	cout << "Input 'exit' to close game." << endl;
	cout << endl;
	cout << BACKGROUND(BackgroundColor::Green, FOREGROUND(ForegroundColor::Black, "Green")) << " = the letter is the word is in the correct spot." << endl;
	cout << BACKGROUND(BackgroundColor::Yellow, FOREGROUND(ForegroundColor::Black, "Yellow")) << " = the letter is in the word but in the wrong spot." << endl;
	cout << BACKGROUND(BackgroundColor::BrightBlack, FOREGROUND(ForegroundColor::Black, "Grey")) << "  = the letter is not in the word in any spot." << endl;
	cout << endl;
	cout << endl;
	cout << "Guess the five letter word: " << endl;
	cout << endl;
}

void Word::create_map_letter_occurrence()
{
	for (int i = 0; i < size(m_word); i++)
	{
		if (m_word_map.count(m_word[i]) > 0)
			m_word_map[m_word[i]] += 1;
		else
			m_word_map[m_word[i]] = 1;

		if (m_index_color_map.count(i) > 0)
			m_word_map[m_word[i]] -= 1;
	}
}

bool Word::is_valid_input(const string& input)
{
	for (int i = 0; i < size(input); i++)
	{
		if (!(input[i] >= 'A' && input[i] <= 'Z') || size(input) != WORD_LENGTH)
			return false;
		if (m_words_set.find(input) == m_words_set.end())
			return false;
	}
	return true;
}

bool Word::is_exit(const string& input)
{
	for (int i = 0; i < size(input); i++)
	{
		if (input[i] != M_EXIT[i])
			return false;
	}
	cout << "Exiting game..." << endl;
	return true;
}

void Word::make_uppercase(string& input)
{
	for (char& ch : input)
		ch = toupper(ch);
}

void Word::print_input_result(string& input)
{
	cout << " " << endl;
	for (int i = 0; i < size(input); i++)
	{
		if (m_index_color_map.count(i) > 0)
			cout << BACKGROUND(m_index_color_map[i], FOREGROUND(ForegroundColor::Black, input[i])) << " ";
		else
			cout << BACKGROUND(BackgroundColor::BrightBlack, FOREGROUND(ForegroundColor::Black, input[i])) << " ";
	}
	cout << endl;
	cout << " " << endl;
}

void Word::assign_green_to_indices(string& input)
{
	for (int i = 0; i < size(input); i++)
	{
		if (input[i] == m_word[i])
			m_index_color_map[i] = BackgroundColor::Green;
	}
}

void Word::assign_yellow_to_indices(string& input)
{
	for (int i = 0; i < size(input); i++)
	{
		if (m_index_color_map.count(i) > 0)
			continue;
		
		if (m_word_map.count(input[i]) > 0)
		{
			if (m_word_map[input[i]] > 0)
			{
				m_word_map[input[i]] -= 1;
				m_index_color_map[i] = BackgroundColor::Yellow;
			}
		}
	}
}

void Word:: clear_maps()
{
	m_index_color_map.clear();
	m_word_map.clear();
}
