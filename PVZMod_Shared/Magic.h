#pragma once
#ifndef _PVZMOD_MAGIC_H_
#define _PVZMOD_MAGIC_H_

#include <functional>

namespace PVZMod
{
	namespace Magic
	{
		enum
		{
			EXIST,
			TYPE_ERROR,
			NOT_EXIST,
			NEED_COMPARE,
		};

		template <typename T> class BaseFunction;

		template <typename Ret, typename... Args>
		class BaseFunction<Ret(Args...)>
		{
		public:
			Ret operator()(Args... args) { return mFunction(args...); }
			Ret operator()() { return mDefaultFunction(); }

			std::function<Ret(Args...)> mFunction;
			std::function<Ret()> mDefaultFunction;
		};
	}
};
/*
#define PVZMOD_CHECK_MAGIC_MEMBER(name)																														\
	template<typename Class, typename PtrType> class Check_##name {																							\
	private:																																				\
		template <typename U> static constexpr bool check_type(decltype(&U::name)) { return std::is_same<decltype(&U::name), PtrType>::value; }				\
		template <typename U> static constexpr bool check_type(...) { return false; }																		\
		template <typename U> static constexpr bool check_exist(decltype(&U::name)) { return true; }														\
		template <typename U> static constexpr bool check_exist(...) { return false; }																		\
	public:																																					\
		static constexpr int value = !check_exist<Class>(nullptr) ? Magic::NOT_EXIST : !check_type<Class>(nullptr) ? Magic::TYPE_ERROR : Magic::EXIST;		\
	}
*/
#define PVZMOD_CHECK_MAGIC_FUNC(name)																														\
	template<typename Class, typename FuncType>	class CheckF_##name;																						\
	template<typename Class, typename Ret, typename ...Args> class CheckF_##name<Class, Ret(Args...)> {														\
	private:																																				\
		template <typename U> static constexpr auto check_type(int) -> std::is_same<Ret, decltype(std::declval<U>().name(std::declval<Args>()...))>;		\
		template <typename U> static constexpr auto check_type(...) -> std::false_type;																		\
		template <typename U> static constexpr auto check_exist(int) -> decltype(&U::name, std::true_type());												\
		template <typename U> static constexpr auto check_exist(...) -> std::false_type;																	\
		template <typename U> static constexpr auto check_static(int) -> decltype(U::name(std::declval<Args>()...), std::true_type());						\
		template <typename U> static constexpr auto check_static(...) -> std::false_type;																	\
	public:																																					\
		static constexpr int value = !decltype(check_exist<Class>(0))::value ? Magic::NOT_EXIST :															\
			!decltype(check_type<Class>(0))::value ? Magic::TYPE_ERROR : Magic::EXIST;																		\
		static constexpr bool is_static_v = decltype(check_static<Class>(0))::value;																		\
	}

#define PVZMOD_CHECK_MAGIC_VAR(name)																								\
	template<typename Class, typename VarType> class CheckV_##name {																\
	private:																														\
		template <typename U> static constexpr auto check_type(int) -> std::is_same<VarType, decltype(std::declval<U>().name)>;		\
		template <typename U> static constexpr auto check_type(...) -> std::false_type;												\
		template <typename U> static constexpr auto check_exist(int) -> decltype(&U::name, std::true_type());						\
		template <typename U> static constexpr auto check_exist(...) -> std::false_type;											\
		template <typename U> static constexpr auto check_static(int) -> std::is_same<decltype(&U::name), VarType*>;				\
		template <typename U> static constexpr auto check_static(...) -> std::false_type;											\
	public:																															\
		static constexpr int value = !decltype(check_exist<Class>(0))::value ? Magic::NOT_EXIST :									\
			!decltype(check_type<Class>(0))::value ? Magic::TYPE_ERROR : Magic::EXIST;												\
		static constexpr bool is_static_v = decltype(check_static<Class>(0))::value;												\
	}

