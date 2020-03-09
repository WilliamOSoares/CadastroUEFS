//Feira de Graduação da UEFS//
/*******************************************************************************
Autor: William Oliveira Soares
Componente Curricular: MI Algoritmos I
Concluido em: 25/11/2017
Declaro que este código foi elaborado por mim de forma individual e não contém nenhum
trecho de código de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código
de outra autoria que não a minha está destacado com uma citação para o autor e a fonte
do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.
******************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/**********************************
Essa struct serve para armazenar os
nomes e os cargos dos proponentes.
***********************************/
typedef struct{
	char cargo[15];
	char nome_do_proponente[125];
}PROPONENTES;
/*****************************************************************************
Esta a struct a seguir tem dados relacionados a proposta dos proponente e uma 
varivel de seleção que será melhor explicada no decorrer do codigo.
*****************************************************************************/
typedef struct {
	char nome_da_proposta[125];
	PROPONENTES proponentes[5];
	char tipo_de_apresentacao[13];
	int data, horario, imprime;
}PROPOSTA;
/**********************************************
A struct abaixo contém todas as outras structs
, e esta struct será manipulada no código.
**********************************************/
typedef struct{
	char curso[45];
	PROPOSTA propostas[10];
}DADOS;
	// Funções
void calculos(int x, DADOS inscricao[10], char cursos_da_uefs[][45], char tipo_de_apresentacoes[][12], FILE *file); 
// faz os calculos de representatividade, tipos de apresentação nos dias 23 e 24, e imprime no arquivo.
void linha (); // Exibirá uma linha: "____".
void preenchimento(char cursos_da_uefs[][45]);	// Preenchimento de uma matriz que irá conter os nomes dos cursos.
int comparacao(char cursos_da_uefs[][45], char curso[]); // Comparação do nome recebido pelo usuario com a matriz de cursos.
void SegundoPreenchimento(char tipo_de_apresentacoes[][12]); // Preenchimento da matriz dos tipos de apresentação.
int SegundaComparacao(char tipo_de_apresentacoes[][12], char curso[]); // Comparação do nome recebido pelo usuario com a matriz dos tipos de apresentações.
void texto (int quant_curs_fixa, DADOS inscricao[100], char cursos_da_uefs[][45], char tipo_de_apresentacoes[][12]); 
// Abre o arquivo .txt, escreve todas as informações, e fecha o arquivo.

