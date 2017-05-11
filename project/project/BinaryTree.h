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

using namespace std;

//node structure for the binary search tree
struct treeNode
{
	treeNode * leftPointer = NULL;
	treeNode * rightPointer = NULL;
	int nodeNumber;
	string steamUser;

	string gameNameInTree[5];
	int gameTimeInTree[5];
};

//root pointer for the binary search tree.  Number of nodes is contained the int numberofNodes
class TreeRootStruct
{
private:
	treeNode * root;
	int numberOfNodes;
	treeNode* findParent(int numberToDelete, treeNode* root);//delete node helper function

	//function declarations
	TreeRootStruct(); 								//creates a pointer to the root of the tree and a counter for number of nodes in tree
	bool IsEmpty(); 						//returns true if binary search tree is empty, false otherwise
	bool FindNode(int numberToFind);//finds a node, or NULL if tree is empty, or would-be parent node if node doesn't exist
	treeNode* CreateNode(int numberToPlace, string steamID);					// – allocate and fills new node. Passes back pointer to new node, or NULL if node could not be allocated.
	bool InsertNode(int id_64, string uName); //– inserts a new node into the correct location within a binary search tree.
	bool InsertNode(treeNode* tempPtr);//overload to redistribute excess node after deletion
	void DeleteNode(int numberToDelete);// – deletes a node from the binary search tree.
	void FreeNodes(treeNode* nodeWalker);// – recursively de-allocates all dynamic memory allocated to nodes in the binary search tree.
	~TreeRootStruct();// – de-allocates all dynamic memory allocated for the binary search tree.
	void InOrderDisplay(treeNode* nodeWalker, int &i);// – neatly displays all integers in the list in sorted order, using a recursive, in-order traversal.
	void InOrderDisplayCall();//calls InOrderDisplay if necessary
	void MostPlayedGame(string gameWithMostTime, int  &timeSpentPlayingGame);

	//end function declarations
};

void UserMenuToInputTextFileName(string & inputTextFile);	//menu for user to imput string file.  Returns when correct
int ReadTextFile(string inputTextFile, TreeRootStruct& treeRoot);
void UserMenu2(TreeRootStruct treeRoot);

#endif
