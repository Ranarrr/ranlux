#ifndef AIMBOT_RAGE_HPP
#define AIMBOT_RAGE_HPP

#pragma once

#include "../main.hpp"

class CUserCmd;
class c_csplayer;

class aimbot_rage {
	aimbot_rage() {};

	int targetidx;
	angle targetang;
	Vector targetpos;

public:
	static aimbot_rage *get();

	void frame( c_usercmd *cmd );
	void get_besttarget();
	void drop_target();

	bool is_validplayer( int idx );
};

#endif // !AIMBOT_RAGE_HPP