int main(void){

int quant_cursos, quant_curs_fixa, cargos, mais_cadastro = 10, i=0, j=0, k=0, l=0, resultado = 10; // Variáveis de manipulação.
DADOS inscricao[28]; // Banco de dados do código.
char cursos_da_uefs[28][45], tipo_de_apresentacoes[4][12]; // Matrizes de curso e dos tipos de apresentação.
char datadebug[5], horariodebug[5], cargodebug[5], maisdebug[5], cursodebug[5]; // Variaveis de conversão.

//As 2 linhas a seguir preencherá as matrizes de cursos e dos tipos de apresentação
preenchimento(cursos_da_uefs); 
SegundoPreenchimento(tipo_de_apresentacoes);

do{
	linha(); // Chamada da função que exibirá uma linha na tela
	printf("\t      Quantos cursos participarao do evento:\n");
	linha();
	setbuf(stdin, NULL); // Esta linha aloca o buffer do teclado e tranforma em nulo, é equivalente a fflush.
	scanf("%s", cursodebug);
	quant_cursos = atoi(cursodebug);
		/************************************************
		A função atoi coverte o char em int, sendo assim, 
		 não causará um looping infinito impedindo que o 
		 usuario digite, fazendo-o fechar o programa
		************************************************/
	if(quant_cursos<=0) // tratamento de erro
		printf("\a\t\t\t    ATENCAO\n-> Verifique se esta digitado corretamente\n");
}while(quant_cursos<=0);
	quant_curs_fixa = quant_cursos;
/* A seguir está o laço de repetição do cadastro de propostas*/	
do{	
	do {
		linha(); 
		printf("\t\t  De qual curso eh a proposta:\n");
		linha();
		setbuf(stdin, NULL); 
		scanf("%[^\n]", inscricao[i].curso);
		resultado = comparacao(cursos_da_uefs, inscricao[i].curso); // comparação do que foi recebido com o que está armazenado.
		if(resultado != 1) 
			printf("\a\t\t\t    ATENCAO\n-> Verifique se esta digitado corretamente!\n");
	} while(resultado != 1);
				
	do{ //Laço de repetição das propostas.
		linha();
		printf("\t\t   Escreva o nome da proposta:\n");
		linha();
		setbuf(stdin, NULL);
		scanf("%[^\n]", inscricao[i].propostas[j].nome_da_proposta);

		do{	
			linha();
			printf("\tEm que dia sera a apresentacao, dia 23 ou dia 24?\n");
			linha();
			setbuf(stdin, NULL);
			scanf("%s", datadebug);
			inscricao[i].propostas[j].data = atoi(datadebug);
			if(inscricao[i].propostas[j].data != 23 && inscricao[i].propostas[j].data != 24)
				printf("\a\t\t\t    ATENCAO\n-> Verifique se o dia foi digitado corretamente o dia!\n");
		}while(inscricao[i].propostas[j].data != 23 && inscricao[i].propostas[j].data != 24);
				
		do{	
			linha();
			printf("\t    Qual sera o horario da apresentacao?\n");
			linha();
			setbuf(stdin, NULL);
			scanf("%s", horariodebug);
			inscricao[i].propostas[j].horario = atoi(horariodebug);
			if(inscricao[i].propostas[j].horario > 20 || inscricao[i].propostas[j].horario < 8)
				printf("\a\t\t\t    ATENCAO\n-> So pode de 8 as 20 horas\n");
		}while(inscricao[i].propostas[j].horario > 20 || inscricao[i].propostas[j].horario < 8);
				
		do{
			resultado =10; // Redefinição de resultado para não dar problema.
			linha();
			printf("\t\t Que tipo de apresentacao sera?\n");
			linha();
			setbuf(stdin, NULL);
			scanf("%[^\n]", inscricao[i].propostas[j].tipo_de_apresentacao);
			resultado = SegundaComparacao(tipo_de_apresentacoes, inscricao[i].propostas[j].tipo_de_apresentacao);
			if(resultado != 1)
				printf("\a\t\t\t    ATENCAO\n-> Verifique se esta digitado igualmente a estes!\nOral\nOficina\nPoster\nLaboratorio\n");
		}while(resultado != 1);
			
		for(k = 0; k < 5; k++){ // 'k' é o numero maximo de proponentes.
			if (k==1 && cargos==3) 
				k=0;
			do{
				linha();
				printf("\t\t    Cargo do proponente:\n1 - Professor \n2 - aluno\n3 - Nao ha mais proponentes\n");
				linha();
				setbuf(stdin, NULL);
				scanf("%s", cargodebug);
				cargos = atoi(cargodebug);
				/******************************************************* 
				Os blocos a seguir comparam a resposta do usuario e 
				 se a resposta se adequar com o que foi pedido, a função
				 strcpy "enviará" o cargo para a variável na struct.
				*******************************************************/
				if(cargos == 1)
					strcpy(inscricao[i].propostas[j].proponentes[k].cargo, "Professor(a)");
				else if(cargos == 2)
					strcpy(inscricao[i].propostas[j].proponentes[k].cargo, "Aluno(a)");
				else if(cargos == 3)
					strcpy(inscricao[i].propostas[j].proponentes[k].cargo, "Acabou");
				else
					printf("\a\t\t\t    ATENCAO\n-> So pode ser digitado 1 ou 2 ou 3!\n");
				if(k == 0 && cargos == 3) // isso é se o usuario nao colocar nenhum proponente
					printf("\a\t\t\t    ATENCAO\n-> Tem que ter pelo menos 1 proponente!\n");
				/* Isso é se o usuario não colocar um proponente se quer, então motrará
				 a mensegem de erro, na linha 134, tem uma comparação, se o usuario não colocou
				 nenhum proponente na primeira pergunta, ele vai zerar a variável de contagem
				 de proponentes cadastrados*/
			}while(!(cargos == 1 || cargos == 2 || cargos == 3));
			if(cargos == 1 || cargos == 2){
				setbuf(stdin, NULL);
				linha();
				printf("\t\t    Nome do proponente:\n");
				linha();
				setbuf(stdin, NULL);
				scanf("%[^\n]", inscricao[i].propostas[j].proponentes[k].nome_do_proponente);
			}
			else if (k!=0 && cargos==3)
				k=5;
		}
		system("cls"); // Limpa a tela.
		do{
			linha();
			printf("\t\tQuer cadastrar mais uma proposta?\n1 - SIM\n2 - NAO\n");
			linha();
			setbuf(stdin, NULL);
			scanf("%s", maisdebug);
			mais_cadastro = atoi(maisdebug);
			if(mais_cadastro != 1 && mais_cadastro != 2)
				printf("\a\t\t\t    ATENCAO\n-> So pode ser digitado 1 ou 2!\n");
		}while(mais_cadastro != 1 && mais_cadastro != 2);
		j++; 
		/* 'j' é o indice do vetor de propostas que esta dentro da struct principal, 
		adição na variável que determina a quantidade maxima de propostas*/
	}while(mais_cadastro==1 && j<10);
	i++; // 'i' é o indice do vetor da struct principal.
	j = 0; // Redefinição da variável para previnir o erro.
	quant_cursos--; // Decremento da variável que indica quantas vezes fará a repetição do código.
}while(quant_cursos>0);
	
	for(i=0;i<quant_curs_fixa;i++){
		for(j=9; j>=0; j--){
			for(l=0;l != j;l++){
				if(inscricao[i].propostas[j].data == inscricao[i].propostas[l].data){
					if(inscricao[i].propostas[j].horario == inscricao[i].propostas[l].horario){
						inscricao[i].propostas[j].imprime = 100;
					}
				}
			}
		}
	}
	/*************************************************************************************************************************
	A cima contém um algoritmo que comprará a data e o horario das propostas se estão iguais, se estiverem iguais, atribuirá
	 100 a variável imprime, sendo que está variável determina que o primeiro com horário seja impresso e os demais, que 
	 estarão com a variável igual a 100, não serão impressos. A variável j percorre o vetor de propostas do maior ao menor e 
	 o 'l' percorre do menor para o j, ou seja, o j estará fixo e comparando com os antecessores determinados por l, se for 
	 encontrado uma igualdade, a proposta equivalente ao indice de j será descartada na impressão.
	 *************************************************************************************************************************/
texto(quant_curs_fixa, inscricao, cursos_da_uefs, tipo_de_apresentacoes); // Saída do arquivo.
system("pause");
return 0;
}

