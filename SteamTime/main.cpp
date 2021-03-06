#include <iostream>
#include <string>
#include "LibInfo.h"
using namespace std;


int main(int argc, char *argv[])
{
	LibInfo* driver = new LibInfo;
	if (argc > 1) {
		for (int i = 1; i < argc; ++i) {
			string user(argv[i]);
			driver->extractAllApps(user, true);
			i++;
		}
	}
	else //if no cmd line arguments
	{
		string rootUser = driver->getSteamID();
		string rootSteamID_64 = driver->getAccountNumber(rootUser);
		if (rootSteamID_64 != "not found") {
			driver->friends.push_back(new User(stoull(rootSteamID_64)));
			driver->findFriends();
			driver->createTree();
			BinaryTree* bt = driver->getBT();
			GameList* gList = bt->mostPlayedGame();
			cout << "\n\nTop 5 Most played games out of ";
			cout << bt->getSize() << " users:" << endl;
			gList->print();
		}
		else {
			cout << "ERROR\n could not resolve username to 64 bit version of SteamID.\n";
			cout << "Make sure you have \"custom URL\" set to your username in steam profile settings!" << endl;
		}
	}
	cout << endl << endl;
	system("PAUSE");
	return 0;
}
