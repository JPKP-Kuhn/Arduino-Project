// C++ code
//coding: utc-8
//Nome das cores das variáveis em inglês

//Semáforo A
#define A_LEDR 12
#define A_LEDY 11
#define A_LEDG 10
#define A_Botao 6
int A_TempoG =  3000;
int A_TempoY = 1000;
int A_TempoR =  3000;
int A_TempoGEmergencia = 1500;
int A_UltimoLedAceso = 2; //0 pro vermelho, 1 amarelo, 2 verde
unsigned long A_UltimaExecucao = 0; 

int pinosA[] = {12, 11, 10};

//Semáforo B
#define B_LEDR 4
#define B_LEDY 3
#define B_LEDG 2
#define B_Botao 5
int B_TempoG = 2000;
int B_TempoY = 1000;
int B_TempoR = 4000;
int B_TempoGEmergencia = 1500;
int B_UltimoLedAceso = 0; //0 pro vermelho, 1 amarelo, 2 verde
unsigned long B_UltimaExecucao = 0;

int pinosB[] = {4, 3, 2};

//controlador pro flash dos LEDs
int controlador = 0;

void setup(){
  Serial.begin(9600);
  //Semáforo A como saída
  for (int i =10; i<13; i++){
    pinMode(i, OUTPUT);
  }
  //Semáforo B como saída
  for (int i =2; i<5; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(A_Botao, INPUT);
  pinMode(B_Botao, INPUT);
  
  iniciar();
  
  A_Semaforo();
  B_Semaforo();
}

void iniciar(){
  //Inicia com flash
    digitalWrite(A_LEDR, HIGH);
    digitalWrite(A_LEDY, HIGH);
    digitalWrite(A_LEDG, HIGH);
    digitalWrite(B_LEDR, HIGH);
    digitalWrite(B_LEDY, HIGH);
    digitalWrite(B_LEDG, HIGH);
    delay(1000);
    digitalWrite(A_LEDR, LOW);
    digitalWrite(A_LEDY, LOW);
    digitalWrite(A_LEDG, LOW);
    digitalWrite(B_LEDR, LOW);
    digitalWrite(B_LEDY, LOW);
    digitalWrite(B_LEDG, LOW);
 
    A_UltimaExecucao = millis();
    B_UltimaExecucao = millis();
}

void loop(){
  //Inicío dos semáforos
  if(A_checar()) {
    A_Semaforo();
  }
  
  if(B_checar()){
    B_Semaforo();
  }
  
  //Botões
  if(digitalRead(A_Botao)){
    A_Button(); 
  }
  if(digitalRead(B_Botao)){
    B_Button();
  }
  
  //Horário de rush
  if(analogRead(A0) < 500){
  A_TempoG = 4000;
  B_TempoR = 5000;
  }
  
}

bool A_checar(){ //Verificar qual foi o LED anterior
  if(A_UltimoLedAceso == 0) { 
    return millis() - A_UltimaExecucao >= A_TempoY;
  } else if(A_UltimoLedAceso == 1) {
    return millis() - A_UltimaExecucao >= A_TempoG;
  } else {
    return millis() - A_UltimaExecucao >= A_TempoR;
  }
}

bool B_checar(){ //Verificar qual foi o LED anterior
  if(B_UltimoLedAceso == 0) { 
    return millis() - B_UltimaExecucao >= B_TempoY;
  } else if(B_UltimoLedAceso == 1) {
    return millis() - B_UltimaExecucao >= B_TempoG;
  } else {
    return millis() - B_UltimaExecucao >= B_TempoR;
  }
}

void A_Semaforo(){
  digitalWrite(A_LEDG, LOW);
  digitalWrite(A_LEDY, LOW);
  digitalWrite(A_LEDR, LOW);
 
  (A_UltimoLedAceso == 0) ? digitalWrite(pinosA[2], LOW) : digitalWrite(pinosA[A_UltimoLedAceso - 1], LOW);
  digitalWrite(pinosA[A_UltimoLedAceso], HIGH);
  A_UltimoLedAceso = (A_UltimoLedAceso == 0) ? 2 : --A_UltimoLedAceso;
  A_UltimaExecucao = millis();
  
}

void B_Semaforo(){
  digitalWrite(B_LEDG, LOW);
  digitalWrite(B_LEDY, LOW);
  digitalWrite(B_LEDR, LOW);
 
  (B_UltimoLedAceso == 0) ? digitalWrite(pinosB[2], LOW) : digitalWrite(pinosB[B_UltimoLedAceso - 1], LOW);
  digitalWrite(pinosB[B_UltimoLedAceso], HIGH);
  B_UltimoLedAceso = (B_UltimoLedAceso == 0) ? 2 : --B_UltimoLedAceso;
  B_UltimaExecucao = millis();
  
}


void A_Button(){
  
    digitalWrite(A_LEDR, LOW);
    digitalWrite(A_LEDY, LOW);
    digitalWrite(B_LEDY, LOW);
    digitalWrite(B_LEDG, LOW);

  digitalWrite(A_LEDG, HIGH);
  digitalWrite(B_LEDR, HIGH);
    delay(4500); //3s + 1,5s
    digitalWrite(A_LEDG, LOW);
  digitalWrite(B_LEDR, LOW);
  
  
    A_UltimoLedAceso = 2; 
    B_UltimoLedAceso = 0;
  
    //A_UltimaExecucao = millis();
    //B_UltimaExecucao = millis();
  
    if(A_checar()) {
    A_Semaforo();
  }
 
}

void B_Button(){
  digitalWrite(B_LEDR, LOW);
  digitalWrite(B_LEDY, LOW);
  digitalWrite(A_LEDY, LOW);
  digitalWrite(A_LEDG, LOW);
  
  digitalWrite(B_LEDG, HIGH);
  digitalWrite(A_LEDR, HIGH);
  delay(3500); //2s + 1,5s
  digitalWrite(B_LEDG, LOW);
  digitalWrite(A_LEDR, LOW);
  
  A_UltimoLedAceso = 0;
  B_UltimoLedAceso = 2;
  
  if(B_checar()){
    B_Semaforo();
  }
}