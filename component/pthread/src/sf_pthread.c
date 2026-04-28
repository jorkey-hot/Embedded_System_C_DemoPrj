
/*****************************************************************************************************
 * @file sf_phread.c
 * @brief 本文件定义多线程相关动作
 * @author 付昊宇
 * 
 *****************************************************************************************************/
#include "../inc/sf_pthread.h"


#ifdef SF_LINUX//使用Linux操作系统

/****************************************
 * @brief 线程创建函数
 * @param self SF_PTHREAD_T结构体指针
 * @param func_start 函数名
 * @param func_arg 函数参数
 * @note 创建分离线程
 * @return 0-成功 -1-失败
 ****************************************/
int sf_pthread_create_linux(void* self,void* func_start,void* func_arg)
{
	pthread_t tid;
    if (NULL==self || NULL==func_start)
    {
        LOG_ERROR("Parameter invalid!\t\n");
        return -1;
    }
    SF_PTHREAD_T* p_thread_t=(SF_PTHREAD_T*)self;
    
	pthread_attr_t thread_attr;

	if(0 != pthread_attr_init(&thread_attr))
	{
		LOG_ERROR("pthread_attr_init fail, err is: %s.\r\n", strerror(errno));
		return -1;
	}
	pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);//设置分离线程
	if(0 != pthread_create(&tid, &thread_attr, func_start, func_arg))
	{
		LOG_ERROR("pthread_create fail, err is: %s.\r\n", strerror(errno));
		return -1;
	}
    prctl(PR_SET_NAME,p_thread_t->thread_name,0,0,0);
	// 初始化线程消息队列
	int ret=sf_pthread_MsgQueueInit(p_thread_t);
	if (ret!=0)
	{
		LOG_ERROR("pthread's MsgQueue init fail,err is %d",ret);
		return -2;
	}
	LOG_INFO("The thread name[%s] id[%d] create success\t\n",p_thread_t->thread_name,p_thread_t->thread_id);
	return 0;
}

#else //使用rtthread操作系统


#endif




