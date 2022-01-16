void checkButtons(){
  BUTTON_CODE = (PIND & BUTTON_MASK) >> 2;
  if(BUTTON_CODE) {
    if(BUTTON_CODE != BUTTON_ROTATE) Shift();
    else Rotate();
  }
}

void Shift(){
  int offset;
  
  switch(BUTTON_CODE){
    case BUTTON_LEFT:
      offset = A;
      break;
    case BUTTON_RIGHT:
      offset = -A;
      break;
    default:
      break;
  }

  for(Position *p = figure; p < sizeof(figure); p += step){
    p->y += offset;
  }
}

void Rotate(){
  for(Position *p = figure; p < sizeof(figure); p += step){
    double mod = sqrt(pow(p->x - figure->x - center_offset.x, 2) + pow(p->y - figure->y - center_offset.y, 2));
    double fi = atan2((p->y - figure->y - center_offset.y), (p->x - figure->x - center_offset.x));
    fi -= HALF_PI;
    p->x = figure->x + center_offset.x + mod * cos(fi);
    p->y = figure->y + center_offset.y + mod * cos(fi);
  }
  
}

void Fall(){
  for(Position *p = figure; p < sizeof(figure); p += step){
    if(p->x >= 0) fallen_acc[p->y][p->x] = 0;
    p->x += A;
    if(p->x >= 0) fallen_acc[p->y][p->x] = 1;
  }
  CheckImpactions();
}

void CheckImpactions(){
  for(Position *p = figure; p < sizeof(figure); p += step){
    if(fallen_acc[p->y][p->x + 4]){
      if(p->x + 4 <= 0) {
        GameOver();
        return;
      }
    }
  }

  for(Position *p = figure; p < sizeof(figure); p += step){
    if(p->x >= SCREEN_HEIGHT - 4) UpdateFigure();
  }
}

void UpdateFigure(){
  byte n = random(5);
  FIGURE_CODE = n;
  Position pos;
  pos.x = START_X;
  pos.y = START_Y;
  Position *p;

  switch(FIGURE_CODE){
    case BOX:
      figure = calloc(4, step);
      p = figure;
      p->x = pos.x;
      p->y = pos.y;
      p += step;
      p->x = pos.x;
      p->y = pos.y - A;
      p += step;
      p->x = pos.x + A;
      p->y = pos.y;
      p += step;
      p->x = pos.x + A;
      p->y = pos.y;
      p = NULL;
      center_offset.x = A;
      center_offset.y = -A;
      break;
    case I:
      figure = calloc(4, step);
      p = figure;
      p->x = pos.x;
      p->y = pos.y;
      p += step;
      p->x = pos.x + A;
      p->y = pos.y;
      p += step;
      p->x = pos.x + A * 2;
      p->y = pos.y;
      p += step;
      p->x = pos.x + A * 3;
      p->y = pos.y;
      p = NULL;
      center_offset.x = A * 2;
      center_offset.y = 0;
      break;
    case L:
      figure = calloc(4, step);
      p = figure;
      p->x = pos.x;
      p->y = pos.y;
      p += step;
      p->x = pos.x + A;
      p->y = pos.y;
      p += step;
      p->x = pos.x + A * 2;
      p->y = pos.y;
      p += step;
      p->x = pos.x + A * 2;
      p->y = pos.y + A;
      p = NULL;
      center_offset.x = A * 2;
      center_offset.y = 0;
      break;
    case T:
      figure = calloc(4, step);
      p = figure;
      p->x = pos.x;
      p->y = pos.y;
      p += step;
      p->x = pos.x;
      p->y = pos.y - A;
      p += step;
      p->x = pos.x;
      p->y = pos.y - A * 2;
      p += step;
      p->x = pos.x + A;
      p->y = pos.y - A;
      p = NULL;
      center_offset.x = 0;
      center_offset.y = -A;
      break;
    case Z:
      figure = calloc(4, step);
      p = figure;
      p->x = pos.x;
      p->y = pos.y;
      p += step;
      p->x = pos.x + A;
      p->y = pos.y;
      p += step;
      p->x = pos.x + A;
      p->y = pos.y - A;
      p += step;
      p->x = pos.x + A * 2;
      p->y = pos.y - A * 2;
      p = NULL;
      center_offset.x = A;
      center_offset.y = -A;
      break;
    default:
      break;
  }
}

void GameOver(){
  free(figure);

  for(int i = 0; i < Y_COUNT; i++){
    for(int j = 0; j < X_COUNT; j++){
      fallen_acc[i][j] = 0;
    }
  }
  UpdateFigure();
}