void linha (){
	printf("------------------------------------------------------------------\n");
}

void texto (int quant_curs_fixa, DADOS inscricao[100], char cursos_da_uefs[][45], char tipo_de_apresentacoes[][12]){
	FILE *file;
	char nome[200], tipo[] = ".txt";
	printf("Qual sera o nome do arquivo:\n");
	setbuf(stdin, NULL);
	scanf("%[^\n]", nome);
	strcat(nome,tipo); // nome.txt
	file = fopen(nome, "w"); // abrindo o arquivo para escrita.
	if(file == NULL)
		printf("\aError 404\n Arquivo nao encontrado!\n");
	/**********************************************
	O trecho abaixo irá escrever toda a struct
	no arquivo de texto, descartando as propostas 
	que contém choque de horário e depois fecha-lo.
	***********************************************/
	int i, j, k;
	for(i = 0; i < quant_curs_fixa; i++){
		fprintf(file, "%s\n", inscricao[i].curso);
		fprintf(file, "------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		for (j = 0; j < 10; j++){ 
			if(inscricao[i].propostas[j].imprime != 100){
				fprintf(file, "%s\n", inscricao[i].propostas[j].nome_da_proposta);
				fprintf(file, "%s\n", inscricao[i].propostas[j].tipo_de_apresentacao);
				fprintf(file, "Dia: %d\n", inscricao[i].propostas[j].data);
				fprintf(file, "Horario: %d hrs\n", inscricao[i].propostas[j].horario);
				for(k = 0; k < 5; k++){
					if (strcmp(inscricao[i].propostas[j].proponentes[k].cargo, "Acabou") != 0)
						fprintf(file, "%s - %s\n", inscricao[i].propostas[j].proponentes[k].cargo, inscricao[i].propostas[j].proponentes[k].nome_do_proponente);
				}
				fprintf(file, "------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			}	
			if(inscricao[i].propostas[j+1].data == 0 && inscricao[i].propostas[j+2].data == 0)
				j = 10; // se não tiver mais propostas cadastradas, esse comando "força" o fechamento do laço de repetição.
		}
	}
	calculos(quant_curs_fixa, inscricao, cursos_da_uefs, tipo_de_apresentacoes, &*file);
	/**********************************************************
	O trecho abaixo irá escrever todas as propostas ofertadas 
	 apenas por estudantes, o algoritmo compará todos os nomes.
	**********************************************************/
	fprintf(file, "------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	fprintf(file, "Proposta ofertada apenas por estudantes:\n");
	for(i=0;i<quant_curs_fixa;i++){
		for(j=0; j<10; j++){	
			k=0;
			if(inscricao[i].propostas[j].imprime != 100){
				if(strcmp(inscricao[i].propostas[j].proponentes[k].cargo, "Aluno(a)")==0){
					if(strcmp(inscricao[i].propostas[j].proponentes[k+1].cargo, "Acabou")==0)
						fprintf(file, "%s\n", inscricao[i].propostas[j].nome_da_proposta);
					else if (strcmp(inscricao[i].propostas[j].proponentes[k].cargo, inscricao[i].propostas[j].proponentes[k+1].cargo)==0){
						if(strcmp(inscricao[i].propostas[j].proponentes[k+2].cargo, "Acabou")==0)
							fprintf(file, "%s\n", inscricao[i].propostas[j].nome_da_proposta);
						else if (strcmp(inscricao[i].propostas[j].proponentes[k+1].cargo, inscricao[i].propostas[j].proponentes[k+2].cargo)==0){
							if(strcmp(inscricao[i].propostas[j].proponentes[k+3].cargo, "Acabou")==0)
								fprintf(file, "%s\n", inscricao[i].propostas[j].nome_da_proposta);
							else if (strcmp(inscricao[i].propostas[j].proponentes[k+2].cargo, inscricao[i].propostas[j].proponentes[k+3].cargo)==0){
								if(strcmp(inscricao[i].propostas[j].proponentes[k+4].cargo, "Acabou")==0)
									fprintf(file, "%s\n", inscricao[i].propostas[j].nome_da_proposta);
								else if (strcmp(inscricao[i].propostas[j].proponentes[k+3].cargo, inscricao[i].propostas[j].proponentes[k+4].cargo)==0){
									fprintf(file, "%s\n", inscricao[i].propostas[j].nome_da_proposta);
								}
							}
						}	
					}
				}
			}
		}
	}
	fclose(file);
}

void preenchimento(char cursos_da_uefs[28][45]) {
	/*******************************************
	O trecho abaixo irá escrever todos os cursos
	da UEFS em uma matriz por meio do comando da
	biblioteca string.h, o strcpy.
	********************************************/
	strcpy(cursos_da_uefs[0], "Administracao");
	strcpy(cursos_da_uefs[1], "Agronomia");
	strcpy(cursos_da_uefs[2], "Bacharelado em Ciencias Biologicas");
	strcpy(cursos_da_uefs[3], "Ciencias Contabeis");
	strcpy(cursos_da_uefs[4], "Ciencias Economicas");
	strcpy(cursos_da_uefs[5], "Direito");
	strcpy(cursos_da_uefs[6], "Enfermagem");
	strcpy(cursos_da_uefs[7], "Engenharia Civil");
	strcpy(cursos_da_uefs[8], "Engenharia de Alimentos");
	strcpy(cursos_da_uefs[9], "Engenharia de Computacao");
	strcpy(cursos_da_uefs[10], "Farmacia");
	strcpy(cursos_da_uefs[11], "Licenciatura e Bacharelado em Filosofia");
	strcpy(cursos_da_uefs[12], "Licenciatura e Bacharelado em Geografia");
	strcpy(cursos_da_uefs[13], "Licenciatura em Letras com Frances");
	strcpy(cursos_da_uefs[14], "Licenciatura em Letras com Ingles");
	strcpy(cursos_da_uefs[15], "Licenciatura em Letras Vernaculas");
	strcpy(cursos_da_uefs[16], "Licenciatura em Letras Portugues e Espanhol");
	strcpy(cursos_da_uefs[17], "Licenciatura em Quimica");
	strcpy(cursos_da_uefs[18], "Licenciatura e Bacharelado em Fisica");
	strcpy(cursos_da_uefs[19], "Licenciatura em Ciencias Biologicas");
	strcpy(cursos_da_uefs[20], "Licenciatura em Educacao Fisica");
	strcpy(cursos_da_uefs[21], "Licenciatura em Historia");
	strcpy(cursos_da_uefs[22], "Licenciatura em Matematica");
	strcpy(cursos_da_uefs[23], "Licenciatura em Musica");
	strcpy(cursos_da_uefs[24], "Licenciatura em Pedagogia");
	strcpy(cursos_da_uefs[25], "Medicina");
	strcpy(cursos_da_uefs[26], "Odontologia");
	strcpy(cursos_da_uefs[27], "Psicologia");
}

void SegundoPreenchimento(char tipo_de_apresentacoes[4][12]){
	/********************************************
	O trecho abaixo irá escrever todos os tipos
	de apresentações que pode ocorrer na feira em 
	uma matriz por meio do comando da biblioteca 
	string.h, o strcpy.
	*********************************************/
	strcpy(tipo_de_apresentacoes[0], "Oral");
	strcpy(tipo_de_apresentacoes[1], "Oficina");
	strcpy(tipo_de_apresentacoes[2], "Poster");
	strcpy(tipo_de_apresentacoes[3], "Laboratorio");
}

int comparacao(char cursos_da_uefs[][45], char curso[]) {
	int j=0; // J é o indice das linhas da matriz de cursos.
	for(j=0; j<28; j++) {
		if(strcmp(curso, cursos_da_uefs[j])==0) { // comparação da string do usuario com os indices da matriz de cursos.
			return 1; // se forem iguais.
		}
	}
	return 0; // se forem diferentes.}
}

int SegundaComparacao(char tipo_de_apresentacoes[][12], char curso[]) {
	int j=0; // J é o indice das linhas da matriz do tipos de apresentações.
	for(j=0; j<4; j++) { 
		if(strcmp(curso, tipo_de_apresentacoes[j])==0) { // comparação da string do usuario com os indices da matriz do tipos de apresentações.
			return 1; // se forem iguais.
		}
	}	
	return 0; // se forem diferentes.
}
void calculos(int x, DADOS inscricao[10], char cursos_da_uefs[][45], char tipo_de_apresentacoes[][12], FILE *file){	
	int i, j, vetorA[28], vetorB[4], vetorC[4];
	for (i = 0; i < 28; i++){
		vetorA[i] = 0;
	}
	for (i = 0; i < 4; i++){
		vetorB[i] = 0;
		vetorC[i] = 0;
	} // Nos 2 for's acima, irão zerar todos os valores dos vetores.
	/**********************************************************************
	Abaixo, faz a atribuições de quantas propostas tem em cada curso, 
	 atribuindo os valores aos indices correspondente a ordem em que 
	 os cursos foram listados, na linha 442 em diante tem a mesmas logica,
	 mas para os tipos de apresentação em cada dia, infelizmente não 
	 foi feita a modularização dessa parte, porque o tempo foi escasso
	 **********************************************************************/
	for(i = 0; i < x; i++){
		for(j = 0; j < 10; j++){
			if(inscricao[i].propostas[j].imprime != 100){
				if(inscricao[i].propostas[j].data == 23 || inscricao[i].propostas[j].data == 24){
					if (strcmp(inscricao[i].curso, "Administracao")==0)
						vetorA[0] = j+1;
					else if (strcmp(inscricao[i].curso, "Agronomia")==0)
						vetorA[1] = j+1;
					else if (strcmp(inscricao[i].curso, "Bacharelado em Ciencias Biologicas")==0)
						vetorA[2] = j+1;
					else if (strcmp(inscricao[i].curso, "Ciencias Contabeis")==0)
						vetorA[3] = j+1;
					else if (strcmp(inscricao[i].curso, "Ciencias Economicas")==0)
						vetorA[4] = j+1;
					else if (strcmp(inscricao[i].curso, "Direito")==0)
						vetorA[5] = j+1;
					else if (strcmp(inscricao[i].curso, "Enfermagem")==0)
						vetorA[6] = j+1;
					else if (strcmp(inscricao[i].curso, "Engenharia Civil")==0)
						vetorA[7] = j+1;
					else if (strcmp(inscricao[i].curso, "Engenharia de Alimentos")==0)
						vetorA[8] = j+1;
					else if (strcmp(inscricao[i].curso, "Engenharia de Computacao")==0)
						vetorA[9] = j+1;
					else if (strcmp(inscricao[i].curso, "Farmacia")==0)
						vetorA[10] = j+1;
					else if (strcmp(inscricao[i].curso, "Licenciatura e Bacharelado em Filosofia")==0)
						vetorA[11] = j+1;
					else if (strcmp(inscricao[i].curso, "Licenciatura e Bacharelado em Geografia")==0)
						vetorA[12] = j+1;
					else if (strcmp(inscricao[i].curso, "Licenciatura em Letras com Frances")==0)
						vetorA[13] = j+1;
					else if (strcmp(inscricao[i].curso, "Licenciatura em Letras com Ingles")==0)
						vetorA[14] = j+1;
					else if (strcmp(inscricao[i].curso, "Licenciatura em Letras Vernaculas")==0)
						vetorA[15] = j+1;
					else if (strcmp(inscricao[i].curso, "Licenciatura em Letras Portugues e Espanhol")==0)
						vetorA[16] = j+1;
					else if (strcmp(inscricao[i].curso, "Licenciatura em Quimica")==0)
						vetorA[17] = j+1;
					else if (strcmp(inscricao[i].curso, "Licenciatura e Bacharelado em Fisica")==0)
						vetorA[18] = j+1;
					else if (strcmp(inscricao[i].curso, "Licenciatura em Ciencias Biologicas")==0)
						vetorA[19] = j+1;
					else if (strcmp(inscricao[i].curso, "Licenciatura em Educacao Fisica")==0)
						vetorA[20] = j+1;
					else if (strcmp(inscricao[i].curso, "Licenciatura em Historia")==0)
						vetorA[21] = j+1;
					else if (strcmp(inscricao[i].curso, "Licenciatura em Matematica")==0)
						vetorA[22] = j+1;
					else if (strcmp(inscricao[i].curso, "Licenciatura em Musica")==0)
						vetorA[23] = j+1;
					else if (strcmp(inscricao[i].curso, "Licenciatura em Pedagogia")==0)
						vetorA[24] = j+1;
					else if (strcmp(inscricao[i].curso, "Medicina")==0)
						vetorA[25] = j+1;
					else if (strcmp(inscricao[i].curso, "Odontologia")==0)
						vetorA[26] = j+1;
					else if (strcmp(inscricao[i].curso, "Psicologia")==0)
						vetorA[27] = j+1;
				}
				else
					j=10;
			}
		}
	}
	for(i = 0; i < x; i++){
		for(j = 0; j < 10; j++){
			if(inscricao[i].propostas[j].imprime != 100){
				if(inscricao[i].propostas[j].data == 23){
					if (strcmp(inscricao[i].propostas[j].tipo_de_apresentacao, "Oral")==0)
						vetorB[0] = vetorB[0]+1;
					else if (strcmp(inscricao[i].propostas[j].tipo_de_apresentacao, "Oficina")==0)
						vetorB[1] = vetorB[1]+1;
					else if (strcmp(inscricao[i].propostas[j].tipo_de_apresentacao, "Poster")==0)
						vetorB[2] = vetorB[2]+1;
					else if (strcmp(inscricao[i].propostas[j].tipo_de_apresentacao, "Laboratorio")==0)
						vetorB[3] = vetorB[3]+1;
					else
						fprintf(file, "\aNao foi possivel fazer operacao\n");
				}
				else if(inscricao[i].propostas[j].data == 24){
					if (strcmp(inscricao[i].propostas[j].tipo_de_apresentacao, "Oral")==0)
						vetorC[0] = vetorC[0]+1;
					else if (strcmp(inscricao[i].propostas[j].tipo_de_apresentacao, "Oficina")==0)
						vetorC[1] = vetorC[1]+1;
					else if (strcmp(inscricao[i].propostas[j].tipo_de_apresentacao, "Poster")==0)
						vetorC[2] = vetorC[2]+1;
					else if (strcmp(inscricao[i].propostas[j].tipo_de_apresentacao, "Laboratorio")==0)
						vetorC[3] = vetorC[3]+1;
					else
						fprintf(file, "\aNao foi possivel fazer operacao\n");
				}
			}
		}
	}
	/*******************************************************************
	Abaixo, ocorrerá a comparação de representatividade e tipos de 
	 apresentação em cada dia e a impressão dos resultados da comparação
	 *******************************************************************/
	int res = 0, res2;
	for (i = 0; i < 28; i++){
		if (vetorA[i]>res){
			res = vetorA[i];
			res2 = i;
		}
	}
	fprintf(file, "Maior representatividade:\n");
	for (i = 0; i < 28; i++){
		if (vetorA[res2]==vetorA[i]){
			fprintf(file, "%s\n", cursos_da_uefs[i]);
		}
	}
	fprintf(file, "------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	int res3 = 100, res4;
	for (i = 0; i < 28; i++){
		if (vetorA[i]<res3 && vetorA[i] != 0){
			res3 = vetorA[i];
			res4 = i;
		}
	}
	fprintf(file, "Menor representatividade:\n");
	for (i = 0; i < 28; i++){
		if (vetorA[res4]==vetorA[i]){
			fprintf(file, "%s\n", cursos_da_uefs[i]);
		}
	}

	fprintf(file, "------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	fprintf(file, "Quantidade de cada tipo de apresentacao do dia 23\n");
	fprintf(file, "Oral:%d\n", vetorB[0]);
	fprintf(file, "Oficina:%d\n", vetorB[1]);
	fprintf(file, "Poster:%d\n", vetorB[2]);
	fprintf(file, "Laboratorio:%d\n", vetorB[3]);
	fprintf(file, "------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	fprintf(file, "Quantidade de cada tipo de apresentacao do dia 24\n");
	fprintf(file, "Oral:%d\n", vetorC[0]);
	fprintf(file, "Oficina:%d\n", vetorC[1]);
	fprintf(file, "Poster:%d\n", vetorC[2]);
	fprintf(file, "Laboratorio:%d\n", vetorC[3]);
}
/* FIM :) [até que em fim] ;) */