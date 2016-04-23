// Blame @DaniBarca for this

/*Include*/
#include "Header.h"
#include "Engine.h"
#include "World.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

/* program entry */
int main(int argc, char *argv[])
{
	Engine::GetInstance()
		->InitGLFW()
		->NewWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Voxels",
			std::bind(&World::OnKeyPress,  World::GetInstance(), _1, _2, _3, _4),
			std::bind(&World::OnMousePress,World::GetInstance(), _1, _2, _3),
			std::bind(&World::OnMouseMove, World::GetInstance(), _1, _2)
		)
		->InitGLEW()
		->InitEngine()
		->Loop(
			std::bind(&World::Init,  World::GetInstance()),
			std::bind(&World::Update,World::GetInstance(), _1),
			std::bind(&World::Draw,  World::GetInstance())
		)
		->Terminate();
}
