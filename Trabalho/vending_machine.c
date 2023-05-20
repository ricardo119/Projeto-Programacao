#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 48

typedef struct data{
	int dia,mes,ano;
}DATA;

typedef struct info{
	char informacao[100];
	float calorias;
}INFO;

typedef struct produtos{
	char codigo[3];
	char nome[20];
	char tipo_produto[20];
	INFO info_produto;
	DATA data_validade;
	float price;
	int quantidade;
}PRODUTO;

void utilizador_admin(PRODUTO produtos[MAX], int* num_produto, char* codigo_utilizador);

void adicionar_produto(PRODUTO produtos[MAX], int* num_produto);

void listar_produtos(PRODUTO produtos[MAX], int* num_produto);

float calculo_troco(PRODUTO produtos[MAX], int* num_produto, float preco_utilizador, int i);

void comprar_produto(PRODUTO produtos[MAX], int* num_produto, char* codigo_utilizador);

float carregar_produtos(PRODUTO produtos[MAX], int* num_produto);

void guardar_produto(PRODUTO produtos[MAX], int* num_produto);

void guardar_compra(PRODUTO produtos[MAX], int* num_produto, float preco_maquina);

void dinheiro_total(PRODUTO produtos[MAX], int* num_produto, float* preco_maquina);

void admin(PRODUTO produtos[MAX], int* num_produto, float* preco_maquina);

void main() {
    setlocale(LC_ALL, "Portuguese");
    PRODUTO produto[MAX];
    int num_produto = 0;
    char codigo_utilizador[3];
    float preco_maquina = 0; 
    
    preco_maquina = carregar_produtos(produto, &num_produto);
    
    do {
        listar_produtos(produto, &num_produto);
        printf("Digita o c�digo: ");
        fgets(codigo_utilizador, 3, stdin);
        utilizador_admin(produto, &num_produto, codigo_utilizador);
    } while (1 == 1);
}

void utilizador_admin(PRODUTO produtos[MAX], int* num_produto, char* codigo_utilizador){
	
	PRODUTO produto;
	
	if (strcmp(codigo_utilizador,"00")==0){
		admin(produtos,num_produto);
	} else{
		comprar_produto(produtos,num_produto,codigo_utilizador);
	}
}

void adicionar_produto(PRODUTO produtos[MAX], int* num_produto){
	PRODUTO produto;
	printf("Digita o c�digo do produto que quer adicionar (Ex.:A0)");
	scanf("%[^\n]s",produto.codigo);
	getchar();

	printf("Digita o nome do produto:");
	scanf("%[^\n]s",produto.nome);
	getchar();

	printf("Digita o tipo do produto:");
	scanf("%[^\n]s",produto.tipo_produto);
	getchar();
	
	printf("Digita informa��es do produto:");
	scanf("%[^\n]s",produto.info_produto.informacao);
	getchar();
	
	printf("Digita as calorias do produto:");
	scanf("%f",&produto.info_produto.calorias);
	getchar();
	
	printf("Digita a validade do produto (dd/mm/aaaa):");
	scanf("%d/%d/%d",&produto.data_validade.dia,&produto.data_validade.mes,&produto.data_validade.ano);
	getchar();
	
	printf("Digita o pre�o do produto:");
	scanf("%f",&produto.price);
	getchar();
	printf("Digita a quantidade:");
	scanf("%d",&produto.quantidade);

	produtos[*num_produto]=produto;
	(*num_produto)++;	
}

void listar_produtos(PRODUTO produtos[MAX], int* num_produto){
	int i;
	printf("\nLista de produtos: \n");
	for (i=0;i<*num_produto;i++){
		printf("\nC�digo:%s Nome:%s Tipo:%s Informa��o:%s Calorias:%.2f Data de validades:%d/%d/%d Pre�o:%.2f Quantidade:%d\n",produtos[i].codigo, 
	produtos[i].nome, produtos[i].tipo_produto, produtos[i].info_produto.informacao, produtos[i].info_produto.calorias, produtos[i].data_validade.dia,
	produtos[i].data_validade.mes,produtos[i].data_validade.ano,produtos[i].price,produtos[i].quantidade);
	}
	
}

float calculo_troco(PRODUTO produtos[MAX], int* num_produto,float preco_utilizador,int i){

	float troco,preco;
	troco=preco_utilizador - produtos[i].price;
    return troco;


    if (preco_utilizador == produtos[i].price){
        printf("\nCompra realizada com sucesso\n");
    }else if (preco_utilizador > produtos[i].price){
        printf("\nCompra realizada com sucesso\nTroco: %.2f", troco);
    }else 
        while (preco_utilizador < produtos[i].price){
            printf("Resta %.2f para finalizar a compra ", produtos[i].price - preco_utilizador);
            scanf("%f", &preco);
            preco_utilizador = preco_utilizador + preco;
            if (preco_utilizador == produtos[i].price){
            	printf("Compra realizada com sucesso\n");
            }else if (preco_utilizador>produtos[i].price){
            	printf("\nCompra realizada com sucesso\nTroco: %.2f",troco);
			}
        } 
        produtos[i].quantidade--;
    	guardar_compra(produtos,num_produto);
	}

