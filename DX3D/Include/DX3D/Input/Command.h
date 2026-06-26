#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Game/World.h>
#include <DX3D/Math/Vec3.h>
#include <unordered_map>
#include <vector>



// unordered maps to put id and sphere together in order to track recently called spheres
// 
// 
// Forward declaration of SphereObj (since it is outside dx3d namespace)

class SphereObj;
class CubeObj;

namespace dx3d // Base Commadn
{
    class Command
    {
    public:
        virtual ~Command() = default;
        virtual void execute() = 0;
        virtual void undo() = 0;
    };



    /// ALL THE COMMANDS BELOW

    // SPAWN THE SPEre

    class SpawnSphereCommand : public Command
    {
    public:
        SpawnSphereCommand(dx3d::World& world, std::unordered_map<uint64_t, SphereObj*>& registry, uint64_t targetId);
        virtual void execute() override;
        virtual void undo() override;

    private:
        dx3d::World& m_world;
        std::unordered_map<uint64_t, ::SphereObj*>& m_registry;
        uint64_t m_targetId;
    };

    //DESTROY THE SPHERE recently spawneds may need to refactor theses stuff to delete undo or delete all gameobjects 

    class DestroyRecentSphereCommand : public Command
    {
    public:
        DestroyRecentSphereCommand(dx3d::World& world, std::unordered_map<uint64_t, SphereObj*>& registry, uint64_t targetId);
        virtual void execute() override;
        virtual void undo() override;

    private:
        dx3d::World& m_world;
        std::unordered_map<uint64_t, SphereObj*>& m_registry;
        uint64_t m_targetId;
        ::SphereObj* m_associatedSphere;
    };

    //DESTROY ALL SPHERES
    class DeleteAllSpheresCommand : public Command
    {
    public:
        DeleteAllSpheresCommand(dx3d::World& world, std::unordered_map<uint64_t, SphereObj*>& registry);
        virtual void execute() override;
        virtual void undo() override;

    private:
        // struct for id and position
        struct SavedSphereData {
            uint64_t id;
            float x, y, z;
        };

        dx3d::World& m_world;
        std::unordered_map<uint64_t, SphereObj*>& m_registry;
        std::vector<SavedSphereData> m_savedSpheres;
    };


    // SpawnCube

    class SpawnCube : public Command
    {
    public:
        SpawnCube(dx3d::World& world, std::unordered_map<uint64_t, CubeObj*>& registry, uint64_t targetId);
        virtual void execute() override;
        virtual void undo() override;


    private:
        dx3d::World& m_world;
        std::unordered_map<uint64_t, CubeObj*>& m_registry;
        uint64_t m_targetId;
    };





}