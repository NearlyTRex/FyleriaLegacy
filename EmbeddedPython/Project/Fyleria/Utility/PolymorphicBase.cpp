// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Utility/PolymorphicBase.h"

namespace Gecko
{

PolymorphicBase::PolymorphicBase()
{
    // Type name
    SetTypeName(String("TypedBase"));
}

PolymorphicBase::PolymorphicBase(const String& sName)
{
    // Type name
    SetTypeName(sName);
}

PolymorphicBase::PolymorphicBase(const Json& jsonData)
{
    from_json(jsonData, *this);
}

void to_json(Json& jsonData, const PolymorphicBase& obj)
{
    // Type name
    SET_JSON_DATA(TypeName);
}

void from_json(const Json& jsonData, PolymorphicBase& obj)
{
    // Type name
    SET_OBJ_DATA(TypeName, String);
}

};
