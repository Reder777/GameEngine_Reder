#include "repch.h"
#include "texture.h"
#include "reder/renderer/rendererAPI.h"
#include "platform/openGL/openglTexture.h"


namespace reder {
    ref<texture2D> texture2D::createTexture(const std::string& path)
    {
        switch (rendererAPI::getLibrary()) {
        case renderGraphicsLibrary::None:
            RE_CORE_ASSERT(false, "texture2D : no render graphics library!");
            break;
        case renderGraphicsLibrary::Opengl:
            return std::make_shared<openglTexture2D>(path);
        }
        RE_CORE_ASSERT(false, "texture2D : unknown graphics library!");
        return nullptr;
    }
}