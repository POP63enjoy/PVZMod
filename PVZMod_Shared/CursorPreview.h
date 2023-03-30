#pragma once
#ifndef _PVZMOD_CURSOR_PREVIEW_H_
#define _PVZMOD_CURSOR_PREVIEW_H_

#include "GameObject.h"

namespace PVZMod
{
	/// 【游戏类】光标预览。（原 ::CursorPreview）
	class CursorPreview : public GameObject
	{
	public:
		int mGridX;
		int mGridY;
	};
}

#endif // !_PVZMOD_CURSOR_PREVIEW_H_
