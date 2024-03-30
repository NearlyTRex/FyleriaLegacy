// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_MACROS_H_
#define _GECKO_MACROS_H_

//=====================================================================================

#define CALL_MEMBER_FN_PTR(object, ptrToMember)     ((object).*(ptrToMember))
#define CALL_SELF_MEMBER_FN_PTR(ptrToMember)        ((*this).*(ptrToMember))

//=====================================================================================

#define MAKE_CURRENT_CONFIG_SHORTCUT_STRING(name)                                   \
String Get##name() const                                                            \
{                                                                                   \
    FilesystemPath basePath = GetUserConfigFolder();                                \
    FilesystemPath funcPath = GetCurrentConfig().Get##name();                       \
    FilesystemPath fullPath = basePath / funcPath;                                  \
    return GetNativeFileLocation(fullPath);                                         \
}

//=====================================================================================

#define GET_JSON_DATA_OR_DEFAULT(name, value_type, value_default)                   \
(jsonData.find(#name) != jsonData.end()) ? jsonData[#name].get<value_type>() : value_default

#define GET_JSON_SHAREDPTR_DATA_OR_DEFAULT(name, type)                              \
(jsonData.find(#name) != jsonData.end()) ? STDMakeSharedPtr<type>(jsonData[#name].get<type>()) : STDSharedPtr<type>()

#define SET_JSON_DATA_IF_NOT_DEFAULT(name, value_default)                           \
{                                                                                   \
    if(obj.Get##name() != value_default)                                            \
    {                                                                               \
        jsonData[#name] = obj.Get##name();                                          \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        jsonData[#name] = value_default;                                            \
    }                                                                               \
}

#define SET_JSON_DATA_IF_NOT_DEFAULT_FROM_PTR(name, value_default)                  \
{                                                                                   \
    if(obj.Get##name() && (*obj.Get##name() != value_default))                      \
    {                                                                               \
        jsonData[#name] = *obj.Get##name();                                         \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        jsonData[#name] = value_default;                                            \
    }                                                                               \
}

#define SET_JSON_DATA_IF_NOT_EMPTY(name)                                            \
{                                                                                   \
    if(!obj.Get##name().empty())                                                    \
    {                                                                               \
        jsonData[#name] = obj.Get##name();                                          \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        jsonData[#name] = JsonArray();                                              \
    }                                                                               \
}

#define SET_JSON_DATA_FROM_PTR_ARRAY_IF_NOT_EMPTY(name)                             \
{                                                                                   \
    if(!obj.Get##name().empty())                                                    \
    {                                                                               \
        jsonData[#name] = JsonArray();                                              \
        for(auto& pObj : obj.Get##name())                                           \
        {                                                                           \
            if(pObj)                                                                \
            {                                                                       \
                jsonData[#name].push_back(*pObj);                                   \
            }                                                                       \
        }                                                                           \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        jsonData[#name] = JsonArray();                                              \
    }                                                                               \
}

//=====================================================================================

#define MAKE_TYPE_TYPEDEFS(type)                                                    \
typedef type* type##Ptr;                                                            \
typedef STDSharedPtr<type> type##SharedPtr;                                         \
typedef STDReferenceWrapper<type> type##Ref;                                        \
typedef STDVector<type> type##List;                                                 \
typedef STDVector<type##Ptr> type##PtrList;                                         \
typedef STDVector<type##Ref> type##RefList;                                         \
typedef STDVector<type##SharedPtr> type##SharedPtrList

//=====================================================================================

#define MAKE_JSON_BASIC_TYPE_CONVERTERS_DECL(type)                                  \
void to_json(Json& jsonData, const type& obj);                                      \
void from_json(const Json& jsonData, type& obj);

#define MAKE_JSON_BASIC_TYPE_CONVERTERS_IMPL(type)                                  \
void to_json(Json& jsonData, const type& obj)                                       \
{                                                                                   \
    jsonData = obj.ToJson();                                                        \
}                                                                                   \
void from_json(const Json& jsonData, type& obj)                                     \
{                                                                                   \
    obj.FromJson(jsonData);                                                         \
}

#define MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(name, type)                          \
String Convert##name##ToJsonString(const type& obj);                                \
String Convert##name##ListToJsonString(const STDVector<type>& vObjs);               \
type Get##name##FromJsonString(const String& jsonString);                           \
STDVector<type> Get##name##ListFromJsonString(const String& jsonString);

#define MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(name, type)                          \
String Convert##name##ToJsonString(const type& obj)                                 \
{                                                                                   \
    Json jsonData = obj;                                                            \
    return jsonData.dump();                                                         \
}                                                                                   \
String Convert##name##ListToJsonString(const STDVector<type>& vObjs)                \
{                                                                                   \
    Json jsonData = vObjs;                                                          \
    return jsonData.dump();                                                         \
}                                                                                   \
type Get##name##FromJsonString(const String& jsonString)                            \
{                                                                                   \
    Json jsonData = JsonParse(jsonString);                                          \
    return jsonData.get<type>();                                                    \
}                                                                                   \
STDVector<type> Get##name##ListFromJsonString(const String& jsonString)             \
{                                                                                   \
    Json jsonData = JsonParse(jsonString);                                          \
    return jsonData.get<STDVector<type>>();                                         \
}

//=====================================================================================

#define MAKE_ENUM_GETSTRINGLIST_DECL(type)                                          \
StringList Get##type##Names();

#define MAKE_ENUM_GETSTRINGLIST_IMPL(type)                                          \
StringList Get##type##Names()                                                       \
{                                                                                   \
    StringList vTypeNames;                                                          \
    for (const char* name : type::_names())                                         \
    {                                                                               \
        vTypeNames.push_back(name);                                                 \
    }                                                                               \
    return vTypeNames;                                                              \
}

#define MAKE_ENUM_CONVERTERS_DECL(type)                                             \
type StringTo##type(const IndexedString& sType);                                    \
Bool IsValid##type(const IndexedString& sType);

#define MAKE_ENUM_CONVERTERS_IMPL(type)                                             \
type StringTo##type(const IndexedString& sType)                                     \
{                                                                                   \
    ASSERT_ERROR(type::_is_valid(sType.c_str()),                                    \
        "Type '%s' was not a valid enum string for type", sType.c_str());           \
    return type::_from_string(sType.c_str());                                       \
}                                                                                   \
Bool IsValid##type(const IndexedString& sType)                                      \
{                                                                                   \
    return type::_is_valid(sType.c_str());                                          \
}

//=====================================================================================

#define MAKE_RAW_BASIC_TYPE_ACCESSORS(name, type)                                   \
type m_var##name;                                                                   \
type Get##name() const { return m_var##name; }                                      \
void Set##name(type varValue) { m_var##name = varValue; }

#define MAKE_RAW_OBJECT_TYPE_ACCESSORS(name, type)                                  \
type m_var##name;                                                                   \
const type& Get##name() const { return m_var##name; }                               \
type& Get##name() { return m_var##name; }                                           \
void Set##name(const type& varValue) { m_var##name = varValue; }

//=====================================================================================

#define MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(name, type)                       \
type m_var##name;                                                                   \
static void Init##name() { Get##type##StatNames().insert(#name); }                  \
type Get##name() const { return m_var##name; }                                      \
void Set##name(type varValue) { m_var##name = varValue; }

#define MAKE_RAW_OBJECT_TYPE_ACCESSORS_WITH_STATIC(name, type)                      \
type m_var##name;                                                                   \
static void Init##name() { Get##type##StatNames().insert(#name); }                  \
const type& Get##name() const { return m_var##name; }                               \
type& Get##name() { return m_var##name; }                                           \
void Set##name(const type& varValue) { m_var##name = varValue; }

//=====================================================================================

#define MAKE_JSON_BASIC_TYPE_ACCESSORS(name, type)                                  \
Bool IsValid##name() const { return m_Data.find(#name) != m_Data.end(); }           \
type Get##name() const                                                              \
{                                                                                   \
    if(m_Data.find(#name) != m_Data.end())                                          \
    {                                                                               \
        return m_Data[#name];                                                       \
    }                                                                               \
    return type();                                                                  \
}                                                                                   \
void Set##name(const type& varValue) { m_Data[#name] = varValue; }

//=====================================================================================

#define WRAPPING_ADD_CONSTRUCTOR_SIMPLE()                                                                   \
.def(PyBindInit<>())

#define WRAPPING_ADD_CONSTRUCTOR_ARGS(...)                                                                  \
.def(PyBindInit<__VA_ARGS__>())

#define WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(name, base)                                             \
.def_property_readonly(#name, &base::Get##name)

#define WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(name, base)                                           \
.def_property_readonly(#name, PyBindOverloadCast<>(&base::Get##name, PyBindConst))

#define WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(name, base)                                                      \
.def_property(#name, &base::Get##name, &base::Set##name)

#define WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(name, base)                                                    \
.def_property(#name, PyBindOverloadCast<>(&base::Get##name, PyBindConst), &base::Set##name)

#define WRAPPING_STANDALONE_METHOD_SIMPLE(name, base)                                                       \
m.def(#name, &base::name)

#define WRAPPING_STANDALONE_METHOD_FUNC(name, func, base)                                                   \
m.def(#name, &base::func)

#define WRAPPING_STANDALONE_METHOD_POLICY(name, base, policy)                                               \
m.def(#name, &base::name, policy)

#define WRAPPING_ADD_METHOD_SIMPLE(name, base)                                                              \
.def(#name, &base::name)

#define WRAPPING_ADD_METHOD_FUNC(name, func, base)                                                          \
.def(#name, &base::func)

#define WRAPPING_ADD_METHOD_ARGS(name, base, ...)                                                           \
.def(#name, &base::name, __VA_ARGS__)

#define WRAPPING_ADD_METHOD_POLICY(name, base, policy)                                                      \
.def(#name, &base::name, policy)

#define WRAPPING_ADD_METHOD_OVERLOADED(name, base, ...)                                                     \
.def(#name, PyBindOverloadCast<__VA_ARGS__>(&base::name))

#define WRAPPING_ADD_METHOD_OVERLOADED_CONST(name, base, ...)                                               \
.def(#name, PyBindOverloadCast<__VA_ARGS__>(&base::name, PyBindConst))

#define WRAPPING_ADD_METHOD_OVERLOADED_POLICY(name, base, policy, ...)                                      \
.def(#name, PyBindOverloadCast<__VA_ARGS__>(&base::name), policy)

#define WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(name, base, policy, ...)                                \
.def(#name, PyBindOverloadCast<__VA_ARGS__>(&base::name, PyBindConst), policy)

//=====================================================================================

#endif
