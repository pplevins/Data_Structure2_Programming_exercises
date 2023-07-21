/*Pinchas plevinski 322211558
data stracture 2
Run exercise 2*/

//the standard "HashTable.h" file for the program, with the body of the function in the same file (template class).

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

template <typename T, typename K>
class HashTable
{
protected:

	enum state { empty, full, deleted };
	template <typename U, typename V>
	class Item
	{
	public:
		U data;
		V key;
		state flag;
		Item() {} //default ctor.
		Item(U d, V  k, state f) { data = d; key = k; flag = f; } //parameter ctor.
	};


	int size;
	Item<T, K>* arr;
	bool prime(int n); //checking if n is a prime number.
	int hash(K key, int i); //the hash function.
	virtual int h1(K key) = 0; //first hash function for the double hashing (virtual).
	virtual int h2(K key) = 0; //the skiping function for the double hashing (i * h2). virtual.
public:
	HashTable(int m = 10); //parameter ctor (with a default parameter).
	~HashTable(); //dtor.
	void add(K& key, T& dat); //adding new key to the table.
	int remove(K key); //removing element from the table.
	int search(K key); //searching element in the table.
	T* entryData(K i) //returning a pointer to the element's data (in our case, the begining of the list<string>titles).
	{
		int ind = search(i); //call to the search function.
		if (ind == -1) //when not found.
			return NULL;
		else
			return &(arr[ind].data);
	}
};

template <typename T, typename K>
bool HashTable<T, K>::prime(int n)
{
	if (n == 0 || n == 1) //n is not a prime
		return false;
	for (int i = 2; i <= n / 2; ++i) //checking if n is dividing by a smaller number.
	{
		if (n % i == 0) //not a prime.
			return false;
	}
	return true;
}

template <typename T, typename K>
int HashTable<T, K>::hash(K key, int i) //the hash function.
{
	return (h1(key) + (i * h2(key))) % size;
}

template <typename T, typename K>
HashTable<T, K>::HashTable(int m)
{
	if (prime(m)) //if m is prime.
		size = m;
	else
	{
		for (int i = m - 1; i > 1; --i) //searching the closest prime number to m.
		{
			if (prime(i))
			{
				size = i;
				break;
			}
		}
	}
	arr = new Item<T, K>[size]; //setting the table.
	for (int i = 0; i < size; ++i)
	{
		arr[i].flag = empty; //setting an empty table.
	}
}

template <typename T, typename K>
HashTable<T, K>::~HashTable() //dtor.
{
	if (arr)
		delete[] arr;
}

template <typename T, typename K>
void HashTable<T, K>::add(K& key, T& dat)
{
	for (int i = 0; i < size; ++i)
	{
		int j = hash(key, i); //hashing the key, and getting the index.
		//only if the arr[index] is empty, setting the element in the table. else, hashing again.
		if (arr[j].flag == empty || arr[j].flag == deleted)
		{
			arr[j].data = dat;
			arr[j].key = key;
			arr[j].flag = full;
			return;
		}
	}
	cout << "error\n";
}

template <typename T, typename K>
int HashTable<T, K>::remove(K key)
{
	for (int i = 0; i < size; ++i)
	{
		int j = hash(key, i);
		if (arr[j].flag == empty) //getting the end of the chosen places, according to the hashing function.
			return -1; //not found.
		if (arr[j].key == key) //if found.
		{
			arr[j].flag = deleted; //mark as a deleted element.
			return j;
		}
	}
	return -1; //not found in all the chosen placesin the table.
}

template <typename T, typename K>
int HashTable<T, K>::search(K key)
{
	for (int i = 0; i < size; ++i)
	{
		int j = hash(key, i);
		if (arr[j].flag == empty) //not found at the index from the hashing function.
			return -1; //not found.
		if (arr[j].flag == deleted) //if it's deleted, continue searching for the next of the hashing function.
			continue;
		if (arr[j].key == key)
			return j; //returning the index.
	}
	return -1; //when coming to the end of the table.
}

//this is the class I used to test phase 1 of the exercise.

//class TestHash :public HashTable<int, int>
//{
//public:
//	TestHash(int n) :HashTable(n) {}
//	int h1(int key) { return key % size; }
//	int h2(int key) { return (key % (size - 1) + 1) % size; }
//};