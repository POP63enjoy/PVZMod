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
		};

		template <typename T> class BaseFunction;

		template <typename Ret, typename... Args>
		class BaseFunction<Ret(Args...)>
		{
		public:
			BaseFunction() {};
			BaseFunction(const BaseFunction&) = delete;
			BaseFunction(BaseFunction&&) = delete;

			Ret operator()(Args... args) { return mFunction(args...); }
			Ret operator()() { return mDefaultFunction(); }

			std::function<Ret(Args...)> mFunction;
			std::function<Ret()> mDefaultFunction;
		};

		template <typename T>
		bool IsEnableMultiReg();

		template <typename T>
		void IterateRef(auto func);

		template <typename ...Types>
		class TypeList
		{
		private:
			template <typename First_, typename ...Other_>
			class Check
			{
			public:
				using First = First_;
				using Other = TypeList<Other_...>;
			};
		public:
			using First = Check<Types...>::First;
			using Other = Check<Types...>::Other;

			static void Iterate(auto func);
		};

		template <> class TypeList<> {};
	}
};

#define PVZMOD_CHECK_MAGIC_FUNC(name) \
	template <typename Class, typename FuncType>	class CheckF_##name; \
	template <typename Class, typename Ret, typename ...Args> class CheckF_##name<Class, Ret(Args...)> { \
	private: \
		template <typename U> static auto check_type(int)	-> std::is_same<Ret, decltype(std::declval<U>().name(std::declval<Args>()...))>; \
		template <typename U> static auto check_type(...)	-> std::false_type; \
		template <typename U> static auto check_exist(int)	-> decltype(&U::name, std::true_type()); \
		template <typename U> static auto check_exist(...)	-> std::false_type; \
		template <typename U> static auto check_static(int)	-> decltype(U::name(std::declval<Args>()...), std::true_type()); \
		template <typename U> static auto check_static(...)	-> std::false_type; \
	public: \
		static constexpr int value = !decltype(check_exist<Class>(0))::value ? Magic::NOT_EXIST : \
			!decltype(check_type<Class>(0))::value ? Magic::TYPE_ERROR : Magic::EXIST; \
		static constexpr bool is_static_v = decltype(check_static<Class>(0))::value; \
	}

#define PVZMOD_CHECK_MAGIC_VAR(name) \
	template <typename Class, typename VarType> class CheckV_##name { \
	private: \
		template <typename U> static auto check_type(int)	-> std::is_same<VarType, decltype(std::declval<U>().name)>; \
		template <typename U> static auto check_type(...)	-> std::false_type; \
		template <typename U> static auto check_exist(int)	-> decltype(&U::name, std::true_type()); \
		template <typename U> static auto check_exist(...)	-> std::false_type; \
		template <typename U> static auto check_static(int)	-> std::is_same<decltype(&U::name), VarType*>; \
		template <typename U> static auto check_static(...)	-> std::false_type; \
	public: \
		static constexpr int value = !decltype(check_exist<Class>(0))::value ? Magic::NOT_EXIST : \
			!decltype(check_type<Class>(0))::value ? Magic::TYPE_ERROR : Magic::EXIST; \
		static constexpr bool is_static_v = decltype(check_static<Class>(0))::value; \
	}

#define PVZMOD_CHECK_MAGIC_TYPE(name) \
	template <typename Class> class CheckT_##name { \
	private: \
		template <typename U, typename = U::name>	static std::true_type	check(int); \
		template <typename U>						static std::false_type	check(...); \
	public: \
		static constexpr int value = decltype(check<Class>(0))::value ? Magic::EXIST : Magic::NOT_EXIST; \
	}

