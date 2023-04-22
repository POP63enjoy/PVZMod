#pragma once
#ifndef _PVZMOD_PVZSTL_H_
#define _PVZMOD_PVZSTL_H_

#ifdef _XTREE_
#error
#endif // _XTREE_

#include "xtree.h"
#include <list>
#include <vector>
#include <map>
#include <set>
#include <string>

namespace PVZMod
{
	static_assert(sizeof(std::vector<int>::iterator) == 0x4, "Missing _ITERATOR_DEBUG_LEVEL=0");

	/// ����Ϸ�ࡿ����Ϸ�ڽṹ���ݵ� `std::basic_string` �ࡣ
	template <typename T>
	class BasicString : public std::basic_string<T>
	{
	private:
		virtual void func() {};
	public:
		using std::basic_string<T>::basic_string;
		using size_type = std::basic_string<T>::size_type;

		_CONSTEXPR20 BasicString(const std::basic_string<T>& _Right)
			:std::basic_string<T>(_Right)
		{
		}

		_CONSTEXPR20 BasicString(std::basic_string<T>&& _Right) noexcept
			:std::basic_string<T>(std::move(_Right))
		{
		}
	};

	/// ����Ϸ�ࡿ����Ϸ�ڽṹ���ݵ� `std::string` �ࡣ
	using String = BasicString<char>;

	/// ����Ϸ�ࡿ����Ϸ�ڽṹ���ݵ� `std::wstring` �ࡣ
	using WString = BasicString<wchar_t>;

	/// ����Ϸ�ࡿ����Ϸ�ڽṹ���ݵ� std::vector �ࡣ
	template <typename T>
	class Vector :public std::vector<T>
	{
	private:
		virtual void func() {};
	public:
		using std::vector<T>::vector;
	};

	/// ����Ϸ�ࡿ����Ϸ�ڽṹ���ݵ� `std::list` �ࡣ
	template <typename T>
	class List :public std::list<T>
	{
	private:
		virtual void func() {};
	public:
		using std::list<T>::list;
	};

	/// ����Ϸ�ࡿ����Ϸ�ڽṹ���ݵ� `std::set` �ࡣ
	template <typename T,typename U = std::less<T>>
	class Set :public std::set<T, U>
	{
	private:
		virtual void func() {};
	public:
		using std::set<T, U>::set;
	};

	/// ����Ϸ�ࡿ����Ϸ�ڽṹ���ݵ� `std::map` �ࡣ
	template <typename T, typename U, typename V = std::less<T>>
	class Map :public std::map<T, U, V>
	{
	private:
		virtual void func() {};
	public:
		using std::map<T, U, V>::map;
	};

	/// ����Ϸ�ࡿ����Ϸ�ڽṹ���ݵĵ������ࡣ
	template <typename T>
	class Iterator
	{
	public:
		T* _Mycont = nullptr;
		typename T::iterator iter;
		
		Iterator() {}

		Iterator(const typename T::iterator& it, T* cont) : _Mycont(cont), iter(it) {};
		
		typename T::iterator* operator->()
		{
			return &iter;
		}
	};
}

#endif // !_PVZMOD_PVZSTL_H_
