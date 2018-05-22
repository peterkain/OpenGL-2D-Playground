#pragma once

#include "types/StringTypes.h"
#include "types/IntTypes.h"

#include <map>

struct ShaderSource
{
    std::map<uintl8, std::string> sources;
};

namespace ShaderFile
{
    constexpr uintl8 VERTEX{0};
    constexpr uintl8 FRAGMENT{1};

    extern ShaderSource parse_shader(conststr& path);
}


