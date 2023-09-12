#include "modoGerente.hpp"
#include "funcionario.hpp"
#include "chefe.hpp"
#include <vector>
#include "menu.hpp"
#include "pessoa.hpp"
#include <string>
using namespace std;
void ModoGerente::listarFuncionarios(vector<Pessoa *> pessoas)
{
    // funcao que lista os funcionarios do vetor pessoa
    for (auto alguem : pessoas)
    {//lista todos os funcionarios por meio de polimorfismo
        if (Funcionario *func = dynamic_cast<Funcionario *>(alguem))
        {
            cout << "\n"
                 << *func;
            cout << endl;
        }
    }
}

void ModoGerente::cadastrarFuncionario(vector<Pessoa *> &pessoas)
{
    string login, senha, nome;
    int tipo,validador=-1;
    float valorHora;
    cout << "\t...CRIANDO UM NOVO FUNCIONARIO...\n";
    do{       
        cout << "Digite\nNOME: ";
        cin.ignore();
        getline(cin, nome);
        cout << "LOGIN: ";
        cin >> login;
        cout << "SENHA: ";
        cin >> senha;
        cout << "VALOR DE HORAS TRABALHADAS: ";
        valorHora = recebeValorf();
        validador = confereCopia(pessoas,login,senha);
        }while(validador == -1);// confere se o login e senha sao iguais
     
    while (tipo != 1 && tipo != 2)// enquanto nao for 1 ou 2 vai repetir
    {
        cout << "\nTipo de funcionario:\n1.Supervisor\n2.Vendedor\n";
        tipo=recebeValor();
    }
    if (tipo == 1)
    {//adiciona novos funcionarios ao vetor de ponteiro de acorodo com o tipo 
        Pessoa *novoFuncionario = new Supervisor(login, senha, nome, valorHora);
        pessoas.push_back(novoFuncionario);
        Supervisor *sup = dynamic_cast<Supervisor*>(novoFuncionario);
        cout << endl << *sup;
    }
    if (tipo == 2)
    {
        Pessoa *novoFuncionario = new Vendedor(login, senha, nome, valorHora);
        pessoas.push_back(novoFuncionario);
        Vendedor* vend = dynamic_cast<Vendedor*>(novoFuncionario);
        cout << endl << "\t...FUNCIONARIO CRIADO...\n"<< *vend << endl;
    }
}
void ModoGerente::menuGerentePrincipal(vector<Pessoa *> &pessoas, int pos)
{
    int opcoes;
    do
    {
        cout << "\n\t**OPCOES DISPONIVEIS PARA GERENTE**";
        cout << "\n\n1.Cadastrar funcionario";
        cout << "\n2.Listar funcionarios";
        cout << "\n3.Checar ponto dos funcionarios";
        cout << "\n4.Calcular salario";
        cout << "\n5.Retornar a tela inicial" << endl;
        opcoes=recebeValor();

        if (opcoes == 1)
        {
            cadastrarFuncionario(pessoas);
        }
        if (opcoes == 2)
        {
            listarFuncionarios(pessoas);
        }
        if (opcoes == 3)
        {
            checkPontoFuncionarios(pessoas);
        }
        if (opcoes == 4)
        {
            mostraSalario(pessoas, pos);
        }
        if (opcoes == 5)
        {
            return;
        }
        if (opcoes < 1 || opcoes > 5)
            cout << "\nOPCAO INVALIDA";
    } while (opcoes != 5);
}

void ModoGerente::checkPontoFuncionarios(vector<Pessoa *> pessoas)
{
    vector<Horario> ponto, horaExtra, entra, sai;
    cout << "\tLEGENDA: ENTRADA [SAIDA]\n";
    for (vector<Pessoa *>::size_type i = 0; i < pessoas.size(); i++)
    {
        Pessoa *alguem = pessoas[i];
        if (Funcionario *func = dynamic_cast<Funcionario *>(alguem))
        {
            sai = func->getHoraSaida();
            entra = func->getHoraEntrada();
            cout << endl
                 << func->getNome() << endl
                 << endl;
            for (int j = 0; j < 4; j++)//4 semanas de 7 dias 
            {
                for (int k = 0; k < 7; k++)
                {
                    cout << entra[j * 7 + k] << "[" << sai[j * 7 + k] << "]";
                    cout << "("<< j * 7 + k <<")";
                    cout << "  ";
                }

                cout << endl;
            }
            cout << endl
                 << endl;
        }
    }
    cout << "\t LEGENDA: HORA NORMAL [HORA EXTRA](DIA DO MES)\n";
    for (vector<Pessoa *>::size_type i = 0; i < pessoas.size(); i++)
    {
        Pessoa *alguem = pessoas[i];
        if (Funcionario *func = dynamic_cast<Funcionario *>(alguem))
        {
            ponto = func->getPonto();
            horaExtra = func->getHorasExtras();
            cout << endl
                 << func->getNome() << endl
                 << endl;
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 7; k++)
                {
                    cout << ponto[j * 7 + k] << "[" << horaExtra[j * 7 + k] << "]";
                    cout << "("<< j * 7 + k <<")";
                    cout << "  ";
                }

                cout << endl;
            }
            cout << endl
                 << endl;
        }
    }
}

void ModoGerente::mostraSalario(vector<Pessoa *> pessoas, int pos)
{
    Pessoa *alguem = pessoas[pos];
    if (Chefe *ch = dynamic_cast<Chefe *>(alguem))
    {//printa o valor do salario por meio das horas trabalhadas e seu valor de hora
        cout << endl
             << "VALOR DA HORA:\t" << ch->getValorHora() << endl;
        cout << "QUANTIDADE DE HORAS:\t" << ch->getQtdHoraTrabalhada() << endl;
        cout << "\nVALOR DO SALARIO:\tR$" << ch->getQtdHoraTrabalhada() * ch->getValorHora();
        cout << endl;
    }
}

int confereCopia(vector<Pessoa *> &pessoas,string login,string senha){
    for(auto pessoa : pessoas){
        if(pessoa->getLogin() == login && pessoa->getSenha() == senha){
            cout<<endl<<"O Login e Senha nao podem ser repetidos.Tente novamente... "<<endl;
            return -1;
            }
    }
    return 1;
}