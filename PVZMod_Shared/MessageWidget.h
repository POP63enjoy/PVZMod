#pragma once
#include "SexyCommon.h"

namespace PVZMod
{
	constexpr size_t MAX_MESSAGE_LENGTH = 128;

	enum MessageStyle
	{
		MESSAGE_STYLE_OFF,
		MESSAGE_STYLE_TUTORIAL_LEVEL1,
		MESSAGE_STYLE_TUTORIAL_LEVEL1_STAY,
		MESSAGE_STYLE_TUTORIAL_LEVEL2,
		MESSAGE_STYLE_TUTORIAL_LATER,
		MESSAGE_STYLE_TUTORIAL_LATER_STAY,
		MESSAGE_STYLE_HINT_LONG,
		MESSAGE_STYLE_HINT_FAST,
		MESSAGE_STYLE_HINT_STAY,
		MESSAGE_STYLE_HINT_TALL_FAST,
		MESSAGE_STYLE_HINT_TALL_UNLOCKMESSAGE,
		MESSAGE_STYLE_HINT_TALL_LONG,
		MESSAGE_STYLE_BIG_MIDDLE,
		MESSAGE_STYLE_BIG_MIDDLE_FAST,
		MESSAGE_STYLE_HOUSE_NAME,
		MESSAGE_STYLE_HUGE_WAVE,
		MESSAGE_STYLE_SLOT_MACHINE,
		MESSAGE_STYLE_ZEN_GARDEN_LONG
	};

	class LawnApp;
	enum ReanimationID;
	enum ReanimationType;

	class MessageWidget
	{
	public:
		LawnApp*			mApp;
		SexyChar			mLabel[MAX_MESSAGE_LENGTH];
		int					mDisplayTime;
		int					mDuration;
		MessageStyle		mMessageStyle;
		ReanimationID		mTextReanimID[MAX_MESSAGE_LENGTH];
		ReanimationType		mReanimType;
		int					mSlideOffTime;
		SexyChar			mLabelNext[MAX_MESSAGE_LENGTH];
		MessageStyle		mMessageStyleNext;
	};
}