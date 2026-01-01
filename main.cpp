//Spaceship Game
//Desenvolvido por Victor El Rachman, Lucas FLoriano e Renan Coelho
//Consiste em uma nave (jogador) indo de cima a baixo desviando de asteróides (obstáculos)
//Obs = Obstaculos

//Adicionando bibliotecas
#include <stdio.h>
#include <conio.c>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include "mov.h"

//O jogo em si
int main()
{
	//Aleatoriedade
	srand(time(NULL));
	
	//Em português
	setlocale(LC_ALL, "portuguese");
	
	//Introdução do jogo
	StartScreen();
	while(rodando == true)//Enquanto a aplicação estiver rodando...
	{
		//Movimento do jogador	(cria jogador)
		JogMov(0);
	
		//Jogo rodando
		while(!game_over)
		{
			JogMovTec(); //Jogador movimenta
			ObsGer(); //Geração de obstáculos
			ObsMov(); //Movimento dos obstáculos
			AumPont(); //Aumenta pontos
			AumVel(); //Aumentando a velocidade
			Sleep(10); //Delay para evitrar que a CPU sobrecarregue
		}
		
		//Para o usuario decidir o que fazer apos o jogo acabar
		GameOver();
	}
	
	return 0;
}


