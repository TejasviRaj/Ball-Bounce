#define direct 0
#define formula 1

extern "C"
#include <cmath>
#include "HGL.h"
#define FALL_FUNC 0


circle::circle(float xc,float yc,float r,Color color,string str):xc(xc),yc(yc),r(r),color(color)
{
  if (str=="nodraw")
  return;
  draw();
}

void circle::draw()
{
  float x=0, y=r;
  float p=1-r;
  while (x<=y)
  {
    point(x+xc,y+yc,color);
    point(-x+xc,-y+yc,color);
    point(-x+xc,y+yc,color);
    point(x+xc,-y+yc,color);
    point(y+xc,x+yc,color);
    point(-y+xc,-x+yc,color);
    point(-y+xc,x+yc,color);
    point(y+xc,-x+yc,color);
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

circle circle::remove()
{
  return circle(xc,yc,r,NONE);
}

circle circle::move(float xt,float yt,float time,string str)
{
//  remove();
  remove();
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
              move(0,-1,count); //fallspeed v/sec
          }
              while (yc-r>FLOOR_HEIGHT);
        count-=2;
        if (count==0)
            return *this;
        else
            rise(risespeed,x);
  }

  circle circle::rise(float risespeed,int maxheight)
  {
    static int count=9;
    static int height=maxheight-100;
      do
        {
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
