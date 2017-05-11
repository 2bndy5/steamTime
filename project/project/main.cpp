#include <iostream>
#include <string>
#include "getLibInfo.h"
using namespace std;

int main(int argc, char *argv[])
{
	if (argc >= 1) {
		string user = argv[1];
		extractAllApps( user, true);
	}
	else {
		string rootUser = getSteamID();
		string rootSteamID_64 = getAccountNumber(rootUser);
		GameList* gList = extractGames(false, rootSteamID_64);
		
		//	findFriends(logOutput, id, indexFriends);
		findFriends(false, rootSteamID_64, false);

	}
	return 0;
}
