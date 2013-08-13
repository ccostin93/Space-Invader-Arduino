void displayScore(int score) {
  int temp = score;
  int v[4] = {
    -1, -1, -1, -1  };
  v[3] = temp%10;
  temp /= 10;
  v[2] = temp%10;
  temp /= 10;
  if (temp!=0) {
    v[1] = temp%10;
    temp /= 10;
  }
  if (temp!=0) {
    v[0] = temp%10;
  }
  if (v[0] >= 0) {
    shiftOut(dataB, CP, MSBFIRST, 16);
    number(v[0]);
    delay(500);
  }
  if (v[1] >= 0) {
    shiftOut(dataB, CP, MSBFIRST, 32);
    number(v[1]);
  }
  delay(500);
  shiftOut(dataB, CP, MSBFIRST, 64);
  number(v[2]);
  delay(500);
  shiftOut(dataB, CP, MSBFIRST, 128);
  number(v[3]);
  delay(500);
}

void number(short num) {
  switch(num) {
  case 9: 
    digitalWrite(stcp, LOW);
    shiftOut(data, shcp, MSBFIRST, 65);
    digitalWrite(stcp, HIGH);
    break;
  case 8: 
    {
      digitalWrite(stcp, LOW);
      shiftOut(data,shcp, MSBFIRST, 64);
      digitalWrite(stcp, HIGH);
      break;
    }
  case 7:
    {
      digitalWrite(stcp, LOW);
      shiftOut(data,shcp, MSBFIRST, 213);
      digitalWrite(stcp, HIGH);
      break;
    }
  case 6:
    {
      digitalWrite(stcp, LOW);
      shiftOut(data,shcp, MSBFIRST, 72);
      digitalWrite(stcp, HIGH);
      break;
    }
  case 5:
    {
      digitalWrite(stcp, LOW);
      shiftOut(data,shcp, MSBFIRST, 73);
      digitalWrite(stcp, HIGH);
      break;
    }
  case 4:
    {
      digitalWrite(stcp, LOW);
      shiftOut(data,shcp, MSBFIRST, 195);
      digitalWrite(stcp, HIGH);
      break;
    }
  case 3:
    {
      digitalWrite(stcp, LOW);
      shiftOut(data,shcp, MSBFIRST, 69);
      digitalWrite(stcp, HIGH);
      break;
    }
  case 2: 
    {  
      digitalWrite(stcp, LOW);
      shiftOut(data,shcp, MSBFIRST, 100);
      digitalWrite(stcp, HIGH);
      break;
    }
  case 1: 
    {
      digitalWrite(stcp, LOW);
      shiftOut(data,shcp, MSBFIRST, 215);
      digitalWrite(stcp, HIGH);
      break;
    }
  case 0: 
    {
      digitalWrite(stcp, LOW);
      shiftOut(data,shcp, MSBFIRST, 80);
      digitalWrite(stcp, HIGH);
      break;
    }
  }
}




















