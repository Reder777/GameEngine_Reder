#include "repch.h"
#include "buffers.h"
#include "reder/renderer/rendererAPI.h"
#include "platform/openGL/openglBuffer.h"
#include <glad/glad.h>
namespace reder {
    /*
    ----------------------------vertexbuffer------------------------------
    */
    vertexBuffer* vertexBuffer::create(float* vertices, RE_BUFFER_INT size)
    {
        switch (rendererAPI::getLibrary()) {
            case renderGraphicsLibrary::None: 
                RE_CORE_ASSERT(false, "no render graphics library!");
                break;
            case renderGraphicsLibrary::Opengl:
                return new openglVertexBuffer(vertices,size);
        }
        RE_CORE_ASSERT(false, "unknown graphics library!");
        return nullptr;
    }



    /*
    ----------------------------indexbuffer-------------------------------
    */
    indexBuffer* indexBuffer::create(RE_BUFFER_INT* indices, RE_BUFFER_INT count)
    {
        switch (rendererAPI::getLibrary()) {
        case renderGraphicsLibrary::None:
            RE_CORE_ASSERT(false, "no render graphics library!");
            break;
        case renderGraphicsLibrary::Opengl:
            return new openglIndexBuffer(indices,count);
        }
        RE_CORE_ASSERT(false, "unknown graphics library!");
        return nullptr;
    }

    

}