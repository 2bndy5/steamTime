#ifndef getLibInfo_H
#define getLibInfo_H
#pragma comment(lib, "winhttp.lib")//works only visual studio
#include "BinaryTree.h" // Inherit BinaryTree to use protected variables like numberOfNodes
#include "windows.h"
#include "Winhttp.h"
#include "GameList.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class LibInfo
{
private:
	BOOL ReadWebPage(string &source, bool secure, const wchar_t *url, const wchar_t *verb);// source from http://stackoverflow.com/a/29552504
	string convertSteamID(string &);// for converting steam ID_64 to steam username
	void useFriendList(bool logOutput, string &src, bool indexGames, BinaryTree *tree);
	/*steam convert id logic ( taken from https://developer.valvesoftware.com/wiki/SteamID )
																			formula:
	W = Z*2+V+Y
																			let W = steamID_64
																			let Z = account # for steam account, this is based on account creation date/time
	acount type = indiviual;
																			let V = steaID_64 identifier, in our case this is 0x0110000100000000
	0x0110000100000000 = 76561197960265728
																			let Y = 0 or 1 defined as "part of the account #", but doesn't say which part. this can be determined in the formula as answer cannot have decimals; ( z + 1 ) / 2 !=  W + 0.5
																			let X = Account universe, in our case this will be 1 ( for individual )
																			example
	2bndy5 = 76561198054478758 : Z == 47106515
	*/
public:
	string getSteamID(); 
	string getAccountNumber(string &uName);//user profile must have a custom URL set to user's steam ID for this to work correctly
	void findFriends(bool logOutput, string &id, bool indexGames);
	
	// 2nd attempt gets library info from profile web page **includes software appIDs**
	void extractAllApps(string &, bool);

	// 1st attempt to implement steam web API, but doesn't return software appIDs
	GameList* extractGames(bool logOutput, string &id);
	

}

#endif
