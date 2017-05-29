#ifndef GameList_H
#define GameList_H
#include <string>
#include "common.h"
using std::string;

class GameList {
private:
	bool isEmpty();
public:
	GameList();
	~GameList();
	void print();//print elements of array "list"
	void addNode(string, unsigned int, unsigned int);//using insertion sort
	ListNode list[MAX_SIZE];
};

#endif // !Game_H
