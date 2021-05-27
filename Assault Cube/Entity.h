#pragma once
#include <vector>
#include <Windows.h>
#include <iostream>
#include "math.h"


class Entity
{
	HANDLE hProcess;
public:
	char name[16];
	int health, team, base;
	Vector3 headPosition;
	Vector3 feetPosition;
	void GetEntityInfo(int i);
	Entity(HANDLE hProcess);
	Entity();
};

class LocalPlayer
{
	HANDLE hProcess;
public:
	Vector3 headPosition;
	Vector3 feetPosition;
	int health, team, base;
	float viewMatrix[16];
	void GetLocalPlayerInfo();
	LocalPlayer(HANDLE hProcess);
};


struct entityList
{
	HANDLE hProcess;
	
public:
	entityList(HANDLE hProcess);
	void GetTotalPlayers();
	void GetEntitiesInfo();


	int totalPlayers;
	std::vector<Entity> list;
};
