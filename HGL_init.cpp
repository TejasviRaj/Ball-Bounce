extern "C"
#include <cmath>
#include "HGL.h"

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 700;
int fullscreen_flag;

SDL_Event event;
 SDL_Window *window;
 SDL_Renderer *renderer;
void OPENGL_INIT(int argc,char **argv);
void OPENGL_end();
void SDL_initialize();
void SDL_close();
void event_handler();

float sdl_mousey()
{
  return WINDOW_HEIGHT-event.button.y;
}
float sdl_mousex()
{
  return event.button.x;
}

void HGL_run(int argc, char **argv,void (*func)(void (*func1)()))
{
/*   OPENGL_INIT(argc,argv);
    glutDisplayFunc(func);
    OPENGL_end();*/

   SDL_initialize();
   func(event_handler);


  	//Free resources and close SDL
  	SDL_close();
}

void point(float x, float y, Color color, float b,string rotate,float angle,float xc,float yc) {
/*	glBegin(GL_POINTS);
  glColor3f(color.r*b, color.g*b, color.b*b);
  angle=(PI/180)*angle;
  if(rotate=="TRUE")
  {
    x=(x-xc)*cos(angle)-(y-yc)*sin(angle)+xc;
    y=(x-xc)*sin(angle)+(y-yc)*cos(angle)+yc;
  }
	glVertex2f(x, y);
	glEnd(); */
  SDL_SetRenderDrawColor(renderer, color.r*255, color.g*255, color.b*255, 255);
  SDL_RenderDrawPoint(renderer, x,WINDOW_HEIGHT-y);
  //  SDL_RenderDrawPoint(renderer, x,y);

}


void SDL_initialize()
{

    SDL_Init(SDL_INIT_VIDEO);
  //  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    window = SDL_CreateWindow("SDL2 Keyboard/Mouse events",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_SetWindowFullscreen(window,0);
    fullscreen_flag=0;
	}



void SDL_close()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();;
}

void event_handler()
{
  switch(event.type)
  {
    case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
          case SDLK_RETURN:
                if (fullscreen_flag==1)
                {
                  SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
                  fullscreen_flag=0;
                }
                else
                {
                  SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);
                  fullscreen_flag=1;
                }
                break;
          case SDLK_ESCAPE:
                SDL_close();
                break;

        }
      break;
    case SDL_QUIT:
        SDL_close();
        break;
  }
}

void line(float x1,float y1,float x2,float y2,Color color,string str)
{
  if (str=="nodraw")
  return;
  float dx=x2-x1;
  float dy=y2-y1;
  float steps,xinr,yinr;
  float x=x1;
  float y=y1;
  if (dx==0)
  {
    steps=fabs(dy);
    yinr=dy/steps;
    for (size_t i = 0; i < steps; i++)
      {
        point (x,y,color);
        y+=yinr;
      }
  }
  else if (dy==0)
  {
    steps=fabs(dx);
    xinr=dx/steps;
    for (size_t i = 0; i < steps; i++)
      {
        point (x,y,color);
        x+=xinr;
      }
  }
  else
  {
    if (fabs(dx)>fabs(dy))
        steps=fabs(dx);
      else
        steps=fabs(dy);

      xinr=dx/steps;
      yinr=dy/steps;

      for (size_t i = 0; i < steps; i++)
        {
          point (x,y,color);
          x=x+xinr;
          y=y+yinr;
        }
  }
  SDL_RenderPresent(renderer);
}
