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

/////////////////////////ADICIONAR PRODUTO//////////////////////////////
void adicionar_produto(PRODUTO produtos[MAX], int* num_produto){
	
	PRODUTO produto;
	
	printf("Digita o código do produto que quer adicionar (Ex.:A0)");
	scanf("%[^\n]s",produto.codigo);
	getchar();

	printf("Digita o nome do produto:");
	scanf("%[^\n]s",produto.nome);
	getchar();

	printf("Digita o tipo do produto:");
	scanf("%[^\n]s",produto.tipo_produto);
	getchar();
	
	printf("Digita informações do produto:");
	scanf("%[^\n]s",produto.info_produto.informacao);
	getchar();
	
	printf("Digita as calorias do produto:");
	scanf("%f",&produto.info_produto.calorias);
	getchar();
	
	printf("Digita a validade do produto (dd/mm/aaaa):");
	scanf("%d/%d/%d",&produto.data_validade.dia,&produto.data_validade.mes,&produto.data_validade.ano);
	getchar();
	
	printf("Digita o preço do produto:");
	scanf("%f",&produto.price);
	getchar();
	printf("Digita a quantidade:");
	scanf("%d",&produto.quantidade);

	produtos[*num_produto]=produto;
	(*num_produto)++;	
	
	guardar_produto(produtos,num_produto);
}

//////////////////////GUARDAR PRODUTO NO FICHEIRO///////////////////////////////
void guardar_produto(PRODUTO produtos[MAX],int* num_produto){
	
	PRODUTO produto;
	FILE *txt;
	int i;
	
	txt = fopen("produtos.txt","w");
	
	if (txt == NULL){
		printf("Erro ao abri o produtos.txt\n");
		return;
	}
		
	for (i = 0; i < *num_produto; i++){
	fprintf(txt, "%s;%s;%s;%s;%.2f;%02d/%02d/%02d;%.2f;%d;%d\n", produtos[i].codigo, produtos[i].nome, produtos[i].tipo_produto,
	produtos[i].info_produto.informacao, produtos[i].info_produto.calorias, produtos[i].data_validade.dia,
	produtos[i].data_validade.mes,produtos[i].data_validade.ano,produtos[i].price,produtos[i].quantidade);
	}
	
	fclose(txt);
	
	printf("\nInformações guardadas com sucesso\n");
}
////////////////////////REEABASTECER MAQUINA//////////////////////////////
void reeabastecer_maquina(PRODUTO produtos[MAX], int* num_produto){
	
	int quantidade_reeabastecida; 
	char codigo_admin[3];
	int i;
	
	listar_produtos_admin(produtos,num_produto);
	
	while (1) {
		printf("\nInsira o código do produto a reeabastecer:\n");
		scanf("%s", codigo_admin);
		
		for (i = 0; i < *num_produto; i++) {
			if (strcmp(codigo_admin, produtos[i].codigo) == 0) {
				printf("Insira a quantidade:");
				scanf("%d", &quantidade_reeabastecida);
				produtos[i].quantidade += quantidade_reeabastecida;
				guardar_produto(produtos, num_produto);
				return; 
			}
		}
		
		printf("Produto não encontrado!\n");
		printf("Deseja tentar novamente? (s/n): ");
		char opcao;
		scanf(" %c", &opcao);
		if (opcao != 's' && opcao != 'S')
			return;
	}
}

//////////////////////////LISTAR PRODUTOS PARA ADMIN DE FORMA MAIS SIMPLES/////////////////////////////////
void listar_produtos_admin(PRODUTO produtos[MAX], int* num_produto){
	
	int i;
	
	printf("\n_____________________________________________________________________________________________________________________");
	for (i = 0; i< *num_produto; i++){
		printf("\n%s|%s|%s|%s|%.2f|%d/%d/%d|%.2f|%d",
		produtos[i].codigo, produtos[i].nome, produtos[i].tipo_produto, produtos[i].info_produto.informacao, produtos[i].info_produto.calorias, 
		produtos[i].data_validade.dia,produtos[i].data_validade.mes, produtos[i].data_validade.ano, produtos[i].price, produtos[i].quantidade);
	}
	printf("\n_______________________________________________________________________________________________________________________\n");
}

