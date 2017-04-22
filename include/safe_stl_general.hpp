/* ************************************************************************* *
   
 * ************************************************************************* */

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
#include <cassert>

#define Q_UNUSED(_VARNAME) ((void)(_VARNAME))

namespace saber
{

using std::allocator_traits;
using std::iterator_traits;
using std::initializer_list;
using std::swap;

FILE*& fp_export(void);
void set_export(FILE* _fp);

#define stl_panic(_DESC) \
    {\
    std::fprintf(fp_export(), "At file %s, line %d\n", __FILE__, __LINE__);\
    std::fprintf(fp_export(), "STL panic called : %s\n", _DESC);\
    std::abort();\
    }

#ifdef SAFE_STL_ENABLE_WARNING
#   define stl_warning(_DESC)\
    {\
    std::fprintf(fp_export(), "At file %s, line %s\n", __FILE__, __LINE__);\
    std::fprintf(fp_export(), "STL warning called : %s\n", _DESC);\
    }
#else
#   define stl_warning(_DESC)
#endif

} // namespace saber

#endif // SAFE_STL_GENERAL_HPP
