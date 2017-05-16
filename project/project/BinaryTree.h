/***********************************************************************************
* PROGRAM FILENAME: BinaryTree_CS200.cpp
* DESCRIPTION:	This program builds a BST and reads input from a txt file
* DESIGNER:  Jerome Latona
*2 March 2017
* DIablo Valley College ComSci 200
************************************************************************************/
#ifndef BinaryTree_H
#define BinaryTree_H
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "GameList.h"
using namespace std;

//node structure for the binary search tree
struct treeNode
{
	treeNode* leftPointer = NULL;
	treeNode* rightPointer = NULL;
	int nodeNumber;
	string steamUser;
	GameList* top5;//seperate class holds most played games
};

class BinaryTree
{
//	friend class LibInfo;//allow LibInfo be driver for tree growth
protected:
	treeNode* root;
	treeNode* findParent(int numberToDelete, treeNode* root);//delete node helper function
	bool InsertNode(treeNode* tempPtr);//overload to redistribute excess node after deletion
	int numberOfNodes;
public:
	BinaryTree();//creates a pointer to the root of the tree and a counter for number of nodes in tree
	~BinaryTree();// de-allocates all dynamic memory allocated for the binary search tree.
	bool IsEmpty();//returns true if binary search tree is empty, false otherwise
	bool InsertNode(int id_64, string uName, GameList* gList); // inserts a new node into the correct location within a binary search tree.
	bool FindNode(int numberToFind);//finds a node, or NULL if tree is empty, or would-be parent node if node doesn't exist
	treeNode* CreateNode(int numberToPlace, string steamID, GameList* topFive);// allocate and fills new node. Passes back pointer to new node, or NULL if node could not be allocated.
	void DeleteNode(int numberToDelete);// deletes a node from the binary search tree.
	void FreeNodes(treeNode* nodeWalker);// recursively de-allocates all dynamic memory allocated to nodes in the binary search tree.
	void InOrderDisplay(treeNode* nodeWalker, int &i);// neatly displays all integers in the list in sorted order, using a recursive, in-order traversal.
	void InOrderDisplayCall();//calls InOrderDisplay if necessary
	GameList* MostPlayedGame();
	void TraverseTree(treeNode * treeWalker, LinkedListNode* gamesDynamicListFront, int & linkedListSize);
};
/*
void UserMenuToInputTextFileName(string & inputTextFile);	//menu for user to imput string file.  Returns when correct
int ReadTextFile(string inputTextFile, BinaryTree& treeRoot);
void UserMenu2(BinaryTree treeRoot);
*/

#endif
