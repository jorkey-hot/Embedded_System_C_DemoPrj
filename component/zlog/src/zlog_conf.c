#include "../inc/zlog_conf.h"
#include <sys/time.h>
#include <time.h>


zlog_category_t *user_cat=NULL;


#define ZLOG_CONF_FILE "zlog_conf.conf"
int zlog_start(void)
{
    int rc = 0;

    rc = zlog_init(ZLOG_CONF_FILE);
    if (rc)
    {
        printf("Zlog init failed,Please check file 'zlog_conf.conf' or check DIR 'log'!\t\n");

        return -1;
    }
    user_cat = zlog_get_category("mycat");
    if (!user_cat)
    {
        printf("get user_cat fail!\t\n");
        zlog_fini();
        return -2;
    }
    return 0;
}

void zlog_addLogHead(char * pOutFormat, const char * pInFormat)
{
	char timeInfo[100] = {0};
	struct timeval tv;
	struct timezone tz;
	struct tm * temptm = NULL;

	/* 打印时间 */
	gettimeofday(&tv, &tz);
	temptm = localtime(&tv.tv_sec);
	snprintf(timeInfo, 100, "%04d-%02d-%02d %02d:%02d:%02d.%03ld ", 
						temptm->tm_year + 1900, temptm->tm_mon + 1, temptm->tm_mday,
						temptm->tm_hour, temptm->tm_min, temptm->tm_sec, tv.tv_usec/1000);
	snprintf(pOutFormat, 1024, "%s%s", timeInfo, pInFormat);
}


void zlog_data(unsigned char* p_data,int len, const char* format, ...)
{
	char newFormat[1024] = {0};
    int ix=0;
	va_list ap;
	zlog_addLogHead(newFormat, format);
    va_start(ap,format);
    zlog_debug(user_cat,newFormat,ap);
    va_end(ap);

    zlog_debug(user_cat,"0x");
	for(ix = 0; ix < len; ix++)
	{
		zlog_debug(user_cat, "%02x ", p_data[ix]);
	}
    zlog_debug(user_cat,"\t\n");
}







