#include "glad/glad.h"
#include "Scene.h"
#include "Shader.h"

#define GL_VERSION_MAJOR 3
#define GL_VERSION_MINOR 1

Scene::Scene(std::string titleWindow, int widthWindow, int heightWindow) :
	m_titleWindow(titleWindow),
	m_widthWindow(widthWindow),
	m_heightWindow(heightWindow)
{
#if _WIN32
	std::cout << std::endl;
#endif

	initSDL2();
	initWindow();
	initGL();
}

Scene::~Scene()
{
	SDL_GL_DeleteContext(m_glcontext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Scene::initSDL2()
{
	// Init SDL
	if (SDL_Init(0) < 0)
	{
		std::cout << "Error Init SDL2 : " << SDL_GetError() << std::endl;
		exit(-3);
	}
	

	if (SDL_VideoInit(nullptr) < 0)
	{
		std::cout << "Error Init Video SDL2 : " << SDL_GetError() << std::endl;
		exit(-5);
	}

	m_basepath = SDL_GetBasePath();
	m_datapath = SDL_GetPrefPath("Coldragon", m_titleWindow.c_str());

	
}

void Scene::initWindow()
{
	// Création de la fenêtre
	m_window = SDL_CreateWindow(m_titleWindow.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_widthWindow, m_heightWindow, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!m_window)
	{
		std::cout << "Can't create window : " << SDL_GetError() << std::endl;
		exit(-4);
	}

	

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_VERSION_MAJOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_VERSION_MINOR);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetSwapInterval(1); //vsync

	// Création du contexte OpenGL

	m_glcontext = SDL_GL_CreateContext(m_window);

	if (!m_glcontext)
	{
		std::cout << SDL_GetError() << std::endl;
		exit(-2);
	}

	
}

void Scene::initGL()
{
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		std::cout << "Error loading Glad !" << std::endl;
		exit(-1);
	}

	// SDL
	std::cout << "Execution Path:  " << m_basepath << std::endl;
	std::cout << "Data Path:       " << m_datapath << std::endl << std::endl;

	SDL_version linked; SDL_GetVersion(&linked);
	std::cout << "SDL Compiled:    " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION << "." << SDL_PATCHLEVEL << std::endl;
	std::cout << "SDL Linked:      " << static_cast<int>(linked.major) << "." << static_cast<int>(linked.minor) << "." << static_cast<int>(linked.patch) << std::endl;

	std::cout << "Platform:        " << SDL_GetPlatform() << std::endl;
	std::cout << "CPU:             " << SDL_GetCPUCount() << " CORE " << SDL_GetCPUCacheLineSize() << " MB L1" << std::endl;
	std::cout << "RAM:             " << SDL_GetSystemRAM() << " MB" << std::endl;
	// GL
	std::cout << "GPU:             " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version:  " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version:    " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Screen:          " << SDL_GetNumVideoDisplays() << std::endl;

	std::cout << std::endl;
}

bool Scene::eventReturn()
{
	while (SDL_PollEvent(&m_event))
	{
		if (m_event.window.event == SDL_WINDOWEVENT_CLOSE)
			return false;
	}

	return true;
}

void Scene::mainLoop()
{

	// Vertices

	float vertices[] = 
	{ 
		-1.0, 0.0,   0.0, 1.0,   1.0, 0.0,				// Triangle 1
		-1.0, 0.0,   0.0, -1.0,  1.0, 0.0				// Triangle 2
	};							

	// Variables
	float color[] =
	{ 
		1.0, 0.0, 0.0,		// Vertex 1
		0.0, 1.0, 0.0 ,		// Vertex 2
		0.0, 0.0, 1.0,		// Vertex 3

		1.0, 0.0, 0.0,		// Vertex 4 (Copie du 1)
		1.0, 1.0, 1.0,		// Vertex 5
		0.0, 0.0, 1.0		// Vertex 6
	};

	// Shaders
	Shader shaderCouleur("res/shaders/couleur2D.vert", "res/shaders/couleur2D.frag");
	shaderCouleur.charger();

	// Main Loop
	while (eventReturn())
	{
		// Screen clear
		glClear(GL_COLOR_BUFFER_BIT);

		// Shader use
		glUseProgram(shaderCouleur.getProgramID());

			// Fill and active the Vertex Array
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
			glEnableVertexAttribArray(0);

			// Fill and active the Vertex Array (Color)
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, color);
			glEnableVertexAttribArray(1);
		
			// Affichage du triangle
			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Vertex Array Disable
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);

		// Shader disable
		glUseProgram(0);

		// Actualisation de la fenêtre
		SDL_GL_SwapWindow(m_window);
	}

}

