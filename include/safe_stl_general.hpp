// //////////////////////////////////////////////////////////////////////// //

//    藕花香 染檐牙                                                         //
//    惹那诗人 纵步随她                                                     //
//    佩声微 琴声儿退                                                       //
//    斗胆了一池眉叶丹砂                                                    //

//    画船开 心随她                                                         //
//    谁不作美 偏起风沙                                                     //
//    倚蓬窗 月色轻晃                                                       //
//    偶闻得渔翁一席话                                                      //

//    试问                                                                  //
//    多一份情又怎地                                                        //
//    站在别人的雨季                                                        //
//    淋湿自己 空弹一出戏                                                   //
//    空望他 功成名就又怎地                                                 //
//    豆腐换成金羽衣                                                        //
//    岂不知你已在画里                                                      //

//    多一份情又怎地                                                        //
//    站在别人的雨季                                                        //
//    淋湿自己 空弹一出戏                                                   //
//    空望他 功成名就又怎地                                                 //
//    豆腐换成金羽衣                                                        //
//    岂不知你已在画里                                                      //

//    这一搭 莲蓬子落地 几回迷                                              //

// //////////////////////////////////////////////////////////////////////// //

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
    std::fprintf(fp_export(), "At file %s, line %d\n", __FILE__, __LINE__);\
    std::fprintf(fp_export(), "STL warning called : %s\n", _DESC);\
    }
#else
#   define stl_warning(_DESC)
#endif

} // namespace saber

#endif // SAFE_STL_GENERAL_HPP
