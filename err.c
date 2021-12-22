#include <stdbool.h>
#include "err.h"

// generate begin
static struct error_str_t
{
	bool exist;
	int last_error;
	const char ** error_array;
}s_error_str_array[1];

static const char* s_exception_enum_t_err_str[] = {
	"Arithmetic",
	"NullPointer",
	"IndexOutofBounds",
	"NoEnoughMemory",
	"InvalidParameter",
	"InvalidOperation",
};

void error_str_init()
{
	s_error_str_array[EXCEPTION_MODULE].exist = true;
	s_error_str_array[EXCEPTION_MODULE].last_error = 5;
	s_error_str_array[EXCEPTION_MODULE].error_array = s_exception_enum_t_err_str;
}

const char* error_to_str(err_t errno)
{
	static bool initialized = false;
	unsigned short error_code = ERR_GET_ERROR_INDEX(errno);
	unsigned short module_id = ERR_GET_MODULE_ID(errno);
	if(!initialized)
	{
		error_str_init();
		initialized = true;
	}
	if(errno > 0)
		return "Errno should less than 0";
	if(!s_error_str_array[module_id].exist)
		return "Error code array isn't exist";
	if(s_error_str_array[module_id].last_error < error_code)
		return "Error code out of range";
	return s_error_str_array[module_id].error_array[error_code];
}
// generate end
