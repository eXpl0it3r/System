#pragma once

#include <string>
#include <vector>

class IFileSystem
{
public:
    virtual ~IFileSystem() = default;

    virtual std::vector<std::string> dir(const std::string& path) const = 0;
    virtual void mkdir(const std::string& dirname) const = 0;
    virtual void rmdir(const std::string& dirname) const = 0;
    virtual void remove(const std::string& filename) const = 0;
    virtual bool exists(const std::string& filepath) const = 0;
    virtual void mount(const std::string& dirname, const std::string& mount_point) const = 0;
};
