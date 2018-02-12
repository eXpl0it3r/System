#pragma once

#include <string>
#include <vector>
#include <memory>

#include <spdlog/spdlog.h>

#include "IFileSystem.hpp"

class FileSystem : public IFileSystem
{
public:
    explicit FileSystem();
    ~FileSystem();

    FileSystem(const FileSystem&) = delete;
    FileSystem& operator=(const FileSystem&) = delete;
    FileSystem(FileSystem&&) = default;
    FileSystem& operator=(FileSystem&&) = default;

	std::vector<std::string> dir(const std::string& path = "/") const final;
    void mkdir(const std::string& dirname) const final;
    void rmdir(const std::string& dirname) const final;
    void remove(const std::string& filename) const final;
	bool exists(const std::string& filepath) const final;

private:
    std::shared_ptr<spdlog::logger> m_logger;
};
