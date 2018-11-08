#ifndef SDK_HPP
#define SDK_HPP

#pragma once

#include "../tools/foi.hpp"
#include "angle.hpp"
#include "color.hpp"
#include "enums.hpp"
#include "vector.hpp"

namespace netvars {
	extern uintptr_t m_iTeamNum, m_iHealth, m_lifeState, m_vecViewoffset, m_aimPunchangle,
		m_vecOrigin, m_Collision;
}

typedef float matrix3x4[ 3 ][ 4 ];

#define M_PI_F 3.14159265358979323846f

#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )

#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2

#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1<<3)	// player jumping out of water
#define FL_ONTRAIN				(1<<4)	// Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<5)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<6)	// Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<7)	// Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<8)	// Is a player
#define FL_FAKECLIENT			(1<<9)	// Fake client, simulated server side; don't send network messages to them
#define	FL_INWATER				(1<<10)	// In water

// Note: These flags need to match the bspfile.h DISPTRI_TAG_* flags.
#define DISPSURF_FLAG_SURFACE		(1<<0)
#define DISPSURF_FLAG_WALKABLE		(1<<1)
#define DISPSURF_FLAG_BUILDABLE		(1<<2)
#define DISPSURF_FLAG_SURFPROP1		(1<<3)
#define DISPSURF_FLAG_SURFPROP2		(1<<4)

#pragma region MASKS

#define DISPSURF_FLAG_SURFACE		(1<<0)
#define DISPSURF_FLAG_WALKABLE		(1<<1)
#define DISPSURF_FLAG_BUILDABLE		(1<<2)
#define DISPSURF_FLAG_SURFPROP1		(1<<3)
#define DISPSURF_FLAG_SURFPROP2		(1<<4)

// lower bits are stronger, and will eat weaker brushes completely
#define	CONTENTS_EMPTY			0		// No contents

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	CONTENTS_OPAQUE

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200

// unused
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
// CONTENTS_OPAQUE + SURF_NODRAW count as CONTENTS_OPAQUE (shadow-casting toolsblocklight textures)
#define CONTENTS_BLOCKLIGHT		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

// NOTE: These are stored in a short in the engine now.  Don't use more than 16 bits
#define	SURF_LIGHT		0x0001		// value will hold the light strength
#define	SURF_SKY2D		0x0002		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
#define	SURF_SKY		0x0004		// don't draw, but add to skybox
#define	SURF_WARP		0x0008		// turbulent water warp
#define	SURF_TRANS		0x0010
#define SURF_NOPORTAL	0x0020	// the surface can not have a portal placed on it
#define	SURF_TRIGGER	0x0040	// FIXME: This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
#define	SURF_NODRAW		0x0080	// don't bother referencing the texture

#define	SURF_HINT		0x0100	// make a primary bsp splitter

#define	SURF_SKIP		0x0200	// completely ignore, allowing non-closed brushes
#define SURF_NOLIGHT	0x0400	// Don't calculate light
#define SURF_BUMPLIGHT	0x0800	// calculate three lightmaps for the surface for bumpmapping
#define SURF_NOSHADOWS	0x1000	// Don't receive shadows
#define SURF_NODECALS	0x2000	// Don't receive decals
#define SURF_NOPAINT	SURF_NODECALS	// the surface can not have paint placed on it
#define SURF_NOCHOP		0x4000	// Don't subdivide patches on this surface
#define SURF_HITBOX		0x8000	// surface is part of a hitbox

// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define	MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks fluid movement
#define	MASK_NPCFLUID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
// water physics in these contents
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define	MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define	MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// bullets see these as solid, except monsters (world+brush only)
#define MASK_SHOT_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// to check for player visibillity
#define MASK_REAL_VISIBLE			(MASK_SHOT|CONTENTS_GRATE)																										// this <- == 0x4600400B
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC_FLUID	(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

// UNDONE: This is untested, any moving water
#define MASK_CURRENT				(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)

// everything that blocks corpse movement
// UNDONE: Not used yet / may be deleted
#define	MASK_DEADSOLID				(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)
#pragma endregion

class c_csplayer {
public:
	int health() {
		return *foi::make_ptr<int*>( this, netvars::m_iHealth );
	}

	angle& get_absangles() {
		return foi::getvfunc< angle&( __thiscall* ) ( void * ) >( this, 11 )( this );
	}

	int get_idx() {
		return foi::getvfunc< int( __thiscall* ) ( void* ) >( this, 76 )( this );
	}

	Vector bbmins() {
		return *foi::make_ptr<Vector*>( this, netvars::m_Collision + 0x8 );
	}

	Vector bbmaxs() {
		return *foi::make_ptr<Vector*>( this, netvars::m_Collision + 0x14 );
	}

	Vector origin() {
		return *foi::make_ptr<Vector*>( this, netvars::m_vecOrigin );
	}

	int teamnum() {
		return *foi::make_ptr<int*>( this, netvars::m_iTeamNum );
	}

	Vector get_eyepos() {
		return origin() + *foi::make_ptr<Vector*>( this, netvars::m_vecViewoffset );
	}

	angle get_punch() {
		return *foi::make_ptr<angle*>( this, netvars::m_aimPunchangle );
	}

	bool is_dormant() {
		__asm {
			mov edi, this
			lea ecx, [ edi + 0x8 ]
			mov edx, dword ptr ds : [ecx]
			call[ edx + 0x24 ]
		}
	}

	bool is_alive() {
		return ( *foi::make_ptr<int*>( this, netvars::m_lifeState ) == LIFE_ALIVE );
	}

	int flags() {
		return *foi::make_ptr<int*>( this, 0x100 );
	}
};

// neither this.
struct player_info_t {
	char __pad0[ 0x8 ];

	int xuidlow;
	int xuidhigh;

	char name[ 128 ];
	int userid;			// local server user ID, unique while server is running
	char guid[ 33 ];	// global unique player identifer

	char __pad1[ 0x17B ];
};

class local_player {
	float _frametime;

public:

	void set_frametime( float frametime ) {
		_frametime = frametime;
	}

	float get_frametime() {
		return _frametime;
	}
};

struct recvtable;

struct recvprop {
	char					*varname;
	SendPropType			recvtype;
	int						flags;
	int						stringbuffersize;
	bool					is_inarray;
	const void				*extradata;
	recvprop				*arrayprop;
	void					*arraylengthproxy;
	void					*proxyfn;
	void					*datatableproxy;
	recvtable				*datatable;
	int						offset;
	int						elementstride;
	int						elements;
	const char				*parentarrayparentname;
};

struct recvtable {
	recvprop		*props;
	int				nprops;
	void			*decoder;
	char			*nettablename;
	bool			is_initialized;
	bool			is_inmainlist;
};

// linked list of classes
struct clientclass {
	void*			createfn;
	void*			createeventfn;	// Only called for event objects.
	const char		*networkname;	// networked name
	recvtable		*recvtable;		// this class's table of properties.
	clientclass		*next;			// next clientclass
	int				classid;		// managed by the engine.
};

class ibaseclient {
public:
	// Connect appsystem components, get global interfaces, don't run any other init code
	virtual int				Connect( void * ( *appSystemFactory ), void *pGlobals ) = 0;
	virtual int				Disconnect( void ) = 0;
	// run other init code here
	virtual int				Init( void * ( *appSystemFactory ), void *pGlobals ) = 0;
	virtual void			PostInit() = 0;
	// Called once when the client DLL is being unloaded
	virtual void			Shutdown( void ) = 0;
	// Called at the start of each level change
	virtual void			LevelInitPreEntity( char const* pMapName ) = 0;
	// Called at the start of a new level, after the entities have been received and created
	virtual void			LevelInitPostEntity() = 0;
	// Called at the end of a level
	virtual void			LevelShutdown( void ) = 0;
	// Request a pointer to the list of client datatable classes
	virtual clientclass		*get_allclasses( void ) = 0;
	// Called once per level to re-initialize any hud element drawing stuff
	virtual int				HudVidInit( void ) = 0;
	// Called by the engine when gathering user input
	virtual void			HudProcessInput( bool bActive ) = 0;
	// Called oncer per frame to allow the hud elements to think
	virtual void			HudUpdate( bool bActive ) = 0;
	// Reset the hud elements to their initial states
	virtual void			HudReset( void ) = 0;
	// Display a hud text message
	virtual void			HudText( const char * message ) = 0;
	virtual void			ShouldDrawDropdownConsole( void ) = 0;
	// Mouse Input Interfaces
	// Activate the mouse (hides the cursor and locks it to the center of the screen)
	virtual void			IN_ActivateMouse( void ) = 0;
	// Deactivates the mouse (shows the cursor and unlocks it)
	virtual void			IN_DeactivateMouse( void ) = 0;
	// This is only called during extra sound updates and just accumulates mouse x, y offets and recenters the mouse.
	//  This call is used to try to prevent the mouse from appearing out of the side of a windowed version of the engine if
	//  rendering or other processing is taking too long
	virtual void			IN_Accumulate( void ) = 0;
	// Reset all key and mouse states to their initial, unpressed state
	virtual void			IN_ClearStates( void ) = 0;
	// If key is found by name, returns whether it's being held down in isdown, otherwise function returns false
	virtual bool			IN_IsKeyDown( const char *name, bool& isdown ) = 0;
	// Raw keyboard signal, if the client .dll returns 1, the engine processes the key as usual, otherwise,
	//  if the client .dll returns 0, the key is swallowed.
	virtual int				IN_KeyEvent( int eventcode, int /*ButtonCode_t*/ keynum, const char *pszCurrentBinding ) = 0;
	// This function is called once per tick to create the player CUserCmd (used for prediction/physics simulation of the player)
	// Because the mouse can be sampled at greater than the tick interval, there is a separate input_sample_frametime, which
	//  specifies how much additional mouse / keyboard simulation to perform.
	virtual void			CreateMove(
		int sequence_number,			// sequence_number of this cmd
		float input_sample_frametime,	// Frametime for mouse input sampling
		bool active ) = 0;				// True if the player is active (not paused)
};

class CEntityList {
public:
	c_csplayer* get_cliententity( int entnum ) {
		return foi::getvfunc<c_csplayer *( __thiscall * )( void *, int )>( this, 3 )( this, entnum );
	}
	c_csplayer* get_cliententity_from_handle( unsigned long hEnt ) {
		return foi::getvfunc<c_csplayer *( __thiscall * ) ( void *, unsigned long )>( this, 4 )( this, hEnt );
	}
};

class vengineclient {
public:
	void get_screensize( int& width, int& height ) {
		return foi::getvfunc< void( __thiscall * )( void *, int&, int& ) >( this, 5 )( this, width, height );
	}

	bool get_playerinfo( int ent_num, player_info_t *pinfo ) {
		return foi::getvfunc< bool( __thiscall * )( void *, int, player_info_t* ) >( this, 8 )( this, ent_num, pinfo );
	}

	int get_localplayer() {
		return foi::getvfunc< int( __thiscall * )( void * ) >( this, 12 )( this );
	}

	void get_viewangles( angle& vAngles ) {
		return foi::getvfunc< void( __thiscall * )( void *, angle& ) >( this, 18 )( this, vAngles );
	}

	void set_viewangles( angle& vAngles ) {
		return foi::getvfunc< void( __thiscall * )( void *, angle& ) >( this, 19 )( this, vAngles );
	}

	int get_maxclients() {
		return foi::getvfunc< bool( __thiscall * )( void * ) >( this, 20 )( this );
	}

	bool in_game() {
		return foi::getvfunc< bool( __thiscall * )( void * ) >( this, 26 )( this );
	}

	bool connected() {
		return foi::getvfunc< bool( __thiscall * )( void * ) >( this, 27 )( this );
	}

	const matrix3x4 &worldtoscreen() {
		return foi::getvfunc< const matrix3x4 &( __thiscall * )( void * ) >( this, 37 )( this );
	}

	void clientcmd_unrestricted( char  const* cmd ) {
		return foi::getvfunc<void( __thiscall * )( void *, const char* )>( this, 114 )( this, cmd );
	}

	bool is_paused() {
		return foi::getvfunc<bool( __thiscall * )( void * ) >( this, 197 )( this );
	}
};

class IVEngineServer {
public:
	bool is_x360() { // should be self-explanatory, not really anything useful.
		return foi::getvfunc< bool( __thiscall* )( void * ) >( this, 3 )( this );
	}

	int get_entitycount() { // returns all entities in map
		return foi::getvfunc< int( __thiscall* )( void * ) >( this, 20 )( this );
	}

	int get_clientcount() { // idk what the fuck this does, returns high number which makes no sense atm. honestly don't have a fucking clue lol
		return foi::getvfunc< int( __thiscall* ) ( void * ) >( this, 104 )( this );
	}
};

class IGameEvent {
public:
	virtual						~IGameEvent() {};
	virtual const char			*GetName() const = 0;						// get event name

	virtual bool				IsReliable() const = 0;						// if event handled reliable
	virtual bool				IsLocal() const = 0;						// if event is never networked
	virtual bool				IsEmpty( const char *keyName = NULL ) = 0;	// check if data field exists

								// Data access
	virtual bool				GetBool( const char *keyName = NULL, bool defaultValue = false ) = 0;
	virtual int					GetInt( const char *keyName = NULL, int defaultValue = 0 ) = 0;
	virtual unsigned long		GetUint64( const char *keyName = NULL, unsigned long defaultValue = 0 ) = 0;
	virtual float				GetFloat( const char *keyName = NULL, float defaultValue = 0.0f ) = 0;
	virtual const char			*GetString( const char *keyName = NULL, const char *defaultValue = "" ) = 0;
	virtual const wchar_t		*GetWString( char const *keyName = NULL, const wchar_t *defaultValue = L"" ) = 0;

	virtual void				SetBool( const char *keyName, bool value ) = 0;
	virtual void				SetInt( const char *keyName, int value ) = 0;
	virtual void				SetUint64( const char *keyName, unsigned long value ) = 0;
	virtual void				SetFloat( const char *keyName, float value ) = 0;
	virtual void				SetString( const char *keyName, const char *value ) = 0;
	virtual void				SetWString( const char *keyName, const wchar_t *value ) = 0;
};

class IGameEventListener2 {
public:
	virtual	~IGameEventListener2( void ) {};

	// FireEvent is called by EventManager if event just occured
	// KeyValue memory will be freed by manager if not needed anymore
	virtual void FireGameEvent( IGameEvent *event ) = 0;

	virtual int	 GetEventDebugID( void ) = 0;
};

class IGameEventManager2 {
	virtual	~IGameEventManager2( void ) {};

	// load game event descriptions from a file eg "resource\gameevents.res"
	virtual int LoadEventsFromFile( const char *filename ) = 0;

	// removes all and anything
	virtual void  Reset() = 0;

	// adds a listener for a particular event
	virtual bool AddListener( IGameEventListener2 *listener, const char *name, bool bServerSide ) = 0;

	// returns true if this listener is listens to given event
	virtual bool FindListener( IGameEventListener2 *listener, const char *name ) = 0;

	// removes a listener 
	virtual void RemoveListener( IGameEventListener2 *listener ) = 0;

	// create an event by name, but doesn't fire it. returns NULL is event is not
	// known or no listener is registered for it. bForce forces the creation even if no listener is active
	virtual IGameEvent *CreateEvent( const char *name, bool bForce = false, int *pCookie = NULL ) = 0;

	// fires a server event created earlier, if bDontBroadcast is set, event is not send to clients
	virtual bool FireEvent( IGameEvent *event, bool bDontBroadcast = false ) = 0;

	// fires an event for the local client only, should be used only by client code
	virtual bool FireEventClientSide( IGameEvent *event ) = 0;

	// create a new copy of this event, must be free later
	virtual IGameEvent *DuplicateEvent( IGameEvent *event ) = 0;

	// if an event was created but not fired for some reason, it has to bee freed, same UnserializeEvent
	virtual void FreeEvent( IGameEvent *event ) = 0;

	// write/read event to/from bitbuffer
	virtual bool SerializeEvent( IGameEvent *event, void *buf ) = 0;
	virtual IGameEvent *UnserializeEvent( void *buf ) = 0; // create new KeyValues, must be deleted
};

namespace vgui {
	typedef unsigned long hfont;
	typedef unsigned int vpanel;

	struct Vertex_t {
		Vector2D	m_Position;
		Vector2D	m_TexCoord;

		Vertex_t() {}
		Vertex_t( const Vector2D &pos, const Vector2D &coord = Vector2D( 0, 0 ) ) {
			m_Position = pos;
			m_TexCoord = coord;
		}
		void Init( const Vector2D &pos, const Vector2D &coord = Vector2D( 0, 0 ) ) {
			m_Position = pos;
			m_TexCoord = coord;
		}
	};

	class ipanel {
	public:
		const char *GetName( vpanel vguiPanel ) {
			return foi::getvfunc<const char* ( __thiscall * )( void *, vpanel )>( this, 36 )( this, vguiPanel );
		}
	};

	class isurface {
	public:
		void setcolor( color col ) {
			return foi::getvfunc< void( __thiscall * )( void *, int, int, int, int ) >( this, 15 )( this, col.getred(), col.getgreen(), col.getblue(), col.getalpha() );
		}

		void filledrect( Vector2D x, Vector2D y ) {
			foi::getvfunc< void( __thiscall * )( void *, int, int, int, int ) >( this, 16 )( this, x.x, x.y, y.x, y.y );
		}

		void outlinedrect( Vector2D x, Vector2D y ) {
			foi::getvfunc< void( __thiscall * )( void *, int, int, int, int ) >( this, 18 )( this, x.x, x.y, y.x, y.y );
		}

		void line( Vector2D x, Vector2D y ) { // don't mind me doing this, it doesn't matter, it's just preference. Using Vectors instead of 2 x's and 2 y's
			foi::getvfunc< void( __thiscall * )( void *, int, int, int, int ) >( this, 19 )( this, x.x, x.y, y.x, y.y );
		}

		void setfont( hfont font ) {
			foi::getvfunc< void( __thiscall * )( void *, hfont ) >( this, 23 )( this, font );
		}

		void setfontcolor( color col ) {
			return foi::getvfunc< void( __thiscall * )( void *, color ) >( this, 24 )( this, col );
		}

		void settextpos( int x, int y ) {
			foi::getvfunc< void( __thiscall * )( void *, int, int ) >( this, 26 )( this, x, y );
		}

		void printtext( const wchar_t* text, int textLen ) {
			typedef void( __thiscall* Fn )( void *, const wchar_t*, int, int );
			foi::getvfunc< Fn >( this, 28 )( this, text, textLen, 0 );
		}

		void settextureid( int textureID ) {
			typedef void( __thiscall* Fn )( void *, int );
			return foi::getvfunc< Fn >( this, 38 )( this, textureID );
		}

		void settexturergba( int textureID, unsigned char  const* colors, int w, int h ) {
			typedef void( __thiscall* Fn )( void *, int, unsigned char  const*, int, int );
			return foi::getvfunc< Fn >( this, 37 )( this, textureID, colors, w, h );
		}

		int createtexture( bool procedural ) {
			typedef int( __thiscall* Fn )( void *, bool );
			return foi::getvfunc< Fn >( this, 43 )( this, procedural );
		}

		void texturedpoly( int vtxCount, Vertex_t *vtx, bool bClipVertices = true ) {
			typedef void( __thiscall* Fn )( void *, int, Vertex_t*, bool );
			return foi::getvfunc< Fn >( this, 106 )( this, vtxCount, vtx, bClipVertices );
		}

		hfont CreateFont() {
			typedef unsigned int( __thiscall* Fn )( void * );
			return foi::getvfunc< Fn >( this, 71 )( this );
		}

		void gettextsize( unsigned long font, const wchar_t* text, int& wide, int& tall ) {
			typedef void( __thiscall* Fn )( void *, unsigned long, const wchar_t*, int&, int& );
			foi::getvfunc< Fn >( this, 79 )( this, font, text, wide, tall );
		}

		void outlinedcircle( int x, int y, int r, int seg ) {
			typedef void( __thiscall* Fn )( void *, int, int, int, int );
			return foi::getvfunc< Fn >( this, 103 )( this, x, y, r, seg );
		}

		void getcursorpos( int &x, int &y ) {
			typedef void( __thiscall* Fn )( void *, int&, int& );
			return foi::getvfunc< Fn >( this, 66 )( this, x, y );
		}
	};
}

// An IHandleEntity-derived class can go into an entity list and use ehandles.
class IHandleEntity {
public:
	virtual ~IHandleEntity() {}
	virtual void SetRefEHandle() = 0; // pad
	virtual void GetRefEHandle() const = 0; // pad
};

//-----------------------------------------------------------------------------
// The standard trace filter... NOTE: Most normal traces inherit from CTraceFilter!!!
//-----------------------------------------------------------------------------
enum TraceType_t {
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity( IHandleEntity *pEntity, int contentsMask ) = 0;
	virtual TraceType_t	GetTraceType() const = 0;
};


//-----------------------------------------------------------------------------
// Classes are expected to inherit these + implement the ShouldHitEntity method
//-----------------------------------------------------------------------------

// This is the one most normal traces will inherit from
class CTraceFilter : public ITraceFilter {
public:
	virtual TraceType_t	GetTraceType() const {
		return TRACE_EVERYTHING;
	}
};

class CTraceFilterEntitiesOnly : public ITraceFilter {
public:
	virtual TraceType_t	GetTraceType() const {
		return TRACE_ENTITIES_ONLY;
	}
};


//-----------------------------------------------------------------------------
// Classes need not inherit from these
//-----------------------------------------------------------------------------
class CTraceFilterWorldOnly : public ITraceFilter {
public:
	bool ShouldHitEntity( IHandleEntity *pServerEntity, int contentsMask ) {
		return false;
	}
	virtual TraceType_t	GetTraceType() const {
		return TRACE_WORLD_ONLY;
	}
};

class CTraceFilterSkipTwoEnts : public ITraceFilter {
public:
	CTraceFilterSkipTwoEnts( void* first, void* second ) : m_first( first ), m_second( second ) {}

	virtual bool ShouldHitEntity( IHandleEntity *entity, int mask ) {
		return ( entity != m_first && entity != m_second );
	}

	virtual TraceType_t	GetTraceType() const {
		return TRACE_EVERYTHING;
	}

	void *m_first, *m_second;
};

class CTraceFilterWorldAndPropsOnly : public ITraceFilter {
public:
	bool ShouldHitEntity( IHandleEntity *pServerEntity, int contentsMask ) {
		return false;
	}
	virtual TraceType_t	GetTraceType() const {
		return TRACE_EVERYTHING;
	}
};

class CTraceFilterHitAll : public CTraceFilter {
public:
	virtual bool ShouldHitEntity( IHandleEntity *pServerEntity, int contentsMask ) {
		return true;
	}
};

struct Ray_t {
	VectorAligned  m_Start;	// starting point, centered within the extents
	VectorAligned  m_Delta;	// direction + length of the ray
	VectorAligned  m_StartOffset;	// Add this to m_Start to get the actual ray start
	VectorAligned  m_Extents;	// Describes an axis aligned box extruded along a ray
	bool	m_IsRay;	// are the extents zero?
	bool	m_IsSwept;	// is delta != 0?

	void Init( Vector const& start, Vector const& end ) {
		Assert( &end );
		VectorSubtract( end, start, m_Delta );

		m_IsSwept = ( m_Delta.LengthSqr() != 0 );

		VectorClear( m_Extents );
		m_IsRay = true;

		// Offset m_Start to be in the center of the box...
		VectorClear( m_StartOffset );
		VectorCopy( start, m_Start );
	}

	void Init( Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs ) {
		Assert( &end );
		VectorSubtract( end, start, m_Delta );

		m_IsSwept = ( m_Delta.LengthSqr() != 0 );

		VectorSubtract( maxs, mins, m_Extents );
		m_Extents *= 0.5f;
		m_IsRay = ( m_Extents.LengthSqr() < 1e-6 );

		// Offset m_Start to be in the center of the box...
		VectorAdd( mins, maxs, m_StartOffset );
		m_StartOffset *= 0.5f;
		VectorAdd( start, m_StartOffset, m_Start );
		m_StartOffset *= -1.0f;
	}

	// compute inverse delta
	Vector InvDelta() const {
		Vector vecInvDelta;
		for( int iAxis = 0; iAxis < 3; ++iAxis ) {
			if( m_Delta[ iAxis ] != 0.0f ) {
				vecInvDelta[ iAxis ] = 1.0f / m_Delta[ iAxis ];
			} else {
				vecInvDelta[ iAxis ] = FLT_MAX;
			}
		}
		return vecInvDelta;
	}

private:
};

//-----------------------------------------------------------------------------
// Enumeration interface for EnumerateLinkEntities
//-----------------------------------------------------------------------------
class IEntityEnumerator
{
public:
	// This gets called with each handle
	virtual bool EnumEntity( IHandleEntity *pHandleEntity ) = 0;
};

struct cplane_t {
	Vector			normal;
	float			dist;
	unsigned __int8	type;			// for fast side tests
	unsigned __int8	signbits;		// signx + (signy<<1) + (signz<<1)
	char			pad[ 2 ];
};

struct csurface_t {
	const char	*name;
	short		surfaceProps;
	unsigned short	flags;		// BUGBUG: These are declared per surface, not per material, but this database is per-material now
};

class CBaseTrace {
public:

	// Displacement flags tests.
	bool IsDispSurface( void ) { return ( ( dispFlags & DISPSURF_FLAG_SURFACE ) != 0 ); }
	bool IsDispSurfaceWalkable( void ) { return ( ( dispFlags & DISPSURF_FLAG_WALKABLE ) != 0 ); }
	bool IsDispSurfaceBuildable( void ) { return ( ( dispFlags & DISPSURF_FLAG_BUILDABLE ) != 0 ); }
	bool IsDispSurfaceProp1( void ) { return ( ( dispFlags & DISPSURF_FLAG_SURFPROP1 ) != 0 ); }
	bool IsDispSurfaceProp2( void ) { return ( ( dispFlags & DISPSURF_FLAG_SURFPROP2 ) != 0 ); }

public:
	// these members are aligned!!
	Vector			startpos;				// start position
	Vector			endpos;					// final position
	cplane_t		plane;					// surface normal at impact

	float			fraction;				// time completed, 1.0 = didn't hit anything

	int				contents;				// contents on other side of surface hit
	unsigned short	dispFlags;				// displacement flags for marking surfaces with data

	bool			allsolid;				// if true, plane is not valid
	bool			startsolid;				// if true, the initial point was in a solid area

	CBaseTrace() {}

private:
	// No copy constructors allowed
	CBaseTrace( const CBaseTrace& vOther );
};

//-----------------------------------------------------------------------------
// Purpose: A trace is returned when a box is swept through the world
// NOTE: eventually more of this class should be moved up into the base class!!
//-----------------------------------------------------------------------------
class CGameTrace : public CBaseTrace {
public:

	// Returns true if hEnt points at the world entity.
	// If this returns true, then you can't use GetHitBoxIndex().
	bool DidHitWorld() {
		return m_pEnt->get_idx() == 0;
	}

	// Returns true if we hit something and it wasn't the world.
	bool DidHitNonWorldEntity() {
		return m_pEnt != NULL && !DidHitWorld();
	}

	// Gets the entity's network index if the trace has hit an entity.
	// If not, returns -1.
	int GetEntityIndex() {
		if( m_pEnt )
			return m_pEnt->get_idx();
		else
			return -1;
	}

	// Returns true if there was any kind of impact at all
	bool DidHit() {
		return fraction < 1 || allsolid || startsolid;
	}

public:

	float		fractionleftsolid;		// time we left a solid, only valid if we started in solid
	csurface_t	surface;				// surface hit (impact surface)

	int			hitgroup;				// 0 == generic, non-zero is specific body part
	short		physicsbone;			// physics bone hit by trace in studio

	c_csplayer *m_pEnt;

	// NOTE: this member is overloaded.
	// If hEnt points at the world entity, then this is the static prop index.
	// Otherwise, this is the hitbox index.
	int			hitbox;					// box hit by trace in studio

	CGameTrace() {}

private:
	// No copy constructors allowed
	CGameTrace( const CGameTrace& vOther );
};

class ICollideable
{
public:
	// Gets at the entity handle associated with the collideable
	virtual IHandleEntity	*GetEntityHandle() = 0;

	// These methods return the bounds of an OBB measured in "collision" space
	// which can be retreived through the CollisionToWorldTransform or
	// GetCollisionOrigin/GetCollisionAngles methods
	virtual const Vector&	OBBMins() const = 0;
	virtual const Vector&	OBBMaxs() const = 0;

	// Returns the bounds of a world-space box used when the collideable is being traced
	// against as a trigger. It's only valid to call these methods if the solid flags
	// have the FSOLID_USE_TRIGGER_BOUNDS flag set.
	virtual void			WorldSpaceTriggerBounds( Vector *pVecWorldMins, Vector *pVecWorldMaxs ) const = 0;

	// custom collision test
	virtual bool			TestCollision( const Ray_t &ray, unsigned int fContentsMask, CGameTrace& tr ) = 0;

	// Perform hitbox test, returns true *if hitboxes were tested at all*!!
	virtual bool			TestHitboxes( const Ray_t &ray, unsigned int fContentsMask, CGameTrace& tr ) = 0;

	// Returns the BRUSH model index if this is a brush model. Otherwise, returns -1.
	virtual int				GetCollisionModelIndex() = 0;

	// Return the model, if it's a studio model.
	virtual const void*	GetCollisionModel() = 0;

	// Get angles and origin.
	virtual const Vector&	GetCollisionOrigin() const = 0;
	virtual const angle&	GetCollisionAngles() const = 0;
	virtual const matrix3x4&	CollisionToWorldTransform() const = 0;

	// Return a SOLID_ define.
	virtual int		GetSolid() const = 0;
	virtual int				GetSolidFlags() const = 0;

	// Gets at the containing class...
	virtual void*	GetIClientUnknown() = 0;

	// We can filter out collisions based on collision group
	virtual int				GetCollisionGroup() const = 0;

	// Returns a world-aligned box guaranteed to surround *everything* in the collision representation
	// Note that this will surround hitboxes, trigger bounds, physics.
	// It may or may not be a tight-fitting box and its volume may suddenly change
	virtual void			WorldSpaceSurroundingBounds( Vector *pVecMins, Vector *pVecMaxs ) = 0;

	virtual bool			ShouldTouchTrigger( int triggerSolidFlags ) const = 0;

	// returns NULL unless this collideable has specified FSOLID_ROOT_PARENT_ALIGNED
	virtual const matrix3x4	*GetRootParentToWorldTransform() const = 0;
};

class IEngineTrace
{
public:
	// Returns the contents mask + entity at a particular world-space position
	virtual int		GetPointContents( const Vector &vecAbsPosition, IHandleEntity** ppEntity = NULL ) = 0;

	// Returns the contents mask of the world only @ the world-space position (static props are ignored)
	virtual int		GetPointContents_WorldOnly( const Vector &vecAbsPosition, int contentsMask = MASK_ALL ) = 0;

	// Get the point contents, but only test the specific entity. This works
	// on static props and brush models.
	// If the entity isn't a static prop or a brush model, it returns CONTENTS_EMPTY and sets
	// bFailed to true if bFailed is non-null.
	virtual int		GetPointContents_Collideable( ICollideable *pCollide, const Vector &vecAbsPosition ) = 0;

	// Traces a ray against a particular entity
	virtual void	ClipRayToEntity( const Ray_t &ray, unsigned int fMask, IHandleEntity *pEnt, CGameTrace *pTrace ) = 0;

	// Traces a ray against a particular entity
	virtual void	ClipRayToCollideable( const Ray_t &ray, unsigned int fMask, ICollideable *pCollide, CGameTrace *pTrace ) = 0;

	// A version that simply accepts a ray (can work as a traceline or tracehull)
	virtual void	TraceRay( const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, CGameTrace *pTrace ) = 0;
};

// reversed this a long time ago
struct OverlayText_t {
	Vector			origin;				// 0x000
	bool			bUseOrigin; 		// 0x00C Align to 4 bytes to avoid padding, stupid valve..
	char			pad0xD[ 3 ];		// 0x00D
	int				lineOffset;			// 0x010
	float			flXPos;				// 0x014
	float			flYPos;				// 0x018
	char			text[ 512 ];		// 0x01C
	float			m_flEndTime;		// 0x21C
	int				m_nServerCount;		// 0x220
	int				m_nCreationTick;	// 0x224
	int				r;					// 0x228
	int				g;					// 0x22C
	int				b;					// 0x230
	int				a;					// 0x234
	OverlayText_t	*nextOverlayText;	// 0x238
};	// size==0x23C

class IVDebugOverlay {
public:
	virtual void AddEntityTextOverlay( int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char *format, ... ) = 0;
	virtual void AddBoxOverlay( const Vector& origin, const Vector& mins, const Vector& maxs, angle const& orientation, int r, int g, int b, int a, float duration ) = 0;
	virtual void AddTriangleOverlay( const Vector& p1, const Vector& p2, const Vector& p3, int r, int g, int b, int a, bool noDepthTest, float duration ) = 0;
	virtual void AddSphereOverlay( const Vector& vOrigin, float flRadius, int nTheta, int nPhi, int r, int g, int b, int a, float flDuration = 0 ) = 0;

	//virtual void AddBoxOverlayNew( const Vector& origin, const Vector& mins, const Vector& maxs, const angle& orientation, int r, int g, int b, int a ) = 0; // new according to dude719

	virtual void AddLineOverlay( const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration ) = 0;
	virtual void AddTextOverlay( const Vector& origin, float duration, const char *format, ... ) = 0;
	virtual void AddTextOverlay( const Vector& origin, int line_offset, float duration, const char *format, ... ) = 0;
	virtual void AddScreenTextOverlay( float flXPos, float flYPos, float flDuration, int r, int g, int b, int a, const char *text ) = 0;
	virtual void AddSweptBoxOverlay( const Vector& start, const Vector& end, const Vector& mins, const Vector& max, const angle & angles, int r, int g, int b, int a, float flDuration ) = 0;
	virtual void AddGridOverlay( const Vector& origin ) = 0;

	virtual void AddCoordFrameOverlay( const matrix3x4& frame, float flScale, int vColorTable[ 3 ][ 3 ] = NULL ) = 0; // new

	virtual int ScreenPosition( const Vector& point, Vector& screen ) = 0;
	virtual int ScreenPosition( float flXPos, float flYPos, Vector& screen ) = 0;

	virtual OverlayText_t *GetFirst( void ) = 0;
	virtual OverlayText_t *GetNext( OverlayText_t *current ) = 0;
	virtual void ClearDeadOverlays( void ) = 0;
	virtual void ClearAllOverlays() = 0;

	virtual void AddTextOverlayRGB( const Vector& origin, int line_offset, float duration, float r, float g, float b, float alpha, const char *format, ... ) = 0;
	virtual void AddTextOverlayRGB( const Vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char *format, ... ) = 0;

	virtual void AddLineOverlayAlpha( const Vector& origin, const Vector& dest, int r, int g, int b, int a, bool noDepthTest, float duration ) = 0;
	virtual void AddBoxOverlay2( const Vector& origin, const Vector& mins, const Vector& max, angle const& orientation, const color& faceColor, const color& edgeColor, float duration ) = 0;

	virtual void PurgeTextOverlays() = 0; // new

	virtual void NewOverlay( const Vector& origin1, const Vector& origin2, int a3, int r, int g, int b, int a, int unusedParam ) = 0; // new

private:
	inline void AddTextOverlay( const Vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char *format, ... ) {} /* catch improper use of bad interface. Needed because '0' duration can be resolved by compiler to NULL format string (i.e., compiles but calls wrong function) */
};

class c_usercmd {
public:
	//char	pad[ 4 ];			// either use this or the destructor ( as padding.. )
	virtual ~c_usercmd() {};	// 0x00
	int		command_number;		// 0x04 For matching server and client commands for debugging
	int		tick_count;			// 0x08 the tick the client created this command
	angle	viewangles;			// 0x0C Player instantaneous view angles.
	Vector	aimdirection;		// 0x18
	float	forwardmove;		// 0x24
	float	sidemove;			// 0x28
	float	upmove;				// 0x2C
	int		buttons;			// 0x30 Attack button states
	BYTE    impulse;			// 0x34
	int		weaponselect;		// 0x38 Current weapon id
	int		weaponsubtype;		// 0x3C
	int		random_seed;		// 0x40 For shared random functions
	short	mousedx;			// 0x44 mouse accum in x from createmove
	short	mousedy;			// 0x46 mouse accum in y from createmove
	bool	hasbeenpredicted;	// 0x48 Client only, tracks whether we've predicted this command at least once
	char	pad_0x4C[ 0x18 ];	// 0x4C Current sizeof( usercmd ) =  100  = 0x64
}; // Size=0x64

class IClientMode {
public:
	virtual			~IClientMode() {}

	// Called before the HUD is initialized.
	virtual void	InitViewport() = 0;

	// One time init when .dll is first loaded.
	virtual void	Init() = 0;

	// Called when vgui is shutting down.
	virtual void	VGui_Shutdown() = 0;

	// One time call when dll is shutting down
	virtual void	Shutdown() = 0;

	// Called when switching from one IClientMode to another.
	// This can re-layout the view and such.
	// Note that Enable and Disable are called when the DLL initializes and shuts down.
	virtual void	Enable() = 0;

	// Called when it's about to go into another client mode.
	virtual void	Disable() = 0;

	// Called when initializing or when the view changes.
	// This should move the viewport into the correct position.
	virtual void	Layout() = 0;

	// Gets at the viewport, if there is one...
	virtual vgui::ipanel *GetViewport() = 0;

	// Gets at the viewports vgui panel animation controller, if there is one...
	virtual void *GetViewportAnimationController() = 0;

	// called every time shared client dll/engine data gets changed,
	// and gives the cdll a chance to modify the data.
	virtual void	ProcessInput( bool bActive ) = 0;

	// The mode can choose to draw/not draw entities.
	virtual bool	ShouldDrawDetailObjects() = 0;
	virtual bool	ShouldDrawEntity( c_csplayer *pEnt ) = 0;
	virtual bool	ShouldDrawLocalPlayer( c_csplayer *pPlayer ) = 0;
	virtual bool	ShouldDrawParticles() = 0;

	// The mode can choose to not draw fog
	virtual bool	ShouldDrawFog( void ) = 0;

	virtual void	OverrideView( void *pSetup ) = 0;
	virtual int		KeyInput( int down, int keynum, const char *pszCurrentBinding ) = 0;
	virtual void	StartMessageMode( int iMessageModeType ) = 0;
	virtual vgui::ipanel *GetMessagePanel() = 0;
	virtual void	OverrideMouseInput( float *x, float *y ) = 0;
	virtual bool	CreateMove( float flInputSampleTime, c_usercmd *cmd ) = 0;

	virtual void	LevelInit( const char *newmap ) = 0;
	virtual void	LevelShutdown( void ) = 0;
};

namespace globals {
	extern vengineclient			*engine;
	extern vgui::isurface			*surface;
	extern vgui::ipanel				*panel;
	extern ibaseclient				*client;
	extern IClientMode				*clientmode;
	extern CEntityList				*entitylist;
	extern IVEngineServer			*engineserver;
	extern IVDebugOverlay			*debugoverlay;
	extern IGameEventManager2		*gameevents;
	extern IEngineTrace				*enginetrace;

	extern c_csplayer				*localplayer;

	extern std::vector<c_csplayer*>	playersinserver;
}

#endif // !SDK_HPP


/* source2 you know :p ya
C_DOTA_PlayerResource::GetTeam( int )                                                                                                                         
C_DOTA_PlayerResource::GetPlayerName( int )                                                                                                                   
C_DOTA_PlayerResource::GetConnectionState( int )                                                                                                              
C_DOTA_PlayerResource::GetSteamID( int )                                                                                                                      
C_DOTA_PlayerResource::IsBroadcaster( int )                                                                                                                   
C_DOTA_PlayerResource::AreCoBroadcasters( int, int )                                                                                                          
C_DOTA_PlayerResource::GetPlayerSelectedHeroHandle( int )                                                                                                     
C_DOTA_PlayerResource::GetBroadcasterChannel( int )                                                                                                           
C_DOTA_PlayerResource::GetBuybackCooldownTime( int )                                                                                                          
C_DOTA_PlayerResource::OnSelectionDirty( void )                                                                                                               
C_DOTA_PlayerResource::OnTeamChanged( void )                                                                                                                  
C_DOTA_PlayerResource::OnFakeClientChanged( void )                                                                                                            
C_DOTA_PlayerResource::OnPlayerSteamIDsChanged( void )                                                                                                        
C_DOTA_PlayerResource::OnPlayerNamesChanged( void )                                                                                                           
C_DOTA_PlayerResource::UpdatePlayerName( int, char const* )                                                                                                   
C_DOTA_PlayerResource::GetClientClass( void )                                                                                                                 
C_DOTA_PlayerResource::YouForgotToImplementOrDeclareClientClass( void )                                                                                       
C_DOTA_PlayerResource::C_DOTA_PlayerResource( void )                                                                                                          
C_DOTA_PlayerResource::LoadOnstageSeatData( void )                                                                                                            
C_DOTA_PlayerResource::~C_DOTA_PlayerResource()                                                                                                             
C_DOTA_PlayerResource::~C_DOTA_PlayerResource()                                                                                                             
`non-virtual thunk to'C_DOTA_PlayerResource::~C_DOTA_PlayerResource()                                                                                       
`non-virtual thunk to'C_DOTA_PlayerResource::~C_DOTA_PlayerResource()                                                                                       
C_DOTA_PlayerResource::~C_DOTA_PlayerResource()                                                                                                             
`non-virtual thunk to'C_DOTA_PlayerResource::~C_DOTA_PlayerResource()                                                                                       
`non-virtual thunk to'C_DOTA_PlayerResource::~C_DOTA_PlayerResource()                                                                                       
C_DOTA_PlayerResource::OnDataChanged( DataUpdateType_t )                                                                                                      
C_DOTA_PlayerResource::IsValidPlayerID( int )                                                                                                                 
C_DOTA_PlayerResource::Spawn( CEntityKeyValues const* )                                                                                                       
C_DOTA_PlayerResource::UpdatePlayer( IGameEvent * )                                                                                                           
C_DOTA_PlayerResource::ClientThink( void )                                                                                                                    
C_DOTA_PlayerResource::InitPlayerSeatAssignments( void )                                                                                                      
C_DOTA_PlayerResource::UpdateTreeState( void )                                                                                                                
C_DOTA_PlayerResource::GetWorldTreeState( int )                                                                                                               
C_DOTA_PlayerResource::GetHTMLSafePlayerName( int )                                                                                                           
C_DOTA_PlayerResource::GetFilteredPlayerName( int )                                                                                                           
C_DOTA_PlayerResource::GetPlayerSelectedHero( int )                                                                                                           
C_DOTA_PlayerResource::IsValidTeamPlayerID( int )                                                                                                             
C_DOTA_PlayerResource::GetPossibleHeroSelection( int )                                                                                                        
C_DOTA_PlayerResource::GetSuggestedHeroesForPlayer( int, CUtlVector<suggested_hero_t, CUtlMemory<suggested_hero_t, int>> *, bool )                            
C_DOTA_PlayerResource::SetPossibleHeroSelection( int, char const* )                                                                                           
C_DOTA_PlayerResource::HasRepicked( int )                                                                                                                     
C_DOTA_PlayerResource::HasRandomed( int )                                                                                                                     
C_DOTA_PlayerResource::GetPlayer( int )                                                                                                                       
C_DOTA_PlayerResource::GetKills( int )                                                                                                                        
C_DOTA_PlayerResource::GetAssists( int )                                                                                                                      
C_DOTA_PlayerResource::GetDeaths( int )                                                                                                                       
C_DOTA_PlayerResource::GetNearbyCreepDeaths( int )                                                                                                            
C_DOTA_PlayerResource::GetStreak( int )                                                                                                                       
C_DOTA_PlayerResource::GetGoldPerMin( int )                                                                                                                   
C_DOTA_PlayerResource::GetXPPerMin( int )                                                                                                                     
C_DOTA_PlayerResource::GetSteamAccountID( int )                                                                                                               
C_DOTA_PlayerResource::GetFantasyPoints( int )                                                                                                                
C_DOTA_PlayerResource::GetFantasyPointsInCategory( int, int )                                                                                                 
C_DOTA_PlayerResource::GetLevel( int )                                                                                                                        
C_DOTA_PlayerResource::GetRespawnSeconds( int )                                                                                                               
C_DOTA_PlayerResource::CanPlayerBuyback( int )                                                                                                                
C_DOTA_PlayerResource::GetExpectedDeathCost( int )                                                                                                            
C_DOTA_PlayerResource::IsBuybackDisabledByReaperScythe( int )                                                                                                 
C_DOTA_PlayerResource::GetPlayerReservedState( int )                                                                                                          
C_DOTA_PlayerResource::GetPlayerQualifiesForPAContractReward( int )                                                                                           
C_DOTA_PlayerResource::GetLastBuybackTime( int )                                                                                                              
C_DOTA_PlayerResource::GetTeamSlot( int )                                                                                                                     
C_DOTA_PlayerResource::HasPickedHero( int )                                                                                                                   
C_DOTA_PlayerResource::IsHeroSelected( char const* )                                                                                                          
C_DOTA_PlayerResource::WhoSelectedHero( char const* )                                                                                                         
C_DOTA_PlayerResource::GetSelectedHeroID( int )                                                                                                               
C_DOTA_PlayerResource::FireGameEvent( IGameEvent * )                                                                                                          
`non-virtual thunk to'C_DOTA_PlayerResource::FireGameEvent(IGameEvent *)                                                                                    
C_DOTA_PlayerResource::NumTeamPlayers( void )                                                                                                                 
C_DOTA_PlayerResource::NumPlayers( void )                                                                                                                     
C_DOTA_PlayerResource::IsFakeClient( int )                                                                                                                    
C_DOTA_PlayerResource::GetPlayerIDsForTeam( int, CUtlVector<int, CUtlMemory<int, int>> & )                                                                    
C_DOTA_PlayerResource::GetPlayerIDsForSides( CUtlVector<int, CUtlMemory<int, int>> &, CUtlVector<int, CUtlMemory<int, int>> & )                               
C_DOTA_PlayerResource::GetPlayerSlotOnTeam( int )                                                                                                             
C_DOTA_PlayerResource::GetPlayerIDBySteamID( ulong long )                                                                                                     
C_DOTA_PlayerResource::GetPlayerIDByAccountID( uint )                                                                                                         
C_DOTA_PlayerResource::GetMetaLevel( int )                                                                                                                    
C_DOTA_PlayerResource::GetMetaExperience( int )                                                                                                               
C_DOTA_PlayerResource::GetMetaExperienceAwarded( int )                                                                                                        
C_DOTA_PlayerResource::GetEventPointsForPlayerID( int )                                                                                                       
C_DOTA_PlayerResource::GetEventPremiumPoints( int )                                                                                                           
C_DOTA_PlayerResource::IsBattlePointBonusActive( int )                                                                                                        
C_DOTA_PlayerResource::GetBattlePointRate( int )                                                                                                              
C_DOTA_PlayerResource::GetBroadcasterChannelSlot( int )                                                                                                       
C_DOTA_PlayerResource::IsLocalPlayerListeningToBroadcaster( int )                                                                                             
C_DOTA_PlayerResource::IsLocalPlayerBroadcaster( void )                                                                                                       
C_DOTA_PlayerResource::GetBroadcasterChannelDescription( int )                                                                                                
C_DOTA_PlayerResource::GetBroadcasterChannelCountryCode( int )                                                                                                
C_DOTA_PlayerResource::GetBroadcasterChannelLanguageCode( int )                                                                                               
C_DOTA_PlayerResource::IsFullyVoiceMuted( int )                                                                                                               
C_DOTA_PlayerResource::OnCourierSpawned( C_DOTA_Unit_Courier * )                                                                                              
C_DOTA_PlayerResource::GetNumCouriersForTeam( int )                                                                                                           
C_DOTA_PlayerResource::GetNthCourierForTeam( int, int )                                                                                                       
C_DOTA_PlayerResource::GetNthPlayerIDOnTeam( int, int )                                                                                                       
C_DOTA_PlayerResource::GetTimedRewardDrop( int )                                                                                                              
C_DOTA_PlayerResource::GetTimedRewardDropOrigin( int )                                                                                                        
C_DOTA_PlayerResource::GetTimedEventDrop( int )                                                                                                               
C_DOTA_PlayerResource::GetTimedCrateDrop( int )                                                                                                               
C_DOTA_PlayerResource::GetCustomBuybackCost( int )                                                                                                            
C_DOTA_PlayerResource::SetSwapWillingness( int, bool )                                                                                                        
C_DOTA_PlayerResource::GetSwapWillingness( int )                                                                                                              
C_DOTA_PlayerResource::GetHeroInOnstageSeat( int )                                                                                                            
C_DOTA_PlayerResource::GetPlayerIDForOnstageSeat( int )                                                                                                       
C_DOTA_PlayerResource::GetOnstageSeatForPlayerID( int )                                                                                                       
C_DOTA_PlayerResource::GetOnstageTeamID( bool )                                                                                                               
C_DOTA_PlayerResource::GetNetWorthOfPlayer( int )                                                                                                             
C_DOTA_PlayerResource::RegisterClassSchema_N__MISSING_DECL_MEANS_MACRO__UNRESOLVED_EXT_MEANS_SCHEMA_GENERATED_CODE( ISchemaSystem *, char const*, char const* )
C_DOTA_PlayerResource::GetEntityClassInternal( void )                                                                                                         
C_DOTA_PlayerResource::Schema_DynamicBinding( void )                                                                                                          
CSchemaNonConstructibleClassBinding<C_DOTA_PlayerResource::CEntityInstanceEntityClass>::Register( ISchemaSystem *, char const*, char const* )                 
CSchemaNonConstructibleClassBinding<C_DOTA_PlayerResource::CEntityInstanceEntityClass>::DeduceDerivedType( void const* )                                      
CSchemaNonConstructibleClassBinding<C_DOTA_PlayerResource::CEntityInstanceEntityClass>::GetSize( void )                                                       
C_DOTA_PlayerResource::CEntityInstanceEntityClass::~CEntityInstanceEntityClass()                                                                            
C_DOTA_PlayerResource::CEntityInstanceEntityClass::~CEntityInstanceEntityClass()                                                                            
C_DOTA_PlayerResource::CEntityInstanceEntityClass::AllocateInstance( void )                                                                                   
C_DOTA_PlayerResource::CEntityInstanceEntityClass::ConstructInstance( void * )                                                                                
C_DOTA_PlayerResource::CEntityInstanceEntityClass::DestructInstance( CEntityInstance * )                                                                      
C_DOTA_PlayerResource::CEntityInstanceEntityClass::FreeInstance( void * )                                                                                     
C_DOTA_PlayerResource::CEntityInstanceEntityClass::GetInstanceSchemaBinding( void )                                                                           
C_DOTA_PlayerResource::CEntityInstanceEntityClass::Schema_DynamicBinding( void )                                                                              
C_DOTA_PlayerResource::GetPlayerColor( int )                                                                                                                  
C_DOTA_PlayerResource::GetTeamDataForPlayer( int )                                                                                                            
C_DOTA_PlayerResource::GetReliableGold( int )                                                                                                                 
C_DOTA_PlayerResource::GetUnreliableGold( int )                                                                                                               
C_DOTA_PlayerResource::GetGold( int )                                                                                                                         
C_DOTA_PlayerResource::GetTotalEarnedGold( int )                                                                                                              
C_DOTA_PlayerResource::GetTotalEarnedXP( int )                                                                                                                
C_DOTA_PlayerResource::GetSharedGold( int )                                                                                                                   
C_DOTA_PlayerResource::GetHeroKillGold( int )                                                                                                                 
C_DOTA_PlayerResource::GetCreepKillGold( int )                                                                                                                
C_DOTA_PlayerResource::GetIncomeGold( int )                                                                                                                   
C_DOTA_PlayerResource::GetDenies( int )                                                                                                                       
C_DOTA_PlayerResource::GetClaimedMisses( int )                                                                                                                
C_DOTA_PlayerResource::GetClaimedDenies( int )                                                                                                                
C_DOTA_PlayerResource::GetMisses( int )                                                                                                                       
C_DOTA_PlayerResource::GetLastHits( int )                                                                                                                     
C_DOTA_PlayerResource::GetLastHitStreak( int )                                                                                                                
C_DOTA_PlayerResource::GetLastHitMultikill( int )                                                                                                             
C_DOTA_PlayerResource::GetBuybackGoldLimitTime( int )                                                                                                         
C_DOTA_PlayerResource::GetBuybackCost( int )                                                                                                                  
C_DOTA_PlayerResource::GetCustomBuybackCooldown( int )                                                                                                        
C_DOTA_PlayerResource::GetCameraTarget( int )                                                                                                                 
C_DOTA_PlayerResource::GetOverrideSelectionEntity( int )*/                                                                            