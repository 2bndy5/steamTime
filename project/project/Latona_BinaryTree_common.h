//*******************************************************************************************************
// PROGRAM FILENAME: Latona_BinaryTree_ Common.h
// DESCRIPTION:	Global declarations
// DESIGNER:  Jerome Latona
//
//25 May 2017
//Diablo Valley College ComSci200
//*******************************************************************************************************

#ifndef LATONA_BINARYTREE_COMMON_H
#define LATONA_BINARYTREE_COMMON_H
#include <string>

using namespace std;

//node structure for the binary search tree
struct treeNode
{
	treeNode * leftPointer = NULL;
	treeNode * rightPointer = NULL;
	int nodeNumber;
	string steamUser;
	
	string gameNameInTree[5] = {"000"};
	int gameTimeInTree[5];
};

//root pointer for the binary search tree.  Number of nodes is contained the int numberofNodes
struct treeRootStruct
{
	treeNode * root;
	int numberOfNodes;
};

const int MAX_TREE_SIZE=10;

#endif 