void comprar_produto(PRODUTO produtos[MAX], int* num_produto, char* codigo_utilizador){

	float preco_utilizador,troco;
	int i;
			
	for (i=0;i<*num_produto;i++){
		if (strcmp(codigo_utilizador,produtos[i].codigo)== 0){
				if(produtos[i].quantidade!=0){
				printf("\nProduto encontrado:\n");
				printf("Insira %.2f para finalizar compra: ",produtos[i].price);
				scanf("%f",&preco_utilizador);
				getchar();
				calculo_troco(produtos,num_produto,preco_utilizador,i);
			}else{
				printf("\nPorduto esgotado!\n");
			}
		}else {
			printf("Produto esgotado!\n");
		}
	}
}



float carregar_produtos(PRODUTO produtos[MAX], int* num_produto){
	FILE *txt,*adm;
	char linha[200];
	float preco_maquina;
	
	txt = fopen("produtos.txt","r");
	
	while(fgets(linha, sizeof (linha), txt) != NULL){
		PRODUTO produto;
		sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%d/%d/%d;%f;%d",
			produto.codigo, produto.nome, produto.tipo_produto, produto.info_produto.informacao, &produto.info_produto.calorias, 
			&produto.data_validade.dia,&produto.data_validade.mes,&produto.data_validade.ano, &produto.price, &produto.quantidade);	
		produtos[*num_produto] = produto;
    	(*num_produto)++;
	}
	
	fclose(txt);
	
	adm = fopen("admin.txt", "r");
    if (adm != NULL) {
        fscanf(adm, "%f", &preco_maquina);
        fclose(adm);
    }
	return preco_maquina;
}



void guardar_produto(PRODUTO produtos[MAX],int* num_produto){
	PRODUTO produto;
	FILE *txt;
	int i;
	
	txt = fopen("produtos.txt","w");
	
	if (txt == NULL){
		printf("Erro ao abri o produtos.txt\n");
		return;
	}
	
	for (i=0;i<*num_produto;i++){
	printf("%s",produtos[i].codigo);
	fprintf(txt, "%s;%s;%s;%s;%f;%d/%d/%d;%f;%d\n", produtos[i].codigo, produtos[i].nome, produtos[i].tipo_produto,
	produtos[i].info_produto.informacao, produtos[i].info_produto.calorias, produtos[i].data_validade.dia,
	produtos[i].data_validade.mes,produtos[i].data_validade.ano,produtos[i].price,produtos[i].quantidade);
	}
	
	fclose(txt);
	
	printf("Informa��es guardadas com sucesso\n");
}


void guardar_compra(PRODUTO produtos[MAX],int* num_produto, float preco_maquina){
	PRODUTO produto;
	FILE *txt,*adm;
	int i;

	adm = fopen("admin.txt", "r");
    if (adm != NULL) {
        fscanf(adm, "%f", &preco_maquina);
        fclose(adm);
    }
	
	txt = fopen("produtos.txt","w");
	
	if (txt == NULL){
		printf("Erro ao abri o produtos.txt\n");
		return;
	}
	
	for (i=0;i<*num_produto;i++){
	fprintf(txt, "%s;%s;%s;%s;%f;%d/%d/%d;%f;%d\n", produtos[i].codigo, produtos[i].nome, produtos[i].tipo_produto,
	produtos[i].info_produto.informacao, produtos[i].info_produto.calorias, produtos[i].data_validade.dia,
	produtos[i].data_validade.mes,produtos[i].data_validade.ano,produtos[i].price,produtos[i].quantidade);
	
	preco_maquina = preco_maquina + produtos[i].price;
	
	}
	
	fclose(txt);
	
	
	adm=fopen("admin.txt","w");
	if (adm == NULL){
		printf("Erro ao abri o admin.txt\n");
		return;
	}
	
	fprintf(adm, "%.2f",preco_maquina);
	
	fclose(adm);
	}
	
void dinheiro_total(PRODUTO produtos[MAX], int* num_produto, float* preco_maquina) {
    char opcao[1];
    
    printf("Dinheiro guardado: %.2f\n", *preco_maquina);
    printf("Quer levantar? (s/n): ");
    scanf("%1s", opcao);
    
    if (strcmp(opcao, "s") == 0) {
        *preco_maquina = 0;
        guardar_compra(produtos, num_produto, *preco_maquina);
        printf("Dinheiro levantado com sucesso.\n");
    }
}

void admin(PRODUTO produtos[MAX], int* num_produto, float* preco_maquina) {
    int opcao;
    
    do {
        printf("\nEscolha a op��o:\n");
        printf("0. Sair\n");
        printf("1. Adicionar produto\n");
        printf("2. Guardar altera��es\n");
        printf("3. Listar produtos\n");
        printf("4. Mostrar dinheiro guardado\n");
        printf("5. Voltar\n");
        printf("Op��o: ");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 0:
                exit(0);
            case 1:
                adicionar_produto(produtos, num_produto);
                break;
            case 2:
                guardar_produto(produtos, num_produto);
                break;
            case 3:
                listar_produtos(produtos, num_produto);
                break;
            case 4:
                dinheiro_total(produtos, num_produto, preco_maquina);
                break;
            case 5:
                return;
            default:
                printf("Op��o inv�lida!\n");
                break;
        }
    } while (opcao != 0);
}



