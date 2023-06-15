#include <iostream>
#include <type_traits>
#include <vector>

template<typename Iterable, typename Function>
auto operator | (const Iterable &iterable, Function function) {

    // Aplica - Método
    if constexpr (std::is_member_function_pointer_v<decltype(function)>) {

        std::vector<decltype(((*std::begin(iterable)).*function)())> v;

        for (auto itr : iterable) {
            v.push_back(((itr).*function)());
        }

        return v;

    }

    // Aplica - Função
    else if constexpr (std::is_same_v<void, decltype(function(*(std::begin(iterable))))>) {
        for (auto itr : iterable) {
            function(itr);
        }
    }

    // Filtra
    else if constexpr (std::is_same_v<bool, decltype(function(*(std::begin(iterable))))>) {

        // Inválido?
        //vector<decltype(*(begin(iterable)))> v;

        // Válido
        auto itr = *(std::begin(iterable));
        std::vector<decltype(itr)> v;

        // Aplica somente nos válidos
        for (auto itr : iterable)
            if (function(itr)) {
                v.push_back(itr);
            }

        return v;

    }

    // Aplica e retorna
    else {
        std::vector<decltype(function(*begin(iterable)))> v;

        for (auto itr : iterable) {
            v.push_back(function(itr));
        }

        return v;
    }
}

using namespace std;

int main() {
    vector<string> v1 = { "janeiro", "fevereiro", "março", "abril", "maio" };
    v1 | &string::length | [] ( int x ) { cout << x << " "; };
    return 0;
}
