#include <algorithm>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

/**
 * @brief Classe functora para representar um intervalo.
 */
class Intervalo {

public:
    /**
     * @brief operator() Retorna um intervalo de inteiros baseado no início e fim.
     * @param begin início do intervalo
     * @param end fim do intervalo
     */
    auto operator()(const int& begin = 0, const int& end = 99)
    {
        std::vector<int> interval(end - begin);

        int i = begin;
        for (auto& element : interval) {
            element = i++;
        }
        return interval;
    }
};

/**
 * @brief Intervalo O mesmo que acima.
 * @param begin
 * @param end
 */
auto Intervalo(const int& begin = 0, const int& end = 99)
{
    std::vector<int> interval(end - begin);

    int i = begin;
    for (auto& element : interval) {
        element = i++;
    }
    return interval;
}

/**
 * @brief Classe functora para obter N primeiros elementos de um vetor
 */
class SliceBegin {

public:
    /**
     * @brief Construtor
     * @param size Tamanho da parte
     */
    SliceBegin(int size)
        : m_size(size)
    {
    }

    /**
     * @brief operator () Retorna N primeiros elementos
     * @param vetor
     */
    template <typename T>
    auto operator()(const std::vector<T>& vetor)
    {
        std::vector<T> data(m_size);
        for (int i = 0; i < m_size; ++i) {
            data[i] = vetor[i];
        }
        return data;
    }

private:
    int m_size;
};

typedef SliceBegin NPrimeiros;

/**
 * Retorna os elementos ímpares de um vetor
 */
auto Impares = []() {
    return [](const std::vector<int>& vetor) {
        std::vector<int> data;
        for (const auto element : vetor) {
            if (element % 2 == 0) {
                data.push_back(element);
            }
        }
        return data;
    };
};

/**
 * @brief operator | Stream
 * @param collection
 * @param function
 */
template <typename Collection, typename Function>
auto operator|(const Collection& collection, Function function)
{
    // Se for possível executar a função no primeiro elemento do vetor
    if constexpr (std::is_invocable<Function, decltype(*begin(collection))>::value) {

        // `function` retorna bool
        if constexpr (std::is_same<bool, std::invoke_result_t<Function, decltype(*begin(collection))>>::value) {
            std::vector<std::decay_t<decltype(*begin(collection))>> data;
            for (const auto& element : collection) {
                if (std::invoke(function, element)) {
                    data.push_back(element);
                }
            }
            return data;
        }

        // `function` retorna void
        else if constexpr (std::is_same<void, std::invoke_result_t<Function, decltype(*begin(collection))>>::value) {
            for (const auto& element : collection) {
                function(element);
            }
        }

        // `function` retorna outra coisa
        else {
            std::vector<std::decay_t<std::invoke_result_t<Function, decltype(*begin(collection))>>> data;
            for (const auto& element : collection) {
                data.push_back(std::invoke(function, element));
            }
            return data;
        }
    }

    else {
        std::vector<std::decay_t<decltype(*begin(collection))>> data(begin(collection), end(collection));
        return invoke(function, data);
    }
}

using std::cout;
using std::endl;

void test01()
{
    auto v = std::vector { 0, 2, 4, 6, 8, 10 };
    for (auto x : v | [](auto x) { return x + 1; })
        cout << x << ";";
}

void test02()
{
    Intervalo(9, 12) | [](auto x) { cout << x << " "; };
}

void test03()
{
    Intervalo(9, 20) | Impares() | [](auto x) { cout << x << " "; };
}

void test04()
{
    auto st = Intervalo(0) | Impares();
    int n = 5;
    for (auto x : st) {
        cout << x << " ";
        if (n-- == 0)
            break;
    }
}

void test05()
{
    auto filtro1 = [](int n) { return n % 3 == 0; };
    auto filtro2 = [](int n) { return n % 2 == 0; };
    auto st = Intervalo(0, 30) | filtro1 | filtro2;
    st | [](int x) { return x / 10.0; } | [](auto x) { cout << x << " "; };
}

void test06()
{
    auto filtro1 = [](int n) { return n % 3 == 0; };
    auto filtro2 = [](int n) { return n % 2 == 0; };
    auto st = Intervalo(0) | filtro1 | filtro2;
    st | SliceBegin(10) | [](int x) { return x / 10.0; } | [](auto x) { cout << x << ";"; };
}

void test07()
{
    auto toString = [](int n) { char buf[20]; sprintf( buf, "%d", n ); return std::string( buf ); };
    Intervalo(1, 7) | toString | [](auto x) { cout << x + "!"
                                                   << ";"; };
}

void test08()
{
    auto toString = [](int n) { char buf[20]; sprintf( buf, "%d", n ); return std::string( buf ); };
    std::vector<std::string> v;
    Intervalo(1) | Impares() | SliceBegin(10) | toString | [&v](auto x) { v.push_back(x); };
    v | [](auto x) { cout << x + "0"
                          << ";"; };
}

void test09()
{
    std::string st[] = { "a", "e", "i", "o", "u" };
    st | SliceBegin(3) | [](auto x) { cout << x + "!"
                                           << ";"; };
}

int main()
{
    test01();
    cout << endl;

    test02();
    cout << endl;

    test03();
    cout << endl;

    test04();
    cout << endl;

    test05();
    cout << endl;

    test06();
    cout << endl;

    test07();
    cout << endl;

    test08();
    cout << endl;

    test09();
    cout << endl;
    return 0;
}
