/*Pinchas plevinski 322211558
data stracture 2
Run exercise 3*/

// C++ program to demonstrate auto-complete feature 
// using Trie data ure.
//this is the standard header file giving for the program with a bit changes.

#include <iostream>
#include <string>
using namespace std;

// Alphabet size (# of symbols) 
#define ALPHABET_SIZE (26) 

// Converts key current character into index 
// use only 'a' through 'z' and lower case 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 

// trie node 
struct TrieNode
{
	TrieNode* children[ALPHABET_SIZE];

	// isWordEnd is true if the node represents 
	// end of a word 
	bool isWordEnd;
};


TrieNode* getNode(void); //creating new node in the trie.
bool isLastNode(TrieNode* root); //checking if the node is not father of diffrent nodes.
bool insertT(TrieNode* root, string key); //insert new string to the trie.
bool delT(TrieNode* root, string key); //deleting string from the trie.
TrieNode* delR(TrieNode* root, string key, int ind, bool &flag); //the recursive function for the delete.
bool searchT(TrieNode* root, string key); //searching string in the trie.
void suggestionsRec(TrieNode* root, string currPrefix); //the reccurssion for complete the possible word name.
int printAutoSuggestionsT(TrieNode* root, string query); //complete the possible word name.
void printT(TrieNode* t, int level); //printing all the trie.



class Trie
{
	TrieNode* root;

public:
	Trie() { root = getNode(); }
	bool insert(string wrd) { return insertT(root, wrd); }
	bool delW(string wrd) { return delT(root, wrd); }
	int printAutoSuggestions(string wrd) { return printAutoSuggestionsT(root, wrd); }
	bool search(string key) { return searchT(root, key); }
	void printTrie() { printT(root, 0); }

};