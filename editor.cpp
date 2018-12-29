#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#include "Conio2.h"
#include "interface.h"
#include "lista.h"
#define XINI 25
#define YINI 7


struct TPCaracter
{
	char letra;
	struct TPCaracter *prox, *ant;	
};
typedef struct TPCaracter TpCaracter;

struct TPLinha
{
	int nrocarac;
	struct TPLinha *top, *botton;
	struct TPCaracter *inicio;
	
};
typedef struct TPLinha TpLinha;

void inserirPalavras(TpLinha *linha, Listagen **l)
{
	TpCaracter *c;
	char palavra[50];
	int i;
	
	c = linha->inicio;
	i = 0;
	
	while(c->prox != NULL && c->letra != '\0')
	{
		while(i<49 && c->prox->prox != NULL && c->letra != ' ' && c->letra != '!' && c->letra != '.' && c->letra != '?')
		{
			palavra[i++]  = c->letra;
			if(c->prox->letra != NULL)
				c = c->prox;
		}
		/*if(c->prox != NULL)
		{*/
			if( i > 3 && i<50)
			{
				palavra[i] = '\0';
				insere(&(*l), palavra);
			}
			else
				palavra[0] = '\0';
				
			i= 0;
			
			if(c != NULL)
				c = c->prox;
		//}
	}
}

void novalinha(TpLinha **linha)
{
	TpCaracter *sentinela = (TpCaracter*)malloc(sizeof(TpCaracter));
	sentinela->letra='*';
	sentinela->prox=NULL;
	sentinela->ant=NULL;
	TpLinha *aux,*nova;
	nova = (TpLinha*)malloc(sizeof(TpLinha));
	nova->nrocarac = 0;
	nova->inicio=sentinela;
	aux=*linha;
	nova->botton=NULL;
	if(aux!=NULL)
	{
		 while(aux->botton!=NULL)
			aux=aux->botton;
	

		nova->top=aux;
		aux->botton=nova;
	
	}
	else
	{
		nova->top=NULL;
		*linha=nova;
		
	}
}

/*void iniciar(TpEditor**edit)
{
	TpLinha * nv = NovaLinha();
	
	//cursor
	TpCursor *cur = (TpCursor*)malloc(sizeof(TpCursor));
	cur->caixa = nv->inicio;
	cur->x = cur->y = 0;
	
	/// primeira linha do texto
	(*edit)->inicio = nv;
	(*edit)->linha = nv;
	/// config paragrafo
	(*edit)->pLinha = 1;
	(*edit)->recuoD = 75;
	(*edit)->recuoE = 5;
	//// infromacoes
	(*edit)->col = 1;
	(*edit)->lin = 1;
	/// estado do insert
	(*edit)->insert = 1;
	///cursor
	(*edit)->cursor = cur;
}*/

void inserenomeio(char l, TpLinha **linha, TpCaracter **cur, TpLinha **linhaux)
{
	
	TpCaracter *novaL, *auxL;
	novaL = (TpCaracter *) malloc (sizeof(TpCaracter));
	novaL->letra=l;
	novaL->prox=(*cur);
	auxL=(*cur);
	if(l!=13)
	{
		if(auxL->ant!=NULL)
		{
			auxL->ant->prox=novaL;
			novaL->ant=auxL->ant;
			novaL->prox=auxL;
			auxL->ant=novaL;
			(*linhaux)->nrocarac++;
		}
		else
		{
			auxL->ant=novaL;
			novaL->prox=auxL;
			novaL->ant=NULL;
			auxL->ant=novaL;
			(*linhaux)->inicio=novaL;
			(*linhaux)->nrocarac++;
		}
	}
	else
	{
		
	}
	
}

