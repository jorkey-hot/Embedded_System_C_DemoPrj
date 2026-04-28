/*****************************************************************************************************
 * @file sf_component.h
 * @brief 本文件定义所有组件状态
 * @author 付昊宇
 * 
 *****************************************************************************************************/

#ifndef _SF_COMPONENT_CFG_H_
#define _SF_COMPONENT_CFG_H_

#define SF_ZLOG_ENABLE 1 
#define SF_PTHREAD 1

#if (SF_ZLOG_ENABLE)
#include "zlog/inc/zlog_conf.h"
#endif

#if (SF_PTHREAD)
#include "pthread/inc/sf_pthread.h"
#endif



#endif
