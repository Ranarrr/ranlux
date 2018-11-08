#include "painttraverse.hpp"

painttraverse* painttraverse::_painttraverse = nullptr;

std::shared_ptr<painttraverse> painttraverse::get() {
	if( !_painttraverse )
		_painttraverse = new painttraverse();

	return std::shared_ptr<painttraverse>( _painttraverse );
}

bool painttraverse::pressed( int key ) {
	return ( GetAsyncKeyState( key ) & ( 1 << 15 ) ) != 0;
}

void __fastcall painttraverse::hkpainttraverse( vgui::ipanel *ecx, void *edx, vgui::vpanel vguipanel, bool forcerepaint, bool allowforce ) {

	const char* panelname = globals::panel->GetName( vguipanel );

	if( strstr( panelname, "FocusOverlayPanel" ) != 0 ) {
		// sorry, snapchat..
		// i was thinking, to optimize my hack, i can loop through all entities that are actually on the server.

		if( GetAsyncKeyState( VK_TAB ) )
			offsets::get()->RevealRanks();

		/*if( ( GetAsyncKeyState( VK_CONTROL ) & 1 && GetAsyncKeyState( VK_HOME ) & 1 ) )
			utility::get()->printtoconsole( "is_x360: %X", globals::engineserver->is_x360() );*/

		c_csplayer *localplayer = globals::entitylist->get_cliententity( globals::engine->get_localplayer() );

		if( globals::engine->in_game() ){
			for( int i = 1; i <= 64; ++i ) {

				c_csplayer *entity = globals::entitylist->get_cliententity( i );

				if( entity == nullptr )
					continue;

				if( entity == localplayer || entity->teamnum() == localplayer->teamnum() )
					continue;

				if( !entity->is_alive() )
					continue;

				if( entity->is_dormant() )
					continue;

				int entteamnum = entity->teamnum();

				if( entteamnum == 1 )
					continue;

				if( entteamnum == 2 /*&& !utility::get()->is_playervisible( entity, entity->origin() )*/ )
					globals::debugoverlay->AddBoxOverlay( entity->origin(), entity->bbmins(), entity->bbmaxs(), entity->get_absangles(), 255, 0, 0, 10, 0.033f ); // this looks so
				/*else if( utility::get()->is_playervisible( entity, entity->origin() ) )
					globals::debugoverlay->AddBoxOverlay( entity->origin(), entity->bbmins(), entity->bbmaxs(), entity->get_absangles(), 255, 0, 0, 0, 0.1f );*/																																		  
																																								  // good in-game :p altough it's flickering alot..
				// rly? how come? because of the time
				// what if you set it to 0? still flickers :( makes no sense ;o shouldn't flicker ikr.. -1?
				
				else if( entteamnum == 3 /*&& !utility::get()->is_playervisible( entity, entity->origin() )*/ )
					globals::debugoverlay->AddBoxOverlay( entity->origin(), entity->bbmins(), entity->bbmaxs(), entity->get_absangles(), 0, 50, 255, 10, 0.033f );
				/*else if( utility::get()->is_playervisible( entity, entity->origin() ) )
					globals::debugoverlay->AddBoxOverlay( entity->origin(), entity->bbmins(), entity->bbmaxs(), entity->get_absangles(), 0, 50, 255, 0, 0.1f );*/
			}
		}
	}

	globalhooks::panelhook.get<void( __thiscall* )( vgui::ipanel *, vgui::vpanel, bool, bool ) >( 41 )( ecx, vguipanel, forcerepaint, allowforce );
}

void painttraverse::drawesp( c_csplayer *local, c_csplayer *entity, int idx ) {

}

/*void get_actualmaxclients() {
	static bool once = false;

	if( !once ||  ) {
		for( int i = 1; i <= 64; ++i ) { // i'll just do it here.
			c_csplayer *entity = globals::entitylist->get_cliententity( i );
			if( entity == nullptr )
				continue;

			globals::playersinserver.push_back( entity );
		}
		once = true;
	}
}*/