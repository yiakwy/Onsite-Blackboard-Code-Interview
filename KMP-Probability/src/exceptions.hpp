//
//  exceptions.hpp
//  KMP
//
//  Created by Wang Yi on 15/3/17.
//  Copyright © 2017 Wang yiak.co. All rights reserved.
//

#ifndef exceptions_hpp
#define exceptions_hpp

#include <stdio.h>

#include <exception>
#include <string>

class NotEnoughMemory: public std::exception
{
public:
    // lvalue type
    explicit NotEnoughMemory(const char* message):
    msg_("Not Enough Memory when allocating ")
    {
        this->msg_ +=
        (message == nullptr) ? "..." : message;
        
    };
    
    ~NotEnoughMemory() throw () {};
    const char* what() const throw () {
        return msg_.c_str();
    };
    
    
protected:
    std::string msg_;
};


#endif /* exceptions_hpp */
