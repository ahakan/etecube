/**
 * @file utilities.h
 * @author ahc (info@ahakan.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <chrono>
#include <string.h>


class Utilities
{
    protected:  
                            Utilities();
                            ~Utilities();

    public:
                            Utilities(const Utilities&)               = delete;       // Singletons should not be cloneable.
                            Utilities& operator=(const Utilities&)    = delete;       // Singletons should not be assignable.

        static Utilities    *instance();
        
        std::string         getTimestamp();
        std::string         convertToString(char* buf);
};

#endif