#include "ECS/ECS.hpp"

void Entity::addGroup(Group m_Group)
{
    groupBitset[m_Group] = true;
    manager.AddToGroup(this, m_Group);
}