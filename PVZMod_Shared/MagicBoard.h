#pragma once
#ifndef _PVZMOD_MAGIC_BOARD_H_
#define _PVZMOD_MAGIC_BOARD_H_

#ifndef _PVZMOD_BOARD_H_
#error ������ #include <MagicBoard.h> ֮ǰ #include <Board.h> ��
#endif // !_PVZMOD_BOARD_H_

#include "Magic.h"
#include "SexyCommon.h"
#include <optional>

namespace PVZMod
{
	class InitPatch;
	class Board;
	class LawnApp;
	class ZombiePicker;
	class SaveGameContext;
	enum GameMode;

	/// `Board` ħ����Ա��չ��
	namespace MagicBoard
	{
		/// ��ħ����ע���������
		template <typename BaseClass>
		class RegisterManager
		{
		public:
			/// ������������ע���Թؿ�Ϊ�ж���������ħ���ࡣ
			///
			/// @tparam LevelClass				��ħ���࣬�̳��� BaseClass���������幹�캯���������������麯�����Ǿ�̬��Ա������
			/// @param patch					��������
			/// @param theLevelId				�ؿ���š�
			/// @param enableMultipleRegister	Ϊ true �������ظ�ע����ͬ���ࡣ��������ͨ�� MT_Ref ���õ��ࣩ
			template <typename LevelClass>
			static RegisterManager RegisterLevel(InitPatch& patch, GameMode theLevelId, bool enableMultipleRegister = false);
		};

		/// ������������Ϊ Board ע����ħ���ࡣ
		///
		/// @tparam T		��ħ���࣬�̳��� Board���������幹�캯���������������麯����
		/// @param patch	��������
		/// @return			����ע����ħ���ࡣ
		template<typename T>
		RegisterManager<T> RegisterMain(InitPatch& patch);

		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////

		// ������Ϣ��

		void Binding_ExtendBase(InitPatch& patch, size_t theBoardSize, bool autoSaveExtendedData);

		// ���캯������������ - MF_Constructor��MF_Destructor

		using Constructor_t = Magic::BaseFunction<void(Board* _this, LawnApp* theApp)>;
		void Binding_MF_Constructor(InitPatch& patch, const std::function<void(Board* _this, LawnApp* theApp, Constructor_t& base)>& func);
		
		using Destructor_t = Magic::BaseFunction<void(Board* _this)>;
		void Binding_MF_Destructor(InitPatch& patch, const std::function<void(Board* _this, Destructor_t& base)>& func);

		// �ؿ���Ϣ��ʼ�� - MF_InitLevel

		using InitLevel_t = Magic::BaseFunction<void(Board* _this)>;
		void Binding_MF_InitLevel(InitPatch& patch, const std::function<void(Board* _this, InitLevel_t& base)>& func);

		// �ͷ���Դ - MF_DisposeBoard

		using DisposeBoard_t = Magic::BaseFunction<void(Board* _this)>;
		void Binding_MF_DisposeBoard(InitPatch& patch, const std::function<void(Board* _this, DisposeBoard_t& base)>& func);

		// �ؿ������ - MF_Sync��MF_FixAfterLoad

		using Sync_SyncData_t = Magic::BaseFunction<void(Board* _this, SaveGameContext& theContext)>;
		void Binding_MF_Sync_SyncData(InitPatch& patch, const std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncData_t& base)>& func);

