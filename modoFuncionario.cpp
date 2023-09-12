#include "modofuncionario.hpp"
#include <iomanip>
#include <vector>
#include "menu.hpp"
#include "pessoa.hpp"
#include "funcionario.hpp"
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
#include "vendas.hpp"
using namespace std;


void ModoFuncionario::menuFuncionarioPrincipal(vector<Pessoa *> &pessoas, int posFuncionario)
{
    int opcoes;
    do
    { // loop para acessar funcoes e so sai quando o user deseja sair
        cout << "\nOPCOES PARA FUNCIONARIOS" << endl;
        cout << "1.Cadastrar ponto" << endl;
        cout << "2.Visualizar salario" << endl;
        cout << "3.Cadastrar vendas" << endl;
        cout << "4.Listar vendas" << endl;
        cout << "5.Voltar ao menu inicial" << endl;
        opcoes=recebeValor();
        if (opcoes == 1)
            cadastraPonto(pessoas, posFuncionario);
        if (opcoes == 2)
            calculaSalario(pessoas, posFuncionario);
        if (opcoes == 3)
            cadastraVenda(pessoas, posFuncionario);
        if (opcoes == 4)
            listarVendas(pessoas, posFuncionario);
        if (opcoes == 5)
        {
            return;
        }
    } while (opcoes != 5);
    
    return;
}

void ModoFuncionario::listarVendas(vector<Pessoa *> pessoas, int pos)
{
    cout << "ESTAS SAO AS VENDAS: " << endl;
    cout << endl;
    Pessoa *alguem = pessoas[pos];
    Funcionario *func = dynamic_cast<Funcionario *>(alguem);
    string auxNome;
    [[maybe_unused]] Supervisor *sup;
    if ((sup = dynamic_cast<Supervisor *>(func))) // lista de todos funcionarios se for supervisor
    {
        vector<Vendas> vendasAcumuladas; 
        for (vector<Pessoa *>::size_type i = 0; i < pessoas.size(); i++)
        {
            alguem = pessoas[i];
            [[maybe_unused]] Funcionario *func;
            if ((func = dynamic_cast<Funcionario *>(alguem)))
            {
                vector<Vendas> copia = func->getVendas();
                if (copia.size() > 0)
                    cout << "Vendas de " << func->getNome() << endl
                         << endl;
                for (vector<Vendas>::size_type j = 0; j < copia.size(); j++)
                {   
                    
                    cout << "VENDA " << j + 1 << endl
                         << endl
                         << copia[j] << endl;
                    
                    auxNome=copia[j].getDescricao();
                    auxNome = auxNome + "  (FUNCIONARIO - " + func->getNome() + ")";
                    copia[j].setDescricao(auxNome);
                    vendasAcumuladas.push_back(copia[j]);
                }
                cout << "---------------------------------------";
            }
        }
        int opc; cout << "\nDeseja ordenar as vendas?\n1.Sim\n2.Nao ";
        opc=recebeValor();
        if(opc == 1){
            cout << "\nOrdenar valor das vendas:\n1.Crescente\n2.Descrescente ";
            opc=recebeValor();
            ordenaEPrintaVendas(vendasAcumuladas,opc);
         }

    }
    [[maybe_unused]] Vendedor *vend;
    if ((vend = dynamic_cast<Vendedor *>(func))) // listar da pessoa se for vendedor
    {
        vector<Vendas> copia = vend->getVendas();
        if(copia.size() == 0) return;
        cout << "Vendas de: " << vend->getNome() << endl;
        for (vector<Vendas>::size_type i = 0; i < copia.size(); i++)
        {
            cout << "VENDA " << i << endl
                 << endl
                 << copia[i] << endl;
        }
        
        int opc; cout << "\nDeseja ordenar as vendas?\n1.Sim\n2.Nao ";
        opc=recebeValor();;
        if(opc == 1){
            cout << "\nOrdenar valor das vendas:\n1.Crescente\n2.Descrescente ";
            opc=recebeValor();
            ordenaEPrintaVendas(copia,opc);
            
         }
        
    }
}

