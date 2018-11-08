#include "main.hpp" // i do .hpp, because this is the correct extension for c++.

// ranlux is a CS:GO base (not finished, and probably never will), that is coded by Ranarrr (code that wasn't has been credited appropriately)
// I started this 8th of July 2017, as a project for a friend, turned out he ripped me off, and leaked this source on his own Github account.
// Tried to have it removed, but github wouldn't even respond, so that's that.
// Do note that this source is under the General Public License v3.0 which states that you can modify, share and use this software/source as you wish.
// I will however not include a .DLL file for you to actually use, you will have to compile this yourself.

// here's where im going to put all my global objects, stated as such:
// IVEngine *g_pEngine;

namespace globals {
	uintptr_t				clientmodule;
	ibaseclient				*client;
	vengineclient			*engine;
	vgui::isurface			*surface;
	vgui::ipanel			*panel;
	IClientMode				*clientmode;
	CEntityList				*entitylist;
	IVEngineServer			*engineserver;
	IVDebugOverlay			*debugoverlay;
	IGameEventManager2		*gameevents;
	IEngineTrace			*enginetrace;

	c_csplayer				*localplayer;

	std::vector<c_csplayer*>	playersinserver;

	Vector2D				screensize;
}

bool setup() {
	// here's where you initialize everything, interfaces, netvars, etc..
	// if you're running a console in your cheat you can initialize configs.
	if( !globals::clientmodule )
		globals::clientmodule = ( uintptr_t ) ( GetModuleHandle( "client.dll" ) );

	// init the shit here
	interfacefactory::get()->setup();
	netvar::get()->setup();
	offsets::get()->setup();
	hooks::get()->setup();

	utility::get()->printtoconsole( "\nINJECTED." );

	// still a nasty trick?
	while( globals::screensize.x == 0 && globals::screensize.y == 0 ) {
		globals::engine->get_screensize( globals::screensize.x, globals::screensize.y );
		Sleep( 500 );
	}

	return true;
}

// i'll make two modes of entrypoint, so one for debug purposes, where you can load and unload your module multiple times
// second for release purposes, won't get debug symbols, and won't be able to unload the module
#ifdef _DEBUG
bool pressed( int key ) {
	return ( GetAsyncKeyState( key ) & ( 1 << 15 ) ) != 0;
} 

DWORD __stdcall startthread( void *param ) { // passing this module, so we can shut down this thread if we choose to unload our module.
	HMODULE module = static_cast< HMODULE >( param );

	// if setup succeeds, it will check if you're pressing ctrl and the numpad * and when you're not, it just sleeps a little. 
	// if you do press those two simultaneously, it will exit the while loop
	// and continue to kill the thread, if you've hooked something, you should destroy those hooks, and then you can exit the thread safely.
	if( setup() )
		while( !( pressed( 0xA2 ) && pressed( 0x6A ) ) ) // CTRL + NUMPAD *
			Sleep( 10 );

	hooks::get()->unhook();
	utility::get()->printtoconsole( "------------------" );
	utility::get()->printtoconsole( "\t\tunhooked\n" );
	utility::get()->printtoconsole( "------------------\n" );
	FreeLibraryAndExitThread( module, 0 );
}

// when you make a dynamic link library project, you need to state dllmain as your entrypoint, otherwise it will not compile.
BOOL WINAPI DllMain( HINSTANCE hInst, uintptr_t dwReason, LPVOID pReserved ) {
	if( dwReason == DLL_PROCESS_ATTACH ) {
																		// if you're making a cheats' config system based on the cheats directory, you should grab the directory path here.
		::CreateThread( nullptr, 0, &startthread, hInst, 0, nullptr );	// here we create the thread our "unload" feature will run on
		
	}

	return TRUE; // always return true. To say that the loading of the dll was successful
}
#else
// when you make a .dll project, you need to state dllmain as your entrypoint, otherwise it will not compile.
BOOL WINAPI DllMain( HINSTANCE hInst, uintptr_t dwReason, LPVOID pReserved ) {
	if( dwReason == DLL_PROCESS_ATTACH ) {
		// if you're making a cheats' config system based on the cheats directory, you should grab the directory path here.
		
		return setup();
	}

	return TRUE;
}
#endif // _DEBUG