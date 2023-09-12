#ifndef VENDAS_HPP
#define VENDAS_HPP

#include <string>
using namespace std;

class Vendas
{
private:
    float valor;
    string descricao;

public:
    void setValor(float);
    void setDescricao(string);
    float getValor();
    string getDescricao();
    Vendas();
    Vendas(string, float);
    friend ostream &operator<<(ostream &out, Vendas &venda);
    friend ostream &operator<<(ostream &out, const Vendas &venda);
    bool operator<(const Vendas& outra) const;
    bool operator>(const Vendas& outra) const;
    bool operator==(const Vendas& outra) const;
  
};

#endif