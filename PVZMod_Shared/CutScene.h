#pragma once
#ifndef _PVZMOD_CUT_SCENE_H_
#define _PVZMOD_CUT_SCENE_H_

namespace PVZMod
{
    class LawnApp;
    class Board;
    class ChallengeScreen;

    enum ReanimationID;

    /// 【游戏类】关卡过场。（原 ::CutScene）
    class CutScene
    {
    public:
        LawnApp*                    mApp;
        Board*                      mBoard;
        int                         mCutsceneTime;
        int                         mSodTime;
        int                         mGraveStoneTime;
        int                         mReadySetPlantTime;
        int                         mFogTime;
        int                         mBossTime;
        int                         mCrazyDaveTime;
        int                         mLawnMowerTime;
        int                         mCrazyDaveDialogStart;
        bool                        mSeedChoosing;
        ReanimationID               mZombiesWonReanimID;
        bool                        mPreloaded;
        bool                        mPlacedZombies;
        bool                        mPlacedLawnItems;
        int                         mCrazyDaveCountDown;
        int                         mCrazyDaveLastTalkIndex;
        bool                        mUpsellHideBoard;
        ChallengeScreen*            mUpsellChallengeScreen;
        bool                        mPreUpdatingBoard;

    public:
        CutScene();
        ~CutScene();
    };
}

#endif // !_PVZMOD_CUT_SCENE_H_
