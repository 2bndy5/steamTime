//*******************************************************************************************************
// PROGRAM FILENAME: Latona-BinaryTree_CS200.cpp
// DESCRIPTION:	This program builds a BST and reads input from a txt file
// DESIGNER:  Jerome Latona
//
//2 March 2017
//Regis University CS372
//*******************************************************************************************************

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
	
	string gameNameInTree[5] = "000";
	int gameTimeInTree[5];
};

//root pointer for the binary search tree.  Number of nodes is contained the int numberofNodes
struct treeRootStruct
{
	treeNode * root;
	int numberOfNodes;
};

//function declarations
treeRootStruct CreateTree(); 								//creates a pointer to the root of the tree and a counter for number of nodes in tree
bool IsEmpty(treeRootStruct treeRoot); 						//returns true if binary search tree is empty, false otherwise
void UserMenuToInputTextFileName(string & inputTextFile);	//menu for user to imput string file.  Returns when correct
int ReadTextFile(string inputTextFile, treeRootStruct& treeRoot);
bool FindNode(treeNode * &nodeFinder, treeRootStruct treeRoot, int numberToFind);//finds a node, or NULL if tree is empty, or would-be parent node if node doesn't exist
treeNode* CreateNode(int numberToPlace);					// � allocate and fills new node. Passes back pointer to new node, or NULL if node could not be allocated.
void InsertNode(treeNode* nodeToInsert, treeRootStruct &treeRoot); //� inserts a new node into the correct location within a binary search tree.
void DeleteNode(int numberToDelete, treeRootStruct &treeRoot);// � deletes a node from the binary search tree.
void FreeNodes(treeNode* nodeWalker);// � recursively de-allocates all dynamic memory allocated to nodes in the binary search tree.
void DestroyTree(treeRootStruct &treeRoot);// � de-allocates all dynamic memory allocated for the binary search tree.
void InOrderDisplay(treeNode* nodeWalker, int &i);// � neatly displays all integers in the list in sorted order, using a recursive, in-order traversal.
void InOrderDisplayCall(treeRootStruct treeRoot);//calls InOrderDisplay if necessary
void UserMenu2(treeRootStruct treeRoot);
void MostPlayedGame(treeRootStruct treeRoot, string gameWithMostTime, int  &timeSpentPlayingGame);

//end function declarations



//**********************************************************************************************************************
// FUNCTION: main()
// DESCRIPTION: Central function that calls relevant functions for the building and manipulating of a binary search tree
// INPUT PARAMETERS: none
// OUTPUT: none
// RETURN VALUE: returns int 0 when everything goes well
//**********************************************************************************************************************
int main ()
{
	int memoryAllocationValidation=0;						//0 is good, any other value is allocation error
	
	string inputTextFile = "File1.txt";
	treeRootStruct treeRoot = CreateTree();
	UserMenuToInputTextFileName(inputTextFile);
	memoryAllocationValidation = ReadTextFile(inputTextFile, treeRoot);
	if(memoryAllocationValidation !=0)
	{cout << "\nMemory allocation fault.  Unable to complete build of Binary Search Tree.\n";}
	UserMenu2(treeRoot);
	
	return 0;
}//end main()

//**********************************************************************************************************************
// FUNCTION: CreateTree()
// DESCRIPTION: Allocate a binary search tree structure, and initialize the root pointer in it to NULL and the count to 0, 
//					to indicate an empty tree. 
// INPUT PARAMETERS: none
// OUTPUT: none
// RETURN VALUE: Returns a pointer to the root node of the new binary search tree structure.
//**********************************************************************************************************************
treeRootStruct CreateTree()
{
	treeRootStruct treeRoot;
	treeRoot.root = NULL;
	treeRoot.numberOfNodes = 0;
	
	return treeRoot;
}//end CreateTree()

//**********************************************************************************************************************
// FUNCTION: IsEmpty()
// DESCRIPTION: looks at a BST structure and determines whether it is empty or not
// INPUT PARAMETERS: node of the tree root
// OUTPUT: none
// RETURN VALUE: returns true if binary search tree is empty, false otherwise
//**********************************************************************************************************************
bool IsEmpty(treeRootStruct treeRoot)
{
	bool isEmpty;			//answers the question, "Is the tree empty?"
	if(treeRoot.root == NULL)
	{isEmpty = true;}
	else
	{isEmpty = false;}
	
	return isEmpty;
}//end IsEmpty()

