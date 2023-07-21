/*Pinchas plevinski 322211558
data stracture 2
Run exercise 4*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <list>
#include <string>
#include "huffman.h"
using namespace std;

HNode::HNode()
{
	ltr = "";
	frq = 0;
	left = nullptr;
	right = nullptr;
}

HNode::HNode(string s, int n)
{
	ltr = s;
	frq = n;
	left = nullptr;
	right = nullptr;
}

void HuffmanTree::encode(string word) //the encoding function.
{
	int numOfLtrs = 0;
	int* frqTable = buildTableOfFreq(word, numOfLtrs);
	cout << "The encoded string is:\n" << numOfLtrs << endl;

	string ltrOrder = "";
	root = buildTree(frqTable, numOfLtrs);
	orderOfLetters(root, ltrOrder);
	cout << ltrOrder << endl;

	printTreeStructRec(root);
	cout << endl;

	string* codeTable = buildTableCode(ltrOrder);
	for (int i = 0; i < word.size(); i++)
		cout << codeTable[word[i]];
	cout << endl;
	return;
}

int* HuffmanTree::buildTableOfFreq(string word, int& size) //building the frequency table.
{
	int* t = new int[256];
	for (int i = 0; i < 256; i++) //intializing the table with '0'.
		t[i] = 0;
	for (int i = 0; i < word.size(); i++) //setting the frequency in the places of the table, according to the ASCII values ('a' 97).
	{
		if (t[word[i]] == 0)
			++size; //summing the letters (n).
		t[word[i]] += 1; //summing the frequency.
	}
	return t;
}

HNode* HuffmanTree::buildTree(int* table, int size) //building the tree according the frqTable and the priority queue.
{
	int n = size;
	priority_queue<HNode*, vector<HNode*>, compareNode> pQueue; //setting the priority queue.
	for (int i = 0; i < 256; i++) //setting new node according the table and entring the node into the queue.
	{
		if (table[i] != 0)
		{
			HNode* node = new HNode;
			node->frq = table[i];
			node->ltr = (char)i;
			pQueue.push(node);
			--n;
		}
		if (n == 0)
			break;
	}
	for (int i = 0; i < size - 1; i++)
	{
		HNode* node = new HNode; //setting the father node.
		node->left = pQueue.top(); //left son.
		pQueue.pop();
		node->right = pQueue.top(); //right son.
		pQueue.pop();
		node->frq = node->left->frq + node->right->frq; //setting the father's frequency.
		pQueue.push(node); //pushing to the priority queue.
	}
	return pQueue.top(); //after all iterations, returning ptr to the root.
}

void HuffmanTree::orderOfLetters(HNode* p, string& ltr) //getting the order of the letters according the tree.
{
	if (!p)
		return;
	if (!p->ltr.empty())
		ltr += p->ltr;
	orderOfLetters(p->left, ltr);
	orderOfLetters(p->right, ltr);
	return;
}

void HuffmanTree::printTreeStructRec(HNode* p) //print the structure of the tree.
{
	if (p->left == nullptr && p->right == nullptr)
	{
		cout << 1; //when it's leaf.
		return;
	}
	cout << 0; //when it's not a leaf.
	printTreeStructRec(p->left);
	printTreeStructRec(p->right);
	return;
}

string* HuffmanTree::buildTableCode(string ltrOrder) //building the code table.
{
	string* t = new string[256]; //setting the table.
	for (int i = 0; i < 256; i++)
		t[i] = "";

	string code;
	string ltr = "";
	for (int i = 0; i < ltrOrder.size(); i++)
	{
		code = "";
		ltr = ltrOrder[i];
		if (codeOfLetters(root, code, ltr))
		{
			t[ltrOrder[i]] = code;
		}
	}
	return t;
}

bool HuffmanTree::codeOfLetters(HNode* p, string& partCode, string word) //setting the code of each letter in the table, according the tree
{
	if (!p)
		return false;
	if (p->ltr == word)
		return true;
	if (codeOfLetters(p->left, partCode, word))
	{
		partCode = "0" + partCode;
		return true;
	}
	if (codeOfLetters(p->right, partCode, word))
	{
		partCode = "1" + partCode;
		return true;
	}
	return false;
}

void HuffmanTree::decode(string ltr, string treeStruct, string code, int n) //decoding the tree. 
{
	string letters = ltr;
	string binaryTree = treeStruct;
	root = new HNode;
	buildTreeDecode(root, binaryTree, letters);

	string* tableCode = buildTableCode(ltr);

	string printText = "";
	decodeText(tableCode, ltr, code, printText);
	cout << "The decoded string is: " << printText << endl;
	return;
}

void HuffmanTree::buildTreeDecode(HNode*& p, string& binaryCode, string& letters) //building the tree according the tree structure code.
{
	if (letters.empty())
		return;
	if (((int)binaryCode[0] - '0') == 1)
	{
		p->ltr = letters.front();
		letters.erase(0, 1);
		binaryCode.erase(0, 1);
		return;
	}
	if (((int)binaryCode[0] - '0') == 0)
	{
		HNode* nodeR = new HNode;
		p->right = nodeR;
		HNode* nodeL = new HNode;
		p->left = nodeL;
		binaryCode.erase(0, 1);
		buildTreeDecode(p->left, binaryCode, letters);
		buildTreeDecode(p->right, binaryCode, letters);
	}
	return;
}

void HuffmanTree::decodeText(string* table, string ltrOrder, string binaryCode, string& decoded) //decoding the binary text, according the code table.
{
	for (int i = 0; i < binaryCode.size(); i++)
	{
		for (int j = 0; j < ltrOrder.size(); j++)
		{
			if (binaryCode.substr(i, table[ltrOrder[j]].size()) == table[ltrOrder[j]])
			{
				decoded += ltrOrder[j];
				i += (int)table[ltrOrder[j]].size() - 1;
				break;
			}
		}
	}
	return;
}