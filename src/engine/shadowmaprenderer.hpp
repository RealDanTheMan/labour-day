#ifndef SHADOWMAP_RENDERER_HPP_
#define SHADOWMAP_RENDERER_HPP_

#include "shadowframebuffer.hpp"
#include "modelinstance.hpp"

namespace Engine
{
    struct ShadowmapSettings
    {
        uint32_t m_resx;
        uint32_t m_resy;
        float m_minDistance;
        float m_maxDistance;
    };

    class ShadowmapRenderer
    {
        public:
        ShadowmapRenderer() = default;
        ShadowmapRenderer(const ShadowmapRenderer &rhs) = delete;

        void Init(const ShadowmapSettings &settings);
        void RenderShadows(std::vector<const ModelInstance*> &instances, const Vec3 &lightDir);
        bool Ready() const;
        const ShadowmapSettings & GetSettings() const;
        const Mat4 & GetShadowProjMatrix() const;

        private:
        void DrawIntoShadowMap(const ModelInstance *instance, const Vec3 &lightDir);
        void CompileShader();
        void ComputeMatrices(const Vec3 &lightDir);

        bool m_ready;
        std::unique_ptr<ShadowFrameBuffer> m_fb;
        std::unique_ptr<ShaderProg> m_shader;
        Mat4 m_lightProj;
        Mat4 m_lightView;
        Mat4 m_shadowProj;
        Mat4 m_scaleBias;
        ShadowmapSettings m_settings;

        static const Vec3 UP_AXIS0;
        static const Vec3 UP_AXIS1;
        static const float DEF_DIST;
    };

    // Simple shadow pass vertex shader
    const std::string SHADOWPASS_VERT_SRC = R"(
        #version 330

        uniform mat4 SV_PROJECTION;
        uniform mat4 SV_VIEW;
        uniform mat4 SV_MODEL;

        mat4x4 MVP = SV_PROJECTION * SV_VIEW * SV_MODEL;

        layout(location = 0) in vec3 SV_VERTEX;

        out vec3 vnormal;

        void main(void)
        {
            gl_Position = MVP * vec4(SV_VERTEX.x, SV_VERTEX.y, SV_VERTEX.z, 1.0);
        }
    )";

    // Simple shadow pass pixel shader 
    // Technically we do not need this but we cannot compile and bind vertex shader alone
    const std::string SHADOWPASS_PIX_SRC = R"(
        #version 330

        in vec3 vnormal;

        out vec4 SV_OUT_COLOR;
        void main()
        {
            SV_OUT_COLOR = vec4(1.0);
        }
    )";
}

#endif