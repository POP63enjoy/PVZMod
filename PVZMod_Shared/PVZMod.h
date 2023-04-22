#pragma once
#ifndef _PVZMOD_PVZMOD_H_
#define _PVZMOD_PVZMOD_H_

#ifdef _WIN64
#error �ݲ�֧�� 64 λ��
#endif

#include "Hook.h"
#include "PVZSTL.h"
#include <stack>
#include <functional>

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID);

/// ����������ռ䡣
/// 
/// �����޸���Ϸ�ĺ������࣬�Լ���Ϸ��ԭ�е��� Sexy �����ռ��������ռ����ݣ������� PVZMod �����ռ䡣
/// 
/// ʹ�ñ���ܵĸİ棬Ҳ���Խ����������ݷ��� PVZMod �����ռ䣬�򴴽��Լ��������ռ䣬�ڴ�֮�� `using namespace PVZMod`��
namespace PVZMod
{
	/// �ṩ����Ϸ�Ļ����޸Ĳ�������ǲ���������
	class InitPatch
	{
	public:

		/// �ṩ�����ĺ����滻�Ͳ�����������
		Hook& mHook;

		/// ���ڱ�ǲ�������
		/// 
		/// @param name			�������ֲ�����������ƣ�ͨ��Ϊ���������ĺ�������
		/// @param func			������������ͨ��Ϊ Lambda��
		/// @param once			Ϊ true ���������ƵĲ�������ֻ��Ҫִ��һ�Σ��ڶ���������ͬ���ƵĲ�������ʱ����ִ�С�
		/// @param throwOnTwice	Ϊ true ������Ʋ��������ڵڶ���ִ��ʱ�׳��쳣��
		void PatchTask(const std::string& name, const std::function<void()>& func, bool once = true, bool throwOnTwice = false);

	private:
		InitPatch();
		~InitPatch();
		
		static Hook* gHook;

		std::unordered_map<std::string, bool> mPatchMap;
		std::list<std::string> mPatchList;

		friend BOOL WINAPI ::DllMain(HINSTANCE, DWORD, LPVOID);
	};

	/// ������ڵ㡿����������ڵ㡣
	///
	/// Ӧ�ڴ˺����ж���Ϸ��������޸��Լ����ò���������
	/// 
	/// �������У��������д��Ϸ��ֻ���ڴ档
	void Main(InitPatch& patch);
}

extern "C" __declspec(dllexport) inline void exportfunc() {};

#endif // !_PVZMOD_PVZMOD_H_
