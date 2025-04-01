#include <iostream>
#include <unistd.h>
#include <ctime>

int gval = 100;

void fun()
{

}

void *threadStart(void* args)
{
    while(true)
    {
        sleep(1);
        std::cout << "new thread running..." << ",pid: " << getpid() <<", gval:"<<gval<<",&gval:"<<&gval<<std::endl;
        fun();
    }
}

int main()
{
    srand(time(nullptr));

    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;

    pthread_create(&tid1, nullptr, threadStart, (void*)"Thread-new");
    pthread_create(&tid2, nullptr, threadStart, (void *)"Thread-new");
    pthread_create(&tid3, nullptr, threadStart, (void *)"Thread-new");

    // 主线程
    while(true)
    {
        sleep(1);
        std::cout << "main thread running..." << ",pid: " << getpid() << ", gval:" << gval << ",&gval:" << &gval << std::endl;
        gval++;
        sleep(1);
    }
    return 0;
}
