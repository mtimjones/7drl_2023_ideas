// levels.c

static int level = 0;

int get_level( void )
{
    return level;
}

void inc_level( void )
{
    level++;
}

typedef struct
{
    unsigned int wrecks;
    unsigned int wreck_resources;
    unsigned int planets;
    unsigned int planet_resources;
    unsigned int gas_cloud_rays;
    unsigned int gas_cloud_ray_len;
    unsigned int gas_smoothing_param;
    unsigned int gas_smoothing_iters;


} levels_t;

const levels_t levels[] = {
    {  4, 5, 0, 0, 20, 80, 4, 10 }, // 0
};


unsigned int get_wreck_count( int level )
{
    return levels[ level ].wrecks;
}

unsigned int get_wreck_resources( int level )
{
    return levels[ level ].wreck_resources;
}

unsigned int get_planet_count( int level )
{
    return levels[ level ].planets;
}

unsigned int get_planet_resources( int level )
{
    return levels[ level ].planet_resources;
}

unsigned int get_gas_cloud_rays( int level )
{
    return levels[ level ].gas_cloud_rays;
}

unsigned int get_gas_cloud_ray_len( int level )
{
    return levels[ level ].gas_cloud_ray_len;
}

unsigned int get_gas_smoothing_param( int level )
{
    return levels[ level ].gas_smoothing_param;
}

unsigned int get_gas_smoothing_iters( int level )
{
    return levels[ level ].gas_smoothing_iters;
}

