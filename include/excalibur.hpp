#ifdef _MSC_VER
#pragma once
#endif

#ifndef EXCALIBUR_HPP
#define EXCALIBUR_HPP

#include <cstdio>

namespace saber
{

template <typename T>
void
excalibur(const T* _t)
{
    for (size_t i = 0; i < sizeof(T); ++i)
    {
        if (i % 8 == 0)
        {
            std::putchar('\n');
        }

        std::printf("%02x ", (unsigned)
                            (*reinterpret_cast<unsigned char*>
                            (const_cast<T*>(_t + i))));
    }
    std::putchar('\n');
}

} // namespace saber

#endif // EXCALIBUR_HPP
