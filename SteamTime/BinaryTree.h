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
	User* user;
	GameList* top5;//seperate class holds most played games
};

class BinaryTree
{
	friend class LibInfo;//allow LibInfo be driver for tree growth
protected:
	treeNode* root;
	void traverseTree(treeNode * treeWalker, LinkListNode*& gamesDynamicListFront, int & linkedListSize);
	void mergeSortCall(ListNode *& unsortedGameList, int linkedListSize);
	void mergeSort(int lowIndex, int highIndex, ListNode *& unsortedGameList, ListNode *& sortedGameList);
	void merge(int midIndex, int lowIndex, int highIndex, ListNode *& unsortedGameList, ListNode *& sortedGameList);
	int numberOfNodes;
public:
	BinaryTree();//creates a pointer to the root of the tree and a counter for number of nodes in tree
	~BinaryTree();// de-allocates all dynamic memory allocated for the binary search tree.
	bool isEmpty();//returns true if binary search tree is empty, false otherwise
	int getSize();//return number of nodes
	bool insertNode(User* u, GameList* gList); // inserts a new node into the correct location within a binary search tree.
	bool findNode(unsigned long long numberToFind);//finds a node, or NULL if tree is empty, or would-be parent node if node doesn't exist
	treeNode* createNode(User* u, GameList* topFive);// allocate and fills new node. Passes back pointer to new node, or NULL if node could not be allocated.
	void freeNodes(treeNode* nodeWalker);// recursively de-allocates all dynamic memory allocated to nodes in the binary search tree.
	void inOrderDisplay(treeNode* nodeWalker, int &i);// neatly displays all integers in the list in sorted order, using a recursive, in-order traversal.
	void inOrderDisplayCall();//calls InOrderDisplay if necessary
	GameList* mostPlayedGame();

};
/*
void UserMenuToInputTextFileName(string & inputTextFile);	//menu for user to imput string file.  Returns when correct
int ReadTextFile(string inputTextFile, BinaryTree& treeRoot);
void UserMenu2(BinaryTree treeRoot);
*/

#endif
