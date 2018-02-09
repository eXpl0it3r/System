#include "FileSystem.hpp"

#include <exception>

#include <physfs.h>

FileSystem::FileSystem()
{
    m_logger = spdlog::get("system");

    if (PHYSFS_isInit() == 0)
    {
        PHYSFS_init(nullptr);
        m_logger->info("FileSystem successfully initialized");
    }
    else
    {
        m_logger->error("FileSystem couldn't be initialized:" + std::string(PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())));
        throw std::exception(PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
    }

    PHYSFS_addToSearchPath("test.7z", 1);
}

FileSystem::~FileSystem()
{
    if (PHYSFS_isInit() != 0)
    {
        PHYSFS_deinit();
        m_logger->info("FileSystem successfully deinitialized");
    }
    else
    {
        m_logger->error("FileSystem couldn't be deinitialized: " + std::string(PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())));
    }
}

std::string FileSystem::currentdir()
{
    return std::string();
}

std::vector<std::string> FileSystem::dir(const std::string & path)
{
    return std::vector<std::string>();
}

void FileSystem::mkdir(const std::string & dirname)
{
}

void FileSystem::rmdir(const std::string& dirname)
{
}

void FileSystem::touch(const std::string& filepath, const std::string& atime, const std::string& mtime)
{
}

void FileSystem::remove(const std::string& filename)
{
}

void FileSystem::rename(const std::string& oldname, const std::string& newname)
{
}
