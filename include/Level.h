#pragma once

#include "types/StringTypes.h"
#include "types/IntTypes.h"

#include <vector>

class Level
{
public:
    Level();
    Level(conststr& path);
    ~Level();

private:
    std::vector<uintl8> _data;
    uintl64 _line_length;
};