		using Sync_SyncDataArray_t = Magic::BaseFunction<void(Board* _this, SaveGameContext& theContext)>;
		void Binding_MF_Sync_SyncDataArray(InitPatch& patch, const std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncDataArray_t& base)>& func);

		using Sync_SyncDataArrayObject_t = Magic::BaseFunction<void(Board* _this, SaveGameContext& theContext)>;
		void Binding_MF_Sync_SyncDataArrayObject(InitPatch& patch, const std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncDataArrayObject_t& base)>& func);

		using Sync_SyncOtherObject_t = Magic::BaseFunction<void(Board* _this, SaveGameContext& theContext)>;
		void Binding_MF_Sync_SyncOtherObject(InitPatch& patch, const std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncOtherObject_t& base)>& func);

		using Sync_SyncOther_t = Magic::BaseFunction<void(Board* _this, SaveGameContext& theContext)>;
		void Binding_MF_Sync_SyncOther(InitPatch& patch, const std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncOther_t& base)>& func);

		using FixAfterLoad_t = Magic::BaseFunction<void(Board* _this)>;
		void Binding_MF_FixAfterLoad(InitPatch& patch, const std::function<void(Board* _this, FixAfterLoad_t& base)>& func);

		// ���ּ��� - MF_ZombiePicker

		using ZombiePicker_CalculateNumWaves_t = Magic::BaseFunction<void(Board* _this)>;
		void Binding_MF_ZombiePicker_CalculateNumWaves(InitPatch& patch, const std::function<void(Board* _this, ZombiePicker_CalculateNumWaves_t& base)>& func);

		using ZombiePicker_SpecialLevelPut_t = Magic::BaseFunction<bool(Board* _this, ZombiePicker& theZombiePicker, int theWave)>;
		void Binding_MF_ZombiePicker_SpecialLevelPut(InitPatch& patch, const std::function<bool(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_SpecialLevelPut_t& base)>& func);

		using ZombiePicker_CalculateBasicPoints_t = Magic::BaseFunction<void(Board* _this, ZombiePicker& theZombiePicker, int theWave)>;
		void Binding_MF_ZombiePicker_CalculateBasicPoints(InitPatch& patch, const std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_CalculateBasicPoints_t& base)>& func);

		using ZombiePicker_PutBeforeMultiple_t = Magic::BaseFunction<void(Board* _this, ZombiePicker& theZombiePicker, int theWave)>;
		void Binding_MF_ZombiePicker_PutBeforeMultiple(InitPatch& patch, const std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutBeforeMultiple_t& base)>& func);

		using ZombiePicker_CalculateMultiplePoints_t = Magic::BaseFunction<void(Board* _this, ZombiePicker& theZombiePicker, int theWave)>;
		void Binding_MF_ZombiePicker_CalculateMultiplePoints(InitPatch& patch, const std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_CalculateMultiplePoints_t& base)>& func);

		using ZombiePicker_PutPreset_t = Magic::BaseFunction<void(Board* _this, ZombiePicker& theZombiePicker, int theWave)>;
		void Binding_MF_ZombiePicker_PutPreset(InitPatch& patch, const std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutPreset_t& base)>& func);

		using ZombiePicker_PutRandom_t = Magic::BaseFunction<void(Board* _this, ZombiePicker& theZombiePicker, int theWave)>;
		void Binding_MF_ZombiePicker_PutRandom(InitPatch& patch, const std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutRandom_t& base)>& func);

		// ��̬�ؿ����� - MC_LEVEL_NAME

		void Binding_MC_LEVEL_NAME(InitPatch& patch, GameMode theLevelId, const SexyChar* theLevelName);
		
		// ��̬�ؿ����� - mvUseDynLevelName��mvDynLevelName

		void Binding_mvDynLevelName(InitPatch& patch, bool* theUseDynLevelNamePtr, SexyString* theDynLevelNamePtr);

		// ���ƹؿ����� - MF_DrawLevel

		using DrawLevel_t = Magic::BaseFunction<void(Board* _this, Graphics* g, const SexyString& theLevelName, int thePosX, int thePosY, DrawStringJustification theJustification, Font* theFont, const Color& theColor)>;
		void Binding_MF_DrawLevel(InitPatch& patch, const std::function<void(Board* _this, Graphics* g, const SexyString& theLevelName, int thePosX, int thePosY, DrawStringJustification theJustification, Font* theFont, const Color& theColor, DrawLevel_t& base)>& func);

		// ����ƫ�� - mvOffsetX��mvOffsetY

		void Binding_mvOffset(InitPatch& patch, int* theOffsetXPtr, int* theOffsetYPtr);
	}
}

#include "MagicBoard.inl"

#endif // !_PVZMOD_MAGIC_BOARD_H_