void ModoFuncionario::cadastraVenda(vector<Pessoa *> &pessoas, int posicao)
{
    float newValue;
    string description;
    Vendas novaVenda;
    cout << "Valor da venda:" << endl;
    newValue=recebeValorf();
    cout << "Descricao da venda:" << endl;
    cin.ignore();
    
    getline(cin, description);

    novaVenda.setDescricao(description);
    novaVenda.setValor(newValue);
    // cadastra uma nova venda por referencia
    Pessoa *alguem = pessoas[posicao];
    if (Funcionario *func = dynamic_cast<Funcionario *>(alguem))
    {

        func->NovaVenda(newValue, description);
        cout << "\n\nVENDA CADASTRADA!!!\n\n";
    }
}

void ModoFuncionario::calculaSalario(vector<Pessoa *> &pessoas, int posicao)
{ 
    
    Pessoa *alguem = pessoas[posicao];
    // 2 tipos de salario: os dos VENDEDORES e dos SUPERVISORES
    Funcionario *func = dynamic_cast<Funcionario *>(alguem);
    Supervisor *sup;
    Vendedor *vend;
    if ((vend = dynamic_cast<Vendedor *>(func)))
    {
        vector<Vendas> vendasFuncionario = func->getVendas();
        vector<Horario> horasExtras, ponto; // variavel para analise a partir de encapsulamento
        float totalHorasExtras = 0, totalMinExtra = 0, totalPonto = 0, totalMinPonto = 0, valorVendas = 0;

        horasExtras = func->getHorasExtras();
        ponto = func->getPonto();

        for (vector<Horario>::size_type i = 0; i < horasExtras.size(); i++)
        {
            totalHorasExtras += horasExtras[i].getHora();
            totalMinExtra += horasExtras[i].getMinuto();
        }
        cout << "\nTOTAL DE HORAS EXTRAS\t\t" << totalHorasExtras << ":" << totalMinExtra;
        cout << endl;
        for (vector<Horario>::size_type i = 0; i < ponto.size(); i++)
        {

            totalPonto += ponto[i].getHora();
            totalMinPonto += ponto[i].getMinuto();
        }
        cout << "\nTOTAL DE HORAS TRABALHADAS\t\t" << totalPonto << ":" << totalMinPonto;
        cout << endl;
        for (vector<Vendas>::size_type i = 0; i < vendasFuncionario.size(); i++)
        {
            valorVendas += vendasFuncionario[i].getValor();
        }
        printaSalario(
            valorVendas,
            valorVendas * 0.1,
            (totalPonto + (totalMinPonto / 60)) * func->getSalarioHora(),
            2 * ((totalHorasExtras + (totalMinExtra / 60)) * func->getSalarioHora())
        );//funcao que vai printar as informações com base nestes parametros
        
    }
    else if ((sup = dynamic_cast<Supervisor *>(func))) // se for supervisor
    {

        // SALARIO: HORAS * VALOR DA HORA + 1% DAS VENDAS DE TODOS + HORASEXTRAS*VALHORA EXTRA
        vector<Vendas> vendasFuncionario;
        vector<Horario> horasExtras, ponto; // variavel para analise a partir de encapsulamento
        float totalHorasExtras = 0, totalMinExtra = 0, totalPonto = 0, totalMinPonto = 0, valorVendas = 0;

        horasExtras = func->getHorasExtras();
        ponto = func->getPonto();

        for (vector<Horario>::size_type i = 0; i < horasExtras.size(); i++)
        {
            totalHorasExtras += horasExtras[i].getHora();
            totalMinExtra += horasExtras[i].getMinuto();
        }

        cout << "\n\nTOTAL DE HORAS EXTRAS\t\t" << totalHorasExtras << ":" << totalMinExtra;
        cout << endl;
        for (vector<Horario>::size_type i = 0; i < ponto.size(); i++)
        {

            totalPonto += ponto[i].getHora();
            totalMinPonto += ponto[i].getMinuto();
        }

        cout << "TOTAL DE HORAS TRABALHADAS\t\t" << totalPonto << ":" << totalMinPonto;
        cout << endl;
        // ESTRUTURA CALCULO DE 1% DE TODAS AS VENDAS
        Pessoa *auxiliar;
        for (vector<Pessoa *>::size_type i = 0; i < pessoas.size(); i++)
        {
            auxiliar = pessoas[i];
            if (Funcionario *fAux = dynamic_cast<Funcionario *>(auxiliar))
            {
                vendasFuncionario = fAux->getVendas();
                for (vector<Vendas>::size_type j = 0; j < vendasFuncionario.size(); j++)
                {
                    valorVendas += vendasFuncionario[j].getValor();
                }
            }
        }
        printaSalario(
            valorVendas,
            valorVendas*0.01,
            (totalPonto + (totalMinPonto / 60)) * func->getSalarioHora(),
            2 * ((totalHorasExtras + (totalMinExtra / 60)) * func->getSalarioHora())
        );
    }
}

