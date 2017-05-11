#include "GameList.h"
#include <iostream>
using std::cout;
using std::endl;

GameList::GameList()
{
	for (int i = 0; i < MAX_SIZE; i++)
		list[i].name = "NULL";
}

GameList::~GameList()
{
//	delete[] list;
}

void GameList::print()
{
	for (int i = 0; i < MAX_SIZE; i++) {
		if (list[i].name == "NULL")//break early
			break;
		cout << list[i].name << " : ";
		cout << list[i].playTime << " minutes";
		cout << endl;
	}
}

void GameList::addNode(string n, unsigned int id, unsigned int t)
{
	ListNode temp;
	temp.name = n;
	temp.appID = id;
	temp.playTime = t;
	if (isEmpty()) {
		list[0] = temp;
	}
	else {
		for (int i = 0; i <= MAX_SIZE - 1; i++)
		{
			if (list[i].name == "NULL") {
				list[i] = temp;
				break;
			}
			if (list[i].playTime < t) {
				ListNode temp2 = list[i];
				list[i] = temp;
				temp = temp2;
			}
		}//end for 5 games
	}//end else not empty
}
bool GameList::isEmpty()
{
	if (list[0].name == "NULL")
		return true;
	else
		return false;
}
