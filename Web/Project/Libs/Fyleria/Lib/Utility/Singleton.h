// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_SINGLETON_H_
#define _GECKO_SINGLETON_H_

namespace Gecko
{

template<typename T>
class Singleton
{
public:

    // Constructors
    Singleton() {}

    // Get instance
    static T* GetInstance()
    {
        if(!m_Instance)
        {
            Singleton<T>::m_Instance = new T;
        }
        return m_Instance;
    }

    // Destroy instance
    static void DestroyInstance()
    {
        delete Singleton<T>::m_Instance;
        Singleton<T>::m_Instance = nullptr;
    }

private:

    // Deleted
    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;

protected:
    static T* m_Instance;
};

template<typename T>
T* Singleton<T>::m_Instance = nullptr;

};

#endif