//**********************************************************************************************************************
// FUNCTION: FindNode()
// DESCRIPTION: //searches for a value within a binary search tree. Passes back a flag indicating if the value was found and a pointer to a node. 
//				If the value was found, the pointer will point to the node containing the value. 
//				If the value was not found, the pointer will point to the last node searched before determining that 
//				the value could not be found (or NULL if the tree was empty).
// INPUT PARAMETERS: root node, number to be found and a dummy node (dummy node will either become the parent node or the node if found).
// OUTPUT: none
// RETURN VALUE: Returns a true/false (found/not founter) bool and pointer to the node (dummy node)
//					or the parent of where the node would be if it was in the tree
//**********************************************************************************************************************
bool FindNode(treeNode * &nodeFinder, treeRootStruct treeRoot, int numberToFind)
{
	nodeFinder = treeRoot.root;
	bool found = false,							//number has/has not been found (yet)
		 notInTree = false;						//number is determined to not be in tree (search stops when true)
	
	if(IsEmpty(treeRoot))//tree is empty
	{notInTree = true;}
		
	while(found != true && notInTree != true)
	{
		
		if(nodeFinder->nodeNumber == numberToFind)
		{found = true;}
		else if(nodeFinder->nodeNumber > numberToFind)
		{
			if(nodeFinder->leftPointer !=NULL)
			{nodeFinder=nodeFinder->leftPointer;}
			else
			{notInTree = true;}
		}
		else if(nodeFinder->nodeNumber < numberToFind)
		{
			if(nodeFinder->rightPointer !=NULL)
			{nodeFinder=nodeFinder->rightPointer;}
			else
			{notInTree = true;}
		}
		else
		{cout << "\nError in FindNode()!\n";}
	}	
	
	return found;
}//end FindNode()

//**********************************************************************************************************************
// FUNCTION: CreateNode()
// DESCRIPTION: allocate and fills new node. Passes back pointer to new node, or NULL if node could not be allocated.
// INPUT PARAMETERS: number for which a node needs to be created
// OUTPUT: none
// RETURN VALUE: returns the created node with initialized pointers to NULL, or NULL is the node could not be created.
//**********************************************************************************************************************
treeNode* CreateNode(int numberToPlaceIntoTree)
{
	treeNode * nodeCreated = new(nothrow) treeNode; 		//the 'nothrow' won't throw an exception if it fails, but will instead return NULL
	if(nodeCreated == NULL)
	{cout << "\nError in dynamic memory allocation in CreateNode().\n";}
	else
	{
		nodeCreated->nodeNumber = numberToPlaceIntoTree;
		nodeCreated->leftPointer = NULL;
		nodeCreated->rightPointer = NULL;
	}
	
	return nodeCreated;	
}//end CreateNode()

//**********************************************************************************************************************
// FUNCTION: InsertNode()
// DESCRIPTION: inserts a new node into the correct location within a binary search tree.
// INPUT PARAMETERS: created node with NULL pointer and a number.  This is the node that will be inserted into the BSt
// OUTPUT: none
// RETURN VALUE: none
//**********************************************************************************************************************
void InsertNode(treeNode* nodeToInsert, treeRootStruct &treeRoot)
{
	treeNode * tempNodePointer = treeRoot.root;
	bool inserted = false;
	
	if(IsEmpty(treeRoot))
	{
		treeRoot.root = nodeToInsert;
		inserted = true;
		treeRoot.numberOfNodes++;
	}
	
	while(inserted == false)
	{
		if(nodeToInsert->nodeNumber < tempNodePointer->nodeNumber)
		{		
			if(tempNodePointer -> leftPointer == NULL)		//insert the node at this location
			{
				tempNodePointer -> leftPointer = nodeToInsert;
				inserted = true;
				treeRoot.numberOfNodes++;
				//cout << "L" << nodeToInsert->nodeNumber << endl;
			}
			else
			{
				tempNodePointer = tempNodePointer->leftPointer;
				//cout << "L";
			}	
		}
		else if(nodeToInsert->nodeNumber > tempNodePointer->nodeNumber)
		{
			if(tempNodePointer -> rightPointer == NULL)		//insert the node at this location
			{
				tempNodePointer -> rightPointer = nodeToInsert;
				inserted = true;
				treeRoot.numberOfNodes++;
				//cout << "R" << nodeToInsert->nodeNumber << endl;
			}
			else
			{
				tempNodePointer = tempNodePointer->rightPointer;
				//cout << "R";
			}
		}
		else//must be equal which is not allowed
		{
			cout << "\nError in InsertNode() due to equal numbers. Check FindNode()!\n";
			inserted = true;
		}
				
	}//end while(inserted == false)
	
	return;
}//end InsertNode()

