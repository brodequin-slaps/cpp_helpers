#include <iostream>

namespace Geranim0
{
    //variadic reduce
    template<typename Op, typename T, typename U>
    U reduce(Op op, U init, T first)
    {
        return op(init, first);
    }
    //variadic reduce
    template<typename Op, typename T, typename U, typename... Args>
    U reduce(Op op, U init, T first, Args... args)
    {
        init = op(init, first);
        return reduce(op, init, args...);
    }

    //Applies func to all the ptrs 'ts' if they are all valid ptrs
    template<typename... Ts, typename Fn>
    void with(Fn func, Ts*... ts)
    {
        if (reduce([](bool init, auto* ptr)
            {
                return init && (ptr != nullptr);
            }, true, ts...))
        {
            func(ts...);
        }
        else
        {
            std::cout << "Cannot call withs: invalid pointers" << std::endl;
        }
    }

    //variadic foreach
    template<typename Fn, typename T>
    void foreach_variadic(Fn fn, T t)
    {
        fn(t);
    }
    //variadic foreach
    template<typename Fn, typename First, typename... Ts>
    void foreach_variadic(Fn fn, First first, Ts... ts)
    {
        fn(first);
        foreach_variadic(fn, ts...);
    }
}