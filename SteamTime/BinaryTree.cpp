#include "BinaryTree.h"
#include "Common.h"

/************************************************************************
* FUNCTION: IsEmpty()
* DESCRIPTION: determines whether root node is empty or not
* INPUT PARAMETERS: none
* OUTPUT: none
* RETURN VALUE: returns true if root is empty, false otherwise
*************************************************************************/
bool BinaryTree::isEmpty()
{
	if (root == NULL)
		return true;
	else
		return false;
}

int BinaryTree::getSize()
{
	return numberOfNodes;
}

/************************************************************************
* FUNCTION: FindNode()
* DESCRIPTION: //searches for a value within a binary search tree. Passes back a flag 
* indicating if the value was found and a pointer to a node. 
*	If the value was found, the pointer will point to the node containing the value. 
*	If the value was not found, the pointer will point to the last node searched before 
*	determining that the value could not be found (or NULL if the tree was empty).
* INPUT PARAMETERS: treeNode->user->id_64 to be found
* OUTPUT: none
* RETURN VALUE: Returns a true/false (found/not found) boolean
*************************************************************************/
bool BinaryTree::findNode(unsigned long long numberToFind)
{
	treeNode* nodeFinder = root;
	bool found = false,							//number has/has not been found (yet)
		notInTree = false;						//number is determined to not be in tree (search stops when true)

	if (isEmpty())//tree is empty
		notInTree = true;

	while (!found && !notInTree)
	{

		if (nodeFinder->user->id_64 == numberToFind)
			found = true;
		else if (nodeFinder->user->id_64 > numberToFind)
		{
			if (nodeFinder->leftPointer != NULL)
				nodeFinder = nodeFinder->leftPointer;
			else
				notInTree = true;
		}
		else if (nodeFinder->user->id_64 < numberToFind)
		{
			if (nodeFinder->rightPointer != NULL)
				nodeFinder = nodeFinder->rightPointer;
			else
				notInTree = true;
		}
		else
			cout << "\nError in FindNode()!\n";
	}

	return found;
}

/************************************************************************
* FUNCTION: CreateNode()
* DESCRIPTION: allocate and fills new node. Passes back pointer to new 
* node, or NULL if node could not be allocated.
* INPUT PARAMETERS: New node's attributes
* OUTPUT: none
* RETURN VALUE: returns the created node with initialized pointers to 
* NULL, or NULL is the node could not be created.
*************************************************************************/
treeNode * BinaryTree::createNode(User* u, GameList* topFive)
{
	treeNode * nodeCreated = new(nothrow) treeNode; 		//the 'nothrow' won't throw an exception if it fails, but will instead return NULL
	if (nodeCreated == NULL)
	{
		cout << "\nError in dynamic memory allocation in CreateNode().\n";
	}
	else
	{
		//create treeNode member attribute to store total overall time per player
		nodeCreated->user = u;
		nodeCreated->top5 = topFive;
		nodeCreated->leftPointer = NULL;
		nodeCreated->rightPointer = NULL;
	}

	return nodeCreated;
}
/************************************************************************
* FUNCTION: InsertNode()
* DESCRIPTION: inserts a new node into the correct location within a binary search tree.
* INPUT PARAMETERS: new node's attributes
* OUTPUT: none
* RETURN VALUE: true if successful, otherwise false if duplicate exists
*************************************************************************/
bool BinaryTree::insertNode(User* u, GameList* gList)
{
	bool inserted = false;
	//do a check for duplicates first
	if (!findNode(u->id_64)) {
		treeNode * tempNodePointer = createNode(u, gList);
		//insert memory error handling here
		if (isEmpty())
		{
			root = tempNodePointer;
			inserted = true;
			numberOfNodes++;
		}
		else {
			treeNode * curr = root;
			while (!inserted)
			{
				if (curr->user->id_64 < tempNodePointer->user->id_64)
				{
					if (curr->leftPointer == NULL)		//insert the node at this location
					{
						curr->leftPointer = tempNodePointer;
						inserted = true;
						numberOfNodes++;
						//cout << "L" << nodeToInsert->user->id_64 << endl;
					}
					else
					{
						curr = curr->leftPointer;
						//cout << "L";
					}
				}
				else if (curr->user->id_64 > tempNodePointer->user->id_64)
				{
					if (curr->rightPointer == NULL)		//insert the node at this location
					{
						curr->rightPointer = tempNodePointer;
						inserted = true;
						numberOfNodes++;
						//cout << "R" << nodeToInsert->user->id_64 << endl;
					}
					else
					{
						curr = curr->rightPointer;
						//cout << "R";
					}
				}
			}//end while(inserted == false)
		}//end else not empty
	}//end if not a duplicate
	return inserted;
}

