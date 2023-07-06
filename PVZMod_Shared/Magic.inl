#pragma once
#ifndef _PVZMOD_MAGIC_INL_
#define _PVZMOD_MAGIC_INL_

namespace PVZMod
{
	namespace Magic
	{
		namespace __PRIVATE__
		{
			PVZMOD_CHECK_MAGIC_VAR(MC_MULTI_REG);
			PVZMOD_CHECK_MAGIC_TYPE(MT_Ref);
			PVZMOD_CHECK_MAGIC_FUNC(Iterate);
		}

		template <typename T>
		bool IsEnableMultiReg()
		{
			using namespace __PRIVATE__;
			bool result = false;
			PVZMOD_IF_MAGIC_SVAR_EXIST(MC_MULTI_REG, const bool, T,
				{
					result = T::MC_MULTI_REG;
				});
			return result;
		}

		template <typename T>
		void IterateRef(auto func)
		{
			using namespace __PRIVATE__;
			using Check = CheckT_MT_Ref<T>;
			if constexpr (Check::value == Magic::EXIST)
				T::MT_Ref::Iterate(func);
		}

		template <typename ...Types>
		void TypeList<Types...>::Iterate(auto func)
		{
			func.operator()<First>();
			if constexpr (!std::is_same<Other, TypeList<>>::value)
				Other::Iterate(func);
		}
	}
}

#endif // !_PVZMOD_MAGIC_INL_
