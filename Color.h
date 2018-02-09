class Color{
public:
  float r, g, b;
  Color(float R, float G, float B):r(R/255), g(G/255), b(B/255){}
};

const Color WHITE(255, 255, 255);
const Color GREEN(0, 255, 0);
const Color RED(255, 0, 0);
const Color BLUE(0, 0, 255);
const Color YELLOW(0, 255, 255);
const Color BLACK(0,0,0);

const Color NONE= WHITE;
