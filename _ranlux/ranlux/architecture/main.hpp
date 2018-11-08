#ifndef MAIN_HPP
#define MAIN_HPP

#pragma once

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#define CHECK_VALID( _v ) 0

inline float BitsToFloat( unsigned long i ) {
	return *reinterpret_cast<float*>( &i );
}

#define FLOAT32_NAN_BITS     (unsigned long)0x7FC00000
#define FLOAT32_NAN          BitsToFloat( FLOAT32_NAN_BITS )

#define float_NAN FLOAT32_NAN

#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <time.h>
#include <float.h>
#include <fstream>
#include <memory>
#include <vector>
#include <assert.h>

#include "sdk\sdk.hpp"
#include "useful\draw.hpp"
#include "useful\interfaces.hpp"
#include "useful\netvar.hpp"
#include "useful\offsets.hpp"
#include "tools\vmthook.hpp"
#include "hooks\hooks.hpp"
#include "useful\utility.hpp"

// here's the external globals gonna be, so we don't get unresolved external error, stated as such: im way to used to using hungarian notation..
// extern IVEngine *g_pEngine; let's fuck it?

// needa move externals that doesn't belong here to their parent header file.
namespace globals {
	extern uintptr_t				clientmodule;

	extern Vector2D					screensize;
}
#endif // !MAIN_HPP