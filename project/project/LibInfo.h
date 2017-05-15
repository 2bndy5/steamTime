#ifndef LibInfo_H
#define LibInfo_H
#pragma comment(lib, "winhttp.lib")//works only visual studio
#include <iostream>
#include <iomanip>
#include <fstream>
#include "windows.h"
#include "Winhttp.h"
#include "GameList.h"
#include "common.h"
#include "BinaryTree.h"
using namespace std;

class LibInfo :public BinaryTree
{
private:
	const int MAX_TREE_SIZE = 10;
	//BinaryTree* tree;
	BOOL ReadWebPage(string &source, bool secure, const wchar_t *url, const wchar_t *verb);// source from http://stackoverflow.com/a/29552504
	string convertSteamID(string &);// for converting steam ID_64 to steam username
	void useFriendList(bool logOutput, string &src);//findFriends() helper function to handle each friend's games individually
public:
	explicit LibInfo();//empty constructor
	string getSteamID();//get string from cin and return as steam username 
	string getAccountNumber(string &uName);//user profile must have a custom URL set to user's steam ID for this to work correctly
	void findFriends(bool logOutput, string &id);//crawl root user's friend list and index games
	void extractAllApps(string &uName, bool logOutput);//gets library info from profile web page **includes software appIDs** called when cmd line arguments passed
	GameList* extractGames(bool logOutput, string &id);//implement steam web API, but doesn't return software appIDs
//	BinaryTree* getBT();//return pointer to working binary tree object
};

#endif
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
