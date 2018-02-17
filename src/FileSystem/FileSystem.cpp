#include "FileSystem.hpp"

#include <exception>
#include <filesystem>

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
        m_logger->error("FileSystem couldn't be initialized: {0}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        throw std::exception(PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
    }
	
	if (PHYSFS_setWriteDir("filesystem") == 0)
	{
		m_logger->error("FileSystem couldn't set write dir: {0}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
	}
}

FileSystem::~FileSystem()
{
	if (PHYSFS_isInit() == 0)
	{
		m_logger->warn("FileSystem wasn't initialized and couldn't be deinitialized: {0}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
		return;
	}

    if (PHYSFS_deinit() == 0)
    {
		m_logger->error("FileSystem couldn't be deinitialized: {0}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
    }

	m_logger->info("FileSystem was successfully deinitialized");
}

std::vector<std::string> FileSystem::dir(const std::string& path) const
{
	std::vector<std::string> files;

	const auto result = PHYSFS_enumerateFiles(path.c_str());

	if (result == nullptr)
	{
		m_logger->warn("FileSystem tried to access a path that doesn't exist: '{0}' - {1}", path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
		return files;
	}

	for (auto i = result; *i != nullptr; i++)
		files.emplace_back(*i);

	return files;
}

void FileSystem::mkdir(const std::string & dirname) const
{
	const auto result = PHYSFS_mkdir(dirname.c_str());

	if(result == 0)
	{
		m_logger->warn("FileSystem failed to create the following directory: '{0}' - {1}", dirname, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
	}

	m_logger->info("FileSystem successfully created the new directory: '{0}'", dirname);
}

void FileSystem::rmdir(const std::string& dirname) const
{
	if (PHYSFS_isDirectory(dirname.c_str()) == 0)
	{
		m_logger->warn("FileSystem tried to directory delete the file: '{0}'", dirname);
		return;
	}

	if (PHYSFS_delete(dirname.c_str()) == 0)
	{
		m_logger->warn("FileSystem failed to removed the directory: '{0}'", dirname);
	}

	m_logger->info("FileSystem successfully deleted the directory: '{0}'", dirname);
}

void FileSystem::remove(const std::string& filename) const
{
	if (PHYSFS_isDirectory(filename.c_str()) != 0)
	{
		m_logger->warn("FileSystem tried to file delete the directory: '{0}'", filename);
		return;
	}

	if (PHYSFS_delete(filename.c_str()) == 0)
	{
		m_logger->warn("FileSystem failed to removed the file: '{0}'", filename);
	}

	m_logger->info("FileSystem successfully deleted the file: '{0}'", filename);
}

bool FileSystem::exists(const std::string& filepath) const
{
	if (PHYSFS_exists(filepath.c_str()) == 0)
	{
		m_logger->info("FileSystem file doesn't exist: '{0}'", filepath);
		return false;
	}

	m_logger->info("FileSystem file does exist: '{0}'", filepath);
	return true;
}

void FileSystem::mount(const std::string& dirname, const std::string& mount_point) const
{
    if (PHYSFS_mount(dirname.c_str(), mount_point.c_str(), 1) == 0)
    {
        m_logger->error("FileSystem failed to mount '{0}' at '{1}'", dirname, mount_point);
        return;
    }

    m_logger->info("FileSystem mounted '{0}' successfully at '{1}'", dirname, mount_point);
}
