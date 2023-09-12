#include "horario.hpp"
#include <iostream>
using namespace std;

void Horario::setHora(int h)
{
    horas = h;
}
void Horario::setMinutos(int m)
{
    minutos = m;
}
int Horario::getHora()
{
    return horas;
}
int Horario::getMinuto()
{
    return minutos;
}
Horario::Horario()
{
    setHora(0);
    setMinutos(0);
}
Horario::Horario(int h, int m)
{
    setHora(h);
    setMinutos(m);
}

ostream &operator<<(ostream &out, Horario &cHorario)
{
    out << cHorario.getHora() << ":" << cHorario.getMinuto();
    return out;
}
