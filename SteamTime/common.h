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

struct User {
	//constructor for use with deque.pushback()
	User(unsigned long long id) {
		id_64 = id;
		name = "NULL";
		lastLogoff = 0;
		created = 0;
	};
	string name;
	unsigned long long id_64;
	int lastLogoff;
	int created;
};

static const int MAX_SIZE = 5;
const int MAX_TREE_SIZE = 100;

#endif // !Common_H
