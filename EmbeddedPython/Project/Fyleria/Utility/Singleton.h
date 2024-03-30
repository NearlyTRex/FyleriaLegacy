// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_SINGLETON_H_
#define _GECKO_UTILITY_SINGLETON_H_

// Internal includes
#include "Utility/ObjectThreadsafe.h"

namespace Gecko
{

template<typename T>
class Singleton
{
public:

    // Constructors
    Singleton() = default;
    ~Singleton() = default;

    // Get instance
    static SafePtr<T>& GetInstance()
    {
        return m_pInstance;
    }

private:

    // Data
    static SafePtr<T> m_pInstance;

    // Deleted
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

template<typename T>
SafePtr<T> Singleton<T>::m_pInstance = {};

};

#endif
