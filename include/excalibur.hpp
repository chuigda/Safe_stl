#ifdef _MSC_VER
#pragma once
#endif

#ifndef EXCALIBUR_HPP
#define EXCALIBUR_HPP

#include <cstdio>
#include <iostream>

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

template <typename InputIterator>
void
avalon(InputIterator _begin, InputIterator _end)
{
    for (;_begin != _end; ++_begin)
    {
        std::cout << *_begin << ' ';
    }
    std::cout << std::endl;
}

} // namespace saber

#endif // EXCALIBUR_HPP
