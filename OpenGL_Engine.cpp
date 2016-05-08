// Blame @DaniBarca for this

/*
	# VisualStudio 2015 config:

	> C/C++>General>Additional Include Directories: 
		$(ProjectDir)lib\assimp-3.2\include;$(ProjectDir)lib\glfw-3.1.2\include;$(ProjectDir)lib\glm-0.9.7.9.3\glm;$(ProjectDir)lib\glew-1.9.0\include;%(AdditionalIncludeDirectories)

	> Linker>General>Additional Library Directories
		$(ProjectDir)lib\assimp-3.2\lib;$(ProjectDir)lib\glfw-3.1.2\lib-vc2015;$(ProjectDir)lib\glew-1.9.0\lib;%(AdditionalLibraryDirectories)

	> Linker>General>Input
		glew32.lib;opengl32.lib;glfw3.lib;assimp-vc130-mt.lib;

	> Build Events>Pre-Build Event>Command-line
		copy "$(ProjectDir)lib\assimp-3.2\lib\assimp-vc130-mt.dll" "$(TargetDir)assimp-vc130-mt.dll"; 
		copy "$(ProjectDir)lib\glew-1.9.0\bin\glew32.dll" "$(TargetDir)glew32.dll";
		xcopy /E /I /Y /D "$(ProjectDir)models" "$(TargetDir)models"
		xcopy /E /I /Y /D "$(ProjectDir)shaders" "$(TargetDir)shaders"

	!! To be built for x64 !!
*/

/*Include*/
#include "Header.h"
#include "Engine.h"
#include "World.h"

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
