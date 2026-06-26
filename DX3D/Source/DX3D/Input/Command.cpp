#include <DX3D/Input/Command.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/GameObject.h>

/// Objects to spawn specific objects
#include "../../Game/Objects/CubeObj.h"

#include "../../Game/Objects/SphereObj.h"



namespace dx3d
{
   // spawm sphere unction
    SpawnSphereCommand::SpawnSphereCommand(World& world, std::unordered_map<uint64_t, SphereObj*>& registry, uint64_t targetId)
        : m_world(world), m_registry(registry), m_targetId(targetId)
    {
    }

    void SpawnSphereCommand::execute()
    {
        // spawn the sphere via world then add it to the registry including the ID
        auto* sphere = m_world.createGameObject<SphereObj>();
        if (sphere)
        {
            m_registry[m_targetId] = sphere;
        }
    }

    void SpawnSphereCommand::undo() // destroys the object and remove from registry
    {
        auto it = m_registry.find(m_targetId);
        if (it != m_registry.end())
        {
            if (it->second)
            {
                m_world.destroyGameObject(*(it->second));
            }
            m_registry.erase(it);
        }
    }

  
    DestroyRecentSphereCommand::DestroyRecentSphereCommand(World& world, std::unordered_map<uint64_t, SphereObj*>& registry, uint64_t targetId)
        : m_world(world), m_registry(registry), m_targetId(targetId), m_associatedSphere(nullptr)
    {
    }

    void DestroyRecentSphereCommand::execute()
    {
        auto it = m_registry.find(m_targetId); // deletes and puts it in registry
        if (it != m_registry.end())
        {
            m_associatedSphere = it->second;
            if (m_associatedSphere)
            {
                m_world.destroyGameObject(*m_associatedSphere);
            }
            m_registry.erase(it);
        }
    }

    void DestroyRecentSphereCommand::undo() //creates based on id
    {
        auto* sphere = m_world.createGameObject<SphereObj>();
        if (sphere)
        {
            m_registry[m_targetId] = sphere;
            m_associatedSphere = sphere;
        }
    }

   
    // delete function here 

    DeleteAllSpheresCommand::DeleteAllSpheresCommand(World& world, std::unordered_map<uint64_t,SphereObj*>& registry)
        : m_world(world), m_registry(registry)
    {
    }
    // gets rid of ALLL recently spawned objects
    void DeleteAllSpheresCommand::execute()
    {
        m_savedSpheres.clear();

        // 1. Snapshot raw float coordinates safely before destroying anything
        for (auto& [id, sphere] : m_registry)
        {
            if (sphere)
            {
                auto pos = sphere->getTransform().getPosition();
                m_savedSpheres.push_back({ id, pos.x, pos.y, pos.z });
                m_world.destroyGameObject(*sphere);
            }
        }

        // 2. Clear out the active map references
        m_registry.clear();
    }

    void DeleteAllSpheresCommand::undo()
    {
        // 3. Recreate completely clean instances and restore their positions exactly
        for (const auto& sphereData : m_savedSpheres)
        {
            auto* sphere = m_world.createGameObject<SphereObj>();
            if (sphere)
            {
                sphere->getTransform().setPosition({ sphereData.x, sphereData.y, sphereData.z });
                m_registry[sphereData.id] = sphere;
            }
        }
    }



    SpawnCube::SpawnCube(dx3d::World& world, std::unordered_map<uint64_t, CubeObj*>& registry, uint64_t targetId)
        : m_world(world), m_registry(registry), m_targetId(targetId)
    {
    }
    void SpawnCube::execute()
    {
        // spawn the sphere via world then add it to the registry including the ID
        auto* Cube = m_world.createGameObject<CubeObj>();
        if (Cube)
        {
            m_registry[m_targetId] = Cube;
        }
    }

    void SpawnCube::undo() // destroys the object and remove from registry
    {
        auto it = m_registry.find(m_targetId);
        if (it != m_registry.end())
        {
            if (it->second)
            {
                m_world.destroyGameObject(*(it->second));
            }
            m_registry.erase(it);
        }
    }
}