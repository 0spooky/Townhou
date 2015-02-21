
#include "world.hpp"

world::world()
{

}

world::world(const world& _genworld)
{
    m_basetile_data = _genworld.m_basetile_data;
}
