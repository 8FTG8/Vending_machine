#include <iostream> //Biblioteca para executar opera��es de leitura e grava��o em arquivos.
#include <vector> //Biblioteca para Armazenar elementos de um determinado tipo e permite o acesso a qualquer elemento.
#include <algorithm> //Biblioteca para pesquisa, classifica��o, contagem e manipula��o de dados.
#include <locale> //Biblioteca que garante que caracteres como ?�? e acentua��es gr�ficas sejam exibidos normalmente.

using namespace std; //Utilizado para que n�o se repita o std em todos os comandos padr�es da linguagem.

//Registro dos produtos da m�quina
typedef struct {
    string nome;
    string codigo;
    double preco;
    int quantidade;
} Produto;

//Vari�veis globais
double Faturamento_Total = 0.0;
double Faturamento_Restante = 0.0;

//Listar Produtos
void Listar_Produtos(const vector<Produto> &produtos) {
  if (produtos.empty()) {
    cout << "\nNenhum produto foi inserido!\n";
  } else {
      cout << "\nProdutos inseridos:\n";
      for (const auto & produto : produtos) {
        cout << "\nNome: " << produto.nome;
        cout << "\nC�digo: " << produto.codigo;
        cout << "\nPre�o: " << produto.preco; 
        cout << "\nQuantidade: " << produto.quantidade << endl;
      }
    }
}

//Modo Administrador
void Modo_Administrador(vector<Produto>& produtos) {
  
  int opcao_ADM = 0;
  int Contador_Login = 0;
  string Nome_ADM, Nome_ADM_Compativel;
  string Senha_ADM, Senha_ADM_Compativel;

  // Cria��o de conta de administrador
  if (Contador_Login == 0) {
    cout << "\n======= Criar Conta =======\n";
    cout << "Criar nome: ";
    cin >> Nome_ADM;
    cout << "Criar senha: ";
    cin >> Senha_ADM;
    cout << "" << endl;
  }
    
  Contador_Login = 1;
  
  do {
    if (Contador_Login == 1) {
      cout << "======= Entrar na Conta =======\n";
      cout << "Digite seu nome: ";
      cin >> Nome_ADM_Compativel;
      cout << "Digite sua senha: ";
      cin >> Senha_ADM_Compativel;
      cout << "" << endl;
  
      if (Nome_ADM == Nome_ADM_Compativel && Senha_ADM == Senha_ADM_Compativel) {
        
        cout << "\n======= Modo Administrador ativado =======" << endl;
        
        do {
          cout << "\n======= Escolha uma op��o: =======\n";
          cout << "1 - Listar os produtos inseridos\n";
          cout << "2 - Retirar um produto\n";
          cout << "3 - Repor um produto\n";
          cout << "4 - Ver faturamento da m�quina\n";
          cout << "5 - Sair do modo administrador e retornar � tela de login\n";
          cout << "Op��o escolhida: ";
          cin >> opcao_ADM;
          cout << "" << endl;
      
          switch (opcao_ADM) {
            
            //Listar os produtos inseridos
            case 1: {
              Listar_Produtos(produtos);
            break; 
            }
            //Excluir produto
            case 2: {
              if (produtos.empty()) {
                cout << "\nNenhum produto dispon�vel para remo��o.\n";
              } else {
                  string codigo;
                  cout << "\nDigite o c�digo do produto que deseja remover: ";
                  cin >> codigo;
                
                  auto it = find_if(produtos.begin(), produtos.end(), [&codigo](const Produto& produto) {
                  return produto.codigo == codigo; });
                
                    if (it != produtos.end()) {
                      Produto produto = *it;
                      produtos.erase(it); //Remove o produto do vetor de produtos
                      Faturamento_Restante -= produto.preco * produto.quantidade; //Atualiza o faturamento em potencial
                      cout << "\nProduto retirado com sucesso!\n";
                    } else {
                        cout << "\nProduto n�o encontrado.\n";
                      }
                    }
            break;
            }
            //Repor produto
            case 3: {
              if (produtos.empty()) {
                cout << "\nNenhum produto dispon�vel para reposi��o.\n";
              } else {
                  string codigo;
                    cout << "\nDigite o c�digo do produto que deseja repor: ";
                    cin >> codigo;
      
                  auto it = find_if(produtos.begin(), produtos.end(), [&codigo](const Produto& produto) {
                  return produto.codigo == codigo; });
      
                  if (it != produtos.end()) {
                    Produto & produto = *it;
                    int quantidade;
                      cout << "Digite a quantidade a ser reposta: ";
                      cin >> quantidade;
                      produto.quantidade += quantidade; //Atualiza a quantidade do produto.
                      Faturamento_Restante += produto.preco * quantidade; // Atualiza o faturamento restante da m�quina
                      cout << "\nProduto reposto com sucesso!\n";
                  } else {
                      cout << "\nProduto n�o encontrado.\n";
                    } 
                }
            break; 
            }
            //Ver faturamento da m�quina
            case 4: {
              cout << "\nTotal faturado: R$" << Faturamento_Total << endl;
              cout << "Faturamento restante: R$" << Faturamento_Restante << endl;
            break; 
            }
            //Sair do modo administrador
            case 5: {
              cout << "Encerrando o modo Administrador...\n";
            break; 
            }
            //Caso o usu�rio n�o digite nenhuma das tr�s op��es
            default:
              cout << "\nOp��o inv�lida! Tente novamente.\n";
            break;
          }
        } while (opcao_ADM != 5);
        
      } else {
        cout << "Nome ou/e senha incorreto(s)!\n";
        cout << "" << endl;
      }
    }
  } while (Nome_ADM != Nome_ADM_Compativel || Senha_ADM != Senha_ADM_Compativel);
}

