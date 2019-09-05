#include "pch.h"
#include "Level.h"
#include "ResourceManager.h"
#include "JsonFile.h"

namespace Fling
{
    Level::Level(const std::string& t_LevelFile)
        : m_LevelFileName(t_LevelFile)
    {
		// Load in a file resource based on this file
        LoadLevel();

        // Parse the file appropriately!
        PostLoad();
    }

    void Level::LoadLevel()
    {
        std::shared_ptr<JsonFile> LevelFileData = 
            ResourceManager::Get().LoadResource<JsonFile>(entt::hashed_string{ m_LevelFileName.c_str() });

		// #TODO: Parse this data here from JSON!
        if(LevelFileData)
        {
            json& LevelData = LevelFileData->GetJsonData();
            
            // Load the title
            std::string Title = LevelData["title"];
            F_LOG_TRACE("Level Title: {}", Title);

            json entityArray = LevelData [ "Entities" ];

            for(const json& EntityData : entityArray)
            {
                // Load it in with the entity manager!
                std::string EntityName = EntityData["name"];
                F_LOG_TRACE("Entity name: {}", EntityName);
            }
        }
    }

    void Level::PostLoad()
    {
        F_LOG_TRACE("Level '{}' Post Load", m_LevelFileName);
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
        F_LOG_TRACE("Unload Level '{}'", m_LevelFileName);
    }
}   // namespace Fling