#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "renderable.hpp"
#include "transform.hpp"

namespace Engine
{
    class Model
    {
        public:
        Model(Renderable& renderable);
        Model(const Model& rhs);

        Renderable& GetRenderable();
        Transform& GetTransform();

        private:
        Transform m_tr;
        Renderable& m_renderable;
    };
}

#endif