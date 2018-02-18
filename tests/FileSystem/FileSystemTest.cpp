#include "../../src/FileSystem/FileSystem.hpp"

#include <catch.hpp>

SCENARIO("FileSystem tests")
{
    GIVEN("FileSystem with two files")
    {
        FileSystem fs;
        fs.mount("filesystem", "/");

        WHEN("listing the directory content")
        {
            auto files = fs.dir("/");

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
                auto files = fs.dir("/");

                REQUIRE(files.size() == 3);
                REQUIRE(files[0] == "test");
                REQUIRE(files[1] == "test.lua");
                REQUIRE(files[2] == "test.txt");
            }

            fs.rmdir("test");
        }

		WHEN("deleting a directory")
        {
			fs.mkdir("test");
			fs.rmdir("test");

			THEN("the directory is deleted")
			{
				auto files = fs.dir("/");

				REQUIRE(files.size() == 2);
				REQUIRE(files[0] == "test.lua");
				REQUIRE(files[1] == "test.txt");
			}
        }

		WHEN("checking if file exists and the file exists")
        {
			const auto result = fs.exists("test.lua");

			THEN("the result is true")
			{
				REQUIRE(result == true);
			}
        }

		WHEN("checking if file exists and the file does not exist")
		{
			const auto result = fs.exists("fileiwantdoesnotexist");

			THEN("the result is false")
			{
				REQUIRE(result == false);
			}
		}

		WHEN("checking if directory exists and the directory exists")
		{
			fs.mkdir("test");
			const auto result = fs.exists("test.lua");

			THEN("the result is true")
			{
				REQUIRE(result == true);
			}

			fs.rmdir("test");
		}

		WHEN("checking if directory exists and the directory does not exist")
		{
			const auto result = fs.exists("directoryiwantdoesnotexist/");

			THEN("the result is false")
			{
				REQUIRE(result == false);
			}
		}
    }
}
