/*Pinchas plevinski 322211558
data stracture 2
Run exercise 4*/

#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <list>
#include <string>
using namespace std;

//a node of a leave or a node of a subtree.
class HNode
{
public:
	string ltr;
	int frq;
	HNode* left;
	HNode* right;


	HNode();
	HNode(string s, int n);

};

class compareNode //class for the priority queue.
{
public:
	HNode* n;
	bool operator()(HNode* const& n1, HNode* const& n2)
	{
		return(n1->frq > n2->frq);
	}
};

class HuffmanTree
{
	HNode* root;
public:
	void encode(string word); //the encoding function.
	int* buildTableOfFreq(string word, int& size); //building the frequency table.
	HNode* buildTree(int* table, int size); //building the tree according the frqTable and the priority queue.
	void orderOfLetters(HNode* p, string& ltr); //getting the order of the letters according the tree.
	void printTreeStructRec(HNode* p); //print the structure of the tree.
	string* buildTableCode(string ltrOrder); //building the code table.
	bool codeOfLetters(HNode* p, string& partCode, string word); //setting the code of each letter in the table, according the tree

	void decode(string ltr, string treeStruct, string code, int n); //the decoding function.
	void buildTreeDecode(HNode*& p, string& binaryCode, string& letters); //building the tree according the tree structure code.
	void decodeText(string* table, string ltrOrder, string binaryCode, string& decoded); //decoding the binary text, according the code table.
};
