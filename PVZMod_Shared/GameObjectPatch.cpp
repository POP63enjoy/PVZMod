#include "GameObjectPatch.h"
#include "PVZMod.h"
#include "Board.h"
#include "Graphics.h"
#include "GameButton.h"
#include "WidgetPatch.h"
#include "LawnApp.h"
#include "CursorObject.h"
#include "TodCommon.h"
#include "Challenge.h"
#include "Reanimator.h"
#include "TodParticle.h"
#include "Res.h"
#include "TodFoley.h"
#include "MagicBoard_private.h"

using namespace PVZMod;
using namespace GameObjectPatch;

void GameObjectPatch::FixBoardToolTipPos(InitPatch& patch)
{
	patch.PatchTask("GameObjectPatch::FixBoardToolTipPos", [&]
		{
			patch.mHook.InsertCode((void*)0x410472, [](Hook::Regs* regs)
				{
					Board* board = (Board*)regs->ebp;
					int& x = *(int*)&regs->ebx;
					int& y = *(int*)&regs->edi;
					auto absPos = board->GetAbsPos();
					x -= absPos.mX + *__MAGIC_BOARD_PRIVATE__::mvOffsetXPtr;
					y -= absPos.mY + *__MAGIC_BOARD_PRIVATE__::mvOffsetYPtr;
				}, 4);
		});
}

void GameObjectPatch::FixBoardCursorPos(InitPatch& patch)
{
	patch.PatchTask("GameObjectPatch::FixBoardCursorPos", [&]
		{
			patch.mHook.InsertCode((void*)0x40fa46, [](Hook::Regs* regs)
				{
					Board* board = (Board*)regs->edi;
					int& x = *(int*)&regs->esi;
					int& y = *(int*)&regs->ebx;
					auto absPos = board->GetAbsPos();
					x -= absPos.mX + *__MAGIC_BOARD_PRIVATE__::mvOffsetXPtr;
					y -= absPos.mY + *__MAGIC_BOARD_PRIVATE__::mvOffsetYPtr;
				});
		});
}

void GameObjectPatch::FixBoardHighlightPos(InitPatch& patch)
{
	patch.PatchTask("GameObjectPatch::FixBoardHighlightPos", [&]
		{
			patch.mHook.InsertCodeAndJump((void*)0x40fffb, (void*)0x410001, [](Hook::Regs* regs)
				{
					Board* board = (Board*)regs->edi;
					int& x = *(int*)&regs->ebx;
					int& y = *(int*)&regs->esi;
					auto absPos = board->GetAbsPos();
					x -= absPos.mX + *__MAGIC_BOARD_PRIVATE__::mvOffsetXPtr;
					y -= absPos.mY + *__MAGIC_BOARD_PRIVATE__::mvOffsetYPtr;
				});

			auto func = [](Hook::Regs* regs)
			{
				Board* board = (Board*)regs->edi;
				int& x = *(int*)&regs->eax;
				int& y = *(int*)&regs->edx;
				auto absPos = board->GetAbsPos();
				x -= absPos.mX + *__MAGIC_BOARD_PRIVATE__::mvOffsetXPtr;
				y -= absPos.mY + *__MAGIC_BOARD_PRIVATE__::mvOffsetYPtr;
			};

			patch.mHook.InsertCode((void*)0x410170, func);
			patch.mHook.InsertCode((void*)0x410197, func);
			patch.mHook.InsertCode((void*)0x41025d, func);
			patch.mHook.InsertCode((void*)0x410284, func);
			patch.mHook.InsertCode((void*)0x41032f, func);
			patch.mHook.InsertCode((void*)0x410350, func);
		});
}

void GameObjectPatch::FixBoardGameButtonParent(InitPatch& patch)
{
	patch.PatchTask("GameObjectPatch::FixBoardGameButtonParent", [&]
		{
			auto func = [](Hook::Regs* regs)
			{
				GameButton* menuButton = (GameButton*)regs->eax;
				Board* board = (Board*)regs->ebp;
				menuButton->mParentWidget = board;
			};

			patch.mHook.InsertCode((void*)0x409896, func); // MenuButton
			patch.mHook.InsertCode((void*)0x4099bb, func); // StoreButton
			patch.mHook.InsertCode((void*)0x409a4a, func); // LastStand
			patch.mHook.InsertCode((void*)0x409b0a, func); // Upsell
		});
}

void GameObjectPatch::FixCursorObjectPos(InitPatch& patch)
{
	patch.PatchTask("GameObjectPatch::FixCursorObjectPos", [&]
		{
			patch.mHook.InsertCode((void*)0x43a627, [](Hook::Regs* regs)
				{
					if (gLawnApp->mBoard)
					{
						CursorObject* curobj = (CursorObject*)regs->esi;
						auto boardPos = gLawnApp->mBoard->GetAbsPos();
						curobj->mX -= boardPos.mX + *__MAGIC_BOARD_PRIVATE__::mvOffsetXPtr;
						curobj->mY -= boardPos.mY + *__MAGIC_BOARD_PRIVATE__::mvOffsetYPtr;
					}
				});
		});
}

void GameObjectPatch::FixCursorPreviewPos(InitPatch& patch)
{
	patch.PatchTask("GameObjectPatch::FixCursorPreviewPos", [&]
		{
			patch.mHook.InsertCode((void*)0x43abf6, [](Hook::Regs* regs)
				{
					if (gLawnApp->mBoard)
					{
						int& x = *(int*)&regs->ebx;
						int& y = *(int*)&regs->edx;
						auto boardPos = gLawnApp->mBoard->GetAbsPos();
						x -= boardPos.mX + *__MAGIC_BOARD_PRIVATE__::mvOffsetXPtr;
						y -= boardPos.mY + *__MAGIC_BOARD_PRIVATE__::mvOffsetYPtr;
					}
				});
		});
}
