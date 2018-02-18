#include "System.hpp"

#include <iostream>

#include <sol.hpp>

#include "../FileSystem/FileSystem.hpp"

void System::run()
{
    // Init FileSystem
    FileSystem fs;
    fs.mount("filesystem", "/");

    // Init Sol 2
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table);
    auto filesystem = lua.create_named_table("fs");
    filesystem.set_function("dir", &FileSystem::dir, &fs);
    filesystem.set_function("mkdir", &FileSystem::mkdir, &fs);
    filesystem.set_function("rmdir", &FileSystem::rmdir, &fs);
    filesystem.set_function("exists", &FileSystem::exists, &fs);
    filesystem.set_function("remove", &FileSystem::remove, &fs);

    std::cout << "Welcome to the System!\n";

    std::string input;
    auto exit = false;
    while (!exit)
    {
        // Input
        std::cout << "system > ";
        std::getline(std::cin, input);
        auto inputs = split(input, " ");

        /*std::cerr << "DEBUG: \n";
        for (auto& in : inputs)
        std::cerr << in << "\n";*/

        // Processing
        if (!inputs.empty())
        {
            if (inputs[0] == "exit")
            {
                exit = true;
            }
            else if (inputs[0] == "ls" || inputs[0] == "dir")
            {
                lua.script("print(table.concat(fs.dir('/'), ' '))");
            }
            else if (inputs[0] == "mkdir")
            {
                if (input.size() > 1)
                    lua.script(std::string("fs.mkdir('") + inputs[1] + std::string("')"));
            }
            else if (inputs[0] == "rmdir")
            {
                if (input.size() > 1)
                    lua.script(std::string("fs.rmdir('") + inputs[1] + std::string("')"));
            }
			else if (inputs[0] == "exists")
			{
				if (input.size() > 1)
					lua.script(std::string("print(fs.exists('") + inputs[1] + std::string("'))"));
			}
			else if (inputs[0] == "remove" | inputs[0] == "rm")
			{
				if (input.size() > 1)
					lua.script(std::string("fs.remove('") + inputs[1] + std::string("')"));
			}
        }
    }
}

std::vector<std::string> System::split(const std::string& input, const std::string& delimiter)
{
    std::vector<std::string> output;
    std::size_t offset = 0;

    while (const auto position = input.find_first_of(delimiter, offset))
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
