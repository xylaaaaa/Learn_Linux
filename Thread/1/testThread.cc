#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// void threadrun(std::string name, int num)
// {
//     while(num)
//    {
//         std::cout << "num: " << num << std::endl;
//         num--;
//         sleep(1);
//     }

// }

// int main()
// {
//     std::string name = "thread-1";
//     std::thread mythread(threadrun, std::move(name), 10);
//     while (true)
//     {
//         std::cout << "main thread..." << std::endl;
//         sleep(1);
//     }
//     mythread.join();
//     return 0;
// }

class ThreadData
{
public:
    ThreadData(const std::string &threadName, int valueX, int valueY)
        : name(threadName), x(valueX), y(valueY) {}

    int Excute()
    {
        return x + y;
    }

    const std::string &getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }

private:
    std::string name;
    int x;
    int y;

    friend void *threadRun(void *args); // 允许threadRun访问私有成员
};

class ThreadResult
{
public:
    std::string print()
    {
        return std::to_string(x) + "+" + std::to_string(y) + "=" + std::to_string(result);
    }
    int x;
    int y;
    int result;
};

void *threadRun(void *args)
{
    ThreadData *td = static_cast<ThreadData *>(args);
    ThreadResult *result = new ThreadResult();
    int cnt = 10;
    while (cnt)
    {
        sleep(3);
        std::cout << td->name << " run ..." << ", cnt: " << cnt-- << std::endl;
        result->result = td->Excute();
        result->x = td->x;
        result->y = td->y;
        break;
    }
    delete td;
    //exit(1) 这是终止进程的
    //pthrea_exit(args) 这是终止线程的
    return (void *)result;
}

std::string PrintToHex(pthread_t &tid)
{
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "0x%lx", tid);
    return buffer;
}

//main函数结束 和 main thread结束 -> 进程结束

int main()
{
    std::vector<pthread_t> threads;
    const int NUM_THREADS = 3;

    // 创建多个线程
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_t tid;
        ThreadData *data = new ThreadData(
            "Thread-" + std::to_string(i),
            i * 10,
            i * 20);

        if (pthread_create(&tid, nullptr, threadRun, data) != 0)
        {
            std::cerr << "Failed to create thread " << i << std::endl;
            delete data;
            continue;
        }
        threads.push_back(tid);
    }

    // 等待所有线程完成并获取结果
    for (size_t i = 0; i < threads.size(); i++)
    {
        void *thread_result;
        pthread_join(threads[i], &thread_result);

        if (thread_result != nullptr)
        {
            ThreadResult *tr = static_cast<ThreadResult *>(thread_result);
            std::cout << "Thread " << i << " result: " << tr->print() << std::endl;
            delete tr; // 清理内存
        }
    }

    return 0;
}

// pthread_detach(tid) 主线程分离新线程 不用再去join()
// 没有被分离的线程,默认是 joinable 需要手动join
