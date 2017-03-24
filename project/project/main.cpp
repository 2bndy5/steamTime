#include <iostream>
#include <string>
#include "getLibInfo.h"
using namespace std;

int main()
{
	//extractAllApps(getSteamID());
	extractGames(false, getAccountNumber(getSteamID64()), true);
	return 0;
}