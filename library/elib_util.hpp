/*
// =====================================================================================
// 
//       Filename:  elib_util.hpp
// 
//    Description:  elwin library utility tools
// 
//        Version:  1.0
//        Created:  07/04/2013 11:45:39 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Elwin.Gao (elwin), elwin.gao4444@gmail.com
//        Company:  
// 
// =====================================================================================
*/

#ifndef  _ELIB_UTIL_H_
#define  _ELIB_UTIL_H_

/* the C standrad library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <time.h>
#include <assert.h>
#include <stdarg.h>

/* the C++ standrad library */
#include <iostream>
#include <new>

/* GNU Linux library */
#include <unistd.h>
// #include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* ********************************************************* */

typedef unsigned char  byte;
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;

/* ********************************************************* */

#define   likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

/* log for debug */

#ifdef  SHOWLOG
#define log_printf(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define err_printf(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define sys_perror(prompt_str_) perror(prompt_str_)
#else      // -----  SHOWLOG  -----
#define log_printf(format, ...) ((void)0)
#define err_printf(format, ...) ((void)0)
#define sys_perror(prompt_str_) ((void)0)
#endif     // -----  not SHOWLOG  -----

/* atomic operation */

#define atom_add_and_fetch(ptr, val)  __sync_add_and_fetch((ptr), (val))
#define atom_sub_and_fetch(ptr, val)  __sync_sub_and_fetch((ptr), (val))
#define atom_and_and_fetch(ptr, val)  __sync_and_and_fetch((ptr), (val))
#define atom_xor_and_fetch(ptr, val)  __sync_xor_and_fetch((ptr), (val))
#define atom_or_and_fetch(ptr, val)   __sync_or_and_fetch((ptr), (val))
#define atom_nand_and_fetch(ptr, val) __sync_nand_and_fetch((ptr), (val))

#define atom_fetch_and_add(ptr, val)  __sync_fetch_and_add((ptr), (val))
#define atom_fetch_and_sub(ptr, val)  __sync_fetch_and_sub((ptr), (val))
#define atom_fetch_and_and(ptr, val)  __sync_fetch_and_and((ptr), (val))
#define atom_fetch_and_xor(ptr, val)  __sync_fetch_and_xor((ptr), (val))
#define atom_fetch_and_or(ptr, val)   __sync_fetch_and_or((ptr), (val))
#define atom_fetch_and_nand(ptr, val) __sync_fetch_and_nand((ptr), (val))

#define atom_cas(ptr, oldval, newval)         __sync_bool_compare_and_swap((ptr), (oldval), (newval))
#define atom_cas_get_old(ptr, oldval, newval) __sync_val_compare_and_swap((ptr), (oldval), (newval))

/* memory barrier */
#define barrier() __asm__ __volatile__("": : :"memory") 

#ifdef __x86_64__
#define mb()	asm volatile("mfence":::"memory")   
#define rmb()	asm volatile("lfence":::"memory")   
#define wmb()	asm volatile("sfence":::"memory")
#endif

#ifdef CONFIG_SMP
#define smp_bm() mb()
#define smp_rbm() rmb()
#define smp_wbm() wmb()
#endif

/* always inline */
// #define __always_inline__ __attribute__((always_inline))

// =====================================================================================
//  Description:  全局函数
// =====================================================================================

#endif   // ----- #ifndef _ELIB_UTIL_H_  -----

