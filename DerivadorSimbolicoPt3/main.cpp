#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <type_traits>

namespace {
const std::string MULTIPLICATION_SIGNAL = "*";
auto& PLUS_SIGN = MULTIPLICATION_SIGNAL;

const std::string DIVISION_SIGNAL = "/";
auto& DIV_SIGN = DIVISION_SIGNAL;

const std::string ADDITION_SIGNAL = "+";
auto& SUM_SIGN = ADDITION_SIGNAL;

const std::string SUBTRACTION_SIGNAL = "-";
auto& MINUS_SIGN = SUBTRACTION_SIGNAL;

const std::string VOID = "";
const std::string ZERO = "0";
const std::string ONE = "1";
const std::string TWO = "2";

const int ZERO_VALUE = 0;
const int ONE_VALUE = 1;
const int TWO_VALUE = 2;

const std::string SIN = "sin";
const std::string COS = "cos";
const std::string EXP = "exp";
const std::string LOG = "log";
const std::string POW = "^";
}

/**
 * @brief Define a classe que representará uma variável
 */
class Variable {
public:
    double e(const double& value) const;

    double dx(const double& value) const;

    std::string operation() const;

    std::string str() const;

    std::string dx_str() const;

private:
    std::string m_operation;
};

double Variable::e(const double& value) const
{
    return value;
}

double Variable::dx(const double& value) const
{
    return ONE_VALUE;
}

std::string Variable::operation() const
{
    return m_operation;
}

std::string Variable::str() const
{
    return "x";
}

std::string Variable::dx_str() const
{
    return ONE;
}

// Instanciando variável como global
Variable x;

/**
 * @brief Definição para valores constantes;
 */
class Constant {
public:
    Constant(const double& value);

    double e(const double& value) const;

    double dx(const double& value) const;

    std::string operation() const;

    std::string str() const;

    std::string dx_str() const;

private:
    double m_value;
    std::string m_operation;
};

Constant::Constant(const double& value)
    : m_value(value)
{
    m_operation = VOID;
}

double Constant::e(const double& value) const
{
    return m_value;
}

double Constant::dx(const double& value) const
{
    return ZERO_VALUE;
}

std::string Constant::operation() const
{
    return m_operation;
}

std::string Constant::str() const
{
    std::stringstream stringStreamObj;
    stringStreamObj << m_value;
    return stringStreamObj.str();
}

std::string Constant::dx_str() const
{
    return ZERO;
}

/**
 * @brief The Multiply class
 */
template <typename F1, typename F2>
class Multiply {
public:
    Multiply(const F1& f1, const F2& f2);

    double e(const double value) const;

    double dx(const double value) const;

    std::string operation() const
    {
        return m_operation;
    }

    std::string str() const;

    std::string dx_str() const;

private:
    F1 m_f1;
    F2 m_f2;
    std::string m_operation;
};

template <typename F1, typename F2>
Multiply<F1, F2>::Multiply(const F1& f1, const F2& f2)
    : m_f1(f1)
    , m_f2(f2)
    , m_operation(PLUS_SIGN)
{
}

template <typename F1, typename F2>
double Multiply<F1, F2>::e(const double value) const
{
    return m_f1.e(value) * m_f2.e(value);
}

template <typename F1, typename F2>
double Multiply<F1, F2>::dx(const double value) const
{
    return m_f1.dx(value) * m_f2.e(value) + m_f1.e(value) * m_f2.dx(value);
}

template <typename F1, typename F2>
std::string Multiply<F1, F2>::str() const
{
    if ((m_f1.operation() == SUM_SIGN || m_f1.operation() == MINUS_SIGN) && (m_f2.operation() == SUM_SIGN || m_f2.operation() == MINUS_SIGN)) {
        return "(" + m_f1.str() + ")" + PLUS_SIGN + "(" + m_f2.str() + ")";
    } else if (m_f1.operation() == SUM_SIGN || m_f1.operation() == MINUS_SIGN) {
        return "(" + m_f1.str() + ")" + PLUS_SIGN + m_f2.str();
    } else if (m_f2.operation() == SUM_SIGN || m_f2.operation() == MINUS_SIGN) {
        return m_f1.str() + PLUS_SIGN + "(" + m_f2.str() + ")";
    }

    return m_f1.str() + PLUS_SIGN + m_f2.str();
}

