#include "BinaryTree.h"

/************************************************************************
* FUNCTION: findParent()
* DESCRIPTION: Finds and returns parent node for node with matching
* attribute that is passed. Uses lookahead idea to peek at children 
* INPUT PARAMETERS: treeNode->nodeNumber and pointer to current parent
* OUTPUT: none
* RETURN VALUE: pointer to parent found or NULL if node doesn't exist
*************************************************************************/
treeNode * BinaryTree::findParent(int numberToDelete, treeNode * curr)
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
bool BinaryTree::FindNode(int numberToFind)
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
treeNode * BinaryTree::CreateNode(int numberToPlace, string steamID, GameList* topFive)
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
bool BinaryTree::InsertNode(int id_64, string uName, GameList* gList)
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
treeNode * BinaryTree::traverseTree(treeNode * curr)
{
	return nullptr;
}
/************************************************************************
* FUNCTION: DeleteNode()
* DESCRIPTION: deletes a node from the binary search tree.
* INPUT PARAMETERS: treeNode->nodeNumber to delete ( checks if node 
* exists via private findParent() )
* OUTPUT: none
* RETURN VALUE: none
*************************************************************************/
void BinaryTree::DeleteNode(int numberToDelete)
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
}

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
* INPUT PARAMETERS: root pointer
* OUTPUT: none
* RETURN VALUE: none
*************************************************************************/
GameList*  BinaryTree::MostPlayedGame()
{
	ListNode* games = new ListNode; //ordered array of strings that will remain mostly empty strings
	GameList* result;

	//traverses entire tree, counting games
	treeNode* curr = root;
	while (traverseTree(curr))
	return;
}


/************************************************************************
* FUNCTION: UserMenuToInputTextFileName()
* DESCRIPTION: menu for user to imput string file. 
* INPUT PARAMETERS: blank string for the name of the inputTextFile name.  Does error 
* checking to see if file exists before return
* OUTPUT: none
* RETURN VALUE: none
*************************************************************************/
/*
void UserMenuToInputTextFileName(string & inputTextFile)
{
	ifstream infile;

	cout << "\nWelcome to the BST builder.\nPlease enter the name of a text input file: ";
	cin >> inputTextFile;

	infile.open(inputTextFile.c_str());


	while (!infile.good())
	{
		cout << endl << "\nFile " << inputTextFile << " does not exist.  Please enter the name of a text input file: ";
		cin >> inputTextFile;
		infile.open(inputTextFile.c_str());
	}

	//cout << endl << inputTextFile  << endl << infile.rdbuf() << endl;
	infile.close();
	return;
}
*/

/************************************************************************
* FUNCTION: ReadTextFile()
* DESCRIPTION: reads the input text file, calls the relevant functions to build the BST
* INPUT PARAMETERS: string with the name of the text file and root node pointer
* OUTPUT: none
* RETURN VALUE: memory allocation validation int.  Zero means all good in the hood
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
