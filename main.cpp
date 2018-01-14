#include"HGL.h"
//#include"Color.h"
void display(void (*func)(void));

int main(int argc, char **argv) {
  HGL_run(argc,argv,display);
}

void display(void (*eventhandle)(void))
{

//  rectangle r(200,200,50,100);
//  r.rotate(135).scale(2,3);
/*line l(450,50,550,200);
line l1(0,0,1926,0);
l1.rotate(45,"Draw",0,0);
l.reflect(45);*/
//triangle c(0,100,100,100,50,50);
line(0,FLOOR_HEIGHT-1,WINDOW_WIDTH,FLOOR_HEIGHT-1);
circle c(200,500,50);
while(1)
{
  if (SDL_PollEvent(&event))
  {
    eventhandle();


    switch(event.type)
    {
      case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
                case SDL_BUTTON_LEFT:
                        //  c.resize(1.2);
                         break;

                case SDL_BUTTON_RIGHT:
                //    c.remove();
                //   c=c.scale(0.8,0.8);
                //   SDL_Delay(20);
                    break;
                default:
                //    SDL_ShowSimpleMessageBox(0, "Mouse", "Some other button was pressed!", window);
                    break;
            }
            break;
  /*  case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
            case SDLK_LEFT:
                  c.move(-10,0,20);
                  break;
            case SDLK_RIGHT:
                  c.move(10,0,20);
                  break;
            case SDLK_UP:
                  c.move(0,10,20);
                  break;
            case SDLK_DOWN:
                  c.move(0,-10,20);
                  break;
        }
        break; */
    }
    /*case SDL_MOUSEMOTION:
        int mouseX = event.motion.x;
        int mouseY = event.motion.y;

        std::stringstream ss;
        ss << "X: " << mouseX << " Y: " << mouseY;

        SDL_SetWindowTitle(window, ss.str().c_str());
        break;*/

   }

      else
        {
            c.fall(1);
        }

  }

}


//  t.scale(2,2);
/*
   line l1(300,300,400,400,WHITE);
    line l2(300,300,400,200,BLUE);
    line l3(300,300,200,400,GREEN);
    line l4(300,300,200,200,RED);
    line l5(300,300,300,400,WHITE);
    line l6(300,300,300,200,BLUE);
    line l7(300,300,200,300,GREEN);
    line l8(300,300,400,300,RED);
    //  line(300,300,400,400,BLUE);
  //  h(5);
    circle c(300,300,sqrt(100*100+100*100));
    ellipse e (300,300,50,100);
    ellipse(300,300,100,50);
    rectangle r (200,200,400,400);
  //  triangle t (200,200,400,200,300,400,YELLOW);
  //  c.translate(-100,-100,"nodraw").scale(2);
    r.translate(-100,-100,"nodraw").scale(1.2,1.2);
    //clear();
     l1.remove();
    //  l1.draw();
    c.remove();
    e.remove();
    t.remove();
    r.remove();
     */
  // glutSwapBuffers();
