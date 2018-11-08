#ifndef AIMBOT_LEGIT_HPP
#define AIMBOT_LEGIT_HPP

#pragma once

#include "../main.hpp"

class aimbot_legit {
	aimbot_legit() {};

	Vector targetpos;
	angle targetang;
	int targetidx;

public:
	static aimbot_legit *get();

	void frame( c_usercmd *cmd );
	void drop_target();
	void get_bestplayer();

	bool is_validplayer( int idx );
};

#endif // !AIMBOT_LEGIT_HPP