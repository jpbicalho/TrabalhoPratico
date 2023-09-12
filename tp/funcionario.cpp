#include "funcionario.hpp"
#include "pessoa.hpp"
#include "horario.hpp"
#include "vendas.hpp"
#include "menu.hpp"
void Funcionario::setNome(string n)
{
    nome = n;
};
void Funcionario::setSalarioHora(float f)
{
    salarioHora = f;
};

float Funcionario::getSalarioHora()
{
    return salarioHora;
};
string Funcionario::getNome()
{
    return nome;
}
Funcionario::Funcionario(string login, string senha, string name, float salario)
{

    setLogin(login);
    setSenha(senha);
    setNome(name);
    setSalarioHora(salario);
    ponto.resize(28);
    horasExtras.resize(28);
    horaEntrada.resize(28);
    horaSaida.resize(28);
}
Funcionario::Funcionario()
{
    setLogin("admin");
    setSenha("1234");
    setNome("name");
    ponto.resize(28);
    horasExtras.resize(28);
    setSalarioHora(0);
    horaEntrada.resize(28);
    horaSaida.resize(28);
}
ostream &operator<<(ostream &out, Funcionario &func)
{
    out << "NOME:\t" << func.nome << endl;
    out << "LOGIN:\t " << func.getLogin() << endl;
    out << "SENHA:\t " << func.getSenha() << endl;
    out << "\tR$" << func.salarioHora << " POR HORA" << endl;

    return out;
}
Vendedor::Vendedor(string login, string senha, string name, float salario) : Funcionario(login, senha, name, salario) {}

ostream &operator<<(ostream &out, Vendedor &vend)
{
    out << "NOME:\t" << vend.getNome() << endl;
    out << "LOGIN:\t" << vend.getLogin() << endl;
    out << "SENHA:\t" << vend.getSenha() << endl;
    out << "VALOR/HORA:\t"<<"R$" << vend.getSalarioHora() << " POR HORA" << endl;
    out << "CARGO:\tVENDEDOR ";

    return out;
}
Supervisor::Supervisor(string login, string senha, string name, float salario) : Funcionario(login, senha, name, salario) {}

ostream &operator<<(ostream &out, Supervisor &sup)
{
    out << "NOME:\t" << sup.getNome() << endl;
    out << "LOGIN:\t" << sup.getLogin() << endl;
    out << "SENHA:\t" << sup.getSenha() << endl;
    out << "VALOR/HORA:\t" <<"R$" << sup.getSalarioHora() << " POR HORA" << endl;
    out << "CARGO:\tSUPERVISOR ";

    return out;
}

void Funcionario::setPonto(int dia, int h, int m)
{
    Horario novo, extraTime;
    int newDate;

    if (dia < 0 || dia > 27)
    { // CONFERE A ENTRADA DOS DIAS
        do
        {
            cout << "\ndigite um valor valido para data:(1-28)\n";
            newDate=recebeValor()-1;
        } while (newDate < 0 || newDate > 28);
    }
    else
        newDate = dia;

    cout << "\nPONTO MARCADO\nDIA: " << newDate + 1;
    cout << "\nHORARIO TRABALHADO: " << h << ":" << m << endl;
    // QUESTAO DAS HORAS EXTRAS
    if (h >= 8)
    {
        extraTime.setHora(h - 8);
        extraTime.setMinutos(m);
        setHorasExtras(newDate, h - 8, m);
        novo.setHora(8);
        novo.setMinutos(0);
        ponto[newDate] = novo;
        return;
    }
    else
    {
        setHorasExtras(newDate, 0, 0);
        novo.setHora(h);
        novo.setMinutos(m);
        ponto[newDate] = novo;
    }
}

vector<Horario> Funcionario::getPonto()
{
    return ponto;
}
void Funcionario::setHorasExtras(int date, int h, int m)
{
    Horario aux;
    aux.setHora(h);
    aux.setMinutos(m);
    horasExtras[date] = aux;
    return;
}

vector<Horario> Funcionario::getHorasExtras()
{
    return horasExtras;
};

void Funcionario::NovaVenda(float val, string descr)
{
    Vendas nova;
    nova.setDescricao(descr);
    nova.setValor(val);
    vendasFeitas.push_back(nova);
    cout << nova;
    return;
}

vector<Vendas> Funcionario::getVendas()
{
    return vendasFeitas;
}

Funcionario &Funcionario::operator=(Funcionario &outro)
{

    nome = outro.nome;
    salarioHora = outro.salarioHora;
    ponto = outro.ponto;
    horasExtras = outro.horasExtras;
    vendasFeitas = outro.vendasFeitas;

    return *this;
}

vector<Horario> Funcionario::getHoraEntrada()
{
    return horaEntrada;
}
vector<Horario> Funcionario::getHoraSaida()
{
    return horaSaida;
}
void Funcionario::setHoraEntrada(int h, int m, int day)
{
    Horario aux;
    aux.setHora(h);
    aux.setMinutos(m);
    horaEntrada[day] = aux;
    return;
}
void Funcionario::setHoraSaida(int h, int m, int day)
{
    Horario aux;
    aux.setHora(h);
    aux.setMinutos(m);
    horaSaida[day] = aux;
}