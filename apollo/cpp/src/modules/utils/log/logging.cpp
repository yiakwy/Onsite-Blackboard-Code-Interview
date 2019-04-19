//
//  logging.cpp
//  MY_GRAND_PROJECT/common/log
//
//  Created by Lei Wang 王磊 on 2018/11/25.
//
#include "logging.hpp"

void init_GLog(int argc, const char** argv)
{
    FLAGS_logtostderr = true;
    
    // log buffer
    string buf;
    unique_ptr<char[]> internal( new char[BUF_SIZE] );
    int location = -1;
    
    C_FORMAT(buf, internal, location, "%s", LOG_DIR.c_str());
    // fLS::FLAGS_log_dir = buf;
    google::SetLogDestination(google::GLOG_INFO, buf.c_str());
    google::SetLogDestination(google::GLOG_WARNING, buf.c_str());
    google::SetLogDestination(google::GLOG_ERROR, buf.c_str());
    // init GLog
    google::InitGoogleLogging(argv[0]);
}

char* getFormattedTime(void)
{
    time_t rawtime;
    struct tm* timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    // Must be static, otherwise won't work
    static char _repr_val[20];
    strftime(_repr_val, sizeof(_repr_val), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    return _repr_val;
    
}

string
format(const char* fmt, ...)
{
    va_list ap;
    char buf[BUF_SIZE];
    string ret;
    
    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
      va_end(ap);
    
    ret = buf;
    return ret;
    
}
