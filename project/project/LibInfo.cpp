#include "LibInfo.h"

BOOL LibInfo::ReadWebPage(string &source, bool secure, const wchar_t *url, const wchar_t *verb)
{
	source = "error";
	BOOL bResults = FALSE;
	HINTERNET hsession = NULL;
	HINTERNET hconnect = NULL;
	HINTERNET hrequest = NULL;

	hsession = WinHttpOpen(L"Example", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	if (!hsession) goto error;

	hconnect = WinHttpConnect(hsession, url, secure ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT, 0);
	if (!hconnect) goto error;

	hrequest = WinHttpOpenRequest(hconnect, L"GET", verb, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, secure ? WINHTTP_FLAG_SECURE : 0);
	if (!hrequest) goto error;

	if (!WinHttpSendRequest(hrequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0))
		goto error;

	if (!WinHttpReceiveResponse(hrequest, NULL))
		goto error;

	source = "";
	for (DWORD size = 1, downloaded = 1; downloaded > 0;)
	{
		WinHttpQueryDataAvailable(hrequest, &size);
		if (!size) break;
		string buf(size + 1, 0);
		WinHttpReadData(hrequest, (LPVOID)&buf[0], size, &downloaded);
		buf.resize(downloaded);
		source += buf;
	}

error:
	if (hrequest) WinHttpCloseHandle(hrequest);
	if (hconnect) WinHttpCloseHandle(hconnect);
	if (hsession) WinHttpCloseHandle(hsession);

	return bResults;
}

LibInfo::LibInfo(){}

string LibInfo::getSteamID()
{
	string id;
	cout << "Enter Steam Username: ";
	cin >> id;
	return id;
}

string LibInfo::convertSteamID(string &ID_64){
	string src = "";
	string subURL = "ISteamUser/GetPlayerSummaries/v0002/?key=0B79957AE6E898D001F03E348355324C&format=xml&steamids=";
	subURL += ID_64;
	string uName = "not found";
	//convert string to wide string for casting to const wide char
	wstring widestr = wstring(subURL.begin(), subURL.end());
	//false indicates not-secure website (http), true is for secure (https)
	ReadWebPage(src, false, L"api.steampowered.com", widestr.c_str());
	//http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=0B79957AE6E898D001F03E348355324C&steamids=76561197960435530
	string start = "<steamid>" + ID_64;
	if (src.find(start) < src.length()) {
		size_t found = src.find("<personaname>");
		size_t startCapture = found + 13;
		size_t endCapture = src.find("</personaname>", startCapture);
		uName = src.substr(startCapture, endCapture - startCapture);
		cout << "\nusername = " << uName << endl;
	}
	return uName;
}

string LibInfo::getAccountNumber(string &uName){
	string src = "";
	string subURL = "calculator/?player=";
	subURL += uName;
	string id_64 = "not found";
	//convert string to wide string for casting to const wide char
	wstring widestr = wstring(subURL.begin(), subURL.end());
	//false indicates not-secure website (http), true is for secure (https)
	ReadWebPage(src, true, L"steamdb.info", widestr.c_str());
	//https://steamdb.info/calculator/?player=2bndy5
	if (src.find("Provided vanity url does not resolve to any SteamID.") != src.length()) {
		size_t found = src.find("SteamID<");
		size_t startCapture = src.find("to copy\">", found) + 9;
		size_t endCapture = src.find("</span", startCapture);
		id_64 = src.substr(startCapture, endCapture - startCapture);
		cout << "id_64 = " << id_64 << endl;
	}
	else
		cout << uName << " doesn't exist or doesn't have custom url set to " << uName << " in profile settings." << endl;
	return id_64;
}

void LibInfo::extractAllApps(string &uName, bool logOutput)
{
	string src;
	string subURL = "id/";
	subURL += uName;
	subURL += "/games/?tab=all&sort=name";
	wstring widestr = wstring(subURL.begin(), subURL.end());
	//http://steamcommunity.com/id/2bndy5/games/?tab=all
	ReadWebPage(src, false, L"steamcommunity.com", widestr.c_str());
	if (src.find("The specified profile could not be found.") != src.length()) 
	{
		src = src.substr(src.find("rgGames = [") + 11, src.find("];", src.find("rgGames = [")) - src.find("rgGames = [") - 11);
		ofstream fout;
		if (logOutput)
			fout.open(uName + " Library.txt");
		int appCount = 0;
		for (size_t i = 0; i < src.length(); i++) {
			string appID = src.substr(src.find("appid\":", i) + 7, src.find(",\"", i) - src.find("appid\":", i) - 7);
			string appName = src.substr(src.find("name\":\"", i) + 7, src.find("\",", i) - src.find("name\":\"", i) - 7);
			size_t nextGame = src.find("},{", i);
			size_t timeInfo = src.find("hours_forever", i);
			string appTime = "";
			if (timeInfo < nextGame && timeInfo < src.length())
				appTime = src.substr(src.find("hours_forever\":\"", i) + 16, src.find("\",", src.find("hours_forever\":\"", i)) - src.find("hours_forever\":\"", i) - 16);

			removeSpecialChars(appName);

			i = src.find("},{", i);
			cout << setw(6) << appID << " = " << appName;
			if (appTime == "")
				cout << endl;
			else
				cout << " : " << appTime << " hour(s) played" << endl;
			appCount++;
			if (logOutput) {
				fout << appID << "\t" << appName;
				if (appTime == "")
					fout << endl;
				else
					fout << "\t" << appTime << endl;
			}
			if (i >= src.length())
				break;
		}
		cout << "Found " << appCount << " apps" << endl;
		if (logOutput) {
			fout << "Found " << appCount << " apps" << endl;
			fout.close();
		}
	}
	else
		cout << uName << " doesn't exist or doesn't have custom url set to " << uName << " in profile settings." << endl;
 }

GameList* LibInfo::extractGames(string &id)
{
	string src;
	//Web API key = 0B79957AE6E898D001F03E348355324C
	string subURL = "IPlayerService/GetOwnedGames/v0001/?key=0B79957AE6E898D001F03E348355324C&steamid=";
	subURL += id;
	subURL += "&include_appinfo=1&format=csv";
	wstring widestr = wstring(subURL.begin(), subURL.end());
	ReadWebPage(src, false, L"api.steampowered.com", widestr.c_str());
	//http://api.steampowered.com/IPlayerService/GetOwnedGames/v0001/?key=0B79957AE6E898D001F03E348355324C&steamid=76561198054478758&format=csv
	//start parsing results
	if (src.find("game_count") < src.length()) {
		int gameCount = stoi(src.substr(src.find("game_count") + 12, src.find(",") - src.find("game_count")));
		cout << "Game count = " << gameCount << endl;
	}
	else
		return NULL;// profile is private, so nothing to do
	GameList* games = new GameList;
	for (size_t i = 0; i < src.length(); i++) {
		if (src.find("appid", i) >= src.length())
			break;
		int appid = stoi(src.substr(src.find("appid", i) + 8, src.find(",", src.find("appid", i)) - src.find("appid", i) - 8));
		string gameTitle = src.substr(src.find("name", i) + 8, src.find("\",", i) - src.find("name", i) - 8);
		removeSpecialChars(gameTitle);
		unsigned long appTime = stoul(src.substr(src.find("playtime_forever", i) + 19, src.find("\",", i) - src.find("playtime_forever", i) - 19));
		//display all games
		if (appTime > 0) {
		//	cout << appid << " = " << gameTitle << " (" << appTime << " minutes)" << endl;
			games->addNode(gameTitle, appid, appTime);
		}
		i = src.find("}", i);
	}
	games->print();//display top 5 played games
	return games;
}

void LibInfo::findFriends()
{
	while (!friends.empty() && numberOfNodes <= MAX_TREE_SIZE) {
		string src;
		string subURL = "ISteamUser/GetFriendList/v0001/?key=0B79957AE6E898D001F03E348355324C&steamid=";
		subURL +=  friends.front();
		subURL += "&relationship=all&format=xml";
		wstring widestr = wstring(subURL.begin(), subURL.end());
		ReadWebPage(src, false, L"api.steampowered.com", widestr.c_str());
		//http://api.steampowered.com/ISteamUser/GetFriendList/v0001/?key=0B79957AE6E898D001F03E348355324C&steamid=76561198054478758&relationship=all&format=xml
		parseFriendList(src);//add current user's friends to vector<string> friends
		unsigned long long id_64 = stoull(friends.front());
		if (!FindNode(id_64)) {//check for duplicates
			string steamName = convertSteamID(friends.front());
			GameList* gList = extractGames(friends.front());
			//now insert into tree accordingly
			if (gList != NULL)//if library is visible
				InsertNode(id_64, steamName, gList);
			else
				cout << "Library for " << steamName << " is empty or set to private only." << endl;
		}
		else
			cout << id_64 << " is already in tree!" << endl;
		friends.pop_front();
		cout << "Building Binary Tree.......... " << numberOfNodes / MAX_TREE_SIZE << "% done" << endl;
	}
}

// This function will extract the games for each friend 
void LibInfo::parseFriendList(string &src)
{
	for (size_t i = 0; i < src.length(); i++) 
  	{
		if (src.find("</steamid>", i) >= src.length())
			break;
		string friendID_64 = src.substr(src.find("<steamid>", i) + 9, src.find("</steamid>", i) - src.find("<steamid>", i) - 9);
		bool inQueue = false;
		for (int j = 0; j < friends.size(); j++) {
			if (friends[j] == friendID_64) {
				inQueue = true;
				break;
			}
		}
		if (!FindNode(stoull(friendID_64)) && !inQueue)
			friends.push_back(friendID_64);
		i = src.find("</steamid>", i);
	}
}

void LibInfo::removeSpecialChars(string &str)
{
	while (str.find("\\u00ae") < str.length())
		str.erase(str.find("\\u00ae"), 6);
	while (str.find("\\u2122") < str.length())
		str.erase(str.find("\\u2122"), 6);
}