void insereCarac(char l, TpLinha **linha, TpCaracter **cur, TpLinha **linhaux, TpLinha **paragrafo, Listagen **listagen)
{
	
	TpLinha *aux, *teste;
	TpCaracter *novaL, *auxL, *ante;
	novaL = (TpCaracter *) malloc (sizeof(TpCaracter));
	novaL->letra=l;
	
	if(*linha == NULL && l!=13 && *cur==NULL)
	{
		
		novalinha(&(*linha));
		novaL->prox=(*linha)->inicio;
		(*cur)=(*linha)->inicio;
		(*linhaux)=(*linha);
		(*linha)->inicio->ant=novaL;
		novaL->ant=NULL;
		novaL->prox=(*linha)->inicio;
		(*linha)->inicio = novaL;
		(*linha)->nrocarac=5;
		(*linha)->nrocarac++;
		*paragrafo = (*linha);
		
	}
	else
	{
		if(l==13)
		{
			aux=*linha;
			if(aux!=NULL)
			{
				while(aux->botton != NULL)
					aux=aux->botton;
			
				auxL=aux->inicio;
				while(auxL->prox!=NULL)
					auxL=auxL->prox;
				if(aux->nrocarac==79 && (auxL->ant->letra!='.' || auxL->ant->letra!='!' || auxL->ant->letra!='?'))
				{	
					novalinha(&aux);
					novaL->letra='.';
					aux->botton->inicio->ant=novaL;
					novaL->prox=aux->botton->inicio;
					novaL->ant=NULL;
					aux->botton->inicio->letra='\0';
					inserirPalavras(*paragrafo,&(*listagen));
					
					*paragrafo = aux->botton;
					
					aux->botton->inicio=novaL;
					aux->botton->nrocarac=5;
					aux->botton->nrocarac++;
					
					(*linhaux)=aux->botton;
					(*cur)=novaL;
				}
				else
				{
					if(auxL->ant!=NULL)
					{
						if(auxL->ant->letra=='.' || auxL->ant->letra=='!' || auxL->ant->letra=='?')
						{
							auxL->letra='\0';
							novalinha(&aux);
							inserirPalavras(*paragrafo,&(*listagen));
							*paragrafo = aux->botton;
							aux->botton->nrocarac=5;
							(*linhaux)=aux->botton;
							(*cur)=aux->botton->inicio;
						
						}
						else
						{
							novaL->letra='.';
							ante=auxL->ant;
							
							if(ante!=NULL)
							{
								novaL->prox=ante->prox;
								ante->prox->ant=novaL;
								novaL->ant=ante;
								ante->prox=novaL;
								
								aux->nrocarac++;
							}
							else
							{
								novaL->prox=auxL;
								novaL->ant=NULL;
								auxL->ant=novaL;
								aux->inicio=novaL;
							}
							
							auxL->letra='\0';
							novalinha(&aux);
							(*cur)=aux->botton->inicio;
							aux->botton->nrocarac=5;
							inserirPalavras(*paragrafo,&(*listagen));
							*paragrafo = aux->botton;
							(*linhaux)=aux->botton;
						}
					}
					else
					{
						novalinha(&aux);
						aux=aux->botton;
						novaL->letra='.';
						novaL->prox=auxL;
						novaL->ant=NULL;
						auxL->ant=novaL;
						auxL->letra='\0';
						aux->inicio=novaL;
						(*cur)=auxL;
						inserirPalavras(*paragrafo,&(*listagen));
						*paragrafo = aux;
						(*linhaux)=aux;
					}
					
				}
			}
				
			
		}
		else
		{
		
				aux=*linha;
				while(aux->botton != NULL)
					aux=aux->botton;
				if(aux->nrocarac==79)
				{
					
					novalinha(&aux);
					aux->botton->inicio->ant=novaL;
					novaL->prox=aux->botton->inicio;
					novaL->ant=NULL;
					aux->botton->inicio=novaL;
					aux->botton->nrocarac++;
					(*cur)=novaL->prox;
					(*linhaux)=aux->botton;
				
				
				}
				else
				{
					auxL=aux->inicio;
					if(auxL->prox!=NULL)
					{
						while(auxL->prox->prox!=NULL)
							auxL=auxL->prox;
						
						
						novaL->prox=auxL->prox;
						auxL->prox->ant=novaL;
						novaL->ant=auxL;
						auxL->prox=novaL;
						aux->nrocarac++;
						(*cur)=novaL->prox;
						(*linhaux)=aux;
						
						
					}
					else
					{
						novaL->prox=auxL;
						novaL->ant=NULL;
						auxL->ant=novaL;
						aux->inicio=novaL;
						aux->nrocarac++;
						(*cur)=novaL->prox;
						(*linhaux)=aux;
					}
				}
		//	}
			
			
		}
		/*	if(l=='.' || l=='!' || l=='?' || aux->nrocarac==79)
			{
				novalinha(&aux);
			}*/
	}
	
}
/*void deletacaracternomeio(TpLinha **linha,TpCaracter *cur, TpLinha *linhaux)
{
	TpCaracter *auxF;
	
	
	
	/*if(cur->ant!=NULL)
	{
		auxF=cur->ant;
		if(auxF->ant!=NULL)
		{
			auxF->ant->prox=cur;
			cur->ant=auxF->ant;
			free(auxF);
			linhaux->nrocarac--;
		}
	}
}*/

