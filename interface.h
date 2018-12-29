void borda(void)
{
	TextColor(15,0);
	//x
	for(int i=1;i<109;i++)
	{
		gotoxy(i,1);printf("%c",219);
		gotoxy(i,32);printf("%c",219);
	}
	//y
	for(int i=1;i<=32;i++)
	{
		gotoxy(1,i);printf("%c",219);
		gotoxy(2,i);printf("%c",219);
		gotoxy(109,i);printf("%c",219);
		gotoxy(110,i);printf("%c",219);
		gotoxy(20,i);printf("%c",219);//separa menu
	}

	for(int i = 25; i< 104; i++)
	{
		gotoxy(i,4);printf("|");
	}
}

void salvar()
{
	gotoxy(25,10);printf("Salvar Arquivo");
	gotoxy(25,20);printf("Nome do Arquivo: ",219);
}

void abrir()
{
	gotoxy(25,10);printf("Abrir Arquivo");
	gotoxy(25,20);printf("Nome do Arquivo: ",219);
}

void config()
{
	gotoxy(25,10);printf("Configuracao dos Paragrafos");
	gotoxy(25,15);printf("Primeira Linha:",219);
	gotoxy(25,20);printf("Recuo Esquedo");
	gotoxy(25,25);printf("Recuo Direito",219);
}

void menu()
{
	int inicio = 4;
	int espacamento = 6;
	gotoxy(6,inicio);printf("F2-Abrir");
	gotoxy(6,inicio+espacamento);printf("F3-Salvar");
	gotoxy(6,inicio+espacamento*2);printf("ESC-Sair");
	gotoxy(6,inicio+espacamento*3);printf("F4-Exibir");
	gotoxy(6,inicio+espacamento*4);printf("F5- Novo");
}

void info()
{
	int lin = 30;
	gotoxy(22,lin);printf("COL =");
	gotoxy(32,lin);printf("LIN =");
	gotoxy(42,lin);printf("INSERT");
	gotoxy(52,lin);printf("||||");
}
void limpatela()
{
	for(int y=7;y<21;y++)
		for(int x=25;x<105;x++)
		{
			gotoxy(x,y);
			printf(" ");
		}
}


