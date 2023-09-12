#include "vendas.hpp"
#include "pessoa.hpp"

void Vendas::setValor(float val)
{
    valor = val;
}
void Vendas::setDescricao(string descrip)
{
    descricao = descrip;
}
float Vendas::getValor()
{
    return valor;
}
string Vendas::getDescricao()
{
    return descricao;
}
Vendas::Vendas()
{
    valor = 0;
    descricao = "";
}
Vendas::Vendas(string descr, float val)
{
    setValor(val);
    setDescricao(descr);
}
ostream &operator<<(ostream &out, Vendas &venda)
{
    out << "R$" << venda.valor << endl;
    out << "Descricao:" << venda.descricao << endl;
    return out;
}
ostream &operator<<(ostream &out,const Vendas &venda){
    out << "R$" << venda.valor << endl;
    out << "Descricao:" << venda.descricao << endl;
    return out;
}
bool Vendas::operator<(const Vendas& outra) const {
  return valor < outra.valor;
}
bool Vendas::operator>(const Vendas& outra) const {
  return valor > outra.valor;
}

bool Vendas::operator==(const Vendas& outra) const{
    return descricao == outra.descricao;
}
