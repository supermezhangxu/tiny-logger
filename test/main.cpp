#include "AsyncLogging.h"
#include "Logging.h"
#include "base/Timestamp.h"

#include <stdio.h>


static const off_t kRollSize = 1*1024*1024;
AsyncLogging* g_asyncLog = NULL;

inline AsyncLogging* getAsyncLog()
{
    return g_asyncLog;
}

void test_Logging()
{
    LOG_DEBUG << "debug";
    LOG_INFO << "info";
    LOG_WARN << "warn";
    LOG_ERROR << "error";

    const int n = 10;
    for (int i = 0; i < n; ++i) {
        LOG_INFO << "Hello, " << i << " abc...xyz";
    }
}

void test_AsyncLogging()
{
    const int n = 1024;
    for (int i = 0; i < n; ++i) {
        LOG_INFO << "Hello, " << i << " abc...xyz";
    }
}

void asyncLog(const char* msg, int len)
{
    AsyncLogging* logging = getAsyncLog();
    if (logging)
    {
        logging->append(msg, len);
    }
}

int main(int argc, char* argv[])
{
    printf("pid = %d\n", getpid());

    AsyncLogging log("test_log", kRollSize);
    test_Logging();

    g_asyncLog = &log;
    Logger::setOutput(asyncLog); // 为Logger设置输出回调, 重新配接输出位置
    log.start();

    test_Logging();
    //test_AsyncLogging();

    std::thread t1([](){
        for (int i = 0; i < 10; ++i) {
            LOG_WARN << "LOG_WARN Test...";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    std::thread t2([](){
        for (int i = 0; i < 10; ++i) {
            LOG_ERROR << "LOG_ERROR Test...";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        
    });

    std::thread t3([](){
        for (int i = 0; i < 10; ++i) {
            LOG_ERROR << "LOG_ERROR Test...";
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        
    });

    t1.join();
    t2.join();
    t3.join();

    log.stop();
    return 0;
}
