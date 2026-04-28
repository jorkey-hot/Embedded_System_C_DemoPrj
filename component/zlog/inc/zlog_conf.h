#ifndef __ZLOG_CONF_H_
#define __ZLOG_CONF_H_
#include "zlog.h"

extern zlog_category_t *user_cat;
int zlog_start(void);
void zlog_data(unsigned char* p_data,int len, const char* format, ...);
#define LOG_FATAL(...) zlog_fatal(user_cat, __VA_ARGS__)  
#define LOG_ERROR(...) zlog_error(user_cat, __VA_ARGS__)  
#define LOG_WARN(...) zlog_warn(user_cat, __VA_ARGS__)  
#define LOG_NOTICE(...) zlog_notice(user_cat, __VA_ARGS__)  
#define LOG_INFO(...) zlog_info(user_cat, __VA_ARGS__)  
#define LOG_DEBUG(...) zlog_debug(user_cat, __VA_ARGS__)  
#define LOG_DATA_PRINT(p_data,len,...) zlog_data(p_data,len,__VA_ARGS__)




#endif
