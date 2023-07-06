#pragma once
#ifndef _PVZMOD_PAKINTERFACE_H_
#define _PVZMOD_PAKINTERFACE_H_

#include "PVZSTL.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace PVZMod
{

class PakCollection;

class PakRecord
{
public:
	PakCollection*			mCollection = nullptr;
	String					mFileName;
	FILETIME				mFileTime;
	int						mStartPos;
	int						mSize;	
};

typedef Map<String, PakRecord> PakRecordMap;

class PakCollection
{
public:
	HANDLE					mFileHandle;
	HANDLE					mMappingHandle;
	void*					mDataPtr;
};

typedef List<PakCollection> PakCollectionList;

struct PFILE
{
	PakRecord*				mRecord;
	int						mPos;
	FILE*					mFP;
};

struct PFindData
{
	HANDLE					mWHandle;
	String					mLastFind;
	String					mFindCriteria;
};

class PakInterfaceBase
{
public:
	virtual PFILE*			FOpen(const char* theFileName, const char* theAccess) = 0;
	virtual PFILE*			FOpen(const wchar_t* theFileName, const wchar_t* theAccess) { return NULL; }
	virtual int				FClose(PFILE* theFile) = 0;
	virtual int				FSeek(PFILE* theFile, long theOffset, int theOrigin) = 0;
	virtual int				FTell(PFILE* theFile) = 0;
	virtual size_t			FRead(void* thePtr, int theElemSize, int theCount, PFILE* theFile) = 0;
	virtual int				FGetC(PFILE* theFile) = 0;
	virtual int				UnGetC(int theChar, PFILE* theFile) = 0;
	virtual char*			FGetS(char* thePtr, int theSize, PFILE* theFile) = 0;
	virtual wchar_t*		FGetS(wchar_t* thePtr, int theSize, PFILE* theFile) { return thePtr; }
	virtual int				FEof(PFILE* theFile) = 0;

	virtual HANDLE			FindFirstFileA(const char* lpFileName, LPWIN32_FIND_DATAA lpFindFileData) = 0;	
	virtual BOOL			FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData) = 0;
	virtual BOOL			FindClose(HANDLE hFindFile) = 0;
};

class PakInterface :public PakInterfaceBase
{
public:
	PakCollectionList		mPakCollectionList;	
	PakRecordMap			mPakRecordMap;

public:
	bool					PFindNext(PFindData* theFindData, LPWIN32_FIND_DATAA lpFindFileData);

public:
	PakInterface();
	~PakInterface();

	bool					AddPakFile(const String& theFileName);
	bool					AddPakRes(HMODULE theModule, const String& theName, const char* theResName, const char* theResType);
	PFILE*					FOpen(const char* theFileName, const char* theAccess);
	int						FClose(PFILE* theFile);
	int						FSeek(PFILE* theFile, long theOffset, int theOrigin);
	int						FTell(PFILE* theFile);
	size_t					FRead(void* thePtr, int theElemSize, int theCount, PFILE* theFile);
	int						FGetC(PFILE* theFile);
	int						UnGetC(int theChar, PFILE* theFile);
	char*					FGetS(char* thePtr, int theSize, PFILE* theFile);
	int						FEof(PFILE* theFile);

	HANDLE					FindFirstFileA(const char* lpFileName, LPWIN32_FIND_DATAA lpFindFileData);
	BOOL					FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData);
	BOOL					FindClose(HANDLE hFindFile);
};

extern PakInterfaceBase* gPakInterfaceBase;
extern PakInterface* gPakInterface;

static PFILE* p_fopen(const char* theFileName, const char* theAccess) 
{
	if (gPakInterfaceBase)
		return gPakInterfaceBase->FOpen(theFileName, theAccess);
	FILE* aFP = nullptr;
	fopen_s(&aFP, theFileName, theAccess);
	if (aFP == nullptr)
		return nullptr;
	PFILE* aPFile = new PFILE();
	aPFile->mRecord = nullptr;
	aPFile->mPos = 0;
	aPFile->mFP = aFP;
	return aPFile;
}

