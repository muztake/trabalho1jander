#include <stdio.h>
#include <string.h>

#define LARGURA_MAXIMA 1000
#define ALTURA_MAXIMA  1000

typedef struct pix {
	int r, g, b;
} Pixel;

// Define a imagem globalmente como uma matriz de pixels
Pixel imagem[LARGURA_MAXIMA][ALTURA_MAXIMA];

// Subrotinas dos comandos
void cinza		(int largura, int altura);
void inversao	(int largura, int altura);
void limiar		(int largura, int altura, double valor);
void suavizacao (int largura, int altura);
void contraste  (int largura, int altura, double valor);
void brilho 	(int largura, int altura, double valor);
void sepia		(int largura, int altura);
void imprimir   (int largura, int altura);

int main(){
	// Comando e parametros
	char comando[4] = "CIN";
	int largura, altura, linha, coluna;
	double parametro;
	scanf("%s", &comando);
	
	// Se o comando possuir parametro
	if(!strcmp(comando, "LIM") || !strcmp(comando, "CON") || !strcmp(comando, "BRI"))
		scanf("%lf", &parametro);
		
	// Leitura das dimensoes da imagem
	scanf("%d %d", &largura, &altura);

	// Leitura da imagem
	for(linha = 0; linha < altura; linha++)
		for(coluna = 0; coluna < largura; coluna++){
			Pixel p; // Um pixel auxiliar
			scanf("%d %d %d", &p.r, &p.g, &p.b);
			imagem[linha][coluna] = p;
		}
	// Aplicacao do comando
	if		(!strcmp(comando, "CIN"))
		cinza(largura, altura);
	else if (!strcmp(comando, "INV"))
		inversao(largura, altura);
	else if (!strcmp(comando, "LIM"))
		limiar(largura, altura, parametro);
	else if (!strcmp(comando, "MED"))
		suavizacao(largura, altura);
	else if (!strcmp(comando, "CON"))
		contraste(largura, altura, parametro);
	else if (!strcmp(comando, "BRI"))
		brilho(largura, altura, parametro);
	else if (!strcmp(comando, "SEP"))
		sepia(largura, altura);
	
	// Impressao da imagem
	imprimir(largura, altura);
}

// Deixa a imagem em escalas de cinza
void cinza(int largura, int altura){
	int linha, coluna;
	for(linha = 0; linha < altura; linha++)
		for(coluna = 0; coluna < largura; coluna++){
			Pixel atual = imagem[linha][coluna];
			int g = atual.r * .2126 + atual.g * .7152 + atual.b * .0722;
		       	atual.r = g;
			atual.g = g;
			atual.b = g;
			imagem[linha][coluna] = atual;	
		}
}

void inversao(int largura, int altura){
	int linha, coluna;
	for(linha = 0; linha < altura; linha++)
		for(coluna = 0; coluna < largura; coluna++){
			Pixel atual = imagem[linha][coluna];
			atual.r = 255 - atual.r;			
			atual.g = 255 - atual.g;			
			atual.b = 255 - atual.b;			
			imagem[linha][coluna] = atual;
		}

}

void limiar(int largura, int altura, double valor){
	int linha, coluna;
	for(linha = 0; linha < altura; linha++)
		for(coluna = 0; coluna < largura; coluna++){
			Pixel atual = imagem[linha][coluna];
			int gray = atual.r * .2126 + atual.g * .7152 + atual.b * .0722;
			gray = gray >= valor ? 255 : 0;
			atual.r = gray;
			atual.g = gray;
			atual.b = gray;
			imagem[linha][coluna] = atual;
		}
}

void suavizacao(int largura, int altura){
	int linha, coluna, i, j;
	// printf("Suav\n");
	for(linha = 0; linha < altura; linha++)
		for(coluna = 0; coluna < largura; coluna++){
			// Váriaveis utilizadas
			Pixel media = imagem[altura][largura]; 
			
			// Checa se está na borda
			if(linha == 0 || coluna == 0 || linha == altura - 1 || coluna == largura - 1)
				continue;
			// Define um pixel que terá o valor de suas componentes iguais à soma das componentes
			// respectivas de seus vizinhos
			media.r = 0; media.g = 0; media.b = 0;
			
			// Soma as componentes dos vizinhos
			for(i = -1; i <= 1; i++)
				for(j = -1; j <= 1; j++){
					media.r += imagem[linha + i][coluna + j].r;
					media.g += imagem[linha + i][coluna + j].g;
					media.b += imagem[linha + i][coluna + j].b;
				}
			
			// Divide pela quantidade de vizinhos
			media.r /= 9;
			media.g /= 9;
			media.b /= 9;

			// Define o pixel na posição
			imagem[linha][coluna] = media;
		}
}

void contraste(int largura, int altura, double valor){
	int linha, coluna;
		for(linha = 0; linha < altura; linha++)
			for(coluna = 0; coluna < largura; coluna++){
				Pixel atual = imagem[linha][coluna];
				atual.r = atual.r * valor > 255 ? 255 : atual.r * valor; 
				atual.g = atual.g * valor > 255 ? 255 : atual.g * valor; 
				atual.b = atual.b * valor > 255 ? 255 : atual.b * valor; 
				imagem[linha][coluna] = atual;
			}
}

void brilho(int largura, int altura, double valor){
	int linha, coluna;
		for(linha = 0; linha < altura; linha++)
			for(coluna = 0; coluna < largura; coluna++){
				Pixel atual = imagem[linha][coluna];
				atual.r = (atual.r + valor > 255) ? 255 : (atual.r + valor < 0 ? 0 : atual.r + valor);
				atual.g = (atual.g + valor > 255) ? 255 : (atual.g + valor < 0 ? 0 : atual.g + valor);
				atual.b = (atual.b + valor > 255) ? 255 : (atual.b + valor < 0 ? 0 : atual.b + valor);
				imagem[linha][coluna] = atual;
			}
}

void sepia(int largura, int altura){
	int linha, coluna;
		for(linha = 0; linha < altura; linha++)
			for(coluna = 0; coluna < largura; coluna++){
				Pixel atual = imagem[linha][coluna];
				atual.r = atual.r * .393 + atual.g * .769 + atual.b * .189;
				atual.g = atual.r * .349 + atual.g * .686 + atual.b * .168;
				atual.b = atual.r * .272 + atual.g * .534 + atual.b * .131;
				imagem[linha][coluna] = atual;
			}
}

void imprimir(int largura, int altura){
	int linha, coluna;
	for(linha = 0; linha < altura; linha++){
		for(coluna = 0; coluna < largura; coluna++){
			Pixel atual = imagem[linha][coluna];
			printf("%3d %3d %3d ", atual.r, atual.g, atual.b); 
		}
		printf("\n");
	}	
}
