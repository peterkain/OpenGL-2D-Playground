#include "ShaderFile.h"
#include "ErrorCodes.h"

#include <fstream>
#include <iostream>


namespace ShaderFile
{
    ShaderSource parse_shader(conststr& path)
    {
        ShaderSource ret;
        std::string line = "";
        uintl8 curr = VERTEX;

        std::ifstream file {path};
        if(file.fail())
        {
            perror(std::string {path + ": "}.c_str());
            std::exit(FILE_ERROR);
        }

        while(std::getline(file, line))
        {
            if(line.find("#shadertype vertex") != std::string::npos) curr = VERTEX;
            else if(line.find("#shadertype fragment") != std::string::npos) curr = FRAGMENT;
            else ret.sources[curr] += (line + '\n');
        }

        return ret;
    }
}
