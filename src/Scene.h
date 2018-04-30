#ifndef DEF_INCLUDE_SCENEOPENGL
#define DEF_INCLUDE_SCENEOPENGL

#if defined(_WIN32) && defined(_DEBUG)
	#include <vld.h>
#endif

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

// Classe

class Scene
{
public:

	Scene(std::string titleWindow, int widthWindow, int heightWindow);
	~Scene();

	void mainLoop();

private:

	void initSDL2();
	void initWindow();
	void initGL();
	void info() const;
	bool eventReturn();
	
	std::string m_titleWindow = nullptr;
	int m_widthWindow = 0;
	int m_heightWindow = 0;

	SDL_Window* m_window = nullptr;
	SDL_GLContext m_glcontext = nullptr;
	SDL_Event m_event = { 0 };

	std::string m_basepath;
	std::string m_datapath;
};

#endif