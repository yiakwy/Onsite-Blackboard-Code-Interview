//
//  logging.cpp
//  KMP
//
//  Created by Wang Yi on 15/3/17.
//  Copyright © 2017 Wang yiak.co. All rights reserved.
//

#include "logging.hpp"

void globalInit(int argc, const char* argv[])
{
    FLAGS_logtostderr = true;
    FLAGS_log_dir = "/Users/wangyi";
    google::SetLogDestination(google::GLOG_INFO,"/Users/wangyi");
    google::InitGoogleLogging(argv[0]);
    
}