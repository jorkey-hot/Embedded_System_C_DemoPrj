/*****************************************************************************************************
 * @file sf_phread_MsgQueue.c
 * @brief 本文件定义多线程消息队列相关动作
 * @author 付昊宇
 *
 *****************************************************************************************************/
#include "../inc/sf_pthread.h"

static SF_MSG_QUEUE_NODE_T total_MsgQueue_pool[THREAD_END][MSG_QUEUE_NODE_MAX_NUM] = {0};
static SF_MSG_QUEUE_NODE_T *p_free_MsgQueue_node[THREAD_END] = {NULL}; /* 对应每个线程的空闲消息队列节点头指针 */
/****************************************
 * @brief 消息队列链表池初始化
 * @return 0-成功 -1-失败
 ****************************************/
int sf_pthread_MsgQueuePoolInit(void)
{
    for (int i = 0; i < THREAD_END; i++)
    {
        p_free_MsgQueue_node[i] = total_MsgQueue_pool[i];
    }
    for (int i = 0; i < THREAD_END; i++)
    {
        for (int j = 0; j < MSG_QUEUE_NODE_MAX_NUM - 1; j++)
        {
            total_MsgQueue_pool[i][j].next = (SF_MSG_QUEUE_NODE_T *)&total_MsgQueue_pool[i][j + 1];
            total_MsgQueue_pool[i][j + 1].prev = &total_MsgQueue_pool[i][j];
        }
        total_MsgQueue_pool[i][MSG_QUEUE_NODE_MAX_NUM - 1].next = NULL;
    }
    return 0;
}

/*****
 * @brief 链表节点申请
 */
SF_MSG_QUEUE_NODE_T *sf_pthread_node_alloc(SF_PTHREAD_T *thread)
{
    SF_MSG_QUEUE_NODE_T *p = p_free_MsgQueue_node[thread->thread_id];
    if (p == NULL)
    {
        return NULL;
    }
    p_free_MsgQueue_node[thread->thread_id] = p_free_MsgQueue_node[thread->thread_id]->next;
    p_free_MsgQueue_node[thread->thread_id]->prev=NULL;
    p->next = NULL;
    p->prev = NULL;
    return p;
}
/*****
 * @brief 链表节点归还
 */
int sf_pthread_node_free(SF_MSG_QUEUE_NODE_T *p_node)
{
    if (p_node == NULL)
    {
        LOG_ERR("Node free fail,parameter is invalid!\t\n");
        return -1;
    }
    p_node->prev=NULL;
    p_node->next=p_free_MsgQueue_node[thread->thread_id];
    p_free_MsgQueue_node[thread->thread_id] = p_node;
    return 0;
}


/****************************************
 * @brief 线程对应消息队列初始化
 * @param thread 线程结构体指针
 * @return 0-成功 -1-失败
 ****************************************/
int sf_pthread_MsgQueueInit(SF_PTHREAD_T *thread)
{
    if (NULL == thread)
    {
        LOG_ERROR("Parameter invalid!\t\n");
        return -1;
    }
    // 初始化线程池
    thread->thread_MsgQueue.sf_msg_queue_head == NULL; /* 初始化时头节点指向空 */
#ifdef SF_LINUX // 使用Linux操作系统
    if (pthread_mutex_init(&thread->thread_MsgQueue.mutex, NULL) != 0)
    {
        LOG_ERROR("The mutex of thread[%s] init fail!\t\n", thread->thread_name);
        return -2;
    }
    else
    {
        LOG_INFO("The mutex[%d] of thread[%s] init success!\t\n", thread->thread_MsgQueue.mutex, thread->thread_name);
    }

    if (pthread_cond_init(&thread->thread_MsgQueue.not_full, NULL) != 0)
    {
        LOG_ERROR("The cond[not_full] of thread[%s] init fail!\t\n", thread->thread_name);
        return -3;
    }
    else
    {
        LOG_INFO("The cond[not_full][%d] of thread[%s] init success!\t\n", thread->thread_MsgQueue.not_full, thread->thread_name);
    }

    if (pthread_cond_init(&thread->thread_MsgQueue.not_empty, NULL) != 0)
    {
        LOG_ERROR("The cond[not_empty] of thread[%s] init fail!\t\n", thread->thread_name);
        return -4;
    }
    else
    {
        LOG_INFO("The cond[not_empty][%d] of thread[%s] init success!\t\n", thread->thread_MsgQueue.not_empty, thread->thread_name);
    }
#else // 使用rtthread操作系统
#endif

    return 0;
}


/****************************************
 * @brief 消息队列发送函数
 * @param p_msg 消息指针
 * @return 0-成功 -1-失败
 ****************************************/
int sf_phread_msg_send(SF_MSG_QUEUE_NODE_T *p_msg)
{
    if (p_msg==NULL)
    {
        LOG_ERROR("");
    }
    
}









