#include "pch.h"
#include "Engine.h"

namespace Fling
{
	Engine::Engine()
	{
	}

    Engine::Engine(int argc, char* argv[])
        : Engine()
    {
        m_CmdLineArgCount = argc;
        m_CmdLineArgs = argv;
    }

	Engine::~Engine()
	{
	}

	UINT64 Engine::Run()
	{
		Startup();

		Tick();

		Shutdown();

		return 0;
	}

	void Engine::Startup()
	{
		Random::Init();

        ResourceManager::Get().Init();
		Logger::Get().Init();

        FlingConfig::Get().Init();
        // Load command line args and any ini files
        UINT32 ArgsLoaded = FlingConfig::Get().LoadCommandLineOpts(m_CmdLineArgCount, m_CmdLineArgs);
        bool ConfigLoaded = FlingConfig::Get().LoadConfigFile("Config/EngineConf.ini");

		Timing::Get().Init();

        Renderer::Get().CreateGameWindow(
            ConfigLoaded ? FlingConfig::Get().GetInt("Engine", "WindowWidth") : FLING_DEFAULT_WINDOW_WIDTH,
            ConfigLoaded ? FlingConfig::Get().GetInt("Engine", "WindowHeight") : FLING_DEFAULT_WINDOW_WIDTH
        );

		Renderer::Get().Init();
	}

	void Engine::Tick()
	{
        // Calculate a fallback delta time in case the engine ever gets out of sync
        const static float FallbackDeltaTime = 1.0f / 60.0f;
        const static float MaxDeltaTime = 1.0f;

        float deltaTime = FallbackDeltaTime;
        float totalTime = 0.0f;

		while( !glfwWindowShouldClose( Renderer::Get().Window() ) )
		{
            // Update events
			glfwPollEvents();

            // #TODO Provide a game play layer that we can use to put any application
            // specific update systems in (i.e. an actual scene graph model)

            // Renderer
            Renderer::Get().DrawFrame();
            
            // Update timing
            Timing::Get().Update();
            deltaTime = Timing::Get().GetDeltaTime();
			totalTime = Timing::Get().GetTimef();

            // If delta time is greater than 1 second, simulate it as 1/60 FPS 
            // because we can assume that it is like that because of debugging
            if (deltaTime >= MaxDeltaTime)
            {
                deltaTime = FallbackDeltaTime;
            }
		}

        // Pre-shutdown options here
        Renderer::Get().PrepShutdown();
	}

	void Engine::Shutdown()
	{
		// Cleanup any resources
        ResourceManager::Get().Shutdown();
		Logger::Get().Shutdown();
        FlingConfig::Get().Shutdown();
		Timing::Get().Shutdown();
		Renderer::Get().Shutdown();
	}
}