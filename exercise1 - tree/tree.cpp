#include <iostream>
#include <list>
#include <string>
#include <cstring>
#include <algorithm>
#include "tree.h"

using namespace std;

Node* Tree::search(Node* p, string val, Node*& parent)
{
	if (p->content == val) //base case, when the val is found.
		return p;
	if (p == nullptr) //base case, when not found.
		return nullptr;
	else
	{
		for (list<Node*>::iterator it = p->responses.begin(); it != p->responses.end(); it++)
		{
			if (it == p->responses.begin())
				parent = p; //updating the parent (by reference parameter).
			Node* result = search(*it, val, parent); //recursion.
			if (result) //if val is found (if not, continue to search in the responses (++it)).
				return result;
		}
	}
	return nullptr;
}

bool Tree::searchAndPrintPath(Node* p, string val)
{
	if (p->content == val) //base case, val is found.
	{
		cout << val; //printing val.
		return true;
	}
	else
	{
		for (list<Node*>::iterator it = p->responses.begin(); it != p->responses.end(); it++)
		{
			if (searchAndPrintPath(*it, val)) //if val is found in the recursion, printing his path
			{
				cout << "=>" << p->content;
				if (p->content == root->content) //when the path printing reaches to the root.
					cout << endl;
				return true;
			}
		}
		return false; //when val is not found.
	}
}

void Tree::print(Node* p, int level)
{
	if (p == nullptr) //base case, when we reach the end of the tree.
		return;
	else
	{
		for (int i = 0; i < level; i++) //adding spaces for the printing level.
		{
			cout << "   "; //3 spaces.
		}
		cout << p->content << endl; //printing the Node content.
		++level; //going deep into the tree.
		for (list<Node*>::iterator it = p->responses.begin(); it != p->responses.end(); it++)
		{
			print(*it, level); //recursion.
		}
		return;
	}
}

void Tree::deleteAllSubTree(Node* t)
{
	if (t == nullptr) //base case, when we reach the end of the tree.
		return;
	else
	{
		for (list<Node*>::iterator it = t->responses.begin(); it != t->responses.end(); it++)
		{
			deleteAllSubTree(*it); //recursion, going deep to the tree.
			t->responses.clear(); //in the way to return, clearing the Node responses.
			delete t; //deleting the Node.
			return;
		}
	}
}

void Tree::addRoot(string newval)
{
	Node* p = new Node(newval); //call to the Node constractor.
	root = p; //setting the tree root.
	return;
}

bool Tree::addSon(string fatherdiscussion, string newresponse)
{
	//seeting a "fake" parent to the parent pointer (it's changes in the search recursion).
	string fake1 = "this-is-fake";
	Node fake(fake1);
	Node* parent = &fake;
	Node* p = new Node(newresponse); //setting the new Node response.
	Node* t = search(root, fatherdiscussion, parent); //call to the search function, returning a pointer to the father Node.
	if (!t) //if not found
		return false;
	t->responses.push_back(p); //adding the response to the responses list of the father.
	t->isLeaf = false;
	return true;
}

bool Tree::printSubTree(Node* curr, string val)
{
	bool flag = false;
	if (curr->content == val) //base case, when the Node is found
	{
		print(curr); //activating the print function for the Node's sub-tree.
		return true;
	}
	if (curr == nullptr) //base case, when Node is not found.
		return false;
	else
	{
		for (list<Node*>::iterator it = curr->responses.begin(); it != curr->responses.end(); it++)
		{
			flag = printSubTree(*it, val); //recursion. returns true when the Node is found.
			if (flag) //if not found, continue to search (++it)
				return flag;
		}
	}
	return false;
}

bool Tree::deleteSubTree(string val)
{
	Node* parent;
	Node* t = search(root, val, parent); //searching the Node of val.
	if (!t) //if not found.
		return false;
	deleteAllSubTree(t); //call to the delete function.
	parent->responses.remove(t); //removing the val Node from his father's responses list.
	return true;
}

treeList::~treeList()
{
	//for each tree, activating the delete function, and setting the root's pointers to 0.
	list<Tree*>::iterator found = trees.begin();
	while (found != trees.end())
	{
		(*found)->deleteAllSubTree((*found)->root);
		(*found)->root = 0;
		++found;
	}
	trees.clear(); //clearing the all treeList.
}

void treeList::addNewTree(string s)
{
	Tree* p = new Tree; //setting a new empty tree.
	p->addRoot(s); //setting the root (call to the Node ctor).
	trees.push_front(p); //adding the tree to the treeList.
}

void treeList::deleteTree(Tree* t)
{
	t->deleteAllSubTree(t->root); //calling the delete function for the all tree.
	trees.remove(t); //removing the root of the tree from the treeList.
	t = nullptr;
	return;
}

void treeList::searchAndPrint(string val)
{
	bool flag = false;
	list<Tree*>::iterator found = trees.begin();
	//searching the val in trees and activating the two function for the print
	while (found != trees.end() || !flag)
	{
		(*found)->printSubTree(val); //printing the sub-tree
		flag = (*found)->searchAndPrintPath(val); //printing the path to the root. 
		++found;
	}
}

bool treeList::addResponse(string rt, string prnt, string res)
{
	bool flag = false;
	list<Tree*>::iterator found = trees.begin();
	//searching the rt tree.
	while (found != trees.end())
	{
		if ((*found)->root->content == rt)
			break;
		++found;
	}
	if (found != (trees.end())) //if the tree is found.
		flag = (*found)->addSon(prnt, res); //call to the adding function.
	return flag;
}

bool treeList::delResponse(string rt, string res)
{
	bool flag = false;
	list<Tree*>::iterator found = trees.begin();
	//searching the rt tree.
	while (found != trees.end())
	{
		if ((*found)->root->content == rt)
			break;
		++found;
	}
	if (found != (trees.end())) //if tree is found.
	{
		if ((*found)->root->content == res) //if res is the root of the tree.
		{
			this->deleteTree(*found); //delelting the all tree.
			return true;
		}
		flag = (*found)->deleteSubTree(res); //deleting the sub-tree.
	}
	return flag;
}

void treeList::printAllTrees()
{
	int i = 1;
	//for each tree in the treeList, activating the printing function.
	for (auto it = trees.begin(); it != trees.end(); ++it)
	{
		cout << "Tree #" << i << endl;
		(*it)->printAllTree(); //call to the printing function.
		cout << endl;
		++i;
	}
	return;
}

void treeList::printSubTree(string rt, string s)
{
	bool flag = false;
	list<Tree*>::iterator found = trees.begin();
	//searching the rt tree.
	while (found != trees.end())
	{
		if ((*found)->root->content == rt)
			break;
		++found;
	}
	if (found != (trees.end())) //if tree is found.
	{
		(*found)->printSubTree(s); //printing the sub-tree
		flag = (*found)->searchAndPrintPath(s); //printing the path to the root. 
	}
}