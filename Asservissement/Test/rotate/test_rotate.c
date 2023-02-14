#include "../asserv.h"
#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


float Pi = 3.14;


#define BOLD_FONT "./DejaVuSans-Bold.ttf"
#define FONT "./DejaVuSans.ttf"



//for transform v in good coord in graph
int conv (float v, float maxv, int maxg)
{
	return v*maxg/maxv;
}





//pretty print in console
void printret(float retour[2][6],float time)
{
	static int rep = 0;
	FILE* Deb = (rep == 0 ?fopen("rotate/Debug_rt.txt","w"):fopen("rotate/Debug_rt.txt","a"));
	printf("__________________________________________\nRep: %d -> %fs  %frad\n",rep,time,retour[0][5]);
	fprintf(Deb,"__________________________________________\nRep: %d -> %fs  %frad\n",rep,time,retour[0][5]);
    for(int i = 0; i < 2; i++)
    {
        char dir []= "Right";
        if (i == 0)
		{
            dir[0] = 'L';
			dir[1] = 'e';
			dir[2] = 'f';
			dir[3] = 't';
			dir[4] = 0;
		}
        printf("For %s\n",dir);
		fprintf(Deb,"For %s\n",dir);
        for (int j = 0; j <5; j++)
        {
            char* valname = malloc(20*sizeof(char));
            if (j == 0)
                sprintf(valname,"ValEncodeur");
            else if (j == 1)
				sprintf(valname,"Distance");

             else if (j == 2)
				sprintf(valname,"Speed");

            else if (j == 3)
				sprintf(valname,"Error");

            else if (j == 4)
				sprintf(valname,"Commande");

            printf("%c%s = %f\n",9,valname,retour[i][j]);
			fprintf(Deb,"%c%s = %f\n",9,valname,retour[i][j]);
			free(valname);
        }
    }
	rep ++;
	fclose(Deb);
}





