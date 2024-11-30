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

void DisplayWords(TreeMap<char, BinaryTree<string>>& letterMap, char letter)
{
	letter = tolower(letter);
	if (!letterMap.containsKey(letter)) {
		cout << "No words found for " << letter << "'." << endl;
		return;
	}
	cout << "Words with the letter '" << letter << "':" << endl;
	auto& tree = letterMap.get(letter);
	tree.printInOrder();
	cout << endl;
}

int main()
{
	TreeMap<char, BinaryTree<string>> letterMap;
	string filename;
	cout << "Enter the name of the file to process: ";
	cin >> filename;
	
	processFile(filename, letterMap);
	
	char choice;
	do
	{
		cout << "Menu:" << endl;
		cout << "1. Display list of letters" << endl;
		cout << "2. Display words of a specific letter" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter a option: ";
		cin >> choice;

		switch (choice) 
		{
		case '1':
			displayLetters(letterMap);
			break;

		case '2':
			char letter;
			cout << "Enter a letter: ";
			cin >> letter;
			DisplayWords(letterMap, letter);
			break;

		case '3':
			cout << "Goodbye!" << endl;
			break;

		default:
			cout << "Invalid option. Please try again." << endl;
		}

	}
	while (choice != '3');

	return 0;
}