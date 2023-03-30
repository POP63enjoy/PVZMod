#include "Reanimator.h"
#include "TodCommon.h"
#include "Definition.h"
#include "Attachment.h"

using namespace PVZMod;

ReanimatorTransform::ReanimatorTransform() :
	mTransX(DEFAULT_FIELD_PLACEHOLDER),
	mTransY(DEFAULT_FIELD_PLACEHOLDER),
	mSkewX(DEFAULT_FIELD_PLACEHOLDER),
	mSkewY(DEFAULT_FIELD_PLACEHOLDER),
	mScaleX(DEFAULT_FIELD_PLACEHOLDER),
	mScaleY(DEFAULT_FIELD_PLACEHOLDER),
	mFrame(DEFAULT_FIELD_PLACEHOLDER),
	mAlpha(DEFAULT_FIELD_PLACEHOLDER),
	mImage(nullptr),
	mFont(nullptr),
	mText("") { }

ReanimatorTrackInstance::ReanimatorTrackInstance()
{
	mBlendCounter = 0;
	mBlendTime = 0;
	mShakeOverride = 0.0f;
	mShakeX = 0.0f;
	mShakeY = 0.0f;
	mAttachmentID = AttachmentID::ATTACHMENTID_NULL;
	mRenderGroup = RENDER_GROUP_NORMAL;
	mIgnoreClipRect = false;
	mImageOverride = nullptr;
	mTruncateDisappearingFrames = true;
	mTrackColor = Color::White;
	mIgnoreColorOverride = false;
	mIgnoreExtraAdditiveColor = false;
}

Reanimation::Reanimation()
{
	mAnimTime = 0;
	mAnimRate = 12.0f;
	mDefinition = nullptr;
	mLoopType = ReanimLoopType::REANIM_PLAY_ONCE;
	mLastFrameTime = -1.0f;
	mDead = false;
	mFrameStart = 0;
	mFrameCount = 0;
	mFrameBasePose = -1;
	mOverlayMatrix.LoadIdentity();
	mColorOverride = Color::White;
	mExtraAdditiveColor = Color::White;
	mEnableExtraAdditiveDraw = false;
	mExtraOverlayColor = Color::White;
	mEnableExtraOverlayDraw = false;
	mLoopCount = 0;
	mIsAttachment = false;
	mRenderOrder = 0;
	mReanimationHolder = nullptr;
	mTrackInstances = nullptr;
	mFilterEffect = FilterEffect::FILTER_EFFECT_NONE;
	mReanimationType = ReanimationType::REANIM_NONE;
}

Reanimation::~Reanimation()
{
	ReanimationDie();
	ReanimationDelete();
}

void Reanimation::ReanimationDie()
{
	int func = 0x476f70;
	__asm
	{
		mov ecx, this
		call func
	}
}

void Reanimation::ReanimationDelete()
{
	assert(mDead);
	if (mTrackInstances != nullptr)
	{
		int aItemSize = mDefinition->mTrackCount * sizeof(ReanimatorTrackInstance);
		FindGlobalAllocator(aItemSize)->Free(mTrackInstances, aItemSize);  // 由 TodAllocator 回收动画轨道的内存区域
		mTrackInstances = nullptr;
	}
}

void Reanimation::Draw(Graphics* g)
{
	DrawRenderGroup(g, RENDER_GROUP_NORMAL);
}

void Reanimation::DrawRenderGroup(Graphics* g, int theRenderGroup)
{
	int func = 0x4769c0;
	__asm
	{
		push theRenderGroup
		push g
		mov ecx,this
		call func
	}
}

int Reanimation::FindTrackIndex(const char* theTrackName)
{
	int func = 0x476AB0;
	int result;
	__asm
	{
		mov ebx, this
		push theTrackName
		call func
		mov result, eax
	}
	return result;
}

ReanimatorTrackInstance* Reanimation::GetTrackInstanceByName(const char* theTrackName)
{
	return &mTrackInstances[FindTrackIndex(theTrackName)];
}

void Reanimation::SetFramesForLayer(const char* theTrackName)
{
	int func = 0x476E00;
	__asm
	{
		mov ecx, this
		push theTrackName
		call func
	}
}

void Reanimation::PlayReanim(const char* theTrackName, ReanimLoopType theLoopType, int theBlendTime, float theAnimRate)
{
	int func = 0x477790;
	__asm
	{
		mov eax, theBlendTime
		mov esi,this
		push theAnimRate
		push theLoopType
		push theTrackName
		call func
	}
}

void Reanimation::AttachToAnotherReanimation(Reanimation* theAttachReanim, const char* theTrackName)
{
	int func = 0x476b00;
	__asm
	{
		mov edx, theTrackName
		mov eax, theAttachReanim
		mov esi, this
		call func
	}
}

void Reanimation::AssignRenderGroupToTrack(const char* theTrackName, int theRenderGroup)
{
	int func = 0x477580;
	__asm
	{
		push theRenderGroup
		push theTrackName
		mov ebx, this
		call func
	}
}

void Reanimation::AssignRenderGroupToPrefix(const char* theTrackName, int theRenderGroup)
{
	int func = 0x4775e0;
	__asm
	{
		push theRenderGroup
		push theTrackName
		push this
		call func
	}
}

void Reanimation::GetFramesForLayer(const char* theTrackName, int& theFrameStart, int& theFrameCount)
{
	int func = 0x476d50;
	__asm
	{
		push theFrameCount
		push theFrameStart
		mov edx, theTrackName
		mov eax, this
		call func
	}
}

bool Reanimation::TrackExists(const char* theTrackName)
{
	for (int aTrackIndex = 0; aTrackIndex < mDefinition->mTrackCount; aTrackIndex++)
		if (_stricmp(mDefinition->mTracks[aTrackIndex].mName, theTrackName) == 0)
			return true;
	return false;
}

void Reanimation::SetTruncateDisappearingFrames(const char* theTrackName, bool theTruncateDisappearingFrames)
{
	if (theTrackName == nullptr)  // 若给出的轨道名称为空指针
	{
		for (int aTrackIndex = 0; aTrackIndex < mDefinition->mTrackCount; aTrackIndex++)  // 依次设置每一轨道
			mTrackInstances[aTrackIndex].mTruncateDisappearingFrames = theTruncateDisappearingFrames;
	}
	else
		GetTrackInstanceByName(theTrackName)->mTruncateDisappearingFrames = theTruncateDisappearingFrames;
}