#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
typedef struct
{
    string codigo;
    string nome;
    float preco;
} Produto;

void toUpperCase(string &str)
{
    for (char &c : str)
    {
        c = toupper(c);
    }
}

bool qtdDigitos(string codigo, int qtd)
{
    if (codigo.length() != qtd)
    {
        cout << "Quantidade de digitos errada!" << endl;
        return false;
    }
    else
    {
        for (char c : codigo)
        {
            if (!isdigit(c))
            {
                cout << "Codigo deve conter apenas numeros!" << endl;
                return false;
            }
        }
    }

    return true;
}
bool verificaNome(vector<Produto> &produtos, string nome)
{
    for (int i = 0; i < produtos.size(); i++)
    {
        if (produtos[i].nome == nome)
        {
            cout << "Nome ja cadastrado" << endl;
            return false;
        }
    }
    if (nome.length() > 20)
    {
        cout << "Quantidade de caractes errada!" << endl;
        return false;
    }
    return true;
}
bool verificaCodigo(vector<Produto> &produtos, string codigo)
{
    for (int i = 0; i < produtos.size(); i++)
    {
        if (produtos[i].codigo == codigo)
        {
            cout << "Codigo ja cadastrado" << endl;
            return false;
        }
    }
    if (qtdDigitos(codigo, 13))
    {
        return true;
    }
    return false;
}
void cadastrarProduto(vector<Produto> &produtos)
{
    Produto produto;
    string nome;
    do
    {

        cout << "Digite o codigo do produto: " << endl;
        cin >> produto.codigo;
    } while (!verificaCodigo(produtos, produto.codigo));
    cin.ignore();
    do
    {
        cout << "Digite o nome do produto: " << endl;
        getline(cin,nome);
        toUpperCase(nome);
        
    } while (!verificaNome(produtos,nome));
    produto.nome = nome;

    cout << "Digite o preco do produto: " << endl;
    cin >> produto.preco;
    produtos.push_back(produto);
}
void listarProdutos(vector<Produto> &produtos)
{
    for (int i = 0; i < produtos.size(); i++)
    {
        cout << "Codigo: " << produtos[i].codigo << endl;
        cout << "Nome: " << produtos[i].nome << endl;
        cout << "Preco: " << produtos[i].preco << endl;
    }
}
bool excluirProduto(vector<Produto> &produtos)
{
    string codigo;
    cout << "Digite o codigo do produto que deseja excluir: " << endl;
    cin >> codigo;
    for (int i = 0; i < produtos.size(); i++)
    {
        if (produtos[i].codigo == codigo)
        {
            produtos.erase(produtos.begin() + i);
            return true;
        }
    }
    return false;
}
Produto consultarProduto(vector<Produto> &produtos, string codigo)
{

    for (int i = 0; i < produtos.size(); i++)
    {
        if (produtos[i].codigo == codigo)
        {
            return produtos[i];
        }
    }
    Produto produto;
    return produto;
}

int main(void)
{
    vector<Produto> produtos;
    int opcao = 0;
    string codigo;
    Produto produto;

    do
    {
        cout << "1-Cadastrar produto" << endl;
        cout << "2-Listar produtos" << endl;
        cout << "3-Excluir produto" << endl;
        cout << "4-Consultar preco" << endl;
        cout << "5-Sair" << endl;
        cin >> opcao;
        switch (opcao)
        {
        case 1:
            cadastrarProduto(produtos);
            break;
        case 2:
            listarProdutos(produtos);
            break;
        case 3:
            if (!excluirProduto(produtos))
            {
                cout << "Produto não encontrado." << endl;
            }
            else
            {
                cout << "Produto excluido com sucesso." << endl;
            }

            break;
        case 4:

            cout << "Digite o codigo do produto que deseja consultar: " << endl;
            cin >> codigo;
            produto = consultarProduto(produtos, codigo);
            if (produto.codigo.empty())
            {
                cout << "Produto não encontrado." << endl;
            }
            else
            {
                cout << "Preco: " << produto.preco << endl;
            }

            break;
        case 5:
            cout << "Saindo..." << endl;
            break;
        default:
            cout << "Opcao invalida" << endl;
            break;
        }

    } while (opcao != 5);
    return 0;
}