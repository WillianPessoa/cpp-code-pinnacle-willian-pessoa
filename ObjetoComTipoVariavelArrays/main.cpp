#ifndef VAR_CC
#define VAR_CC

#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <type_traits>

class Var {
public:
    /**
     * @brief Var
     */
    Var();

    /**
     * @brief Var
     * @param value
     */
    Var(const int& value);

    /**
     * @brief Var
     * @param value
     */
    Var(const double& value);

    /**
     * @brief Var
     * @param value
     */
    Var(const bool& value);

    /**
     * @brief Var
     * @param value
     */
    Var(const std::string& value);

    /**
     * @brief Var
     * @param value
     */
    Var(const char* value);

    /**
     * @brief Var
     * @param value
     */
    Var(const char& value);

    /**
     * @brief operator =
     * @param value
     * @return
     */
    Var operator=(const bool& value);

    /**
     * @brief operator =
     * @param value
     * @return
     */
    Var operator=(const int& value);

    /**
     * @brief operator =
     * @param value
     * @return
     */
    Var operator=(const double& value);

    /**
     * @brief operator =
     * @param value
     * @return
     */
    Var operator=(const std::string& value);

    /**
     * @brief operator =
     * @param value
     * @return
     */
    Var operator=(const char* value);

    /**
     * @brief operator =
     * @param var
     * @return
     */
    Var& operator=(const Var& var);

    /**
     * @brief operator +
     * @param rhs
     * @return
     */
    Var operator+(const Var& rhs) const;

    /**
     * @brief operator -
     * @param rhs
     * @return
     */
    Var operator-(const Var& rhs) const;

    /**
     * @brief operator *
     * @param rhs
     * @return
     */
    Var operator*(const Var& rhs) const;

    /**
     * @brief operator /
     * @param rhs
     * @return
     */
    Var operator/(const Var& rhs) const;

    /**
     * @brief operator &&
     * @param rhs
     * @return
     */
    Var operator&&(const Var& rhs) const;

    /**
     * @brief operator ||
     * @param rhs
     * @return
     */
    Var operator||(const Var& rhs) const;

    /**
     * @brief operator !
     * @return
     */
    Var operator!() const;

    /**
     * @brief operator <
     * @param rhs
     * @return
     */
    Var operator<(const Var& rhs) const;

    /**
     * @brief operator []
     * @param str
     * @return
     */
    Var& operator[](const std::string& str) const;

    /**
     * @brief operator []
     * @param ch
     * @return
     */
    Var& operator[](const char* ch) const;

    /**
     * @brief operator ()
     * @param var
     * @return
     */
    Var operator()(const Var& var) const;

    /**
     * @brief imprime
     * @param o
     */
    void imprime(std::ostream& o) const;

