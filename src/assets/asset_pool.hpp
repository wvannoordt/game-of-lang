#pragma once

#include <map>
#include <filesystem>

namespace gola
{
    template <typename asset_t>
    struct asset_pool_t
    {
        std::map<std::string, asset_t> data;
        asset_pool_t(const std::filesystem::path& direc)
        {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(direc))
            {
                if (entry.is_regular_file())
                {
                    const auto        basepath  = entry.path();
                    const std::string basename  = basepath.filename();
                    const std::string extension = basepath.extension();
                    const std::string key = basename.substr(0, basename.length() - extension.length());
                    data[key].loadFromFile(basepath);
                }
            }
        }
        
        const asset_t& operator[] (const std::string& key) const
        {
            return data.at(key);
        }
    };
}