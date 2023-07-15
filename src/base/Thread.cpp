#include "base/Thread.h"

void Thread::Start(EventCall onCreate, EventCall onRun, EventCall onDestory)
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (!_isRun)
    {
        _isRun = true;

        if (onCreate)
            _onCreate = onCreate;
        if (onRun)
            _onRun = onRun;
        if (onDestory)
            _onDestory = onDestory;

        // 线程
        std::thread t(std::mem_fn(&Thread::OnWork), this);
        t.detach();
    }
}

void Thread::Close()
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_isRun)
    {
        _isRun = false;
        _sem.wait();
    }
}

void Thread::Exit()
{
    if (_isRun)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _isRun = false;
    }
}
