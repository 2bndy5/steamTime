# steamTime
Project to index and compare users' steam games' playtimes

WILL ONLY WORK UNDER WINDOWS!! or at least until I figure out how to include libcurl (documentation for windows didn't work: probably just me)
Other requirements include: set your profile's custom URL to your steam username (or any alias really, but using your steam username is more concise), and it helps to have your game library visible to public (skips indexing of users whose profile is set to private)
	
For cross platform compatibility, the only function/libraries that need to be replaced is	ReadWebPage function (in getLibInfo.h/cpp) which relies on windows.h for typedefs and winhttp.h for all interaction with internet.

