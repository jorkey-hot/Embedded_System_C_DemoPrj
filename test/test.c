#include <stdio.h>
#include "../component/sf_component.h"


SF_PTHREAD_T test_recv_thread={.thread_name="recv_thread",.thread_id=TEST_RECV_THREAD,.pthread_creat=sf_pthread_create_linux};
SF_PTHREAD_T test_pro_thread={.thread_name="pro_thread",.thread_id=TEST_PRO_THREAD,.pthread_creat=sf_pthread_create_linux};
void test_recv_func(SF_PTHREAD_T* p_thread)
{
    while (1)
    {
        LOG_INFO("[%s] running!\t\n",p_thread->thread_name);
        sleep(1);
    }
}
void test_pro_func(SF_PTHREAD_T* p_thread)
{
    while (1)
    {
        LOG_INFO("[%s] running!\t\n",p_thread->thread_name);
        sleep(1);
    }
}
int main(int argc,char *argv[])
{
    if (zlog_start()!=0)
    {
        printf("zlog start fail!\t\n");
        return -1;
    }

    test_recv_thread.pthread_creat(&test_recv_thread,test_recv_func,(void*)&test_recv_thread);
    test_pro_thread.pthread_creat(&test_pro_thread,test_pro_func,(void*)&test_pro_thread);




    // for (int i = 0; i < atoi(argv[1]); i++)
    // {
    //     LOG_INFO("[main task] LOG times is %d!\t\n",i);
    // }
    while (1)
    {
        sleep(1);
    }
    
        
        
    

    return 0;

}
