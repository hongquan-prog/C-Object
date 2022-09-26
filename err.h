#ifndef ERR_H
#define ERR_H

#include "err_def.h"

#define ENABLE_GLOBAL_DEBUG 1

#define LOG(errno, info)                                                \
  do                                                                    \
  {                                                                     \
    const char *str = error_to_str(errno);                              \
    printf("[%s:%d] Errno: %s: %s\n", __FILE__, __LINE__, str, info);   \
  } while (0)

#if ((1 == ENABLE_GLOBAL_DEBUG))
#define DEBUG_ASSERT(p)                                                      \
  {                                                                          \
    if (!(p))                                                                \
    {                                                                        \
      LOG(ERR_CONSTRUCT(ConditionDropped), "please check conditions! \r\n"); \
      while (1)                                                              \
        ;                                                                    \
    }                                                                        \
  }
#define DEBUG_PRINT(code, format, ...) LOG(ERR_CONSTRUCT(code), format, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(code, format, ...)
#define DEBUG_ASSERT(p) \
  {                    \
    while (!(p))       \
      ;                \
  }
#endif

typedef enum
{
  EXCEPTION_MODULE,
} module_enum_t;

// error code begin

typedef enum
{
  Arithmetic = ERR_CODE_BEGIN(EXCEPTION_MODULE),
  NullPointer,
  IndexOutofBounds,
  NoEnoughMemory,
  InvalidParameter,
  ConditionDropped
} exception_enum_t;

// error code end

const char *error_to_str(err_t errno);

#endif