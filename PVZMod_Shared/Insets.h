#pragma once
#ifndef _PVZMOD_INSETS_H_
#define _PVZMOD_INSETS_H_

namespace PVZMod
{
	class Insets
	{
	public:
		int						mLeft;
		int						mTop;
		int						mRight;
		int						mBottom;

	public:
		Insets();
		Insets(int theLeft, int theTop, int theRight, int theBottom);
		Insets(const Insets& theInsets);
	};
}

#endif // !_PVZMOD_INSETS_H_
