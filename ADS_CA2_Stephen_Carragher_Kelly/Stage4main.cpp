#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "TreeMap.H"

using namespace std;

struct Book 
{
	string name;
	string author;
	string releaseDate;
	float highestReview;
	float lowestReview;

	bool operator<(const Book& other) const
	{
		return name < other.name;
	}

	bool operator==(const Book& other) const
	{
		return name == other.name;
	}
};

TreeMap<string, Book> loadBooks(const string& filename)
{
	TreeMap<string, Book> bookMap;
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Could not open file " << filename << endl;
		return bookMap;
	}

	string line;
	getline(file, line);

	while (getline(file, line))
	{
		stringstream ss(line);
		Book book;
		string highestReviewStr, lowestReviewStr;

		getline(ss, book.name, ',');
		getline(ss, book.author, ',');
		getline(ss, book.releaseDate, ',');
		getline(ss, highestReviewStr, ',');
		getline(ss, lowestReviewStr, ',');
		
		book.highestReview = stof(highestReviewStr);
		book.lowestReview = stof(lowestReviewStr);

		bookMap.put(book.name, book);
		
	}

	file.close();
	return bookMap;

}

void indexData(TreeMap<string, Book>& bookMap, string& field)
{
	TreeMap<string, int> index;

	auto keysTree = bookMap.keySet();
	auto keys = keysTree.toArray();
	int count = bookMap.size();

	for (int i = 0; i < count; i++) 
	{
		string keyValue;
		const Book& book = bookMap.get(keys[i]);

		if (field == "name")
		{
			keyValue = book.name;
		}
		else if (field == "author")
		{
			keyValue = book.author;
		}
		else if (field == "releaseDate")
		{
			keyValue = book.releaseDate;
		}
		else
		{
			cout << "Invalid field name" << endl;
			delete[] keys;
			return;
		}

		if (!index.containsKey(keyValue))
		{
			index.put(keyValue, 1);
		}
		else 
		{
			int currentCount = index.get(keyValue);
			index.put(keyValue, currentCount + 1);
		}
	}

	delete[] keys;

	cout << "Index of " << field << ":" << endl;
	auto indexTree = index.keySet();
	auto indexArray = indexTree.toArray();
	int indexCount = index.size();

	for (int i = 0; i < indexCount; i++)
	{
		cout << indexArray[i] << " - " << index.get(indexArray[i]) << endl;
	}

	delete[] indexArray;
}

void viewSubset(TreeMap<string, Book>& bookMap, string& field, string& value)
{
	auto keysTree = bookMap.keySet();
	auto keys = keysTree.toArray();
	int count = bookMap.size();
	cout << "Subset of data for " << field << " = " << value << ":" << endl;

	for (int i = 0; i < count; i++)
	{
		const Book& book = bookMap.get(keys[i]);
		string keyValue;

		if ((field == "name" && book.name == value) || (field == "author" && book.author == value) || (field == "releaseDate" && book.releaseDate == value))
		{
			cout << "Name: " << book.name << ", Author: " << book.author << ", Release Date: " << book.releaseDate << ", Highest Review: " << book.highestReview << ", Lowest Review: " << book.lowestReview << endl;
		}
	}

	delete[] keys;
}

int main()
{
	string filename;
	cout << "Enter the name of the file to process: ";
	cin >> filename;

	TreeMap<string, Book> bookMap = loadBooks(filename);

	if (bookMap.size() == 0) 
	{
		cout << "No books loaded." << endl;
		return 0;
	}

	char choice;
	do
	{
		cout << "Menu:" << endl;
		cout << "1. Index data by field" << endl;
		cout << "2. View subset of data" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter a option: ";
		cin >> choice;

		switch (choice)
		{
		case '1':
		{
			string field;
			cout << "Enter the field to index. Options are [name, author, releaseDate]";
			cin >> field;
			indexData(bookMap, field);
			break;
		}
		case '2':
		{
			string field, value;
			cout << "Enter the field to filter. Options are [name, author, releaseDate]";
			cin >> field;
			cout << "Enter the filter value: ";
			cin >> value;
			viewSubset(bookMap, field, value);
			break;
		}
		case '3':
		{
			cout << "Goodbye!" << endl;
			break;
		}
		default:
		{
			cout << "Invalid option. Please try again." << endl;
		}
		}
	} 
	
	while (choice != '3');

	return 0;
}