#include "vector.hpp"

int main()
{
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.pop_back();
    vec.push_back(3);

    std::vector<int> another = vec;

    for (size_t i = 0; i < another.size(); i++)
    {
        std::printf("%d", another[i]);
    }

    return 0;
}
