#ifndef FUNCIONARIO_HPP
#define FUNCIONARIO_HPP

#include "pessoa.hpp"
#include "horario.hpp"
#include <iostream>
#include "vendas.hpp"
using namespace std;
class Funcionario : public Pessoa
{
private:
    string nome;
    float salarioHora;
    vector<Horario> ponto, horasExtras, horaEntrada, horaSaida;
    vector<Vendas> vendasFeitas;

public:
    void setNome(string);
    void setSalarioHora(float);
    float getSalarioHora();
    string getNome();
    void setPonto(int, int, int);
    vector<Horario> getPonto();
    void setHorasExtras(int, int, int);
    vector<Horario> getHorasExtras();

    vector<Horario> getHoraEntrada();
    vector<Horario> getHoraSaida();
    void setHoraEntrada(int, int, int);
    void setHoraSaida(int, int, int);

    Funcionario();
    Funcionario(string, string, string, float);
    friend ostream &operator<<(ostream &out, Funcionario &func);
    Funcionario &operator=(Funcionario &);
    void NovaVenda(float, string);
    vector<Vendas> getVendas();
};

class Vendedor : public Funcionario
{
    friend class Supervisor; //amigas para que o supervisor tenha acesso as vendas do vendedor

public:
    Vendedor(string, string, string, float);
    friend ostream &operator<<(ostream &out, Vendedor &vend);
};

class Supervisor : public Funcionario
{
public:
    Supervisor(string, string, string, float);
    friend ostream &operator<<(ostream &out, Supervisor &sup);
};
#endif