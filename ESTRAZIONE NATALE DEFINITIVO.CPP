#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

//*****************************************************************************************************
//												STRUCT
//*****************************************************************************************************

struct details
{
	char name[20];
	int id;
	char coupling[20];
	int pairednumber;
	
	void reset ()	// METHOD FOR CLEAR COUPLING AND PAIREDNUMBER
	{
		strcpy (coupling, "");
		pairednumber = -1;	
	}
	
	details ()	// STRUCTURE BUILDER
	{
		strcpy (name, "");
		id = -1;
		strcpy (coupling, "");
		pairednumber = -1;	
	}	
};

//*****************************************************************************************************
//											GLOBAL VARIABLES
//*****************************************************************************************************

details player [100];

int n_players = 0;	

//*****************************************************************************************************
//												PROTOTIPI
//*****************************************************************************************************
	
void reset(int numofplayers, details *a);	// RESET DATAS COLLECTED IN THE STRUCT

int getplayersnumber();	// GET NUMBER OF THE PLAYERS FROM EXT. INPUT

void getplayersnames (details *a);	// GET PLAYERS' NAMES FROM EXT. INPUT

char carattereMinuscolo (char a[]); // CONVERT NAMES IN LOWERCASE

void coupling();	// CREATE RANDOM COUPLES BETWEEN PLAYERS

void printresults(); // PRINT CUPLING RESULTS

//*****************************************************************************************************
//												MAIN
//*****************************************************************************************************

int main ()
{
	getplayersnumber();
	getplayersnames(player);
	coupling();
	printresults();
		
	return 0;
}

//*****************************************************************************************************
//												METHODS
//*****************************************************************************************************

void reset (int numofplayers, details *a)	// METHOD FOR RECALL RESET IN THE STRUCT
{
	for (int i = 0; i < numofplayers; i++)
	{
		a[i].reset();	
	}	
}

//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************

int getplayersnumber()
{
	do
	{
		printf ("Inserire un numero di giocatori PARI: ");	// INSERT AN EVEN PLAYERS NUMBER
		scanf("%d", &n_players);
	}
	
	while (n_players %2 != 0);	// IF IS ODD REDO
	
	return n_players;
}

//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************

void getplayersnames (details *a)
{	
	for (int i = 0; i < n_players; i++)	// COLLECTING NAMES AND SAVING THEM IN A STRUCT
	{
		a[i].id = i;
		printf ("\nInserire il nome numero %d: ", i + 1);
		scanf("%s", a[i].name);
	}	
}

//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************

char carattereMinuscolo (char a[])	// TRANSFORM CHARACTERS IN LOWERCASES
	
{	
	for (int i = 0; i < 20; i++)
	{
		if (a[i] >= 'A' && a[i] <= 'Z')
			
			a[i] = a[i] + 32;
							
		else 
				
			a[i] = a[i];								
	}		
}
	
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************	

void coupling ()
{	
	srand (time(NULL));
	
	bool flag = true;
	
	while (flag)
	{
		flag = false;
		int err = 0;
		
		for (int i = 0; i < n_players; i++)	
		{	
			int nrandom = rand() % n_players;	// GENERATE RANDOM NUMBERS
			
			if (nrandom == i)	// CHECK THAT A NAME IS NOT EXTRACTED WITH ITSELF
			{
				i--;
				flag = true;
				break;	
			}
				
			player[i].pairednumber = nrandom;	// NUMBER ASSIGNMENT
			strcpy (player[i].coupling, player[nrandom].name);	// NAME ASSIGNMENT

			
			for (int i1 = 0; i1 < i; i1++)	// CHECK THAT A NAME IS NOT ALREADY EXTRACTED
			{
				if (player[i].pairednumber == player[i1].pairednumber)
				{
					reset(n_players, player); // CLEAN ALL
					err = 1;
					flag = true;
					break;
				}
			}		
		
			if (err == 1)
				break;	
		}		
	}		
}

//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************

void printresults()
{
	int cnt = 0;
	bool tamp = true;
	
	while(tamp)
	{
		char user_name[20] = {""};
		
		printf("\n\n");
		system("pause");
		system("cls");	// CLEAR THE SCREEN
		
		printf("\tBenvenuto all'estrazione dei regali di Natale!\n\n\tPer favore inserisci il tuo nome: ");
		scanf("%s", user_name);
		carattereMinuscolo(user_name);	// TRANSFORM CHARACTERS IN LOWERCASES
		
		for (int i = 0; i < n_players; i++)
		{	
			if(strcmp (user_name, player[i].name) == 0)
			{
				printf("\n\tDovrai fare un regalo a: %s", player[i].coupling);
				printf("\n\n");
				cnt ++;
				break;
			}
		}
	
		if(cnt == n_players)	// IF I HAVE PRINTED ALL THE CASES -> EXIT
		tamp = false;
	}
	
	printf ("\n************ESTRAZIONE TERMINATA, BUON NATALE**************");
}
