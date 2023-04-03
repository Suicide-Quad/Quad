#include <math.h>
#define PI 3.14159
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "binary.h"

//width and height of the image in real, size on the floor
#define WIDTH_IMAGE 10
#define HEIGHT_IMAGE 10

//positive distance between the center of robot and the left_bottom point of image
#define DIST_ROBOT_SIDE 10
#define DIST_ROBOT_FRONT 10

//ecart for not wall in bordure
#define ECART 10

#define SCALE 5

void Draw_Line(SDL_Surface* map_s, Uint32 color, int xd0, int yd0, int xf0, int yf0)
{
	int x0 = (xd0+xf0)/2;
	int y0 = (yd0+yf0)/2;
	int px = (xd0 < xf0 ? 1 : -1);
	int py = (yd0 < yf0 ? 1 : -1);
	int rep = 0;

	if (x0 > y0)
	{
		py = 0;
		rep = fmax(xf0,xd0)-fmin(xd0,xf0);
	}
	else
	{
		px = 0;
		rep = fmax(yf0,yd0)-fmin(yd0,yf0);
	}

	for(int j = 0; j < rep; j ++)
	{
		SDL_Rect p = {x0+j*px,y0+j*py,SCALE,SCALE};
		SDL_FillRect(map_s,&p,color);
	}
}

void print_laby(float*** map, size_t size)
{
	float minx = (*(map))[0][0];
	float maxx = minx;
	float miny = (*(map))[0][1];
	float maxy = miny;
	for(size_t i = 0; i < size; i ++)
	{
		for (int j = 0; j < 2; j++)
		{
			if ((*(map+i))[j][0] < minx)
				minx = (*(map+i))[j][0];
			if ((*(map+i))[j][0] > maxx)
				maxx = (*(map+i))[j][0];
			if ((*(map+i))[j][1] < miny)
				miny = (*(map+i))[j][1];
			if ((*(map+i))[j][1] > maxy)
				maxy = (*(map+i))[j][1];
		}
	}

	int decal_negX = (minx < 0 ? (-1)*minx : 0);
	int decal_negY = (miny < 0 ? (-1)*miny : 0) ;

	SDL_Surface* map_s  = SDL_CreateRGBSurface(SDL_SWSURFACE,2*ECART+(maxx-minx),2*ECART+(maxy-miny),32,0,0,0,0);
	Uint32 wh = SDL_MapRGB(map_s->format,255,255,255);
	Uint32 bl = SDL_MapRGB(map_s->format,0,0,0);
	SDL_FillRect(map_s,NULL,wh);

	SDL_LockSurface(map_s);

	for (size_t i = 0; i < size; i ++)
	{
		Draw_Line(map_s, bl ,(int)(*(map+i))[0][0]+decal_negX+ECART,(int)(*(map+i))[0][1]+decal_negY+ECART,(int)(*(map+i))[1][0]+decal_negX+ECART,(int)(*(map+i))[1][1]+decal_negY+ECART);
	}

	IMG_SavePNG(map_s,"./Labyrinthe.png");

	SDL_FreeSurface(map_s);
}

void free_map(float*** map, size_t size)
{
	for (size_t z = 0; z < size; z++)
	{
		for (int i = 0; i < 2; i++)
		{
			free((*(map+z))[i]);
		}
		free(*(map+z));
	}
	free(map);
}

void realloc_map(float*** lines, size_t size)
{
	float**** addr = &lines;
	float*** new= realloc(lines,sizeof(float**)*size);
	free_map(lines,size);
	*(addr) = new;
	for (size_t z = 0; z < size; z ++)
	{
		for (int i = 0; i < 2; i ++)
		{
			*(lines+z) = malloc(sizeof(float*)*2);
			for (int j = 0; j < 2 ; j ++)
			{
				(*lines+z)[j] = malloc(sizeof(float)*2);
			}
		}
	}
}

void swap (float* a, float* b)
{
	float inter = *a;
	*a = *b;
	*b = inter;
}


