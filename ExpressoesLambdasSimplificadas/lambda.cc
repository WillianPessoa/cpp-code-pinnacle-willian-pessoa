#include <functional>
#include <string>
#include <type_traits>
#include <vector>

class Var {
public:
    template <typename K>
    K operator()(K v)
    {
        return v;
    }
};

Var x;

template <typename T>
class Cte {
public:
    Cte(const T& c)
        : c(c)
    {
    }

    template <typename K>
    T operator()(K v)
    {
        return c;
    }

private:
    T c;
};

template <typename F1>
class Sin {
public:
    Sin(F1 f1)
        : f1(f1)
    {
    }

    template <typename K>
    K operator()(K v)
    {
        return sin(f1(v));
    }

private:
    F1 f1;
};

template <typename F1>
Sin<F1> sin(F1 f1)
{
    if constexpr ((std::is_same_v<int, F1> || std::is_same_v<double, F1>)) {
        return Sin<Cte<F1>>(f1);
    }
    return Sin<F1>(f1);
}

template <typename F1>
class Cos {
public:
    Cos(F1 f1)
        : f1(f1)
    {
    }

    template <typename K>
    K operator()(K v)
    {
        return cos(f1(v));
    }

private:
    F1 f1;
};

template <typename F1>
Cos<F1> cos(F1 f1)
{
    if constexpr ((std::is_same_v<int, F1> || std::is_same_v<double, F1>)) {
        return Cos<Cte<F1>>(f1);
    }
    return Cos<F1>(f1);
}

template <typename F1>
class Exp {
public:
    Exp(F1 f1)
        : f1(f1)
    {
    }

    template <typename K>
    K operator()(K v)
    {
        return exp(f1(v));
    }

private:
    F1 f1;
};

template <typename F1>
Exp<F1> exp(F1 f1)
{
    if constexpr ((std::is_same_v<int, F1> || std::is_same_v<double, F1>)) {
        return Exp<Cte<F1>>(f1);
    }
    return Exp<F1>(f1);
}

template <typename F1>
class Log {
public:
    Log(F1 f1)
        : f1(f1)
    {
    }

    template <typename K>
    K operator()(K v)
    {
        return log(f1(v));
    }

private:
    F1 f1;
};

template <typename F1>
auto log(F1 f1)
{
    if constexpr ((std::is_same_v<int, F1> || std::is_same_v<double, F1>)) {
        return Log<Cte<F1>>(f1);
    }
    return Log<F1>(f1);
}

template <typename F1, typename F2>
class Soma {
public:
    Soma(F1 f1, F2 f2)
        : f1(f1)
        , f2(f2)
    {
    }

    template <typename K>
    K operator()(K v)
    {
        return f1(v) + f2(v);
    }

private:
    F1 f1;
    F2 f2;
};

template <typename F1, typename F2>
auto operator+(F1 f1, F2 f2)
{
    if constexpr ((std::is_same_v<int, F1> || std::is_same_v<double, F1>)&&(std::is_same_v<int, F2> || std::is_same_v<double, F2>)) {
        return Soma<Cte<F1>, Cte<F2>>(f1, f2);
    } else if constexpr ((std::is_same_v<int, F1> || std::is_same_v<double, F1>)&&(std::is_same_v<int, F2> || !std::is_same_v<double, F2>)) {
        return Soma<Cte<F1>, F2>(f1, f2);
    } else if constexpr (!(std::is_same_v<int, F1> || std::is_same_v<double, F1>)&&(std::is_same_v<int, F2> || std::is_same_v<double, F2>)) {
        return Soma<F1, Cte<F2>>(f1, f2);
    } else {
        return Soma<F1, F2>(f1, f2);
    }
}

template <typename F1, typename F2>
class Multiplica {
public:
    Multiplica(F1 f1, F2 f2)
        : f1(f1)
        , f2(f2)
    {
    }

    template <typename K>
    K operator()(K v)
    {
        return f1(v) * f2(v);
    }

private:
    F1 f1;
    F2 f2;
};

template <typename F1, typename F2>
auto operator*(F1 f1, F2 f2)
{
    if constexpr ((std::is_same_v<int, F1> || std::is_same_v<double, F1>)&&(std::is_same_v<int, F2> || std::is_same_v<double, F2>)) {
        return Multiplica<Cte<F1>, Cte<F2>>(f1, f2);
    } else if constexpr ((std::is_same_v<int, F1> || std::is_same_v<double, F1>)&&(std::is_same_v<int, F2> || !std::is_same_v<double, F2>)) {
        return Multiplica<Cte<F1>, F2>(f1, f2);
    } else if constexpr (!(std::is_same_v<int, F1> || std::is_same_v<double, F1>)&&(std::is_same_v<int, F2> || std::is_same_v<double, F2>)) {
        return Multiplica<F1, Cte<F2>>(f1, f2);
    } else {
        return Multiplica<F1, F2>(f1, f2);
    }
}

