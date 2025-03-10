// ======================================================================
//  MyClass.h
// ======================================================================
//                   This file is a part of the book 
//             "Qt 5.10 Professional programming with C++"
//                       http://qt-book.com
// ======================================================================
//  Copyright (c) 2017 by Max Schlee
// ======================================================================

#pragma once

// ======================================================================
class MyClass {
public:
    int min(int n1, int n2)
    {
        return n1 < n2 ? n1 : n2;
    }

    int max(int n1, int n2)
    {
        return n1 > n2 ? n1 : n2;
    }
};

