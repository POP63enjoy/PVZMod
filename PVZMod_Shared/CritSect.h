#pragma once
#ifndef _PVZMOD_CRIT_SECT_H_
#define _PVZMOD_CRIT_SECT_H_

#include <windows.h>

namespace PVZMod
{
	/// 【游戏类】线程锁对象（原 Sexy::CritSect）
	class CritSect
	{
	private:
		CRITICAL_SECTION mCriticalSection;
		friend class AutoCrit;

	public:
		CritSect(void);
		~CritSect(void);
	};
}

#endif // !_PVZMOD_CRIT_SECT_H_
