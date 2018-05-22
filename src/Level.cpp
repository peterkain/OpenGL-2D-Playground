#include "Level.h"

#include <fstream>
#include <iterator>
#include <iostream>


Level::Level()
{
}


Level::Level(conststr& path)
    :   _line_length    {0}
{
    std::ifstream file {path};
    file >> _line_length;
    std::istream_iterator<uintl8> start{file}, end;
    _data.insert(_data.end(), start, end);
    file.close();


}


Level::~Level()
{
}