//**********************************************************************************************************************
// FUNCTION: DeleteNode()
// DESCRIPTION: deletes a node from the binary search tree.
// INPUT PARAMETERS: number to delete (already determined that it is in the tree, node needs to be found), tree root node
// OUTPUT: none
// RETURN VALUE: none
//**********************************************************************************************************************
void DeleteNode(int numberToDelete, treeRootStruct &treeRoot)
{
	treeNode * tempNodePointer = treeRoot.root;
	treeNode * tempNodePointerParent = NULL;
	treeNode * childLeaf = NULL;												//this is the leaf that will replace a two-child deleted node
	treeNode * childLeafParent = NULL;
	
	if(tempNodePointer->nodeNumber == numberToDelete && treeRoot.numberOfNodes == 1)//tree has only one node and after delete is empty
	{treeRoot.root = NULL;}
	else if(tempNodePointer->nodeNumber == numberToDelete)						//special case of deleting the root of the tree
	{	
		if(tempNodePointer->leftPointer == NULL)
		{treeRoot.root = tempNodePointer->rightPointer;}
		else if(tempNodePointer->rightPointer == NULL)
		{treeRoot.root = tempNodePointer->leftPointer;}
		else																	//find the rightmost child on the left leg... it's the new root
		{
			childLeaf = tempNodePointer->leftPointer;
			while(childLeaf->rightPointer !=NULL)
			{
				childLeafParent = childLeaf;
				childLeaf = childLeaf->rightPointer;
			}
			childLeafParent->rightPointer = NULL;
			childLeafParent->leftPointer = childLeaf->leftPointer;
			childLeaf->leftPointer = treeRoot.root->leftPointer;
			childLeaf->rightPointer = treeRoot.root->rightPointer;
			treeRoot.root = childLeaf;
		}
	}
	else																		//node to delete is not the root node						
	{
		while(tempNodePointer->nodeNumber != numberToDelete)
		{
			tempNodePointerParent = tempNodePointer;
			if(tempNodePointer->nodeNumber > numberToDelete)
			{tempNodePointer = tempNodePointer->leftPointer;}
			else
			{tempNodePointer = tempNodePointer->rightPointer;}
		}

		if(tempNodePointer->leftPointer == NULL && tempNodePointer->rightPointer == NULL)				//node to delete is a leaf node
		{
			if(tempNodePointerParent->leftPointer !=NULL)
			{
				if(tempNodePointerParent->leftPointer->nodeNumber == tempNodePointer->nodeNumber)		//leaf is a left leaf
				{tempNodePointerParent->leftPointer = NULL;}
			}
			
			if(tempNodePointerParent->rightPointer != NULL)
			{
				if(tempNodePointerParent->rightPointer->nodeNumber == tempNodePointer->nodeNumber)		//leaf is a right leaf
				{tempNodePointerParent->rightPointer = NULL;}
			}
		}
		else if(tempNodePointer->leftPointer == NULL) 													//if node to delete has only one child (right pointer)
		{	
			if(tempNodePointerParent->rightPointer !=NULL)
			{
				if(tempNodePointerParent->rightPointer->nodeNumber == tempNodePointer->nodeNumber)		//child belongs to parent right leg
				{tempNodePointerParent->rightPointer = tempNodePointer->rightPointer;}
			}
			
			if(tempNodePointerParent->leftPointer !=NULL)
			{
				if(tempNodePointerParent->leftPointer->nodeNumber == tempNodePointer->nodeNumber)		//child belongs to parent left leg
				{tempNodePointerParent->leftPointer = tempNodePointer->rightPointer;}
			}
		}
		else if(tempNodePointer->rightPointer == NULL)													//if node to delete has only one child (left pointer)
		{
			if(tempNodePointerParent->rightPointer->nodeNumber == tempNodePointer->nodeNumber)			//child belongs to parent right leg
			{tempNodePointerParent->rightPointer = tempNodePointer->leftPointer;}
			else if(tempNodePointerParent->leftPointer->nodeNumber == tempNodePointer->nodeNumber)		//child belongs to parent left leg
			{tempNodePointerParent->leftPointer = tempNodePointer->leftPointer;}
			else
			{cout << "\nError in DeletePointer(), one child (right leg=NULL) node section!\n";}		
		}
		else if(tempNodePointer->rightPointer != NULL && tempNodePointer->leftPointer != NULL)			//node to delete has two children
		{
			if(tempNodePointerParent->leftPointer != NULL)
			{
				if(tempNodePointerParent->leftPointer->nodeNumber == tempNodePointer->nodeNumber)			//child belongs to parent's a left leg
				{//since it's a left leg child, need LARGEST leaf to replace
					childLeaf = tempNodePointer->rightPointer;
					childLeafParent = tempNodePointer;
				
					while(childLeaf->rightPointer != NULL)
					{//when childLeaf->rightPointer == NULL, then that is the largest leaf
						childLeafParent=childLeaf;
						childLeaf = childLeaf->rightPointer;
					}
	
					tempNodePointerParent->leftPointer = childLeafParent->rightPointer;
					childLeafParent->rightPointer = childLeaf->leftPointer;								//child leaf parent is ready to live without child
				
					childLeaf->rightPointer = tempNodePointer->rightPointer;
					childLeaf->leftPointer = tempNodePointer->leftPointer;
				}
			}
			else if(tempNodePointerParent->rightPointer->nodeNumber == tempNodePointer->nodeNumber)		//child belongs to parent right leg
			{//since it's a right leg child, need SMALLEST leaf to replace
				childLeaf = tempNodePointer->leftPointer;
				
				while(childLeaf->leftPointer != NULL)
				{//when childLeaf->leftPointer == NULL, then that is the smallest leaf
					childLeafParent=childLeaf;
					childLeaf = childLeaf->leftPointer;	
				}
				
				childLeafParent->leftPointer = childLeaf->rightPointer;								//child leaf parent is ready to live without child
				
				tempNodePointerParent->leftPointer = childLeaf;
				childLeaf->rightPointer = tempNodePointer->rightPointer;
				childLeaf->leftPointer = tempNodePointer->leftPointer;
			}
			else
			{cout << "\nError in DeletePointer(), two children section!\n";}		
		}	
		else
		{cout << "\nError in DeletePointer(), somewhere children pointers are not assigned!\n";}		
	}

	treeRoot.numberOfNodes--;
	delete tempNodePointer;
	
	return;
}//end DeleteNode()

