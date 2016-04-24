OpenGL Engine by @DaniBarca

# VisualStudio 2015 config:

> C/C++>General>Additional Include Directories: 
	$(ProjectDir)lib\assimp-3.2\include;$(ProjectDir)lib\glfw-3.1.2\include;$(ProjectDir)lib\glm-0.9.7.9.3\glm;$(ProjectDir)lib\glew-1.9.0\include;%(AdditionalIncludeDirectories)

> Linker>General>Additional Library Directories
	$(ProjectDir)lib\assimp-3.2\lib;$(ProjectDir)lib\glfw-3.1.2\lib-vc2015;$(ProjectDir)lib\glew-1.9.0\lib;%(AdditionalLibraryDirectories)

> Linker>General>Input
	glew32.lib;opengl32.lib;glfw3.lib;assimp-vc130-mt.lib;

> Build Events>Post-Build Event>Command-line
	copy "$(ProjectDir)lib\assimp-3.2\lib\assimp-vc130-mt.dll" "$(TargetDir)assimp-vc130-mt.dll"; 
	copy "$(ProjectDir)lib\glew-1.9.0\bin\glew32.dll" "$(TargetDir)glew32.dll";
	xcopy "$(ProjectDir)models" "$(TargetDir)models" /e /i /Y

!! To be built for x64 !!