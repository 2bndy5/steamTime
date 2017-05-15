#include <iostream>
#include <string>
#include "LibInfo.h"
using namespace std;


int main(int argc, char *argv[])
{
	LibInfo* driver = new LibInfo;
	if (argc >= 2) {
		string user(argv[1]);
		driver->extractAllApps( user, true);
	}
	else {
		string rootUser = driver->getSteamID();
		string rootSteamID_64 = driver->getAccountNumber(rootUser);
		GameList* gList = driver->extractGames(false, rootSteamID_64);
		dynamic_cast<BinaryTree*>(driver)->InsertNode(stoull(rootSteamID_64), rootUser, gList);
		driver->findFriends(true, rootSteamID_64);
	}
	return 0;
}
