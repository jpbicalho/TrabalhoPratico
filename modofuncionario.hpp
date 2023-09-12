#ifndef MODOFUNCIONARIO_HPP
#define MODOFUNCIONAIO_HPP

#include "pessoa.hpp"
#include "horario.hpp"
#include "vendas.hpp"

class ModoFuncionario
{
public:
    void menuFuncionarioPrincipal(vector<Pessoa *> &, int);
    void listarVendas(vector<Pessoa *>, int);
    void cadastraVenda(vector<Pessoa *> &, int);
    void calculaSalario(vector<Pessoa *> &, int);
    void cadastraPonto(vector<Pessoa *> &, int);
    int conferePontoSemanal(Pessoa *);
    vector<Horario> calculaPonto();
    void ordenaEPrintaVendas(vector<Vendas>,int);
    
};

void printaSalario(float,float,float,float);

#endif