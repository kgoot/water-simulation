//
// Created by Dillon Yao on 4/15/18.
//

#ifndef F2_UTIL_H
#define F2_UTIL_H

#include <iostream>

inline void scoped_msg(const char *scope, const char *msg, int level=0, bool end=false) {
    for (int i = 0; i < level; ++i)
        std::cout << "\t";
    std::cout << "[" << scope << "]\t" << msg;
    if (end) std::cout << std::endl;
}

inline void level_msg(const char *msg, int level=0, bool end=false) {
    for (int i = 0; i < level; ++i)
        std::cout << "\t";
    std::cout << msg;
    if (end) std::cout << std::endl;
}

#endif //F2_UTIL_H
