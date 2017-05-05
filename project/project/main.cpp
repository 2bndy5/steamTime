#include <iostream>
#include <string>
#include "getLibInfo.h"
using namespace std;
//Jerome was here

//No way that I can see you typing

int main()
{
	//extractAllApps(getSteamID());
	extractGames(false, getAccountNumber(getSteamID64()), true);
	return 0;
}