//////////////////////////LISTAR PRODUTOS/////////////////////////////////
void listar_produtos(PRODUTO produtos[MAX], int* num_produto){
	
	int i;
	
	printf("\n_____________________________________________________________________________________________________________________");
	printf("\nCÓDIGO:  |  NOME DO PRODUTO:                   |  TIPO DO PRODUTO:  |  DATA DE VALIDADE:  |  PREÇO:  |  QUANTIDADE:\n");
	for (i = 0; i < *num_produto; i++){
		printf("%-10s  %-36s  %-19s  %02d/%02d/%04d            %.2f       %d\n",
		produtos[i].codigo, produtos[i].nome, produtos[i].tipo_produto, produtos[i].data_validade.dia,
		produtos[i].data_validade.mes, produtos[i].data_validade.ano, produtos[i].price, produtos[i].quantidade);
	}
	printf("______________________________________________________________________________________________________________________\n");
}

///////////////LISTAR VALIDADE DOS PRODUTOS ////////////////////////
void listar_validade_produtos(PRODUTO produtos[MAX], int* num_produto){
	
    int dia_atual, mes_atual, ano_atual, quantidade_removida;
    int i=0;
    char opcao[2];
    char codigo_admin[3];
    int produtos_excedidos = 0;
    int encontrado=0;

    printf("\nIntroduza a data atual (dd/mm/aaaa):\n ");
    scanf("%d/%d/%d", &dia_atual, &mes_atual, &ano_atual);
    getchar();
    
	do {
        if (ano_atual > produtos[i].data_validade.ano ||
            (ano_atual == produtos[i].data_validade.ano && mes_atual > produtos[i].data_validade.mes) ||
            (ano_atual == produtos[i].data_validade.ano && mes_atual == produtos[i].data_validade.mes && dia_atual >= produtos[i].data_validade.dia)) {
            
            produtos_excedidos = 1;
        }
        i++;
    } while(i!=(*num_produto));

    if (produtos_excedidos == 1) {
        printf("\nOs seguintes produtos estão fora de prazo:\n");
        printf("________________________________________________________________________________________________________________________");
        printf("\nCÓDIGO:  |  NOME DO PRODUTO:                   |  DATA DE VALIDADE:  |  QUANTIDADE:\n");
        for (i = 0; i < *num_produto; i++) {
            if (ano_atual > produtos[i].data_validade.ano ||
                (ano_atual == produtos[i].data_validade.ano && mes_atual > produtos[i].data_validade.mes) ||
                (ano_atual == produtos[i].data_validade.ano && mes_atual == produtos[i].data_validade.mes && dia_atual >= produtos[i].data_validade.dia)) {
                	printf("%-10s  %-36s  %02d/%02d/%04d            %d\n", produtos[i].codigo, produtos[i].nome, produtos[i].data_validade.dia, produtos[i].data_validade.mes, produtos[i].data_validade.ano, produtos[i].quantidade);
            	}
       		}
       		printf("________________________________________________________________________________________________________________________");
	
	while (1) {
		
        printf("\nInsira o código do produto a remover:\n");
        scanf("%2s", &codigo_admin);
        getchar();
        
        for (i = 0; i < *num_produto; i++) {
           	if (strcmp(codigo_admin, produtos[i].codigo) == 0) {
           		encontrado=1;
            	if (produtos[i].quantidade==0){
            		printf("Já não existem estes produtos (%s) na máquina\n",produtos[i].nome);
				} else {
            		do{
                	printf("Insira a quantidade a remover:\n");
                	scanf("%d", &quantidade_removida);
                	getchar();
                
                	if (produtos[i].quantidade < quantidade_removida){
                		printf("Está a remover mais produtos do que tem na máquina!\n");
					}
            	} while (quantidade_removida > produtos[i].quantidade);
            		produtos[i].quantidade -= quantidade_removida;
                	guardar_produto(produtos, num_produto);
        	}
   		} 
	}
	if (encontrado==1){
		break;
		}else {
			printf("Produto não encontrado!\n");
        	printf("Deseja tentar novamente? (s/n): ");
        	char opcao;
        	scanf(" %c", &opcao);
        	getchar();
        	if (opcao != 's' && opcao != 'S') {
        		break;
    		}
		}
	}	
	}
		
    printf("\nNão há produtos fora de prazo. Deseja verificar a validade dos produtos em stock? (Sim(s)/Não(n))\n");
    scanf("%c", opcao);
    getchar();
    if (opcao != 's' && opcao != 'S') {
           	listar_produtos_admin(produtos, num_produto);   
	} else {
			return;
	}
}

