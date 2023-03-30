#include "WidgetPatch.h"
#include "PVZMod.h"
#include "Board.h"
#include "LawnApp.h"
#include "MagicBoard.h"

using namespace PVZMod;

void WidgetPatch::FixGameButtonClickPos(InitPatch& patch)
{
	patch.PatchTask("WidgetPatch::FixGameButtonClickPos", [&]
		{
			patch.mHook.InsertCodeAndJump((void*)0x44a6a0, (void*)0x44a6a6, [](Hook::Regs* regs)
				{
					WidgetContainer* parent = (WidgetContainer*)regs->ebp;
					int& x = *(int*)&regs->edx;
					int& y = *(int*)&regs->eax;
					auto parentPos = parent->GetAbsPos();
					x -= parentPos.mX;
					y -= parentPos.mY;
					if (parent == gLawnApp->mBoard)
					{
						x -= *MagicBoard::mvOffsetXPtr;
						y -= *MagicBoard::mvOffsetYPtr;
					}
				});
		});
}
