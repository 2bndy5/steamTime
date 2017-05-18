#include "BinaryTree.h"
#include "Common.h"

/************************************************************************
* FUNCTION: findParent()
* DESCRIPTION: Finds and returns parent node for node with matching
* attribute that is passed. Uses lookahead idea to peek at children 
* INPUT PARAMETERS: treeNode->nodeNumber and pointer to current parent
* OUTPUT: none
* RETURN VALUE: pointer to parent found or NULL if node doesn't exist
*************************************************************************/
treeNode * BinaryTree::findParent(unsigned long long numberToDelete, treeNode * curr)
{
	//first two if and else statements are redundant. Could probably lose them.
	//May need to better define NULL base case for branch end points
	if (curr->leftPointer->nodeNumber == numberToDelete)
		return curr;
	else if (curr->rightPointer->nodeNumber == numberToDelete)
		return curr;
	else if (numberToDelete > curr->nodeNumber && curr->leftPointer != NULL)
		return findParent(numberToDelete, curr->leftPointer);
	else if (numberToDelete < curr->nodeNumber && curr->rightPointer != NULL)
		return findParent(numberToDelete, curr->rightPointer);
	else return NULL;//invalid input: could not find node
}

/************************************************************************
* FUNCTION: IsEmpty()
* DESCRIPTION: determines whether root node is empty or not
* INPUT PARAMETERS: none
* OUTPUT: none
* RETURN VALUE: returns true if root is empty, false otherwise
*************************************************************************/
bool BinaryTree::IsEmpty()
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
* INPUT PARAMETERS: treeNode->nodeNumber to be found
* OUTPUT: none
* RETURN VALUE: Returns a true/false (found/not found) boolean
*************************************************************************/
bool BinaryTree::FindNode(unsigned long long numberToFind)
{
	treeNode* nodeFinder = root;
	bool found = false,							//number has/has not been found (yet)
		notInTree = false;						//number is determined to not be in tree (search stops when true)

	if (IsEmpty())//tree is empty
		notInTree = true;

	while (!found && !notInTree)
	{

		if (nodeFinder->nodeNumber == numberToFind)
			found = true;
		else if (nodeFinder->nodeNumber > numberToFind)
		{
			if (nodeFinder->leftPointer != NULL)
				nodeFinder = nodeFinder->leftPointer;
			else
				notInTree = true;
		}
		else if (nodeFinder->nodeNumber < numberToFind)
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
treeNode * BinaryTree::CreateNode(unsigned long long numberToPlace, string steamID, GameList* topFive)
{
	treeNode * nodeCreated = new(nothrow) treeNode; 		//the 'nothrow' won't throw an exception if it fails, but will instead return NULL
	if (nodeCreated == NULL)
	{
		cout << "\nError in dynamic memory allocation in CreateNode().\n";
	}
	else
	{
		//create treeNode member attribute to store total overall time per player
		nodeCreated->nodeNumber = numberToPlace;
		nodeCreated->steamUser = steamID;
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
bool BinaryTree::InsertNode(unsigned long long id_64, string uName, GameList* gList)
{
	bool inserted = false;
	//do a check for duplicates first
	if (!FindNode(id_64)) {
		treeNode * tempNodePointer = CreateNode(id_64, uName, gList);
		//insert memory error handling here
		if (IsEmpty())
		{
			root = tempNodePointer;
			inserted = true;
			numberOfNodes++;
		}
		else {
			treeNode * curr = root;
			while (!inserted)
			{
				if (curr->nodeNumber < tempNodePointer->nodeNumber)
				{
					if (curr->leftPointer == NULL)		//insert the node at this location
					{
						curr->leftPointer = tempNodePointer;
						inserted = true;
						numberOfNodes++;
						//cout << "L" << nodeToInsert->nodeNumber << endl;
					}
					else
					{
						curr = curr->leftPointer;
						//cout << "L";
					}
				}
				else if (curr->nodeNumber > tempNodePointer->nodeNumber)
				{
					if (curr->rightPointer == NULL)		//insert the node at this location
					{
						curr->rightPointer = tempNodePointer;
						inserted = true;
						numberOfNodes++;
						//cout << "R" << nodeToInsert->nodeNumber << endl;
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
* FUNCTION: InsertNode()
* INPUT: temporary pointer to node overflow from removing said node's 
* parent
* OUTPUT: none
* RETURN VALUE: returns true when done or false if node already exists
* (shouldn't happen as public insertNode() checks for duplicates)
* DESCRIPTION: Private helper function to deleteNode(). This will traverse
* binary tree and insert specified node accordingly
************************************************************************/
bool BinaryTree::InsertNode(treeNode * tempPtr)
{
	if (tempPtr == NULL)
		return true;//we passed an empty child: nothing to do
	treeNode* curr = root;
	bool success = false;
	while (!success)
	{
		if (curr->nodeNumber > tempPtr->nodeNumber)
		{
			if (curr->leftPointer == NULL) {
				curr->leftPointer = tempPtr;
				success = true;
			}
			else
				curr = curr->leftPointer;
		}
		else if (curr->nodeNumber < tempPtr->nodeNumber)
		{
			if (curr->rightPointer == NULL)
			{
				curr->rightPointer = tempPtr;
				success = true;
			}
			else
				curr = curr->rightPointer;
		}
		else
			break;//somehow a duplicate slipped through: node will be lost
	}
	return success;
}
/************************************************************************
* FUNCTION: DeleteNode()
* DESCRIPTION: deletes a node from the binary search tree.
* INPUT PARAMETERS: treeNode->nodeNumber to delete ( checks if node 
* exists via private findParent() )
* OUTPUT: none
* RETURN VALUE: none
*************************************************************************/
void BinaryTree::DeleteNode(unsigned long long numberToDelete)
{
	//find first branch w/ null children and replace into deleted node
	if (root->nodeNumber != numberToDelete) {
		treeNode * Parent = findParent(numberToDelete, root);
		if (Parent != NULL)//NULL means could not find node
		{
			if (numberToDelete > Parent->nodeNumber) {
				treeNode* tempPtr = Parent->leftPointer->rightPointer;
				Parent->leftPointer = Parent->leftPointer->leftPointer;
				bool isinserted = InsertNode(tempPtr);
			}
			else if (numberToDelete < Parent->nodeNumber) {
				treeNode* tempPtr = Parent->rightPointer->leftPointer;
				Parent->rightPointer = Parent->rightPointer->rightPointer;
				bool isinserted = InsertNode(tempPtr);
			}
		}
	}
	else //delete root node and restructure accordingly
	{
		treeNode* tempRoot = root;
		if (root->leftPointer != NULL && root->rightPointer == NULL) {
			root = tempRoot->leftPointer;
			root->rightPointer = tempRoot->leftPointer->rightPointer;
			root->leftPointer = tempRoot->leftPointer->leftPointer;
		}
		else if (root->leftPointer == NULL && root->rightPointer != NULL) {
			root = tempRoot->rightPointer;
			root->rightPointer = tempRoot->rightPointer->rightPointer;
			root->leftPointer = tempRoot->rightPointer->leftPointer;
		}
		else if (root->leftPointer != NULL && root->rightPointer != NULL) {
			//shift root to Left Pointer by defualt
			root = tempRoot->leftPointer;
			root->rightPointer = tempRoot->leftPointer->rightPointer;
			root->leftPointer = tempRoot->leftPointer->leftPointer;
			bool isInserted = InsertNode(tempRoot->rightPointer);
		}
		else //both right and left nodes are NULL
			delete root;
		delete tempRoot;
	}//end else delete root node
	return;
}

/************************************************************************
* FUNCTION: FreeNodes()
* DESCRIPTION: recursively de-allocates all dynamic memory allocated to nodes in the 
* binary search tree.
* INPUT PARAMETERS: node that points to the root node
* OUTPUT: none
* RETURN VALUE: none
*************************************************************************/
void BinaryTree::FreeNodes(treeNode * nodeWalker)
{
	if (nodeWalker->leftPointer == NULL && nodeWalker->rightPointer == NULL)		//is a leaf node
	{
		delete nodeWalker;
	}
	else if (nodeWalker->leftPointer != NULL && nodeWalker->rightPointer != NULL)//has two children
	{
		treeNode* nodeWalkerLeftChild = nodeWalker->leftPointer;
		FreeNodes(nodeWalkerLeftChild);
		nodeWalkerLeftChild = NULL;

		treeNode* nodeWalkerRightChild = nodeWalker->rightPointer;
		FreeNodes(nodeWalkerRightChild);
		nodeWalkerRightChild = NULL;

		FreeNodes(nodeWalker);
	}
	else if (nodeWalker->leftPointer != NULL && nodeWalker->rightPointer == NULL)//has only right child
	{
		treeNode* nodeWalkerLeftChild = nodeWalker->leftPointer;
		FreeNodes(nodeWalkerLeftChild);
		nodeWalkerLeftChild = NULL;

		FreeNodes(nodeWalker);
	}
	else if (nodeWalker->leftPointer == NULL && nodeWalker->rightPointer != NULL)//has only left child
	{
		treeNode* nodeWalkerRightChild = nodeWalker->rightPointer;
		FreeNodes(nodeWalkerRightChild);
		nodeWalkerRightChild = NULL;

		FreeNodes(nodeWalker);
	}

	return;
}

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
}

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
	FreeNodes(root);
	numberOfNodes = 0;
	root = NULL;
	return;
}

/************************************************************************
* FUNCTION: InOrderDisplay()
* DESCRIPTION: traverses the BST and outputs the numbers in order (lowest to highest)
* INPUT PARAMETERS: nodeWalker node pointer to tree root, and counter for carriage return 
* for output
* OUTPUT: outputs all the BST numbers to screen in order
* RETURN VALUE: none
*************************************************************************/
void BinaryTree::InOrderDisplay(treeNode * nodeWalker, int & i)
{
	//using Depth First traversal, will walk from left (to the leaves and back) to right of the tree

	if (nodeWalker->leftPointer != NULL)
		InOrderDisplay(nodeWalker->leftPointer, i);

	i++;
	cout << setw(6) << right << nodeWalker->nodeNumber;
	if (i % 10 == 0)
		cout << endl;

	if (nodeWalker->rightPointer != NULL)
		InOrderDisplay(nodeWalker->rightPointer, i);

	return;
}//end InOrderDisplay()

/************************************************************************
* FUNCTION: InOrderDisplayCall()
* DESCRIPTION: initializes nodeWalker and an int for i%10==0 endl for good output, then 
* calls the recursive function InOrderDisplay()
* INPUT PARAMETERS: none
* OUTPUT: none
* RETURN VALUE: none
*************************************************************************/
void BinaryTree::InOrderDisplayCall()
{
	treeNode* nodeWalker = root;
	int i = 0;				// if(i%10==0, then cout << endl

							//cout << "\nNumber of nodes is " << treeRoot.numberOfNodes << endl;

	if (IsEmpty())
	{
		cout << "\nBinary search tree is empty.\n";
	}
	else
	{
		cout << "\nValues displayed in the entire binary search tree are:\n";
		InOrderDisplay(nodeWalker, i);
	}

	return;

}

/************************************************************************
* FUNCTION: MostPlayedGame()
* DESCRIPTION: traverses the tree and counts how much time is spent playing each game.  
* Game with most hours spent is returned
* INPUT PARAMETERS: inherits root (none)
* OUTPUT: none
* RETURN VALUE: GameList * which contains 5 games and 5 playtimes
*************************************************************************/
GameList* BinaryTree::MostPlayedGame()
{
	LinkListNode* gamesDynamicListFront = NULL;		//Always points to the first element of the list
	LinkListNode* temp = NULL;
	GameList* resultToReturn = NULL;
	treeNode* treeWalker = root;
	int linkedListSize = 0, max;

		
	if (!IsEmpty())						
	{
		TraverseTree(treeWalker, gamesDynamicListFront, linkedListSize);	//traverses entire tree, counting games
	}
	
	ListNode* unsortedGameList = new ListNode[linkedListSize];

	temp = gamesDynamicListFront;
	for (int i = 0; i < linkedListSize; i++)
	{
		unsortedGameList[i].appID = temp->appID;
		unsortedGameList[i].name = temp->name;
		unsortedGameList[i].playTime = temp->playTime;
		temp = temp->next;
		if (temp == NULL && i > linkedListSize - 1)
		{cout << "\nError in the creation of unsortedGameList.  Overflow linked list!\n\n";}
	}

	MergeSortCall(unsortedGameList, linkedListSize);
	//unsortedGameList is now a list sorted based on playTime

	if(linkedListSize > MAX_SIZE)
	{max = MAX_SIZE;}
	else
	{max = linkedListSize;}

	for (int i = 0; i < max; i++)
	{
		resultToReturn[i].list->appID = unsortedGameList[i].appID;
		resultToReturn[i].list->name = unsortedGameList[i].name;
		resultToReturn[i].list->playTime = unsortedGameList[i].playTime;
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
*************************************************************************/
void BinaryTree::TraverseTree(treeNode * treeWalker, LinkListNode* gamesDynamicListFront, int & linkedListSize)
{//traverses entire tree LRV... Left, Right, then Value

	if (treeWalker->leftPointer != NULL)		//Left first
	{TraverseTree(treeWalker->leftPointer, gamesDynamicListFront, ++linkedListSize);}

	if (treeWalker->rightPointer != NULL)		//Right second
	{TraverseTree(treeWalker->rightPointer, gamesDynamicListFront, ++linkedListSize);}
	
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
			i = MAX_SIZE;
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
					//write access violation when listWalker == NULL
					listWalker->next = tempNode;
					tempNode->next = NULL;
					tempNode->appID = treeWalker->top5->list[i].appID;
					tempNode->playTime = treeWalker->top5->list[i].playTime;
					tempNode->name = treeWalker->top5->list[i].name;
				}
			}//end if() create a new list from an empty list
			else//list is not empty... start walking the list
			{
				while (listWalker->next != NULL)
				{
					if (treeWalker->top5->list[i].appID == listWalker->appID)//games match, now add the times
					{
						listWalker->playTime += treeWalker->top5->list[i].playTime;
					}
					else if (listWalker->appID < treeWalker->top5->list[i].appID)
					{
						if (listWalker->next != NULL)
						{
							listWalker = listWalker->next;
						}
						else//reached end of list, insert new node at end of list
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
							}
						}
					}
					else//listWalker->appID is greater than treeWalker.appID, so insert new node here
					{
						LinkListNode* parent = gamesDynamicListFront;
						while (parent->next->appID < treeWalker->top5->list[i].appID)
						{
							parent = parent->next;
						}

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

void BinaryTree::MergeSortCall(ListNode * unsortedGameList, int linkedListSize)
{
	ListNode * sortedGameList = new ListNode[linkedListSize];	//used as a temp array to help with the merge
	int	lowIndex = 0,									//low is the first index of the array, used in MergeSort()
		highIndex =  linkedListSize;					//high is the last index of the array, used in MergeSort()

	MergeSort(lowIndex, highIndex, unsortedGameList, sortedGameList);

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

void BinaryTree::MergeSort(int lowIndex, int highIndex, ListNode * unsortedGameList, ListNode * sortedGameList)
{
	int midIndex;

	if (lowIndex < highIndex)						//if low == high, then the sort is complete
	{
		midIndex = (highIndex + lowIndex) / 2;
		//start going down the rabbit hole of recursion, cutting the array in half each time

		MergeSort(lowIndex, midIndex, unsortedGameList, sortedGameList);
		MergeSort(midIndex + 1, highIndex, unsortedGameList, sortedGameList);
		//From this point, we're coming up the rabbit hole of recursion, merging each sorted list along the way.
		Merge(midIndex, lowIndex, highIndex, unsortedGameList, sortedGameList);
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
void BinaryTree::Merge(int midIndex, int lowIndex, int highIndex, ListNode * unsortedGameList, ListNode * sortedGameList)
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

/************************************************************************
* FUNCTION: ReadTextFile()
* DESCRIPTION: reads the input text file, calls the relevant functions to build the BST
* INPUT PARAMETERS: string with the name of the text file and root node pointer
* OUTPUT: none
* RETURN VALUE: memory allocation validation int.  Zero means all good in the hood
* IMPLEMENTED BY: Jerome Latona
*************************************************************************/
/*
int ReadTextFile(string inputTextFile, TreeRootStruct & treeRoot)
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

	while (memoryAllocationValidation == 0 && infile >> numberFromInput)	//works even if input fie has whitespace before EOF
	{
		newNode = CreateNode(numberFromInput);
		if (newNode == NULL)
		{
			memoryAllocationValidation = -1;
		}
		else
		{
			numberFound = FindNode(newNodeParent, treeRoot, numberFromInput);
			if (numberFound == false)														//insert into tree, node doesn't already exist
			{
				InsertNode(newNode, treeRoot);
			}
			else
			{
				cout << "\t" << numberFromInput << " is a duplicate and will be ignored.\n";
				delete newNode;
			}
		}
	}

	if (memoryAllocationValidation == -1)
	{
		cout << "\nMemory allocation error.  Cannot add further integers.\n";
	}

	infile.close();
	return memoryAllocationValidation;

}
*/

/************************************************************************
* FUNCTION: UserMenu2()
* DESCRIPTION: offers a menu of options to the user and calls functions until exit
* INPUT PARAMETERS: root pointer
* OUTPUT: menu to user 
* RETURN VALUE: none
* IMPLEMENTED BY: Jerome Latona
*************************************************************************/
/*
void UserMenu2(TreeRootStruct treeRoot)
{
	char choice = 'a';
	int number,
		i = 0;
	bool numberFound;
	treeNode* userNode = NULL;
	treeRootStruct userRoot = CreateTree();

	cout << "\nThe total number of integers in the BST";
	if (treeRoot.numberOfNodes == 0)
	{
		cout << " is ";
	}
	else
	{
		cout << " are ";
	}
	cout << treeRoot.numberOfNodes << endl;

	while (choice != 'E' && choice != 'X')
	{

		cout << "\n\nEnter a choice from the following menu:\n"
			<< "\t[S]how all integers in the binary search tree.\n"
			<< "\t[A]dd an integer to the tree.\n"
			<< "\t[D]elete an integer from the tree.\n"
			<< "\t[F]ind an integer within the tree, and display its subtree.\n"
			<< "\t[E][x]it the program.\n";
		cin >> choice;
		choice = toupper(choice);
		if (choice != 'S' && choice != 'A' && choice != 'D' && choice != 'F' && choice != 'E' && choice != 'X')
		{
			cout << "\nThat is not a valid menu option.\n";
		}

		switch (choice)
		{
		case 'S':
			InOrderDisplayCall(treeRoot);
			break;
		case 'A':
			cout << "Enter integer to add to tree: ";
			cin >> number;
			numberFound = FindNode(userNode, treeRoot, number);
			if (numberFound == false)
			{
				userNode = CreateNode(number);
				if (userNode != NULL)
				{
					InsertNode(userNode, treeRoot);
				}
			}
			else
			{
				cout << "\t" << number << " is a duplicate and will be ignored.\n";
			}	//dynamic memory allocation will only happen on non-duplicates

			if (userNode == NULL && numberFound == false)
			{
				cout << "\nMemory allocation fail. Unable to add new number to the tree.\n";
			}

			if (userNode != NULL && numberFound == false)
			{
				cout << "\t" << number << " is has been added to the tree.\n";
			}
			break;
		case 'D':
			cout << "Enter integer to delete from tree: ";
			cin >> number;
			numberFound = FindNode(userNode, treeRoot, number);
			if (numberFound == false)
			{
				cout << endl << number << " is not in tree.  Unable to delete.\n";
			}
			else
			{
				DeleteNode(number, treeRoot);
			}
			break;
		case 'F':
			cout << "Enter integer whose subtree will be displayed: ";
			cin >> number;
			numberFound = FindNode(userNode, treeRoot, number);
			if (numberFound == false)
			{
				cout << endl << number << " is not in tree.  Unable to display subtree.\n";
			}
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
}
*/
