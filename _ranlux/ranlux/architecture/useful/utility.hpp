#ifndef UTILITY_HPP
#define UTILITY_HPP

#pragma once

#include "../main.hpp"

class Vector;
class angle;
class c_csplayer;

class utility { // using smart pointers (kept alive by reference count)
	utility() {};
	static utility *_utility;

public:
	static std::shared_ptr<utility> get();
	~utility() { _utility = nullptr; }

	// findpattern that accepts mask within pattern shown as such:
	// 8B E8 ? ? ? ?
	PBYTE findpattern( std::string module, const char *ccPattern );

	void printtoconsole( const char* szMsg, ... );
	void normalizeangle( angle ang );

	bool pressed( int key );
	bool is_playervisible( c_csplayer *player, const Vector end );
};

#endif // !UTILITY_HPP