#include "Main.h"
#include <StateManager.h>

#define USE_ENEMY_SPRITE_BATCH 1

APPLICATION_ENTRY( Main );

using namespace NHTV;

Main::Main()
{

}

Main::~Main()
{}

bool Main::onCreate( int a_argc, char* a_argv[] )
{
    setBackgroundColor( NHTV::SColour( 0x00, 0x00, 0x00, 0xFF ) );
    GetScreenSize( screenWidth, screenHeight );

	AddFont("../resources/fonts/invaders.fnt");

	StateManager::Launch();

    return true;
}

void Main::onUpdate( float a_deltaTime )
{
	StateManager::Update(a_deltaTime);
}

void Main::onDraw()
{
    clearScreen();

	StateManager::Draw();
}

void Main::onDestroy()
{
	StateManager::Delete();
}