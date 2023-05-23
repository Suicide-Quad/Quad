#include <cstdint>
#include "map.h"

const uint8_t father = 0;

//uint8_t
struct node {
    uint8_t idfather;
    uint8_t nbrmvt;
    uint8_t orientation;
}

struct intResult
{
    uint8_t nbrmvt;
    uint8_t orientation;
};


struct node map[42] = {
    {3, 2, EAST}, // 1
    {3, 1, EAST}, // 2
    {9, 1, SOUTH}, // 3
    {16, 2, SOUTH}, // 4
    {4, 1, WEST}, // 5
    {12, 1,SOUTH}, // 6
    {19, 2, SOUTH}, // 7
    {7, 1, WEST}, // 8
    {7, 2, WEST}, // 9
    {16, 1, SOUTH}, // 10
    {17, 1, SOUTH}, // 11
    {11, 1, WEST}, // 12
    {19, 1, SOUTH}, // 13
    {13, 1, WEST}, // 14
    {13, 2, WEST }, // 15
    {15, 1, WEST}, // 16
    {18, 1, EAST}, // 17
    {24, 1, SOUTH}, // 18
    {0, 0, WEST}, // 19
    {32, 2, SOUTH}, // 20
    {15, 1, NORTH}, // 21
    {16, 1, NORTH}, // 22
    {17, 1, NORTH}, // 23
    {0, 0, WEST}, // 24
    {19, 1, NORTH}, // 25
    {32, 1, SOUTH}, // 26
    {33, 1 ,SOUTH}, // 27
    {16, 2, NORTH}, // 28
    {17, 2, NORTH}, // 29
    {36, 1, SOUTH}, // 30
    {32, 1, EAST}, // 31
    {33, 1, EAST}, // 32
    {34, 1, EAST}, // 33
    {16, 3, NORTH}, // 34
    {17, 3, NORTH}, // 35
    {35, 1, WEST}, // 36
    {31, 1, NORTH}, // 37
    {37, 1, WEST}, // 38
    {42, 3, EAST}, // 39
    {42, 2, EAST}, // 40
    {42, 1, EAST}, // 41
    {36, 1, NORTH}, // 42
};

void init_map(uint8_t id){
    father = id;
}

struct intResult get_father(){
    uint8_t old_father = father;
    father = map[old_father].idfather;
    struct intResult result = {map[old_father].nbrmvt, map[old_father].orientation};
    return result;
}