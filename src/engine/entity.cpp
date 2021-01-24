#include "entity.hpp"
#include "components/transformcomponent.hpp"

using namespace Engine;

Entity::Entity():
    m_uuid(0),
    m_components(nullptr),
    m_parent(nullptr),
    OnComponentAddedDelegate(ComponentAddedDelegate(std::bind(&Entity::OnComponentAdded, this, std::placeholders::_1))),
    OnParentTransformChangedDelegate(ChangedDelegate(std::bind(&Entity::OnParentTransformChanged, this, std::placeholders::_1))),
    OnLocalTransformChangedDelegate(ChangedDelegate(std::bind(&Entity::OnLocalTransformChanged, this, std::placeholders::_1)))
{
    m_components = std::make_unique<EntityComponentCollection>();
    m_components->ComponentAddedEvent().AddHandler(&OnComponentAddedDelegate);
}

EntityComponentCollection& Entity::Components()
{
    assert (m_components != nullptr);
    return *m_components;
}

std::unique_ptr<Entity> Entity::Duplicate() const 
{
    auto dup = std::make_unique<Entity>();
    dup->m_components = m_components->Duplicate();
    dup->m_parent = m_parent;
    dup->m_tags = Tags(m_tags);

    // Hookup transform event callbacks
    auto transforms = dup->Components().GetAll<Components::TransformComponent>();
    for(auto &tr : transforms)
    {
        tr->GetTransformLocal().ChangedEvent().AddHandler(&dup->OnLocalTransformChangedDelegate);
    }

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
            // Hookup transform event callbacks
            auto transforms = dupChild->Components().GetAll<Components::TransformComponent>();
            for(auto &tr : transforms)
            {
                tr->GetTransformLocal().ChangedEvent().AddHandler(&dupChild->OnLocalTransformChangedDelegate);
            }

            // Update hierarchy parents & children
            dupChild->SetParent(entities[0].get());
            entities.push_back(std::move(dupChild));
        }
    }

    return entities;
}

void Entity::SetParent(Entity *parent)
{
    if(parent == m_parent)
    {
        // Early exit if we not actually changing parents
        return;
    }

    // Unhook old parent transform callbacks
    // Remove Child references
    if(m_parent != nullptr)
    {
        auto parentTr = m_parent->GetTransform();
        if(parentTr != nullptr)
        {
            parentTr->GetTransform().ChangedEvent().RemoveHandler(&OnParentTransformChangedDelegate);
        }

        m_parent->m_children.erase(std::remove(
            m_parent->m_children.begin(), 
            m_parent->m_children.end(), this), 
            m_parent->m_children.end());
    }

    if(parent != nullptr)
    {
        // Push transform to local
        auto localTrs = Components().GetAll<Components::TransformComponent>();
        for(auto &tr : localTrs)
        {
            tr->SetLocalTranslation(tr->GetTransform().Translation());
            tr->SetLocalRotation(tr->GetTransform().Rotation());
            tr->SetLocalScale(tr->GetTransform().Scale());
            tr->GetTransform().Reset();
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
    }
    else
    {
        // No parent - this will be a root object
        // Apply local transforms to world so that global position remains unchanged
        auto localTrs = Components().GetAll<Components::TransformComponent>();
        for(auto &tr : localTrs)
        {
            if(m_parent != nullptr)
            {
                auto parentTr = m_parent->GetTransform();
                if(parentTr != nullptr)
                {
                    Transform global(parentTr->GetTransform());
                    global.TransformBy(tr->GetTransformLocal());
                    tr->GetTransform().Set(global);
                }
            }
        }
    }
    

    // Update parent handle & child references
    m_parent = parent;
    if(parent != nullptr)
    {
        m_parent->m_children.push_back(this);
        OnParentTransformChanged(0);
    }
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

Tags * Entity::GetTags()
{
    return &m_tags;
}

void Entity::OnComponentAdded(EntityComponent *com)
{
    auto *tr = dynamic_cast<Components::TransformComponent*>(com);
    if(tr != nullptr)
    {
        tr->GetTransformLocal().ChangedEvent().AddHandler(&OnLocalTransformChangedDelegate);
    }
}

void Entity::OnParentTransformChanged(int param)
{
    assert (GetParent() != nullptr);
    UpdateEntityTransforms();
}

void Entity::OnLocalTransformChanged(int param)
{
    if(m_parent != nullptr)
    {
        UpdateEntityTransforms();
    }
}

void Entity::UpdateEntityTransforms()
{
    auto parentTr = GetParent()->GetTransform();
    if(parentTr != nullptr)
    {
        // Transform all local transform by the parent transform matrix
        auto localTrs = Components().GetAll<Components::TransformComponent>();
        for(auto &tr : localTrs)
        {
            Transform parent(parentTr->GetTransform());
            Transform childLocal(tr->GetTransformLocal());

            parent.TransformBy(childLocal);
            tr->GetTransform().Set(parent);
        }
    }
}

Components::TransformComponent * Entity::GetTransform()
{
    return Components().GetFirst<Components::TransformComponent>();
}