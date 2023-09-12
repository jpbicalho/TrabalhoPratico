#ifndef MENU_HPP
#define MENU_HPP
#include "pessoa.hpp"
class Menu
{
private:
    int opcao;

public:
    int getOpcao();
    void setOpcao(int);
    Menu();
    void  menuInicial();
    void menuFuncionario(vector<Pessoa *> &);
    void menuGerente(vector<Pessoa *> &);
    int fazerLoginGerente(vector<Pessoa *>);
    int fazerLoginFuncionario(vector<Pessoa *>);
    vector<Pessoa *> contrutorMenu();
};

int recebeValor();
float recebeValorf();
#endif