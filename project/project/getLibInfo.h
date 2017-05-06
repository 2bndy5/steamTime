#ifndef getLibInfo_H
#define getLibInfo_H
#pragma comment(lib, "winhttp.lib")//works only visual studio
#include "windows.h"
#include "Winhttp.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

BOOL ReadWebPage(string &source, bool secure, const wchar_t *url, const wchar_t *verb);// source from http://stackoverflow.com/a/29552504
string getSteamID();
string convertSteamID(string &);// for converting steam ID_64 to steam username
string getAccountNumber(string &uName);//user profile must have a custom URL set to user's steam ID for this to work correctly

// 2nd attempt gets library info from profile web page **includes software appIDs**
void extractAllApps(string &, bool);

// 1st attempt to implement steam web API, but doesn't return software appIDs
void extractGames(bool, string &, bool);
void findFriends(bool, string &, bool);

#endif