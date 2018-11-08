#include "aimbot_legit.hpp"

aimbot_legit *aimbot_legit::get() {
	static aimbot_legit aimbot_legit_;
	return &aimbot_legit_;
}

void aimbot_legit::get_bestplayer() {
	float best_fov;

	for( int i = 1; i <= 64; ++i ) {
		if( is_validplayer( i ) ) {
		}
	}
}

float get_fov(Vector pos, angle ang ) {

	return 0.f;

}

bool aimbot_legit::is_validplayer( int idx ) {
	c_csplayer *ent = globals::entitylist->get_cliententity( idx );

	if( ent == nullptr )
		return false;

	if( !ent->is_alive() )
		return false;

	if( !ent->is_dormant() )
		return false;

	targetpos = ent->get_eyepos(); // replace with better hitbox getting.

	if( !utility::get()->is_playervisible( ent, targetpos ) )
		return false;

	return true;
}

void aimbot_legit::drop_target() {
	if( !is_validplayer( targetidx ) )
		targetidx = -1;
}

/*void aimbot_legit::frame( CUserCmd *cmd ) {

	drop_target();

	if( targetidx == -1 ) {
		get_bestplayer();
		return;
	}

	if( targetidx ) {
	}

}*/