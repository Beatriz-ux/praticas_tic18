#include <iostream>
#include <vector>

using namespace std;
typedef struct
{
    int poltrona;
    int cpf;
    string nome;
    int codigo;
} Passagem;

typedef struct
{
    int codigo;
    string data;
    string horario;
    string origem;
    string destino;
    int assentos[40];
} Viagem;

void cadastrarViagem(vector<Viagem> &viagens)
{
    Viagem viagem;
    int opcao;
    if (viagens.size() == 10)
    {
        cout << "Numero maximo de viagens cadastradas" << endl;
        return;
    }
    cout << "Digite o codigo da viagem: " << endl;
    cin >> viagem.codigo;
    cout << "Digite a data da viagem: " << endl;
    cin >> viagem.data;
    cout << "Digite o horario da viagem: " << endl;
    cin >> viagem.horario;
    cout << "Qual sera a origem? 1-Rio de Janeiro 2-Sao Paulo" << endl;
    cin >> opcao;
    switch (opcao)
    {
    case 1:
        viagem.origem = "Rio de Janeiro";
        viagem.destino = "Sao Paulo";
        break;
    case 2:
        viagem.origem = "Sao Paulo";
        viagem.destino = "Rio de Janeiro";
        break;
    }
    viagem.assentos[40] = {0}; // inicializa tudo com 0, desocupado
    viagens.push_back(viagem);
}
void listarViagem(vector<Viagem> &viagens)
{
    // cout << "Viagens disponiveis: " << endl;
    cout << "\tCodigo\tData\tHorario\tOrigem\tDestino\t" << viagens.size() << endl;
    for (int i = 0; i < viagens.size(); i++)
    {
        cout << viagens[i].codigo << "\t";
        cout << viagens[i].data << "\t";
        cout << viagens[i].horario << "\t";
        cout << viagens[i].origem << "\t";
        cout << viagens[i].destino << endl;
    }
}
int buscarViagem(vector<Viagem> &viagens, int codigo)
{
    for (int i = 0; i < viagens.size(); i++)
    {
        if (viagens[i].codigo == codigo)
        {
            return i;
        }
    }
    return -1;
}

void venderPassagem(vector<Viagem> &viagens, vector<Passagem> &passagens)
{
    int codigo;
    Passagem passagem;
    int poltrona;
    cout << "Escolha o codigo de uma das viagens" << endl;
    listarViagem(viagens);
    cin >> codigo;
    int posicao = buscarViagem(viagens, codigo);
    if (posicao == -1)
    {
        cout << "Viagem nao encontrada" << endl;
        return;
    }

    do
    {
        cout << "Digite o numero da poltrona: " << endl;
        cin >> poltrona;
        if (viagens[posicao].assentos[poltrona] == 1)
        {
            cout << "Poltrona ocupada" << endl;
            poltrona = 0;
        }
        else
        {
            viagens[posicao].assentos[poltrona] = 1;
        }

    } while (poltrona < 1 || poltrona > 40);
    cout << "Digite o CPF do cliente: " << endl;
    cin >> passagem.cpf;
    cout << "Digite o nome do cliente: " << endl;
    cin >> passagem.nome;
    cout << "1" << endl;

    passagem.poltrona = poltrona;
    cout << "2" << endl;

    passagem.codigo = codigo;
    cout << "3" << endl;
    passagens.push_back(passagem);
    cout << "Passagem vendida com sucesso" << endl;
}
int main(void)
{
    vector<Passagem> passagens;
    vector<Viagem> viagens;
    int resposta = 0;
    do
    {
        cout << "Digite o numero da opcao desejada: " << endl;
        cout << "1 - Cadastrar Viagem" << endl;
        cout << "2 - Listar Passagens" << endl;
        cout << "2 - Venda de Passagens" << endl;
        cout << "4 - Sair" << endl;
        cin >> resposta;
        switch (resposta)
        {
        case 1:
            cadastrarViagem(viagens);
            break;
        case 2:
            listarViagem(viagens);
            break;
        case 3:
            venderPassagem(viagens, passagens);
            break;
        default:
            cout << "Opcao invalida" << endl;
            break;
        }

    } while (resposta != 4);
}