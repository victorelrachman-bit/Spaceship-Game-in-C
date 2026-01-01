#ifndef MOV_H
#define MOV_H
#define px_ini 2 //X inicial do jogador
#define oqtd 10 //Qtd de obs

//Jogador
int px = px_ini; //Posição x do jogador
int py = 3; //Posição y do jogador

//Game over
bool game_over = false;
int rodando = true; //Se está rodando o main.cpp
	
//Obs
int on = -3;//Se ox for -1, então obs não deve existir
int oxini = 50; //X do obs inicial para todos os obs
int ox[oqtd] = {on, on, on, on, on, on, on, on, on, on}; //Posição x dos 5 obs
int oy[oqtd] = {-1, -1, -1, -1, -1,  -1, -1, -1, -1, -1}; //Posição y dos 5 obs
int odelay = 300; //Delay para se movimentar
int odelayger = 3000; //Delay para geração de obs
int odelayultger = clock(); //Ultima vez que gerou obs
int oultaum = 0; //Ultima vez que aumentou a velocidade de geração e de movimento do obs
int oultmov[oqtd] = {0, 0, 0, 0 ,0,0, 0, 0, 0 ,0}; //Ultima vez que obs se movimentou
int maxObsVel = 20; //maximo de velocidade do obs
int maxObsGerVel = 220; //maximo de velocidade de geração do obs
int odelayaum = 300; //Delay para aumentar a velocidade o jogo
int score = 0; //Pontuação
int ultscore = 0; //Ultima vez que o score aumentou
int scoredelay = 1000; //delay para aumentar o score 
int scoreAnterior = 0; //Score do ultimo jogo

//Movimento do player, variavel mov para somar-se ao py do jogador
void JogMov(int mov)	
{
	textcolor(14);
	
	gotoxy(px, py-1); printf(" "); //Apaga
	gotoxy(px, py); printf(" "); //Apaga
	gotoxy(px, py+1); printf(" "); //Apaga
	py += mov; //movimentação (JogMov é impura)
	gotoxy(px, py-1); printf("|"); //Asa
	gotoxy(px, py); printf("-"); //Corpo
	gotoxy(px, py+1); printf("|"); //Asa
	
	textcolor(15);
}

//Movimento do jogador
void JogMovTec()
{
	//Se alguma tecla foi pressionada
	if(kbhit())
	{
		char tec = getch(); //Pega a tecla
		fflush(stdin); //Limpa o buffer do teclado
		if(tec == 's' && py + 2 < 20) //Para baixo
			JogMov(1);
		else if(tec == 'w' && py - 2 > 0) //Para cima
			JogMov(-1);
	}
}
	
