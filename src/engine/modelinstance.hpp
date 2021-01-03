#ifndef MODEL_INSTANCE_HPP_
#define MODEL_INSTANCE_HPP_

#include "model.hpp"

namespace Engine
{
    class ModelInstance
    {
        public:
        ModelInstance() = delete;
        ModelInstance(Model * model);
        ModelInstance(const ModelInstance &rhs) = default;

        Transform& GetTransform();
        const Transform& GetTransform() const;
        const Model* const GetModel() const;


        private:
        Transform m_tr;
        Model * m_model;
    };
}

#endif