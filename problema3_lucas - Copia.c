#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<strings.h>

#define CIDADE 10
#define DIA 30
#define HORA 24

typedef struct_dados{	// Estrutura de Dados de Entrada
	// a hora nao � armazenada, j� que tem um indice para isso
    float temp;
    float pressao;
    float umidade;
    float prec;
    float km;
    char vento[3];
} dados;
typedef struct_saida{		//Estrutura de Dados de Saida
	float temp;
	int cidade;
}saida;

void selection_sort(saida [])
void leitura(dados [][DIA][HORA], int,char [],char []);
void temp_minima(dados [][DIA][HORA], int);
void temp_media(dados [][DIA][HORA], int);
void temp_max(dados [][DIA][HORA], int);
void medias(dados [][DIA][HORA],int);
void consulta(char[],int,int );
void desconversor(char [],int);
int conversor(char []);

int main (void)
{
	int escolha = 0;
	char sigla[3];
	char dia[3];
	char mes[3];
	int count=0;
	int dia_media;
	dados matriz[CIDADE][DIA][HORA];
	while(true)
	{
		printf("######################	\n");
		printf(" 1 - Importar dados	\n");
		printf(" 2 - Exportar dados	\n");
		printf(" 3 - Consultar		\n");
		printf(" 4 - M�dias Di�rias	\n");
		printf(" 5 - Sair		\n");
		printf("######################	\n");
		scanf("%d",&escolha);
		switch (escolha)
		{
			case 1:
				printf("Digite de qual dia deseja realizar a leitura, Exemplo: 02,05...\n");
				scanf(" %s",dia);
				printf("Digite qual mes  Exemplo:08,09....\n");
				scanf(" %s",mes);

				if (count <= 29)
					leitura(dados matriz[][DIA][HORA],count,dia,mes);
				else
				{
					count = 0;
					leitura(dados matriz[][DIA][HORA],count,dia,mes);
				}
				count++;

				break;
			case 2:
				temp_minima(dados matriz[][DIA][HORA]);
				temp_max(dados matriz[][DIA][HORA]);
				temp_media(dados matriz[][DIA][HORA]);
				printf("Arquivos gerados com sucesso\n");
				break;
			case 3:
				printf("Informe a sigla, o dia e a hora que deseja consultar, separado por um espa�o\n");
				printf("Exemplo: SSA 13 22");
				__fpurge(stdin)
				scanf("%s %d %d",sigla ,&dia ,&hora);
				consulta(sigla,dia,hora);
				break;
			case 4:
				printf("Digite o dia em que deseja gerar as m�dias");
				scanf("%d",&dia_media);
				medias(dados matriz[][DIA][HORA], dia_media);
			case 5:
				return 0;
			default:
				printf("Comando Inv�lido \n");
				break;
		}
	}
}
void leitura(dados matriz[][DIA][HORA], int count,char dia[],char mes[])  // testado
{
	char nome_arquivo[20];
	int hora = 0;
	FILE *file;
	int i;
	int aux;
	for(i = 0;i < 10; i++){
		desconversor(nome_arquivo,i);
		strcat(nome_arquivo, "2016");
		strcat(nome_arquivo, mes);
		strcat(nome_arquivo, dia);
		strcat(nome_arquivo, ".txt");


		file = fopen(nome_arquivo, "r");
		if (file == NULL){
			printf("Arquivo n�o encontrado");
			exit(1);
		}
		while( (fscanf(file,"%d %f %f %f %f %f %s\n", &aux, &matriz[cidade][count][hora].temp, &matriz[cidade][count][hora].pressao, &matriz[cidade][count][hora].umidade,&matriz[cidade][count][hora].prec, &matriz[cidade][count][hora].km, matriz[cidade][count][hora].vento))!=EOF ){
		hora++;
	}
	fclose(file);

	}

}
void consulta(char sigla[3], int dia, int hora)
{
	int cidade = conversor(sigla);
	printf("Temperatura: |%f|,  Press�o Atmosferica: |%f|,  Umidade: |%f|,  Precipita��o: |%f|, Km: |%f|,  Vento:  |%s|",matriz[cidade][dia][hora].temp,matriz[cidade][dia][hora].pressao,matriz[cidade][dia][hora].umidade,matriz[cidade][dia][hora].prec,matriz[cidade][dia][hora].km,matriz[cidade][dia][hora].vento);

}
void temp_minima(dados matriz[][DIA][HORA], int dia_escolhido)
{
	int minima;
	char nome[3];
	char temperatura[10];
	saida vet[10];
	int c;
	int aux = 0;
	int h;
	for(c = 0;c < 10; c++)	// zerando o vetor
	{
		vet[c].temp = 0;
		vet[c].cidade = c;
	}
	for(c = 0;c < 10; c++)
	{
		minima = matriz[c][dia_escolhido][0].temp;
		for(h = 0; h < 24; h++)
		{
			if (matriz[c][dia_escolhido][h] < minima)
				minima = matriz[c][dia_escolhido][h];
		}
		vet[c].temp = minima;
	}
	selection_sort(saida vet);


	file = fopen("temp_minima.txt", "w"); // cria um arquivo
	for(c = 0;c < 10; c++)
	{
		desconversor(nome,vet[c].cidade);
		fprintf(file,"%s %.2f \n", nome,vet[c].temp);	//Escreve a sigla da cidade e a temperatura media
	}
	fclose(file);
}
void temp_media(dados matriz[][DIA][HORA], int dia_escolhido)
{
	char nome[3];
	char temperatura[10];
	saida vet[10];
	int c;
	int aux = 0;
	int h;
	for(c = 0;c < 10; c++)	// zerando o vetor
	{
		vet[c].temp = 0;
		vet[c].cidade = c;
	}

	for(c = 0;c < 10; c++)
		for(h = 0;h < 24; h++)
			vet[c].temp += matriz[c][dia_escolhido][h];


	selection_sort(vet);


	file = fopen("temp_media.txt", "w"); // cria um arquivo
	for(c = 0;c < 10; c++)
	{
		desconversor(nome, vet[c].cidade);
		fprintf(file,"%s %.2f \n",nome,vet[c].temp/24);	//Escreve a sigla da cidade e a temperatura media
	}
	fclose(file);
}
void temp_max(dados matriz[][DIA][HORA], int dia_escolhido)
{
	int maxima;
	char nome[3];
	char temperatura[10];
	saida vet[10];
	int c;
	int aux = 0;
	int h;
	for(c = 0;c < 10; c++)	// zerando o vetor
	{
		vet[c].temp = 0;
		vet[c].cidade = c;
	}
	for(c = 0;c < 10; c++)
	{
		maxima = matriz[c][dia_escolhido][0].temp;
		for(h = 0;h < 24; h++)
		{
			if (matriz[c][dia_escolhido][h] > maxima)
				maxima = matriz[c][dia_escolhido][h];
		}
		vet[c].temp = maxima;
	}
	selection_sort(vet);


	file = fopen("temp_maxima.txt", "w"); // cria um arquivo
	for(c = 0; c < 10; c++)
	{
		desconversor(nome,vet[c].cidade);
		fprintf(file,"%s %.2f \n",nome,vet[c].temp);	//Escreve a sigla da cidade e a temperatura media
	}
	fclose(file);


}
void medias(dados [][DIA][HORA],int dia);
{
	FILE *file;
	char sigla[3];
	int i;
	int h;
	float media_temp = 0;
	float media_pressao = 0;
	float media_umidade = 0
	float media_prec = 0;
	file = fopen("medias_diarias.txt", "w");
	for(i = 0; i < 10; i++)
	{
	    desconversor(sigla, i);
	    for(h = 0; h < 24; h++)
	    {
	      media_temp += matriz[i][dia][h].temp;
	      media_pressao += matriz[i][dia][h].pressao;
	      media_umidade += matriz[i][dia][h].umidade;
	      media_prec += matriz[i][dia][h].prec;
	    }
	  fprintf(file,"CIDADE: %s  Temperatura: %.2f  Pressao: %.2f  Umidade: %.2f  Precipitacao: %.2f \n", sigla, media_temp/24, media_pressao/24, media_umidade/24, media_prec/24);
	  
	}
	fclose(file);

}
int conversor(char sigla[3])
{
		if (!strcmp(sigla,"SSA"))
			return 0;
		else if (!strcmp(sigla, "FSA"))
			return 1;
		else if (!strcmp(sigla, "VDC"))
			return 2;
		else if (!strcmp(sigla, "CAM"))
			return 3;
		else if (!strcmp(sigla, "ITA"))
			return 4;
		else if (!strcmp(sigla, "  "))
			return 5
		else if (!strcmp(sigla, "  "))
			return 6
		else if (!strcmp(sigla, "  "))
			return 7
		else if (!strcmp(sigla, "  "))
			return 8
		else if (!strcmp(sigla, "  "))
			return 9
	}
	return (cidade);
}
void desconversor(char nome[],int sigla)
{
	switch (sigla)
	{
		case 0:
			strcpy(nome, "SSA_");
			break;
		case 1:
			strcpy(nome, "FSA_");
			break:
		case 2:
			strcpy(nome, "VDC_");
			break;
		case 3:
			strcpy(nome, "CAM_");
			break;
		case 4:
			strcpy(nome, "ITA_");
			break;
		case 5:
			strcpy(nome, "_");
			break;
		case 6:
			strcpy(nome, "_");
			break;
		case 7:
			strcpy(nome, "_");
			break;
		case 8:
			strcpy(nome, "_");
			break;
		case 9:
			strcpy(nome, "_");
			break;
	}
}
void selection_sort(saida vet[])
{

    int i, j, min,aux;

    for (i = 0; i < 10; i++)
    {
        min = i;
        for (j = i + 1; j < 10; j++)
        {
            if (a[j] < a[min])
                min = j;
        }
		//troca a temperatura
		aux = a[i].temp;
		a[i].temp = a[min].temp;
		a[min].temp = aux;
		//o campo CIDADE tamb�m acompanha a troca para nao se perder
		aux = a[i].cidade;
		a[i].cidade = a[min].cidade;
		a[min].cidade = aux;
    }
}