//Movimento automático do obs
void ObsMov()
{
	textcolor(4);
	
	for(int i = 0; i < oqtd; i++) //Para cada possivel obs
	{
		if(ox[i] == on) //Seguindo a proposição indicada acima
		{
			ox[i] = on; //Deixando de existir
			oultmov[i] = 0;	//Deixando de existir
		}else //Se existir
		{
			if(oultmov[i] + odelay <= clock()) //Se já passou o tempo para se mover
			{
				if((ox[i] >= px-1  && ox[i] <= px+1) && (oy[i] >= py - 1 && oy[i] <= py + 1)) //Se enconstou na nave
				{
					game_over = true; //Fim de jogo
				}else
				{
					if(ox[i] == 0) //x = 0, evita bug
					{				
						gotoxy(ox[i]+1, oy[i]); printf(" "); //Apaga
						gotoxy(ox[i], oy[i]); printf(" "); //Apaga
						gotoxy(ox[i]-1, oy[i]); printf(" "); //Apaga
						ox[i] = on; //movimentação (ObsMov é impura)
						oultmov[i] = clock(); //Atualizando a ultima vez que se movimentou
					}
					if(ox[i] == 1) //x = 1, evita bug
					{				
						gotoxy(ox[i]+1, oy[i]); printf(" "); //Apaga
						gotoxy(ox[i], oy[i]); printf(" "); //Apaga
						gotoxy(ox[i]-1, oy[i]); printf(" "); //Apaga
						ox[i] -= 1; //movimentação (ObsMov é impura)
						gotoxy(ox[i]+1, oy[i]); printf("-"); //Obs
						oultmov[i] = clock(); //Atualizando a ultima vez que se movimentou
					}
					if(ox[i] == 2) //x = 2, evita bug
					{				
						gotoxy(ox[i]+1, oy[i]); printf(" "); //Apaga
						gotoxy(ox[i], oy[i]); printf(" "); //Apaga
						gotoxy(ox[i]-1, oy[i]); printf(" "); //Apaga
						ox[i] -= 1; //movimentação (ObsMov é impura)
						gotoxy(ox[i]+1, oy[i]); printf("-"); //Obs
						gotoxy(ox[i], oy[i]); printf("-"); //Obs
						oultmov[i] = clock(); //Atualizando a ultima vez que se movimentou
					}
					else if(ox[i] > 2) //não haverá numeros negativos no x, sem bugs
					{				
						gotoxy(ox[i]+1, oy[i]); printf(" "); //Apaga
						gotoxy(ox[i], oy[i]); printf(" "); //Apaga
						gotoxy(ox[i]-1, oy[i]); printf(" "); //Apaga
						ox[i] -= 1; //movimentação (ObsMov é impura)
						gotoxy(ox[i]+1, oy[i]); printf("-"); //Obs
						gotoxy(ox[i], oy[i]); printf("-"); //Obs
						gotoxy(ox[i]-1, oy[i]); printf("-"); //Obs
						oultmov[i] = clock(); //Atualizando a ultima vez que se movimentou
					}
				}
			}	
		}	
	}
	
	textcolor(15);	
}

//Geração de obstáculos
//indice - possiveis y
//0 - 1, 2
//1 - 3, 4
//2 - 5, 6
//3 - 7, 8
//4 - 9, 10
//5 - 11, 12
//6 - 13, 14
//7 - 15, 16
//8 - 17, 18
//9 - 19, 20
void ObsGer()
{
	if(odelayultger + odelayger < clock()) //Se já deu o tempo para gerar de novo
	{
		int i; //indice
		
		int ocheio = 0; //Contador de obs cheio
		//Verifica se todos os obs estão cheios
		for(int j = 0; j < oqtd; j++)
		{
			if(ox[j] != on)
				ocheio++;//Aumenta o contador de obs cheios
		}
		
		//Se não está cheio
		if(ocheio < oqtd)
		{
			//Busca um obs que não existe para o gerar
			do
			{
				i = rand() % oqtd; //Algum aleatório
			}while(ox[i] != on);
			ox[i] = oxini; //Atualiza x
			oy[i] = i*(20 / oqtd) + rand() % (20 / oqtd) + 1; //Atualiza y conforme predito
			odelayultger = clock(); //Atualiza o tempo para gerar novamente
		}
	}
}

//Ir aumentando a velocidade
void AumVel()
{
	if(oultaum + odelayaum <= clock()) //Se já deu o tempo de aumentar a velocidade
	{
		if(odelay >= maxObsVel) //Se ainda não está no minimo
			odelay -= 2; //Delay para se movimentar
		if(odelayger >= maxObsGerVel) //Se ainda não está no minimo
			odelayger-= 20; //Delay para geração de obs
		oultaum = clock(); //Ultima vez que aumentou a velocidade
	}
}

//Aumenta pontuação
void AumPont()
{
	if(ultscore + scoredelay <= clock()) //Se já deu o tempo para aumentar a pontuação
	{
		score++; //Aumenta a pontuação
		ultscore = clock();	//Ultima vez que o score aumentou redefinida
		gotoxy(1, 21); printf("Score: %d", score); //Mostrando o score
	}	
} 