void deletacaracter(TpLinha **linha,TpCaracter **cur, TpLinha **linhaux)
{
	TpLinha *aux;
	TpCaracter *auxL, *auxF, *excluir, *ant;
	
	if(*linha!=NULL)
	{
		if((*cur)->prox!=NULL)
		{
			if((*cur)->ant!=NULL)
			{
				auxF=(*cur)->ant;
				if(auxF->ant!=NULL)
				{
					auxF->ant->prox=(*cur);
					(*cur)->ant=auxF->ant;
					free(auxF);
					(*linhaux)->nrocarac--;
					
				}
				else
				{
					aux=(*linhaux);
					if(aux->top!=NULL)
					{
						(*cur)->ant=NULL;
						(*linhaux)->inicio=(*cur);
						(*linhaux)->nrocarac--;
						free(auxF);
						aux=aux->top;
						auxF=aux->inicio;
						while(auxF->prox!=NULL){
						
							auxF=auxF->prox;
							
						}
						(*cur)=auxF;
						(*linhaux)=aux;
						
						
						
					}
					else
					{
						(*cur)->ant=NULL;
						(*linhaux)->inicio=(*cur);
						free(auxF);
						(*linhaux)->nrocarac--;
						
							
					}
					
				}
			}
			
		}
		else
		{	
			
			
			aux=*linha;
			while(aux->botton!=NULL)
				aux=aux->botton;
			auxL=aux->inicio;
			if(auxL!=NULL)
			{
				if(auxL->prox==NULL)//while//
				{
					aux=aux->top;
					free(auxL);
					free(aux->botton);
					auxL=aux->inicio;
				}
				if(auxL->prox!=NULL)
				{
					while(auxL->prox!=NULL)
						auxL=auxL->prox;
					excluir=auxL->ant;
					if(excluir->ant!=NULL)
					{
						excluir->ant->prox=auxL;
						auxL->ant=excluir->ant;
						free(excluir);
						aux->nrocarac--;
					}
					else
					{
						auxL->ant=NULL;
						free(excluir);
						free(auxL);
						
						if(aux->top!=NULL)
						{
							aux=aux->top;
							free(aux->botton);
							aux->botton=NULL;
						}
						else
						{
							free(aux);
							(*linha)=NULL;
							(*linhaux)=NULL;
							(*cur)=NULL;
						}
							
					}
				}	
			}
			
			
		}
	
		
	}	
	
}


void exibe( TpLinha *l)
{
	TpCaracter *c;
	char flag = 1;
	limpatela();
	int x, y, cont;

//	y=edit->pLinha + 6;
	y=7;
	cont = 0;
	//l= edit->inicio;

	while(l != NULL && cont < 21)
	{
		c = l->inicio;
		x =  XINI;
		if(flag)
			x+=5;
		while(c->prox != NULL)
		{
			gotoxy(x, y); printf("%c", c->letra);
			c = c->prox;
			
			x++;
		}
		if(c->letra=='\0')
			flag=1;
		else
			flag=0;
		l = l->botton;
		y++;
		cont++;
	}
}



void exibedois(Listagen *listagen, char palavra[])
{
	
	for(int x=58;x<108; x++)
	{
		gotoxy(x,30);
		printf(" ");
	}
		
	gotoxy(58,30);
	printf("%s",palavra);
}

