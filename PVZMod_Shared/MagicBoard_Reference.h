#pragma once

#error 本文件仅用于参考，不要包含

#include "Board.h"
#include "MagicBoard.h"

namespace PVZMod
{
	/// MagicBoard 魔法成员参考。
	///
	/// @code{.cpp}
	/// #include <MagicBoard.h>
	/// 
	/// using namespace PVZMod;
	/// 
	/// void PVZMod::Main(InitPatch& patch)
	/// {
	///		MagicBoard::Extend<MagicBoard_Main>(patch)											// 替换主类。
	///			.RegisterLevel<(GameMode)100, MagicBoard_Level>(patch)							// 注册单关类。
	///			.RegisterLevel<(GameMode)100, MagicBoard_Level2>(patch)							// 一个关卡可以注册多个类，将按照倒序调用。
	///			.RegisterLevel<(GameMode)101, MagicBoard_Level>(patch)							// 多个关卡可以使用一个类。
	///			.RegisterLevel<GAMEMODE_SURVIVAL_NORMAL_STAGE_1, MagicBoard_Level>(patch);		// 可以为原版关卡注册类。
	/// }
	/// @endcode
	namespace MagicBoard_Reference
	{
		/// MagicBoard 主类。
		class MagicBoard_Main :public Board
		{
		public:
			/// 构造函数。
			/// 
			/// @param theApp	游戏程序对象。
			/// @param base		原始函数。
			void MF_Constructor(LawnApp* theApp, MagicBoard::Constructor_t& base);

			/// 析构函数。
			///
			/// @param base		原始函数。
			void MF_Destructor(MagicBoard::Destructor_t& base);

			/// 关卡信息初始化。
			///
			/// @param base		原始函数。
			void MF_InitLevel(MagicBoard::InitLevel_t& base);

			/// 释放相关资源。
			///
			/// @param base		原始函数。
			void MF_DisposeBoard(MagicBoard::DisposeBoard_t& base);

			/// 出怪计算 - 计算波数。
			///
			/// 计算结果存放在 mNumWaves 中。
			/// 
			/// @param base		原始函数。
			void MF_ZombiePicker_CalculateNumWaves(MagicBoard::ZombiePicker_CalculateNumWaves_t& base);

			/// 出怪计算 - 针对特殊关卡进行特殊的僵尸放置操作。
			///
			/// @param theZombiePicker	出怪计算信息。
			/// @param theWave			当前波数。
			/// @param base				原始函数。
			/// @return					如果为 true，则不执行普通关卡的常规出怪计算操作。
			bool MF_ZombiePicker_SpecialLevelPut(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_SpecialLevelPut_t& base);

			/// 出怪计算 - 计算本波基础出怪点数。
			/// 
			/// 计算结果存放在 mZombiePoints.mZombiePoints 中。
			/// 
			/// @param theZombiePicker	出怪计算信息。
			/// @param theWave			当前波数。
			/// @param base				原始函数。
			void MF_ZombiePicker_CalculateBasicPoints(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_CalculateBasicPoints_t& base);

			/// 出怪计算 - 在出怪点数加倍之前进行僵尸放置操作。
			///
			/// 在原版中，这里用于放置旗帜波的特殊僵尸。
			/// 
			/// @param theZombiePicker	出怪计算信息。
			/// @param theWave			当前波数。
			/// @param base				原始函数。
			void MF_ZombiePicker_PutBeforeMultiple(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_PutBeforeMultiple_t& base);

			/// 出怪计算 - 根据关卡不同，计算出怪点数倍数。
			///
			/// 将基础出怪点数乘倍数的结果存放在 mZombiePoints.mZombiePoints 中。
			/// 
			/// @param theZombiePicker	出怪计算信息。
			/// @param theWave			当前波数。
			/// @param base				原始函数。
			void MF_ZombiePicker_CalculateMultiplePoints(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_CalculateMultiplePoints_t& base);

			/// 出怪计算 - 放置关卡预设僵尸。
			/// 
			/// @param theZombiePicker	出怪计算信息。
			/// @param theWave			当前波数。
			/// @param base				原始函数。
			void MF_ZombiePicker_PutPreset(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_PutPreset_t& base);

