#ifndef ERR_H
#define ERR_H

#include <stdio.h>
#include "err_def.h"

#define LOG(errno) do{ \
	const char* str = error_to_str(errno); \
	printf("[%s:%d] Errno: %s\n", __FILE__, __LINE__, str); \
}while(0)

typedef enum {
  EXCEPTION_MODULE,
} module_enum_t;

// error code begin

typedef enum {
    Arithmetic = ERR_CODE_BEGIN(EXCEPTION_MODULE),
    NullPointer,
    IndexOutofBounds,
    NoEnoughMemory,
    InvalidParameter,
    InvalidOperation
} exception_enum_t;

// error code end

const char* error_to_str(err_t errno);

#endif