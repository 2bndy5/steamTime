#ifndef GameList_H
#define GameList_H
#include <string>
using std::string;

struct ListNode {
	string name;
	unsigned int appID;
	unsigned int playTime;
};

class GameList {
public:
	GameList();
	~GameList();
	void print();
	void addNode(string, unsigned int, unsigned int);
private:
	bool isEmpty();
	static const int MAX_SIZE = 5;
	ListNode list[MAX_SIZE];
};

#endif // !Game_H
