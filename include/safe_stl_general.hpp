#ifndef SAFE_STL_GENERAL_HPP
#define SAFE_STL_GENERAL_HPP

#define SAFE_STL_ENABLE_WARNING

#include <cstdio>
#include <cstdlib>
#include <new>
#include <ctime>
#include <utility>
#include <initializer_list>
#include <memory>
#include <limits>

#include "strings.defs.h"

namespace saber
{
using std::allocator_traits;

FILE*& fp_export(void);
void set_export(FILE* _fp);
void stl_panic(const char* _description);
void stl_warning(const char *_description);
}

#endif // SAFE_STL_GENERAL_HPP