			/// 出怪计算 - 放置随机僵尸。
			/// 
			/// @param theZombiePicker	出怪计算信息。
			/// @param theWave			当前波数。
			/// @param base				原始函数。
			void MF_ZombiePicker_PutRandom(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_PutRandom_t& base);

			/// Board 偏移 X 坐标。
			static int mvOffsetX;

			/// Board 偏移 Y 坐标。
			static int mvOffsetY;

			/// 为 true 则自动存储扩展的数据。（默认为 false）
			static const bool MC_AUTO_SAVE_EXTENDED_DATA;
		};

		/// MagicBoard 单个关卡类。
		///
		/// 注意：单关类不得添加成员变量，请在主类中添加。
		class MagicBoard_Level :public MagicBoard_Main
		{
		public:
			/// 构造函数。
			/// 
			/// @param theApp	游戏程序对象。
			/// @param base		原始函数。
			void MF_Constructor(LawnApp* theApp, MagicBoard::Constructor_t& base);

			/// 析构函数。
			///
			/// @param base		原始函数。
			void MF_Destructor(MagicBoard::Destructor_t& base);

			/// 关卡信息初始化。
			///
			/// @param base		原始函数。
			void MF_InitLevel(MagicBoard::InitLevel_t& base);

			/// 释放相关资源。
			///
			/// @param base		原始函数。
			void MF_DisposeBoard(MagicBoard::DisposeBoard_t& base);

			/// 出怪计算 - 计算波数。
			///
			/// 计算结果存放在 mNumWaves 中。
			/// 
			/// @param base		原始函数。
			void MF_ZombiePicker_CalculateNumWaves(MagicBoard::ZombiePicker_CalculateNumWaves_t& base);

			/// 出怪计算 - 针对特殊关卡进行特殊的僵尸放置操作。
			///
			/// @param theZombiePicker	出怪计算信息。
			/// @param theWave			当前波数。
			/// @param base				原始函数。
			/// @return					如果为 true，则不执行普通关卡的常规出怪计算操作。
			bool MF_ZombiePicker_SpecialLevelPut(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_SpecialLevelPut_t& base);

			/// 出怪计算 - 计算本波基础出怪点数。
			/// 
			/// 计算结果存放在 mZombiePoints.mZombiePoints 中。
			/// 
			/// @param theZombiePicker	出怪计算信息。
			/// @param theWave			当前波数。
			/// @param base				原始函数。
			void MF_ZombiePicker_CalculateBasicPoints(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_CalculateBasicPoints_t& base);

			/// 出怪计算 - 在出怪点数加倍之前进行僵尸放置操作。
			///
			/// 在原版中，这里用于放置旗帜波的特殊僵尸。
			/// 
			/// @param theZombiePicker	出怪计算信息。
			/// @param theWave			当前波数。
			/// @param base				原始函数。
			void MF_ZombiePicker_PutBeforeMultiple(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_PutBeforeMultiple_t& base);

			/// 出怪计算 - 根据关卡不同，计算出怪点数倍数。
			///
			/// 将基础出怪点数乘倍数的结果存放在 mZombiePoints.mZombiePoints 中。
			/// 
			/// @param theZombiePicker	出怪计算信息。
			/// @param theWave			当前波数。
			/// @param base				原始函数。
			void MF_ZombiePicker_CalculateMultiplePoints(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_CalculateMultiplePoints_t& base);

			/// 出怪计算 - 放置关卡预设僵尸。
			/// 
			/// @param theZombiePicker	出怪计算信息。
			/// @param theWave			当前波数。
			/// @param base				原始函数。
			void MF_ZombiePicker_PutPreset(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_PutPreset_t& base);

			/// 出怪计算 - 放置随机僵尸。
			/// 
			/// @param theZombiePicker	出怪计算信息。
			/// @param theWave			当前波数。
			/// @param base				原始函数。
			void MF_ZombiePicker_PutRandom(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_PutRandom_t& base);
		};

	}
}