#include "chefe.hpp"

void Chefe::setNome(string name)
{
    nome = name;
}
string Chefe::getNome()
{
    return nome;
}
void Chefe::setValorHora(float v)
{
    valorHora = v;
}
void Chefe::setQtdHoraTrabalhada(float v)
{
    qtdHoraTrabalhada = v;
}
float Chefe::getValorHora()
{
    return valorHora;
}
float Chefe::getQtdHoraTrabalhada()
{
    return qtdHoraTrabalhada;
}
Chefe::Chefe(string n, string s, string name, float val, float qtd)
{
    setLogin(n);
    setSenha(s);
    setNome(name);
    setQtdHoraTrabalhada(qtd);
    setValorHora(val);
};

ostream &operator<<(ostream &out, Chefe &chefe)
{
    out << chefe.getLogin() << endl;
    out << chefe.getSenha() << endl;
    out << chefe.nome << endl;
    out << chefe.qtdHoraTrabalhada << endl;
    out << chefe.valorHora;
    return out;
}