    /**
     * @brief The Undefined class
     */
    class Undefined {
    public:
        /**
         * @brief operator <
         * @param rhs
         * @return
         */
        virtual Var operator<(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief operator !
         * @return
         */
        virtual Var operator!() const;
        ;

        /**
         * @brief operator +
         * @param rhs
         * @return
         */
        virtual Var operator+(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief operator -
         * @param rhs
         * @return
         */
        virtual Var operator-(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief operator *
         * @param rhs
         * @return
         */
        virtual Var operator*(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief operator /
         * @param rhs
         * @return
         */
        virtual Var operator/(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief operator &&
         * @param rhs
         * @return
         */
        virtual Var operator&&(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief operator ||
         * @param rhs
         * @return
         */
        virtual Var operator||(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief operator []
         * @param str
         * @return
         */
        virtual Var& operator[](const std::string& str);

        /**
         * @brief imprime
         * @param o
         */
        virtual void imprime(std::ostream& o) const;

        /**
         * @brief operator ()
         * @param var
         * @return
         */
        virtual Var operator()(const Var& var) const;

        /**
         * @brief operator <<
         * @param o
         * @return
         */
        std::ostream& operator<<(std::ostream& o);
    };

    /**
     * @brief The Boolean class
     */
    class Boolean : public Undefined {
    public:
        /**
         * @brief Boolean
         * @param val
         */
        Boolean(bool value);

        /**
         * @brief valor
         * @return
         */
        bool value();

        /**
         * @brief operator !
         * @return
         */
        Var operator!() const;
        ;

        /**
         * @brief operator <
         * @param oth
         * @return
         */
        Var operator<(const std::shared_ptr<Undefined> rhs) const;

        /**
         * @brief operator &&
         * @param oth
         * @return
         */
        Var operator&&(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief operator ||
         * @param oth
         * @return
         */
        Var operator||(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief imprime
         * @param o
         */
        void imprime(std::ostream& o) const;

    private:
        bool m_value;
    };

    /**
     * @brief The Int class
     */
    class Int : public Undefined {
    public:
        /**
         * @brief Int
         * @param val
         */
        Int(int value);
        /**
         * @brief valor
         * @return
         */
        int value();

        /**
         * @brief operator <
         * @param oth
         * @return
         */
        Var operator<(const std::shared_ptr<Undefined> rhs) const;

        /**
         * @brief operator +
         * @param oth
         * @return
         */
        Var operator+(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief operator -
         * @param oth
         * @return
         */
        Var operator-(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief operator *
         * @param oth
         * @return
         */
        Var operator*(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief operator /
         * @param oth
         * @return
         */
        Var operator/(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief imprime
         * @param o
         */
        void imprime(std::ostream& o) const;

    private:
        int m_value;
    };

    /**
     * @brief The Double class
     */
    class Double : public Undefined {
    public:
        /**
         * @brief Double
         * @param val
         */
        Double(double value);

        /**
         * @brief valor
         * @return
         */
        double value();

        /**
         * @brief operator <
         * @param oth
         * @return
         */
        Var operator<(const std::shared_ptr<Undefined> rhs) const;

        /**
         * @brief operator +
         * @param oth
         * @return
         */
        Var operator+(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief operator -
         * @param oth
         * @return
         */
        Var operator-(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief operator *
         * @param oth
         * @return
         */
        Var operator*(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief operator /
         * @param oth
         * @return
         */
        Var operator/(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief imprime
         * @param o
         */
        void imprime(std::ostream& o) const;

    private:
        double m_value;
    };

    /**
     * @brief The Char class
     */
    class Char : public Undefined {
    public:
        /**
         * @brief Char
         * @param val
         */
        Char(char value);

        /**
         * @brief valor
         * @return
         */
        char value();

        /**
         * @brief operator <
         * @param oth
         * @return
         */
        Var operator<(const std::shared_ptr<Undefined> rhs) const;

        /**
         * @brief operator +
         * @param oth
         * @return
         */
        Var operator+(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief imprime
         * @param o
         */
        void imprime(std::ostream& o) const;

    private:
        char m_value;
    };

    /**
     * @brief The String class
     */
    class String : public Undefined {
    public:
        /**
         * @brief String
         * @param val
         */
        String(std::string value);

        /**
         * @brief valor
         * @return
         */
        std::string value();

        /**
         * @brief operator <
         * @param oth
         * @return
         */
        Var operator<(const std::shared_ptr<Undefined> rhs) const;

        /**
         * @brief operator +
         * @param oth
         * @return
         */
        Var operator+(const std::shared_ptr<Undefined> rhs) const;
        ;

        /**
         * @brief imprime
         * @param o
         */
        void imprime(std::ostream& o) const;

    private:
        std::string m_value;
    };

    /**
     * @brief The Object class
     */
    class Object : public Undefined {
    public:
        /**
         * @brief operator []
         * @param s
         * @return
         */
        Var& operator[](const std::string& str);

        /**
         * @brief imprime
         * @param o
         */
        void imprime(std::ostream& o) const;

    private:
        std::map<std::string, Var> m_objects;
    };

    /**
     * @brief Var
     * @param o
     */
    Var(Object* o)
        : m_value(std::shared_ptr<Undefined>(o))
    {
    }

    /**
     * @brief operator =
     * @param o
     * @return
     */
    Var operator=(Object* o)
    {
        m_value = std::shared_ptr<Undefined>(o);
        return (*this);
    }

    /**
     * @brief The Function class
     */
    template <typename F>
    class Function : public Undefined {
    public:
        /**
         * @brief Function
         * @param _f
         */
        Function(F _f)
            : f(_f)
        {
        }

        /**
         * @brief operator ()
         * @param v
         * @return
         */
        Var operator()(const Var& v) const
        {
            return f(v);
        }

        /**
         * @brief imprime
         * @param o
         */
        void imprime(std::ostream& o) const
        {
            o << std::string("function");
        }

    private:
        F f;
    };

    /**
     * @brief Var
     * @param f
     */
    template <typename F>
    Var(F f)
        : m_value(std::shared_ptr<Function<F>>(new Function(f)))
    {
    }

    /**
     * @brief operator =
     * @param f
     * @return
     */
    template <typename F>
    Var operator=(F f)
    {
        m_value = std::shared_ptr<Undefined>(new Function(f));
        return (*this);
    }

    /**
     * @brief The Erro class
     */
    class Erro {
    public:
        /**
         * @brief Erro
         * @param msg
         */
        Erro(std::string msg)
            : msg(msg)
        {
        }

        /**
         * @brief operator ()
         * @return
         */
        std::string operator()() const
        {
            return msg;
        }

    private:
        std::string msg;
    };

private:
    std::shared_ptr<Undefined> m_value;
};

Var::Var()
    : m_value(new Undefined())
{
}

Var::Var(const int& value)
    : m_value(std::shared_ptr<Undefined>(new Int(value)))
{
}

Var::Var(const double& value)
    : m_value(std::shared_ptr<Undefined>(new Double(value)))
{
}

Var::Var(const bool& value)
    : m_value(std::shared_ptr<Undefined>(new Boolean(value)))
{
}

Var::Var(const std::string& value)
    : m_value(std::shared_ptr<Undefined>(new String(value)))
{
}

Var::Var(const char* value)
    : m_value(std::shared_ptr<Undefined>(new String(std::string(value))))
{
}

Var::Var(const char& value)
    : m_value(std::shared_ptr<Undefined>(new Char(value)))
{
}

Var Var::operator=(const bool& value)
{
    m_value = std::shared_ptr<Undefined>(new Boolean(value));
    return (*this);
}

Var Var::operator=(const int& value)
{
    m_value = std::shared_ptr<Undefined>(new Int(value));
    return (*this);
}

Var Var::operator=(const double& value)
{
    m_value = std::shared_ptr<Undefined>(new Double(value));
    return (*this);
}

Var Var::operator=(const std::string& value)
{
    m_value = std::shared_ptr<Undefined>(new String(value));
    return (*this);
}

Var Var::operator=(const char* value)
{
    m_value = std::shared_ptr<Undefined>(new String(std::string(value)));
    return (*this);
}

Var& Var::operator=(const Var& var)
{
    m_value = var.m_value;
    return (*this);
}

Var Var::operator+(const Var& rhs) const
{
    return (*m_value) + rhs.m_value;
}

Var Var::operator-(const Var& rhs) const
{
    return (*m_value) - rhs.m_value;
}

Var Var::operator*(const Var& rhs) const
{
    return (*m_value) * rhs.m_value;
}

Var Var::operator/(const Var& rhs) const
{
    return (*m_value) / rhs.m_value;
}

Var Var::operator&&(const Var& rhs) const
{
    return (*m_value) && rhs.m_value;
}

Var Var::operator||(const Var& rhs) const
{
    return (*m_value) || rhs.m_value;
}

Var Var::operator!() const
{
    return !(*m_value);
}

Var Var::operator<(const Var& rhs) const
{
    return *(m_value) < rhs.m_value;
}

Var& Var::operator[](const std::string& str) const
{
    return (*m_value)[str];
}

Var Var::operator()(const Var& var) const
{
    return (*m_value)(var);
}

void Var::imprime(std::ostream& o) const
{
    m_value->imprime(o);
}

Var& Var::operator[](const char* ch) const
{
    return operator[](std::string(ch));
}

/** ============================== Var::Undefined ======================================*/

Var Var::Undefined::operator<(const std::shared_ptr<Undefined> rhs) const
{
    Var var;
    return var;
}

Var Var::Undefined::operator!() const
{
    Var var;
    return var;
}

Var Var::Undefined::operator+(const std::shared_ptr<Undefined> rhs) const
{
    Var var;
    return var;
}

Var Var::Undefined::operator-(const std::shared_ptr<Undefined> rhs) const
{
    Var var;
    return var;
}

Var Var::Undefined::operator*(const std::shared_ptr<Undefined> rhs) const
{
    Var var;
    return var;
}

Var Var::Undefined::operator/(const std::shared_ptr<Undefined> rhs) const
{
    Var var;
    return var;
}

Var Var::Undefined::operator&&(const std::shared_ptr<Undefined> rhs) const
{
    Var var;
    return var;
}

Var Var::Undefined::operator||(const std::shared_ptr<Undefined> rhs) const
{
    Var var;
    return var;
}

Var& Var::Undefined::operator[](const std::string& str)
{
    throw Erro("Essa variável não é um objeto");
}

void Var::Undefined::imprime(std::ostream& o) const
{
    o << std::string("undefined");
}

Var Var::Undefined::operator()(const Var& var) const
{
    throw Erro("Essa variável não pode ser usada como função");
}

std::ostream& Var::Undefined::operator<<(std::ostream& o)
{
    (*this).imprime(o);
    return o;
}

// Var::Undefined

/** ============================== Var::Boolean ======================================*/
Var::Boolean::Boolean(bool value)
    : m_value(value)
{
}

bool Var::Boolean::value()
{
    return m_value;
}

Var Var::Boolean::operator!() const
{
    return !m_value;
}

Var Var::Boolean::operator<(const std::shared_ptr<Undefined> rhs) const
{
    auto temp = std::dynamic_pointer_cast<Boolean>(rhs);
    if (temp) {
        return m_value < temp->value();
    }
    return {};
}

Var Var::Boolean::operator&&(const std::shared_ptr<Undefined> rhs) const
{
    auto temp = std::dynamic_pointer_cast<Boolean>(rhs);
    if (temp) {
        return Var(m_value && temp->value());
    }
    return {};
}

Var Var::Boolean::operator||(const std::shared_ptr<Undefined> rhs) const
{
    auto temp = std::dynamic_pointer_cast<Boolean>(rhs);
    if (temp) {
        return Var(m_value || temp->value());
    }
    return {};
}

void Var::Boolean::imprime(std::ostream& o) const
{
    o << (m_value ? std::string("true") : std::string("false"));
}

// Var::Boolean

/** ============================== Var::Int ======================================*/

Var::Int::Int(int value)
    : m_value(value)
{
}

int Var::Int::value()
{
    return m_value;
}

Var Var::Int::operator<(const std::shared_ptr<Undefined> rhs) const
{
    auto tempInt = std::dynamic_pointer_cast<Int>(rhs);
    if (tempInt) {
        return m_value < tempInt->value();
    }

    auto tempDouble = std::dynamic_pointer_cast<Double>(rhs);
    if (tempDouble) {
        return m_value < tempDouble->value();
    }

    auto tempChar = std::dynamic_pointer_cast<Char>(rhs);
    if (tempChar) {
        return m_value < tempChar->value();
    }
    return {};
}

Var Var::Int::operator+(const std::shared_ptr<Undefined> rhs) const
{
    auto tempInt = std::dynamic_pointer_cast<Int>(rhs);
    if (tempInt) {
        return m_value + tempInt->value();
    }

    auto tempDouble = std::dynamic_pointer_cast<Double>(rhs);
    if (tempDouble) {
        return m_value + tempDouble->value();
    }

    return {};
}

Var Var::Int::operator-(const std::shared_ptr<Undefined> rhs) const
{
    auto tempInt = std::dynamic_pointer_cast<Int>(rhs);
    if (tempInt) {
        return m_value - tempInt->value();
    }

    auto tempDouble = std::dynamic_pointer_cast<Double>(rhs);
    if (tempDouble) {
        return m_value - tempDouble->value();
    }

    return {};
}

Var Var::Int::operator*(const std::shared_ptr<Undefined> rhs) const
{
    auto tempInt = std::dynamic_pointer_cast<Int>(rhs);
    if (tempInt) {
        return m_value * tempInt->value();
    }

    auto tempDouble = std::dynamic_pointer_cast<Double>(rhs);
    if (tempDouble) {
        return m_value * tempDouble->value();
    }

    return {};
}

Var Var::Int::operator/(const std::shared_ptr<Undefined> rhs) const
{
    auto tempInt = std::dynamic_pointer_cast<Int>(rhs);
    if (tempInt) {
        return m_value / tempInt->value();
    }

    auto tempDouble = std::dynamic_pointer_cast<Double>(rhs);
    if (tempDouble) {
        return m_value / tempDouble->value();
    }

    return {};
}

void Var::Int::imprime(std::ostream& o) const
{
    o << std::to_string(m_value);
}

// Var::Int

/** ============================== Var::Boolean ======================================*/

Var::Double::Double(double value)
    : m_value(value)
{
}

double Var::Double::value()
{
    return m_value;
}

Var Var::Double::operator<(const std::shared_ptr<Undefined> rhs) const
{
    auto tempDouble = std::dynamic_pointer_cast<Double>(rhs);
    if (tempDouble) {
        return m_value < tempDouble->value();
    }

    auto tempInt = std::dynamic_pointer_cast<Int>(rhs);
    if (tempInt) {
        return m_value < tempInt->value();
    }

    auto tempChar = std::dynamic_pointer_cast<Char>(rhs);
    if (tempChar) {
        return m_value < tempChar->value();
    }

    return {};
}

Var Var::Double::operator+(const std::shared_ptr<Undefined> rhs) const
{
    auto tempDouble = std::dynamic_pointer_cast<Double>(rhs);
    if (tempDouble) {
        return m_value + tempDouble->value();
    }

    auto tempInt = std::dynamic_pointer_cast<Int>(rhs);
    if (tempInt) {
        return m_value + tempInt->value();
    }

    return {};
}

Var Var::Double::operator-(const std::shared_ptr<Undefined> rhs) const
{
    auto tempDouble = std::dynamic_pointer_cast<Double>(rhs);
    if (tempDouble) {
        return m_value - tempDouble->value();
    }

    auto tempInt = std::dynamic_pointer_cast<Int>(rhs);
    if (tempInt) {
        return m_value - tempInt->value();
    }

    return {};
}

Var Var::Double::operator*(const std::shared_ptr<Undefined> rhs) const
{
    auto tempDouble = std::dynamic_pointer_cast<Double>(rhs);
    if (tempDouble) {
        return m_value * tempDouble->value();
    }

    auto tempInt = std::dynamic_pointer_cast<Int>(rhs);
    if (tempInt) {
        return m_value * tempInt->value();
    }

    return {};
}

Var Var::Double::operator/(const std::shared_ptr<Undefined> rhs) const
{
    auto tempDouble = std::dynamic_pointer_cast<Double>(rhs);
    if (tempDouble) {
        return m_value / tempDouble->value();
    }

    auto tempInt = std::dynamic_pointer_cast<Int>(rhs);
    if (tempInt) {
        return m_value / tempInt->value();
    }

    return {};
}

void Var::Double::imprime(std::ostream& o) const
{
    o << m_value;
}

// Var::Double

/** ============================== Var::Boolean ======================================*/

Var::Char::Char(char value)
    : m_value(value)
{
}

char Var::Char::value()
{
    return m_value;
}

Var Var::Char::operator<(const std::shared_ptr<Undefined> rhs) const
{
    auto tempChar = std::dynamic_pointer_cast<Char>(rhs);
    if (tempChar) {
        return m_value < tempChar->value();
    }
    auto tempInt = std::dynamic_pointer_cast<Int>(rhs);
    if (tempInt) {
        return m_value < tempInt->value();
    }
    auto tempDouble = std::dynamic_pointer_cast<Double>(rhs);
    if (tempDouble) {
        return m_value < tempDouble->value();
    }
    auto otherString = std::dynamic_pointer_cast<String>(rhs);
    if (otherString) {
        return std::string(1, m_value) < otherString->value();
    }
    return {};
}

Var Var::Char::operator+(const std::shared_ptr<Undefined> rhs) const
{
    auto tempChar = std::dynamic_pointer_cast<Char>(rhs);
    if (tempChar) {
        return std::string(1, m_value) + std::string(1, tempChar->value());
    }
    auto tempInt = std::dynamic_pointer_cast<Int>(rhs);
    if (tempInt) {
        return m_value + tempInt->value();
    }
    auto otherString = std::dynamic_pointer_cast<String>(rhs);
    if (otherString) {
        return m_value + otherString->value();
    }
    return {};
}

void Var::Char::imprime(std::ostream& o) const
{
    o << std::to_string(m_value);
}

// Var::Char

Var::String::String(std::string value)
    : m_value(value)
{
}

std::string Var::String::value()
{
    return m_value;
}

Var Var::String::operator<(const std::shared_ptr<Undefined> rhs) const
{
    auto otherString = std::dynamic_pointer_cast<String>(rhs);
    if (otherString) {
        return m_value < otherString->value();
    }
    auto tempChar = std::dynamic_pointer_cast<Char>(rhs);
    if (tempChar) {
        return m_value < std::string(1, tempChar->value());
    }
    return {};
}

Var Var::String::operator+(const std::shared_ptr<Undefined> rhs) const
{
    auto otherString = std::dynamic_pointer_cast<String>(rhs);
    if (otherString) {
        return Var(m_value + otherString->value());
    }
    auto tempChar = std::dynamic_pointer_cast<Char>(rhs);
    if (tempChar) {
        return Var(m_value + std::string(1, tempChar->value()));
    }
    return {};
}

void Var::String::imprime(std::ostream& o) const
{
    o << m_value;
}

/**
 * @brief newObject
 * @return
 */
Var::Object* newObject()
{
    return new Var::Object;
}

/**
 * @brief operator >
 * @param a
 * @param b
 * @return
 */
Var operator>(const Var& a, const Var& b)
{
    return b < a;
}

/**
 * @brief operator !=
 * @param a
 * @param b
 * @return
 */
Var operator!=(const Var& a, const Var& b)
{
    return (a < b) || (b < a);
}

/**
 * @brief operator ==
 * @param a
 * @param b
 * @return
 */
Var operator==(const Var& a, const Var& b)
{
    return !(a != b);
}

/**
 * @brief operator <=
 * @param a
 * @param b
 * @return
 */
Var operator<=(const Var& a, const Var& b)
{
    return !(b < a);
}

/**
 * @brief operator >=
 * @param a
 * @param b
 * @return
 */
Var operator>=(const Var& a, const Var& b)
{
    return !(a < b);
}

/**
 * @brief operator ==
 * @param a
 * @param b
 * @return
 */
template <typename T>

/**
 * @brief operator ==
 * @param a
 * @param b
 * @return
 */
Var operator==(T a, const Var& b)
{
    return Var(a) == b;
}

/**
 * @brief operator +
 * @param a
 * @param b
 * @return
 */
template <typename T>
Var operator+(T a, const Var& b)
{
    return Var(a) + b;
}

/**
 * @brief operator -
 * @param a
 * @param b
 * @return
 */
template <typename T>
Var operator-(T a, const Var& b)
{
    return Var(a) - b;
}

/**
 * @brief operator *
 * @param a
 * @param b
 * @return
 */
template <typename T>
Var operator*(T a, const Var& b)
{
    return Var(a) * b;
}

/**
 * @brief operator /
 * @param a
 * @param b
 * @return
 */
template <typename T>
Var operator/(T a, const Var& b)
{
    return Var(a) / b;
}

/**
 * @brief operator &&
 * @param a
 * @param b
 * @return
 */
template <typename T>
Var operator&&(T a, const Var& b)
{
    return Var(a) && b;
}

/**
 * @brief operator ||
 * @param a
 * @param b
 * @return
 */
template <typename T>
Var operator||(T a, const Var& b)
{
    return Var(a) || b;
}

/**
 * @brief operator <<
 * @param o
 * @param v
 * @return
 */
std::ostream& operator<<(std::ostream& o, const Var& v)
{
    v.imprime(o);
    return o;
}

#endif // VAR_CC

Var& Var::Object::operator[](const std::string& str)
{
    return m_objects[str];
}

void Var::Object::imprime(std::ostream& o) const
{
    o << std::string("object");
}
/***********************************************************************************************/
using std::cout;
using std::endl;

void test01()
{

    Var tab[] = { Var(), true, 10, '2', 0, '0', 'X', newObject(), "", "palavra", " 0 " };

    for (auto& a : tab)
        cout << "Valor=" << a << ":" << a.asString() << "," << a.asBool() << "," << !!a << "," << Var(a.isNumber()) << endl;
}

int main()
{
    test01();
    cout << endl;
    return 0;
}
