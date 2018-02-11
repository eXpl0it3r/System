#pragma once

#include <string>
#include <vector>
#include <memory>

#include <sol.hpp>
#include <spdlog/spdlog.h>

class FileSystem
{
public:
    explicit FileSystem();
    ~FileSystem();

    FileSystem(const FileSystem&) = default;
    FileSystem& operator=(const FileSystem&) = default;
    FileSystem(FileSystem&&) = default;
    FileSystem& operator=(FileSystem&&) = default;

	sol::as_table_t<std::vector<std::string>> dir(const std::string& path = "/") const;
    void mkdir(const std::string& dirname) const;
    void rmdir(const std::string& dirname) const;
    void remove(const std::string& filename) const;
	bool exists(const std::string& filepath) const;

private:
    std::shared_ptr<spdlog::logger> m_logger;
};
