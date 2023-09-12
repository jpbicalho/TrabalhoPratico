#ifndef CHEFE_HPP
#define CHEFE_HPP

#include "pessoa.hpp"

class Chefe : public Pessoa
{
private:
    string nome;
    float valorHora, qtdHoraTrabalhada;

public:
    Chefe(string, string, string, float, float);
    void setNome(string);
    string getNome();
    void setValorHora(float);
    void setQtdHoraTrabalhada(float);
    float getValorHora();
    float getQtdHoraTrabalhada();
    friend ostream &operator<<(ostream &out, Chefe &chefe);
};

#endif