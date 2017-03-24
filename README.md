# steamTime
Project to index an compare users' steam games' play times

WILL ONLY WORK UNDER WINDOWS!! or at least until i figure out how to include libcurl (documentation for windows didn't work)
	
For cross platform compatibility, the only function/libraries that need to be replaced is	ReadWebPage function (in getLibInfo.h/cpp) which relies on windows.h for typedefs and winhttp.h for all interaction with internet.

