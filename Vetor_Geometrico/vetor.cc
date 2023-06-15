#include <initializer_list>
#include <iostream>
#include <vector>

using namespace std;

template<int n, typename T>
class Vetor {
public:
    class MeioDoProdutoVetorial {

    public:
        // Não consegui definir fora
        MeioDoProdutoVetorial operator,(T value) {
            *m_self = value;
            return *this;
        }

    private:
        MeioDoProdutoVetorial(Vetor<n,T> *vetor);
        friend class Vetor;

    private:
        Vetor<n,T> *m_self;
    };

public:

    void insere(T value);

    void print(std::ostream& o) const;

    Vetor<n,T> operator+(const Vetor<n,T> &rhs);

    Vetor<n,T> operator-(const Vetor<n,T> &vetor);

    T operator*(const Vetor<n,T> &vetor);

    Vetor<n,T> operator*(T scalar);

    Vetor<n,T> operator*(const MeioDoProdutoVetorial rhs);

    // Não consegui definir fora da classe
    MeioDoProdutoVetorial operator=(initializer_list<T> values) {
        for (T value: values) {
            m_data.push_back(value);
        }
    }

    MeioDoProdutoVetorial operator*() {
        return MeioDoProdutoVetorial(this);
    }

private:
    vector<T> m_data;
};

template<int n, typename T>
Vetor<n, T>::MeioDoProdutoVetorial::MeioDoProdutoVetorial(Vetor<n, T> *v):
    m_self(v)
{

}

template<int n, typename T>
void Vetor<n, T>::insere(T value)
{
    m_data.push_back(value);
}

template<int n, typename T>
void Vetor<n, T>::print(ostream &o) const
{
    for (auto value: m_data) {
        o << value << " ";
    }
}

template<int n, typename T>
Vetor<n, T> Vetor<n, T>::operator+(const Vetor<n, T> &rhs)
{
   Vetor<n,T> temp;
   for (size_t i = 0; i < n; ++i) {
       temp.m_data.push_back(m_data[i] + rhs.m_data[i]);
   }
   return temp;
}

template<int n, typename T>
Vetor<n, T> Vetor<n, T>::operator-(const Vetor<n, T> &rhs)
{
    Vetor<n,T> temp;
    for (size_t i = 0; i < n; ++i) {
        temp.m_data.push_back(m_data[i] - rhs.m_data[i]);
    }
    return temp;
}

template<int n, typename T>
T Vetor<n, T>::operator*(const Vetor<n, T> &rhs)
{
    T product = 0;
    for (size_t i = 0; i < n; ++i) {
        product += m_data[i] * rhs.m_data[i];
    }
    return product;
}

template<int n, typename T>
Vetor<n,T> Vetor<n, T>::operator*(T scalar)
{
    Vetor<n,T> temp;
    for (size_t i = 0; i < n; ++i) {
        temp.m_data.push_back(m_data[i] * scalar);
    }
    return temp;
}

template<int n, typename T>
Vetor<n,T> Vetor<n, T>::operator*(const Vetor<n, T>::MeioDoProdutoVetorial rhs)
{
    Vetor<n,T> temp;

    if (n == 2) {
        temp.m_data.push_back(0);
        temp.m_data.push_back(0);
    } else if (n == 3) {
        temp.m_data.push_back(m_data[1] * (rhs.m_self)->m_data[2] - m_data[2] * (rhs.m_self)->m_data[1]);
        temp.m_data.push_back(m_data[2] * (rhs.m_self)->m_data[0] - m_data[0] * (rhs.m_self)->m_data[2]);
    }

    temp.insere(m_data[0] * (rhs.m_self)->m_data[1] - m_data[1] * (rhs.m_self)->m_data[0]);

    return temp;
}

// Especializações necessárias para o caso de teste na main()
template<int n, typename T>
ostream& operator <<(ostream& o, Vetor<n,T> rhs)
{
    rhs.print(o);
    return o;
}

template<int n, typename T>
Vetor<n,T> operator *(T escalar, Vetor<n,T> rhs)
{
    return rhs * escalar;
}
