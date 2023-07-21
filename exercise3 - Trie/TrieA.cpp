//#include <iostream>
//#include "TrieA.h"
//using namespace std;
//
//void Trie::insertWord(string str)
//{
//	//check if word exists
//	if (searchWord(str))//word exists
//	{
//		cout << " word exists, no need to insert\n";
//		return;
//	}
//	//search for the word in the tree
//	//start from beginning of word and continue
//	
//	TrieNode* ptr = root;//for going over tree
//	int i = 0;//begining of word 
//	while (i < str.size())
//	{
//		//doesn't exist - insert
//		int index = chToInd(str[i]);
//		if (ptr->children[index] == nullptr)
//			ptr->children[index] = new TrieNode(ptr);
//		ptr = ptr->children[index];
//		i++;
//	}
//	//end of word
//	ptr->isEndWord = true;
//}