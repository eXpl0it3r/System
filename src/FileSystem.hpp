#pragma once

#include <string>
#include <vector>
#include <memory>

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

    std::string currentdir();
    std::vector<std::string> dir(const std::string& path);
    void mkdir(const std::string& dirname);
    void rmdir(const std::string& dirname);
    void touch(const std::string& filepath, const std::string& atime, const std::string& mtime);
    void remove(const std::string& filename);
    void rename(const std::string& oldname, const std::string& newname);

private:
    std::shared_ptr<spdlog::logger> m_logger;
};