#define PVZMOD_IF_MAGIC_FUNC_EXIST(Name, Type, Class, ...) \
	do { \
		using Check = CheckF_##Name<Class, Type>; \
		static_assert(Check::value != Magic::TYPE_ERROR, "The magic function \"" #Name "\" is of wrong type, it should be \"" #Type "\"."); \
		if constexpr (Check::value == Magic::EXIST) { __VA_ARGS__ } \
	} while (false)

#define PVZMOD_IF_CHILD_MAGIC_FUNC_EXIST(Name, Type, Class, BaseClass, ...) \
	do { \
		using Check = CheckF_##Name<Class, Type>; \
		using CheckBase = CheckF_##Name<BaseClass, Type>; \
		static_assert(Check::value != Magic::TYPE_ERROR, "The magic function \"" #Name "\" is of wrong type, it should be \"" #Type "\"."); \
		if constexpr (Check::value == Magic::EXIST)	{ \
			if constexpr (CheckBase::value == Magic::EXIST) { \
				if (&Class::Name != &BaseClass::Name) { __VA_ARGS__ } \
			} \
			else { __VA_ARGS__ } \
		} \
	} while (false)

#define PVZMOD_IF_MAGIC_VAR_EXIST(Name, Type, Class, ...) \
	do { \
		using Check = CheckV_##Name<Class, Type>; \
		static_assert(Check::value != Magic::TYPE_ERROR, "The magic variable \"" #Name "\" is of wrong type, it should be \"" #Type "\"."); \
		if constexpr (Check::value == Magic::EXIST) { __VA_ARGS__ } \
	} while (false)


#define PVZMOD_IF_CHILD_MAGIC_VAR_EXIST(Name, Type, Class, BaseClass, ...) \
	do { \
		using Check = CheckV_##Name<Class, Type>; \
		using CheckBase = CheckV_##Name<BaseClass, Type>; \
		static_assert(Check::value != Magic::TYPE_ERROR, "The magic variable \"" #Name "\" is of wrong type, it should be \"" #Type "\"."); \
		if constexpr (Check::value == Magic::EXIST)	{ \
			if constexpr (CheckBase::value == Magic::EXIST) { \
				if (&Class::Name != &BaseClass::Name) { __VA_ARGS__ } \
			} \
			else { __VA_ARGS__ } \
		} \
	} while (false)

#define PVZMOD_IF_MAGIC_SVAR_EXIST(Name, Type, Class, ...) \
	do { \
		using Check = CheckV_##Name<Class, Type>; \
		static_assert(Check::value != Magic::TYPE_ERROR, "The magic variable \"" #Name "\" is of wrong type, it should be \"" #Type "\"."); \
		if constexpr (Check::value == Magic::EXIST) { \
			static_assert(Check::is_static_v, "The magic variable \"" #Name "\" must be static."); \
			if constexpr (Check::is_static_v) { __VA_ARGS__ } \
		} \
	} while (false)

#define PVZMOD_IF_CHILD_MAGIC_SVAR_EXIST(Name, Type, Class, BaseClass, ...) \
	do { \
		using Check = CheckV_##Name<Class, Type>; \
		using CheckBase = CheckV_##Name<BaseClass, Type>; \
		static_assert(Check::value != Magic::TYPE_ERROR, "The magic variable \"" #Name "\" is of wrong type, it should be \"" #Type "\"."); \
		if constexpr (Check::value == Magic::EXIST)	{ \
			static_assert(Check::is_static_v, "The magic variable \"" #Name "\" must be static."); \
			if constexpr (Check::is_static_v && CheckBase::value == Magic::EXIST) { \
				if (&Class::Name != &BaseClass::Name) { __VA_ARGS__ } \
			} \
			else { __VA_ARGS__ } \
		} \
	} while (false)

#define PVZMOD_IF_MAGIC_NSVAR_EXIST(Name, Type, Class, ...) \
	do { \
		using Check = CheckV_##Name<Class, Type>; \
		static_assert(Check::value != Magic::TYPE_ERROR, "The magic variable \"" #Name "\" is of wrong type, it should be \"" #Type "\"."); \
		if constexpr (Check::value == Magic::EXIST) { \
			static_assert(!Check::is_static_v, "The magic variable \"" #Name "\" must be non-static."); \
			if constexpr (!Check::is_static_v) { __VA_ARGS__ } \
		} \
	} while (false)

#define PVZMOD_IF_CHILD_MAGIC_NSVAR_EXIST(Name, Type, Class, BaseClass, ...) \
	do { \
		using Check = CheckV_##Name<Class, Type>; \
		using CheckBase = CheckV_##Name<BaseClass, Type>; \
		static_assert(Check::value != Magic::TYPE_ERROR, "The magic variable \"" #Name "\" is of wrong type, it should be \"" #Type "\"."); \
		if constexpr (Check::value == Magic::EXIST)	{ \
			static_assert(!Check::is_static_v, "The magic variable \"" #Name "\" must be non-static."); \
			if constexpr (!Check::is_static_v && CheckBase::value == Magic::EXIST) { \
				if (&Class::Name != &BaseClass::Name) { __VA_ARGS__ } \
			} \
			else { __VA_ARGS__ } \
		} \
	} while (false)

#define PVZMOD_GENERAL_MAGIC_FUNC(Name, Type, Class) \
	PVZMOD_IF_MAGIC_FUNC_EXIST(Name, Type, Class, { \
		Binding_##Name(patch, []<typename ...Args>(auto* _this, Args&&... args) { \
			((Class*)_this)->Name(std::forward<Args>(args)...); \
		}); \
	})

#define PVZMOD_SPECIAL_THIS_MAGIC_FUNC(Name, Type, Class, This) \
	PVZMOD_IF_MAGIC_FUNC_EXIST(Name, Type, Class, { \
		Binding_##Name(patch, []<typename ...Args>(Args&&... args) { \
			((Class*)This)->Name(std::forward<Args>(args)...); \
		}); \
	})

#define PVZMOD_ARG(Index) (*std::get<Index>(arglist))

#define PVZMOD_GENERAL_CHILD_MAGIC_FUNC(Name, Type, Class, BaseClass, Captures, Check) \
	PVZMOD_IF_CHILD_MAGIC_FUNC_EXIST(Name, Type, Class, BaseClass, { \
		Binding_##Name(patch, [Captures]<typename ...Args>(auto* _this, Args&&... args) { \
			std::tuple arglist {&args...}; \
			if (Check) \
				((Class*)_this)->Name(std::forward<Args>(args)...); \
			else \
				PVZMOD_ARG(sizeof...(args) - 1)(); \
		}); \
	})

#define __PVZMOD_UNPACK__(...) __VA_ARGS__

#define PVZMOD_INIT_GROUP(type, name, var, ...) \
	~type() {} \
	struct name##_t	{ \
	private: \
		struct { __PVZMOD_UNPACK__ var }; \
	public: \
		__VA_ARGS__; \
		template <typename ...Args> void ctor(Args... args) { new(this) name##_t(args...); } \
									void dtor() { this->~name##_t(); } \
	}; \
	union { \
		name##_t m##name; \
		struct { __PVZMOD_UNPACK__ var }; \
	}

#include "Magic.inl"

#endif // !_PVZMOD_MAGIC_H_