void ledoArq(TpLinha **linha, TpCaracter **cur, TpLinha **linhaux, TpLinha **paragrafo, Listagen **listagen, char nome[])
{
	char l;
	
	FILE *arq = fopen(nome,"r");
	if(arq==NULL)
	{
		system("cls");
		menu();
		borda();
		info();
		gotoxy(XINI,YINI);
		
		printf("Arquivo nao encontrado");
		getch();
	}
	else
	{
		l=fgetc(arq);
		while(!feof(arq))
		{
			if(l=='\n')
			{
				insereCarac(13, &(*linha), &(*cur), &(*linhaux), &(*paragrafo), (&*listagen));
			}
			else
				insereCarac(l, &(*linha), &(*cur), &(*linhaux), &(*paragrafo), (&*listagen));
			l=fgetc(arq);
		}
		
	}

	fclose(arq);
}

void gravarArq(TpLinha *linha, char nome[])
{
	TpCaracter *c;
	FILE *arq = fopen(nome, "w");
	
	while(linha != NULL)
	{
		c = linha->inicio;
		
		while(c->prox != NULL)
		{
			fputc(c->letra, arq);
			c = c->prox;
		}
		fputc('\n', arq);
		linha = linha->botton;
	}
	fclose(arq);
}

void deletatudo(TpLinha **linha, TpCaracter **cur, TpLinha **linhaux)
{
	TpCaracter *auxL;
	TpCaracter *excluir;
	TpLinha *excluirlinha;
	TpLinha *aux = (*linha);
	if(*linha!=NULL)
	{
		while(aux!=NULL)
		{
			auxL = aux->inicio;
			while(auxL->prox!=NULL)
			{
				auxL= auxL->prox;
				excluir = auxL->ant;
				aux->inicio=auxL;
				free(excluir);
				auxL->ant=NULL;
			}
			if(auxL->prox==NULL)
			{
				aux->inicio=NULL;
				free(auxL);
			}
			excluirlinha=aux;
			aux=aux->botton;
			free(excluirlinha);		
		}
		(*linha)=NULL;
		(*cur)=NULL;
		(*linhaux)=NULL;
	}

}

