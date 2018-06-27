#pragma once

#include <string>
#include <vector>
#include <memory>

#include <spdlog/spdlog.h>

#include <FileSystem/IFileSystem.hpp>

class FileSystem : public IFileSystem
{
public:
    explicit FileSystem();
    ~FileSystem();

    FileSystem(const FileSystem&) = delete;
    FileSystem& operator=(const FileSystem&) = delete;
    FileSystem(FileSystem&&) = default;
    FileSystem& operator=(FileSystem&&) = default;

	std::vector<std::string> dir(const std::string& path) const override final;
    void mkdir(const std::string& dirname) const override final;
    void rmdir(const std::string& dirname) const override final;
    void remove(const std::string& filename) const override final;
	bool exists(const std::string& path) const override final;
    void mount(const std::string& dirname, const std::string& mount_point) const override final;

private:
    std::shared_ptr<spdlog::logger> m_logger;
};