//Modo Usu�rio
void Modo_Usuario(const vector<Produto>& produtos) {
  
  cout << "\n======= Modo Usu�rio ativado =======" << endl;
  
   int opcao = 0;

  while (opcao != 3) {
    cout << "\n======= Escolha uma op��o: =======\n";
    cout << "1 - Listar os produtos dispon�veis\n";
    cout << "2 - Realizar uma compra\n";
    cout << "3 - Sair do modo usu�rio e retornar � tela de login\n";
    cout << "Op��o escolhida: ";
    cin >> opcao;

    switch (opcao) {
      
      //Listar os produtos dispon�veis
      case 1: {
        Listar_Produtos(produtos);
      break; }
      
      //Realizar uma compra  
      case 2: {
        Listar_Produtos(produtos);
        
          string codigo;
          cout << "\nDigite o c�digo do produto que deseja comprar: ";
          cin >> codigo;

          auto it = find_if(produtos.begin(), produtos.end(), [&codigo](const Produto& produto) {
          return produto.codigo == codigo; });

          if (it != produtos.end()) {
              Produto produto = *it;
              int quantidade_compra;
                cout << "\nProduto encontrado!";
                cout << "Digite a quantidade que deseja comprar: ";
                cin >> quantidade_compra;

              double valor_total = produto.preco * quantidade_compra;
                cout << "Valor total da compra: R$" << valor_total << endl;

              double valor_pago;
                cout << "Digite o valor que voc� ir� dar � m�quina: R$";
                cin >> valor_pago;

            if (valor_pago >= valor_total) {
                double troco = valor_pago - valor_total;
                  cout << "Pagamento realizado com sucesso! Seu troco � de R$" << troco << endl;
            } else {
                  cout << "Valor insuficiente. A compra n�o pode ser realizada." << endl;
              }
          } else {
              cout << "\nProduto n�o encontrado.\n";
            }
        break; }
      
      //Sair do modo Usu�rio
      case 3: {
        cout << "\nEncerrando o modo Usu�rio...\n";
      break; }
     
      //Caso o usu�rio n�o digite nenhuma das tr�s op��es
      default:
        cout << "\nOp��o inv�lida! Tente novamente.\n";
      break;
    }
  }
}

//Tela de login
int main() {

  setlocale(LC_ALL, "Portuguese_Brazil");
  
  int Opcao_Login;

  vector<Produto> produtos = {  {"Coca-Cola 600ml", "001", 6.5, 10},     // Produto 1
                                {"�gua com G�s", "002", 3.0, 5},         // Produto 2
                                {"�gua Mineral", "003", 2.5, 3},         // Produto 3
                                {"Diamante Negro", "004", 10.0, 8},      // Produto 4
                                {"Salgadinho cheetos", "005", 9.0, 6} }; // Produto 5

  do {
    cout << "\n===== VENDING MACHINE =====\n" << endl;
    cout << "====== Tela de Login ======\n" << endl;
    cout << "Selecione um modo:" << endl;
    cout << "1 - ADMINISTRADOR" << endl;
    cout << "2 - USU�RIO" << endl;
    cout << "3 - SAIR DA M�QUINA DE VENDAS" << endl;
    cout << "Modo escolhido: ";
    cin >> Opcao_Login;

    if (Opcao_Login == 1) {
        Modo_Administrador(produtos); //Chama a fun��o respons�vel pelo modo de administrador
    } else if (Opcao_Login == 2) {
        Modo_Usuario(produtos); //Chama a fun��o respons�vel pelo modo de usu�rio
    } else if (Opcao_Login == 3) {
        cout << "\nSaindo do programa...\n";
      break;
    } else {
        cout << "\nOp��o inv�lida! Tente novamente." << endl;
    }
  } while (true);
}