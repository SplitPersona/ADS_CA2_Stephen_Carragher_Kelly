#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "TreeMap.H"
#include "BinaryTree.H"

using namespace std;

string toLower(const string& str) //conversta a string to lower case
{
	string result = str;
	for (char& c : result)
	{
		c = tolower(c);
	}
	return result;
}

void processFile(const string& filename, TreeMap<char, BinaryTree<string>>& letterMap) //takes in a ile and filles the treeap with the words by the first letter
{
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Could not open file " << filename << endl;
		return;
	}

	string line;
	while (getline(file, line)) // reads this line by line
	{
		stringstream ss(line);
		string word;
		while (ss >> word)
		{
			size_t start = word.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"); // finds the startand end of alphabet letters
			size_t end = word.find_last_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
			if (start == string::npos || end == string::npos)
			{
				continue; //skip if no letters found
			}

			char firstLetter = word[0];
			if (!letterMap.containsKey(firstLetter)) //if lettter is not in the tree it will add it to a empty one
			{
				letterMap.put(firstLetter, BinaryTree<string>());
			}
			auto& tree = letterMap.get(firstLetter);
			tree.add(word); // adds the word to the tree

		}
	}
	file.close();
}

void displayLetters(TreeMap<char, BinaryTree<string>>& letterMap) //displays the list o of letters in the tree
{
	cout << "Letters with words in the file:" << endl;
	auto keysTree = letterMap.keySet();
	keysTree.printInOrder();
	cout << endl;
}

void DisplayWords(TreeMap<char, BinaryTree<string>>& letterMap, char letter) //showsn all the words associated wiht a certain letter
{
	letter = tolower(letter);
	if (!letterMap.containsKey(letter)) {
		cout << "No words found for " << letter << "'." << endl;
		return;
	}
	cout << "Words with the letter '" << letter << "':" << endl;
	auto& tree = letterMap.get(letter);
	tree.printInOrder(); // prints them out in order
	cout << endl;
}

int main()
{
	TreeMap<char, BinaryTree<string>> letterMap; // the ap to hold the words organizedby the letter
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