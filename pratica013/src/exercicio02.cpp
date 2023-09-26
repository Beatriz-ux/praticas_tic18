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
    cout << "Digite a data de nascimento do empregado: " << endl;
    cin >> empregados[*tamanho].dataNascimento;
    cout << "Digite o RG do empregado: " << endl;
    cin >> empregados[*tamanho].rg;
    cout << "Digite o ano de admissao do empregado: " << endl;
    cin >> empregados[*tamanho].anoAdmissao;
    cout << "Digite o salario do empregado: " << endl;
    cin >> empregados[*tamanho].salario;
    *tamanho += 1;
}
void listarEmpregados(Empregado* empregados, int tamanho){
    for(int i = 0; i < tamanho; i++){
        cout << "Nome: " << empregados[i].nome << endl;
        cout << "Sobrenome: " << empregados[i].sobrenome << endl;
        cout << "Data de nascimento: " << empregados[i].dataNascimento << endl;
        cout << "RG: " << empregados[i].rg << endl;
        cout << "Ano de admissao: " << empregados[i].anoAdmissao << endl;
        cout << "Salario: " << empregados[i].salario << endl;
    }
}

int main (void){
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