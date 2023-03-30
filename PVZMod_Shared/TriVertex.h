#pragma once
#ifndef _PVZMOD_TRI_VERTEX_H_
#define _PVZMOD_TRI_VERTEX_H_

#include <Windows.h>

namespace PVZMod
{
	/// 【游戏类】三角形顶点（原 Sexy::TriVertex）
	class TriVertex
	{
	public:
		float x, y, u, v;
		DWORD color; //ARGB (0 = use color specified in function call)

	public:
		TriVertex() { color = 0; }
		TriVertex(float theX, float theY) : x(theX), y(theY) { color = 0; }
		TriVertex(float theX, float theY, float theU, float theV) : x(theX), y(theY), u(theU), v(theV) { color = 0; }
		TriVertex(float theX, float theY, float theU, float theV, DWORD theColor) : x(theX), y(theY), u(theU), v(theV), color(theColor) { }
	};
}

#endif // !_PVZMOD_TRI_VERTEX_H_
