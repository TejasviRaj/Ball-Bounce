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

void point(float x, float y, Color color,float b) {
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
  SDL_SetRenderDrawColor(renderer, color.r*255*b, color.g*255*b, color.b*255*b, 255);
  SDL_RenderDrawPoint(renderer, x,WINDOW_HEIGHT-y);
  //  SDL_RenderDrawPoint(renderer, x,y);

}


void SDL_initialize()
{

    SDL_Init(SDL_INIT_VIDEO);
  //  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    window = SDL_CreateWindow("Ball bounce",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, NONE.r*255, NONE.g*255, NONE.b*255, 0);
    SDL_RenderClear(renderer);
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

void line(float x1,float y1,float x2,float y2,Color color)
{

  float dx=x2-x1;
  float dy=y2-y1;
  float steps,xinr,yinr;
  float x=x1;
  float y=y1;

    steps=fabs(dx);
    xinr=dx/steps;
    for (size_t i = 0; i < steps; i++)
      {
        point (x,y,BLACK);

        x+=xinr;
      }

    //  SDL_RenderPresent(renderer);

}