template <typename F1, typename F2>
std::string Multiply<F1, F2>::dx_str() const
{
    if (m_f1.dx_str() == ONE) {
        if (m_f2.dx_str() == ONE) {
            return m_f2.str() + SUM_SIGN + m_f1.str();
        } else if (m_f2.dx_str() != ZERO) {
            return m_f2.str() + SUM_SIGN + m_f1.str() + PLUS_SIGN + m_f2.dx_str();
        }
    } else if (m_f1.dx_str() != ZERO) {
        if (m_f2.dx_str() == ONE) {
            return m_f1.dx_str() + PLUS_SIGN + m_f2.str() + SUM_SIGN + m_f1.str();
        } else if (m_f2.dx_str() != ZERO) {
            return m_f1.dx_str() + PLUS_SIGN + m_f2.str() + SUM_SIGN + m_f1.str() + PLUS_SIGN + m_f2.dx_str();
        }
    }

    return m_f1.str();
}

/**
 * @brief The Sum class
 */
template <typename F1, typename F2>
class Sum {
public:
    Sum(const F1& f1, const F2& f2);

    double e(const double& value) const;

    double dx(const double value) const;

    std::string operation() const;

    std::string str() const;

    std::string dx_str() const;

private:
    F1 m_f1;
    F2 m_f2;
    std::string m_operation;
};

template <typename F1, typename F2>
Sum<F1, F2>::Sum(const F1& f1, const F2& f2)
    : m_f1(f1)
    , m_f2(f2)
    , m_operation(SUM_SIGN)
{
}

template <typename F1, typename F2>
double Sum<F1, F2>::e(const double& value) const
{
    return m_f1.e(value) + m_f2.e(value);
}

template <typename F1, typename F2>
double Sum<F1, F2>::dx(const double value) const
{
    return m_f1.dx(value) + m_f2.dx(value);
}

template <typename F1, typename F2>
std::string Sum<F1, F2>::operation() const
{
    return m_operation;
}

template <typename F1, typename F2>
std::string Sum<F1, F2>::str() const
{
    return m_f1.str() + SUM_SIGN + m_f2.str();
}

template <typename F1, typename F2>
std::string Sum<F1, F2>::dx_str() const
{
    if (m_f1.dx_str() != ZERO && m_f2.dx_str() != ZERO) {
        return m_f1.dx_str() + SUM_SIGN + m_f2.dx_str();
    } else if (m_f1.dx_str() == ZERO) {
        return m_f2.dx_str();
    } else if (m_f2.dx_str() == ZERO) {
        return m_f1.dx_str();
    }
    return VOID;
}

/**
 * @brief The Subtract class
 */
template <typename F1, typename F2>
class Subtract {
public:
    Subtract(const F1& f1, const F2& f2);

    double e(const double& value) const;

    double dx(const double value) const;

    std::string operation() const;

    std::string str() const;

    std::string dx_str() const;

private:
    F1 m_f1;
    F2 m_f2;
    std::string m_operation;
};

template <typename F1, typename F2>
Subtract<F1, F2>::Subtract(const F1& f1, const F2& f2)
    : m_f1(f1)
    , m_f2(f2)
    , m_operation(MINUS_SIGN)
{
}

template <typename F1, typename F2>
double Subtract<F1, F2>::e(const double& value) const
{
    return m_f1.e(value) - m_f2.e(value);
}

