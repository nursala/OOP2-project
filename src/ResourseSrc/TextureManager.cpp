#include "ResourseInc/TextureManager.h"

// Constructor: load all textures listed in the map
TextureManager::TextureManager() {
    for (const auto& [id, path] : TextureFileMap)
        load(id, path);
}

// Singleton access method
TextureManager& TextureManager::instance() {
    static TextureManager inst;
    return inst;
}
