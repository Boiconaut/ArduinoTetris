#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 128
#define BORDER_UP 0
#define BORDER_DOWN 128
#define BORDER_LEFT 64
#define BORDER_RIGHT 0

#define BUTTON_LEFT 1
#define BUTTON_RIGHT 2
#define BUTTON_ROTATE 3

#define BOX 0
#define L 1
#define Z 2
#define T 3
#define I 4

#define A 4
#define START_X -20
#define START_Y 32
#define BUTTON_MASK B00001100
#define OLED_RESET -1

#define X_COUNT 16
#define Y_COUNT 32

Adafruit_SH1106G display(128, 64, &Wire, OLED_RESET);

byte BUTTON_CODE;
byte FIGURE_CODE;
unsigned long timer = 0;
int speed;

byte fallen_acc[Y_COUNT][X_COUNT];

struct Position{
  int x;
  int y;
};

Position *figure;
Position center_offset;
int step;
