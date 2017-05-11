#include "GameList.h"

GameList::GameList()
{
	root = new ListNode;
	root->name= "NULL";
	root->next = NULL;
}

GameList::~GameList()
{
	makeEmpty();
	delete root;
}

void GameList::addNode(string n, unsigned int id, unsigned int t)
{
	ListNode* temp;
	temp->name = n;
	temp->appID = id;
	temp->playTime = t;
	temp->next = NULL;
	bool success = false;
	ListNode* curr = root;
	if (isEmpty()) {
		delete root;
		root = temp;
	}
	while (!success)
	{
		if (curr->next == NULL) {
			curr->next = temp;
			success = true;
		}
		else if (curr->playTime < t && curr == root) {
			temp->next = curr;
			root = temp;
			success = true;
		}
		else if (curr->next->playTime < t) {
			temp->next = curr->next;
			curr->next = temp;
			success = true;
		}
		else
			curr = curr->next;
	}
}

void GameList::makeEmpty()
{
	bool success = false;
	ListNode* curr = root;
	while(curr)
	{
		if (curr->next == NULL)
			delete curr;
		else {
			ListNode* temp = curr;
			curr = curr->next;
			delete temp;
		}
	}
}

bool GameList::isEmpty()
{
	if (root->name == "NULL")
		return true;
	else
		return false;
}
