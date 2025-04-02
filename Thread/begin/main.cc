#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

/*int main()
{
    signal(SIGCHLD, SIG_IGN); // 忽略子进程退出信号
    pid_t pid = fork();
    if (pid == 0)
    {
        int cnt = 5;
        while (cnt)
        {
            std::cout << "children running" << std::endl;
            cnt--;
            sleep(1);
        }
        exit(1);
    }
    while (true)
    {
        std::cout<< "father running" << std::endl;
        sleep(1);
    }
}*/

/*int main()
{
    int pid_t = fork();
    if (pid_t == 0)
    {
        sleep(1);
        int cnt = 5;
        while (cnt--)
        {
            std::cout << "child running" << std::endl;
            sleep(1);            
        }
        exit(1);
    }
    int status = 0;
    while (true)
    {
        std::cout << "father running" << std::endl;
        if(waitpid(-1, &status, WNOHANG) > 0)//指定要等待的进程id,返回子进程的退出码,非阻塞状态
        {
            std::cout << "等待成功" << std::endl;
            //std::cout << WIFEXITED(status) << std::endl; 正常退出
            std::cout << WEXITSTATUS(status) << std::endl; //退出码
            break;
        }
        sleep(1);
    }
    return 0;
}*/

/*void notice(int signo)
{
    std::cout << "收到信号: " << signo << " 进程ID: " << getpid() << std::endl;
    
    while (true)
    {
        pid_t rid = waitpid(-1, nullptr, WNOHANG);
        
        if (rid > 0)
        {
            std::cout << "成功回收子进程，进程ID: " << rid << std::endl;
        }
        else if (rid < 0)
        {
            std::cout << "没有子进程需要回收" << std::endl;
            break;  // 退出循环
        }
        else
        {
            std::cout << "还有子进程在运行" << std::endl;
            break;  // 退出循环
        }
    }
}

void DoOtherThing()
{
    std::cout<< "DoOtherThing~" << std::endl;
}


int main()
{
    signal(SIGCHLD, notice);
    for (int i = 0; i < 10; i++)
    {
        pid_t id = fork();
        if (id == 0)
        {
            std::cout<< "I am chid pid: " << getpid() << std::endl;  
            sleep(3);
            exit(1);
        }
    }
    while (true)
    {
        DoOtherThing();
        sleep(1);
    }
    return 0;

}*/

/*volatile int gflag = 0;//每次都要从内存中读取, 每次都要放在内存中

void changedata(int signo)
{
    std::cout<< "get a signo: " << signo << ", change gflag 0 -> 1" << std::endl;
    gflag = 1;
}

int main()
{
    signal(2, changedata); // 中断信号

    while (!gflag);
    std::cout<< "process quie normal" << std::endl;
    
}*/

void Print(sigset_t &pending)
{
    for (int sig = 31; sig > 0; sig--)
    {
        if (sigismember(&pending, sig))
        {
            std::cout << 1;
        }
        else
        {
            std::cout << 0;
        }
    }
    std::cout << std::endl;
}

void handler(int signum)
{
    std::cout<< "get a sig: " << signum << std::endl;
    while (true)
    {
        sigset_t pending;
        sigpending(&pending);

        Print(pending);

        sleep(1);
        //break;
    }
    //exit(1);
}

int main()
{
    struct sigaction act, oact;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, 3);
    act.sa_flags = 0;

    for (int i = 0; i <= 31; i++)
    {
        sigaction(i, &act, &oact);
    }

    while (true)
    {
        std::cout << "I am a process, pid: " << getpid() << std::endl;
        sleep(1);
    }
    return 0;

}




