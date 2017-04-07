#include "vector.hpp"

class Trace
{
public:
    Trace() { std::printf("Trace() at %p\n", this); }
    Trace(const Trace&) { std::printf("Trace(const Trace&) at %p\n", this); }
    ~Trace() {std::printf("~Trace() at %p\n", this);}
};

int main()
{
    // test case 1

    {
        std::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.pop_back();
        vec.push_back(3);

        std::vector<int> another = vec;
        std::vector<int> that;

        that = vec;

        for (size_t i = 0; i < another.size(); i++)
        {
            std::printf("%d ", another[i]);
        }
        std::putchar('\n');

        for (size_t i = 0; i < that.size(); i++)
        {
            std::printf("%d ", another[i]);
        }
        std::putchar('\n');
    }

    // test case 2

    {
        std::vector<Trace> vec;
        vec.push_back(Trace());
        vec.push_back(Trace());

        std::vector<Trace> another = vec;
        std::vector<Trace> that;

        that = another;
    }

    // test case 3

    {
        std::vector<float> vec;
        vec.push_back(3);
        vec.push_back(4);

        for (auto it = vec.begin(); it != vec.end(); ++it)
        {
            std::printf("%f ", *it);
        }
        putchar('\n');

        for (auto &it : vec)
        {
            std::printf("%f ", it);
        }
        putchar('\n');
    }

    return 0;
}
