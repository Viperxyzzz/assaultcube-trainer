#include <iostream>

#include "proc.h"
#include "draw.h"



int main()
{
	Proc proc;
	DWORD procId = proc.GetProcId(L"ac_client.exe");

	uintptr_t moduleBase = proc.GetModuleBaseAddress(procId, L"ac_client.exe");

	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	uintptr_t dynamicPtr = moduleBase + 0x10f4f4;
	

	std::vector<unsigned int> ammoOffsets = { 0x374, 0x14,0x0 };
	uintptr_t ammoAddr = proc.FindDMAAddy(hProcess, dynamicPtr, ammoOffsets);
	uintptr_t healthAddr = proc.FindDMAAddy(hProcess, dynamicPtr, { 0xf8 });
	
	LocalPlayer player(hProcess);
	entityList entities(hProcess);

	player.GetLocalPlayerInfo();
	entities.GetTotalPlayers();
	entities.GetEntitiesInfo();
	
	GDI_drawing draw;
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), true);
	draw.TargetWnd = FindWindow(0, L"AssaultCube");
	draw.HDC_Desktop = GetDC(draw.TargetWnd);
	draw.SetupDrawing(draw.HDC_Desktop, draw.TargetWnd);
	Vector3 screen;
	draw.esp(entities, player, screen);
	
	while (true)
	{
		player.GetLocalPlayerInfo();
		entities.GetTotalPlayers();
		entities.GetEntitiesInfo();
		if (GetKeyState('X') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			for (int i = 0; i < entities.totalPlayers; i++)
			{
				std::cout << "#########ENTITIES ############" << std::endl;
				std::cout << "##############################" << std::endl;
				std::cout << "##############################" << std::endl;
				std::cout << "Entity name : " << entities.list[i].name << std::endl;
				std::cout << "Entity health : " << entities.list[i].health << std::endl;
				std::cout << "Entity x : " << entities.list[i].headPosition.x << std::endl;
				std::cout << "Entity y : " << entities.list[i].headPosition.y << std::endl;
				std::cout << "Entity z : " << entities.list[i].headPosition.z << std::endl;

			}
			std::cout << "############################" << std::endl;
			std::cout << "############################" << std::endl;
			std::cout << "############################" << std::endl;
			std::cout << "PLAYER !!!" << std::endl;
			std::cout << "Player health : " << player.health << std::endl;
			std::cout << "Player x : " << player.headPosition.x << std::endl;
			std::cout << "Player y : " << player.headPosition.y << std::endl;
			std::cout << "Player z : " << player.headPosition.z << std::endl;
			std::cout << "Player xn : " << player.feetPosition.x << std::endl;
			std::cout << "Player yn : " << player.feetPosition.y << std::endl;
			std::cout << "Player zn : " << player.feetPosition.z << std::endl;
		}
	}
	


}