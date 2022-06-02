#include <iostream>
#include <algorithm>
#include <vector>
#include <Windows.h>

#define NOT_FOUND -1

class Random
{
public:
	static int random(int begin, int end)
	{
		return rand() % (end - begin) + begin;
	}

	template<class SS>
	static SS getRandom(const SS vec[], int size)
	{
		return vec[random(0, size)];
	}

	template<class SS>
	static SS getRandom(const std::vector<SS> vec)
	{
		return vec[random(0, vec.size())];
	}
};

class Player
{
public:

	Player(const std::string& selectedWord, int hp) : m_selectedWord{ selectedWord }
	{
	}

	void setFoundSym (int count)
	{
		m_FoundSymbols = normalize(count);
	}

	size_t getFoundSym() const
	{
		return m_FoundSymbols;
	}

	const std::string& SelectWord() const
	{
		return m_selectedWord;
	}

private:

	int normalize(int number)
	{
		return number > 0 ? number : 0;
	}

	int m_FoundSymbols { 0 };
	

	std::string m_selectedWord;

};

class Game
{
public:
	Game(Player& play, const std::string* dictionary) : m_play{ play }, m_dictionary{ dictionary },
		m_foundedLetters(play.SelectWord().size(), '_')
	{
	}

	void launch()
	{
		std::cout << "Слово: ";
		std::for_each(m_play.SelectWord().begin(), m_play.SelectWord().end(), [](const auto e) {std::cout << '_' << " "; });

		char letter;

		std::string foundedL(m_play.SelectWord().size(), '_');

		{

			std::cout << "\nУгадайте букву: ";
			std::cin >> letter;

			letter = std::toupper(letter);

			if (m_play.SelectWord().find(letter) != NOT_FOUND)
			{
				std::cout << "Da: ";

				for (int index{ 0 }; index < m_play.SelectWord().size(); ++index)
				{
					if (m_play.SelectWord()[index] == letter)
					{
						foundedL[index] = letter;
						m_play.setFoundSym(m_play.getFoundSym() + 1);
					}

					std::cout << foundedL[index] << " ";
				}
			}
			else
			{
				std::cout << "Net! Такой буквы нет" << std::endl;
			}
			

		}
	}

	
private:
	Player& m_play;
	const std::string* m_dictionary;

	std::string m_foundedLetters;
};

int main()
{

	setlocale(LC_ALL, "Russian");

	std::cout << "Добро пожаловать в игру \"Pole chudes\"" << std::endl;

	constexpr int WORD_COUNT{ 4 };
	std::string words[WORD_COUNT]{ "МЫШКА", "СНЕГ", "ОКНО", "ОГОНЬ"};

	Player player(Random::getRandom(words, WORD_COUNT), 5);
	Game game(player, words);

	game.launch();
	

	return 0;
}