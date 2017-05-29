#include "LibInfo.h"

/************************************************************************
* FUNCTION: ReadWebPage()
* DESCRIPTION: function to get information from internet and save into "source" string
* INPUT PARAMETERS: string (by reference) of where to save http request, boolean to specify http (false) or https (true), wide char* of domain, wide char* of http request (everything after ".com" or ".org" etc.)
* OUTPUT: none
* RETURN VALUE: window.h typedef of a boolean that returns true only if successful
*************************************************************************/
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

/************************************************************************
* FUNCTION: LibInfo()
* DESCRIPTION: constructor set binary tree pointer to empty tree
* INPUT PARAMETERS: none
* OUTPUT: none
* RETURN VALUE: N/A
*************************************************************************/
LibInfo::LibInfo() {
	tree = new BinaryTree;
}

/************************************************************************
* FUNCTION: getBT()
* DESCRIPTION: getter for binary tree object
* INPUT PARAMETERS: none
* OUTPUT: none
* RETURN VALUE: pointer to BinaryTree object
*************************************************************************/
BinaryTree* LibInfo::getBT() {
	return tree;
}

/************************************************************************
* FUNCTION: getSteamID()
* DESCRIPTION: get steam username from console input and return it in a string
* INPUT PARAMETERS: none
* OUTPUT: none
* RETURN VALUE: string of steam username
*************************************************************************/
string LibInfo::getSteamID()
{
	string id;
	cout << "Enter Steam Username: ";
	cin >> id;
	return id;
}

/************************************************************************
* FUNCTION: convertSteamID()
* DESCRIPTION: helper function to fillQueue2ndaryInfo() to get additional user info like steam username, last logoff, and account creation date
* INPUT PARAMETERS: string of steam user 64 bit IDs, can contain up to 100 seperated by commas
* OUTPUT: none
* RETURN VALUE: none, finds pre-existing User object and saves info accordingly
*************************************************************************/
void LibInfo::convertSteamID(string &idList) {
	string src = "";
	string subURL = "ISteamUser/GetPlayerSummaries/v0002/?key=0B79957AE6E898D001F03E348355324C&format=xml&steamids=";
	subURL += idList;
	//convert string to wide string for casting to const wide char*
	wstring widestr = wstring(subURL.begin(), subURL.end());
	//false indicates not-secure website (http), true is for secure (https)
	ReadWebPage(src, false, L"api.steampowered.com", widestr.c_str());
	//http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=0B79957AE6E898D001F03E348355324C&steamids=76561197960435530
	size_t i = src.find("<steamid>") + 9;
	while (i < src.length() && i > 8) {
		size_t end = src.find("</steamid>", i);
		string id_64 = src.substr(i, end - i);
		i = src.find("<personaname>", i) + 13;
		end = src.find("</personaname>", i);
		string uName = src.substr(i, end - i);
		i = src.find("<lastlogoff>", i) + 12;
		end = src.find("</lastlogoff>", i);
		int lastLogoff = stoi(src.substr(i, end - i));
		i = src.find("<timecreated>", i) + 13;
		end = src.find("</timecreated>", i);
		int created = stoi(src.substr(i, end - i));
		for (unsigned j = 0; j < friends.size(); j++){
			if (friends[j]->id_64 == stoull(id_64)) {
				friends[j]->name = uName;
				friends[j]->lastLogoff = lastLogoff;
				friends[j]->created = created;
				break;
			}
		}
		i = src.find("<steamid>", i) + 9;
	}
}

/************************************************************************
* FUNCTION: getAccountNumber()
* DESCRIPTION: Finds and returns 64 bit version of specified user's steam id (requires "custom URL" to set to steam username in steam profile settings)
* INPUT PARAMETERS: string of steam username
* OUTPUT: none
* RETURN VALUE: string of 64 bit steam id
*************************************************************************/
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

/************************************************************************
* FUNCTION: extractAllApps()
* DESCRIPTION: Finds and returns parent node for node with matching
* attribute that is passed. Uses lookahead idea to peek at children
* INPUT PARAMETERS: treeNode->user->id_64 and pointer to current parent
* OUTPUT: none
* RETURN VALUE: none, outputs to a excel formatted txt file "$username& library.txt"
*************************************************************************/
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

/************************************************************************
* FUNCTION: extractGames()
* DESCRIPTION: implement steam web API call that returns all owned games for specified user (doesn't return software info)
* INPUT PARAMETERS: string version of 64 bit steam user id
* OUTPUT: none
* RETURN VALUE: GameList object that contains user's top played games
*************************************************************************/
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