/************************************************************************
* FUNCTION: FreeNodes()
* DESCRIPTION: recursively de-allocates all dynamic memory allocated to nodes in the 
* binary search tree.
* INPUT PARAMETERS: node that points to the root node
* OUTPUT: none
* RETURN VALUE: none
*************************************************************************/
void BinaryTree::freeNodes(treeNode * nodeWalker)
{
	if (nodeWalker->leftPointer == NULL && nodeWalker->rightPointer == NULL)		//is a leaf node
	{
		delete nodeWalker;
	}
	else if (nodeWalker->leftPointer != NULL && nodeWalker->rightPointer != NULL)//has two children
	{
		treeNode* nodeWalkerLeftChild = nodeWalker->leftPointer;
		freeNodes(nodeWalkerLeftChild);
		nodeWalkerLeftChild = NULL;

		treeNode* nodeWalkerRightChild = nodeWalker->rightPointer;
		freeNodes(nodeWalkerRightChild);
		nodeWalkerRightChild = NULL;

		freeNodes(nodeWalker);
	}
	else if (nodeWalker->leftPointer != NULL && nodeWalker->rightPointer == NULL)//has only right child
	{
		treeNode* nodeWalkerLeftChild = nodeWalker->leftPointer;
		freeNodes(nodeWalkerLeftChild);
		nodeWalkerLeftChild = NULL;

		freeNodes(nodeWalker);
	}
	else if (nodeWalker->leftPointer == NULL && nodeWalker->rightPointer != NULL)//has only left child
	{
		treeNode* nodeWalkerRightChild = nodeWalker->rightPointer;
		freeNodes(nodeWalkerRightChild);
		nodeWalkerRightChild = NULL;

		freeNodes(nodeWalker);
	}

	return;
}//end FreeNodes()

/************************************************************************
* FUNCTION: BinaryTree()
* DESCRIPTION: constructor for binary search tree structure, and
* initialize the root pointer to NULL and the Node count to 0
* INPUT PARAMETERS: N/A
* OUTPUT: none
* RETURN VALUE: N/A
*************************************************************************/
BinaryTree::BinaryTree()
{
	numberOfNodes = 0;
	root = NULL;
	return;
}//end BinaryTree() constructor

/************************************************************************
* FUNCTION: DestroyTree()
* DESCRIPTION: Calls FreeNodes() to delete all the tree nodes and then destroys the root 
* pointers 
* INPUT PARAMETERS: N/A
* OUTPUT: none
* RETURN VALUE: N/A
*************************************************************************/
BinaryTree::~BinaryTree()
{
	freeNodes(root);
	numberOfNodes = 0;
	root = NULL;
	return;
}//end ~BinaryTree() destructor

/************************************************************************
* FUNCTION: InOrderDisplay()
* DESCRIPTION: traverses the BST and outputs the numbers in order (lowest to highest)
* INPUT PARAMETERS: nodeWalker node pointer to tree root, and counter for carriage return 
* for output
* OUTPUT: outputs all the BST numbers to screen in order
* RETURN VALUE: none
* IMPLEMENTED BY: Jerome Latona
*************************************************************************/
void BinaryTree::inOrderDisplay(treeNode * nodeWalker, int & i)
{
	//using Depth First traversal, will walk from left (to the leaves and back) to right of the tree

	if (nodeWalker->leftPointer != NULL)
		inOrderDisplay(nodeWalker->leftPointer, i);

	i++;
	cout << setw(6) << right << nodeWalker->user->id_64;
	if (i % 10 == 0)
		cout << endl;

	if (nodeWalker->rightPointer != NULL)
		inOrderDisplay(nodeWalker->rightPointer, i);

	return;
}//end InOrderDisplay()

