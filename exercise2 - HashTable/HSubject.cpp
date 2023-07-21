/*Pinchas plevinski 322211558
data stracture 2
Run exercise 2*/

#include <iostream>
#include <string>
#include <list>
using namespace std;
#include "HSubject.h"

void HSubject::printS(string ky) //printing all title of the subject.
{
	list<string>* listA = entryData(ky); //returning a pointer to the start of the titles list.
	if (!listA) //if null returned.
	{
		cout << "ERROR\n";
		return;
	}
	else
	{
		cout << "Subject " << ky << " " << listA->size() << " topics\n";
		list<string>::iterator it = listA->begin();
		while (it != listA->end())
		{
			cout << *it << " "; //printing all the titles.
			++it;
		}
		cout << endl;
		return;
	}
}

void HSubject::printN(string ky, int N) //printing N titles of the subject.
{
	list<string>* listA = entryData(ky); //returning a pointer to the start of the titles list.
	if (!listA)  //if null returned.
	{
		cout << "ERROR\n";
		return;
	}
	else
	{
		list<string>::iterator it = listA->begin();
		int i = 0;
		while (it != listA->end() && i  < N)
		{
			cout << *it << " "; //printing N titles (or if N > size of the list, printing all the titles.
			++it;
			++i;
		}
		cout << endl;
		return;
	}
}

void HSubject::print() //printing all the table in a lexicographic order.
{
	cout << "All subjects and titles:\n";
	//sorting all the subject keys in a new array, then sorting it.
	list<string>* p;
	string* copyArr = new string[size];
	int j = 0;
	for (int i = 0; i < size; i++)
		if (arr[i].flag == full)
		{
			copyArr[j] = arr[i].key;
			++j;
		}
	sort(copyArr, copyArr + j); //sorting all the keys.
	for (int i = 0; i < j; ++i)
	{
		p = entryData(copyArr[i]); //finding the titles list's head.
		cout << copyArr[i] << ": "; //printing the subject.
		for (list<string>::iterator it = p->begin(); it != p->end(); ++it)
		{
			cout << *it << " "; //printing all the titles for each subject.
		}
		cout << endl;
	}
	delete[] copyArr; //deleting the keys copy array.
	copyArr = nullptr;
	return;
}

void HSubject::startNewTable() //initializing the table.
{
	for (int i = 0; i < size; ++i)
	{
		arr[i].flag = empty; //setting all element to be empty.
	}
}

void HSubject::addSubjectAndTitle(string s, string t) //adding new subject and/or title.
{
	list<string>* p = entryData(s); //searching if the subject exist in the table.
	if (p)
		p->push_front(t); //if exist, placing the new title in the subject.
	else //if subject doesn't exist.
	{
		list<string> newList; //setting new titles list.
		newList.push_front(t); //putting the title in the head of the list.
		add(s, newList); //adding the new element in the table.
	}
}