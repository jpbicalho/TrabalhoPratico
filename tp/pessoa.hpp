#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Pessoa
{
private:
    string login, senha;

public:
    void setLogin(string);
    void setSenha(string);
    string getLogin();
    string getSenha();
    Pessoa(string = "", string = "");
    virtual ~Pessoa(){};
    friend ostream &operator<<(ostream &out, Pessoa &pessoa);
};

#endif