/************************************************************************
* FUNCTION: InOrderDisplayCall()
* DESCRIPTION: initializes nodeWalker and an int for i%10==0 endl for good output, then 
* calls the recursive function InOrderDisplay()
* INPUT PARAMETERS: none
* OUTPUT: none
* RETURN VALUE: none
* IMPLEMENTED BY: Jerome Latona
*************************************************************************/
void BinaryTree::inOrderDisplayCall()
{
	treeNode* nodeWalker = root;
	int i = 0;				// if(i%10==0, then cout << endl

							//cout << "\nNumber of nodes is " << treeRoot.numberOfNodes << endl;

	if (isEmpty())
	{
		cout << "\nBinary search tree is empty.\n";
	}
	else
	{
		cout << "\nValues displayed in the entire binary search tree are:\n";
		inOrderDisplay(nodeWalker, i);
	}

	return;

}//end InOrderDisplay()

/************************************************************************
* FUNCTION: MostPlayedGame()
* DESCRIPTION: traverses the tree and counts how much time is spent playing each game.  
* Game with most hours spent is returned
* INPUT PARAMETERS: inherits root (none)
* OUTPUT: none
* RETURN VALUE: GameList * which contains 5 games and 5 playtimes
* IMPLEMENTED BY: Jerome Latona
*************************************************************************/
GameList* BinaryTree::mostPlayedGame()
{
	LinkListNode* gamesDynamicListFront = NULL;		//Always points to the first element of the list
	LinkListNode* temp = NULL;
	if (root == NULL)
	{cout << "\nTree is empty.  No list to build!\n";}
	GameList* resultToReturn = new GameList;					//contains garbage for now
	treeNode* treeWalker = root;
	int linkedListSize = 0, max = MAX_TREE_SIZE*5;//max will be reduced when the list is built, but this is the absolute max

		
	if (!isEmpty())						
	{traverseTree(treeWalker, gamesDynamicListFront, linkedListSize);}	//traverses entire tree, counting games

	if (gamesDynamicListFront == NULL)
		cout << "\ngamesDYN is NULL here!\n";
	
	ListNode* unsortedGameList = new ListNode[linkedListSize];

	temp = gamesDynamicListFront;

	cout << "\nTotal games & times (minutes):\n\n";
	for (int i = 0; i < linkedListSize; i++)
	{
		unsortedGameList[i].appID = temp->appID;
		unsortedGameList[i].name = temp->name;
		unsortedGameList[i].playTime = temp->playTime;
		temp = temp->next;
		cout << unsortedGameList[i].name << " " << unsortedGameList[i].playTime << endl;
	}

	mergeSortCall(unsortedGameList, linkedListSize);
	//unsortedGameList is now a list sorted based on playTime

	cout << "\n\nTotal games & sorted times (minutes):\n\n";
	for (int i = 0; i < linkedListSize; i++)
	{cout << unsortedGameList[i].name << " " << unsortedGameList[i].playTime << endl;}


	if(linkedListSize > MAX_SIZE)
	{max = MAX_SIZE;}
	else
	{max = linkedListSize;}

	for (int i = 0; i < max; i++)
	{
		resultToReturn->list[i].appID = unsortedGameList[linkedListSize-1-i].appID;
		resultToReturn->list[i].name = unsortedGameList[linkedListSize - 1 - i].name;
		resultToReturn->list[i].playTime = unsortedGameList[linkedListSize - 1 - i].playTime;
	}

	delete[] unsortedGameList;
	return resultToReturn;
}//end MostPlayedGame()

