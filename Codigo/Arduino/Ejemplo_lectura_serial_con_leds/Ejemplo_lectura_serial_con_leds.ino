String dedos;
String dedosAnterior = "11111";
const int ledPIN1 = 2;
const int ledPIN2 = 3;
const int ledPIN3 = 4;
const int ledPIN4 = 5;
const int ledPIN5 = 6;

void mover(int i, char a){
  if(a == '1'){
    digitalWrite(i+2 , HIGH);
  }
  if(a == '0'){
    digitalWrite(i+2 , LOW);
  }
}

void verificar(){
  for(int i=0;i<16;i++){
    if(dedos[i] != dedosAnterior[i]){
      mover(i,dedos[i]);
      dedosAnterior[i] = dedos[i];
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(ledPIN1 , OUTPUT);
  digitalWrite(ledPIN1 , HIGH);
  pinMode(ledPIN2 , OUTPUT);
  digitalWrite(ledPIN2 , HIGH);
  pinMode(ledPIN3 , OUTPUT);
  digitalWrite(ledPIN3 , HIGH);
  pinMode(ledPIN4 , OUTPUT);
  digitalWrite(ledPIN4 , HIGH);
  pinMode(ledPIN5 , OUTPUT);
  digitalWrite(ledPIN5 , HIGH);
}

void loop() {
  if (Serial.available()>0){
    dedos = Serial.readString();
    verificar();
  }
}