void ModoFuncionario::cadastraPonto(vector<Pessoa *> &pessoas, int posicao)
{ // refinar funcao
    int date, hour, minute;
    int confere;
    do
    {
        vector<Horario> extra, entraeSai;
        cout << "\nSelecione o dia: ";
        date=recebeValor();
        entraeSai = calculaPonto(); // chama a funcao que recebe entrada e saida e calcula o horario trabalhado
        hour = entraeSai[2].getHora();
        minute = entraeSai[2].getMinuto();

        Pessoa *alguem = pessoas[posicao]; // recebe a pessoa em que o ponto vai ser cadastrado

        if (Funcionario *func = dynamic_cast<Funcionario *>(alguem))
        {                                           // cast para cadastrar o ponto da pessoa , cadastro realizado por referencia
            func->setPonto(date - 1, hour, minute); // funcao vai definir horas normais e extras trabalhas
            func->setHoraEntrada(entraeSai[0].getHora(), entraeSai[0].getMinuto(), date - 1);
            func->setHoraSaida(entraeSai[1].getHora(), entraeSai[1].getMinuto(), date - 1);
        }
        confere = conferePontoSemanal(alguem);
    } while (confere != 1);
}

int ModoFuncionario::conferePontoSemanal(Pessoa *pessoas)
{
    Pessoa *alguem = pessoas;
    if (Funcionario *func = dynamic_cast<Funcionario *>(alguem)) // transforma em funcionario e
    {
        vector<Horario> horaExtra, ponto;
        float somaHoraExtra = 0, somaMinExtra = 0, somaPonto = 0, somaPontoMin = 0, somaTotal = 0;
        horaExtra = func->getHorasExtras();
        ponto = func->getPonto();
        for (int i = 0; i < 4; i++)
        { // 4 semanas
            somaTotal = 0;
            somaHoraExtra = 0;
            somaMinExtra = 0;
            somaPonto = 0;
            somaPontoMin = 0;
            for (int j = 0; j < 7; j++)
            {

                somaHoraExtra += horaExtra[j + 7 * i].getHora()*60;
                somaMinExtra += horaExtra[j + 7 * i].getMinuto();
                somaPontoMin += ponto[j + 7 * i].getMinuto();
                somaPonto += ponto[j + 7 * i].getHora()*60;
                somaTotal = somaPonto + somaPontoMin + somaMinExtra + somaHoraExtra;
            } // somatorio das horas com os minutos, se ultrapassar 50 gera erro
            if (somaTotal > 3000)
            {
                cout << "\n\nHORARIO TRABALHADO ULTRAPASSOU 50 HORAS (" << somaTotal/60 << " horas)";
                cout << "\n\nDIGITE NOVAMENTE UM HORARIO EM QUE NAO ULTRAPASSE O HORARIO SEMANAL DE 50 HORAS!\n";
                return 0;
            }
        }
    }
    return 1;
}

