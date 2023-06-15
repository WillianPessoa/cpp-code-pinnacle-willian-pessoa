#include <iostream>
#include <memory>

using namespace std;

class AbstractPair
{
  public:
    virtual void imprime(ostream& o) {

    }

  private:
};

template <typename A, typename B>
class PairImpl : public AbstractPair
{
public:
    PairImpl(A &a, B &b):
        m_a(a),
        m_b(b)
    {

    }

    A first() const
    {
        return m_a;
    }

    B second() const
    {
        return m_b;
    }

    virtual void imprime(ostream& o)
    {
        o << m_a << " = " << m_b << std::endl;
    }

private:
    A m_a;
    B m_b;

};

class Pair {
public:
  template <typename A, typename B>
  Pair(A a, B b ):
      p(std::shared_ptr<AbstractPair>(new PairImpl<A, B>(a, b)))
  {
  }

  ~Pair() {
      ;
  }

  void imprime(ostream& o) const
  {
      p->imprime(o);
  }
private:
  std::shared_ptr<AbstractPair> p;
};

void print( ostream& o, const initializer_list<Pair> &lista ) {
    for (const auto &p: lista) {
        p.imprime(o);
    }
}

int n_leak;

class Leak {
public:
    Leak () {
        n = n_leak++;
        cout << "Criou: " << n << endl;
    }
    Leak (const Leak& l) {
        n = n_leak++;
        cout << "Criou: " << n << " copiando de " << l.n << endl;
    }
    ~Leak () {
        cout << "Destruiu: " << n << endl;
    }

    int n;
};

ostream& operator<<(ostream& o, const Leak& l)
{
    o << "lk(" << l.n << ")";
    return o;
}

int main()
{
    print( cout, { { "jan", Leak() }, { string( "pi" ), Leak() } } );
    return 0;
}
