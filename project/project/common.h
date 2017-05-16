/**********************************************************************************************
* PROGRAM FILENAME: Common.h
* DESCRIPTION: global declarations
* DESIGNER: Brendan Doherty
* May 15, 2017
* DVC COMSC200
**********************************************************************************************/

#ifndef Common_H
#define Common_H
#include <string>
using std::string;

struct ListNode {
	string name;
	unsigned int appID;
	unsigned int playTime;
};

struct LinkedListNode {
	string name;
	unsigned int appID;
	unsigned int playTime;
	ListNode * next = NULL;
};





const int MAX_TREE_SIZE = 100;

#endif // !Common_H
