#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define BUFLEN 30

typedef struct
{
    int codigo;
    char nome[BUFLEN];
    float preco;
} Produto;

typedef struct
{
    Produto produto;
    int quantidade;
} Itens;

// Declarando as funções
void infoProduto(); // implementada
void menu(); // implementada
void cadastrarProduto(); // implementada
void listarProduto(); // implementada
void comprarProduto();
void visuCarrinho(); // implementada
Produto pegarProdutoPorCodigo(int codigo); // implementada
int *temNocarrinho(int codigo); // implementada
void fecharPedido(); // implementada

// Variáveis globais
static int contador_produtos = 0;
static int contador_carrinho = 0;
static Itens  carrinho[50];
static Produto produtos[50];

int main()
{
    menu();
    return 0;
};

// Informa o produto
void infoProduto(Produto prod)
{
    printf("Codigo: %d\nNome: %s\nPreco: %.2f\n", prod.codigo, strtok(prod.nome, "\n"), prod.preco);
}

// Menu para mostrar as opções ao usuário
void menu()
{
    printf("======================================\n");
    printf("============== Bem vindo =============\n");
    printf("======================================\n");

    int opcao;

    printf("Selecione uma das opcoes abaixo\n");
    printf("1 - cadastrar produto\n");
    printf("2 - Listar produto\n");
    printf("3 - Comprar produto\n");
    printf("4 - Visualiar carrinho\n");
    printf("5 - Fechar pedido\n");
    printf("6 - sair do sistema\n");

    scanf("%d", &opcao);
    getchar(); // contenção de bugs

    //Switch case para uma das opções
    switch(opcao)
    {
    case 1: // cadastrar um produto
        cadastrarProduto();
        break;
    case 2: // Listar produto
        listarProduto();
        break;
    case 3: // Comprar produto
        comprarProduto();
        break;
    case 4: // Visuliza os itens no carrinho
        visuCarrinho();
        break;
    case 5: // Fecha o pedido
        fecharPedido();
        break;
    case 6: // Fecha o sistema
        printf("Ate a proxima\nVolte sempre\n");
        Sleep(2);
        exit(0);
    default: // caso nenhum case seja satisfeito, chama a função menu novamente
        printf("opcao invalida");
        menu();
        break;
    }

}
void cadastrarProduto()
{
    printf("Cadastro de produtos\n");

    printf("Informe o nome do produto\n");
    fgets(produtos[contador_produtos].nome, BUFLEN, stdin); // Pegando o nome do produto

    printf("Informe o preco do produto\n");
    scanf("%f", &produtos[contador_produtos].preco); // Pegando o preço do produto

    printf("produto %s foi cadastrado com sucesso\n", strtok(produtos[contador_produtos].nome, "\n"));

    produtos[contador_produtos].codigo = (contador_produtos + 1); // codigo = contador + 1
    contador_produtos++; // Incrementando o contador

    Sleep(2);
    menu();
}
// Lista os produtos cadastrados
void listarProduto()
{
    if(contador_produtos > 0)  // se for maior que 0
    {
        printf("Listage de produtos.\n");
        printf("--------------------\n");
        for(int i = 0; i < contador_produtos; i++)  // varre o vetor de produtos
        {
            infoProduto(produtos[i]); // informa os proddutos no vetor
            printf("--------------------------------\n");
            Sleep(1);
        }
    }
    else   // se o conta_produtos < 0, não há produtos cadastrados
    {
        printf("Nao ha produtos cadastrados\n\n");
    }
    Sleep(3);
    menu();

}
// Adiocina um produto ou incrementa a quantidade do mesmo
void comprarProduto()
{
    if(contador_produtos > 0)
    {
        // Mostrar os produtos cadastrados
        printf("--- Produtos disponiveis ---\n");
        for(int i = 0; i < contador_produtos; i++)
        {
            infoProduto(produtos[i]);
            printf("-------------------\n");
            Sleep(2);
        }
        int codigo; // variável para procurar o produto desejado
        scanf("%d", &codigo);
        getchar();
        int tem_mercado  = 0;
        for(int i = 0; i < contador_produtos; i++) // Varre o vetor de produtos
        {
            if(produtos[i].codigo == codigo) // compara o codigo procurado com o codigo dos produtos cadastrados
            {
                tem_mercado = 1; // se achar, muda o valor da flag

                if(contador_carrinho > 0) // caso haja produtos no carrinho
                {
                    int * retorno = temNocarrinho(codigo); // verifica se o produto já está no carrinho

                    if(retorno[0] == 1) // caso o retorno seja 1 -> o produto já está no carrinho
                    {
                        carrinho[retorno[1]].quantidade++; // aumenta a quantidade do produto que já está no carrinho
                        printf("O produto %s está no carrinho,+1 adicionado: %d \n",
                               strtok(carrinho[retorno[1]].produto.nome, "\n"), carrinho[retorno[1]].quantidade);
                        Sleep(2); // pausa o programa por 2 segundos
                        menu(); // chama o menu novamente
                    }
                    else // caso o produto procurado não esteja no carrinho
                    {
                        // declarando uma variável do tipo produto para atribuir a função pegarProdutosPorCodigo
                        Produto p = pegarProdutoPorCodigo(codigo); // Procurando nos produtos cadastrados através do código
                        carrinho[contador_carrinho].produto = p; //adicionando p ao carrinho
                        carrinho[contador_carrinho].quantidade = 1; // adionando a quantidade inicial ao produto;
                        contador_carrinho++; // aumentando o tamanho do vetor de itens no carrinho
                        printf("O produto %s foi adicionado ao carrinho\n",strtok(p.nome, "\n"));
                        Sleep(2);
                        menu(); // chama o menu novamente
                    }
                }
                else // caso não haja produtos no carrinho
                    {
                    Produto p = pegarProdutoPorCodigo(codigo); // Procurando nos produtos cadastrados através do código
                    carrinho[contador_carrinho].produto = p; //adicionando p ao carrinho
                    carrinho[contador_carrinho].quantidade = 1; // adionando a quantidade inicial ao produto;
                    contador_carrinho++; // aumentando o tamanho do vetor de itens no carrinho
                    printf("O produto %s foi adicionado ao carrinho\n",strtok(p.nome, "\n"));
                    Sleep(2);
                    menu(); // chama o menu novamente
                    }
                }
            }
            if(!tem_mercado) // se o produto procurado nn costar nos itens cadastrados
                {
                printf("Nao foi encontrado produtos com o codigo digitado: %d\n\n", codigo);
                Sleep(4);
                menu(); // chama o menu novamente
                }
        }
        else // se não houver item algum cadastrado
        {
            printf("Nao ha produtos cadastrados no momento\n\n");
            Sleep(2);
            menu(); // chama o menu novamente
        }


    }
