#ifndef NETVAR_HPP
#define NETVAR_HPP

#pragma once

#include "../main.hpp"

class netvar {
	netvar() {};
	static netvar *_netvar;

public:
	static std::shared_ptr<netvar> get();
	~netvar() { _netvar = nullptr; }

	void setup();
};

#endif // !NETVAR_HPP