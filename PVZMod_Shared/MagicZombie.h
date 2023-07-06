#pragma once
#ifndef _PVZMOD_MAGIC_ZOMBIE_H_
#define _PVZMOD_MAGIC_ZOMBIE_H_

#ifndef _PVZMOD_ZOMBIE_H_
#error ������ #include <MagicZombie.h> ֮ǰ #include <Zombie.h> ��
#endif // !_PVZMOD_BOARD_H_

#include "Magic.h"

namespace PVZMod
{
	class InitPatch;
	class Zombie;
	class ZombieDefinition;
	enum RenderLayer;
	enum ZombieType;

	/// `Zombie` ħ����Ա��չ��
	namespace MagicZombie
	{
		/// ��ħ����ע���������
		template <typename BaseClass>
		class RegisterManager
		{
		public:
			/// ������������ע���Խ�ʬ����Ϊ�ж���������ħ���ࡣ
			///
			/// @tparam ZombieClass				��ħ���࣬�̳��� BaseClass���������幹�캯���������������麯�����Ǿ�̬��Ա������
			/// @param patch					��������
			/// @param theZombieId				��ʬ��š�
			/// @param enableMultipleRegister	Ϊ true �������ظ�ע����ͬ���ࡣ��������ͨ�� MT_Ref ���õ��ࣩ
			template <typename ZombieClass>
			RegisterManager RegisterZombie(InitPatch& patch, ZombieType theZombieId, bool enableMultipleRegister = false);
		};

		/// ������������Ϊ Zombie ע����ħ���ࡣ
		///
		/// @tparam T		��ħ���࣬�̳��� Zombie���������幹�캯���������������麯����
		/// @param patch	��������
		/// @return			����ע����ħ���ࡣ
		template <typename T>
		RegisterManager<T> RegisterMain(InitPatch& patch);

		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////

		// ������Ϣ�� & �������� - MC_DATA_ARRAY_SIZE

		void Binding_ExtendBase(InitPatch& patch, size_t theZombieSize, size_t theDataArraySize);

		// ��ʼ�� - MF_ZombieInitialize

		using ZombieInitialize_InitMemberVariable_t = Magic::BaseFunction<ZombieDefinition& (Zombie* _this, int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave)>;
		void Binding_MF_ZombieInitialize_InitMemberVariable(InitPatch& patch, const std::function<ZombieDefinition& (Zombie* _this, int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave, ZombieInitialize_InitMemberVariable_t& base)>& func);

		using ZombieInitialize_InitReanimation_t = Magic::BaseFunction<void(Zombie* _this, ZombieDefinition& theZombieDef)>;
		void Binding_MF_ZombieInitialize_InitReanimation(InitPatch& patch, const std::function<void(Zombie* _this, ZombieDefinition& theZombieDef, ZombieInitialize_InitReanimation_t& base)>& func);
		
		using ZombieInitialize_InitType_t = Magic::BaseFunction<void(Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer& theRenderLayer, int& theRenderOffset)>;
		void Binding_MF_ZombieInitialize_InitType(InitPatch& patch, const std::function<void(Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer& theRenderLayer, int& theRenderOffset, ZombieInitialize_InitType_t& base)>& func);

		using ZombieInitialize_AfterInitType_t = Magic::BaseFunction<void(Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer theRenderLayer, int theRenderOffset)>;
		void Binding_MF_ZombieInitialize_AfterInitType(InitPatch& patch, const std::function<void(Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer theRenderLayer, int theRenderOffset, ZombieInitialize_AfterInitType_t& base)>& func);
	}
}

#include "MagicZombie.inl"

#endif // !_PVZMOD_MAGIC_ZOMBIE_H_
