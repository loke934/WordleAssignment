#include"game.h"

Word word;

void Game::run_game_loop()
{
	//cout << word.m_word << endl; // print the random word
	for (int i = 0; i < ROUNDS; i++)
	{
		string input;
		cin >> input;
		word.make_uppercase(input);

		while (!word.is_valid_input(input))
		{
			if (word.is_exit(input))
				return;
			cout << FOREGROUND(ForegroundColor::Red, "Not a valid word, try again") << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> input;
			word.make_uppercase(input);
		}

		word.assign_green_to_indices(input);
		word.create_map_letter_occurrence();
		word.assign_yellow_to_indices(input);
		word.print_input_result(input);

		if (input == word.m_word)
		{
			cout << "Woop right word!" << endl;
			return;
		}

		word.clear_maps();
	}
	cout << "Boooo the word was " << word.m_word << "." << endl;
}