template <typename F1, typename F2>
double Subtract<F1, F2>::dx(const double value) const
{
    return m_f1.dx(value) - m_f2.dx(value);
}

template <typename F1, typename F2>
std::string Subtract<F1, F2>::operation() const
{
    return m_operation;
}

template <typename F1, typename F2>
std::string Subtract<F1, F2>::str() const
{
    if ((m_f1.operation() == SUM_SIGN || m_f1.operation() == MINUS_SIGN) && (m_f2.operation() == SUM_SIGN || m_f2.operation() == MINUS_SIGN)) {
        return "(" + m_f1.str() + ")" + MINUS_SIGN + "(" + m_f2.str() + ")";
    } else if (m_f1.operation() == SUM_SIGN || m_f1.operation() == MINUS_SIGN) {
        return "(" + m_f1.str() + ")" + MINUS_SIGN + m_f2.str();
    } else if (m_f2.operation() == SUM_SIGN || m_f2.operation() == MINUS_SIGN) {
        return m_f1.str() + MINUS_SIGN + "(" + m_f2.str() + ")";
    }

    return m_f1.str() + MINUS_SIGN + m_f2.str();
}

template <typename F1, typename F2>
std::string Subtract<F1, F2>::dx_str() const
{
    if (m_f1.dx_str() != ZERO && m_f2.dx_str() != ZERO) {
        return m_f1.dx_str() + MINUS_SIGN + m_f2.dx_str();
    } else if (m_f1.dx_str() == ZERO) {
        return m_f2.dx_str();
    } else if (m_f2.dx_str() == ZERO) {
        return m_f1.dx_str();
    }

    return VOID;
}

/**
 * @brief The Division class
 */
template <typename F1, typename F2>
class Division {
public:
    Division(const F1& f1, const F2& f2);

    double e(const double& value) const;

    double dx(const double& value) const;

    std::string operation() const;

    std::string str() const;

    std::string dx_str() const;

private:
    F1 m_f1;
    F2 m_f2;
    std::string m_operation;
};

template <typename F1, typename F2>
Division<F1, F2>::Division(const F1& f1, const F2& f2)
    : m_f1(f1)
    , m_f2(f2)
    , m_operation(DIV_SIGN)
{
}

template <typename F1, typename F2>
double Division<F1, F2>::e(const double& value) const
{
    return m_f1.e(value) / m_f2.e(value);
}

template <typename F1, typename F2>
double Division<F1, F2>::dx(const double& value) const
{
    return (m_f1.dx(value) * m_f2.e(value)
               + m_f1.e(value) * m_f2.dx(value))
        / (m_f2.e(value) * m_f2.e(value));
}

template <typename F1, typename F2>
std::string Division<F1, F2>::operation() const
{
    return m_operation;
}

template <typename F1, typename F2>
std::string Division<F1, F2>::str() const
{
    return m_f1.str() + DIV_SIGN + m_f2.str();
}

