#pragma once
#ifndef _PVZMOD_BASS_LOADER_H_
#define _PVZMOD_BASS_LOADER_H_

#include "bass.h"

namespace PVZMod
{
	/// ����Ϸ�ࡿbass.dll 2.2 �ӿڡ���ԭ `Sexy::BASS_INSTANCE`��
	struct BASS_INSTANCE
	{
		BASS_INSTANCE(const char* dllName) = delete;
		virtual ~BASS_INSTANCE();

		BOOL BASS_MusicSetAmplify(HMUSIC handle, DWORD amp);
		BOOL BASS_MusicPlay(HMUSIC handle);
		BOOL BASS_MusicPlayEx(HMUSIC handle, DWORD pos, int flags, BOOL reset);
		BOOL BASS_ChannelResume(DWORD handle);
		BOOL BASS_StreamPlay(HSTREAM handle, BOOL flush, DWORD flags);

		HMODULE		 mModule;
		bool			mVersion2;

		DWORD(WINAPI* BASS_GetVersion)();

		BOOL(WINAPI* BASS_Init)(int device, DWORD freq, DWORD flags, HWND win);
		BOOL(WINAPI* BASS_Init2)(int device, DWORD freq, DWORD flags, HWND win, GUID* clsid);
		void(WINAPI* BASS_Free)();
		BOOL(WINAPI* BASS_Stop)();
		BOOL(WINAPI* BASS_Start)();
		void(WINAPI* BASS_SetGlobalVolumes)(int musvol, int samvol, int strvol);
		BOOL(WINAPI* BASS_SetVolume)(DWORD volume);
		DWORD(WINAPI* BASS_GetVolume)();
		BOOL(WINAPI* BASS_GetInfo)(BASS_INFO* info);

		DWORD(WINAPI* BASS_SetConfig)(DWORD option, DWORD value);
		DWORD(WINAPI* BASS_GetConfig)(DWORD option);

		BOOL(WINAPI* BASS_ChannelStop)(DWORD handle);
		BOOL(WINAPI* BASS_ChannelPlay)(DWORD handle, BOOL restart);
		BOOL(WINAPI* BASS_ChannelPause)(DWORD handle);
		BOOL(WINAPI* BASS_ChannelSetAttributes)(DWORD handle, int freq, int volume, int pan);
		BOOL(WINAPI* BASS_ChannelGetAttributes)(DWORD handle, DWORD* freq, DWORD* volume, int* pan);
		BOOL(WINAPI* BASS_ChannelSetPosition)(DWORD handle, QWORD pos);
		QWORD(WINAPI* BASS_ChannelGetPosition)(DWORD handle);
		BOOL(WINAPI* BASS_ChannelSetFlags)(DWORD handle, DWORD flags);
		DWORD(WINAPI* BASS_ChannelIsActive)(DWORD handle);
		BOOL(WINAPI* BASS_ChannelSlideAttributes)(DWORD handle, int freq, int volume, int pan, DWORD time);
		DWORD(WINAPI* BASS_ChannelIsSliding)(DWORD handle);
		DWORD(WINAPI* BASS_ChannelGetLevel)(DWORD handle);
		HFX(WINAPI* BASS_ChannelSetFX)(DWORD handle, DWORD theType, int priority);
		BOOL(WINAPI* BASS_ChannelRemoveFX)(DWORD handle, HFX fx);
		QWORD(WINAPI* BASS_ChannelGetLength)(DWORD handle);
		DWORD(WINAPI* BASS_ChannelGetData)(DWORD handle, void* buffer, DWORD length);
		BOOL(WINAPI* BASS_ChannelPreBuf)(DWORD handle, DWORD length);
		HSYNC(WINAPI* BASS_ChannelSetSync)(DWORD handle, DWORD theType, QWORD theParam, SYNCPROC* proc, DWORD user);
		BOOL(WINAPI* BASS_ChannelRemoveSync)(DWORD handle, HSYNC sync);

		HMUSIC(WINAPI* BASS_MusicLoad)(BOOL mem, void* file, DWORD offset, DWORD length, DWORD flags);
		HMUSIC(WINAPI* BASS_MusicLoad2)(BOOL mem, void* file, DWORD offset, DWORD length, DWORD flags, DWORD freq);
		void(WINAPI* BASS_MusicFree)(HMUSIC handle);

		HSTREAM(WINAPI* BASS_StreamCreateFile)(BOOL mem, void* file, DWORD offset, DWORD length, DWORD flags);
		void(WINAPI* BASS_StreamFree)(HSTREAM handle);

		BOOL(WINAPI* BASS_FXSetParameters)(HFX handle, void* par);
		BOOL(WINAPI* BASS_FXGetParameters)(HFX handle, void* par);

		DWORD(WINAPI* BASS_MusicGetAttribute)(DWORD handle, DWORD attrib);
		void(WINAPI* BASS_MusicSetAttribute)(DWORD handle, DWORD attrib, DWORD value);

		DWORD(WINAPI* BASS_MusicGetOrders)(HMUSIC handle);
		DWORD(WINAPI* BASS_MusicGetOrderPosition)(HMUSIC handle);

		HPLUGIN(WINAPI* BASS_PluginLoad)(char* file);

		HSAMPLE(WINAPI* BASS_SampleLoad)(BOOL mem, void* file, DWORD offset, DWORD length, DWORD max, DWORD flags);
		BOOL(WINAPI* BASS_SampleFree)(HSAMPLE handle);
		BOOL(WINAPI* BASS_SampleSetInfo)(HSAMPLE handle, BASS_SAMPLE* info);
		BOOL(WINAPI* BASS_SampleGetInfo)(HSAMPLE handle, BASS_SAMPLE* info);
		HCHANNEL(WINAPI* BASS_SampleGetChannel)(HSAMPLE handle, BOOL onlynew);
		BOOL(WINAPI* BASS_SampleStop)(HSAMPLE handle);

		int (WINAPI* BASS_ErrorGetCode)();

	protected:
		BASS_INSTANCE() {};	// for wrapper
	};

	extern BASS_INSTANCE*& gBass;
}

#endif // !_PVZMOD_BASS_LOADER_H_