/************************************************************************
* FUNCTION: TraverseTree()
* DESCRIPTION: recursively traverses the entire tree, building the linked list of games as it 
*		walks the tree
* INPUT PARAMETERS: treeWalker pointer, and gamesDynamicList
* OUTPUT: none
* RETURN VALUE: memory allocation validation int.  Zero means all good in the hood
* IMPLEMENTED BY: Jerome Latona
*************************************************************************/
void BinaryTree::traverseTree(treeNode * treeWalker, LinkListNode*& gamesDynamicListFront, int & linkedListSize)
{//traverses entire tree LRV... Left, Right, then Value

	if (treeWalker == NULL)//tree is empty
	{cout << "\nTree is empty.  No list to build!\n";}
	
	if (treeWalker->leftPointer != NULL)		//Left first
	{
		//cout << "\nGoing down left leg.";
		traverseTree(treeWalker->leftPointer, gamesDynamicListFront, linkedListSize);
	}

	if (treeWalker->rightPointer != NULL)		//Right second
	{
		//cout << "\nGoing down right leg.";
		traverseTree(treeWalker->rightPointer, gamesDynamicListFront, linkedListSize);
	}
	
	//at this point in the code, you are at a leaf node, or both left and right legs have been traversed
	//LRV .... LR are done, now for V
	LinkListNode* listWalker = gamesDynamicListFront;

	//if(gamesDynamicListFront == NULL)		//List is empty
	//{listWalker = gamesDynamicListFront;}
		
	//Will traverse list & compare/insert by gameApp number ordering
	for (int i = 0; i < MAX_SIZE; i++)
	{
		listWalker = gamesDynamicListFront;

		if (treeWalker->top5->list[i].name == "NULL")//no game in this slot
		{
			i = MAX_SIZE+1;
		}// end the loop because tree node contains no more games
		else
		{
			if (listWalker == NULL)//empty list... time to start the list
			{
				LinkListNode* tempNode = new(nothrow) LinkListNode;
				if (tempNode == NULL)
				{cout << "\nError in dynamic memory allocation in TraverseTree(), with list size " << linkedListSize << "!\n";}
				else
				{
					tempNode->next = NULL;
					tempNode->appID = treeWalker->top5->list[i].appID;
					tempNode->playTime = treeWalker->top5->list[i].playTime;
					tempNode->name = treeWalker->top5->list[i].name;
					listWalker = tempNode;
					linkedListSize++;
					gamesDynamicListFront = tempNode;
					cout << endl << gamesDynamicListFront->appID << " "  
						 << gamesDynamicListFront->name << " has been added to the front of the empty list.";
					listWalker = NULL;
				}
			}//end if() create a new list from an empty list
			else//list is not empty... start walking the list
			{
				if (gamesDynamicListFront->appID > treeWalker->top5->list[i].appID)//edge case insert game at front of list
				{
					LinkListNode* tempNode = new(nothrow) LinkListNode;
					if (tempNode == NULL)
					{cout << "\nError in dynamic memory allocation in TraverseTree(), with list size " << linkedListSize << "!\n";}
					else
					{
						tempNode->next = gamesDynamicListFront;
						tempNode->appID = treeWalker->top5->list[i].appID;
						tempNode->playTime = treeWalker->top5->list[i].playTime;
						tempNode->name = treeWalker->top5->list[i].name;
						linkedListSize++;
						gamesDynamicListFront = tempNode;
						cout << endl << gamesDynamicListFront->appID << " "
							 << gamesDynamicListFront->name << " has been added to the front of the list.";
						listWalker = NULL;
					}
				}
				
				while (listWalker != NULL)
				{
					if (treeWalker->top5->list[i].appID == listWalker->appID)//games match, now add the times
					{
						listWalker->playTime += treeWalker->top5->list[i].playTime;
						listWalker = NULL;
					}
					else if (treeWalker->top5->list[i].appID > listWalker->appID)
					{
						if (listWalker->next != NULL)
						{listWalker = listWalker->next;}
						
						if (treeWalker->top5->list[i].appID == listWalker->appID)//games match, now add the times
						{
							listWalker->playTime += treeWalker->top5->list[i].playTime;
							listWalker = NULL;
						}
						else if(listWalker->next == NULL)//reached end of list, insert new node at end of list
						{
							LinkListNode* tempNode = new(nothrow) LinkListNode;
							if (tempNode == NULL)
							{cout << "\nError in dynamic memory allocation in TraverseTree(), with list size " << linkedListSize << "!\n";}
							else
							{
								listWalker->next = tempNode;
								tempNode->next = NULL;
								tempNode->appID = treeWalker->top5->list[i].appID;
								tempNode->playTime = treeWalker->top5->list[i].playTime;
								tempNode->name = treeWalker->top5->list[i].name;
								cout << endl << tempNode->appID << " "
									 << tempNode->name << " has been added to the end of the list.";
								linkedListSize++;
								listWalker = NULL;
							}
						}
					}
					else if(treeWalker->top5->list[i].appID < listWalker->appID )//insert new node here
					{
						LinkListNode* parent = gamesDynamicListFront;
						while (parent->next->appID < treeWalker->top5->list[i].appID)
						{parent = parent->next;}

						LinkListNode* tempNode = new(nothrow) LinkListNode;
						if (tempNode == NULL)
						{cout << "\nError in dynamic memory allocation in TraverseTree(), with list size " << linkedListSize << "!\n";}
						else
						{
							tempNode->next = listWalker;
							parent->next = tempNode;
							tempNode->appID = treeWalker->top5->list[i].appID;
							tempNode->playTime = treeWalker->top5->list[i].playTime;
							tempNode->name = treeWalker->top5->list[i].name;
							cout << endl << tempNode->appID << " "
								 << tempNode->name << " has been added to the list.";
							linkedListSize++;
							listWalker = NULL;
						}
					}
				}//end while(listWalker->next !=NULL)
			}
		}
	}
	
	return;
}//end TraverseTree()

