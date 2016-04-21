// Blame @DaniBarca for this

/*Include*/
#include "Header.h"
#include "Engine.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

static void Init() {
}

static void Update(double dt) {
}

static void Draw() {
}

static void OnKeyPress(int key, int scancode, int action, int mods) {
}

static void OnMousePress(int button, int action, int mods) {
}

static void OnMouseMove(double x, double y) {
}

/* program entry */
int main(int argc, char *argv[])
{
	Engine::GetInstance()
		->InitGLFW()
		->NewWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Voxels", OnKeyPress, OnMousePress, OnMouseMove)
		->InitGLEW()
		->InitEngine()
		->Loop(Init, Update, Draw)
		->Terminate();
}