template <typename F1, typename F2>
class Modulo {
public:
    Modulo(F1 f1, F2 f2)
        : f1(f1)
        , f2(f2)
    {
    }

    template <typename K>
    K operator()(K v)
    {
        if constexpr ((std::is_same_v<int, F1> || std::is_same_v<double, F1>)&&(std::is_same_v<int, F2> || std::is_same_v<double, F2>)) {
            return f1 % f2;
        } else if constexpr (!(std::is_same_v<int, F1> || std::is_same_v<double, F1>)&&(std::is_same_v<int, F2> || std::is_same_v<double, F2>)) {
            return f1(v) % f2;
        } else if constexpr ((std::is_same_v<int, F1> || std::is_same_v<double, F1>)&&!(std::is_same_v<int, F2> || std::is_same_v<double, F2>)) {
            return f1 % f2(v);
        } else {
            return f1(v) % f2(v);
        }
    }

private:
    F1 f1;
    F2 f2;
};

template <typename F1, typename F2>
Modulo<F1, F2> operator%(F1 f1, F2 f2)
{
    return Modulo<F1, F2>(f1, f2);
}

template <typename F1, typename F2>
class Booleano {
public:
    Booleano(F1 f1, F2 f2)
        : f1(f1)
        , f2(f2)
    {
    }

    template <typename K>
    bool operator()(K v)
    {
        if constexpr ((std::is_same_v<int, F1> || std::is_same_v<double, F1>)&&(std::is_same_v<int, F2> || std::is_same_v<double, F2>)) {
            return (f1 == f2) ? true : false;
        } else if constexpr (!(std::is_same_v<int, F1> || std::is_same_v<double, F1>)&&(std::is_same_v<int, F2> || std::is_same_v<double, F2>)) {
            return (f1(v) == f2) ? true : false;
        } else if constexpr ((std::is_same_v<int, F1> || std::is_same_v<double, F1>)&&!(std::is_same_v<int, F2> || std::is_same_v<double, F2>)) {
            return (f1 == f2(v)) ? true : false;
        } else {
            return (f1(v) == f2(v)) ? true : false;
        }
    }

private:
    F1 f1;
    F2 f2;
};

template <typename F1, typename F2>
Booleano<F1, F2> operator==(F1 f1, F2 f2)
{
    return Booleano<F1, F2>(f1, f2);
}

template <typename T, typename F>
auto operator|(const T& iterable, F function)
{
    if constexpr (std::is_same_v<bool, std::invoke_result_t<F, decltype(*begin(iterable))>>) {
        std::vector<std::decay_t<decltype(*begin(iterable))>> result;

        for (auto element : iterable)
            if (std::invoke(function, element))
                result.push_back(element);

        return result;
    } else if constexpr (std::is_same_v<void, std::invoke_result_t<F, decltype(*begin(iterable))>>) {
        for (auto element : iterable)
            std::invoke(function, element);
    } else {
        std::vector<std::decay_t<std::invoke_result_t<F, decltype(*begin(iterable))>>> result;

        for (auto element : iterable)
            result.push_back(std::invoke(function, element));

        return result;
    }
}

template <typename F1, typename F2>
class Imprime {
public:
    std::string f3 = "";
    Imprime(F1& f1, F2 f2)
        : f1(f1)
        , f2(f2)
    {
    }

    template <typename K>
    void operator()(K v)
    {
        f1 << f2(v) << f3;
    }

private:
    F1& f1;
    F2 f2;
};

template <typename F1>
F1 operator<<(F1 f1, char f2)
{
    f1.f3 = f1.f3 + f2;
    return f1;
}

Imprime<std::ostream, Var> operator<<(std::ostream& o, Var f1)
{
    return Imprime<std::ostream, Var>(o, f1);
}

template <typename T1, typename T2>
Imprime<std::ostream, Soma<T1, T2>> operator<<(std::ostream& o, Soma<T1, T2> f1)
{
    return Imprime<std::ostream, Soma<T1, T2>>(o, f1);
}

template <typename T1, typename T2>
Imprime<std::ostream, Multiplica<T1, T2>> operator<<(std::ostream& o, Multiplica<T1, T2> f1)
{
    return Imprime<std::ostream, Multiplica<T1, T2>>(o, f1);
}
