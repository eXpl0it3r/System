#include "../../src/FileSystem/FileSystem.hpp"

#include <catch.hpp>
#include <spdlog/spdlog.h>

SCENARIO("FileSystem tests")
{
    GIVEN("FileSystem with a 7z archive")
    {
        auto console = spdlog::stdout_color_mt("system");
        FileSystem fs;
        fs.mount("filesystem", "/");

        WHEN("listing the directory content")
        {
            auto files = fs.dir();

            THEN("two files are returned")
            {
                REQUIRE(files.size() == 2);
                REQUIRE(files[0] == "test.lua");
                REQUIRE(files[1] == "test.txt");
            }
        }
    }
}
