#pragma once

#include <string>
#include <vector>

class System
{
public:
    void run();

private:
    static std::vector<std::string> split(const std::string& input, const std::string& delimiter);
};
