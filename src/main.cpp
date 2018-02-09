#include <iostream>
#include <string>
#include <vector>

#include <sol.hpp>

std::vector<std::string> split(const std::string& input, const std::string& delimiter)
{
    std::vector<std::string> output;
    std::size_t offset = 0;
    
    while(const auto position = input.find_first_of(delimiter, offset))
    {
        if (position == std::string::npos)
        {
            auto insert = input.substr(offset, input.size() - offset);

            if (!insert.empty())
                output.push_back(insert);

            break;
        }

        auto insert = input.substr(offset, position - offset);
        if (!insert.empty())
            output.push_back(insert);

        offset = position + delimiter.size();
    }

    return output;
}

sol::as_table_t<std::vector<std::string>> fs_list()
{
   return std::vector<std::string>{
        "haha.txt",
        "no idea.md",
        "clickme.exe"
    };
}

int main()
{
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table);
    lua.set_function("fs_list", fs_list);

    std::cout << "Welcome to the System!\n";

    std::string input;
    auto exit = false;
    while(!exit)
    {
        // Input
        std::cout << "system > ";
        std::getline(std::cin, input);
        auto inputs = split(input, " ");

        std::cout << "You wish is my command!\n";
        std::cerr << "DEBUG: \n";

        for (auto& in : inputs)
            std::cerr << in << "\n";

        // Processing
        if (!inputs.empty())
        {
            if (inputs[0] == "exit")
                exit = true;
            else if (inputs[0] == "ls")
                lua.script("print(table.concat(fs_list(), ' '))");
        }
    }
}
