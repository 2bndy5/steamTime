#ifndef GameList_H
#define GameList_H
#include <string>
using std::string;

struct ListNode {
	string name;
	unsigned int appID;
	unsigned int playTime;
	ListNode* next;
};

class GameList {
public:
	GameList();
	~GameList();
	void addNode(string, unsigned int, unsigned int);
private:
	void makeEmpty();
	bool isEmpty();
	ListNode* root;
};

#endif // !Game_H
