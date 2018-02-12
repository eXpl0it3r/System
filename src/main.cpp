#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include <sol.hpp>
#include <physfs.h>
#include <spdlog/spdlog.h>

#include "FileSystem/FileSystem.hpp"

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
    std::vector<std::string> files;
    
    const auto rc = PHYSFS_enumerateFiles("/");
    for (auto i = rc; *i != nullptr; i++)
        files.emplace_back(*i);

    return files;
}

int main()
{
    // Config
    const std::string log_directory = "logs/";

    // Init spdlog
    spdlog::set_async_mode(4096);
    auto logger = spdlog::daily_logger_mt("system", log_directory + "system.log");

    // Init FileSystem
    FileSystem fs;

    // Init Sol 2
    sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table);
	auto filesystem = lua.create_named_table("fs");
	filesystem.set_function("dir", &FileSystem::dir, &fs);
	filesystem.set_function("mkdir", &FileSystem::mkdir, &fs);
	filesystem.set_function("rmdir", &FileSystem::rmdir, &fs);

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
                lua.script("print(table.concat(fs.dir(), ' '))");
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
        }
    }
}