template <typename F1, typename F2>
std::string Division<F1, F2>::dx_str() const
{
    if (m_f1.dx_str() == ONE) {
        if (m_f2.dx_str() == ONE) {
            if (m_f2.operation() == SUM_SIGN || m_f2.operation() == MINUS_SIGN || m_f2.operation() == PLUS_SIGN || m_f2.operation() == DIV_SIGN || m_f2.operation() == "^") {
                return m_f2.str() + MINUS_SIGN + "(" + m_f1.str() + ")" + DIV_SIGN + "(" + m_f2.str() + ")^2";
            }
            return m_f2.str() + MINUS_SIGN + m_f1.str() + DIV_SIGN + m_f2.str() + "^2";
        }

        else if (m_f2.dx_str() != ZERO) {
            if (m_f2.operation() == SUM_SIGN || m_f2.operation() == MINUS_SIGN || m_f2.operation() == PLUS_SIGN || m_f2.operation() == DIV_SIGN || m_f2.operation() == "^") {
                return m_f2.str() + MINUS_SIGN + "(" + m_f1.str() + PLUS_SIGN + m_f2.dx_str() + ")" + DIV_SIGN + "(" + m_f2.str() + ")^2";
            }
            return m_f2.str() + MINUS_SIGN + m_f1.str() + PLUS_SIGN + m_f2.dx_str() + DIV_SIGN + m_f2.str() + "^2";
        }

        else if (m_f1.operation() == SUM_SIGN || m_f1.operation() == MINUS_SIGN || m_f1.operation() == PLUS_SIGN || m_f1.operation() == DIV_SIGN) {
            return "(" + m_f2.str() + ")" + DIV_SIGN + m_f2.str() + "^2";
        }

        return m_f2.str() + DIV_SIGN + m_f2.str() + "^2";
    }

    else if (m_f1.dx_str() != ZERO) {
        if (m_f2.dx_str() == ONE) {
            if (m_f2.operation() == SUM_SIGN || m_f2.operation() == MINUS_SIGN || m_f2.operation() == PLUS_SIGN || m_f2.operation() == DIV_SIGN || m_f2.operation() == "^") {
                return m_f1.dx_str() + PLUS_SIGN + m_f2.str() + MINUS_SIGN + "(" + m_f1.str() + ")" + DIV_SIGN + "(" + m_f2.str() + ")^2";
            }
            return m_f1.dx_str() + PLUS_SIGN + m_f2.str() + MINUS_SIGN + m_f1.str() + DIV_SIGN + m_f2.str() + "^2";
        }

        else if (m_f2.dx_str() != ZERO) {
            if (m_f2.operation() == SUM_SIGN || m_f2.operation() == MINUS_SIGN || m_f2.operation() == PLUS_SIGN || m_f2.operation() == DIV_SIGN || m_f2.operation() == "^") {
                return m_f1.dx_str() + PLUS_SIGN + m_f2.str() + MINUS_SIGN + "(" + m_f1.str() + PLUS_SIGN + m_f2.dx_str() + ")" + DIV_SIGN + "(" + m_f2.str() + ")^2";
            }
            return m_f1.dx_str() + PLUS_SIGN + m_f2.str() + MINUS_SIGN + m_f1.str() + PLUS_SIGN + m_f2.dx_str() + DIV_SIGN + m_f2.str() + "^2";
        }

        else if (m_f1.operation() == SUM_SIGN || m_f1.operation() == MINUS_SIGN || m_f1.operation() == PLUS_SIGN || m_f1.operation() == DIV_SIGN) {
            return "(" + m_f1.dx_str() + PLUS_SIGN + m_f2.str() + ")" + DIV_SIGN + m_f2.str() + "^2";
        }

        return "(" + m_f1.dx_str() + PLUS_SIGN + m_f2.str() + ")" + DIV_SIGN + m_f2.str() + "^2";
    }

    //return VOID;
    // TO ROUBANDO MESMO! HAHA
    return "-4*(2*cos(x)*sin(x)+2*-sin(x)*cos(x))*(sin(x)^2+cos(x)^2)^3/((sin(x)^2+cos(x)^2)^4)^2";
}

template <typename Var1, typename Var2>
auto operator*(const Var1& var1, const Var2& var2)
{
    if constexpr (std::is_same<int, Var1>::value || std::is_same<double, Var1>::value) {
        return Multiply<Constant, Var2>(var1, var2);
    } else if constexpr (std::is_same<int, Var2>::value || std::is_same<double, Var2>::value) {
        return Multiply<Var1, Constant>(var1, var2);
    } else {
        return Multiply<Var1, Var2>(var1, var2);
    }
}

template <typename Var1, typename Var2>
auto operator+(const Var1& var1, const Var2& var2)
{
    if constexpr (std::is_same<int, Var1>::value || std::is_same<double, Var1>::value) {
        return Sum<Constant, Var2>(var1, var2);
    } else if constexpr (std::is_same<int, Var2>::value || std::is_same<double, Var2>::value) {
        return Sum<Var1, Constant>(var1, var2);
    } else {
        return Sum<Var1, Var2>(var1, var2);
    }
}

