#define direct 0
#define formula 1
#define totaldelete 0
#define fewpixel 1

extern "C"
#include <cmath>
#include "HGL.h"
#define FALL_FUNC 0
#define remove_flag 0

int visit=0;

circle::circle(float xc,float yc,float r,Color color,string str):xc(xc),yc(yc),r(r),color(color)
{
  if (str=="nodraw")
  return;
  draw();
}

void circle::phong(int x,int y)
{
  int x1=200,y1=200,z1=300; // light source
  int z = sqrt (r*r-(x-xc)*(x-xc)-(y-yc)*(y-yc));
  float xn= x-xc;
  float yn= y-yc;
  float zn= z;

  float xl= x1-x;
  float yl= y1-y;
  float zl= z1-z;

  float xnn=xn/sqrt(xn*xn+yn*yn+zn*zn);
  float ynn=yn/sqrt(xn*xn+yn*yn+zn*zn);
  float znn=zn/sqrt(xn*xn+yn*yn+zn*zn);

  float xll=xl/sqrt(xl*xl+yl*yl+zl*zl);
  float yll=yl/sqrt(xl*xl+yl*yl+zl*zl);
  float zll=zl/sqrt(xl*xl+yl*yl+zl*zl);

  float fact= xnn*xll+ynn*yll+zll*znn;

  // if (fact>0.98)
  // {
  //   (x,y,WHITE,1) ;
  //   return;
  // }
  if (fact <0) fact=0;
  fact+=0.01;
  if (fact>1) fact=1;
  //if (fact <0.3) fact+=0.1;
  if (fact==1)
  {
    //fact=1;
    point (x,y,WHITE,fact);
      return;
  }
  point (x,y,color,fact);




}

void circle::draw()
{
  float x=0, y=r;
  float p=1-r;
  while (x<=y)
  {
    for (int i=-x;i<=+x;i++)
    {
      phong(i+xc,y+yc);
      phong(i+xc,-y+yc);
    }

    for (int i=-y;i<=+y;i++)
    {
      phong(i+xc,x+yc);
      phong(i+xc,-x+yc);
    }

    x++;
    if (p<0)
    p+=2*x+1;
    else
    {
      y-=1;
      p+=2*x+1-2*y;
    }
  }
  if (color.r != NONE.r || color.g != NONE.g || color.b != NONE.b)
  SDL_RenderPresent(renderer);

}

circle circle::translate(float xt,float yt,string str)
{
  //return circle(xc+xt,yc+yt,r,color);
  return circle(xc+xt,yc+yt,r,color,str);

}

circle circle::scale(float s,string str)
{
  //return circle(xc+xt,yc+yt,r,color);
  return circle(xc,yc,r*sqrt(s),color,str);

}

#if remove_flag== totaldelete
circle circle::remove()
{
 // return circle(xc,yc,r,NONE);

     SDL_SetRenderDrawColor(renderer, NONE.r*255, NONE.g*255, NONE.b*255, 0);
     SDL_RenderClear(renderer);

     for (int i=0;i<=FLOOR_HEIGHT-1;i++)
line(0,i,WINDOW_WIDTH,i);
}

#elif remove_flag == fewpixel
circle circle::remove()
{
  float x=0, y=r;
  float p=1-r;
  for (int k=1;k<=10;k++)
  {
    for (int i=0;i<=WINDOW_WIDTH;i++)
    {
      point(i,y+yc,NONE);
    }
    x++;
    if (p<0)
    p+=2*x+1;
    else
    {
      y-=1;
      p+=2*x+1-2*y;
    }
  }

  SDL_RenderPresent(renderer);
  //while(1) {}

}

#else
#error "remove flag wrong"


#endif

circle circle::move(float xt,float yt,float time,string str)
{
//  remove();
 remove();

// for (int i=0;i<=FLOOR_HEIGHT-1;i++)
// line(0,i,WINDOW_WIDTH,i);

// for (int i=0;i<=FLOOR_HEIGHT-1;i++)
// {
//   SDL_SetRenderDrawColor(renderer, WHITE.r*255, WHITE.g*255, WHITE.b*255, 0);
//   SDL_RenderDrawLine(renderer,0,WINDOW_HEIGHT-i,WINDOW_WIDTH,WINDOW_HEIGHT-i);
//
// }


  *this=translate(xt,yt,str);
  SDL_Delay(time);
  return *this;
}


  bool circle::inside(int x,int y)
  {
    float d= sqrt((x-xc)*(x-xc)+(y-yc)*(y-yc));
    if (d>r)
      return OUTSIDE; //outside
    else if (d==r)
      return BOUNDARY;
    else
      return INSIDE;
  }

    #if FALL_FUNC==formula
  circle circle::fall(float fallspeed)
  {

    // float heightinit=yc;
    // float u=fallspeed;
    // float v=u;
    int del_time =8/fallspeed;
    while(1)
    {
      move(0,-10,del_time); //fallspeed v/sec
      if (del_time>1)
      del_time--;
       // float s=(heightinit-yc)+1;
       // v=sqrt(u*u+2*G*s);
       // cout<<v<<" ";
       if (yc-r<=FLOOR_HEIGHT)
       break;

    }
    // if (v==0)
    // return *this;
     // else
     // rise(v);
  }

  circle circle::rise(float risespeed)
  {
    int heightinit=yc;
    int u=risespeed;
    int v;
    while(1)
    {
      int s=yc-heightinit;
      v=sqrt(u*u-2*G*s);
      if (v<=0)
      break;
      move(0,1,100.0/v); //fallspeed v/sec

    }

    fall(0);
  }

  #elif FALL_FUNC== direct


  circle circle::fall(float risespeed)
  {
      static int count=10;
      int x=yc;

        do
          {
            if (SDL_PollEvent(&event))
            event_handler();
              move(0,-1,count); //fallspeed v/sec
          }
              while (yc-r>FLOOR_HEIGHT);
        count-=2;
        if (count==0)
        {
          count=10;
          return *this;
        }
        else
            rise(risespeed,x);
  }

  circle circle::rise(float risespeed,int maxheight)
  {
    static int count =9;
    static int height=maxheight-100;
    if (visit==0)
    {
      count=9;
     height=maxheight-100;
    }
    visit=1;
      do
        {
          if (SDL_PollEvent(&event))
          event_handler();

            move(0,1,count); //fallspeed v/sec
        }
            while (yc<height);
            height-=100;
      count-=2;

          fall(risespeed);
  }

  #else
  #error "lol"

  #endif
