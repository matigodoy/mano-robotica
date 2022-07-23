// Definimos los pines donde tenemos conectadas las bobinas
#define IN1  A2
#define IN2  A3
#define IN3  A4
#define IN4  A5
 
// Secuencia de pasos (par máximo)
int paso [4][4] =
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

int pasoalverre [4][4] =
{
  {1, 1, 0, 0},
  {1, 0, 0, 1},
  {0, 0, 1, 1},
  {0, 1, 1, 0}
};
 
void setup() {
  for(int i=0;i<14;i++){
    pinMode(i, OUTPUT);
  }
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
}

void pasos(boolean dir, byte pin1, byte pin2, byte pin3, byte pin4, int steps){
  if(dir == true){
    for (int j = 0; j < steps; j++){
      for (int i = 0; i < 4; i++){
        digitalWrite(pin1, paso[i][0]);
        digitalWrite(pin2, paso[i][1]);
        digitalWrite(pin3, paso[i][2]);
        digitalWrite(pin4, paso[i][3]);
        delay(5);
      }
    }
  }
  if(dir == false){
    for (int j = 0; j < steps; j++){
      for (int i = 0; i < 4; i++){
        digitalWrite(pin1, pasoalverre[i][0]);
        digitalWrite(pin2, pasoalverre[i][1]);
        digitalWrite(pin3, pasoalverre[i][2]);
        digitalWrite(pin4, pasoalverre[i][3]);
        delay(5);
      }
    }
  }
}

void loop()
{ 
  pasos(true,IN1,IN2,IN3,IN4,200);
  pasos(false,IN1,IN2,IN3,IN4,200);
}
