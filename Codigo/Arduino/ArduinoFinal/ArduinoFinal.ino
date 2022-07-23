//string para determinar que dedo se tiene que mover
String dedos;
String dedosAnteriores = "11111";

// Secuencia de pasos (par máximo)
int paso_adelante [4][4] =
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

int paso_atras [4][4] =
{
  {1, 1, 0, 0},
  {1, 0, 0, 1},
  {0, 0, 1, 1},
  {0, 1, 1, 0}
};

int cantidad[] = {100,100,100,100,100}; //vector con la cantidad de pasos por dedo

//funcion que hace mover el motor segun direccion, pasos y pines
void pasos(char dir, byte pin1, byte pin2, byte pin3, byte pin4, int steps){
  if(dir == '1'){
    for (int j = 0; j < steps; j++){
      for (int i = 0; i < 4; i++){
        digitalWrite(pin1, paso_adelante[i][0]);
        digitalWrite(pin2, paso_adelante[i][1]);
        digitalWrite(pin3, paso_adelante[i][2]);
        digitalWrite(pin4, paso_adelante[i][3]);
        delay(2);
      }
    }
  }
  if(dir == '0'){
    for (int j = 0; j < steps; j++){
      for (int i = 0; i < 4; i++){
        digitalWrite(pin1, paso_atras[i][0]);
        digitalWrite(pin2, paso_atras[i][1]);
        digitalWrite(pin3, paso_atras[i][2]);
        digitalWrite(pin4, paso_atras[i][3]);
        delay(2);
      }
    }
  }
}

void mover(int i, char a){
  if(i == 0){
    Serial.end();
    pasos(a,0,1,2,3,cantidad[0]);
    Serial.begin(9600);
  }
  if(i == 1){pasos(a,4,5,6,7,cantidad[1]);}
  if(i == 2){pasos(a,8,9,10,11,cantidad[2]);}
  if(i == 3){pasos(a,12,13,A0,A1,cantidad[3]);}
  if(i == 4){pasos(a,A2,A3,A4,A5,cantidad[4]);}
}

void verificar(){
  for(int i=0;i<5;i++){
    if(dedos[i] != dedosAnteriores[i]){
      mover(i,dedos[i]);
      dedosAnteriores[i] = dedos[i];
    }
  }
}

void setup() {
  Serial.begin(9600);
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

void loop() {
  if(Serial.available()>0){
    dedos = Serial.readString();
    verificar();
  }
}
