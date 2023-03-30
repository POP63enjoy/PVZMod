#include "BassMusicInterface.h"

using namespace PVZMod;

BassMusicInfo::BassMusicInfo()
{
	mVolume = 0.0;
	mVolumeAdd = 0.0;
	mVolumeCap = 1.0;
	mStopOnFade = false;
	mHMusic = NULL;
	mHStream = NULL;
}