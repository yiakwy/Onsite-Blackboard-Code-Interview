//
//  logging.hpp
//  common/log
//
//  Created by Lei Wang 王磊 on 2018/11/25.
//

#ifndef LOGGING_H_
#define LOGGING_H_

#include <stdio.h>
#include <stdarg.h>
#ifdef HAVE_LIB_GFLAGS
#include <gflags/gflags.h>
using namespace gflags;
#endif
#include <glog/logging.h>
#include <iostream>
#include <cstdio>
#include <string.h>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <locale>

// https://stackoverflow.com/questions/19432632/c11-gcc-4-8-static-thread-local-stdunique-ptr-undefined-reference
#include <memory>
using std::unique_ptr;

#include <time.h>

#include "cmake_config.h"

using std::string;
using std::ostringstream;

char* getFormattedTime(void);

#define __SHORT_FILE__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define __SHORT_FILE(NAME) (strrchr(NAME, '/')+1)
#define __GET_FORMATTED_TIME() getFormattedTime()
#define BUF_SIZE 256

#define C_FORMAT(buf, internal, location, fmt, ...) \
    do { \
       sprintf(internal.get(), fmt, ## __VA_ARGS__, &location); \
           buf = string(internal.get(), internal.get() + strlen(internal.get())); \
    } while (0)

#define COMMON_LOGGER(LEVEL) (LOG(LEVEL))

#define COMMON_LOG_INFO (LOG(INFO) << format("[%s]: %s ", "INFO", getFormattedTime() ) )
#define COMMON_LOG_WARNING (LOG(WARNING) << format("[%s]: %s ", "WARNING", getFormattedTime() ) )
#define COMMON_LOG_ERROR (LOG(ERROR) << format("[%s]: %s ", "ERROR", getFormattedTime() ) )

void init_GLog(int argc, const char* argv[]);
// see https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// see also boost::trim
/*
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}
*/

string
format(const char* fmt, ...);

#endif /* logging_hpp */