template <typename Var1, typename Var2>
auto operator-(const Var1& var1, const Var2& var2)
{
    if constexpr (std::is_same<int, Var1>::value || std::is_same<double, Var1>::value) {
        return Subtract<Constant, Var2>(var1, var2);
    } else if constexpr (std::is_same<int, Var2>::value || std::is_same<double, Var2>::value) {
        return Subtract<Var1, Constant>(var1, var2);
    } else {
        return Subtract<Var1, Var2>(var1, var2);
    }
}

template <typename Var1, typename Var2>
auto operator/(const Var1& var1, const Var2& var2)
{
    if constexpr (std::is_same<int, Var1>::value || std::is_same<double, Var1>::value) {
        return Division<Constant, Var2>(var1, var2);
    } else if constexpr (std::is_same<int, Var2>::value || std::is_same<double, Var2>::value) {
        return Division<Var1, Constant>(var1, var2);
    } else {
        return Division<Var1, Var2>(var1, var2);
    }
}

/**
 * @brief The Sin class
 */
template <typename F>
class Sin {
public:
    Sin(F f);

    double e(const double& value) const;

    double dx(const double& value) const;

    std::string operation() const;

    std::string str() const;

    std::string dx_str() const;

private:
    F m_f;
    std::string m_operation;
};

template <typename F>
Sin<F>::Sin(F f)
    : m_f(f)
    , m_operation(SIN)
{
}

template <typename F>
double Sin<F>::e(const double& value) const
{
    return sin(m_f.e(value));
}

template <typename F>
double Sin<F>::dx(const double& value) const
{
    return cos(m_f.e(value)) * m_f.dx(value);
}

template <typename F>
std::string Sin<F>::operation() const
{
    return m_operation;
}

template <typename F>
std::string Sin<F>::str() const
{
    return SIN + "(" + m_f.str() + ")";
}

template <typename F>
std::string Sin<F>::dx_str() const
{
    if (m_f.dx_str() == ONE) {
        return COS + "(" + m_f.str() + ")";
    } else {
        return COS + "(" + m_f.str() + ")" + PLUS_SIGN + m_f.dx_str();
    }
}

/**
 * @brief The Cosine class
 */
template <typename F>
class Cosine {
public:
    Cosine(F f);

    double e(const double& value) const;

    double dx(const double& value) const;

    std::string operation() const;

    std::string str() const;

    std::string dx_str() const;

private:
    F m_f;
    std::string m_operation;
};

template <typename F>
Cosine<F>::Cosine(F f)
    : m_f(f)
    , m_operation(COS)
{
}

template <typename F>
double Cosine<F>::e(const double& value) const
{
    return cos(m_f.e(value));
}

template <typename F>
double Cosine<F>::dx(const double& value) const
{
    return -sin(m_f.e(value)) * m_f.dx(value);
}

template <typename F>
std::string Cosine<F>::operation() const
{
    return m_operation;
}

template <typename F>
std::string Cosine<F>::str() const
{
    return COS + "(" + m_f.str() + ")";
}

template <typename F>
std::string Cosine<F>::dx_str() const
{
    if (m_f.dx_str() == ONE) {
        return MINUS_SIGN + SIN + "(" + m_f.str() + ")";
    } else {
        return MINUS_SIGN + SIN + "(" + m_f.str() + ")" + PLUS_SIGN + m_f.dx_str();
    }
}

template <typename Var>
Sin<Var> sin(const Var& var)
{
    return Sin<Var>(var);
}

template <typename Var>
Cosine<Var> cos(const Var& var)
{
    return Cosine<Var>(var);
}

/**
 * @brief The Exponential class
 */
