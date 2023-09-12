#ifndef HORARIO_HPP
#define HORARIO_HPP
#include <iostream>
using namespace std;
class Horario
{
private:
    int horas, minutos;

public:
    void setHora(int);
    void setMinutos(int);
    int getHora();
    int getMinuto();
    Horario();
    Horario(int, int);
    friend ostream &operator<<(ostream &out, Horario &cHorario);
};

#endif