void push_lines(float** line, float*** lines,size_t* size)
{
	//define pos of segment and put the less greater x into start point segment
	float xd0 = line[0][0];
	float yd0 = line[0][1];
	float xf0 = line[1][0];
	float yf0 = line[1][1];
	if (xd0 > xf0)
	{
		swap(&xd0,&xf0);
		swap(&yd0,&yf0);
	}
	//define theta of the segment
	float X0 = fmax(xd0,xf0)-fmin(xd0,xf0);
	float Y0 = fmax(yd0,yf0)-fmin(yd0,yf0);
	float H0 = sqrtf(X0*X0+Y0*Y0);
	float th0 = acosf(Y0/H0);

	int at_do = 1;

	//research if the segment is the extension or in another existing segments and merch it
	for(size_t i = 0; i < *size && at_do; i++)
	{
		//localisation and theta of the existing segment
		float xd1 = (*(lines+i))[0][0];
		float yd1 = (*(lines+i))[0][1];
		float xf1 = (*(lines+i))[1][0];
		float yf1 = (*(lines+i))[1][1];
		float maxX1 = fmax(xd1,xf1);
		float minX1 = fmin(xd1,xf1);
		float minY1 = fmin(yd1,yf1);
		float maxY1 = fmax(yd1,yf1);
		float X1 = maxX1-minX1;
		float Y1 = maxY1-minY1;
		float H1 = sqrt(X1*X1+Y1*Y1);
		float th1 = acosf(Y1/H1);

		//if same angle
		if (th1 == th0)
		{
			//if include do nothing
			if (xd0 >= minX1 && xd0 <= maxX1 && xf0 >= minX1 && xf0 <= maxX1 &&
					yd0 >= minY1 && yd0 <= maxY1 && yf0 >= minY1 && yf0 <= maxX1)
			{
				at_do = 0;
			}
			//if start is in existing segment, extend the end of existing segment
			else if (xd0 >= minX1 && xd0 <= maxX1)
			{
				(*(lines+i))[1][0] = xf0;
				(*(lines+i))[1][1] = yf0;
				at_do = 0;
			}
			//if end is in existing segment, extend the start of existing segment
			else if (xf0 >= xd1 && xf0 <= xf1)
			{
				(*(lines+i))[0][0] = xd0;
				(*(lines+i))[0][1] = yd0;
				at_do = 0;
			}
		}
	}
	//if new segment, append it
	if (at_do)
	{
		*(size)  = *(size)+1;
		realloc_map(lines,*size);
		(*(lines+*size-1))[0][0]=xd0;
		(*(lines+*size-1))[0][1]=yd0;
		(*(lines+*size-1))[1][0]=xf0;
		(*(lines+*size-1))[1][1]=yf0;
	}
}

void translate_into_map(float** line, float posX_Robot, float posY_Robot, float rot_Robot, int height_image_px, int width_image_px)
{
	for(int i = 0; i < 2; i++)
	{
		line[i][0] = posX_Robot-DIST_ROBOT_FRONT*sinf(rot_Robot)-DIST_ROBOT_SIDE*sinf(rot_Robot+PI/2)+line[i][0]*WIDTH_IMAGE/width_image_px;
		line[i][1] = posY_Robot+DIST_ROBOT_FRONT*cosf(rot_Robot)+DIST_ROBOT_SIDE*cosf(rot_Robot+PI/2)+(height_image_px-line[i][1])*HEIGHT_IMAGE/height_image_px;
	}
}

int isline(int average, int l)//, int coorddav, int coordfav, int coordirld, int coordirlf)
{
	int t1 = 0;
	if (l > average/5  && l < 5*average)
		t1 = 1;
	return t1;
}

float** malloc_tab()
{
	float** line = malloc(sizeof(float*)*2);
	for (int i = 0; i < 2; i ++)
	{
		*(line+i) = malloc(sizeof(float)*2);
	}
	return line;
}

void free_tab(float** line)
{
	for (int i = 0; i < 2; i ++)
	{
		free(*(line+i));
	}
	free(line);
}

void manage_lines( int average, int diagmax, int ListRhoTheta [diagmax][91], int IsLineX[91][diagmax], int IsLineY[91][diagmax], float*** lines, size_t* size, float posX_Robot, float posY_Robot, float rot_Robot, int height_image_px, int width_image_px)
{
	float** line = malloc_tab();

	//if lines is find, merge into the list of existing segments
	for(int t = 0; t <= 90; t++)
	{
		for(int r = 0; r < diagmax; r ++)
		{
			if (isline(average,ListRhoTheta[r][t]))
			{
				line[0][0] = r*sinf(t);
				line[0][1] = r*cosf(t);
				line[1][0] = IsLineX[t][r];
				line[1][1] = IsLineY[t][r];
				translate_into_map(line, posX_Robot, posY_Robot, rot_Robot, height_image_px, width_image_px);
				push_lines(line,lines,size);
			}
		}
	}
	free_tab(line);
}

//get the average of px for forme a segment in image
int get_average(int diagmax, int nbtheta, int ListRhoTheta[diagmax][nbtheta],int ListRhoThetaInter[diagmax][nbtheta], int l)
{
        int max = 0;
        int min = 0;
        int defmin = 0;
        int nblines = 0;
        int nbpixels = 0;
        for (int i = 0 ; i < diagmax; i ++)
        {
                for (int j = 0; j < nbtheta; j++)
                {
                        if ( ListRhoThetaInter[i][j] > ListRhoTheta[i][j])
                                ListRhoTheta[i][j] = ListRhoThetaInter[i][j];
                        int v = ListRhoTheta[i][j];
                        if (v >= l)
                        {
                                if (v > max)
                                        max = v;
                                if (defmin == 0) 
                                {
                                        min = v;
                                        defmin = 1;
                                }
                                if (v < min)
                                        min = v;
                                nblines ++;
                                nbpixels += v;
                        }
                }
        }
        return ((nbpixels-min-max)/(nblines-2));
}

