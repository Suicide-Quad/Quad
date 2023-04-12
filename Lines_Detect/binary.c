#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Converts a colored pixel into grayscale.
//
// pixel_color: Color of the pixel to convert in the RGB format.
// format: Format of the pixel used by the surface.
Uint32 To_Black(Uint32 pixel_color, SDL_PixelFormat* format, float seuil)
{
        Uint8 r, g, b;
        SDL_GetRGB(pixel_color, format, &r, &g, &b);
        float average = (0.3*r + 0.59*g + 0.11*b)/255;
	//printf("average == %f",average);
	if((average*1.24 > seuil || average == 1) && average != 0)
	{
		r=255;
		b=255;
		g=255;
	}
	else
	{
        	r=0;
        	b=0;
        	g=0;
	}
        Uint32 color = SDL_MapRGB(format, r, g, b);
        return color;
}

float find_seuil(Uint32* pixels, SDL_PixelFormat* format, int dx, int dy, int LcX, int LcY, int width)
{
	float sum=0;

	int cx = dx;
	int cy = dy;
	int endx = dx + LcX;
	//printf("\ncy == %d, endy == %d, cx == %d, endx == %d",cy,dy+LcY,cx, endx);
	while(cy < dy + LcY)
	{
		Uint8 r, g, b;
		SDL_GetRGB(pixels[cy*width+cx], format, &r, &g, &b);
		float average = (0.3*r + 0.59*g + 0.11*b)/255;
		sum += average;
		cy = (cx+1 > endx ? cy + 1 : cy);
		cx = (cx+1 > endx ? dx : cx + 1);
	}
	//printf(" sum == %f, nb == %d\n",sum, LcX*LcY);
	return sum/(LcX*LcY);
}

void binary(SDL_Surface* surface)
{
	Uint32* pixels = surface->pixels;
	SDL_LockSurface(surface);
	SDL_PixelFormat* format = surface->format;

	float seuil= 0;

	int nb = surface->w/100;
	int LcX [nb];
	int LcY [nb];
	int cx = 0;
	int cy = 0;
	int width = surface->w;
	int height = surface->h;
	int largw = width/nb+width%nb;
	int largh = height/nb+height%nb;


	for (int e = 0; e < nb; e++)
	{
		if (width >= largw)
		{
			LcX[e] = largw;
			width -= largw;
		}
		else if(width > 0)
		{
			LcX[e] = width;
			width = 0;
		}
		if (height >= largh)
		{
			LcY[e] = largh;
			height -= largh;
		}
		else if (height > 0)
		{
			LcY[e] = height;
			height = 0;
		}
	}
	width = surface->w;
	height = surface->h;

	for (int y = 0; y < height - LcY[nb-1]/2; y += LcY[cy-1])
	{
		cx = 0;
		for (int x = 0; x < width - LcX[nb-1]/2; x += LcX[cx-1])
		{
			int cix = x;
			int ciy = y;
			int endx = x + LcX[cx];
			seuil= find_seuil(pixels, format, cix, ciy, LcX[cx], LcY[cy], width);
			while (ciy < y + LcY[cy])
			{
				pixels[ciy*width+cix] = To_Black(pixels[ciy*width+cix], format, seuil);
				Uint8 r, g, b;
				SDL_GetRGB(pixels[ciy*width+cix], format, &r, &g, &b);
				if (r == g && g == b && b == 255)
				{
				}
				else if (r == g && g == b && b ==0)
				{
				}
				else
				{
					errx(0,"Error in To_Black");
				}
				ciy = (cix+1 >= endx ? ciy + 1 : ciy);
				cix = (cix+1 >= endx ? x : cix + 1);
			}
			cx ++;
		}
		cy ++;
	}
	IMG_SavePNG(surface,"./debug_img/binarized.png");
}


