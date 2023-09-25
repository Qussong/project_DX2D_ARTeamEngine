#include "vanComponent.h"

namespace van
{
    Component::Component(COMPONENTTYPE type)
        : mType(type)
        , mOwner(nullptr)
    {
        SetName(L"Componenet class");
    }

    Component::~Component()
    {
    }
}
