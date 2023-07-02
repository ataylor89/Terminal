#include "StringUtils.h"

std::vector<std::string> StringUtils::split(const std::string& str, char delim)
{
    std::vector<std::string> strs;
    size_t start;
    size_t end = 0;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        strs.push_back(str.substr(start, end - start));
    }
    return strs;
}