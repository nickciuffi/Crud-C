#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct filmes{
	char nome[40];
	char genero[40];
	char faixaEt[10];
	int ano_lancamento;
	int duracao;
}filme;

int armazenar( FILE *arq, filme *flm){
	
	arq = fopen("filmes.txt", "ab");
	
	if(arq != NULL){
		fwrite(flm, sizeof(filme), 1, arq); 
		fclose(arq);	
		return 1;
	}
	else{
		
		return -1;
	}
	return -1;
	
}

int lerFilmes(FILE *arq, filme *f){
	
	int cont = 0;
	arq = fopen("filmes.txt", "rb");
	
	if(arq ==NULL){
		return -1;
	}
	while(1){
	
	fread(f, sizeof(filme), 1, arq);
	if(feof(arq)){
		fclose(arq);
		break;
	}
	cont++;
	filme film = *f;
	printf("Filme %i\n", cont);
	printf("|Nome: %s\n", film.nome);
	printf("|Genero: %s\n", film.genero);
	printf("|Classificação Indicativa: %s\n", film.faixaEt);
	printf("|Data de Lançamento: %i\n", film.ano_lancamento);
	printf("|Duração: %i\n\n", film.duracao);
}
	return cont;	
}

int editar(FILE *arq, int cod, int size){
		setbuf(stdin, NULL);
		filme films[size];
		
		int i = 0;
		arq = fopen("filmes.txt", "rb");
		
		if(arq ==NULL){
			return -1;
		}
		for(i = 0; i < size; i++){
		
		fread(&films[i], sizeof(filme), 1, arq);
		if(feof(arq)){
			break;
		}
	}
		printf("Editando o filme %i\n\n", cod);
		filme editFil;
		printf("Qual o nome do filme? \n");
		gets(editFil.nome);
		printf("Qual o genero do filme? \n");
		gets(editFil.genero);
		printf("Qual a classificação indicativa do filme? \n");
		gets(editFil.faixaEt);
		printf("Qual o ano de lançamento do filme? \n");
		scanf("%i", &editFil.ano_lancamento);
		setbuf(stdin, NULL);
		printf("Qual a duração do filme?(mins) \n");
		scanf("%i", &editFil.duracao);
		setbuf(stdin, NULL);
		int filmId = cod - 1;
		films[filmId]= editFil;
		fclose(arq);
		
		arq = fopen("filmes.txt", "wb");
		fclose(arq);
		arq = fopen("filmes.txt", "wb");
		if(arq == NULL){
			return -1;
		}
		
		fwrite(&films, sizeof(filme), size, arq);	
		
		fclose(arq);
		return 1;
}

int deletar(FILE *arq, int cod, int size){
		setbuf(stdin, NULL);
		filme films[size];
		
		int i = 0;
		arq = fopen("filmes.txt", "rb");
		
		if(arq ==NULL){
			return -1;
		}
		for(i = 0; i < size; i++){
		
		fread(&films[i], sizeof(filme), 1, arq);
		if(feof(arq)){
			break;
		}
	}
		int filmId = cod - 1;
		
		for(i = filmId; i < size; i++){
    		films[i] = films[i + 1];
   		}
		   		
		fclose(arq);
		arq = fopen("filmes.txt", "wb");
		fclose(arq);
		arq = fopen("filmes.txt", "wb");
		if(arq == NULL){
			return -1;
		}
		
		fwrite(&films, sizeof(filme), size-1, arq);	
		
		fclose(arq);
		return 1;
		
		
		
}

