# steamTime
Project to index and compare users' steam games' playtimes

WILL ONLY WORK UNDER WINDOWS!! or at least until I figure out how to include libcurl (documentation for windows didn't work: probably just me)
	
For cross platform compatibility, the only function/libraries that need to be replaced is	ReadWebPage function (in getLibInfo.h/cpp) which relies on windows.h for typedefs and winhttp.h for all interaction with internet.

