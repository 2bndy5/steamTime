/**********************************************************************************************
* PROGRAM FILENAME: Common.h
* DESCRIPTION: global declarations
* DESIGNER: Brendan Doherty
* may 15, 2017
* DVC COMSC200
**********************************************************************************************/
#ifndef Common_H
#define Common_H
#include <string>
using std::string;

struct ListNode {
	string name;
	int appID;
	unsigned long playTime;
};

struct LinkListNode :public ListNode
{
	LinkListNode* next = NULL;
};

static const int MAX_SIZE = 5;
const int MAX_TREE_SIZE = 100;

#endif // !Common_H
