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
	BinaryTree<pair<K, V>> tree;
	int mapSize;
	BSTNode<pair<K, V>>* findNode(const K& key) 
	{
		auto node = tree.root;
		while (node) 
		{
			if (node->data.first == key)
			{
				return node;
			}
			if (key < node->getItem().first)
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
	TreeMap() :mapSize(0) {}
	void clear() 
	{
		tree.clear();
		mapSize = 0;
	}

	bool containsKey(const K& key)
	{
		return findNode(key) != nullptr;
	}

	V& get(const K& key)
	{
		auto node = findNode(key);
		if (!node)
		{
			throw invalid_argument("Key not found: " + to_string(key));
		}
		return node->getItem().second;
	}

	BinaryTree<K> keySet()
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

	void put(const K& key, const V& value)
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

	int size() 
	{
		return mapSize;
	}

	bool removeKey(const K& key) 
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

	V& operator[](const K& key)
	{
		auto node = findNode(key);
		if (!node)
		{
			throw invalid_argument("Key not found: " + to_string(key));
		}
		return node->getItem().second;
	}

};
