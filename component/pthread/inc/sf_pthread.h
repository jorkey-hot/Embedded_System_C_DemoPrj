
/*****************************************************************************************************
 * @file sf_phread.h
 * @brief 本文件与所有pthread线程相关源文件关联
 * @author 付昊宇
 * 
 *****************************************************************************************************/

#ifndef _SF_PTHREAD_H_
#define _SF_PTHREAD_H_

#include "sf_c_public.h"
#include "sf_os.h"
#include "../../zlog/inc/zlog_conf.h"

#ifdef SF_LINUX//使用Linux操作系统
#include "sf_linux.h"
#else //使用rtthread操作系统


#endif
/* ==============================宏相关定义============================== */

#define MSG_QUEUE_NODE_MAX_LEN (U32)(1024*2) /* 消息队列单节点最大字节长度 可自定义*/
#define MSG_QUEUE_NODE_MAX_NUM  (U32)(1000)/* 每个消息队列最大有1000个节点数量 */

/* ==============================枚举相关定义============================== */
typedef enum
{
    MAIN_THREAD=0,
    TEST_RECV_THREAD,
    TEST_PRO_THREAD,
    THREAD_END
}THREAD_ID_T;




/* ==============================结构体相关定义============================== */
#pragma pack(1)



/******
 * @brief 消息队列数据结构体
 * @param STID 源线程id
 * @param DTID 目的线程id
 * @param msgLen 消息长度，字节
 * @param data 数据缓存
 */
typedef struct
{
	U16		STID;
	U16		DTID;
	U16		msgLen;
    U08 data[MSG_QUEUE_NODE_MAX_LEN];
}SF_MSG_QUEUE_DATA_T;


/******
 * @brief 消息队列节点结构体
 * @param sf_msg_queue_data 消息队列缓存数据
 * @param prev 后节点地址
 * @param next 前节点地址
 */
typedef struct
{
    SF_MSG_QUEUE_DATA_T sf_msg_queue_data;
    struct SF_MSG_QUEUE_NODE_T* prev;
    struct SF_MSG_QUEUE_NODE_T* next;
    
}SF_MSG_QUEUE_NODE_T;

/******
 * @brief 消息队列结构体
 * @param sf_msg_queue_head 表示对应消息队列链表的头节点，如果不为NULL，则表示消息队列中有数据
 * @param mutex 对应消息队列的锁
 * @param not_full 消息队列未满标识
 * @param not_empty 消息队列非空标识
 * @param node_num 表示已使用的链表节点数量
 */
typedef struct
{
    // SF_MSG_QUEUE_NODE_T* sf_msg_queue_head;//表示对应消息队列链表的头节点，如果不为NULL，则表示消息队列中有数据
    #ifdef SF_LINUX//使用Linux操作系统时使用的锁变量
    pthread_mutex_t mutex;//锁
    pthread_cond_t not_full;//条件变量
    pthread_cond_t not_empty;
    #else //使用rtthread操作系统

    #endif
    U16 node_num;
}SF_MSG_QUEUE_T;


/******
 * @brief 统一的线程结构体
 * @param thread_name 线程名称，最长16字节
 * @param thread_id 线程id
 * @param pthread_creat 线程创建接口函数
 *  
 */
typedef struct
{
    S08 thread_name[16];
    U16 thread_id;
    SF_MSG_QUEUE_T thread_MsgQueue;
    int (*pthread_creat)(void* self,void* func_start,void* func_arg);//不同系统使用的创建函数名不同
}SF_PTHREAD_T;


#pragma pack()
#ifdef SF_LINUX//使用Linux操作系统
int sf_pthread_create_linux(void* self,void* func_start,void* func_arg);

int sf_pthread_MsgQueueInit(SF_PTHREAD_T* thread);


#else //使用rtthread操作系统

#endif


#endif