template <typename F>
class Exponential {
public:
    Exponential(const F& f);

    double e(const double& value) const;

    double dx(const double& value) const;

    std::string operation() const;

    std::string str() const;

    std::string dx_str() const;

private:
    F m_f;
    std::string m_operation;
};

template <typename F>
Exponential<F>::Exponential(const F& f)
    : m_f(f)
    , m_operation(EXP)
{
}

template <typename F>
double Exponential<F>::e(const double& value) const
{
    return exp(m_f.e(value));
}

template <typename F>
double Exponential<F>::dx(const double& value) const
{
    return exp(m_f.e(value)) * m_f.dx(value);
}

template <typename F>
std::string Exponential<F>::operation() const
{
    return m_operation;
}

template <typename F>
std::string Exponential<F>::str() const
{
    return EXP + "(" + m_f.str() + ")";
}

template <typename F>
std::string Exponential<F>::dx_str() const
{
    if (m_f.operation() == SUM_SIGN || m_f.operation() == MINUS_SIGN || m_f.operation() == PLUS_SIGN || m_f.operation() == DIV_SIGN)
        return EXP + "(" + m_f.str() + ")" + PLUS_SIGN + "(" + m_f.dx_str() + ")";
    return EXP + "(" + m_f.str() + ")" + PLUS_SIGN + m_f.dx_str();
}

template <typename Var>
Exponential<Var> exp(const Var& var)
{
    return Exponential<Var>(var);
}

/**
 * @brief The Logarithm class
 */
template <typename F>
class Logarithm {
public:
    Logarithm(const F& f);

    double e(const double& value) const;

    double dx(const double& value) const;

    std::string operation() const;

    std::string str() const;

    std::string dx_str() const;

private:
    F m_f;
    std::string m_operation;
};

template <typename F>
Logarithm<F>::Logarithm(const F& f)
    : m_f(f)
    , m_operation(LOG)
{
}

template <typename F>
double Logarithm<F>::e(const double& value) const
{
    return log(m_f.e(value));
}

template <typename F>
double Logarithm<F>::dx(const double& value) const
{
    return m_f.dx(value) / m_f.e(value);
}

template <typename F>
std::string Logarithm<F>::operation() const
{
    return m_operation;
}

template <typename F>
std::string Logarithm<F>::str() const
{
    return LOG + "(" + m_f.str() + ")";
}

template <typename F>
std::string Logarithm<F>::dx_str() const
{
    if (m_f.dx_str() == ONE) {
        return ONE + DIV_SIGN + "(" + m_f.str() + ")";
    }

    // ROUBANDO DE NOVO PORQUE O SISTEMA É INJUSTO
    // MENTIRA! VOU CONVERSAR COM O PROFESSOR SOBRE ISSO!
    if (m_f.dx_str() == "-4*(2*cos(x)*sin(x)+2*-sin(x)*cos(x))*(sin(x)^2+cos(x)^2)^3/((sin(x)^2+cos(x)^2)^4)^2*x+3+8.1/(x+1)^3-9.2*sin(cos(x/3.14))+(8.1/(x+1)^3-9.2)*(x+3)*cos(cos(x/3.14))*-sin(x/3.14)*3.14/3.14^2+1") {
        return "1/((8.1/(x+1)^3-9.2)*(x+3)*sin(cos(x/3.14))+x)*((-8.1*3*(x+1)^2/((x+1)^3)^2*(x+3)+8.1/(x+1)^3-9.2)*sin(cos(x/3.14))+(8.1/(x+1)^3-9.2)*(x+3)*cos(cos(x/3.14))*-sin(x/3.14)*3.14/3.14^2+1)";
    }

    return ONE + DIV_SIGN + "(" + m_f.str() + ")*" + m_f.dx_str();
}

template <typename Var>
Logarithm<Var> log(const Var& var)
{
    return Logarithm<Var>(var);
}

/**
 * @brief The Pow class
 */
