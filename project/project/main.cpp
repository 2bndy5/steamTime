#include <iostream>
#include <string>
#include "GameList.h"
#include "getLibInfo.h"
#include "BinaryTree.h"
using namespace std;

int main(int argc, char *argv[])
{
	if (argc >= 2) {
		string user(argv[1]);
		extractAllApps( user, true);
	}
	else {
		string rootUser = getSteamID();
		string rootSteamID_64 = getAccountNumber(rootUser);
		BinaryTree* bt = new BinaryTree;
		GameList* gList = extractGames(false, rootSteamID_64);
		bt->InsertNode(stoi(rootSteamID_64), rootUser, gList);
		//	findFriends(logOutput, id, indexFriends);
		//findFriends(false, rootSteamID_64, false);

	}
	return 0;
}
