#pragma once

#error 本文件仅用于参考，不要包含

#include "MagicPlant.h"

namespace PVZMod
{
	/// MagicPlant 魔法成员参考。
	namespace MagicPlant_Reference
	{
		class MagicPlant_Main :public Plant
		{
		public:
			/// 植物初始化 - 初始化成员变量。
			///
			/// @param theGridX			列数。
			/// @param theGridY			行数。
			/// @param theSeedType		植物类型。
			/// @param theImitaterType	模仿者类型。
			/// @param base				原始函数。
			/// @return					植物定义信息。
			PlantDefinition& MF_PlantInitialize_InitMemberVariable(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType, MagicPlant::PlantInitialize_InitMemberVariable_t& base);

			/// 植物初始化 - 初始化动画。
			///
			/// @param thePlantDef	植物定义信息。
			/// @param base			原始函数。
			/// @return				主体动画指针。
			Reanimation* MF_PlantInitialize_InitReanimation(PlantDefinition& thePlantDef, MagicPlant::PlantInitialize_InitReanimation& base);

			/// 植物初始化 - 针对不同植物类型初始化之前。
			///
			/// @param thePlantDef		植物定义信息。
			/// @param theBodyReanim	植物主体动画。
			/// @param base				原始函数。
			void MF_PlantInitialize_BeforeInitType(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, MagicPlant::PlantInitialize_BeforeInitType& base);

			/// 植物初始化 - 针对不同植物类型初始化。
			///
			/// @param thePlantDef		植物定义信息。
			/// @param theBodyReanim	植物主体动画。
			/// @param base				原始函数。
			void MF_PlantInitialize_InitType(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, MagicPlant::PlantInitialize_InitType& base);

			/// 植物初始化 - 针对不同植物类型初始化之后。
			///
			/// @param thePlantDef		植物定义信息。
			/// @param theBodyReanim	植物主体动画。
			/// @param base				原始函数。
			void MF_PlantInitialize_AfterInitType(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, MagicPlant::PlantInitialize_AfterInitType& base);

			/// 植物 DataArray 大小。
			static const size_t MC_DATA_ARRAY_SIZE;
		};

		class MagicPlant_Plant :public MagicPlant_Main
		{
		public:
			/// 植物初始化 - 初始化成员变量。
			///
			/// @param theGridX			列数。
			/// @param theGridY			行数。
			/// @param theSeedType		植物类型。
			/// @param theImitaterType	模仿者类型。
			/// @param base				原始函数。
			/// @return					植物定义信息。
			PlantDefinition& MF_PlantInitialize_InitMemberVariable(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType, MagicPlant::PlantInitialize_InitMemberVariable_t& base);

			/// 植物初始化 - 初始化动画。
			///
			/// @param thePlantDef	植物定义信息。
			/// @param base			原始函数。
			/// @return				主体动画指针。
			Reanimation* MF_PlantInitialize_InitReanimation(PlantDefinition& thePlantDef, MagicPlant::PlantInitialize_InitReanimation& base);

			/// 植物初始化 - 针对不同植物类型初始化之前。
			///
			/// @param thePlantDef		植物定义信息。
			/// @param theBodyReanim	植物主体动画。
			/// @param base				原始函数。
			void MF_PlantInitialize_BeforeInitType(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, MagicPlant::PlantInitialize_BeforeInitType& base);

			/// 植物初始化 - 针对不同植物类型初始化。
			///
			/// @param thePlantDef		植物定义信息。
			/// @param theBodyReanim	植物主体动画。
			/// @param base				原始函数。
			void MF_PlantInitialize_InitType(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, MagicPlant::PlantInitialize_InitType& base);

			/// 植物初始化 - 针对不同植物类型初始化之后。
			///
			/// @param thePlantDef		植物定义信息。
			/// @param theBodyReanim	植物主体动画。
			/// @param base				原始函数。
			void MF_PlantInitialize_AfterInitType(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, MagicPlant::PlantInitialize_AfterInitType& base);
		};
	}
}