////////////////////GUARDAR COMPRA NO FICHEIRO//////////////////////////////////
void guardar_compra(PRODUTO produtos[MAX], int* num_produto, float total_dinheiro){
	FILE *txt, *adm;
	int i;
	
	txt = fopen("produtos.txt","w");
	if (txt == NULL){
		printf("Erro ao abrir o produtos.txt\n");
		return;
	}

	for (i=0; i< *num_produto; i++){
		fprintf(txt, "%s;%s;%s;%s;%f;%d/%d/%d;%f;%d\n", produtos[i].codigo, produtos[i].nome, produtos[i].tipo_produto,
				produtos[i].info_produto.informacao, produtos[i].info_produto.calorias, produtos[i].data_validade.dia,
				produtos[i].data_validade.mes, produtos[i].data_validade.ano, produtos[i].price, produtos[i].quantidade);
	}

	fclose(txt);

	total_dinheiro = total_dinheiro + produtos[i].price;
	adm = fopen("admin.txt","w");
	if (adm == NULL){
		printf("Erro ao abrir o admin.txt\n");
		return;
	} else {
		fprintf(adm, "%.2f", total_dinheiro);
	}

	fclose(adm);
}

/////////////////////CALCULO TROCO////////////////////////////////
void calculo_troco(PRODUTO produtos[MAX], int* num_produto, float preco_utilizador, int i, float dinheiro_total){
	float troco;
	troco = preco_utilizador - produtos[i].price;

	if (preco_utilizador == produtos[i].price){
		printf("\nCompra realizada com sucesso\n");
	} else if (preco_utilizador > produtos[i].price){
		printf("\nCompra realizada com sucesso\nTroco: %.2f\n", troco);
	} else {
		while (preco_utilizador < produtos[i].price){
			float preco;
			printf("Restam %.2f para finalizar a compra ", produtos[i].price - preco_utilizador);
			scanf("%f", &preco);
			getchar();
			preco_utilizador += preco;
			if (preco_utilizador == produtos[i].price){
				printf("\nCompra realizada com sucesso\n");
			} else if (preco_utilizador > produtos[i].price){
				printf("\nCompra realizada com sucesso\nTroco: %.2f", troco);
			}
		}
	}
	produtos[i].quantidade--;
	guardar_compra(produtos, num_produto, dinheiro_total);
}