// Mostra os produtos no carrinho
    void visuCarrinho()
    {
        if(contador_carrinho > 0)  // caso o contador de itens no carrinho seja maior que 0
        {
            printf("Produtos no carrinho\n");
            printf("---------------------\n");
            for(int i = 0; i < contador_carrinho; i++) // Varre o vetor de itens no carrinho
            {
                infoProduto(carrinho[i].produto);  // informa os produtos
                printf("Quantidade: %d\n", carrinho[i].quantidade); // informa a quantidade
                printf("---------------------\n");
                Sleep(1);
            }
        }
        else   // se não for maior que 0, significa que o carrinho está vazio
        {
            printf("O carrinho esta vazio\n\n");
        }
        Sleep(2);
        menu(); // chama o menu novamente
    }
// Procura por um produto pelo código
    Produto pegarProdutoPorCodigo(int codigo)
    {
        Produto p;

        // Varrendo o vetor de produtos, vendo codigo a codigo
        for(int i = 0; i < contador_produtos; i++)
        {
            if(produtos[i].codigo == codigo)  // se o  codigo for igual ao procurado, retorna o produto
            {
                p = produtos[i];
            }
        }
        return p;
    }
// Informa se um produto já está no carrinho
    int *temNocarrinho(int codigo)
    {
        int static retorno[] = {0, 0};
        for(int i = 0; i < contador_carrinho; i++)  // varre o vetor de itens no carrinho
        {
            if(carrinho[i].produto.codigo == codigo)
            {
                retorno[0] = 1; // tem produto com esse codigo no carrinho
                retorno[1] = i; // o indice do produto no carrinho
            }
        }
        return retorno;
    }
// Fecha o pedido e entrega o valor total a ser pago
    void fecharPedido()
    {
        if(contador_carrinho > 0)  // verificando se ha itens no carrinho
        {
            float valor_total = 0.0;
            printf("Produtos no carrinho\n");
            printf("--------------------\n");
            for(int i  = 0; i < contador_carrinho; i++)
            {
                Produto p = carrinho[i].produto;
                int quantidade = carrinho[i].quantidade;
                valor_total += p.preco * quantidade; // somando o valor de cada produto vezes a quantidade ao vt
                infoProduto(p); // informa os produtos no carrinho
                printf("Quantidade: %d\n", quantidade); // informando a quantidade do produto
                printf("--------------\n");
            }
            printf("Sua fatura é R$ %.2f\n", valor_total);
            // limpando o carrinho
            contador_carrinho = 0;

            printf("Obrigado pela preferencia\n\n");
            Sleep(5);
            menu(); // chama o menu novamente
        }
        else
        {
            printf("Nao ha itens no carrinho ainda\n\n");
            Sleep(3);
            menu(); // chama o menu novamente
        }
    }
