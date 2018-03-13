// ideal move time=20 and distance=10
#ifndef HGL_H
#define HGL_H

#include "Color.h"
#include <SDL2/SDL.h>
#include <stdio.h>

#include <iostream>
#include <cmath>
using namespace std;
#define PI 3.1415926535897932384626433
#define OUTSIDE 0
#define INSIDE 1
#define BOUNDARY 2
#define FLOOR_HEIGHT 20
#define G 9.8


extern SDL_Renderer *renderer;
extern SDL_Event event;
 extern SDL_Window *window;
 extern const int WINDOW_WIDTH ;
 extern const int WINDOW_HEIGHT ;
 extern int fullscreen_flag;
 extern int visit;


//class line;
void init();
void point(float x, float y, Color color=WHITE,float b=1.0);//void HGL_init(int argc, char **argv);
//void HGL_End(void (*func)(void));
void clear(Color color=NONE);
void HGL_run(int argc, char **argv,void (*func)(void (*)()));
float area(float x1,float y1,float x2,float y2,float x3,float y3);
float sdl_mousey();
float sdl_mousex();
void line(float x1,float y1,float x2,float y2, Color color=WHITE);
void SDL_close();
void event_handler();



//void OPENGL_init();
//void OPENGL_end();


class circle
{
  float xc,yc,r;
  Color color;
  public:
    circle(float xc,float yc,float r, Color color=WHITE,string str="Draw");
    void draw();
    circle translate(float xt,float yt,string str="Draw");
    circle move(float xt,float yt,float time=20,string str="Draw");
    circle scale(float s,string str="Draw");
    circle remove();
    bool inside(int x,int y);
    circle fall(float fallspeed);
    circle rise(float risespeed,int maxheight);
    void phong(int x ,int r);
};

#endif
