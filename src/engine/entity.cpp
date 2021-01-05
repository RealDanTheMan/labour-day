#include "entity.hpp"
#include "components/transformcomponent.hpp"

using namespace Engine;

Entity::Entity():
    m_uuid(0),
    m_components(nullptr),
    m_parent(nullptr),
    OnParentTransformChangedDelegate(ChangedDelegate(std::bind(&Entity::OnParentTransformChanged, this, std::placeholders::_1)))
{
    m_components = std::make_unique<EntityComponentCollection>();
}

EntityComponentCollection& Entity::Components()
{
    assert (m_components != nullptr);
    return *m_components;
}

std::unique_ptr<Entity> Entity::Duplicate() const 
{
    // TODO : Should we duplicate whole hierarchy chain ?

    auto dup = std::make_unique<Entity>();
    dup->m_components = m_components->Duplicate();
    dup->m_parent = m_parent;

    return dup;
}

std::vector<std::unique_ptr<Entity>> Entity::DuplicateHierarchy() const
{
    std::vector<std::unique_ptr<Entity>> entities;
    entities.push_back(Duplicate());

    for(auto &child : m_children)
    {
        std::vector<std::unique_ptr<Entity>> dups = child->DuplicateHierarchy();
        for(auto & dupChild : dups)
        {
            dupChild->SetParent(entities[0].get());
            entities.push_back(std::move(dupChild));
        }
    }

    return entities;
}

void Entity::SetParent(Entity *parent)
{
    // Unhook old parent transform callbacks
    // Remove Child references
    if(m_parent != nullptr)
    {
        auto parentTrs = m_parent->Components().GetAll<Components::TransformComponent>();
        if(parentTrs.size() > 0)
        {
            for(auto& cTr : parentTrs)
            {
                cTr->GetTransform().ChangedEvent().RemoveHandler(&OnParentTransformChangedDelegate);
            }
        }

        m_parent->m_children.erase(std::remove(
            m_parent->m_children.begin(), 
            m_parent->m_children.end(), this), 
            m_parent->m_children.end());
    }

    // Push transform to local
    auto localTrs = Components().GetAll<Components::TransformComponent>();
    for(auto &tr : localTrs)
    {
        tr->SetLocalTranslation(tr->GetTransform().Translation());
        tr->SetLocalRotation(tr->GetTransform().Rotation());
        tr->SetLocalScale(tr->GetTransform().Scale());
        //tr->GetTransform().Reset();
    }

    // Hookup new parent transform callbacks
    auto parentTrs = parent->Components().GetAll<Components::TransformComponent>();
    if(parentTrs.size() > 0)
    {
        for(auto &cTr : parentTrs)
        {
            cTr->GetTransform().ChangedEvent().AddHandler(&OnParentTransformChangedDelegate);
        }
    }

    // Update parent handle & child references
    m_parent = parent;
    m_parent->m_children.push_back(this);
    OnParentTransformChanged(0);
}

Entity * Entity::GetParent()
{
    return m_parent;
}

bool Entity::IsRoot() const
{
    if(m_parent == nullptr)
    {
        return true;
    }

    return false;
}

void Entity::OnParentTransformChanged(int param)
{
    assert (GetParent() != nullptr);

    auto parentTr = GetParent()->Components().Get<Components::TransformComponent>();
    if(parentTr != nullptr)
    {
        // Transform all local transform by the parent transform matrix
        auto localTrs = Components().GetAll<Components::TransformComponent>();
        for(auto &tr : localTrs)
        {
            //Transform local(tr->GetTransformLocal());
            //local.TransformBy(parentTr->GetTransform());
            //tr->GetTransform().Set(local);

            Transform parent(parentTr->GetTransform());
            Transform child(tr->GetTransform());
            Transform childLocal(tr->GetTransformLocal());

            parent.TransformBy(childLocal);

            tr->GetTransform().Set(parent);
            //Transform delta(parentTr->GetTransform());
            //delta.TransformByInv(tr->GetTransform());
            //tr->GetTransform().TransformBy(delta);
            
        }
    }
}