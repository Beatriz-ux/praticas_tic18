#include <iostream>
using namespace std;

typedef struct 
{
    string nome;
    string sobrenome;
    char dataNascimento[11];
    char rg[10];
    char anoAdmissao[5];
    float salario;
}Empregado;

void reajustar_dez_porcento(Empregado*, int);
void cadastrarEmpregado(Empregado*, int*);
void listarEmpregados(Empregado*, int);

// Validacoes
bool validaData(string);
bool validaRG(char cpf[12]);
bool validaRGEmpregado(char rg[11], Empregado *empregados, int tamanho);
int main(void)
    Empregado empregados[50];
    int tamanho = 0;
    int opcao;
    do{
        cout << "1-Cadastrar empregado" << endl;
        cout << "2-Reajustar salario" << endl;
        cout << "3-Sair" << endl;
        cin >> opcao;
        switch (opcao)
        {
        case 1:
            cadastrarEmpregado(empregados,&tamanho);
            break;
        case 2:
            reajustar_dez_porcento(empregados,tamanho);
            break;
        case 3:
            listarEmpregados(empregados,tamanho);
            break;
        case 4:
            cout << "Saindo..." << endl;
            break;
        default:
            cout << "Opcao invalida" << endl;
            break;
        }
    }while(opcao != 4);
    return 0;

}


void reajustar_dez_porcento(Empregado* empregados, int tamanho){
    for(int i = 0; i < tamanho; i++){
        empregados[i].salario *= 1.1;
    }
}
void cadastrarEmpregado(Empregado* empregados,int* tamanho){
    cout << "Digite o nome do empregado: " << endl;
    cin >> empregados[*tamanho].nome;
    cout << "Digite o sobrenome do empregado: " << endl;
    cin >> empregados[*tamanho].sobrenome;
    do
    {
    cout << "Digite a data de nascimento do empregado: " << endl;
    cin >> empregados[*tamanho].dataNascimento;
        if (!validaData(empregados[*tamanho].dataNascimento))
        {
            cout << "Data invalida" << endl;
            valido = true;
        }
        else
        {
            valido = false;
        }
    } while (valido);
    do
    {

    cout << "Digite o RG do empregado: " << endl;
    cin >> empregados[*tamanho].rg;
        if (!validaRGEmpregado(empregados[*tamanho].rg, empregados, *tamanho))
        {
            cout << "RG invalido" << endl;
            valido = true;
        }
        else
        {
            valido = false;
        }
    } while (valido);
    cout << "Digite o ano de admissao do empregado: " << endl;
    cin >> empregados[*tamanho].anoAdmissao;
    cout << "Digite o salario do empregado: " << endl;
    cin >> empregados[*tamanho].salario;
    *tamanho += 1;
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
bool validaRG(char rg[11])
{
    // Verifica se o CPF possui 11 dígitos
    if (strlen(rg) != 10)
        return false;

    // Verifica se todos os caracteres são dígitos numéricos
    for (int i = 0; i < 10; i++)
    {
        if (!isdigit(rg[i]))
            return false;
    }

    // Converte o array de char para um array de inteiros
    int digitos[10];
    for (int i = 0; i < 10; i++)
    {
        digitos[i] = rg[i] - '0';
    }
    // Se todas as verificações passaram, o CPF é válido
    return true;
}
bool validaRGEmpregado(char rg[11], Empregado *empregados, int tamanho)
{
    if(!validaRG(rg)){
        return false;
    }else{
        for (int i = 0; i < tamanho; i++)
        {
            if(strcmp(rg, empregados[i].rg) == 0){
                return false;
            }
}
    }
    return true;
}