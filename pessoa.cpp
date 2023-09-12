#include "pessoa.hpp"

void Pessoa::setLogin(string nome)
{
    login = nome;
};
void Pessoa::setSenha(string nome)
{
    senha = nome;
};
string Pessoa::getLogin()
{
    return login;
};
string Pessoa::getSenha()
{
    return senha;
};
Pessoa::Pessoa(string n, string s)
{
    setLogin(n);
    setSenha(s);
};

ostream &operator<<(ostream &out, Pessoa &pessoa)
{
    out << pessoa.login;
    out << "\n";
    out << pessoa.senha;
    return out;
}