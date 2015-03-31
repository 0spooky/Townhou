#include "World.hpp"

World::World()
{

}

World::World(const World& _generated_world)
{
    m_basetile_data = _generated_world.m_basetile_data;
}