///////////////////////COMPRAR PRODUTO////////////////////////////
void comprar_produto(PRODUTO produtos[MAX], int* num_produto, char* codigo_utilizador, float dinheiro_total){
	
	float preco_utilizador;
	int i;
	char opcao[2];
			
	for (i = 0 ; i < *num_produto; i++){
		if (strcmp(codigo_utilizador,produtos[i].codigo)== 0){
			if(produtos[i].quantidade!=0){
				printf("Produto encontrado! Quer saber mais informações do produto?(s/n): ");
				scanf(" %c",&opcao);
				getchar();
				if (opcao != 'n' && opcao != 'N'){
					printf("Informações de %s:\n", produtos[i].nome);
					printf("Descrição: %s\n",produtos[i].info_produto.informacao);
					printf("Calorias: %.2f\n", produtos[i].info_produto.calorias);
					printf("Insira %.2f para finalizar compra: ",produtos[i].price);
					scanf("%f",&preco_utilizador);
					getchar();
					calculo_troco(produtos, num_produto, preco_utilizador, i, dinheiro_total);
				} else {
					printf("Insira %.2f para finalizar compra: ",produtos[i].price);
					scanf("%f",&preco_utilizador);
					getchar();
					calculo_troco(produtos, num_produto, preco_utilizador, i, dinheiro_total);
				}
			}else{
				printf("Produto esgotado!\n");
				printf("Quer comprar outro produto?(s/n): ");
				scanf(" %c", &opcao);
				if (opcao == 's' && opcao == 'S')
				main ();
			}
		}else {
			printf("Produto não encontrado!\n");
			printf("Quer comprar outro produto?(s/n): ");
			scanf(" %c", &opcao);
			if (opcao == 's' && opcao == 'S'){
			main ();
			}
		}
	}
}

/////////////////////CARREGAR PRODUTOS DO FICHEIRO//////////////////////////////
void carregar_produtos(PRODUTO produtos[MAX], int* num_produto){
	FILE *txt;
	char linha[200];
	
	txt = fopen("produtos.txt","r");
	
	if (txt==NULL){
		printf("Erro na arbertura do arquivo!\n");
		exit(1);
	}
	
	while(fgets(linha, sizeof (linha), txt) != NULL){
		PRODUTO produto;
		sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%d/%d/%d;%f;%d",
			produto.codigo, produto.nome, produto.tipo_produto, produto.info_produto.informacao, &produto.info_produto.calorias, 
			&produto.data_validade.dia,&produto.data_validade.mes,&produto.data_validade.ano, &produto.price, &produto.quantidade);	
		produtos[*num_produto] = produto;
    	(*num_produto)++;
	}
	
	fclose(txt);
}

/////////////////////LEVANTAR DINHEIRO ACUMULADO//////////////////////////////	
void levantar_dinheiro() {
    FILE *adm;
    char opcao[1];
    float dinheiro;

    adm = fopen("admin.txt", "r");
    if (adm == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return 0;
    } else {
        fscanf(adm, "%f", &dinheiro);
        fclose(adm);
    }

    printf("Dinheiro guardado: %.2f\n", dinheiro);
    printf("Quer levantar? (s/n): ");
    scanf("%c", opcao);
    getchar();

    if (opcao == 's' && opcao == 'S') {
        adm = fopen("admin.txt", "w");
        dinheiro = 0;
        fprintf(adm, "%.2f", dinheiro);
        fclose(adm);
        printf("Dinheiro levantado com sucesso.\n");
    } else {
        return dinheiro;
    }
}

/////////////////////CARREGAR DINHEIRO DO FICHEIRO//////////////////////////////	
float carregar_dinheiro() {
    FILE *adm;
    char opcao[1];
    float dinheiro;

    adm = fopen("admin.txt", "r");
    if (adm == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return 0;
    } else {
        fscanf(adm, "%f", &dinheiro);
        fclose(adm);
    }
        return;
    }

/////////////////////ATUALIZAR PREÇO DE UM PRODUTO//////////////////////////////	
void atualizar_preco_produto(PRODUTO produtos[MAX], int* num_produto) {
    char codigo[5];
    int i;
    float price;
    char opcao;

	while (1){
		listar_produtos_admin(produtos, num_produto);
    	printf("\nQual o produto que desejas alterar o preco: ");
    	scanf("%s",codigo);
    	getchar();
    	for (i = 0; i < *num_produto; i++) {
        	if (strcmp(codigo, produtos[i].codigo) == 0) {
            	do {
            		printf("\nQual é o novo preço do produto %s: ", produtos[i].nome);
               		scanf("%f", &price);
                	getchar();
            	} while ( price < 0 || price > 100);
            	produtos[i].price = price;
            	guardar_produto(produtos, num_produto);
            	printf("Quer alterar o preço de mais produtos? (s/n): ");
            	scanf(" %c",&opcao);
            	if (opcao !='s' && opcao != 'S')
            	return; 
        	}
        	else{
			printf("Produto não encontrado!\n");
			printf("Deseja tentar novamente? (s/n): ");
			scanf(" %c", &opcao);
			if (opcao != 's' && opcao != 'S')
			return;	
			}
		}
	}
}