//**********************************************************************************************************************
// FUNCTION: MergeSortCall()
// DESCRIPTION: Initializes necessary variables and calls MergeSort().  The purpose of initializig these variables
// 					here instead of in MergeSort() is that way they are initialized once instead of multiple times 
//					since MergeSort() is a recursive function, and using function pointers the variables for all of the
//					functions must be the same. 
// INPUT PARAMETERS: one unsorted games list array 
// OUTPUT: none
// RETURN VALUE: sorted array that it receives from completed MergeSort()
// IMPLEMENTED BY: Jerome Latona
//**********************************************************************************************************************

void BinaryTree::mergeSortCall(ListNode *& unsortedGameList, int linkedListSize)
{
	ListNode * sortedGameList = new ListNode[linkedListSize];	//used as a temp array to help with the merge
	int	lowIndex = 0,									//low is the first index of the array, used in MergeSort()
		highIndex =  linkedListSize-1;					//high is the last index of the array, used in MergeSort()

	mergeSort(lowIndex, highIndex, unsortedGameList, sortedGameList);

	delete[] sortedGameList;
	return;
}//end MergeSortCall()

//**********************************************************************************************************************
// FUNCTION: MergeSort()
// DESCRIPTION: MergeSort() together with Merge() sort the inputed games array using the merge sort algorithm
//				MergeSort() halves the array until it is ready to be merged (done by the Merge() function)
// INPUT PARAMETERS: array, as well as ints representing the low and high indexes
// OUTPUT: none
// RETURN VALUE: returns one sorted linked list
// IMPLEMENTED BY: Jerome Latona
//**********************************************************************************************************************

void BinaryTree::mergeSort(int lowIndex, int highIndex, ListNode *& unsortedGameList, ListNode *& sortedGameList)
{
	int midIndex;

	if (lowIndex < highIndex)						//if low == high, then the sort is complete
	{
		midIndex = (highIndex + lowIndex) / 2;
		//start going down the rabbit hole of recursion, cutting the array in half each time

		mergeSort(lowIndex, midIndex, unsortedGameList, sortedGameList);
		mergeSort(midIndex + 1, highIndex, unsortedGameList, sortedGameList);
		//From this point, we're coming up the rabbit hole of recursion, merging each sorted list along the way.
		merge(midIndex, lowIndex, highIndex, unsortedGameList, sortedGameList);
	}

	return;
}//end MergeSort()

 //**********************************************************************************************************************
 // FUNCTION: Merge()
 // DESCRIPTION: MergeSort() together with Merge() sort the inputed array using the merge sort algorithm
 //				Merge() will combine two sorted arrays into one sorted array by looking at the first element of each array
 //					at each step and choosing the smallest one to be put into the new array
 // INPUT PARAMETERS: two arrays that are already sorted
 // OUTPUT: none
 // RETURN VALUE: returns the sorted array
 // IMPLEMENTED BY: Jerome Latona
 //**********************************************************************************************************************
void BinaryTree::merge(int midIndex, int lowIndex, int highIndex, ListNode *& unsortedGameList, ListNode *& sortedGameList)
{
	//need several int counters for the loops
	int i = lowIndex,
		k = lowIndex,
		j = midIndex+1;
		
	while (i <= midIndex && j <= highIndex)
    {
        if (unsortedGameList[i].playTime < unsortedGameList[j].playTime)
        {
            sortedGameList[k] = unsortedGameList[i];
            k++;
            i++;
        }
        else
        {
            sortedGameList[k] = unsortedGameList[j];
            k++;
            j++;
        }
    }
   
    //these two while loops that follow means that one of the two arrays has reached the end, so the other one 
	//needs to be truncated to the end of the sorted tempArray and the written into the random number array
	while (i <= midIndex)	
    {
        sortedGameList[k] = unsortedGameList[i];
        k++;
        i++;
    }
    
	while (j <= highIndex)
    {
        sortedGameList[k] = unsortedGameList[j];
        k++;
        j++;
    }
    
	for (i = lowIndex; i < k; i++)//overwrite the unsortedGameList with the sortedGameList
    {unsortedGameList[i] = sortedGameList[i];}
    
    return;
}//end Merge()