//Resetar o jogo
void ResetGame()
{
	//Jogador
	px = px_ini; //Posição x do jogador
	py = 3; //Posição y do jogador
	
	//Game over
	game_over = false;
	on = -3;//Se ox for -1, então obs não deve existir
	oxini = 50; //X do obs inicial para todos os obs
	for(int i = 0; i < oqtd; i++)
	{
		ox[i] = on;
		oy[i] = on;
		oultmov[i] = 0;
	}
	odelay = 300; //Delay para se movimentar
	odelayger = 3000; //Delay para geração de obs
	odelayultger = clock(); //Ultima vez que gerou obs
	oultaum = 0; //Ultima vez que aumentou a velocidade de geração e de movimento do obs
	maxObsVel = 25; //maximo de velocidade do obs
	maxObsGerVel = 250; //maximo de velocidade de geração do obs
	odelayaum = 300; //Delay para aumentar a velocidade o jogo
	ultscore = 0; //Ultima vez que o score aumentou
	scoredelay = 1000; //delay para aumentar o score 
	scoreAnterior = score; //Score do ultimo jogo
	score = 0; //Pontuação

			
	clrscr(); 
}

//Iniciar a tela
void StartScreen()
{
	textcolor(1); //Cor azul
	
    clrscr();//Limpa tela

    // Pixel art escrevendo exatamente "SPACESHIP GAME"
    const char *art[5] = {
        " ###   ####    ###    ###   #####   ###   #   #  #####  ####           ###    ###   #   #  #####  ",
        "#      #   #  #   #  #   #  #      #      #   #    #    #   #         #   #  #   #  ## ##  #      ",
        " ###   ####   #####  #      #####   ###   #####    #    ####          #  ##  #####  # # #  #####  ",
        "    #  #      #   #  #   #  #          #  #   #    #    #             #   #  #   #  #   #  #      ",
        " ###   #      #   #   ###   #####   ###   #   #  #####  #              ###   #   #  #   #  #####  "
    };    
    for (int i = 0; i < 5; i++) { //Desenha na tela
        gotoxy(2, 2 + i);
        printf("%s", art[i]);
    }
    
    textcolor(15); //Cor normal
    
	printf("\n\nJogo desenvolvido por Victor El Rachman, Renan Coelho e Lucas Floriano\n"); //Creditos
    printf("Aperte 's' para descer e 'w' para subir\n"); //Instruções
    printf("Desvie dos obstáculos"); //Intruções

    gotoxy(1, 10); printf("Pressione qualquer tecla para iniciar..."); //Para comecaer
	
    while (!kbhit()) { /* espera */ } //Enquanto nao clica
    getch();//Pega o click
    fflush(stdin);//Limpa o buffer do teclado

    printf("\nComeçando...");
	Sleep(1000);
	system("cls");
}

//Game over
void GameOver()
{
		gotoxy(1,1); //Coloca no começo
		clrscr(); //Limpa tela
		char c;  //Char para o usuário digitar o que quer fazer
		
		textcolor(1); //Cor azul
		
		const char *art_over[5] = {
	        " ####    ##    #   #   ####        ####    #  #   ####   #### ",
	        " #       # #   ## ##   #           #  #    #  #   #      #  # ",
	        " #  ##   ####  # # #   ###         #  #    #  #   ###    #### ",
	        " #   #   #  #  #   #   #           #  #     ##    #      # #  ",
	        " ####    #  #  #   #   ####        ####     ##    ####   #  # "
    	};

	    for (int i = 0; i < 5; i++) { //Desenha
	        gotoxy(2, 2 + i);
	        printf("%s", art_over[i]);
	    }
    
    	textcolor(15); //Cor normal
    
    	printf("\n\nScore: %d", score); //MOstra score
    	printf("\nScore Anterior: %d", scoreAnterior); //Mostra outro score
		printf("\nDigite s para jogar novamente ou qualquer outra tecla para parar\n");
		scanf("%c", &c); //Pegando o que o usuario disse
		if(c == 's') //Reiniciando
		{
			ResetGame();
		}else //Saindo
		{
			printf("\nSaindo...");
			Sleep(1500);
			rodando = false;
		}
}

#endif


