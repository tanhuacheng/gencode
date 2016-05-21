/*
*********************************************************************************************************
* 文件: types.h
* 版本: V1.00
* 创建: Sat May 21 17:44:55 2016
* 作者: 谭化成
* 描述: 定义平台无关的基本数据类型, 应根据不同平台作适当修改
*
* 版本历史
* +----------------------------------------------------------------------------------------------------+
* |    时间    |  版本  |                              描 述                              |    作者    |
* +----------------------------------------------------------------------------------------------------+
* | 2016/05/21 |  1.00  | 定义平台无关的基本数据类型                                      |   谭化成   |
* +----------------------------------------------------------------------------------------------------+
*
*********************************************************************************************************
*/

#ifndef TYPES_H_
#define TYPES_H_

#ifdef __cplusplus
  extern "C" {
#endif

typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef unsigned long long uint64_t;
typedef signed long long int64_t;

typedef float fp32_t;
typedef double fp64_t;

#ifndef BOOL
#define BOOL uint32_t
#endif

#ifndef TRUE
#define TRUE (1u)
#endif

#ifndef FALSE
#define FALSE (0u)
#endif

#ifdef __cplusplus
  }
#endif

#endif /* TYPES_H_ */
/********************************************* end of file *********************************************/

