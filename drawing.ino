void drawShip(byte ShipX, byte ShipY) {
  display.fillRect(ShipX-2, ShipY-3, 3, 2, BLACK);
  display.fillRect(ShipX-2, ShipY+2, 3, 2, BLACK);
  display.fillRect(ShipX-1, ShipY-1, 2, 3, BLACK);
  display.drawFastHLine(ShipX-4, ShipY, 3, BLACK);
  display.display();
}

void drawEnemy(byte x, byte y) {
  display.fillRect(x-2, y-3, 3, 7, BLACK);
  display.drawPixel(x-3, y-3, BLACK);
  display.drawPixel(x-3, y+3, BLACK);
  display.drawPixel(x-4, y, BLACK);
  display.drawFastVLine(x-3, y-1, 3, BLACK);
  display.drawPixel(x-1, y-1, WHITE);
  display.drawPixel(x-1, y+1, WHITE);
  display.display();
}

void initGame(byte lvl) {
  if (lvl == 1) {
    ship =  new Ship(83, 24);
    score = 0;
    shiftOut(dataB, CP, MSBFIRST, 0);
  }
  else {  
    ship->setX(83); 
    ship->setY(24); //reset ship position
  }
  //Enemy initialization
  for (byte i = 1; i <= 4; i++) {
    for (byte j = 1; j <= 3; j++) {
      enemy[(i-1)*3+j-1] = new Enemy(10*i+6, 42 - 9*(j-1), lvl);
    }
  }
  //draw the level
  display.clearDisplay();
  drawShip(ship->getX(), ship->getY());
  drawLives(ship->getLives());
  for (byte i=0; i<nr_enemy; i++) {
    drawEnemy(enemy[i]->getX(), enemy[i]->getY());
  }
}

void moveShip() {
  joyX = analogRead(0);
  short int dir = map(joyX, 0, 1023, -5, 5); 
  if (dir != 0) { 
    dir = dir < 0 ? -1 : 1;
    display.fillRect(ship->getX()-6, ship->getY()-7, 7, 15, WHITE);
    display.display();
    ship->move(dir);
    drawShip(ship->getX(), ship->getY());
  }
}

void moveBullet() {
  if (ShipBullet->getExist() == 1) {//the bullet exists
    display.drawFastHLine(ShipBullet->getX(), ShipBullet->getY(), 3, WHITE);
    display.display();
    ShipBullet->move();
    display.drawFastHLine(ShipBullet->getX(), ShipBullet->getY(), 3, BLACK);
    display.display();
    for (byte i=0; i<nr_enemy; i++) {
      if (ShipBullet->collisionEnemy(enemy[i]) == 1) {
        enemy[i]->setDead();
        score += 100;
      }
    }
  }
  if (EnemyBullet->getExist() == 1) {//the bullet exists
    display.drawFastHLine(EnemyBullet->getX(), EnemyBullet->getY(), 3, WHITE);
    display.display();
    EnemyBullet->move();
    display.drawFastHLine(EnemyBullet->getX(), EnemyBullet->getY(), 3, BLACK);
    display.display();
    if (EnemyBullet->collisionShip(ship) == 1) {
      ship->setLives(ship->getLives()-1);
      ship->setX(83);
      ship->setY(24);
    }
  }
}

byte remaining_enemys() {
  byte k=0;
  for (byte i=0; i<nr_enemy; i++) {
    if(enemy[i]->Alive()) {
      k++;
    }
  }
  return k;
}


void moveEnemy() {
  bounce = 0;
  for (byte i=0; i<nr_enemy; i++) { //le misc
    if (bounce == 0 && enemy[i]->Alive() == true && enemy[i]->move() == 1) {
      for (byte j=0; j<nr_enemy; j++) { //schimb directia la toti ceilalti
        if(j < i) {
          enemy[j]->update(1);
        }
        else if (j > i) {
          enemy[j]->update(0);
        }
      }
      bounce = 1;
    }          
  }
  display.clearDisplay();
  drawShip(ship->getX(), ship->getY());
  drawLives(ship->getLives());
  for (byte i=0; i<nr_enemy; i++) { //desenez toate navele inamice
    if (enemy[i]->Alive()) { //daca inamicul na fost doborat inca
      drawEnemy(enemy[i]->getX(), enemy[i]->getY()); //il desenez
      if (enemy[i]->Defeat()) {
        play = 2;
      }
      if((int)random(chance_shoot) == 0) {//enemy shoots bullet
        addBullet(enemy[i]->getX(), enemy[i]->getY(), 3, 0);
      }
    }
  }
}

void drawLives(unsigned short int lives) {
  for (byte i=0; i<lives; i++) { 
    drawL(1, 42 - i*7);
  }
} 

void drawL(int x, int y) {
  display.fillRect(x+1, y, 3, 5, BLACK);
  display.drawPixel(x, y+1, BLACK);
  display.drawPixel(x, y+3, BLACK);
  display.drawFastVLine(x+4, y+1, 3, BLACK);
  display.drawPixel(x+5, y+2, BLACK);
  display.display();
}

void buttonsPressed() {
  char b = getButton(BPIN, oldB);
  if (b == 0 && oldB == 1) {
    oldB = 0;
    if (play == 0) {
      addBullet(ship->getX()-8, ship->getY(), -3, 1);
    }
    else if (play == 2) {
      play = 0;
      level = 1;
      initGame(level);
    }
  }
  else if(b == 1 && oldB == 0) {
    oldB = 1;
  }
  char b1 = getButton(JPIN, oldJB);
  if (b1 == 0 && oldJB == 1) {
    oldJB = 0;
    if (play == 0) {
      play = 1;
    }
    else if (play == 1) {
      play = 0;
    }
    else if (play == 2) {
      play = 0;
      level = 1;
      initGame(level);
    }
  }
  else if(b1 == 1 && oldJB == 0) {
    oldJB = 1;
  }
}

void showMenu() {
  display.clearDisplay();
  display.drawBitmap(30, 16, game, 8, 23, BLACK);
  display.drawBitmap(39, 10, over, 8, 23, BLACK);
  display.display();
}

void showPause() {
  display.clearDisplay();
  display.drawBitmap(30, 8, pause, 8, 32, BLACK);
  display.display();
}





























