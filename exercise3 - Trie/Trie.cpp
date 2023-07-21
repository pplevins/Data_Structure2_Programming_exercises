/*Pinchas plevinski 322211558
data stracture 2
Run exercise 3*/

#include <iostream>
#include "trie.h"
using namespace std;

TrieNode* getNode(void) //creating new node in the trie.
{
    TrieNode* p = new TrieNode;
    for (int i = 0; i < ALPHABET_SIZE; ++i) //intializing all the array with nullptr.
    {
        p->children[i] = nullptr;
    }
    p->isWordEnd = false;
    return p;
}

bool isLastNode(TrieNode* root) //checking if the node is not father of diffrent nodes.
{
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i] != nullptr)
            return false;
    }
    return true;
}

bool insertT(TrieNode* root, string key) //insert new string to the trie.
{
    if (searchT(root, key)) //if the word exists.
        return false; //no action needed.

    TrieNode* ptr = root; //ptr to run all over the trie.
    int i = 0;
    while (i < key.size())
    {
        int index = CHAR_TO_INDEX(key[i]); //converting the letter to index
        if (ptr->children[index] == nullptr) //if doesn't exist
            ptr->children[index] = getNode(); //insert new node in the index.
        ptr = ptr->children[index]; //moving to the next level for the next letter to insert.
        i++;
    }

    ptr->isWordEnd = true; //setting to end of word.
    return true;
}

bool delT(TrieNode* root, string key) //deleting string from the trie.
{
    bool flag = false;
    root = delR(root, key, 0, flag); //the recurssion function.
    if (flag) //if string deleted.
        return true;
    else
        return false;
}

TrieNode* delR(TrieNode* root, string key, int ind, bool& flag) //the recursive function for the delete.
{
    if (!root) // if the tree is empty.
        return nullptr;

    if (ind == key.size()) //when we rheached to the last character of key.
    {
        if (root->isWordEnd)
        {
            root->isWordEnd = false; //because of the delete, the node is no more the word's end.
            flag = true; //setting the flag of the delete.
        }

        if (isLastNode(root)) // if the node is not prefix of any other word
        {
            delete (root); //deleting the node
            root = nullptr;
        }
        return root;
    }

    // if we didn't reached to the end of the word yet, doing the reccussion
    int index = CHAR_TO_INDEX(key[ind]); //converint the index.
    root->children[index] = delR(root->children[index], key, ind + 1, flag); //reccurssion.

    //when the node doesn't have children, or when we finished the reccurssion and there's no node in the way.
    if (isLastNode(root) && root->isWordEnd == false)
    {
        delete (root); //deleting the node.
        root = nullptr;
    }
    return root;
}

bool searchT(TrieNode* root, string key) //searching string in the trie.
{
    if (!root) //if trie is empty.
        return false;
    TrieNode* ptr = root; //ptr to run all over the trie.
    int i = 0;
    while (i < key.size())
    {
        int index = CHAR_TO_INDEX(key[i]); //converting to index.
        if (ptr->children[index] == nullptr) //the word is not found.
            return false;
        ptr = ptr->children[index];
        i++;
    };
    return ptr->isWordEnd; //returning true only when the node is the word's end.
}

void suggestionsRec(TrieNode* root, string currPrefix) //the reccurssion for complete the possible word name.
{
    if (root->isWordEnd) //when found word that is the prefix.
        cout << currPrefix << endl;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i]) //if there's children to the node.
        {
            char child = 'a' + i; //converting back to char.
            suggestionsRec(root->children[i], currPrefix + child);
            //reccurssion. adding the child to the prefix, and continue until the word's end.
        }
    }
}

int printAutoSuggestionsT(TrieNode* root, string query) //for complete the possible word name.
{
    TrieNode* ptr = root;
    for (char i : query)
    {
        int ind = CHAR_TO_INDEX(i); //converting the index

        //if no prefix of the word is in the children's node.
        if (!ptr->children[ind])
            return 0;

        ptr = ptr->children[ind]; //checking the next letter.
    }

    if (isLastNode(ptr)) //if the prefix found, but it doesn't have any children to suggest.
        return 0;
    suggestionsRec(ptr, query); //going to the reccurssion function for printing the suggestions.
    return 1;
}

void printT(TrieNode* t, int level) //printing all the trie.
{
    if (isLastNode(t)) //when reached to the end of the trie.
        cout << endl;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (t->children[i]) //if there's children to the node.
        {
            for (int j = 0; j < level; ++j) //printing the spaces according to the level.
            {
                cout << "   ";
            }
            cout << (char)('a' + i) << ":\n"; //printing the letter (converted to char).
            printT(t->children[i], level + 1); //reccurssion.
        }
    }
}