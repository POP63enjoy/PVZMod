#include "Attachment.h"

using namespace PVZMod;

AttachEffect* PVZMod::AttachReanim(AttachmentID* theAttachmentID, Reanimation* theReanimation, float theOffsetX, float theOffsetY)
{
	int func = 0x406B80;
	AttachEffect* result;
	__asm
	{
		mov esi, theReanimation
		mov edi, theAttachmentID
		push theOffsetY
		push theOffsetX
		call func
		add esp, 0x8
		mov result, eax
	}
	return result;
}
