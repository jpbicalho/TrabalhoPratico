#ifndef MODOGERENTE_HPP
#define MODOGERENTE_HPP
#include "pessoa.hpp"
class ModoGerente
{

public:
    void cadastrarFuncionario(vector<Pessoa *> &);
    void menuGerentePrincipal(vector<Pessoa *> &, int);
    void listarFuncionarios(vector<Pessoa *>);
    void checkPontoFuncionarios(vector<Pessoa *>);
    void mostraSalario(vector<Pessoa *>, int);
};

int confereCopia(vector<Pessoa *> &pessoas,string,string);
#endif