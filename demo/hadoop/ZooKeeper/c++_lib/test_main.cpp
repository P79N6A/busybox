/*
// =====================================================================================
// 
//       Filename:  test_main.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/12/2016 05:40:24 PM
//       Revision:  All Rights Reserved
//       Compiler:  g++
// 
//         Author:  gaowei08@baidu.com
//        Company:  Baidu.com, Inc.
// 
// =====================================================================================
*/

#include <cstdlib>
#include <iostream>

#include <gtest/gtest.h>

/* 
// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  
// =====================================================================================
*/
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}                // ----------  end of function main  ----------

