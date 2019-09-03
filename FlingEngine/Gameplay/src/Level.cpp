#include "pch.h"
#include "Level.h"
#include "ResourceManager.h"

namespace Fling
{
    Level::Level(const std::string& t_LevelFile)
    {
		m_LevelFileName = t_LevelFile;

        // Load in a file resource based on this file
        LoadLevel();

        // Parse the file appropriately!
        PostLoad();
    }

    void Level::LoadLevel()
    {
		std::vector<char> LevelData = ResourceManager::ReadFile(m_LevelFileName);
		// #TODO: Parse this data here from JSON!
    }

    void Level::PostLoad()
    {

    }

    Level::~Level()
    {
        // Clean up any actors in this level
        Unload();
    }

    void Level::Update(float t_DeltaTime)
    {   
        // Update the BSP of actors
        // m_Model.Update(t_DeltaTime);
        // Tick an active actors
        // for(Actor* : m_ActiveActors) { ... }
    }

    void Level::Unload()
    {

    }
}   // namespace Fling