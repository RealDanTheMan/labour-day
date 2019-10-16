#ifndef RUNTIME_SHADERS_H_
#define RUNTIME_SHADERS_H_

#include "shaderprog.hpp"
#include <memory>

namespace Engine
{
    class RuntimeShaders
    {
        public:
        void Init();
        void Free();
        const bool Ready() const ;

        const ShaderProg* FlatWhite() const;

        private:
        std::unique_ptr<ShaderProg> m_flatWhite;
    };

    const std::string FLAT_WHITE_VERT_SRC = R"(
        #version 330

        layout(location = 0) in vec3 SV_VERTEX;

        void main(void)
        {
            gl_Position = vec4(SV_VERTEX.x, SV_VERTEX.y, SV_VERTEX.z, 1.0);
        }
    )";

    const std::string FLAT_WHITE_PIX_SRC = R"(
        #version 330

        out vec4 SV_OUT_COLOR;
        void main()
        {
            SV_OUT_COLOR = vec4(1, 1, 1, 1);
        }
    )";
}

#endif