#include <iostream>
#include <list>
#include <iterator>
#include <future>
#include <thread>
#include <algorithm>

int function(int value)
{
    return value + 1;
}

template<typename F_e, typename Func>

void par(F_e first, F_e last, Func f)
{
    unsigned int const length = std::distance(first, last);

    if (!length)
    {
        return;
    }

    unsigned int const min_thread = 25;

    if (length < (2 * min_thread))
    {
        std::for_each(first, last, f);
    }
    else
    {
        F_e const mid = first + length / 2;
        std::future<void> first_half = std::async(&par <F_e, Func>, first, mid, f);
        std::future<void> last_half = std::async(&par <F_e, Func>, mid, last, f);
        first_half.get();
        last_half.get();

    }

}

void print(std::vector<int>& v)
{
    for (const auto& element : v)
        std::cout << element << " ";
    std::cout << std::endl;
}

int main()
{
    std::vector<int> v { 5, 8, 15, 6, 1, 19, 3 };
    
    print(v);
    int a = 0;

    par(v.begin(), v.end(), [](int a) {std::cout << function(a) << " ";});


}

