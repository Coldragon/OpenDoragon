#include "Scene.h"

int main(int argc, char** argv)
{
	(void)argc, (void)argv;

	Scene scene("OpenGL BlackMagic", 512, 512);
	scene.mainLoop();

	return 0;
}