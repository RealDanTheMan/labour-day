#ifndef SHADER_SEMANTICS_HPP_
#define SHADER_SEMANTICS_HPP_

#include "types.hpp"

namespace Engine
{
    const uint32_t MAX_USER_TEX_COUNT = 8;
    const uint32_t SHADOW_MAP0_IDX = MAX_USER_TEX_COUNT;

    extern const char* SV_VERTEX;
    extern const char* SV_NORMAL;
    extern const char* SV_TEXCOORD0;
    extern const char* SV_OUT_COLOR;
    extern const char* SV_PROJECTION;
    extern const char* SV_VIEW;
    extern const char* SV_MODEL;
    extern const char* SV_MAIN_LIGHT_DIR;
    extern const char* SV_MAIN_LIGHT_INTENSITY;
    extern const char* SV_SHADOW_PROJ0;
    extern const char* SV_SHADOW_MAP0;
}

#endif