#include "FolderMappingInterface.h"
#include "SexyCommon.h"
#include <direct.h>

using namespace PVZMod;

enum
{
	FILEFLAGS_END = 0x80
};

static void FixFileName(const char* theFileName, char* theUpperName)
{
	if ((theFileName[0] != 0) && (theFileName[1] == ':'))
	{
		char aDir[256];
		_getcwd(aDir, 256);
		int aLen = strlen(aDir);
		aDir[aLen++] = '\\';
		aDir[aLen] = 0;

		if (_strnicmp(aDir, theFileName, aLen) == 0)
			theFileName += aLen;
	}

	bool lastSlash = false;
	const char* aSrc = theFileName;
	char* aDest = theUpperName;

	for (;;)
	{
		char c = *(aSrc++);

		if ((c == '\\') || (c == '/'))
		{
			if (!lastSlash)
				*(aDest++) = '\\';
			lastSlash = true;
		}
		else if ((c == '.') && (lastSlash) && (*aSrc == '.'))
		{
			// We have a '/..' on our hands
			aDest--;
			while ((aDest > theUpperName + 1) && (*(aDest - 1) != '\\'))
				--aDest;
			aSrc++;
		}
		else
		{
			*(aDest++) = toupper((uint8_t)c);
			if (c == 0)
				break;
			lastSlash = false;
		}
	}
}

FolderMappingInterface::Pak::Pak(const String &theFileName)
{
	AddPakFile(theFileName);
}

FolderMappingInterface::Pak::Pak(HMODULE theModule, const String& theName, const char* theResName, const char* theResType)
{
	AddPakRes(theModule, theName, theResName, theResType);
}


FolderMappingInterface::FolderMappingInterface()
{
	mFolderList.push_back("");
}

FolderMappingInterface::~FolderMappingInterface()
{
	for (auto& folder : mFolderList)
	{
		auto pak = std::get_if<Pak*>(&folder);
		if (pak)
			delete* pak;
	}
}

void FolderMappingInterface::MF_LoadPak()
{
	mFolderList.push_front(new Pak("main.pak"));
}

PFILE* FolderMappingInterface::FOpen(const char* theFileName, const char* theAccess)
{
	if ((_stricmp(theAccess, "r") == 0) || (_stricmp(theAccess, "rb") == 0) || (_stricmp(theAccess, "rt") == 0))
	{
		for (auto& folder : mFolderList)
		{
			if (auto folderName = std::get_if<Folder>(&folder); folderName)
			{
				FILE* aFP = nullptr;
				fopen_s(&aFP, (*folderName + theFileName).c_str(), theAccess);
				if (aFP == NULL)
					return NULL;
				PFILE* aPFP = new PFILE;
				aPFP->mRecord = NULL;
				aPFP->mPos = 0;
				aPFP->mFP = aFP;
				return aPFP;
			}
			else
			{
				auto pak = std::get<Pak*>(folder);

				char anUpperName[256];
				FixFileName(theFileName, anUpperName);

				auto anItr = pak->mPakRecordMap.find(anUpperName);

				if (anItr != pak->mPakRecordMap.end())
				{
					PFILE* aPFP = new PFILE;
					aPFP->mRecord = &anItr->second;
					aPFP->mPos = 0;
					aPFP->mFP = NULL;
					return aPFP;
				}
			}
		}

		return nullptr;
	}

	FILE* aFP = nullptr;
	fopen_s(&aFP, theFileName, theAccess);
	if (aFP == NULL)
		return NULL;
	PFILE* aPFP = new PFILE;
	aPFP->mRecord = NULL;
	aPFP->mPos = 0;
	aPFP->mFP = aFP;
	return aPFP;
}

int FolderMappingInterface::FClose(PFILE* theFile)
{
	if (theFile->mRecord == NULL)
		fclose(theFile->mFP);
	delete theFile;
	return 0;
}

int FolderMappingInterface::FSeek(PFILE* theFile, long theOffset, int theOrigin)
{
	if (theFile->mRecord != NULL)
	{
		if (theOrigin == SEEK_SET)
			theFile->mPos = theOffset;
		else if (theOrigin == SEEK_END)
			theFile->mPos = theFile->mRecord->mSize - theOffset;
		else if (theOrigin == SEEK_CUR)
			theFile->mPos += theOffset;

		theFile->mPos = max(min(theFile->mPos, theFile->mRecord->mSize), 0);
		return 0;
	}
	else
		return fseek(theFile->mFP, theOffset, theOrigin);
}

int FolderMappingInterface::FTell(PFILE* theFile)
{
	if (theFile->mRecord != NULL)
		return theFile->mPos;
	else
		return ftell(theFile->mFP);
}

