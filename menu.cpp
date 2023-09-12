#include "menu.hpp"
#include <iostream>
#include <string>
#include "pessoa.hpp"
#include <vector>
#include "chefe.hpp"
#include "funcionario.hpp"
#include "modoGerente.hpp"
#include "modofuncionario.hpp"

using namespace std;

enum Logar
{
    FALHA,
    ACERTO
};

int Menu::getOpcao()
{
    return opcao;
}

void Menu::setOpcao(int opc)
{
    opcao = opc;
    return;
}

vector<Pessoa *> Menu::contrutorMenu()
{
    vector<Pessoa *> p;
    
    
    Pessoa *primeiroGerente = new Chefe("joao", "1234", "Joao Bicalho", 120, 70);     // criacao de um gerente e um funcionario incial
    
    // aplicação de polimorfismo
    p.push_back(primeiroGerente);
    
    setOpcao(1);

    return p;
}

Menu::Menu()
{
    opcao = 0;
}

void Menu::menuInicial()
{
    int opc;
    vector<Pessoa *> pessoas;
    do //looping que vai acontecer ate o usuario querer sair
    {
        if (getOpcao() == 0)//pelo construtor padrao, opcao começa em 0, depois de executar a funcao,set opcao para != 0 
        {
            pessoas = contrutorMenu();
        }

        cout << "Entrar como:  " << endl;
        cout << "1.Gerente" << endl
             << "2.Funcionario\n3.Sair\n";
        
        opc = recebeValor();
        if (opc == 1)
        {
            menuGerente(pessoas);//acessa o validador para entrar no modo gerente
        }
        if (opc == 2)
        {
            menuFuncionario(pessoas);//acessa validado para entrar modo funcionario
        }
        if (opc == 3)
        {
            //limpa o vetor, de modo que as variaveis alocadas dinamicamente sao deletadas
            //para nao vazar memoria
            for (auto& pessoa : pessoas) {
                delete pessoa;
                pessoa = nullptr;
                }
            pessoas.clear();
            return;
        }
    } while (opc != 3);
}
void Menu::menuGerente(vector<Pessoa *> &p)
{
    int pos = fazerLoginGerente(p); // retorna posicao de login der certo ou -1 se falhar
    if (pos == -1)
        return;
    ModoGerente novoMenu;
    novoMenu.menuGerentePrincipal(p, pos);//entra no modo passando a referencia do vetor e a posicao da pessoa que entrou
}
void Menu::menuFuncionario(vector<Pessoa *> &p)
{
    int posicao = fazerLoginFuncionario(p);
    if (posicao == -1)
        return;
    ModoFuncionario novoMenu;
    novoMenu.menuFuncionarioPrincipal(p, posicao); //entra no modo passando a referencia do vetor e a posicao da pessoa que entrou
}

int Menu::fazerLoginGerente(vector<Pessoa *> p)
{

    Logar tentativa = FALHA;
    string user, password; // variaveis para comparação
    [[maybe_unused]] int posicao = 0;

    do
    {//looping de tela que sai ao conseguir logar ou quando o usuario querer sair

        cout << "Fazer Login no modo GERENTE:\n\n";
        cout << "Login: ";
        cin >> user;
        cout << "Senha: ";
        cin >> password;

        for (vector<Pessoa *>::size_type i = 0; i < p.size(); i++)
        {
            // estrutura de login credenciada:
            // SO CONSEGUE ENTRAR NO MENU GERENTE QUEM EH GERENTE
            Pessoa *alguem = p[i];
            [[maybe_unused]] Funcionario *func;
            if ((func = dynamic_cast<Funcionario *>(alguem)))
                continue;
            // Se no vetor for funcionario, o LOOP continua e ñ confere
            if (p[i]->getLogin() == user && p[i]->getSenha() == password)
            {
                cout << "\n\n****LOGIN VALIDADO!!!****\n";
                tentativa = ACERTO;
                posicao = i;
                return i;
            }
        }
        if (tentativa == FALHA)
        {
            int opc;
            cout << "\n\nERRO NO LOGIN, TENTE NOVAMENTE";
            cout << "\n1.TENTAR NOVAMENTE\n2.VOLTAR";
            opc = recebeValor();
            if (opc == 2)
                return -1;
        }

    } while (tentativa == FALHA);

    return 0;
}
int Menu::fazerLoginFuncionario(vector<Pessoa *> p)
{
    Logar tentativa = FALHA;
    string user, password; // variaveis para comparação

    do
    {//looping que sai quando quer sair ou quando conseguir logar

        cout << "Fazer Login no modo FUNCIONARIO:\n\n";
        cout << "Login: ";
        cin >> user;
        cout << "Senha: ";
        cin >> password;

        for (vector<Pessoa *>::size_type i = 0; i < p.size(); i++)
        {
            // estrutura de login credenciada:
            // SO CONSEGUE ENTRAR NO MENU FUNCIONARIO QUEM EH FUNCIONARIO
            Pessoa *alguem = p[i];
            [[maybe_unused]] Chefe *func;
            if ((func = dynamic_cast<Chefe *>(alguem)))
                continue;
            // Se no vetor for funcionario, o LOOP continua e ñ confere
            if (p[i]->getLogin() == user && p[i]->getSenha() == password)
            {
                cout << "\n\nlogin VALIDADO\n\n";
                tentativa = ACERTO;

                return i;
            }
        }
        if (tentativa == FALHA)
        {
            int opc;
            cout << "\n\nERRO NO LOGIN, TENTE NOVAMENTE";
            cout << "\n1.TENTAR NOVAMENTE\n2.VOLTAR\n\n";
            opc=recebeValor();
            if (opc == 2)
                return -1;
        }

    } while (tentativa == FALHA);
    return 0;
}

int recebeValor(){
    int valor;
    cin >> valor;
    if( !cin>>valor){
        cin.clear();
        cin.ignore();
        cout << "\n\tDigite um valor valido: "; 
        cin >> valor;
    };
    return valor;

}

float recebeValorf(){
    float valor;
    
    if( !scanf("%f",&valor)){
        cin.clear();
        cin.ignore();
        cout << "\n\tDigite um valor (float) valido: "; 
        scanf("%f",&valor);
    };
    return valor;
}