vector<Horario> ModoFuncionario::calculaPonto()
{
    int eHoras, eMinutos;
    int sHoras, sMinutos;
    int aux = 0;
    Horario entrada, saida, ponto;
    vector<Horario> conjunto;
    do // faz o calculo e validacao da entrada de horas e minutos
    {
        // HORAS: 0 - 24
        // MINUTOS: 0 - 59
        // recebe os dados
        do
        {
            cout << "\tHorario de entrada: \n";
            cout << "Horas:(Valor entre 0 e 23) ";
            eHoras=recebeValor();
        } while (eHoras < 0 || eHoras >= 24);
        do
        {
            cout << "Minutos: (Valor entre 0 e 59)";
            eMinutos=recebeValor();
            cout << endl;
        } while (eMinutos < 0 || eMinutos >= 60);
        do
        {
            cout << "\tHorario de saida: \n";
            cout << "Horas: (Valor entre 0 e 23) ";
            sHoras=recebeValor();
        } while (sHoras < 0 || sHoras >= 24);
        do
        {
            cout << "Minutos: (Valor entre 0 e 59) ";
            sMinutos=recebeValor();
        } while (sMinutos < 0 || sMinutos >= 60);

        entrada.setHora(eHoras);
        entrada.setMinutos(eMinutos);
        saida.setHora(sHoras);
        saida.setMinutos(sMinutos);
        // calcula o tempo de trabalho
        if (eHoras < sHoras)
        {
            if (eMinutos <= sMinutos)
            {
                ponto.setHora(sHoras - eHoras);
                ponto.setMinutos(sMinutos - eMinutos);
            }
            else
            
            {
                ponto.setHora(sHoras - eHoras - 1);
                ponto.setMinutos(60 - eMinutos + sMinutos);
            }
        }
        else if (eHoras > sHoras)
        {
            if (eMinutos <= sMinutos)
            {
                ponto.setHora(24 + sHoras - eHoras);
                ponto.setMinutos(sMinutos - eMinutos);
            }
            else
            {
                ponto.setHora(24 + sHoras - eHoras - 1);
                ponto.setMinutos(60 - eMinutos + sMinutos);
            }
        }
        else
        {
            if (eMinutos <= sMinutos)
            {
                ponto.setHora(0);
                ponto.setMinutos(sMinutos - eMinutos);
            }
            else
            {
                ponto.setHora(23);
                ponto.setMinutos(60 - eMinutos + sMinutos);
            }
        }
        aux = ponto.getHora() * 60 + ponto.getMinuto();
        if (aux > 600) // 10 horas * 60 = 600 minutos
            cout << endl
                 << "valor excedeu (" << ponto << ")\n";
    } while (aux > 600); // vai repetir ate que o tempo de trabalho seja menor ou igual a 10hrs
    cout << entrada << " - " << saida;
    /*retora um vetor de 3 posicoes:
        1- HORA DE ENTRADA
        2- HORA DE SAIDA
        3- HORARIO TRABALHADO (0 HRS - 10 HRS)
    */
    conjunto.push_back(entrada);
    conjunto.push_back(saida);
    conjunto.push_back(ponto);
    return conjunto;
}

void ModoFuncionario::ordenaEPrintaVendas(vector<Vendas> vendas,int opc){
    if(opc == 1){
        multiset<Vendas,less<Vendas>> vendaOrdenada;
        for(auto& auxiliar : vendas){
        vendaOrdenada.insert(auxiliar);
    }
    cout << "\n\n\tVENDAS ORDENADAS\n\n";
    for(const auto& auxPrinta : vendaOrdenada){
        cout << auxPrinta << endl;
    }
    }else if(opc==2){
        multiset<Vendas,greater<Vendas>> vendaOrdenada;
        for(auto& auxiliar : vendas){
        vendaOrdenada.insert(auxiliar);
    }
    cout << "\n\n\tVENDAS ORDENADAS\n\n";
    for(const auto& auxPrinta : vendaOrdenada){
        cout << auxPrinta << endl;
    }
    }

    vector<Vendas>::iterator it = max_element(vendas.begin(),vendas.end());
    cout << "\n O valor maximo eh: "<< *it;
    vector<Vendas>::iterator ite = min_element(vendas.begin(),vendas.end());
    cout << "\n O valor minimo eh: "<< *ite;

}


void printaSalario(float vendasTotais,float vendasFeitas,float horas,float horasExtras){
        cout << "\nVALOR TOTAL DAS VENDAS FEITAS:\t\tR$" << vendasTotais;
        cout << endl
             << endl; // calcula separadente com base no valor diferente de horas normais e extras
        cout << "VALOR HORAS TRABALHADAS\t\tR$" << fixed << setprecision(2)<<horas;
        cout << "\nVALOR HORAS EXTRAS\t\tR$" << fixed << setprecision(2)<<horasExtras;
        cout << "\nVALOR VENDAS\t\tR$" <<fixed << setprecision(2) <<vendasFeitas<< endl
             << endl;
        cout << "\nTOTAL \t\tR$"; // soma todos os possiveis tipos de receitas
        cout << fixed << setprecision(2) << horas + horasExtras + vendasFeitas;
        cout << endl
             << endl;
}