int is_black (SDL_Surface* surface, Uint32 pixel)
{
	SDL_PixelFormat* format = surface->format;
	SDL_Color c;
	SDL_GetRGBA(pixel, format, &c.r, &c.g, &c.b, &c.a);
	float float_color =(float) (c.r+c.g+c.b)/765;

	return float_color <= 0.70;
}
Uint32 my_getpixel(SDL_Surface* surface, int x , int y)
{
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	return *(Uint32*)p;
}
//build the accumalator for find segment
void build_accu(SDL_Surface* image_surface, int diagmax, int ListRhoTheta[diagmax][91],int ListRhoThetaInter [diagmax][91], int IsLineX[91][diagmax], int IsLineY[91][diagmax])
{
	for (int y = 0; y < image_surface->h; y++)
	{
		for (int x = 0; x < image_surface->w; x++)
		{
			Uint32 pixel = my_getpixel(image_surface, x, y);
			if (is_black(image_surface,pixel))
			{
				for (int theta = 0; theta < 91; theta ++)
				{
					int v = (int) y*cos(theta*PI/180)+x*sin(theta*PI/180);
					if (IsLineX[theta][v] >= x-1 && IsLineX[theta][v] <= x+1 && IsLineY[theta][v] >= y-1 && IsLineY[theta][v] <= y+1)
					{
						ListRhoThetaInter [v][theta] += 1;
					}
					else
					{
						if (ListRhoThetaInter [v][theta] > ListRhoTheta[v][theta])
						{
							ListRhoTheta[v][theta] = ListRhoThetaInter [v][theta];
						}
						ListRhoThetaInter[v][theta] = 1;
					}
					IsLineX[theta][v] = x;
					IsLineY[theta][v] = y;
				}
			}
		}
	}
}

SDL_Surface* load_image(const char* path)
{
    SDL_Surface* test=IMG_Load(path);
    SDL_Surface *rep=SDL_ConvertSurfaceFormat(test, SDL_PIXELFORMAT_RGB888, 0);
    SDL_FreeSurface(test);
	if (rep == NULL)
		errx(EXIT_FAILURE,"error load image");
    return rep;
}

//merge line in image define by path into the list lines,needed the pos and the angle of robot
void new_line(char* path, float*** lines, size_t* size, float posX_Robot, float posY_Robot, float rot_Robot)
{
	//init value and table;
	SDL_Surface* image_surface = load_image(path);
	SDL_UnlockSurface(image_surface);
	//binarize image
	binary(image_surface);
	int diagmax = sqrt(image_surface->w*image_surface->w+image_surface->h*image_surface->h);
	int ListRhoTheta [diagmax][91];
	int ListRhoThetaInter [diagmax][91];
	int IsLineX[91][diagmax];
	int IsLineY[91][diagmax];

	for (int i = 0; i < diagmax; i++)
	{
		for (int j = 0; j < 91; j ++)
		{
			ListRhoTheta[i][j]=0;
			ListRhoThetaInter[i][j]=0;
			IsLineX[j][i] = 0;
			IsLineY[j][i] = 0;
		}
	}

	//build accu
	build_accu(image_surface, diagmax, ListRhoTheta, ListRhoThetaInter , IsLineX, IsLineY);

	//average = average of pixel in a line
	int average = get_average(diagmax, 91, ListRhoTheta, ListRhoThetaInter, image_surface->w/20);

	//get line and push
	manage_lines( average, diagmax, ListRhoTheta , IsLineX, IsLineY, lines, size, posX_Robot, posY_Robot, rot_Robot, image_surface->h, image_surface->w);

	SDL_FreeSurface(image_surface);
}

float*** malloc_map()
{
	float*** lines = malloc(sizeof(float**));
	*(lines) = malloc(sizeof(float*)*2);
	for (int j = 0; j < 2 ; j ++)
	{
		(*lines)[j] = malloc(sizeof(float)*2);
	}
	return lines;
}

int main(int argv, char* argc [])
{
	if (argv <= 4)
		errx(EXIT_FAILURE,"call with: posx_robot posy_robot rot_robot path0 path1 ...");
	
	float*** map = malloc_map();

	size_t size = 1; 
	float posx_robot = atof(argc[1]);
	float posy_robot = atof(argc[2]);
	float rot_robot = atof(argc[3]);
	for(int i = 4; i < argv; i ++)
	{
		new_line(argc[i], map, &size, posx_robot, posy_robot, rot_robot);
	}

	print_laby(map,size);

	free_map(map,size);
	SDL_Quit();

	return EXIT_SUCCESS;
}
