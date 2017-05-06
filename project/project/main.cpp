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
		extractGames(false, getAccountNumber(getSteamID()), true);
	}
	return 0;
}
