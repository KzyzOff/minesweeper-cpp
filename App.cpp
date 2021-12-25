
#include "App.h"

App::App(const std::string &title, int x, int y, int width, int height)
: m_window(nullptr),
  m_renderer(nullptr),
  m_running(false)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Success initializing everything\n";

		m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, 0);
		if (m_window != nullptr)
		{
			std::cout << "Success creating an window\n";

			m_renderer = SDL_CreateRenderer(m_window, -1, 0);
			if (m_renderer != nullptr)
			{
				std::cout << "Success creating renderer\n";
				SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
			}
			else
			{
				std::cout << "Renderer init failure...\n";
				return;
			}
		}
		else
		{
			std::cout << "Window init failure...\n";
			return;
		}
	}
	else
	{
		std::cout << "Init everything failure...\n";
		return;
	}

	m_mc = new MinesweeperCore(5, 5, GameDifficulty::EASY);
	m_fm = new FontManager("../VCR_OSD_MONO.ttf");
	m_bv = new BoardView(*m_mc, *m_fm, width, height);

//	m_mc->reveal(0, 2);
	m_mc->debug_draw();
//	m_bv->debug_print();

	m_running = true;
}

App::~App()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void App::run()
{
	while (running())
	{
		handleEvents();
		update();
		render();
//		SDL_Delay(200);
	}
}

void App::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		{
			m_running = false;
		}
		m_bv->handleEvents(event);
	}
}

void App::update()
{
	m_bv->update();
}

void App::render()
{
	SDL_RenderClear(m_renderer);

	m_bv->draw(m_renderer);

	SDL_SetRenderDrawColor(m_renderer, Color::black.r, Color::black.g, Color::black.b, Color::black.a);
	SDL_RenderPresent(m_renderer);
}
