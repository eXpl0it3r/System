#include "../../src/FileSystem/FileSystem.hpp"

#include <catch.hpp>

SCENARIO("FileSystem tests")
{
    GIVEN("FileSystem with a 7z archive")
    {
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

        WHEN("creating a new directory")
        {
            fs.mkdir("test");

            THEN("the directory is being listed")
            {
                auto files = fs.dir();

                REQUIRE(files.size() == 3);
                REQUIRE(files[0] == "test");
                REQUIRE(files[1] == "test.lua");
                REQUIRE(files[2] == "test.txt");
            }

            fs.rmdir("test");
        }
    }
}
