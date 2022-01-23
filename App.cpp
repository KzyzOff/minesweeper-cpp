
#include "App.h"

App::App(const std::string &title, int x, int y)
: m_current(nullptr),
  m_window(nullptr),
  m_renderer(nullptr),
  m_running(false)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Success initializing everything\n";

        m_window = SDL_CreateWindow(title.c_str(), x, y, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
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

    IMG_Init(IMG_INIT_PNG);

    m_fm = std::make_shared<FontManager>("../assets/VCR_OSD_MONO.ttf");
    m_current = std::make_unique<MainMenu>(m_fm.get());

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
        m_current->update();
        render();
    }
}

void App::handleEvents()
{
    SDL_PumpEvents();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        {
            m_running = false;
            break;
        }
        m_current->handleEvents(event);
        if (event.user.data1 == (void*)GameDifficulty::EASY)
        {
            printf("Initializing EASY board.\n");
            m_current = initBoard(GameDifficulty::EASY);
            break;
        }
        if (event.user.data1 == (void*)GameDifficulty::MEDIUM)
        {
            printf("Initializing MEDIUM board.\n");
            m_current = initBoard(GameDifficulty::MEDIUM);
            break;
        }
        if (event.user.data1 == (void*)GameDifficulty::HARD)
        {
            printf("Initializing HARD board. Event user data = %d\n", event.user.data1);
            m_current = initBoard(GameDifficulty::HARD);
            break;
        }
        /* PAUSE EVENT HANDLING */
    }
}

void App::render()
{
    SDL_RenderClear(m_renderer);

    m_current->draw(m_renderer);

    SDL_SetRenderDrawColor(m_renderer, Color::black.r, Color::black.g, Color::black.b, Color::black.a);
    SDL_RenderPresent(m_renderer);
}

std::unique_ptr<Controller> App::initBoard(GameDifficulty diff)
{
    return std::make_unique<BoardController>(2, 2, diff, m_fm.get());
}