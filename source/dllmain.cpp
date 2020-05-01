// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <filesystem>
#include "MemoryMgr.h"
#include "pattern/Hooking.Patterns.h"
#include <fstream>
#include <iostream>


using namespace Memory::VP;

void HookDecryptCarInfo(const char* input, const char* output)
{
	std::string fname(input, strlen(input) - 3);
	fname += "ini";

	if (std::experimental::filesystem::exists(fname.c_str()))
	{
		FILE* in = fopen(fname.c_str(), "rb");
		FILE* out = fopen(output, "wb");

		char byte = 0;
		byte = fgetc(in);
		for (int i = byte; !feof(in); i++)
		{
			fputc(byte, out);
			byte = fgetc(in);
		}
		fclose(in);
		fclose(out);
	}
	else
	{
		FILE* in = fopen(input, "rb");
		FILE* out = fopen(output, "wb");

		char byte = 0;
		byte = fgetc(in) ^ 0x7B;
		for (int i = byte; !feof(in); i++)
		{
			fputc(byte, out);
			byte = i ^ fgetc(in);
		}
		fclose(in);
		fclose(out);
	}

}

void Init()
{
	char text[256];
	HMODULE hmod = 0;
	// could do a better way but 
	while (!hmod)
	{
		hmod = GetModuleHandleA("mr2.dll");
	}
	if (hmod)
	{
		auto pattern = hook::module_pattern(GetModuleHandleA("mr2.dll"), "8B 84 24 8C 00 00 00 53 55 56 57");
		if (!pattern.count_hint(1).empty())
		{
			auto ptr = pattern.get(0).get<int>(0);
			InjectHook((int)ptr + 0x13, HookDecryptCarInfo, PATCH_CALL);

		}
	}
}



extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Init), nullptr, 0, nullptr);
	}
}
