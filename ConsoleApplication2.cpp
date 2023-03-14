// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<Windows.h>
#include<iostream>
#include<psapi.h>
using namespace  std;
DWORD pid,write;
DWORD read /*0x0113FB74*/;//47BF3110
int value;
SIZE_T written;
int main()
{


	MEMORY_BASIC_INFORMATION info;
	SYSTEM_INFO sysinfo;
	//LPSTR path;
	
	HMODULE* lphModuel;
		HWND hwnd = FindWindowA(0, ("hackme"));
		GetWindowThreadProcessId(hwnd, &pid);
		std::cout << pid << std::endl;
		cout << "Enter Memory Address:";
		cin >>hex >>read;
		cout <<"Address is:" <<read<< endl;
		HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		//GetProcessImageFileNameA(phandle,path,sizeof(path));
		//INCOMPLETE :- https://stackoverflow.com/questions/14467229/get-base-address-of-process
		//BOOL rst = EnumProcessModules(phandle, lphModuel, byte(sizeof(lphModuel)),);
		GetSystemInfo(&sysinfo);
		written = VirtualQueryEx(phandle, (LPCVOID)sysinfo.dwPageSize,&info, sizeof(MEMORY_BASIC_INFORMATION));
		cout << "Page Size:" << sysinfo.dwPageSize << endl;
		cout << "BaseAddress:" << info.BaseAddress << endl;
		cout << "AllocationAddress:" << info.AllocationBase << endl;
		cout << "RegionSize:" << info.RegionSize << endl;;
		
		while (1) {
			ReadProcessMemory(phandle, (void*)read, &value, sizeof(value), 0);
			std::cout << "Value:";
			std::cout << value << std::endl;
			value = value + 1;
			WriteProcessMemory(phandle, (LPVOID)read, &value, sizeof(write), NULL);
			//cout << "Written:" << written << endl;
			Sleep(1000);
			//write++;
		}
		system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