#define PVZMOD_MAGIC_FUNC(Name, Type, Class, ...)																							\
	do {																																	\
		using Check = CheckF_##Name<Class, Type>;																							\
		static_assert(Check::value != Magic::TYPE_ERROR, "The magic function \"" #Name "\" is of wrong type, it should be \"" #Type "\".");	\
		if constexpr (Check::value == Magic::EXIST) { __VA_ARGS__ }																			\
	} while (false)

#define PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(Name, Type, Class, BaseClass, ...)																\
	do {																																	\
		using Check = CheckF_##Name<Class, Type>;																							\
		using CheckBase = CheckF_##Name<BaseClass, Type>;																					\
		static_assert(Check::value != Magic::TYPE_ERROR, "The magic function \"" #Name "\" is of wrong type, it should be \"" #Type "\".");	\
		if constexpr (Check::value == Magic::EXIST)	{																						\
			if constexpr (CheckBase::value == Magic::EXIST) {																				\
				if (&Class::Name != &BaseClass::Name) { __VA_ARGS__ }																		\
			}																																\
			else { __VA_ARGS__ }																											\
		}																																	\
	} while(false)

#define PVZMOD_MAGIC_VAR(Name, Type, Class, ...) /*untested*/																				\
	do {																																	\
		using Check = CheckV_##Name<Class, Type>;																							\
		static_assert(Check::value != Magic::TYPE_ERROR, "The magic variable \"" #Name "\" is of wrong type, it should be \"" #Type "\".");	\
		if constexpr (Check::value == Magic::EXIST) { __VA_ARGS__ }																			\
	} while (false)


#define PVZMOD_MAGIC_VAR_CHECK_BASE_CLASS(Name, Type, Class, BaseClass, ...) /*untested*/													\
	do {																																	\
		using Check = CheckV_##Name<Class, Type>;																							\
		using CheckBase = CheckV_##Name<BaseClass, Type>;																					\
		static_assert(Check::value != Magic::TYPE_ERROR, "The magic variable \"" #Name "\" is of wrong type, it should be \"" #Type "\".");	\
		if constexpr (Check::value == Magic::EXIST)	{																						\
			if constexpr (CheckBase::value == Magic::EXIST) {																				\
				if (&Class::Name != &BaseClass::Name) { __VA_ARGS__ }																		\
			}																																\
			else { __VA_ARGS__ }																											\
		}																																	\
	} while(false)

#define PVZMOD_MAGIC_SVAR(Name, Type, Class, ...)																							\
	do {																																	\
		using Check = CheckV_##Name<Class, Type>;																							\
		static_assert(Check::value != Magic::TYPE_ERROR, "The magic variable \"" #Name "\" is of wrong type, it should be \"" #Type "\".");	\
		if constexpr (Check::value == Magic::EXIST) {																						\
			static_assert(Check::is_static_v, "The magic variable \"" #Name "\" must be static.");											\
			if constexpr (Check::is_static_v) { __VA_ARGS__ }																				\
		}																																	\
	} while (false)

#define PVZMOD_MAGIC_NSVAR(Name, Type, Class, ...)																							\
	do {																																	\
		using Check = CheckV_##Name<Class, Type>;																							\
		static_assert(Check::value != Magic::TYPE_ERROR, "The magic variable \"" #Name "\" is of wrong type, it should be \"" #Type "\".");	\
		if constexpr (Check::value == Magic::EXIST) {																						\
			static_assert(!Check::is_static_v, "The magic variable \"" #Name "\" must be non-static.");										\
			if constexpr (!Check::is_static_v) { __VA_ARGS__ }																				\
		}																																	\
	} while (false)

#define __PVZMOD_UNPACK__(...) __VA_ARGS__

#define PVZMOD_INIT_GROUP(type, name, var, ...)													\
	~type() {}																					\
	struct name##_t	{																			\
	private:																					\
		struct { __PVZMOD_UNPACK__ var };														\
	public:																						\
		__VA_ARGS__;																			\
		template <typename ...Args> void ctor(Args... args) { new(this) name##_t(args...); }	\
									void dtor() { this->~name##_t(); } 							\
	};																							\
	union {																						\
		name##_t m##name;																		\
		struct { __PVZMOD_UNPACK__ var };														\
	};

#endif // !_PVZMOD_MAGIC_H_