/************************************************************************
* FUNCTION: createTree()
* DESCRIPTION: Creates Binary tree from deque<User*> friends
* INPUT PARAMETERS: none
* OUTPUT: none
* RETURN VALUE: none
*************************************************************************/
void LibInfo::createTree()
{
	while (!friends.empty()) {
		if (!tree->findNode(friends.front()->id_64)) {//check for duplicates
			cout << endl << friends.front()->name << " ( " << friends.front()->id_64 << " )" << endl;
			GameList* gList = extractGames(to_string(friends.front()->id_64));
			//now insert into tree accordingly
			if (gList != NULL)//if library is visible
				tree->insertNode(friends.front(), gList);
			else
				cout << "Library for " << friends.front()->name << " is empty or set to private only." << endl;
		}
		else
			cout << friends.front()->id_64 << " is already in tree!" << endl;
		friends.pop_front();
		cout << "Building Binary Tree.......... " << (double)tree->numberOfNodes / MAX_TREE_SIZE * 100 << "% done" << endl;
	}
}

/************************************************************************
* FUNCTION: findFriends()
* DESCRIPTION: download xml list of friends for each user in deque and pass it to parseFriends helper function
* INPUT PARAMETERS: none
* OUTPUT: none
* RETURN VALUE: none (data saved in deque<User*> friends)
*************************************************************************/
void LibInfo::findFriends()
{
	unsigned i = 0;
	while (!friends.empty() && friends.size() <= MAX_TREE_SIZE) {
		string src;
		string subURL = "ISteamUser/GetFriendList/v0001/?key=0B79957AE6E898D001F03E348355324C&steamid=";
		subURL += to_string(friends[i++]->id_64);
		subURL += "&relationship=all&format=xml";
		wstring widestr = wstring(subURL.begin(), subURL.end());
		ReadWebPage(src, false, L"api.steampowered.com", widestr.c_str());
		//http://api.steampowered.com/ISteamUser/GetFriendList/v0001/?key=0B79957AE6E898D001F03E348355324C&steamid=76561198054478758&relationship=all&format=xml
		parseFriendList(src);//add current user's friends to vector<string> friends
	}
	fillQueue2ndaryInfo();
}

/************************************************************************
* FUNCTION: fillQueue2ndaryInfo()
* DESCRIPTION: get users persona names (steam usernames), account creation (UNIX timestamp), and last logout time (UNIX timestamp). adds info to User objects (if it exists)
* INPUT PARAMETERS: none (uses deque<User*> friends)
* OUTPUT: none
* RETURN VALUE: none
*************************************************************************/
void LibInfo::fillQueue2ndaryInfo()
{
	unsigned i = 1;
	string steamNames = to_string(friends.front()->id_64);
	while (i < friends.size()) {
		steamNames += "," + to_string(friends[i]->id_64);
		i++;
		if (i == friends.size() - 1) {
			convertSteamID(steamNames);
		}
		else if (i % 100 == 0) {
			convertSteamID(steamNames);
			steamNames = to_string(friends[i + 1]->id_64);
			i++;
		}
	}
}

/************************************************************************
* FUNCTION: parseFriendList()
* DESCRIPTION: This parses each friend from src string add them into queue provided they aren't already
* INPUT PARAMETERS: string containing xml version of friends list returned from findFriends
* OUTPUT: none
* RETURN VALUE: none
*************************************************************************/
void LibInfo::parseFriendList(string &src)
{
	for (size_t i = 0; i < src.length(); i++) 
  	{
		if (src.find("</steamid>", i) >= src.length())
			break;
		string friendID_64 = src.substr(src.find("<steamid>", i) + 9, src.find("</steamid>", i) - src.find("<steamid>", i) - 9);
		bool inQueue = false;
		for (unsigned j = 0; j < friends.size(); j++) {
			if (friends[j]->id_64 == stoull(friendID_64)) {
				inQueue = true;
				break;
			}
		}// end check for duplicate in queue
		if (!inQueue && friends.size() <= MAX_TREE_SIZE)
			friends.push_back(new User(stoull(friendID_64)));
		i = src.find("</steamid>", i);
	}
}

/************************************************************************
* FUNCTION: removeSpecialChars()
* DESCRIPTION: Finds and removes characters like (TM) and (R)
* INPUT PARAMETERS: string to be edited by reference
* OUTPUT: none
* RETURN VALUE: altered string saved in arrguments passed
*************************************************************************/
void LibInfo::removeSpecialChars(string &str)
{
	while (str.find("\\u00ae") < str.length())
		str.erase(str.find("\\u00ae"), 6);
	while (str.find("\\u2122") < str.length())
		str.erase(str.find("\\u2122"), 6);
}