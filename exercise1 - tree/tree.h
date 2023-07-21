//this is the given "tree.h" form the moodle with a bit of changes.

#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;

class Node;

//Node: each Node in the discussion tree
class Node
{
public:
	list<Node*> responses;
	string content;
	bool isLeaf;
	Node(string v) { isLeaf = true;  content = v; }

	friend class Tree;
};


//Tree: the discussion Tree
class Tree
{
	Node* root;
	Node* search(Node* p, string val, Node*& parent);
	//returns Node t where the string equals val. If t has a parent, the pointer parent will contain its address. 

	bool searchAndPrintPath(Node* p, string val);
	void print(Node* p, int level = 0);
public:
	Tree() { root = nullptr; }
	~Tree() {
		deleteAllSubTree(root);
		root = 0;
	}
	void deleteAllSubTree(Node* t); //when the Node is given, printing the Node and all is sons.
	void addRoot(string newval); //adding new tree to the treeList.
	bool addSon(string fatherdiscussion, string newresponse); //searching the "father" Node, and adding a new son to it.
	bool search(string val) //when string is given, searching Node with this string in all tree;
	{
		Node* parent;
		if (search(root, val, parent)) //call to the recursion function (Node* search). 
			cout << root->content << endl;
	}
	bool searchAndPrintPath(string val) //when string is given, searching Node with this string in all tree, and printing the path to the root.
	{
		bool flag = searchAndPrintPath(root, val); //call to the recursion function.
		return flag;
	}

	void printAllTree() { print(root); } //runs the "print" function on all the tree.
	void printSubTree(string val) { printSubTree(root, val); } //when string is given, searching Node with the string and printing all is sons.
	bool printSubTree(Node* curr, string val); //searching Node with the string and printing all is sons.
	bool deleteSubTree(string val); //when string is given, deleting all of is sub-tree. 

	friend class treeList;
};


class treeList
{
	list<Tree*> trees;

public:
	treeList() {} //constractor
	~treeList(); //distractor.
	void addNewTree(string s); //adding new tree to treeList (case n).
	void deleteTree(Tree*); //deleting whole tree.
	void searchAndPrint(string val); //when string is given, searching Node with this string in all tree, and printing the path to the root.
	bool addResponse(string rt, string prnt, string res); //adding new Node to a tree (case s).
	bool delResponse(string rt, string res); //deleting Node from a tree (case d).
	void printAllTrees(); //printing all the trees (case p).
	void printSubTree(string rt, string s); //printing sub-tree (case r and w).
};