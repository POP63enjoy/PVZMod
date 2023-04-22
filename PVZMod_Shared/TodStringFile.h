#pragma once
#ifndef _PVZMOD_TOD_STRING_FILE_H_
#define _PVZMOD_TOD_STRING_FILE_H_

#include "SexyCommon.h"

namespace PVZMod
{
	/// 【游戏函数】读取 TodString 文本。（原 `::%TodStringListReadItems`）
	///
	/// @param theFileText	TodString 文本。
	/// @result				为 false 则读取失败。
	bool				TodStringListReadItems(const SexyChar* theFileText);

	/// 【游戏函数】读取 TodString 文件。（原 `::%TodStringListReadFile`）
	///
	/// @param theFileName	文件名。
	/// @result				为 false 则读取失败。
	bool				TodStringListReadFile(const char* theFileName);

	/// 【游戏函数】加载 TodString 文件，加载失败则弹出消息框。（原 `::%TodStringListLoad`）
	///
	/// @param theFileName	文件名。
	void                TodStringListLoad(const char* theFileName);

	/// 【游戏函数】查询 TodString 项对应字符串。（原 `::%TodStringListFind`）
	///
	/// @param theName	TodString 项名称，不包括中括号。
	/// @return			对应的字符串，如果不存在，则返回 "<Missing %s>" 。
	SexyString          TodStringListFind(const SexyString& theName);

	/// 【游戏函数】解析 TodString。（原 `::%TodStringTranslate`）
	///
	/// @param theName	带中括号的 TodString 项名称或普通字符串。
	/// @return			如果 theName 是带有中括号的 TodString 项，则返回 TodStringListFind 查询的结果；如果是普通字符串，则返回字符串本身。
	SexyString			TodStringTranslate(const SexyString& theString);

	/// 【游戏函数】解析 TodString。（原 `::%TodStringTranslate`）
	///
	/// @param theName	带中括号的 TodString 项名称或普通字符串。
	/// @return			如果 theName 是带有中括号的 TodString 项，则返回 TodStringListFind 查询的结果；如果是普通字符串，则返回字符串本身。
	SexyString			TodStringTranslate(const SexyChar* theString);

	/// 【游戏函数】查询 TodString 项是否存在。（原 `::%TodStringListExists`）
	///
	/// @param theName	TodString 项名称，包括中括号。
	/// @return			如果 TodString 项不存在或 theName 不包括中括号，返回 false，否则返回 true。
	bool                TodStringListExists(const SexyString& theString);
}

#endif // !_PVZMOD_TOD_STRING_FILE_H_
