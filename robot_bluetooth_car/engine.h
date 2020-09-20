//Engine representation.
struct engine{
  char direction;
  int pin_1;
  int pin_2;
  bool active;
};

typedef struct engine robo_engine;
robo_engine defineEngine(char dir,int p1, int p2);
bool runEngine(robo_engine engine);
void stopEngine(robo_engine engine);
void goForward(robo_engine engine);
void goReverse(robo_engine engine);