//**********************************************************************************************************************
// FUNCTION: UserMenuToInputTextFileName()
// DESCRIPTION: menu for user to imput string file. 
// INPUT PARAMETERS: blank string for the name of the inputTextFile name.  Does error checking to see if file exists before return
// OUTPUT: none
// RETURN VALUE: none
//**********************************************************************************************************************
void UserMenuToInputTextFileName(string & inputTextFile)
{
	ifstream infile;
	
	cout << "\nWelcome to the BST builder.\nPlease enter the name of a text input file: ";
	cin >> inputTextFile;
  
	infile.open(inputTextFile.c_str());
	
	
	while(!infile.good())
   	{
   	cout << endl << "\nFile " << inputTextFile << " does not exist.  Please enter the name of a text input file: ";
   	cin >> inputTextFile;
   	infile.open(inputTextFile.c_str());
   	}
   	
   	//cout << endl << inputTextFile  << endl << infile.rdbuf() << endl;
   	infile.close();
   	return;
}//end UserMenuToInputTextFileName()

//**********************************************************************************************************************
// FUNCTION: ReadTextFile()
// DESCRIPTION: reads the input text file, calls the relevant functions to build the BST
// INPUT PARAMETERS: string with the name of the text file and root node pointer
// OUTPUT: none
// RETURN VALUE: memory allocation validation int.  Zero means all good in the hood
//**********************************************************************************************************************
int ReadTextFile(string inputTextFile, treeRootStruct& treeRoot)
{
	int memoryAllocationValidation = 0;
	treeNode * newNode;
	treeNode * newNodeParent = NULL;
	bool numberFound;
	int numberFromInput;
	
	ifstream infile;
	infile.open(inputTextFile.c_str());
	
	//cout << endl << inputTextFile  << endl << infile.rdbuf() << endl;
	cout << "\nReading Input\n\n";
	
	while(memoryAllocationValidation == 0 && infile >> numberFromInput)	//works even if input fie has whitespace before EOF
	{
		newNode = CreateNode(numberFromInput);
		if(newNode == NULL)
		{memoryAllocationValidation = -1;}
		else
		{
			numberFound = FindNode(newNodeParent, treeRoot, numberFromInput);
			if(numberFound == false)														//insert into tree, node doesn't already exist
			{InsertNode(newNode, treeRoot);}
			else
			{
				cout << "\t" << numberFromInput << " is a duplicate and will be ignored.\n";
				delete newNode;
			}
		}
	}
	
	if(memoryAllocationValidation == -1)
	{cout << "\nMemory allocation error.  Cannot add further integers.\n";}
	
	infile.close();	
	return memoryAllocationValidation;
}//end ReadTextFile()

