#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

namespace
{
	std::vector<std::string> LoadWordList(const std::string& fileName)
	{
		std::vector<std::string> words;
		words.reserve(375'000);

		std::ifstream wordFile(fileName.c_str());

		std::string word;

		while (std::getline(wordFile, word))
		{
			words.push_back(word);
		}

		return words;
	}

	void CharacterSet(std::string& set, const std::string& str)
	{
		set = str;
		std::ranges::sort(set);
		const auto [newEnd, contEnd] = std::ranges::unique(set);
		set.erase(newEnd, contEnd);
	}
}

int main()
{
	std::string allLetters = "ajdlciu";
	char centerLetter = 'a';
	//{
	//	std::string centerLetterInput;
	//	std::string otherLetters;

	//	while (std::ssize(centerLetterInput) != 1)
	//	{
	//		std::cout << "Enter the center letter:\n";
	//		std::cin >> centerLetterInput;

	//		if (std::ssize(centerLetterInput) != 1)
	//		{
	//			std::cout << "Must be one character. Please try again.\n\n";
	//		}

	//	}

	//	while (std::ssize(otherLetters) != 6)
	//	{
	//		std::cout << "Enter the other six letters, all on one line with no spaces between letters.\n";
	//		std::cin >> otherLetters;

	//		if (std::ssize(otherLetters) != 6)
	//		{
	//			std::cout << "Must be six characters. Please try again.\n\n";
	//		}
	//	}
	//	allLetters = centerLetterInput + otherLetters;
	//	centerLetter = centerLetterInput[0];
	//}

	const auto start = std::chrono::high_resolution_clock::now();
	auto wordList = LoadWordList("words_alpha_len_4_greater.txt");
	
	std::string allSet;
	CharacterSet(allSet, allLetters);
	std::erase_if(wordList, [centerLetter](const std::string& word)
		{
			return word.find(centerLetter) == std::string::npos;
		});
	std::string wordSet;
	std::erase_if(wordList, [&allSet, &wordSet](const std::string& word)
		{
			CharacterSet(wordSet, word);
			return !std::ranges::includes(allSet, wordSet);
		});
	const auto end = std::chrono::high_resolution_clock::now();
	const auto elapse = std::chrono::duration<double>(end - start);
	std::cout << std::format("Elapsed {0}\n", elapse);

	std::cout << std::format("Number of words {0}\n", wordList.size());
}