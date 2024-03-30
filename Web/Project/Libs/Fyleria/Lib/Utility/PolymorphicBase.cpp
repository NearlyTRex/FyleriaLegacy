// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Utility/PolymorphicBase.h"

namespace Gecko
{

PolymorphicBase::PolymorphicBase()
{
    // Type name
    SetTypeName(IndexedString("TypedBase"));
}

PolymorphicBase::PolymorphicBase(const IndexedString& sName)
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
    SET_JSON_DATA_IF_NOT_DEFAULT(TypeName, IndexedString(""));
}

void from_json(const Json& jsonData, PolymorphicBase& obj)
{
    // Type name
    obj.SetTypeName(GET_JSON_DATA_OR_DEFAULT(TypeName, IndexedString, IndexedString("")));
}

};