//**********************************************************************************************************************
// FUNCTION: FreeNodes()
// DESCRIPTION: recursively de-allocates all dynamic memory allocated to nodes in the binary search tree.
// INPUT PARAMETERS: node that points to the root node
// OUTPUT: none
// RETURN VALUE: none
//**********************************************************************************************************************
void FreeNodes(treeNode* nodeWalker)
{
	if(nodeWalker->leftPointer == NULL && nodeWalker->rightPointer == NULL)		//is a leaf node
	{delete nodeWalker;}
	else if(nodeWalker->leftPointer != NULL && nodeWalker->rightPointer != NULL)//has two children
	{
		treeNode* nodeWalkerLeftChild = nodeWalker->leftPointer;
		FreeNodes(nodeWalkerLeftChild);
		nodeWalkerLeftChild = NULL;
		
		treeNode* nodeWalkerRightChild = nodeWalker->rightPointer;
		FreeNodes(nodeWalkerRightChild);
		nodeWalkerRightChild = NULL;
		
		FreeNodes(nodeWalker);
	}
	else if(nodeWalker->leftPointer != NULL && nodeWalker->rightPointer == NULL)//has only right child
	{
		treeNode* nodeWalkerLeftChild = nodeWalker->leftPointer;
		FreeNodes(nodeWalkerLeftChild);
		nodeWalkerLeftChild = NULL;
		
		FreeNodes(nodeWalker);
	}
	else if(nodeWalker->leftPointer == NULL && nodeWalker->rightPointer != NULL)//has only left child
	{
		treeNode* nodeWalkerRightChild = nodeWalker->rightPointer;
		FreeNodes(nodeWalkerRightChild);
		nodeWalkerRightChild = NULL;
		
		FreeNodes(nodeWalker);
	}
	
	return;
}//end FreeNodes()

//**********************************************************************************************************************
// FUNCTION: DestroyTree()
// DESCRIPTION: Calls FreeNodes() to delete all the tree nodes and then destroys the root pointers 
// INPUT PARAMETERS: pointer to the root node
// OUTPUT: none
// RETURN VALUE: none
//**********************************************************************************************************************
void DestroyTree(treeRootStruct &treeRoot)// � de-allocates all dynamic memory allocated for the binary search tree.
{
	treeNode* nodeWalker = treeRoot.root;
	FreeNodes(nodeWalker);
	treeRoot.numberOfNodes = 0;
	treeRoot.root = NULL;
	return;
}//end DestroyTree()

