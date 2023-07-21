/*Pinchas plevinski 322211558
data stracture 2
Run exercise 3*/

//this is the standard main file giving for the program.

#include <iostream>
#include <list>
#include <string>
#include "trie.h"

using namespace std;


int main()
{

	char ch;
	string wrd;
	Trie tr;
	int comp;

	cout << "\nTRIE PROGRAM" << endl;
	cout << "\nChoose one of the following" << endl;
	cout << "a: add a new word" << endl;
	cout << "d: delete a word" << endl;
	cout << "s: check if a word exists " << endl;
	cout << "c: complete the possible word name " << endl;
	cout << "p: print trie" << endl;
	cout << "e: exit " << endl;
	do
	{
		cin >> ch;

		switch (ch)
		{
		case 'a':
			cout << "Enter a word to insert " << endl;
			cin >> wrd;
			if (tr.insert(wrd) == false)
				cout << "ERROR\n";
			break;
		case 'd':
			cout << "Enter a word to del " << endl;
			cin >> wrd;
			if (!tr.delW(wrd)) cout << "ERROR\n";
			break;
		case 's':
			cout << "Enter a word to search " << endl;
			cin >> wrd;
			if (tr.search(wrd))
				cout << "exists\n";
			else
				cout << "does not exist\n";
			break;

		case 'c':
			cout << "Enter a prefix to complete " << endl;
			cin >> wrd;
			comp = tr.printAutoSuggestions(wrd);

			if (comp == 0)
				cout << "No string exist with this prefix\n";
			break;
		case 'p': tr.printTrie(); break;
		case 'e':cout << "bye " << endl; break;
		default: cout << "ERROR " << endl;  break;
		}//switch
	} while (ch != 'e');
	return 0;
}