void Executar()
{	Listagen *listagen = (Listagen*) malloc(sizeof(Listagen)); 
	listagen=NULL;
	int x=XINI+5,y=YINI, j=0, k=0, TL=0;
	char palavra[50], nome[50];
	TpCaracter *cursor=NULL;
	TpCaracter *auxandax=NULL;
	TpLinha *paragrafo = NULL;
	TpLinha *auxcursor;
	TpLinha *linha=NULL;
	TpLinha *linhaux=NULL;
	TpCaracter *auxL=NULL;
	char l;
	gotoxy(x,y);
	do
	{
			l=getch();
		if(l==-32 || l==0|| l==224)
		{
			l=getch();
			switch(l)
				{
					case 77: //direita
							if(cursor!=NULL)
							{
								if(cursor->prox!=NULL)
								{
									cursor=cursor->prox;
									x++;
									gotoxy(x,y);
									
								}
								else
								{
									if(linhaux->botton!=NULL)
									{
										if(cursor->letra=='\0')
											x=XINI+5;
										else
											x=XINI;
										linhaux=linhaux->botton;
										cursor=linhaux->inicio;
										y++;
										
										gotoxy(x,y);
									}
								}
							}
							
					break;

					case 75: // esquerda
							if(cursor!=NULL)
							{
								if(cursor->ant!=NULL)
								{
									cursor=cursor->ant;
									x--;
									gotoxy(x,y);
									
								}
								else
								{
									if(linhaux->top!=NULL)
									{
										linhaux=linhaux->top;
										auxL=linhaux->inicio;
										
										
										
										
										x=XINI;
										while(auxL->prox!=NULL)
										{
											x++;
											auxL=auxL->prox;
										}
										if(auxL->letra=='\0')
											x+=4;
										cursor=auxL=auxL->ant;
										gotoxy(x,--y);
									}
								}
							}
							
					break;
						
					case 80:// baixo
							
					break;
						
					case 72: /// cima
							
					break;
					
					case 71: //home
						if(cursor!=NULL && linhaux!=NULL)
						{
							cursor=linhaux->inicio;
						}					
						
						break;
					case 79: // end
						if(cursor!=NULL)
						{
							while(cursor->prox!=NULL)
								cursor=cursor->prox;		
						}
					
						
						break;
					case 63: //novo texto
							
						deletatudo(&linha,&cursor,&linhaux);
						exibe(linha);
						x=XINI+5;
						y=YINI;
						gotoxy(x,y);
						break;
					
					case 83: // del
					if(cursor->prox!=NULL){
					
						deletacaracter(&linha,&cursor->prox,&linhaux);
						exibe(linha);
					}
						break;
					case 61: // f3
						system("cls");
						borda();
						menu();
						salvar();
						gets(nome);
						gravarArq(linha,nome);
						system("cls");
						exibe(linha);
						borda();
						info();
						menu();
					//	printf("deu certo");
						break;
					
					case 60: //f2 abrir
						
						deletatudo(&linha,&cursor,&linhaux);
						system("cls");
						borda();
						menu();
						abrir();
						gets(nome);
						ledoArq(&linha,&cursor,&linhaux,&paragrafo,&listagen,nome);
						system("cls");
						menu();
						borda();
						info();
						exibe(linha);
						break;
						
				}
					
		}
		else
		{
		
			if(l==8)
			{
					auxcursor=linhaux;
					deletacaracter(&linha,&cursor,&linhaux);
					exibe(linha);
				/*	if(auxcursor!=linhaux)
					{
						
						y--;
						auxandax=linhaux->inicio;	
						while(auxandax->prox!=NULL)
							x++;
						
						
					}
					else
					{
						x--;
					}
					/*if(linhaux!=auxcursor)
					{
						if(auxcursor!=NULL)
							y--;
						if(linhaux->inicio->prox!=NULL)
						{
								if(linhaux->inicio->prox->prox==NULL)
								{
									x=XINI+6;
								}	
								else
									x=XINI;		
						}
						else
						{
							
								if(linhaux->inicio->prox==NULL)
								{
									x=XINI+5;
								}	
								else
									x=XINI;	
						}
					
					}
					else
					{
						x++;
					}*/
					gotoxy(x,y);
			}
			else
			{
				auxcursor=linhaux;
				if(cursor!=NULL)
				{
					
					if(cursor->prox!=NULL)
						inserenomeio(l,&linha,&cursor,&linhaux);
					else
						insereCarac(l,&linha,&cursor,&linhaux,&paragrafo, &listagen);
					
				}
					
				else
					insereCarac(l,&linha,&cursor,&linhaux,&paragrafo,&listagen);
				
				if(linhaux!=auxcursor)
				{
					if(auxcursor!=NULL)
						y++;
					if(linhaux->inicio->prox!=NULL)
					{
							if(linhaux->inicio->prox->prox==NULL)
							{
								x=XINI+6;
							}	
							else
								x=XINI;		
					}
					else
					{
						
							if(linhaux->inicio->prox==NULL)
							{
								x=XINI+5;
							}	
							else
								x=XINI;	
					}
				
				}
				else
				{
					x++;
				}
				
				if(l==' ' || l=='.' || l=='!' || l=='?' || l==13 || l==',' || l==';' || TL==49)
				{
					
					palavra[0]='\0';
					if(l==' ' || l=='.' || l=='!' || l=='?' || l==13 || l==',' || l==';')
						TL=0;
				}
				else
				{
					if(TL<49)
					{
						palavra[TL++]=l;
						palavra[TL]='\0';
						sujestao(listagen,palavra);	
					}
					
				}
				exibedois(listagen,palavra);
				exibe(linha);
				
				gotoxy(x,y);		
			}
		
		}
		
	}while(l!=27);
	
	
	
	
}

int main()
{
	//tela();
	borda();
	menu();
	info();
	//salvar();
	//config();
	Executar();
	getch();
}

