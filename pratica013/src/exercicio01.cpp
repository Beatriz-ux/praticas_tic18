#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
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

// Viagem
int qtdViagemDia(vector<Viagem> &, string);
void cadastrarViagem(vector<Viagem> &);
void listarViagem(vector<Viagem> &);
int buscarViagem(vector<Viagem> &, int);

// Passagem
void venderPassagem(vector<Viagem> &, vector<Passagem> &);
int valorTotalViagem(vector<Viagem> &, int);
int valorTotalViagemMes(vector<Viagem> &, int);
Passagem encontraPassagem(vector<Passagem> &, int, int);

// Validacoes
bool validaData(string);
bool validaCPF(char cpf[12]);

// Relatorios
string horarioMaisRentavel(vector<Viagem> &);
float mediaIdade(vector<Passagem> &);

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

// Passagem
void venderPassagem(vector<Viagem> &viagens, vector<Passagem> &passagens)
{
    int codigo;
    Passagem passagem;
    int poltrona;
    int resposta;
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
    do
    {

        cout << "Digite o CPF do cliente (apenas numeros): " << endl;
        cin >> passagem.cpf;
        resposta = validaCPF(passagem.cpf);
        if (!resposta)
        {
            cout << "CPF invalido" << endl;
        }
    } while (resposta);
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

// Viagem
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
    bool erro = false;
    viagem.codigo = viagens.size() + 1; // codigo da viagem é o tamanho do vetor +1, fazendo com meu codigo seja unico(para esse caso que não tem exclusao)
    do
    {
        do
        {
            cout << "Digite a data da viagem: " << endl;
            cin >> viagem.data;
            if (!validaData(viagem.data))
            {
                cout << "Data invalida" << endl;
                erro = true;
            }
            else
            {
                erro = false;
            }
        } while (erro);
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
    cout << "Viagens disponiveis: " << endl;
    cout << setw(10) << left << "Codigo"
         << setw(12) << left << "Data"
         << setw(10) << left << "Horario"
         << setw(18) << left << "Origem"
         << setw(18) << left << "Destino" << endl;
    for (int i = 0; i < viagens.size(); i++)
    {
        cout << setw(10) << left << viagens[i].codigo
             << setw(12) << left << viagens[i].data
             << setw(10) << left << viagens[i].horario
             << setw(18) << left << viagens[i].origem
             << setw(18) << left << viagens[i].destino << endl;
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

// Validacoes
bool validaData(string data)
{
    char temp[5], mesC[10];
    int i = 0, j = 0, dia, mes, ano;
    if (data.size() != 10)
    {
        return false;
    }
    else
    {
        while (data[i] != '/')
        {
            temp[i] = data[i];
            i++;
        }
        dia = atoi(temp);

        if (dia < 1 || dia > 31)
        {
            return false;
        }
        i++;
        while (data[i] != '/')
        {
            temp[j++] = data[i];
            i++;
        }
        i++;

        j = 0;
        mes = atoi(temp);

        if (mes < 1 || mes > 12)
        {
            return false;
        }
        j = 0;
        while (data[i] != '\0')
        {
            temp[j++] = data[i];
            i++;
        }
        ano = atoi(temp);

        if (ano == 0)
        {
            return false;
        }

        switch (mes)
        {
        case 1:
            if (dia > 31)
            {
                return false;
            }
            strcpy(mesC, "Janeiro");
            break;
        case 2:
            if (!(
                    (ano % 400 == 0) ||
                    ((ano % 4 == 0) && (ano % 100 != 0))) &&
                (dia == 29))
            {
                return false;
            }
            if (dia > 29)
            {
                return false;
            }
            strcpy(mesC, "Fevereiro");

            break;
        case 3:
            if (dia > 31)
            {
                return false;
            }
            strcpy(mesC, "Marco");
            break;
        case 4:
            if (dia > 30)
            {
                return false;
            }
            strcpy(mesC, "Abril");
            break;
        case 5:
            if (dia > 31)
            {
                return false;
            }
            strcpy(mesC, "Maio");
            break;
        case 6:
            if (dia > 30)
            {
                return false;
            }
            strcpy(mesC, "Junho");
            break;
        case 7:
            if (dia > 31)
            {
                return false;
            }
            strcpy(mesC, "Julho");
            break;
        case 8:
            if (dia > 31)
            {
                return false;
            }
            strcpy(mesC, "Agosto");
            break;
        case 9:
            if (dia > 30)
            {
                return false;
            }
            strcpy(mesC, "Setembro");
            break;
        case 10:
            if (dia > 31)
            {
                return false;
            }
            strcpy(mesC, "Outubro");
            break;
        case 11:
            if (dia > 30)
            {
                return false;
            }
            strcpy(mesC, "Novembro");
            break;
        case 12:
            if (dia > 31)
            {
                return false;
            }
            strcpy(mesC, "Dezembro");
            break;

        default:
            break;
        }
        return true;
    }
}
bool validaCPF(char cpf[12])
{
    // Verifica se o CPF possui 11 dígitos
    if (strlen(cpf) != 11)
        return false;

    // Verifica se todos os caracteres são dígitos numéricos
    for (int i = 0; i < 11; i++)
    {
        if (!isdigit(cpf[i]))
            return false;
    }

    // Converte o array de char para um array de inteiros
    int digitos[11];
    for (int i = 0; i < 11; i++)
    {
        digitos[i] = cpf[i] - '0';
    }
    // Se todas as verificações passaram, o CPF é válido
    return true;
}

// Relatorios
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
    if (passagens.size() == 0)
    {
        return 0;
    }
    for (int i = 0; i < passagens.size(); i++)
    {
        media += passagens[i].idade;
    }
    return media / passagens.size();
}
