#include "safe_stl_general.hpp"

namespace saber
{

static FILE *fp = stdin;

FILE *& fp_export(void)
{
    return fp;
}

void set_export(FILE *_fp)
{
    fp_export() = _fp;
}

void stl_panic(const char *_description)
{
    std::fprintf(fp_export(),
                 "safe-STL panic called because : %s \n",
                 _description);
    std::abort();
}

void stl_warning(const char *_description)
{
#ifdef SAFE_STL_ENABLE_WARNING
    std::fprintf(fp_export(),
                 "safe-STL warning called because : %s \n",
                 _description);
#endif
}

}
