#pragma once
#include "Buffer.h"

namespace PVZMod
{
	class ReanimatorDefinition;
	class TodParticleDefinition;
	class TrailDefinition;
	class Image;
	class Board;
	class TodParticleSystem;
	class Reanimation;
	class Trail;

	class SaveGameContext
	{
	public:
		Buffer			mBuffer;
		bool			mFailed;
		bool			mReading;

	public:
		int			ByteLeftToRead();
		void		SyncBytes(void* theDest, int theReadSize);
		void		SyncInt(int& theInt);
		void		SyncInt(unsigned int& theInt);
		void		SyncReanimationDef(ReanimatorDefinition*& theDefinition);
		void		SyncParticleDef(TodParticleDefinition*& theDefinition);
		void		SyncTrailDef(TrailDefinition*& theDefinition);
		void		SyncImage(Image*& theImage);
	};

	void                SyncParticleSystem(Board* theBoard, TodParticleSystem* theParticleSystem, SaveGameContext& theContext);
	void                SyncReanimation(Board* theBoard, Reanimation* theReanimation, SaveGameContext& theContext);
	void                SyncTrail(Board* theBoard, Trail* theTrail, SaveGameContext& theContext);
}
