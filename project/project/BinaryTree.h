/****************************************************************************************
* PROGRAM FILENAME: Latona-BinaryTree_CS200.cpp
* DESCRIPTION:	This program builds a BST and reads input from a txt file
* DESIGNER:  Jerome Latona
*2 March 2017
* Regis University CS372
*****************************************************************************************/
#ifndef BinaryTree_H
#define BinaryTree_H

//#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "GameList.h"
using namespace std;

//node structure for the binary search tree
struct treeNode
{
	treeNode * leftPointer = NULL;
	treeNode * rightPointer = NULL;
	int nodeNumber;
	string steamUser;
	GameList* top5;//seperate class holds most played games
};

//root pointer for the binary search tree.  Number of nodes is contained the int numberofNodes
class BinaryTree
{
private:
	treeNode * root;
	int numberOfNodes;
	treeNode* findParent(int numberToDelete, treeNode* root);//delete node helper function
	bool InsertNode(treeNode* tempPtr);//overload to redistribute excess node after deletion
public:
	//creates a pointer to the root of the tree and a counter for number of nodes in tree
	BinaryTree(); 	
	//returns true if binary search tree is empty, false otherwise
	bool IsEmpty(); 
	//finds a node, or NULL if tree is empty, or would-be parent node if node doesn't exist
	bool FindNode(int numberToFind);
	// allocate and fills new node. Passes back pointer to new node, or NULL if node could not be allocated.
	treeNode* CreateNode(int numberToPlace, string steamID, GameList* topFive);
	// inserts a new node into the correct location within a binary search tree.
	bool InsertNode(int id_64, string uName, GameList* gList); 
	// deletes a node from the binary search tree.
	void DeleteNode(int numberToDelete);
	// recursively de-allocates all dynamic memory allocated to nodes in the binary search tree.
	void FreeNodes(treeNode* nodeWalker);
	// de-allocates all dynamic memory allocated for the binary search tree.
	~BinaryTree();
	// neatly displays all integers in the list in sorted order, using a recursive, in-order traversal.
	void InOrderDisplay(treeNode* nodeWalker, int &i);
	void InOrderDisplayCall();//calls InOrderDisplay if necessary
	//void MostPlayedGame(string gameWithMostTime, int  &timeSpentPlayingGame);
};
/*
void UserMenuToInputTextFileName(string & inputTextFile);	//menu for user to imput string file.  Returns when correct
int ReadTextFile(string inputTextFile, BinaryTree& treeRoot);
void UserMenu2(BinaryTree treeRoot);
*/

#endif