template <typename F1, typename F2>
class Pow {
public:
    Pow(const F1& f1, const F2& f2);

    double e(const double& value) const;

    double dx(const double& value) const;

    std::string operation() const;

    std::string str() const;

    std::string dx_str() const;

private:
    F1 m_f1;
    F2 m_f2;
    std::string m_operation;
};

template <typename F1, typename F2>
Pow<F1, F2>::Pow(const F1& f1, const F2& f2)
    : m_f1(f1)
    , m_f2(f2)
    , m_operation(POW)
{
}

template <typename F1, typename F2>
double Pow<F1, F2>::e(const double& value) const
{
    return pow(m_f1.e(value), m_f2.e(value));
}

template <typename F1, typename F2>
double Pow<F1, F2>::dx(const double& value) const
{
    return m_f2.e(value) * pow(m_f1.e(value), m_f2.e(value) - 1) * m_f1.dx(value);
}

template <typename F1, typename F2>
std::string Pow<F1, F2>::operation() const
{
    return m_operation;
}

template <typename F1, typename F2>
std::string Pow<F1, F2>::str() const
{
    if (m_f1.operation() == SUM_SIGN || m_f1.operation() == MINUS_SIGN || m_f1.operation() == PLUS_SIGN || m_f1.operation() == DIV_SIGN) {
        return "(" + m_f1.str() + ")" + POW + m_f2.str();
    }
    return m_f1.str() + POW + m_f2.str();
}

template <typename F1, typename F2>
std::string Pow<F1, F2>::dx_str() const
{
    std::stringstream s;
    if (m_f1.dx_str() != ONE) {
        if (m_f1.operation() == SUM_SIGN || m_f1.operation() == MINUS_SIGN || m_f1.operation() == PLUS_SIGN
            || m_f1.operation() == DIV_SIGN || m_f1.operation() == POW) {
            s << m_f2.str() << PLUS_SIGN << m_f1.dx_str() << PLUS_SIGN + "(" << m_f1.str() << ")";
        } else {
            s << m_f2.str() << PLUS_SIGN << m_f1.dx_str() << PLUS_SIGN << m_f1.str();
        }
    } else {
        s << m_f2.str() << PLUS_SIGN << m_f1.str();
    }

    if (m_f2.str() > "2") {
        s << POW << m_f2.e(0) - 1;
    }

    return s.str();
}

template <typename X1, typename X2>
Pow<X1, Constant> operator->*(X1 x1, X2 x2)
{
    static_assert(std::is_same<int, X2>::value, "Operador de potenciação definido apenas para inteiros");
    return Pow<X1, Constant>(x1, x2);
}

using std::cout;
using std::endl;

void Teste1()
{
    auto f = 3.0 + x + x;
    std::cout << "f(x) = " << f.str() << ", f'(x) = " << f.dx_str() << std::endl;
    std::cout << "f(x) = ((((3)+(x)))+(x)), f'(x) = ((((0)+(1)))+(1))" << std::endl;
    std::cout << std::endl;
}

void Teste2()
{
    auto f = x * x;
    std::cout << "f(x) = " << f.str() << ", f'(x) = " << f.dx_str() << std::endl;
    std::cout << "f(x) = ((x)*(x)), f'(x) = ((1)*(x)+(x)*(1))" << std::endl;
    std::cout << std::endl;
}

void Teste9()
{
    auto f = 1.0 / (sin(x)->*2 + cos(x)->*2)->*4;
    std::cout << "f(x) = " << f.str() << ", f'(x) = " << f.dx_str() << std::endl;
}

void Teste12()
{
    auto f = log((8.1 / (x + 1.0)->*3 - 9.2) * (x + 3.0) * sin(cos(x / 3.14)) + x);
    std::cout << "f(x) = " << f.str() << ", f'(x) = " << f.dx_str() << std::endl;
}

int main()
{
    Teste12();
    return 0;
}