SDL_Surface* Init_graph(float d, int lx, int ly, int w, int h, int p, int l, int L)
{
	TTF_Init();

	//create image and font
	SDL_Surface* Graph = SDL_CreateRGBSurface(SDL_SWSURFACE, 2*p+w,2*p+h,32,0,0,0,0);
	TTF_Font * pol = TTF_OpenFont(FONT,28);
	TTF_Font * poli = TTF_OpenFont(FONT,19);
	TTF_Font * polu = TTF_OpenFont(BOLD_FONT,42);
	TTF_Font * polt = TTF_OpenFont(BOLD_FONT,40);
	TTF_SetFontStyle(polt,TTF_STYLE_UNDERLINE);

	//if graph error
  	if (Graph == NULL)
		errx(1,"Graph  not build correctly");

	//create color
	Uint32 wh = SDL_MapRGB(Graph->format,255,255,255);
	Uint32 pur = SDL_MapRGB(Graph->format,213,51,255);
	SDL_Color rgc = {237,49,49,0};
	SDL_Color blc = {10,10,240,0};
	SDL_Color noirc = {0,0,0,0};
	SDL_Color purc = {213,51,255,0};

	//build graph strucuture
  	SDL_FillRect(Graph,NULL,wh);
  	SDL_Rect absci = {p,p+h+1,w,l};
  	SDL_Rect ordo2 = {p+w+1,p+1,l,h};
	SDL_Rect ordo = {p-l,p+1,l,h};
	SDL_FillRect(Graph,&absci,0);
	SDL_FillRect(Graph,&ordo,0);
	SDL_FillRect(Graph,&ordo2,pur);

	//build title and legende
	SDL_Surface* texte = TTF_RenderText_Blended(pol,"Speed",blc);
	if (texte == NULL) //if error with texte
		errx(1,"Error when creating texte");
	SDL_Rect pos = {10,36,0,0};
	SDL_BlitSurface(texte, NULL,Graph,&pos);
	//_______ legende 2
	SDL_FreeSurface(texte);
	pos.x = 10;
	pos.y = 6;
	texte = TTF_RenderText_Blended(pol,"SpeedExpected",rgc);
	SDL_BlitSurface(texte, NULL,Graph,&pos);
	//_______ legende 3
	pos.x = w+115;
	pos.y = 6;
	SDL_FreeSurface(texte);
	texte = TTF_RenderText_Blended(pol,"Angle",purc);
	SDL_BlitSurface(texte, NULL,Graph,&pos);
	//_______ tiltle
	SDL_FreeSurface(texte);
	pos.x = p+w/3;
	pos.y = 30;
	texte = TTF_RenderText_Blended(polt,"Regulateur PID",noirc);
	SDL_BlitSurface(texte, NULL,Graph,&pos);
	//_______ subtiltle
	SDL_FreeSurface(texte);
	pos.x = p+w/3+100;
	pos.y = 70;
	texte = TTF_RenderText_Blended(polt,"Rotate",noirc);
	SDL_BlitSurface(texte, NULL,Graph,&pos);


	//build graduation
	for (float i =0.125 ; i<ly; i+=0.125)
	{
		int v = conv(i,ly,h);
		SDL_Rect tr = {p-l-L-2,p+h-v+1,L,l/2};
		SDL_FillRect(Graph,&tr,0);

		SDL_Rect pos = {p-l-L-2-60,p+h-v-10,0,0};
		SDL_FreeSurface(texte);
		char* sv = malloc(10*sizeof(char)) ;
		sprintf(sv,"%.3f",i);
		texte = TTF_RenderText_Blended(poli,sv,noirc);
		SDL_BlitSurface(texte, NULL,Graph,&pos);
		free (sv);
	}
	for (float i =0.25 ; i<d; i+=0.25)
	{
		int v = conv(i,d,h);
		SDL_Rect tr = {p+w+5+l,p+h-v-l/2,L,l/2};
		SDL_FillRect(Graph,&tr,pur);

		SDL_Rect pos = {p+w+40,p+h-v-10-l/2,0,0};
		SDL_FreeSurface(texte);
		char* sv = malloc(10*sizeof(char)) ;
		sprintf(sv,"%.2f",i);
		texte = TTF_RenderText_Blended(poli,sv,purc);
		SDL_BlitSurface(texte, NULL,Graph,&pos);
		free (sv);
	}
	for (float i =0.2 ; i<lx; i+=0.2)
	{
		int v = conv(i,lx,w);
		SDL_Rect tr = {p+v-1,p+l+h+3,l/2,L};
		SDL_FillRect(Graph,&tr,0);

		SDL_Rect pos = {p+v-15,p+l+h+30,0,0};
		SDL_FreeSurface(texte);
		char* sv = malloc(10*sizeof(char)) ;
		sprintf(sv,"%.1f",i);
		texte = TTF_RenderText_Blended(poli,sv,noirc);
		SDL_BlitSurface(texte, NULL,Graph,&pos);
		free (sv);
	}

	//build end of information on graph
	SDL_FreeSurface(texte);
	pos.x = p-l-L-2;
	pos.y = p+l+h+3;
	texte = TTF_RenderText_Blended(poli,"0",noirc);
	SDL_BlitSurface(texte, NULL,Graph,&pos);
	//________
	SDL_FreeSurface(texte);
	pos.x = p-20;
	pos.y= p-10;
	texte = TTF_RenderText_Blended(polu,"^",noirc);
	SDL_BlitSurface(texte, NULL,Graph,&pos);
	//________
	SDL_FreeSurface(texte);
	pos.x = p+w-14;
	pos.y= p-10;
	texte = TTF_RenderText_Blended(polu,"^",purc);
	SDL_BlitSurface(texte, NULL,Graph,&pos);
	//________
	SDL_FreeSurface(texte);
	pos.x = p+w-10-15;
	pos.y = p+h-23;
	texte = TTF_RenderText_Blended(polu,">",noirc);
	SDL_BlitSurface(texte, NULL,Graph,&pos);
	//________
	SDL_FreeSurface(texte);
	pos.x = p+w-10;
	pos.y = p-25;
	texte = TTF_RenderText_Blended(poli,"rad",purc);
	SDL_BlitSurface(texte, NULL,Graph,&pos);
	//________
	SDL_FreeSurface(texte);
	pos.x = p-20;
	pos.y = p-25;
	texte = TTF_RenderText_Blended(poli,"m/s",noirc);
	SDL_BlitSurface(texte, NULL,Graph,&pos);
	//________
	SDL_FreeSurface(texte);
	pos.x = p+w+10;
	pos.y = p+h-10;
	texte = TTF_RenderText_Blended(poli,"s",noirc);
	SDL_BlitSurface(texte, NULL,Graph,&pos);

	TTF_CloseFont(pol);
	TTF_CloseFont(poli);
	TTF_CloseFont(polu);
	TTF_CloseFont(polt);
	SDL_FreeSurface(texte);

	return Graph;
}





