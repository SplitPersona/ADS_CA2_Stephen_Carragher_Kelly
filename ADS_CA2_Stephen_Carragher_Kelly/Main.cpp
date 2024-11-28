#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "TreeMap.H"
#include "BinaryTree.H"

using namespace std;

string toLower(const string& str) 
{
	string result = str;
	for (char& c : result)
	{
		c = tolower(c);
	}
	return result;
}

void processFile(const string& filename, TreeMap<char, BinaryTree<string>>& letterMap)
{
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Could not open file " << filename << endl;
		return;
	}

	string line;
	while (getline(file, line))
	{
		stringstream ss(line);
		string word;
		while (ss >> word)
		{
			size_t start = word.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
			size_t end = word.find_last_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
			if (start == string::npos || end == string::npos)
			{
				continue;
			}

			char firstLetter = word[0];
			if (!letterMap.containsKey(firstLetter)) 
			{
				letterMap.put(firstLetter, BinaryTree<string>());
			}
			auto& tree = letterMap.get(firstLetter);
			tree.add(word);

		}
	}
	file.close();
}

void displayLetters(TreeMap<char, BinaryTree<string>>& letterMap) {
	cout << "Letters with words in the file:" << endl;
	auto keysTree = letterMap.keySet();
	keysTree.printInOrder();
	cout << endl;
}

void displayWordsForLetter(TreeMap<char, BinaryTree<string>>& letterMap, char letter)
{
	letter = tolower(letter);
	if (!letterMap.containsKey(letter)) {
		cout << "No words found for the letter '" << letter << "'." << endl;
		return;
	}
	cout << "Words for the letter '" << letter << "':" << endl;
	auto& tree = letterMap.get(letter);
	tree.printInOrder();
	cout << endl;
}