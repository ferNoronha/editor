struct lista
{
	char letra;
	char final;
	struct lista *cabeca, *cauda;
};
typedef struct lista Listagen;

Listagen *criaCaixa(char letra)
{
	Listagen *l = (Listagen*)malloc(sizeof(Listagen));
	l->cabeca = NULL;
	l->cauda = NULL;
	l->final = 'F';
	l->letra = letra;
	
	return l;
}

void insere(Listagen **l, char palavra[])
{
	Listagen *nova, *ant, *aux;
	int i, verif, cont, k;
	
	char terminou = 0;
	
	if(*l == NULL)
	{
		i = 0;
		nova = criaCaixa(palavra[i++]);
		*l = nova;
		while(palavra[i] != '\0')
		{
			nova->cabeca = criaCaixa(palavra[i++]);
			nova = nova->cabeca;
		}
		nova->final = 'T';
	}
	else
	{
		i = 0;
		aux = *l;
		while( palavra[i] != '\0')
		{
			
			while(aux != NULL && aux->letra < palavra[i])
			{
				ant = aux;
				aux = aux->cauda;
			}
			
			if(aux != NULL && aux->letra == palavra[i])
			{
				i++;
				if(palavra[i] == '\0')
					aux->final = 'T';
				else
				{
					if(aux->cabeca == NULL)
					{
						while(palavra[i] != '\0')
						{
							aux->cabeca = criaCaixa(palavra[i++]);
							aux = aux->cabeca;
						}
						aux->final = 'T';
					}
					else
						aux = aux->cabeca;
				}
			}
			else
			{
				nova = criaCaixa(palavra[i++]);
				
				if(*l == aux)
					*l = nova;
				else
					ant->cauda = nova;
				
				nova->cauda = aux;
				
				while(palavra[i] != '\0')
				{
					nova->cabeca = criaCaixa(palavra[i++]);
					nova = nova->cabeca;
				}
				nova->final = 'T';
			}
		}
	}
}

char busca(Listagen *l, char palavra[])
{
	char achou = 1;
	int i = 0;
		
	while(l != NULL && achou && palavra[i] != '\0')
	{
		while(l != NULL && l->letra < palavra[i])
			l = l->cauda;
		
		if(l != NULL && l->letra == palavra[i])
		{
			i++;
			if(palavra[i] != '\0')
				l = l->cabeca;
		
		}
		else
		 achou = 0;
	}
	if(l == NULL)
		achou = 0;
	else
		if(achou && l->final != 'T')
			achou = 0;
		
	return achou;
}

void sujestao(Listagen *l, char palavra[])
{
	Listagen *aux;
	char auxp[30];
	strcpy(auxp, palavra);
	
	char achou = 1;
	int i = 0;
		
	while(l != NULL && achou && auxp[i] != '\0')
	{
		while(l != NULL && l->letra < auxp[i])
			l = l->cauda;
		
		if(l != NULL && l->letra == auxp[i])
		{
			i++;
			if(auxp[i] != '\0')
				l = l->cabeca;
		}
		else
		 achou = 0;
	}
	if(l == NULL)
		achou = 0;
			
	if(achou)
	{
		aux = l;
		while(aux!= NULL && aux->cauda == NULL && aux->final == 'F')
			aux= aux->cabeca;
		if(aux->cauda == NULL && aux->cabeca == NULL)
			aux= aux->cabeca;
	}
	
	if(aux == NULL)
	{
		l = l->cabeca;
		while(l != NULL)
		{
			palavra[i++] = l->letra;
			l = l->cabeca;
		}
		palavra[i] = '\0';
	}
}

/*void exibe(Listagen *l)
{
	Listagen *aux;	
	while(l != NULL)
	{
		aux = l;
		while(aux != NULL)
		{
			printf("%c", aux->letra);
			aux=aux->cabeca;
		}
		printf("\n");
		l = l->cauda;
	}
}*/