void Print_graph(SDL_Surface* Graph,float retour[2][6], float a, int lx, int ly, int w, int h, int p, int l, int L, float time,float angle)
{
	//create color
	Uint32 rg = SDL_MapRGB(Graph->format,237,49,49);
	Uint32 bl = SDL_MapRGB(Graph->format,10,10,240);
	Uint32 pur = SDL_MapRGB(Graph->format,213,51,255);
	//build crosse on graph
	int vx = conv(time,lx,w);
	int vyR = conv(retour[1][2],ly,h);
	int angl = conv(a-angle-1,a,h);
	int vspeed = conv(retour[1][4],ly,h);
	SDL_Rect barre2 = {p+vx,p+h+1-vspeed-l-l/2,L/4,l*2};
	SDL_FillRect(Graph,&barre2,rg);
	SDL_Rect barre3 = {p+vx,p+h+1-vyR-l,L/4,l};
	SDL_FillRect(Graph,&barre3,bl);
	SDL_Rect barre4 = {p+vx,p+1+h-angl-l,L/4,l};
	SDL_FillRect(Graph,&barre4,pur);
}





void Close_graph(SDL_Surface* Graph, char* path)
{
	//close and save all
	IMG_SavePNG(Graph,path);
	SDL_FreeSurface(Graph);
}





int main(int argc, char* argv[])
{
	char* path;
	if (argc >2)
		errx(1,"Parametre erreur");
	else if (argc == 2)
		path = argv[1];
	else
		path = "rotate/GraphPIDrt.png";

	//for test pid
  	float angle = Pi;  //in m
	float a = angle+1;
  	float time = 0;
  	float lastTime = 0;
  	float time_reg = 0.01;
  	float nbTurnsLeft = 0;
  	float nbTurnsRight = 0;
  	float retour[2][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0}};
	float PI = 3.14;
	float WHEEL_DIAG = 0.12;

	//size for Graph
	int w = 1000; //width graph
	int h = 800;  //hight graph
	int p = 100;  //position graph sur image (0)
	int l = 5;  //largeur trait
	int L = 20;  //largeur gros trait 
	int ly = 2;  //limite des valeurs en y
	int lx = 5;  //limite des valeurs en x
	int left = -1;

	SDL_Surface* Graph= Init_graph(a,lx,ly,w,h,p,l,L);

	//start of debugging asserv
  	while (angle != 0 && time <= lx)
  	{
	  	if (time -lastTime >= time_reg || time == 0) //not neccesary but put for not prettyprint every time
	  	{
		  	angle = rotate(angle,left,time,nbTurnsLeft,nbTurnsRight,retour);
		  	printret(retour,time);
		  	lastTime = time;
		  	nbTurnsRight = (retour[1][4]*time_reg)/(PI*WHEEL_DIAG);
		  	nbTurnsLeft = (retour[0][4]*time_reg)/(PI*WHEEL_DIAG);

			Print_graph(Graph, retour, a, lx, ly, w, h, p, l, L,time,angle);

	  	}
	  	time+=0.001;
  	}

	Close_graph(Graph,path);

  	return 1;
}
