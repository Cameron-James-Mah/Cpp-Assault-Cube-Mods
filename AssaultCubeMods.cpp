#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
       

//Local player base address
DWORD Base = 0x50F4F4;

//Player offsets
DWORD Health = 0xF8;
DWORD Armor = 0xFC;
DWORD Grenade = 0x158;
DWORD Speed = 0x80;
DWORD primaryMag = 0x150;
DWORD secondaryMag = 0x13c;


int main()
{
	HWND hwnd = FindWindowA(0, ("AssaultCube")); 
	if (hwnd == 0) {
		std::cout << "Can't find window" << std::endl;
	}
	else {
		DWORD pid;
		GetWindowThreadProcessId(hwnd, &pid);
		HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		DWORD dynamicPlayer;
		ReadProcessMemory(pHandle, LPCVOID(0x50F4F4), &dynamicPlayer, sizeof(dynamicPlayer), 0);
		int modGrenade = 9999;
		int modHp = 9999;
		int modArmor = 9999;
		int modPrimaryMag = 9999;
		int modSecondaryMag = 9999;
		
		while (true) {
			WriteProcessMemory(pHandle, LPVOID(dynamicPlayer+Grenade), &modGrenade, sizeof(modGrenade), 0);
			WriteProcessMemory(pHandle, LPVOID(dynamicPlayer + Health), &modHp, sizeof(modHp), 0);
			WriteProcessMemory(pHandle, LPVOID(dynamicPlayer + Armor), &modArmor, sizeof(modArmor), 0);
			WriteProcessMemory(pHandle, LPVOID(dynamicPlayer + primaryMag), &modPrimaryMag, sizeof(modPrimaryMag), 0);
			WriteProcessMemory(pHandle, LPVOID(dynamicPlayer + secondaryMag), &modPrimaryMag, sizeof(modPrimaryMag), 0);
			
			Sleep(500);
		}
	}
}

