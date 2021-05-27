#include "Entity.h"

DWORD LocalPlayerOffset = 0x509B74;
DWORD RVSF_Team = 0x32C;
DWORD Viewx = 0x40;
DWORD Viewy = 0x44;
DWORD EntityBaseOffset = 0x50F4F8;
DWORD PlayerCountAddress = 0x50F500;
DWORD xPosOffset = 0x4;
DWORD yPosOffset = 0x8;
DWORD zPosOffset = 0xC;
DWORD xPosOffsetN = 0x34;
DWORD yPosOffsetN = 0x38;
DWORD zPosOffsetN = 0x3C;
DWORD pistolMag = 0x70;
DWORD RifleMag = 0x128;
DWORD RifleAmmo = 0x150;
DWORD GrenadeAmmount = 0x158;
DWORD PlayerSpeed = 0x80;
DWORD ViewMatrixAddress = 0x501AE8;
DWORD Health = 0xF8;
DWORD ForceAttack = 0x224;
DWORD nameOffset = 0x225;
DWORD numberofplayers = 0x50F500;


Entity::Entity(HANDLE hProcess)
{
	this->hProcess = hProcess;
}

Entity::Entity()
{
	;
}

void Entity::GetEntityInfo(int i)
{
	ReadProcessMemory(hProcess, (LPCVOID)EntityBaseOffset, &this->base, sizeof(this->base), nullptr);
	ReadProcessMemory(hProcess, (LPCVOID)(this->base + i * 0x04), &this->base, sizeof(this->base), nullptr);
	if (this->base != 0)
	{
		ReadProcessMemory(hProcess, (LPCVOID)(this->base + RVSF_Team), &this->team, sizeof(this->team), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(this->base + Health), &this->health, sizeof(this->health), nullptr);
		std::cout << this->health << std::endl;
		ReadProcessMemory(hProcess, (LPCVOID)(this->base + nameOffset), &this->name, sizeof(this->name), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(this->base + xPosOffset), &this->headPosition.x, sizeof(this->headPosition.x), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(this->base + yPosOffset), &this->headPosition.y, sizeof(this->headPosition.y), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(this->base + zPosOffset), &this->headPosition.z, sizeof(this->headPosition.z), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(this->base + xPosOffsetN), &this->feetPosition.x, sizeof(this->feetPosition.x), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(this->base + yPosOffsetN), &this->feetPosition.y, sizeof(this->feetPosition.y), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(this->base + zPosOffsetN), &this->feetPosition.z, sizeof(this->feetPosition.z), nullptr);


	}
}

LocalPlayer::LocalPlayer(HANDLE hProcess)
{
	this->hProcess = hProcess;
}

void LocalPlayer::GetLocalPlayerInfo()
{
	//WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);
	ReadProcessMemory(hProcess,(LPCVOID)LocalPlayerOffset, &this->base, sizeof(this->base),nullptr);
	ReadProcessMemory(hProcess,(LPCVOID)(this->base + RVSF_Team), &this->team, sizeof(this->team), nullptr);
	ReadProcessMemory(hProcess, (LPCVOID)(this->base + xPosOffset), &this->headPosition.x, sizeof(this->headPosition.x), nullptr);
	ReadProcessMemory(hProcess, (LPCVOID)(this->base + yPosOffset), &this->headPosition.y, sizeof(this->headPosition.y), nullptr);
	ReadProcessMemory(hProcess, (LPCVOID)(this->base + zPosOffset), &this->headPosition.z, sizeof(this->headPosition.z), nullptr);
	ReadProcessMemory(hProcess, (LPCVOID)(this->base + xPosOffsetN), &this->feetPosition.x, sizeof(this->feetPosition.x), nullptr);
	ReadProcessMemory(hProcess, (LPCVOID)(this->base + yPosOffsetN), &this->feetPosition.y, sizeof(this->feetPosition.y), nullptr);
	ReadProcessMemory(hProcess, (LPCVOID)(this->base + zPosOffsetN), &this->feetPosition.z, sizeof(this->feetPosition.z), nullptr);
	ReadProcessMemory(hProcess, (LPCVOID)(this->base + Health), &this->health, sizeof(this->health), nullptr);
	ReadProcessMemory(hProcess, (LPCVOID)0x501AE8, &this->viewMatrix, sizeof(this->viewMatrix), nullptr);
}

entityList::entityList(HANDLE hProcess)
{
	this->hProcess = hProcess;
}

void entityList::GetTotalPlayers()
{
	ReadProcessMemory(hProcess, (LPCVOID)(numberofplayers), &this->totalPlayers, sizeof(this->totalPlayers), nullptr);
	
}	

void entityList::GetEntitiesInfo()
{
	list.resize(totalPlayers);
	for (int i = 1; i < this->totalPlayers; i++)
	{
		ReadProcessMemory(hProcess, (LPCVOID)EntityBaseOffset, &list[i].base, sizeof(list[i].base), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(list[i].base + i * 0x04), &list[i].base, sizeof(list[i].base), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(list[i].base + RVSF_Team), &list[i].team, sizeof(list[i].team), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(list[i].base + Health), &list[i].health, sizeof(list[i].health), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(list[i].base + nameOffset), &list[i].name, sizeof(list[i].name), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(list[i].base + xPosOffset), &list[i].headPosition.x, sizeof(list[i].headPosition.x), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(list[i].base + yPosOffset), &list[i].headPosition.y, sizeof(list[i].headPosition.y), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(list[i].base + zPosOffset), &list[i].headPosition.z, sizeof(list[i].headPosition.z), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(list[i].base + xPosOffsetN), &list[i].feetPosition.x, sizeof(list[i].feetPosition.x), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(list[i].base + yPosOffsetN), &list[i].feetPosition.y, sizeof(list[i].feetPosition.y), nullptr);
		ReadProcessMemory(hProcess, (LPCVOID)(list[i].base + zPosOffsetN), &list[i].feetPosition.z, sizeof(list[i].feetPosition.z), nullptr);
	}
}