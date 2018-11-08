#include "aimbot_rage.hpp"

aimbot_rage *aimbot_rage::get() {
	static aimbot_rage aimbot_rage_;
	return &aimbot_rage_;
}

void aimbot_rage::drop_target() {
	if( !is_validplayer( targetidx ) ) {
		targetidx = -1;
	}
}

void aimbot_rage::get_besttarget() {
	for( int i = 1; i <= 64; ++i ) {
		if( is_validplayer( i ) ) {
			targetidx = i;
			return;
		}
	}
}

bool aimbot_rage::is_validplayer( int idx ) {
	c_csplayer *ent = globals::entitylist->get_cliententity( idx );

	if( ent == nullptr )
		return false;

	if( !ent->is_alive() ) // u always gotta check if the player is alive before checking dormant
		return false;

	if( ent->is_dormant() )
		return false;

	if( ent->teamnum() == globals::localplayer->teamnum() )
		return false;

	// i don't have time to make proper hitbox uhh getting player hitbox

	targetpos = ent->get_eyepos();

	if( !utility::get()->is_playervisible( ent, targetpos ) )
		return false;

	return true;
}

void calc_angle( Vector vecSource, Vector vecEnd, angle& vecOut ) {
	auto delta( vecSource - vecEnd );
	auto hyp = delta.Length2D();

	vecOut.x = RAD2DEG( atan( delta.z / hyp ) );
	vecOut.y = RAD2DEG( atan( delta.y / delta.x ) );
	vecOut.z = 0.0f;

	if( delta.x >= 0.0f )
		vecOut.y += 180.0f;
}

inline void VectorAngles( Vector& forward, angle& angles ) {
	if( forward[ 1 ] == 0.0f && forward[ 0 ] == 0.0f ) {
		angles[ 0 ] = ( forward[ 2 ] > 0.0f ) ? 270.0f : 90.0f;
		angles[ 1 ] = 0.0f;
	} else {
		float len2d = forward.Length2D();

		angles[ 0 ] = RAD2DEG( atan2f( -forward[ 2 ], len2d ) );
		angles[ 1 ] = RAD2DEG( atan2f( forward[ 1 ], forward[ 0 ] ) );

		if( angles[ 0 ] < 0.0f ) angles[ 0 ] += 360.0f;
		if( angles[ 1 ] < 0.0f ) angles[ 1 ] += 360.0f;
	}

	angles[ 2 ] = 0.0f;
}

void aimbot_rage::frame( c_usercmd *cmd ) {

	drop_target();

	if( targetidx == -1 ) {
		get_besttarget();
		return;
	}

	if( targetidx ) {
		calc_angle( globals::localplayer->get_eyepos(), targetpos, targetang ); // don't need any getfov func, so will be 180 fov all time

		targetang -= globals::localplayer->get_punch() * 2.f;

		Vector vMove( cmd->forwardmove, cmd->sidemove, cmd->upmove );
		float flSpeed = sqrt( vMove.x * vMove.x + vMove.y * vMove.y ), flYaw;
		angle vMove2;
		angle vRealView( cmd->viewangles );
		VectorAngles( vMove, vMove2 );

		VectorCopy( targetang, cmd->viewangles );

		flYaw = DEG2RAD( cmd->viewangles.y - vRealView.y + vMove2.y );
		cmd->forwardmove = cos( flYaw ) * flSpeed;
		cmd->sidemove = sin( flYaw ) * flSpeed;

		cmd->buttons |= IN_ATTACK;
	}
}