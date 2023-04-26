#ifndef MAP_H
#define MAP_H

enum Direction
{
    NORTH=90,
    SOUTH=270,
    EAST=180,
    WEST=0
};

void init_map(int id);

int get_father(void);

#endif
