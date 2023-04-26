#include <cstdint>

const uint8_t father = 0;

#define north 90
#define south 270
#define east 180
#define west 0

//uint8_t
struct node {
    uint8_t idfather;
    uint8_t nbrmvt;
    uint8_t orientation;
}

struct node map[42] = {
    {3, 2,east}, // 1
    {3, 1,east}, // 2
    {9, 1,south}, // 3
    {16, 2,south}, // 4
    {4, 1,west}, // 5
    {12, 1,south}, // 6
    {19, 2,south}, // 7
    {7, 1,west}, // 8
    {7, 2,west}, // 9
    {16, 1,south}, // 10
    {17, 1,south}, // 11
    {11, 1,west}, // 12
    {19, 1,south}, // 13
    {13, 1,west}, // 14
    {13, 2, west }, // 15
    {15, 1, west}, // 16
    {18, 1, east}, // 17
    {24, 1, south}, // 18
    {0, 0, 0}, // 19
    {32, 2, south}, // 20
    {15, 1, north}, // 21
    {16, 1, north}, // 22
    {17, 1, north}, // 23
    {0, 0, 0}, // 24
    {19, 1, north}, // 25
    {32, 1, south}, // 26
    {33, 1 ,south}, // 27
    {16, 2, north}, // 28
    {17, 2, north}, // 29
    {36, 1, south}, // 30
    {32, 1, east}, // 31
    {33, 1, east}, // 32
    {34, 1, east}, // 33
    {16, 3, north}, // 34
    {17, 3, north}, // 35
    {35, 1, west}, // 36
    {31, 1, north}, // 37
    {37, 1, west}, // 38
    {42, 3, east}, // 39
    {42, 2, east}, // 40
    {42, 1, east}, // 41
    {36, 1, north}, // 42
};

void init_map(uint8_t id){
    father = id;
}

uint8_t get_father(){
    uint8_t old_father = father;
    father = map[old_father].idfather;
    return (max[old_father].nbrmvt, max[old_father].orientation);
}
