#pragma once
#include "BinaryTree.h"
#include <iostream>
#include <stdexcept>
#include <utility>

using namespace std;

template <class K, class V>
class TreeMap 
{

	private:
	BinaryTree<pair<K, V>> tree; //A tree to store the key values 
	int mapSize = 0; 

	// a funciton to find a node with a given key
	BSTNode<pair<K, V>>* findNode(const K& key) 
	{
		auto node = tree.root;
		while (node) 
		{
			if (node->data.first == key)
			{
				return node;
			}
			if (key < node->getItem().first) // moves left or right based on the comparison
			{
				node = node->getLeft();
			}
			else
			{
				node = node->getRight();
			}
		}
		return nullptr;
	}

public:

	TreeMap() = default;

	void clear() // clears the tree
	{
		tree.clear();
		mapSize = 0;
	}

	bool containsKey(const K& key) // checks if the key exists in the maps
	{
		return findNode(key) != nullptr;
	}

	// gets the alue associted wiht the key
	V& get(const K& key)
	{
		auto node = findNode(key);
		if (!node)
		{
			throw invalid_argument("Key not found");
		}
		return node->getItem().second;
	}

	BinaryTree<K> keySet() //returns a binarytree with the all the keys of the map
	{
		BinaryTree<K> keysTree;
		auto itemsArray = tree.toArray();
		int count = tree.count();
		for (int i = 0; i < count; i++)
		{
			keysTree.add(itemsArray[i].first);
		}
		delete[] itemsArray;
		return keysTree;
	}

	void put(const K& key, const V& value) //adds a key pair to the map
	{
		auto node = findNode(key);
		if (node)
		{
			node->getItem().second = value;
		}
		else
		{
			pair<K, V> item = make_pair(key, value);
			tree.add(item);
			mapSize++;
		}
	}

	int size() //returns the number of elemenets in the map
	{
		return mapSize;
	}

	bool removeKey(const K& key) //removes the key pair form the map
	{
		auto node = findNode(key);
		if (!node)
		{
			return false;
		}
		tree.remove(make_pair(key, node->getItem().second));
		mapSize--;
		return true;
	}

	V& operator[](const K& key) //overload the subscript operator to access values by key
	{
		auto node = findNode(key);
		if (!node)
		{
			throw invalid_argument("Key not found");
		}
		return node->getItem().second;
	}

};
