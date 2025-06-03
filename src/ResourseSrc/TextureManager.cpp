#include "ResourseInc/TextureManager.h"
//TextureManager.cpp
TextureManager::TextureManager() {
    for (const auto& [id, path] : TextureFileMap)
        load(id, path);
}

TextureManager& TextureManager::instance() {
    static TextureManager inst;
    return inst;
}