#pragma once
#ifndef _PVZMOD_SEXY_COMMON_H_
#define _PVZMOD_SEXY_COMMON_H_

#include "PVZSTL.h"
#include <Windows.h>

#define _USE_WIDE_STRING

namespace PVZMod
{
	/// 【游戏类】默认字符串类型（原 `::%SexyString`）。
	using SexyString = WString;
	/// 【游戏类】默认字符类型（原 `::%SexyChar`）。
	using SexyChar = wchar_t;

	using DefinesMap = Map<String, String>;

#define _S(str) L##str
	constexpr auto sexystrncmp	= wcsncmp;
	constexpr auto sexystrcmp	= wcscmp;
	constexpr auto sexystricmp	= wcsicmp;
	constexpr auto sexysscanf	= swscanf;
	constexpr auto sexyatoi		= _wtoi;
	constexpr auto sexystrcpy	= wcscpy;
	constexpr auto sexystrlen	= wcslen;

	struct StringLessNoCase { bool operator()(const String& s1, const String& s2) const { return _stricmp(s1.c_str(), s2.c_str()) < 0; } };

	struct WStringLessNoCase { bool operator()(const WString& s1, const WString& s2) const { return _wcsicmp(s1.c_str(), s2.c_str()) < 0; } };

	using SexyStringLessNoCase = WStringLessNoCase;

	bool				Deltree(const String& thePath);
	bool				FileExists(const String& theFileName);
	void				MkDir(const String& theDir);

	String				vformat(const char* fmt, va_list argPtr);
	WString				vformat(const wchar_t* fmt, va_list argPtr);
	String				StrFormat(const char* fmt ...);
	WString				StrFormat(const wchar_t* fmt ...);


	constexpr uint32_t SEXY_RAND_MAX = 0x7FFFFFFF;
	int					Rand();
	int					Rand(int range);
	float				Rand(float range);
	void				SRand(uint32_t theSeed);

	WString				StringToWString(const String& theString);
	String				WStringToString(const WString& theString);
	SexyString			StringToSexyString(const String& theString);
	SexyString			WStringToSexyString(const WString& theString);
	String				SexyStringToString(const SexyString& theString);
	WString				SexyStringToWString(const SexyString& theString);

	String				StringToUpper(const String& theString);
	WString				StringToUpper(const WString& theString);
	String				StringToLower(const String& theString);
	WString				StringToLower(const WString& theString);
}

#endif // !_PVZMOD_SEXY_COMMON_H_
