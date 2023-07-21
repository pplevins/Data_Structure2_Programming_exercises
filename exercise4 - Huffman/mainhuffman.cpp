/*Pinchas plevinski 322211558
data stracture 2
Run exercise 4*/

#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <cmath>
#include "huffman.h"


int main()
{
	int choice, n, sum;
	string word;
	string ltr, treeStruct, code, decoded;



	cout << "enter 1 to encode a text\n";
	cout << "enter 2 to decode a text\n";
	cout << "enter 3 to exit\n";

	do
	{
		cin >> choice;
		switch (choice)
		{
		case 1:

			cout << "enter the original text" << endl;
			cin >> word;

			HuffmanTree myTree;
			myTree.encode(word);
			//Build Huffman tree given the data inside "word".
			//Then find the code of each letter.
			//Then print the output - number of leaves, order of letters, tree structure and the encoded text - according to the explanation in the exercise.

			break;
		case 2:

			cout << "enter n ";
			cin >> n;
			cout << "enter the letters ";
			cin >> ltr;
			if (n != ltr.size())
			{
				cout << "ERROR\n";
				break;
			}
			cout << "enter the encoded structure ";
			cin >> treeStruct;
			sum = 0;
			for (int i = 0; i < treeStruct.size(); i++)
				sum += treeStruct[i] - '0';
			if (sum != n)
			{
				cout << "ERROR\n";
				break;
			}
			cout << "enter the encoded text ";
			cin >> code;

			HuffmanTree hTree;
			hTree.decode(ltr, treeStruct, code, n);
			//input the number of leaves, the  order of letters, tree structure and the encoded text.
			//build the Huffman Tree according to the tree strcture. put the letters in the leaves according to the given order. 
			//Given the Huffman Tree and the encoded text, find the original text, and print it. 
			break;
		case 3:
			break;
		default:
			cout << "ERROR\n";
		}

	} while (choice != 3);
	return 0;
}