#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "shaderprog.hpp"
#include "shaderparam.hpp"
#include "types.hpp"
#include "texture2d.hpp"
#include <map>
#include <vector>
#include "debugging.hpp"

namespace Engine
{
    class Material
    {
        public:
        Material(const ShaderProg &shader);
        Material(const Material &rhs) = delete;

        ShaderParamCollection* const ShaderParameters();
        const ShaderParamCollection* const ShaderParameters() const;

        private:
        std::unique_ptr<ShaderParamCollection> m_params;
    };
}

#endif