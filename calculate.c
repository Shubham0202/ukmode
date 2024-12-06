#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<sys/resource.h>

void childProcesses(int id){
    printf("Child process %d start\n",id);
    sleep(id);
    printf("Child process %d end\n",id);
    exit(EXIT_SUCCESS);
}
int main()
{
    struct rusage usage;
    struct rusage total_usage={0};
    int n;
    printf("Enter how many processes you wnat to run:");
    scanf("%d",&n);
    
    pid_t pid[n];
    for(int i=0;i<n;i++)
    {
        pid[i]=fork();
        if(pid[i] ==0)
            childProcesses(i+1);
        
    }
    
    for (int i = 0; i < n; i++) {
	
        waitpid(pid[i],NULL,0);
        
        if (getrusage(RUSAGE_CHILDREN, &usage) == 0) {
        total_usage.ru_utime.tv_sec+=usage.ru_utime.tv_sec;
        total_usage.ru_utime.tv_usec+=usage.ru_utime.tv_usec;
        total_usage.ru_stime.tv_sec+=usage.ru_stime.tv_sec;
        total_usage.ru_stime.tv_usec+=usage.ru_stime.tv_usec;
        }
    }
    
    printf("Total user time: %ld.%06ld",(long)total_usage.ru_utime.tv_sec,(long)total_usage.ru_utime.tv_usec);
    printf("\nTotal Kernel time: %ld.%06ld",(long)total_usage.ru_stime.tv_sec,(long)total_usage.ru_stime.tv_usec);
}
