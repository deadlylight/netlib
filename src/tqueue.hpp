#pragma once
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

template <class Q, class T>
class TQueue : public Q
{
private:
    queue<shared_ptr<T>> mQ;
    mutex mMutex;
    condition_variable mCond;

public:
    void push(shared_ptr<T> inT) override
    {
        unique_lock<mutex> vLock;
        mQ.push(inT);
        mCond.notify_one();
    }

    shared_ptr<T> pop(bool inNonBlock) override
    {
        unique_lock<mutex> vLock;
        while (mQ.empty())
        {
            if (inNonBlock)
            {
                return nullptr;
            }
            mCond.wait(vLock);
        }
        shared_ptr<T> vT = mQ.front();
        mQ.pop();
        return vT;
    }

    void move(Q *inQ) override
    {
        while (1)
        {
            shared_ptr<T> vT = inQ->pop(true);
            if (!vT)
            {
                break;
            }
            push(vT);
        }
    }
};
