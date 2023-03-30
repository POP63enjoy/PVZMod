#include "SexyCommon.h"
#include <direct.h>
#include "MTRand.h"
#include <cassert>

using namespace PVZMod;

bool PVZMod::Deltree(const String& thePath)
{
	bool success = true;

	String aSourceDir = thePath;

	if (aSourceDir.length() < 2)
		return false;

	if ((aSourceDir[aSourceDir.length() - 1] != '\\') &&
		(aSourceDir[aSourceDir.length() - 1] != '/'))
		aSourceDir += "\\";

	WIN32_FIND_DATAA aFindData;

	HANDLE aFindHandle = FindFirstFileA((aSourceDir + "*.*").c_str(), &aFindData);
	if (aFindHandle == INVALID_HANDLE_VALUE)
		return false;

	do
	{
		if ((aFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
		{
			if ((strcmp(aFindData.cFileName, ".") != 0) &&
				(strcmp(aFindData.cFileName, "..") != 0))
			{
				// Follow the directory
				if (!Deltree(aSourceDir + aFindData.cFileName))
					success = false;
			}
		}
		else
		{
			String aFullName = aSourceDir + aFindData.cFileName;
			if (!DeleteFileA(aFullName.c_str()))
				success = false;
		}
	} while (FindNextFileA(aFindHandle, &aFindData));
	FindClose(aFindHandle);

	if (_rmdir(thePath.c_str()) == 0)
		success = false;

	return success;
}

bool PVZMod::FileExists(const String& theFileName)
{
	WIN32_FIND_DATAA aFindData;

	HANDLE aFindHandle = FindFirstFileA(theFileName.c_str(), &aFindData);
	if (aFindHandle == INVALID_HANDLE_VALUE)
		return false;

	FindClose(aFindHandle);
	return true;
}

void PVZMod::MkDir(const String& theDir)
{
	String aPath = theDir;

	int aCurPos = 0;
	for (;;)
	{
		int aSlashPos = aPath.find_first_of("\\/", aCurPos);
		if (aSlashPos == -1)
		{
			_mkdir(aPath.c_str());
			break;
		}

		aCurPos = aSlashPos + 1;

		String aCurPath = aPath.substr(0, aSlashPos);
		_mkdir(aCurPath.c_str());
	}
}

String PVZMod::vformat(const char* fmt, va_list argPtr)
{
	// We draw the line at a 1MB string.
	const int maxSize = 1000000;

	// If the string is less than 161 characters,
	// allocate it on the stack because this saves
	// the malloc/free time.
	const int bufSize = 161;
	char stackBuffer[bufSize];

	int attemptedSize = bufSize - 1;

	int numChars = 0;
#ifdef _WIN32
	numChars = _vsnprintf_s(stackBuffer, attemptedSize, fmt, argPtr);
#else
	numChars = vsnprintf(stackBuffer, attemptedSize, fmt, argPtr);
#endif

	//cout << "NumChars: " << numChars << endl;

	if ((numChars >= 0) && (numChars <= attemptedSize))
	{
		// Needed for case of 160-character printf thing
		stackBuffer[numChars] = '\0';

		// Got it on the first try.
		return String(stackBuffer);
	}

	// Now use the heap.
	char* heapBuffer = NULL;

	while (((numChars == -1) || (numChars > attemptedSize)) &&
		(attemptedSize < maxSize))
	{
		// Try a bigger size
		attemptedSize *= 2;
		heapBuffer = (char*)realloc(heapBuffer, (attemptedSize + 1));
#ifdef _WIN32
		numChars = _vsnprintf_s(heapBuffer, attemptedSize, attemptedSize, fmt, argPtr);
#else
		numChars = vsnprintf(heapBuffer, attemptedSize, fmt, argPtr);
#endif
	}

	heapBuffer[numChars] = 0;

	String result = String(heapBuffer);

	free(heapBuffer);
	return result;
}

//overloaded StrFormat: should only be used by the xml strings
String PVZMod::StrFormat(const char* fmt ...)
{
	va_list argList;
	va_start(argList, fmt);
	String result = vformat(fmt, argList);
	va_end(argList);

	return result;
}

WString PVZMod::vformat(const wchar_t* fmt, va_list argPtr)
{
	// We draw the line at a 1MB string.
	const int maxSize = 1000000;

	// If the string is less than 161 characters,
	// allocate it on the stack because this saves
	// the malloc/free time.
	const int bufSize = 161;
	wchar_t stackBuffer[bufSize];

	int attemptedSize = bufSize - 1;

	int numChars = 0;
#ifdef _WIN32
	numChars = _vsnwprintf_s(stackBuffer, attemptedSize, fmt, argPtr);
#else
	numChars = vsnwprintf(stackBuffer, attemptedSize, fmt, argPtr);
#endif

	//cout << "NumChars: " << numChars << endl;

	if ((numChars >= 0) && (numChars <= attemptedSize))
	{
		// Needed for case of 160-character printf thing
		stackBuffer[numChars] = '\0';

		// Got it on the first try.
		return WString(stackBuffer);
	}

	// Now use the heap.
	wchar_t* heapBuffer = NULL;

	while (((numChars == -1) || (numChars > attemptedSize)) &&
		(attemptedSize < maxSize))
	{
		// Try a bigger size
		attemptedSize *= 2;
		heapBuffer = (wchar_t*)realloc(heapBuffer, (attemptedSize + 1));
#ifdef _WIN32
		numChars = _vsnwprintf_s(heapBuffer, attemptedSize, attemptedSize, fmt, argPtr);
#else
		numChars = vsnwprintf(heapBuffer, attemptedSize, fmt, argPtr);
#endif
	}

	heapBuffer[numChars] = 0;

	WString result = WString(heapBuffer);

	free(heapBuffer);

	return result;
}

//overloaded StrFormat: should only be used by the xml strings
WString PVZMod::StrFormat(const wchar_t* fmt ...)
{
	va_list argList;
	va_start(argList, fmt);
	WString result = vformat(fmt, argList);
	va_end(argList);

	return result;
}

static PVZMod::MTRand &gMTRand = *(MTRand*)0x76AA30;

int PVZMod::Rand()
{
	return gMTRand.Next();
}

int PVZMod::Rand(int range)
{
	return gMTRand.Next((unsigned long)range);
}

float PVZMod::Rand(float range)
{
	return gMTRand.Next(range);
}

void PVZMod::SRand(uint32_t theSeed)
{
	gMTRand.SRand(theSeed);
}


WString PVZMod::StringToWString(const String& theString)
{
	WString aString;
	aString.reserve(theString.length());
	for (size_t i = 0; i < theString.length(); ++i)
		aString += theString[i];
	return aString;
}

String PVZMod::WStringToString(const WString& theString)
{
	String aString;
	aString.reserve(theString.length());
	for (size_t i = 0; i < theString.length(); ++i)
		aString += (char)theString[i];
	return aString;
}

SexyString PVZMod::StringToSexyString(const String& theString)
{
#ifdef _USE_WIDE_STRING
	return StringToWString(theString);
#else
	return SexyString(theString);
#endif
}

SexyString PVZMod::WStringToSexyString(const WString& theString)
{
#ifdef _USE_WIDE_STRING
	return SexyString(theString);
#else
	return WStringToString(theString);
#endif
}

String PVZMod::SexyStringToString(const SexyString& theString)
{
#ifdef _USE_WIDE_STRING
	return WStringToString(theString);
#else
	return String(theString);
#endif
}

WString PVZMod::SexyStringToWString(const SexyString& theString)
{
#ifdef _USE_WIDE_STRING
	return WString(theString);
#else
	return StringToWString(theString);
#endif
}

String PVZMod::StringToUpper(const String& theString)
{
	String aString;

	for (unsigned i = 0; i < theString.length(); i++)
		aString += toupper(theString[i]);

	return aString;
}

WString PVZMod::StringToUpper(const WString& theString)
{
	WString aString;

	for (unsigned i = 0; i < theString.length(); i++)
		aString += towupper(theString[i]);

	return aString;
}

String PVZMod::StringToLower(const String& theString)
{
	String aString;

	for (unsigned i = 0; i < theString.length(); i++)
		aString += tolower(theString[i]);

	return aString;
}

WString PVZMod::StringToLower(const WString& theString)
{
	WString aString;

	for (unsigned i = 0; i < theString.length(); ++i)
		aString += tolower(theString[i]);

	return aString;
}
