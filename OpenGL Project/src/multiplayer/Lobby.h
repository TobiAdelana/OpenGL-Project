#pragma once
#include <steam\steam_api.h>
#include <steam\steam_gameserver.h>

class Lobby
{
public:
	Lobby();
	void Create();
	void Join();
	~Lobby();
};

