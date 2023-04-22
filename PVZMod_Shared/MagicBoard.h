#pragma once
#ifndef _PVZMOD_MAGIC_BOARD_H_
#define _PVZMOD_MAGIC_BOARD_H_

#ifndef _PVZMOD_BOARD_H_
#error 必须在 #include <MagicBoard.h> 之前 #include <Board.h> 。
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
	enum GameMode;

	/// `Board` 魔法成员扩展。
	namespace MagicBoard
	{
		/// 子魔法类注册管理器。
		template <typename BaseClass>
		class RegisterManager
		{
		public:
			/// 【补丁函数】注册以关卡为判断条件的子魔法类。
			///
			/// @tparam LevelClass				子魔法类，继承于 BaseClass，不允许定义构造函数、析构函数、虚函数、非静态成员变量。
			/// @param patch					补丁对象。
			/// @param theLevelId				关卡编号。
			/// @param enableMultipleRegister	为 true 则允许重复注册相同的类。（不包括通过 MT_Ref 引用的类）
			template <typename LevelClass>
			static RegisterManager RegisterLevel(InitPatch& patch, GameMode theLevelId, bool enableMultipleRegister = false);
		};

		/// 【补丁函数】为 Board 注册主魔法类。
		///
		/// @tparam T		主魔法类，继承于 Board，不允许定义构造函数、析构函数、虚函数。
		/// @param patch	补丁对象。
		/// @return			用于注册子魔法类。
		template<typename T>
		RegisterManager<T> RegisterMain(InitPatch& patch);

		void Binding_ExtendBase(InitPatch& patch, size_t theBoardSize, bool autoSaveExtendedData);

		using Constructor_t = Magic::BaseFunction<void(Board* _this, LawnApp* theApp)>;
		void Binding_MF_Constructor(InitPatch& patch, const std::function<void(Board* _this, LawnApp* theApp, Constructor_t& base)>& func);
		
		using Destructor_t = Magic::BaseFunction<void(Board* _this)>;
		void Binding_MF_Destructor(InitPatch& patch, const std::function<void(Board* _this, Destructor_t& base)>& func);

		using InitLevel_t = Magic::BaseFunction<void(Board* _this)>;
		void Binding_MF_InitLevel(InitPatch& patch, const std::function<void(Board* _this, InitLevel_t& base)>& func);

		using DisposeBoard_t = Magic::BaseFunction<void(Board* _this)>;
		void Binding_MF_DisposeBoard(InitPatch& patch, const std::function<void(Board* _this, DisposeBoard_t& base)>& func);

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

		extern int* mvOffsetXPtr, * mvOffsetYPtr;
		void Binding_mvOffset(InitPatch& patch, int* theOffsetXPtr, int* theOffsetYPtr);
	}
}

#include "MagicBoard.inl"

#endif // !_PVZMOD_MAGIC_BOARD_H_