/////////////////////ATUALIZAR PREÇO DE VÁRIOS PRODUTOS//////////////////////////////	
void atualizar_preco_todos_produtos(PRODUTO produtos[MAX], int* num_produto){
	float inflacao;
	int i;
	
	do{
	   printf("Qual é a percentagem da inflação (1 á 100): \n");
	   scanf("%f",&inflacao);
	   getchar();
	   
		if (inflacao <0 || inflacao >100){
			printf("A inflaçõa deve ser um valor entre 1 a 100\n");
	   	}	
	}while( inflacao < 0 || inflacao > 100);
	
	for(i = 0; i < *num_produto; i++){
		printf("\n%f  \t  %s",produtos[i].price,produtos[i].nome);
		produtos[i].price= produtos[i].price + (inflacao/100)*produtos[i].price;
		
	}
	
	guardar_produto(produtos, num_produto);	
}

/////////////////////UTILIZADOR ADMIN//////////////////////////////
void utilizador_admin(PRODUTO produtos[MAX], int* num_produto, char* codigo_utilizador, float dinheiro_total){
	
	PRODUTO produto;
	
	if (strcmp(codigo_utilizador,"00")==0){
		admin(produtos,num_produto, dinheiro_total);
	} else{
		comprar_produto(produtos,num_produto,codigo_utilizador, dinheiro_total);
	}
}

/////////////////////MENU ADMIN////////////////////////////////////
void admin(PRODUTO produtos[MAX], int* num_produto,float dinheiro_total){
	
	int opcao_admin;

	do {
		printf("\n*********Menu Admin***********");
		printf("\nEscolha a opção:\n");
		printf("0. Sair\n");
		printf("1. Adicionar produto\n");
		printf("2. Listar produtos\n");
		printf("3. Reeabastecer máquina\n");
		printf("4. Listar validade dos produtos\n");
		printf("5. Atualizar preço de um produto\n");
		printf("6. Atualizar preço de todos os produtos\n");
		printf("7. Mostrar dinheiro guardado\n");
		printf("8. Voltar\n");
		printf("Opção: ");
		scanf("%d", &opcao_admin);
		getchar();
		
		switch (opcao_admin) {
			case 0:
				exit(0);
			case 1:
				adicionar_produto(produtos,num_produto);
				break;
			case 2:
				listar_produtos_admin(produtos,num_produto);
				break;
			case 3:
				reeabastecer_maquina(produtos,num_produto);
				break;
			case 4:
				listar_validade_produtos(produtos,num_produto);
				break;
			case 5:
				atualizar_preco_produto(produtos, num_produto);
				break;
			case 6:
				atualizar_preco_todos_produtos(produtos, num_produto);
				break;
			case 7:
				levantar_dinheiro();
				break;
			case 8:
				return;
			default:
				printf("Opção inválida!\n");
				break;
		}
	} while (opcao_admin != 0);
}


void main() {
    setlocale(LC_ALL, "Portuguese");
    PRODUTO produto[MAX];
    int num_produto = 0;
    char codigo_utilizador[3];
    
	carregar_produtos(produto, &num_produto);
	float dinheiro_total = carregar_dinheiro();
    
    do {
        printf("************************************************CNR.Lda*****************************************************************");
        listar_produtos(produto, &num_produto);
        
        printf("Digita o código do produto: ");
        scanf("%s",&codigo_utilizador);
        getchar();
        
        utilizador_admin(produto, &num_produto, codigo_utilizador, dinheiro_total);
    } while (1);  
}
