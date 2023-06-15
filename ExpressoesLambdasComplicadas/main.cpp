#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

/**
 * @brief The Lambda class
 */
template <typename FunctorType>
class LambdaExp {
public:
    /**
         * @brief Lambda
         * @param functor
         */
    LambdaExp(const FunctorType& functor)
        : m_functor(functor)
    {
    }

    /**
         * @brief operator ()
         * @param value
         * @return
         */
    template <typename ValueType>
    std::invoke_result_t<FunctorType, ValueType> operator()(const ValueType& value) const
    {
        return m_functor(value);
    }

    /**
         * @brief operator []
         * @param value
         */
    auto operator[](const auto& value)
    {
        return [value](const auto& otherValue) {
            return otherValue[value];
        };
    }

private:
    FunctorType m_functor;
};

// Necessary to avoid -> 'x' cannot be capture because it does not have automatic storage duration
auto autoStorageDuration = [](const auto& value) {
    return value;
};
LambdaExp x { autoStorageDuration };

/**
 * @brief operator <<
 * @param ostreamObj
 * @param operation
 */
template <typename T>
auto operator<<(std::ostream& ostreamObj, const LambdaExp<T>& operation)
{
    return LambdaExp { [&ostreamObj, operation](const auto& value) -> decltype(ostreamObj << operation(value)) {
        return ostreamObj << operation(value);
    } };
}

// Operator +
template <typename T1, typename T2>
auto operator+(const LambdaExp<T1>& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) + value2(value)) {
        return value1(value) + value2(value);
    } };
}

template <typename T1, typename T2>
auto operator+(const LambdaExp<T1>& value1, const T2& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) + value2) {
        return value1(value) + value2;
    } };
}

template <typename T1, typename T2>
auto operator+(const T1& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1 + value2(value)) {
        return value1 + value2(value);
    } };
}

// Operator -
template <typename T1, typename T2>
auto operator-(const LambdaExp<T1>& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) - value2(value)) {
        return value1(value) - value2(value);
    } };
}

template <typename T1, typename T2>
auto operator-(const LambdaExp<T1>& value1, const T2& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) - value2) {
        return value1(value) - value2;
    } };
}

template <typename T1, typename T2>
auto operator-(const T1& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1 - value2(value)) {
        return value1 - value2(value);
    } };
}

// Operator *
template <typename T1, typename T2>
auto operator*(const LambdaExp<T1>& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) * value2(value)) {
        return value1(value) * value2(value);
    } };
}

template <typename T1, typename T2>
auto operator*(const LambdaExp<T1>& value1, const T2& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) * value2) {
        return value1(value) * value2;
    } };
}

template <typename T1, typename T2>
auto operator*(const T1& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1 * value2(value)) {
        return value1 * value2(value);
    } };
}

// Operator /
template <typename T1, typename T2>
auto operator/(const LambdaExp<T1>& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) / value2(value)) {
        return value1(value) / value2(value);
    } };
}

template <typename T1, typename T2>
auto operator/(const LambdaExp<T1>& value1, const T2& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) / value2) {
        return value1(value) / value2;
    } };
}

template <typename T1, typename T2>
auto operator/(const T1& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1 / value2(value)) {
        return value1 / value2(value);
    } };
}

// Operator %
template <typename T1, typename T2>
auto operator%(const LambdaExp<T1>& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) % value2(value)) {
        return value1(value) % value2(value);
    } };
}

template <typename T1, typename T2>
auto operator%(const LambdaExp<T1>& value1, const T2& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) % value2) {
        return value1(value) % value2;
    } };
}

template <typename T1, typename T2>
auto operator%(const T1& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1 % value2(value)) {
        return value1 % value2(value);
    } };
}

// Operator ==
template <typename T1, typename T2>
auto operator==(const LambdaExp<T1>& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) == value2(value)) {
        return value1(value) == value2(value);
    } };
}

template <typename T1, typename T2>
auto operator==(const LambdaExp<T1>& value1, const T2& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) == value2) {
        return value1(value) == value2;
    } };
}

template <typename T1, typename T2>
auto operator==(const T1& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1 == value2(value)) {
        return value1 == value2(value);
    } };
}

// Operator !=
template <typename T1, typename T2>
auto operator!=(const LambdaExp<T1>& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) != value2(value)) {
        return value1(value) != value2(value);
    } };
}

template <typename T1, typename T2>
auto operator!=(const LambdaExp<T1>& value1, const T2& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) != value2) {
        return value1(value) != value2;
    } };
}

template <typename T1, typename T2>
auto operator!=(const T1& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1 != value2(value)) {
        return value1 != value2(value);
    } };
}

// Operator <<
template <typename T1, typename T2>
auto operator<<(const LambdaExp<T1>& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) << value2(value)) {
        return value1(value) << value2(value);
    } };
}

template <typename T1, typename T2>
auto operator<<(const LambdaExp<T1>& value1, const T2& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1(value) << value2) {
        return value1(value) << value2;
    } };
}

template <typename T1, typename T2>
auto operator<<(const T1& value1, const LambdaExp<T2>& value2)
{
    return LambdaExp { [value1, value2](const auto& value) -> decltype(value1 << value2(value)) {
        return value1 << value2(value);
    } };
}

/**
 * @brief operator != Caso onde pode ocorrer x[0] != 0
 * @param value1
 * @param value2
 */
template <typename T1, typename T2>
auto operator!=(const T1& value1, const T2& value2)
{
    return LambdaExp { [value1, value2](const auto& value) {
        return value1(value) != value2;
    } };
}

/**
 * @brief operator | Caso genérico ao de cima
 * @param a
 * @param b
 */
template <typename T1, typename T2>
auto operator|(const LambdaExp<T1>& lambdaExpr1, const LambdaExp<T2>& lambdaExpr2)
{
    return LambdaExp { [lambdaExpr1, lambdaExpr2](const auto& value) {
        lambdaExpr1(value) | lambdaExpr2;
    } };
}

/**
 * @brief operator |
 * @param iterable
 * @param function
 */
template <typename Iterable, typename FunctorType>
auto operator|(const Iterable& iterable, const FunctorType& function)
{

    // Boolean
    if constexpr (std::is_same_v<void, std::invoke_result_t<FunctorType, decltype(*std::begin(iterable))>> || std::is_reference_v<std::invoke_result_t<FunctorType, decltype(*std::begin(iterable))>>) {
        for (const auto& value : iterable) {
            invoke(function, value);
        }
    }

    // Void
    else if constexpr (std::is_same_v<bool, std::invoke_result_t<FunctorType, decltype(*std::begin(iterable))>>) {

        std::vector<std::decay_t<decltype(*begin(iterable))>> vector;

        for (const auto& value : iterable) {
            if (invoke(function, value)) {
                vector.push_back(value);
            }
        }

        return vector;
    }

    // Somewhat more (could be const and should use decay)
    else {
        std::vector<std::decay_t<std::invoke_result_t<FunctorType, decltype(*std::begin(iterable))>>> vector;
        for (const auto& value : iterable) {
            vector.push_back(invoke(function, value));
        }

        return vector;
    }
}
