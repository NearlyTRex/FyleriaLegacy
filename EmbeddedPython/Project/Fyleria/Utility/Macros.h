// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_MACROS_H_
#define _GECKO_UTILITY_MACROS_H_

//======================================================================================================================

#define THROW_LOGIC_ERROR(message) { throw LogicError(message, __FILE__, __LINE__); }
#define THROW_RUNTIME_ERROR(message) { throw RuntimeError(message, __FILE__, __LINE__); }
#define THROW_PYTHON_ERROR(message) { throw PythonError(message, __FILE__, __LINE__); }

//======================================================================================================================

#define SET_JSON_DATA(name)                                                                                             \
{                                                                                                                       \
    jsonData[#name] = obj.Get##name();                                                                                  \
}

#define SET_OBJ_DATA(name, value_type)                                                                                  \
{                                                                                                                       \
    if(jsonData.find(#name) != jsonData.end())                                                                          \
    {                                                                                                                   \
        obj.Set##name(jsonData[#name].get<value_type>());                                                               \
    }                                                                                                                   \
    else                                                                                                                \
    {                                                                                                                   \
        obj.Set##name({});                                                                                              \
    }                                                                                                                   \
}

//======================================================================================================================

#define MAKE_COMMON_TYPEDEFS(type)                                                                                      \
typedef type* type##Ptr;                                                                                                \
typedef STDSharedPtr<type> type##SharedPtr;                                                                             \
typedef STDReferenceWrapper<type> type##Ref;                                                                            \
typedef STDVector<type> type##Array;                                                                                    \
typedef STDVector<type##Ptr> type##PtrArray;                                                                            \
typedef STDVector<type##Ref> type##RefArray;                                                                            \
typedef STDVector<type##SharedPtr> type##SharedPtrArray

//======================================================================================================================

#define MAKE_PRIMITIVE_TYPE_ACCESSORS(name, type)                                                                       \
type m_var##name {};                                                                                                    \
type Get##name() { return m_var##name; }                                                                                \
void Set##name(type varValue) { m_var##name = varValue; }

#define MAKE_PRIMITIVE_TYPE_ACCESSORS_INITIAL_VALUE(name, type, value)                                                  \
type m_var##name = value;                                                                                               \
type Get##name() { return m_var##name; }                                                                                \
void Set##name(type varValue) { m_var##name = varValue; }

#define MAKE_RAW_TYPE_ACCESSORS(name, type)                                                                             \
type m_var##name {};                                                                                                    \
const type& Get##name() const { return m_var##name; }                                                                   \
type& Get##name() { return m_var##name; }                                                                               \
void Set##name(const type& varValue) { m_var##name = varValue; }

#define MAKE_RAW_TYPE_ACCESSORS_INITIAL_VALUE(name, type, value)                                                        \
type m_var##name = value;                                                                                               \
const type& Get##name() const { return m_var##name; }                                                                   \
type& Get##name() { return m_var##name; }                                                                               \
void Set##name(const type& varValue) { m_var##name = varValue; }

#define MAKE_STAT_TYPE_ACCESSORS(name, type)                                                                            \
type Get##name() const { return GetStatValue<type>(#name); }                                                            \
void Set##name(const type& var##name) { SetStatValue(#name, var##name); }

//======================================================================================================================

#define MAKE_MODULE_RESULT_VARIANT(method)                                                                              \
void method##_StoreResult(const String& sResultID)                                                                      \
{                                                                                                                       \
    ResultManager::GetInstance()->StoreResult(sResultID, Json(method()).dump());                                        \
}

#define MAKE_MODULE_RESULT_VARIANT_A1(method, at1)                                                                      \
void method##_StoreResult(const String& sResultID, at1 av1)                                                             \
{                                                                                                                       \
    ResultManager::GetInstance()->StoreResult(sResultID, Json(method(av1)).dump());                                     \
}

#define MAKE_MODULE_RESULT_VARIANT_A2(method, at1, at2)                                                                 \
void method##_StoreResult(const String& sResultID, at1 av1, at2 av2)                                                    \
{                                                                                                                       \
    ResultManager::GetInstance()->StoreResult(sResultID, Json(method(av1, av2)).dump());                                \
}

#define MAKE_MODULE_RESULT_VARIANT_A3(method, at1, at2, at3)                                                            \
void method##_StoreResult(const String& sResultID, at1 av1, at2 av2, at3 av3)                                           \
{                                                                                                                       \
    ResultManager::GetInstance()->StoreResult(sResultID, Json(method(av1, av2, av3)).dump());                           \
}

#define MAKE_MODULE_RESULT_VARIANT_A4(method, at1, at2, at3, at4)                                                       \
void method##_StoreResult(const String& sResultID, at1 av1, at2 av2, at3 av3, at4 av4)                                  \
{                                                                                                                       \
    ResultManager::GetInstance()->StoreResult(sResultID, Json(method(av1, av2, av3, av4)).dump());                      \
}

//======================================================================================================================

#define MAKE_MANAGER_RETURN_LAMBDA(manager, method, return_type)                                                        \
[]() -> return_type { return manager::GetInstance()->method(); }

#define MAKE_MANAGER_RETURN_LAMBDA_A1(manager, method, return_type, at1)                                                \
[](at1 av1) -> return_type { return manager::GetInstance()->method(av1); }

#define MAKE_MANAGER_RETURN_LAMBDA_A2(manager, method, return_type, at1, at2)                                           \
[](at1 av1, at2 av2) -> return_type { return manager::GetInstance()->method(av1, av2); }

#define MAKE_MANAGER_RETURN_LAMBDA_A3(manager, method, return_type, at1, at2, at3)                                      \
[](at1 av1, at2 av2, at3 av3) -> return_type { return manager::GetInstance()->method(av1, av2, av3); }

#define MAKE_MANAGER_RETURN_LAMBDA_A4(manager, method, return_type, at1, at2, at3, at4)                                 \
[](at1 av1, at2 av2, at3 av3, at4 av4) -> return_type { return manager::GetInstance()->method(av1, av2, av3, av4); }

#define MAKE_MANAGER_VOID_LAMBDA(manager, method)                                                                       \
[]() { manager::GetInstance()->method(); }

#define MAKE_MANAGER_VOID_LAMBDA_A1(manager, method, at1)                                                               \
[](at1 av1) { manager::GetInstance()->method(av1); }

#define MAKE_MANAGER_VOID_LAMBDA_A2(manager, method, at1, at2)                                                          \
[](at1 av1, at2 av2) { manager::GetInstance()->method(av1, av2); }

#define MAKE_MANAGER_VOID_LAMBDA_A3(manager, method, at1, at2, at3)                                                     \
[](at1 av1, at2 av2, at3 av3) { manager::GetInstance()->method(av1, av2, av3); }

#define MAKE_MANAGER_VOID_LAMBDA_A4(manager, method, at1, at2, at3, at4)                                                \
[](at1 av1, at2 av2, at3 av3, at4 av4) { manager::GetInstance()->method(av1, av2, av3, av4); }

//======================================================================================================================

#define WRAPPING_ADD_CONSTRUCTOR_SIMPLE()                                                                               \
.def(PyBindInit<>())

#define WRAPPING_ADD_CONSTRUCTOR_ARGS(...)                                                                              \
.def(PyBindInit<__VA_ARGS__>())

#define WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(name, base)                                                         \
.def_property_readonly(#name, &base::Get##name)

#define WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(name, base)                                                       \
.def_property_readonly(#name, PyBindOverloadCast<>(&base::Get##name, PyBindConst))

#define WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(name, base)                                                                  \
.def_property(#name, &base::Get##name, &base::Set##name)

#define WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(name, base)                                                                \
.def_property(#name, PyBindOverloadCast<>(&base::Get##name, PyBindConst), &base::Set##name)

#define WRAPPING_STANDALONE_LAMBDA(name, lambda)                                                                        \
m.def(#name, lambda)

#define WRAPPING_STANDALONE_LAMBDA_POLICY(name, lambda, policy)                                                         \
m.def(#name, lambda, policy)

#define WRAPPING_STANDALONE_LAMBDA_ARGS(name, lambda, ...)                                                              \
m.def(#name, lambda, __VA_ARGS__)

#define WRAPPING_STANDALONE_METHOD_SIMPLE(name, base)                                                                   \
m.def(#name, &base::name)

#define WRAPPING_STANDALONE_METHOD_FUNC(name, func, base)                                                               \
m.def(#name, &base::func)

#define WRAPPING_STANDALONE_METHOD_POLICY(name, base, policy)                                                           \
m.def(#name, &base::name, policy)

#define WRAPPING_ADD_METHOD_SIMPLE(name, base)                                                                          \
.def(#name, &base::name)

#define WRAPPING_ADD_METHOD_STATIC_SIMPLE(name, base)                                                                   \
.def_static(#name, &base::name)

#define WRAPPING_ADD_METHOD_FUNC(name, func, base)                                                                      \
.def(#name, &base::func)

#define WRAPPING_ADD_METHOD_STATIC_FUNC(name, func, base)                                                               \
.def_static(#name, &base::func)

#define WRAPPING_ADD_METHOD_ARGS(name, base, ...)                                                                       \
.def(#name, &base::name, __VA_ARGS__)

#define WRAPPING_ADD_METHOD_STATIC_ARGS(name, base, ...)                                                                \
.def_static(#name, &base::name, __VA_ARGS__)

#define WRAPPING_ADD_METHOD_POLICY(name, base, policy)                                                                  \
.def(#name, &base::name, policy)

#define WRAPPING_ADD_METHOD_STATIC_POLICY(name, base, policy)                                                           \
.def_static(#name, &base::name, policy)

#define WRAPPING_ADD_METHOD_OVERLOADED(name, base, ...)                                                                 \
.def(#name, PyBindOverloadCast<__VA_ARGS__>(&base::name))

#define WRAPPING_ADD_METHOD_OVERLOADED_CONST(name, base, ...)                                                           \
.def(#name, PyBindOverloadCast<__VA_ARGS__>(&base::name, PyBindConst))

#define WRAPPING_ADD_METHOD_OVERLOADED_POLICY(name, base, policy, ...)                                                  \
.def(#name, PyBindOverloadCast<__VA_ARGS__>(&base::name), policy)

#define WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(name, base, policy, ...)                                            \
.def(#name, PyBindOverloadCast<__VA_ARGS__>(&base::name, PyBindConst), policy)

//======================================================================================================================

#endif
