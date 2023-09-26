#include <iostream>
#include <vector>

using namespace std;
typedef struct
{
    int poltrona;
    char cpf[12];
    string nome;
    int idade;
    int codigo = -1;
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
int qtdViagemDia(vector<Viagem> &viagens, string data)
{
    int qtd = 0;
    for (int i = 0; i < viagens.size(); i++)
    {
        if (viagens[i].data == data)
        {
            qtd++;
        }
    }
    return qtd;
}

void cadastrarViagem(vector<Viagem> &viagens)
{
    Viagem viagem;
    int opcao;
    int qtdDia;
    viagem.codigo = viagens.size() + 1; // codigo da viagem é o tamanho do vetor +1, fazendo com meu codigo seja unico(para esse caso que não tem exclusao)
    do
    {
        cout << "Digite a data da viagem: " << endl;
        cin >> viagem.data;
        qtdDia = qtdViagemDia(viagens, viagem.data);
        if (qtdDia >= 10)
        {
            cout << "Não há frota, data lotada" << endl;
        }
    } while (qtdDia >= 10);
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
    cout << "Digite a idade do cliente: " << endl;
    cin >> passagem.idade;
    passagem.poltrona = poltrona;
    passagem.codigo = codigo;
    passagens.push_back(passagem);
    cout << "Passagem vendida com sucesso" << endl;
}
int valorTotalViagem(vector<Viagem> &viagens, int codigo)
{
    int posicao = buscarViagem(viagens, codigo);
    int valor = 0;
    if (posicao == -1)
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < 40; i++)
        {
            if (viagens[posicao].assentos[i] == 1)
            {
                valor += 80;
            }
        }
    }
    return valor;
}
int valorTotalViagemMes(vector<Viagem> &viagens, int mes)
{
    string mesV;
    int valor = 0;
    for (int i = 0; i < viagens.size(); i++)
    {
        mesV = viagens[i].data.substr(3, 2);
        if (stoi(mesV) == mes)
        {
            valor += valorTotalViagem(viagens, viagens[i].codigo);
        }
    }
    return valor;
}
Passagem encontraPassagem(vector<Passagem> &passagens, int codigo, int poltrona)
{
    for (int i = 0; i < passagens.size(); i++)
    {

        if (passagens[i].codigo == codigo && passagens[i].poltrona == poltrona)
        {
            return passagens[i];
        }
    }

    return Passagem();
}

string horarioMaisRentavel(vector<Viagem> &viagens)
{
    int maior = 0, posicao = 0;
    for (int i = 0; i < viagens.size(); i++)
    {
        if (valorTotalViagem(viagens, viagens[i].codigo) > maior)
        {
            maior = valorTotalViagem(viagens, viagens[i].codigo);
            posicao = i;
        }
    }
    return viagens[posicao].horario;
}

float mediaIdade(vector<Passagem> &passagens)
{
    float media = 0;
    if(passagens.size() == 0){
        return 0;
    }
    for (int i = 0; i < passagens.size(); i++)
    {
        media += passagens[i].idade;
    }
    return media / passagens.size();
}
int main(void)
{
    vector<Passagem> passagens;
    vector<Viagem> viagens;
    Passagem passagem;
    int resposta = 0;
    do
    {
        cout << "Digite o numero da opcao desejada: " << endl;
        cout << "1 - Cadastrar Viagem" << endl;
        cout << "2 - Listar Viagens" << endl;
        cout << "3 - Venda de Passagens" << endl;
        cout << "4 - Total arrecadado de uma viagem" << endl;
        cout << "5 - Total arrecadado do mes" << endl;
        cout << "6 - Encontrar passageiro" << endl;
        cout << "7 - Horario da viagem mais rentavel" << endl;
        cout << "8 - Media de idade dos passageiros" << endl;
        cout << "9 - Sair" << endl;
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
        case 4:
            int codigo;
            cout << "Digite o codigo da viagem: " << endl;
            cin >> codigo;
            if (valorTotalViagem(viagens, codigo) != -1)
                cout << "Total arrecadado: " << valorTotalViagem(viagens, codigo) << endl;
            else
            {
                cout << "Viagem nao encontrada" << endl;
            }
            break;
        case 5:
            int mes;
            cout << "Digite o mes: " << endl;
            cin >> mes;
            cout << "Total arrecadado: " << valorTotalViagemMes(viagens, mes) << endl;
            break;
        case 6:
            int codigoP, poltrona;
            cout << "Digite o codigo da viagem: " << endl;
            cin >> codigoP;
            cout << "Digite o numero da poltrona: " << endl;
            cin >> poltrona;
            passagem = encontraPassagem(passagens, codigoP, poltrona);
            if (passagem.codigo != -1)
            {

                cout << "Nome: " << passagem.nome << endl;
                cout << "CPF: " << passagem.cpf << endl;
            }
            else
            {
                cout << "Passagem nao encontrada" << endl;
            }
            break;
        case 7:
            cout << "Horario da viagem mais rentavel: " << horarioMaisRentavel(viagens) << endl;
            break;
        case 8:
            cout << "Media de idade dos passageiros: " << mediaIdade(passagens) << endl;
            break;

        case 9:
            break;
        default:
            cout << "Opcao invalida" << endl;
            resposta = 9;
            break;
        }

    } while (resposta != 9);
    return 0;

}