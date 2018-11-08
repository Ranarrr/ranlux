#include "createmove.hpp"

createmove* createmove::_createmove = nullptr;

std::shared_ptr<createmove> createmove::get() {
	if( !_createmove )
		_createmove = new createmove();

	return std::shared_ptr<createmove>( _createmove );
}

bool __fastcall createmove::hkcreatemove( void *ecx, int edx, float frametime, c_usercmd *cmd ) { // in clientmode cmd will never be null
	if( !cmd->command_number )
		return true;

	globals::localplayer = globals::entitylist->get_cliententity( globals::engine->get_localplayer() );

	if( globals::localplayer == nullptr || !globals::localplayer->is_alive() )
		return true;

	//aimbot_rage::get()->frame( cmd ); still using some stuff like vmt class tho

	/*angle delta = current_angles - previous_angles; // faceit bypass?

	mousedx = ( previous_angles.y - delta.y ) / m_yaw;
	mousedy = -( previous_angles.x - delta.x ) / m_pitch;*/


	if( cmd->buttons&IN_JUMP ) // bhop
		if( !( globals::localplayer->flags() & FL_ONGROUND ) )
			cmd->buttons &= ~IN_JUMP;

	utility::get()->normalizeangle( cmd->viewangles );

	return false;
}