//#pragma once
//#pragma once
//#include <iostream>
//using namespace std;
//const int ALPHABET = 26;
//int chToInd(char ab) { return (int)ab - (int)'a'; }
//class Trie
//{
//protected:
//	class TrieNode
//	{
//	public:
//		TrieNode* children[ALPHABET] = { 0 };
//		TrieNode* father ;
//		bool isEndWord = false;
//		//int countChildren = 0;
//	public:
//		TrieNode() {};
//		TrieNode(TrieNode* dad) { father = dad; };
//	};
//	TrieNode* root;
//public:
//	Trie()
//	{
//		root = new TrieNode(NULL);
//	}//ctor - initialize root to be "root"
//
//	//all functions
//	void insertWord(string str);
//	void deleteWord(string str);
//	bool searchWord(string str);
//	void printAllWordsFromPrefix(TrieNode*);
//private:
//	bool searchWord(string str, TrieNode* node);
//};