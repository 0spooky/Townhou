
#include "world.hpp"

world::world()
{

}

world::world(const world& genworld)
{
    basetile_data = genworld.basetile_data;
}
