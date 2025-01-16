#pragma once
#include "Define.h"
#include "CObject.h"
template<typename T>
class CObjPool
{
public:
    CObjPool(size_t initial_size = 10)
    {
        for (size_t i = 0; i < initial_size; i++)
        {
            m_PoolQueue.push(new T());  // 流立 货肺款 按眉 积己
        }
    }
    ~CObjPool()
    {
        while (!m_PoolQueue.empty())
        {
            Safe_Delete<T*>(m_PoolQueue.front());
            m_PoolQueue.pop();
        }
    }
    void Return_Obj(T* obj)
    {
        if (obj)
        {
            m_PoolQueue.push(obj);
        }
    }
    T* Get_Obj()
    {
        if (m_PoolQueue.empty())
        {
            T* tmpObj = new T();
            tmpObj->Initialize();
            return tmpObj;  // 货肺款 按眉 积己
        }
        T* tmpObj = m_PoolQueue.front();
        tmpObj->Initialize();
        m_PoolQueue.pop();
        return tmpObj;
    }
private:
    queue<T*> m_PoolQueue;
};

