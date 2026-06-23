#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Game/World.h>
#include <unordered_map>
#include <vector>



namespace dx3d
{
    class SphereObj;
    class Command
    {
    public:
        virtual ~Command() = default;
        virtual void execute() = 0;
        virtual void undo() = 0;


    };

    class SpawnSphereCommand : public Command
    {
    public:
        SpawnSphereCommand(World& world, std::unordered_map<uint64_t, SphereObj*>& registry, uint64_t targetId)
            : m_world(world), m_registry(registry), m_targetId(targetId) {
        }

        virtual void execute() override
        {
            auto* sphere = m_world.createGameObject<::SphereObj>();
            if (sphere)
            {
                m_registry[m_targetId] = sphere;
            }
        }

        virtual void undo() override
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

    private:
        World& m_world;
        std::unordered_map<uint64_t,SphereObj*>& m_registry;
        uint64_t m_targetId;
    };

    // 2. Command for Backspace (Manually destroying the single most recent sphere)
    class DestroyRecentSphereCommand : public Command
    {
    public:
        DestroyRecentSphereCommand(World& world, std::unordered_map<uint64_t, ::SphereObj*>& registry, uint64_t targetId)
            : m_world(world), m_registry(registry), m_targetId(targetId), m_associatedSphere(nullptr) {
        }

        virtual void execute() override
        {
            auto it = m_registry.find(m_targetId);
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

        virtual void undo() override
        {
            // Re-spawn the sphere if undone
            auto* sphere = m_world.createGameObject<::SphereObj>();
            if (sphere)
            {
                m_registry[m_targetId] = sphere;
                m_associatedSphere = sphere;
            }
        }

    private:
        World& m_world;
        std::unordered_map<uint64_t, ::SphereObj*>& m_registry;
        uint64_t m_targetId;
        ::SphereObj* m_associatedSphere;
    };

    // 3. Command for Delete (Wiping out every single spawned sphere)
    class DeleteAllSpheresCommand : public Command
    {
    public:
        DeleteAllSpheresCommand(World& world, std::unordered_map<uint64_t, ::SphereObj*>& registry)
            : m_world(world), m_registry(registry) {
        }

        virtual void execute() override
        {
            // Save current snapshot state for undoing
            m_snapshotState = m_registry;

            for (auto& [id, sphere] : m_registry)
            {
                if (sphere)
                {
                    m_world.destroyGameObject(*sphere);
                }
            }
            m_registry.clear();
        }

        virtual void undo() override
        {
            // Reconstruct the exact world map positions from before the wipe
            for (auto& [id, oldSphere] : m_snapshotState)
            {
                auto* sphere = m_world.createGameObject<::SphereObj>();
                if (sphere)
                {
                    m_registry[id] = sphere;
                }
            }
        }

    private:
        World& m_world;
        std::unordered_map<uint64_t, ::SphereObj*>& m_registry;
        std::unordered_map<uint64_t, ::SphereObj*> m_snapshotState;
    };
}