//**********************************************************************************************************************
// FUNCTION: InOrderDisplay()
// DESCRIPTION: traverses the BST and outputs the numbers in order (lowest to highest)
// INPUT PARAMETERS: nodeWalker node pointer to tree root, and counter for carriage return for output
// OUTPUT: outputs all the BST numbers to screen in order
// RETURN VALUE: none
//**********************************************************************************************************************
void InOrderDisplay(treeNode* nodeWalker, int& i)// � neatly displays all integers in the list in sorted order, using a recursive, in-order traversal.
{
	//using Depth First traversal, will walk from left (to the leaves and back) to right of the tree
	
	if(nodeWalker->leftPointer != NULL)
	{
		
		InOrderDisplay(nodeWalker->leftPointer, i);
	}
	
	i++;
	cout << setw(6) << right << nodeWalker->nodeNumber;
	if(i%10==0)
	{cout << endl;}
		
	if(nodeWalker->rightPointer != NULL)
	{
		InOrderDisplay(nodeWalker->rightPointer, i);
	}
		
	return;		 
}//end InOrderDisplay()

//**********************************************************************************************************************
// FUNCTION: InOrderDisplayCall()
// DESCRIPTION: initializes nodeWalker and an int for i%10==0 endl for good output, then calls the recursive function InOrderDisplay()
// INPUT PARAMETERS: pointer to root node
// OUTPUT: none
// RETURN VALUE: none
//**********************************************************************************************************************
void InOrderDisplayCall(treeRootStruct treeRoot)
{
	treeNode* nodeWalker = treeRoot.root;
	int i = 0;															// if(i%10==0, then cout << endl
	
	//cout << "\nNumber of nodes is " << treeRoot.numberOfNodes << endl;
	
	if(IsEmpty(treeRoot))
	{cout << "\nBinary search tree is empty.\n";}
	else
	{
		cout << "\nValues displayed in the entire binary search tree are:\n";
		InOrderDisplay(nodeWalker, i);
	}
	
	return;
}//end InOrderDisplayCall()

//**********************************************************************************************************************
// FUNCTION: UserMenu2()
// DESCRIPTION: offers a menu of options to the user and calls functions until exit
// INPUT PARAMETERS: root pointer
// OUTPUT: menu to user 
// RETURN VALUE: none
//**********************************************************************************************************************
void UserMenu2(treeRootStruct treeRoot)
{
	char choice = 'a';
	int number, 
		i=0;
	bool numberFound;
	treeNode* userNode = NULL;
	treeRootStruct userRoot = CreateTree();
	
	cout << "\nThe total number of integers in the BST";
	if(treeRoot.numberOfNodes == 0)
	{cout << " is " ;}
	else
	{cout << " are ";}
	cout << treeRoot.numberOfNodes << endl;
	
	while(choice != 'E' && choice != 'X')
	{
	
		cout << "\n\nEnter a choice from the following menu:\n"
			 << "\t[S]how all integers in the binary search tree.\n"
			 << "\t[A]dd an integer to the tree.\n"
		   	 << "\t[D]elete an integer from the tree.\n"
			 << "\t[F]ind an integer within the tree, and display its subtree.\n"
			 << "\t[E][x]it the program.\n";
		cin >> choice;
		choice = toupper(choice);
		if(choice != 'S' && choice != 'A' && choice != 'D' && choice != 'F' && choice != 'E' && choice != 'X')
		{cout << "\nThat is not a valid menu option.\n";}	
		
		switch(choice)
		{
			case 'S':
				InOrderDisplayCall(treeRoot);
				break;
			case 'A':
				cout << "Enter integer to add to tree: ";
				cin >> number;
				numberFound = FindNode(userNode, treeRoot, number); 
				if(numberFound == false)
				{
					userNode = CreateNode(number);
					if(userNode != NULL)
					{InsertNode(userNode, treeRoot);}
				}
				else
				{cout << "\t" << number << " is a duplicate and will be ignored.\n";}	//dynamic memory allocation will only happen on non-duplicates
				
				if(userNode == NULL && numberFound == false)
				{cout << "\nMemory allocation fail. Unable to add new number to the tree.\n";}
				
				if(userNode != NULL && numberFound == false)
				{cout << "\t" << number << " is has been added to the tree.\n";}
				break;
			case 'D':
				cout << "Enter integer to delete from tree: ";
				cin >> number;
				numberFound = FindNode(userNode, treeRoot, number); 
				if(numberFound == false)
				{cout << endl << number << " is not in tree.  Unable to delete.\n";}
				else
				{DeleteNode(number, treeRoot);}
				break;
			case 'F':
				cout << "Enter integer whose subtree will be displayed: ";
				cin >> number;
				numberFound = FindNode(userNode, treeRoot, number); 
				if(numberFound == false)
				{cout << endl << number << " is not in tree.  Unable to display subtree.\n";}
				else
				{
					cout << "\nValues stored in the subtree with root " << number << " are:\n";
					InOrderDisplay(userNode, i);
				}
				break;
			case 'E':
				break;
			case 'X':
				break;
			default:
				break;
		}//end switch(choice)
	}//end while(not exit)
	
	return;
}//end UserMenu2()