static PFILE* p_fopen(const wchar_t* theFileName, const wchar_t* theAccess) 
{
	if (gPakInterfaceBase)
		return gPakInterfaceBase->FOpen(theFileName, theAccess);
	FILE* aFP = nullptr;
	_wfopen_s(&aFP, theFileName, theAccess);
	if (aFP == nullptr)
		return nullptr;
	PFILE* aPFile = new PFILE();
	aPFile->mRecord = nullptr;
	aPFile->mPos = 0;
	aPFile->mFP = aFP;
	return aPFile;
}

static int p_fclose(PFILE* theFile)
{
	if (gPakInterfaceBase)
		return gPakInterfaceBase->FClose(theFile);
	int aResult = fclose(theFile->mFP);
	delete theFile;
	return aResult;
}

static int p_fseek(PFILE* theFile, long theOffset, int theOrigin)
{
	if (gPakInterfaceBase)
		return gPakInterfaceBase->FSeek(theFile, theOffset, theOrigin);
	return fseek(theFile->mFP, theOffset, theOrigin);
}

static int p_ftell(PFILE* theFile)
{
	if (gPakInterfaceBase)
		return gPakInterfaceBase->FTell(theFile);
	return ftell(theFile->mFP);
}

static size_t p_fread(void* thePtr, int theSize, int theCount, PFILE* theFile)
{
	if (gPakInterfaceBase)
		return gPakInterfaceBase->FRead(thePtr, theSize, theCount, theFile);
	return fread(thePtr, theSize, theCount, theFile->mFP);
}

static size_t p_fwrite(const void* thePtr, int theSize, int theCount, PFILE* theFile)
{	
	if (theFile->mFP == NULL)
		return 0;
	return fwrite(thePtr, theSize, theCount, theFile->mFP);
}

static int p_fgetc(PFILE* theFile)
{
	if (gPakInterfaceBase)
		return gPakInterfaceBase->FGetC(theFile);
	return fgetc(theFile->mFP);
}

static int p_ungetc(int theChar, PFILE* theFile)
{
	if (gPakInterfaceBase)
		return gPakInterfaceBase->UnGetC(theChar, theFile);
	return ungetc(theChar, theFile->mFP);
}

static char* p_fgets(char* thePtr, int theSize, PFILE* theFile)
{
	if (gPakInterfaceBase)
		return gPakInterfaceBase->FGetS(thePtr, theSize, theFile);
	return fgets(thePtr, theSize, theFile->mFP);
}

static wchar_t* p_fgets(wchar_t* thePtr, int theSize, PFILE* theFile)
{
	if (gPakInterfaceBase)
		return gPakInterfaceBase->FGetS(thePtr, theSize, theFile);
	return fgetws(thePtr, theSize, theFile->mFP);
}

static int p_feof(PFILE* theFile)
{
	if (gPakInterfaceBase)
		return gPakInterfaceBase->FEof(theFile);
	return feof(theFile->mFP);
}

static HANDLE p_FindFirstFileA(const char* lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
	if (gPakInterfaceBase)
		return gPakInterfaceBase->FindFirstFileA(lpFileName, lpFindFileData);
	return FindFirstFileA(lpFileName, lpFindFileData);
}

static BOOL p_FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData)
{
	if (gPakInterfaceBase)
		return gPakInterfaceBase->FindNextFileA(hFindFile, lpFindFileData);
	return FindNextFileA(hFindFile, lpFindFileData);
}

static BOOL p_FindClose(HANDLE hFindFile)
{
	if (gPakInterfaceBase)
		return gPakInterfaceBase->FindClose(hFindFile);
	return FindClose(hFindFile);
}
}

#endif // !_PVZMOD_PAKINTERFACE_H_
