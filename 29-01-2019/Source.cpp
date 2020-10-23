#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include<string.h>

typedef struct  firewall firewall;
struct firewall {
	char ip_sursa[20], ip_dest[20], prot[10], permisiune[10], directie[10], ip[10], ip_banned[10];
}f1[10],f2[10],f3[10];

void citire1(char*file_name, firewall f1[100], int *nr)
{
	FILE*traffic = fopen(file_name, "r");
	if (traffic == NULL)
	{
		printf("Eroare citire fisier!");
		return;
	}
	*nr = 0;
	while (!feof(traffic))
	{
		fscanf(traffic, "%s", f1[*nr].ip_sursa);
		fscanf(traffic, "%s", f1[*nr].ip_dest);
		fscanf(traffic, "%s", f1[*nr].prot);
		(*nr)++;
	}
	for (int i = 0; i < *nr; i++)
	{
		fprintf(stdout, "%s -> %s [%s]\n", f1[i].ip_sursa, f1[i].ip_dest,f1[i].prot);

	}
	fclose(traffic);
}

void citire2(char*file_name, firewall f2[100], int*nrr)
{
	FILE* reguli = fopen(file_name, "r");
	if (reguli == NULL)
	{
		printf("Eroare citire fisier!");
		return;

	}
	*nrr = 0;
	while (!feof(reguli))
	{
		fscanf(reguli, "%s", f2[*nrr].permisiune);
		fscanf(reguli, "%s", f2[*nrr].directie);
		fscanf(reguli, "%s", f2[*nrr].ip);
		fscanf(reguli, "%s", f2[*nrr].prot);
		(*nrr)++;
	}
	for (int i = 0; i < *nrr; i++)
	{
		fprintf(stdout, "%s %s %s %s\n", f2[i].permisiune, f2[i].directie, f2[i].ip, f2[i].prot);

	}
	fclose(reguli);
}
int gasire_block_all(firewall f2[10], int nrr)
{
	int i;
	for (i = 0; i < nrr; i++)
	{
		if (strcmp(f2[i].permisiune,"BLOCK") == 0 && strcmp(f2[i].directie,"ALL")==0)
		{
			return i;
		}
	}
}

void verificare(firewall f1[100], int nr, firewall f2[100], int nrr) {
	int i, j,k;
	k=gasire_block_all(f2, nrr);
	for (i = 0; i < nr; i++)
	{
	
		for (j = 0; j < nrr; j++)
		{
			if (k == 0)
			{
				break;
			}
			else
			{
			if (strcmp(f1[i].ip_sursa, f2[i].ip) == 0 && strcmp(f2[i].directie, "INBOUND") == 0)
			{
				if (strcmp(f2[i].permisiune, "BLOCK") == 0 && strcmp(f2[i].prot, f1[i].prot)==0)
				{
					break;
				}
				if (strcmp(f2[i].permisiune, "ALLOW")==0 && strcmp(f2[i].prot,f1[i].prot)== 0)
				{
					fprintf(stdout, "%s -> %s [%s]\n", f1[i].ip_sursa, f1[i].ip_dest, f1[i].prot);
					break;
				}

			}

			

			if (strcmp(f1[i].ip_dest, f2[i].ip) == 0 && strcmp(f2[i].directie, "OUTBOUND") == 0)
			{
				if (strcmp(f2[i].permisiune, "BLOCK")==0 && strcmp(f2[i].prot, f1[i].prot) == 0)
				{
					break;
				}
				if (strcmp(f2[i].permisiune, "ALLOW") == 0 && strcmp(f2[i].prot, f1[i].prot)==0)
				{
					fprintf(stdout, "%s -> %s [%s]\n", f1[i].ip_sursa, f1[i].ip_dest, f1[i].prot);
					break;
				}

			}
			}
          
			
				
			}
			
		}
	}

//void citire_ip_banned(char*file_name, firewall f3[50], int *nrb)
//{
//	FILE*banned_ip = fopen(file_name, "r");
//	if (banned_ip == NULL)
//	{
//		printf("Eroare citire fisier!");
//		return;
//	}
//	*nrb = 0;
//	while (!feof(banned_ip))
//	{
//		fscanf(banned_ip, "%s", f3[*nrb].ip_banned);
//		(*nrb)++;
//	}
//	for (int i = 0; i < *nrb; i++)
//	{
//		printf("%s", f3[i].ip_banned);
//	}
//}

void gasire_ip_banned(firewall f1[10], int nr, firewall f2[10], int nrr, char*file_name)
{
	int i, j, k = 0, m = 0, l;
	int a = 0, c, b = 0;
	char aux[30], *aux1[30];
	for (j = 0; j < nrr; j++)
	{
		if (strcmp(f2[j].permisiune, "BLOCK") == 0)
		{

			for (i = 0; i < nr; i++)
			{

				//if (strcmp(f1[i].ip_sursa, f2[j].ip) == 0)
				//{
				//	k++;

				//	if (k == 3)
				//	{
				//		m++;
				//		strcpy(aux, f1[i].ip_sursa);

				//			FILE*f = fopen(file_name, "w");
				//			for(l=0;l<m;l++)
				//			{
				//				fprintf(f, "%s\n", aux);
				//			}


				//			fclose(f);
				//			//k = 0;
				//		break;
				//	}

				//}
				if (strcmp(f1[i].ip_dest, f2[j].ip) == 0)
				{

					a++;

					if (a == 3)
					{
						m++;


						FILE*f = fopen(file_name, "w");
						for (l = 0; l < m; l++)
						{
							aux1[l] = (char*)malloc(50);
							strcpy(aux1[l], f1[i].ip_dest);
							b++;
						}
						for (c = 0; c < b; c++)
						{
							fprintf(f, "%s\n", aux1[c]);
						}

						//fclose(f);
					//a = 0;
						break;

					}

					//}
				/*	for (l = 0; l<m-1; l++)
					{
						FILE*f = fopen(file_name, "w");
						fprintf(f, "%s \n%s", aux,aux1);
					}*/


				}


			}



		}
	}


}

int main()
{
	int nr,nrr,nrb;
	char s1[50] = "traffic";
	char s2[50] = "reguli";
	char s3[50] = "banned_ip";
	citire1(s1, f1, &nr);
	printf("\n");
	citire2(s2, f2, &nrr);
	printf("\n");
	verificare(f1, nr, f2, nrr);
	printf("\n");
	gasire_ip_banned(f1, nr, f2, nrr, s3);
	
	_getch();
}