void main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
	char action;
	FILE *arq;
	int response = 0;
	
	
	while(1){
		
		//Definir ação
		system("cls");
		printf("\nGERENCIAMENTO DE FILMES \n");
		printf("\nAções: \n");
		printf("Ler: l \t");
		printf("Armazenar: a \t");
		printf("Editar: e \t");
		printf("Deletar: d \t");
		printf("Sair: s \n\n");
		printf("O que você quer fazer?\n");
		scanf("%c", &action);
		setbuf(stdin, NULL);
		//se não for digitado uma ação válida, o loop reinicia
		if(action != 'l' && action != 'a' && action != 'e' && action != 'd' && action != 's'){
			system("cls");
			continue;
		}
		
		//sair
		
		if(action == 's'){
			break;
		}
		
		//armazenar
		
		if(action == 'a'){
			system("cls");
			filme fil;
			printf("Qual o nome do Filme? \n");
			gets(fil.nome);
			printf("Qual o genero do Filme? \n");
			gets(fil.genero);
			printf("Qual a classificação indicativa do Filme? \n");
			gets(fil.faixaEt);
			printf("Qual o ano de lançamento do Filme? \n");
			scanf("%i", &fil.ano_lancamento);
			printf("Qual a duração do Filme?(mins) \n");
			scanf("%i", &fil.duracao);
			response = armazenar(arq, &fil);
			if(response < 0){
				printf("Algo deu errado no cadastro \n Aperte qualquer tecla para continuar");
				scanf("%c");
				continue;
			}
			printf("Filme cadastrado com sucesso \n Aperte qualquer tecla para continuar");
			scanf("%c");
			continue;
			
		}
		
		//ler
		if(action == 'l'){
			filme films;
			system("cls");
			printf("Filmes cadastrados: \n \n");
			response = lerFilmes(arq, &films);
			if(response <= 0){
				system("cls");
				printf("Parece que você não possui filmes cadastrados. \nAperte qualquer tecla para continuar");
				scanf("%c");
				continue;
			}
			
			printf("Aperte qualquer tecla para continuar");
			scanf("%c");
			continue;
		}
		
		//editar
		
		if(action =='e'){
			filme films;
			int editId;
			system("cls");
			printf("Filmes cadastrados: \n \n");
			//response é a qtd de ids das bandas
			response = lerFilmes(arq, &films);
			if(response <= 0){
				system("cls");
				printf("Parece que você não possui filmes cadastrados. \nAperte qualquer tecla para continuar");
				scanf("%c");
				continue;
			}
			while(1){
				
			printf("Qual desses filmes você quer editar? Digite o id \n");
			scanf("%i", &editId);
			//response é o maior id das bandas
			//repete ate ser digitado um id correto
			if(editId > 0 && editId <= response){
				break;
			}
		}
			response = editar(arq, editId, response);
			if(response < 0){
				printf("Algo deu errado na edição do filme \nAperte qualquer tecla para continuar");
				scanf("%c");
				continue;
			}
			
			printf("Filme editado com sucesso \nAperte qualquer tecla para continuar");
			scanf("%c");
			continue;	
		}
		
		//deletar
		
		if(action = 'd') {
			filme films;
			int deleteId;
			system("cls");
			printf("Filmes cadastrados: \n \n");
			//response é a qtd de ids das bandas
			response = lerFilmes(arq, &films);
			if(response <= 0){
				system("cls");
				printf("Parece que você não possui filmes cadastrados. \nAperte qualquer tecla para continuar");
				scanf("%c");
				continue;
			}
			while(1){
				
			printf("Qual desses filmes você quer deletar? Digite o id \n");
			scanf("%i", &deleteId);
			//response é o maior id das bandas
			//repete ate ser digitado um id correto
			if(deleteId > 0 && deleteId <= response){
				break;
			}
		}
			response = deletar(arq, deleteId, response);
			if(response < 0){
				printf("Algo deu errado ao tentar deletar este filme \nAperte qualquer tecla para continuar");
				scanf("%c");
				continue;
			}
			
			printf("Filme deletado com sucesso \nAperte qualquer tecla para continuar");
			scanf("%c");
			continue;
		}
		
		
	
}
		system("cls");
		printf("\n\n\nObrigado por utilizar o nosso sistema de armazenamento de filmes");
}

