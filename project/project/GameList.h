#ifndef GameList_H
#define GameList_H
#include <string>
#include "common.h"
using std::string;

class GameList {
public:
	GameList();
	~GameList();
	void print();
	void addNode(string, unsigned int, unsigned int);
	ListNode list[MAX_SIZE];
private:
	bool isEmpty();
	static const int MAX_SIZE = 5;
};

#endif // !Game_H
