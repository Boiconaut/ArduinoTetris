void Redraw(){
  for(Position *p = figure; p < sizeof(figure); p += step){
    display.fillRect(p->x, p->y, A, A, 1);
  }

  for(int i = 0; i < Y_COUNT; i++){
    for(int j = 0; j < X_COUNT; j++){
      if(fallen_acc[i][j]) display.fillRect(i, j, A, A, 1);
    }
  }
}
