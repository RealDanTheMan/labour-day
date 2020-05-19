#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "renderable.hpp"
#include "transform.hpp"
#include "material.hpp"

namespace Engine
{
    class Model
    {
        public:
        Model(Renderable& renderable, Material * const mat);
        Model(const Model& rhs);

        Renderable& GetRenderable();
        Transform& GetTransform();
        Material* const GetMaterial() const;

        private:
        Transform m_tr;
        Renderable& m_renderable;
        Material* m_mat;
    };
}

#endif