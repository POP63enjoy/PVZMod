#pragma once
#ifndef _PVZMOD_FOLDER_MAPPING_INTERFACE_H_
#define _PVZMOD_FOLDER_MAPPING_INTERFACE_H_

#include "PakInterface.h"
#include <variant>

namespace PVZMod
{
	/// 文件夹映射接口，可取代 PakInterface。
	class FolderMappingInterface :public PakInterfaceBase
	{
	public:
		class Pak :public PakInterface
		{
		public:
			Pak(const String& pakFile);
			Pak(HMODULE theModule, const String& theName, const char* theResName, const char* theResType);
		};

		using Folder = String;
		using FolderList = std::list<std::variant<Pak*, Folder>>;

		struct PFindData :PVZMod::PFindData
		{
			FolderList::iterator	mIter;
		};

		FolderList	mFolderList;

	public:
		FolderMappingInterface();
		virtual ~FolderMappingInterface();

		virtual void			MF_LoadPak();

		virtual PFILE*			FOpen(const char* theFileName, const char* theAccess);
		virtual int				FClose(PFILE* theFile);
		virtual int				FSeek(PFILE* theFile, long theOffset, int theOrigin);
		virtual int				FTell(PFILE* theFile);
		virtual size_t			FRead(void* thePtr, int theElemSize, int theCount, PFILE* theFile);
		virtual int				FGetC(PFILE* theFile);
		virtual int				UnGetC(int theChar, PFILE* theFile);
		virtual char*			FGetS(char* thePtr, int theSize, PFILE* theFile);
		virtual int				FEof(PFILE* theFile);

		virtual HANDLE			FindFirstFileA(const char* lpFileName, LPWIN32_FIND_DATAA lpFindFileData);
		virtual BOOL			FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData);
		virtual BOOL			FindClose(HANDLE hFindFile);
	};
}

#endif // !_PVZMOD_FOLDER_MAPPING_INTERFACE_H_