size_t FolderMappingInterface::FRead(void* thePtr, int theElemSize, int theCount, PFILE* theFile)
{
	if (theFile->mRecord != NULL)
	{
		int aSizeBytes = min(theElemSize * theCount, theFile->mRecord->mSize - theFile->mPos);

		uint8_t* src = (uint8_t*)theFile->mRecord->mCollection->mDataPtr + theFile->mRecord->mStartPos + theFile->mPos;
		uint8_t* dest = (uint8_t*)thePtr;
		for (int i = 0; i < aSizeBytes; i++)
			*(dest++) = (*src++) ^ 0xF7; // 'Decrypt'
		theFile->mPos += aSizeBytes;
		return aSizeBytes / theElemSize;
	}

	return fread(thePtr, theElemSize, theCount, theFile->mFP);
}

int FolderMappingInterface::FGetC(PFILE* theFile)
{
	if (theFile->mRecord != NULL)
	{
		for (;;)
		{
			if (theFile->mPos >= theFile->mRecord->mSize)
				return EOF;
			char aChar = *((char*)theFile->mRecord->mCollection->mDataPtr + theFile->mRecord->mStartPos + theFile->mPos++) ^ 0xF7;
			if (aChar != '\r')
				return (uint8_t)aChar;
		}
	}

	return fgetc(theFile->mFP);
}

int FolderMappingInterface::UnGetC(int theChar, PFILE* theFile)
{
	if (theFile->mRecord != NULL)
	{
		// This won't work if we're not pushing the same chars back in the stream
		theFile->mPos = max(theFile->mPos - 1, 0);
		return theChar;
	}

	return ungetc(theChar, theFile->mFP);
}

char* FolderMappingInterface::FGetS(char* thePtr, int theSize, PFILE* theFile)
{
	if (theFile->mRecord != NULL)
	{
		int anIdx = 0;
		while (anIdx < theSize)
		{
			if (theFile->mPos >= theFile->mRecord->mSize)
			{
				if (anIdx == 0)
					return NULL;
				break;
			}
			char aChar = *((char*)theFile->mRecord->mCollection->mDataPtr + theFile->mRecord->mStartPos + theFile->mPos++) ^ 0xF7;
			if (aChar != '\r')
				thePtr[anIdx++] = aChar;
			if (aChar == '\n')
				break;
		}
		thePtr[anIdx] = 0;
		return thePtr;
	}

	return fgets(thePtr, theSize, theFile->mFP);
}

int FolderMappingInterface::FEof(PFILE* theFile)
{
	if (theFile->mRecord != NULL)
		return theFile->mPos >= theFile->mRecord->mSize;
	else
		return feof(theFile->mFP);
}

HANDLE FolderMappingInterface::FindFirstFileA(const char* lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
	PFindData* aFindData = new PFindData;
	char anUpperName[256];
	FixFileName(lpFileName, anUpperName);
	aFindData->mFindCriteria = anUpperName;
	aFindData->mWHandle = INVALID_HANDLE_VALUE;
	aFindData->mIter = mFolderList.begin();

	for (auto &folder : mFolderList)
	{
		if (auto folderName = std::get_if<Folder>(&folder); folderName)
		{
			aFindData->mWHandle = ::FindFirstFileA((*folderName + aFindData->mFindCriteria).c_str(), lpFindFileData);
			if (aFindData->mWHandle != INVALID_HANDLE_VALUE)
				return (HANDLE)aFindData;
		}
		else
		{
			auto pak = std::get<Pak*>(folder);

			if (pak->PFindNext(aFindData, lpFindFileData))
				return (HANDLE)aFindData;
		}

		aFindData->mIter++;
	}

	delete aFindData;
	return INVALID_HANDLE_VALUE;
}

BOOL FolderMappingInterface::FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData)
{
	PFindData* aFindData = (PFindData*)hFindFile;
	auto& folder = *aFindData->mIter;

	if (std::get_if<Folder>(&folder))
	{
		if (::FindNextFileA(aFindData->mWHandle, lpFindFileData))
			return TRUE;

		::FindClose(aFindData->mWHandle);
		aFindData->mWHandle = INVALID_HANDLE_VALUE;
	}
	else
	{
		auto pak = std::get<Pak*>(folder);
		if (pak->PFindNext(aFindData, lpFindFileData))
			return TRUE;
	}

	while (++aFindData->mIter != mFolderList.end())
	{
		folder = *aFindData->mIter;
		if (auto folderName = std::get_if<Folder>(&folder); folderName)
		{
			aFindData->mWHandle = ::FindFirstFileA((*folderName+aFindData->mFindCriteria).c_str(), lpFindFileData);
			if (aFindData->mWHandle != INVALID_HANDLE_VALUE)
				return TRUE;
		}
		else
		{
			auto pak = std::get<Pak*>(folder);
			if (pak->PFindNext(aFindData, lpFindFileData))
				return TRUE;
		}
	}

	return FALSE;
}

BOOL FolderMappingInterface::FindClose(HANDLE hFindFile)
{
	PFindData* aFindData = (PFindData*)hFindFile;

	if (aFindData->mWHandle != INVALID_HANDLE_VALUE)
		::FindClose(aFindData->mWHandle);

	delete aFindData;
	return TRUE;
}
