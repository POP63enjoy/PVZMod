#include "BassLoader.h"

using namespace PVZMod;

BASS_INSTANCE*& PVZMod::gBass = *(BASS_INSTANCE**)0x6BA110;

BASS_INSTANCE::~BASS_INSTANCE()
{
	if (mModule)
		FreeLibrary(mModule);
}

BOOL BASS_INSTANCE::BASS_MusicSetAmplify(HMUSIC handle, DWORD amp)
{
	BASS_MusicSetAttribute(handle, BASS_MUSIC_ATTRIB_AMPLIFY, amp);
	return true;
}


BOOL BASS_INSTANCE::BASS_MusicPlay(HMUSIC handle)
{
	return BASS_ChannelPlay(handle, true);
}


BOOL BASS_INSTANCE::BASS_MusicPlayEx(HMUSIC handle, DWORD pos, int flags, BOOL reset)
{
	int anOffset = MAKEMUSICPOS(pos, 0);

	BASS_ChannelStop(handle);
	BASS_ChannelSetPosition(handle, anOffset);
	BASS_ChannelSetFlags(handle, flags);

	return BASS_ChannelPlay(handle, false/*reset*/);
}


BOOL BASS_INSTANCE::BASS_ChannelResume(DWORD handle)
{
	return BASS_ChannelPlay(handle, false);
}

BOOL BASS_INSTANCE::BASS_StreamPlay(HSTREAM handle, BOOL flush, DWORD flags)
{
	BASS_ChannelSetFlags(handle, flags);
	return BASS_ChannelPlay(handle, flush);
}