//**********************************************************************************************************************
// FUNCTION: MostPlayedGame()
// DESCRIPTION: traverses the tree and counts how much time is spent playing each game.  Game with most hours spent is returned
// INPUT PARAMETERS: root pointer
// OUTPUT: none
// RETURN VALUE: none
//**********************************************************************************************************************

void MostPlayedGame(treeRootStruct treeRoot, string gameWithMostTime, int  &timeSpentPlayingGame)
{
	string gameNames [treeRoot.numberOfNodes * 5] = {"000"}; //ordered array of strings that will remain mostly empty strings
	int gameTimes[treeRoot.numberOfNode * 5] = {-1};
	treeNode * tempNodePointer = treeRoot.root;				//this pointer traverses the tree and builds the games[] array
	int stringCompare;  
	string tempString;									//this int will be -1, 0, or 1 depending on how the strings compare alphabetically
	
	//traverses entire tree, counting games
	for(int i=0; i<5; i++)
	{
		if(tempNodePointer.gameNameInTree[i] == "000")
		{
			if(tempNodePointer.gamesTimeInTree[i] !=-1)			//check for error
			{cout << "\nError in gameNames/gameTimes matchup.  A 000 game should have -1 time!\n";}

			i=5;
		}
		else//since gameName != "000", then a name exists in this slot and it must be inserted into the gameNames[] array.  
		{
			//using alphabetical insertion
			for(int j=0; j<treeRoot.numberOfNodes*5; j++)
			{
				stringCompare = strcmp(tempNodePointer.gameNameInTree[i], gameNames[j])
				
				if(stringCompare == 0) //names Match
				{
					gameTimes[j] += tempNodePointer.gameTimeInTree[i];
					j = numberOfNodes*5+1;//exit loop
					i = 5;//exit out loop
				}
				else if(stringCompare == -1)//insert new game name IN FRONT OF current game.... need to shift arrays to the right
				{
					for(int k=treeRoot.numberOfNodes*5-1; k = j ; k--)
					{
						if(gameNames[k] != "000")
						{
							gameTimes[k+1] = gameTimes[k];
							gameNames[k+1] = gameNames[k];			
						}
					}//completed array shift loops
					
					gameNames[j] = tempNodePointer.gameNameInTree[i];
					gameTimes[j] = tempnodePointer.gameTimeInTree[i];
				}
				//else - stringCompare == 1, then move to the next name in the array and compare again
			}
		}//end for loop for int j < numberOfNodes*5
	}//end for loop for int i < 5
	//at this point, this node has been read and we need to move the pointer to the next node in the tree
	
	
	if(nodeWalker->leftPointer != NULL)
	{
		
		InOrderDisplay(nodeWalker->leftPointer, i);
	}
	
	i++;
	cout << setw(6) << right << nodeWalker->nodeNumber;
	if(i%10==0)
	{cout << endl;}
		
	if(nodeWalker->rightPointer != NULL)
	{
		InOrderDisplay(nodeWalker->rightPointer, i);
	}
	
	
	
	
	
	return;
}

