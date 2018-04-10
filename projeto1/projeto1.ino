//Include LCD library
#include <LiquidCrystal.h>

#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880
//int vetMusic[100] = {a, a, a, f, cH, a, f, cH, a, eH, eH, eH, fH, cH, gS, f, cH, a, aH, a, a, aH, gSH, gH, fSH, fH, fSH, aS, dSH, dH, cSH, cH, b, cH, f, gS, f, a, cH, a, cH, eH, aH, a, a, aH, gSH, gH,
//fSH, fH,fSH, aS, dSH, dH, cSH, cH, b, cH, f, gS, f, cH, a, f, c, a};

//int vetDelay[100] = {500, 500, 5000, 350, 150, 500, 350, 150, 1000, 500, 500, 500, 350, 150, 500, 350, 150, 1000, 500, 350, 150, 500, 250, 250, 125, 125, 250, 250, 500, 250, 250, 125, 125, 250, 125, 500,
//375, 125, 500, 375, 125, 1000, 500, 350, 150, 500, 250, 250, 125, 125, 250, 250, 500, 250, 250, 125, 125, 250, 250, 500, 375, 125, 500, 275, 125, 1000};

//int pos = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int ldrPin = 0; //LDR no pino analígico 8
int ldrValor = 0; //Valor lido do LDR
int ldrPin2 = 1;
int ldrValor2 = 0;
int buzzer = 8;
char nota = '-';
char branco = ' ';
char vetor[12] = {branco, branco, branco, branco, branco, branco, branco, branco, branco, branco, branco, branco};
char vetor2[12] = {branco, branco, branco, branco, branco, branco, branco, branco, branco, branco, branco, branco};
int i;
int aux;
int aux2;
int erro = 0;
int score = 0;
int reset = 0;
char scoreVet[3];
char erroVet[3];

void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); //Inicia a comunicação serial
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.clear();
  //lcd.setCursor(0, 0);
  // Print a message to the LCD.
  //for(i = 0; i < 16; i++){
  //  lcd.print(vetor[i]);
      
  //}
}

void loop() {
  
  ///ler o valor do LDR
  ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
  Serial.println("LDR1");
  Serial.println(ldrValor);
  delay(100);

  ///ler o valor do LDR2
  ldrValor2 = analogRead(ldrPin2); //O valor lido será entre 0 e 1023
  Serial.println("LDR2");
  Serial.println(ldrValor2);
  delay(100);

  if(erro < 10){
  
    for(i = 0; i < 11; i++){
      vetor[i] = vetor[i+1];
    }
  
    for(i = 0; i < 11; i++){
      vetor2[i] = vetor2[i+1];
    }
    
    aux = random(2);
    if(aux == 0){
      vetor[11] = nota;  
    }
    else{
      vetor[11] = branco;  
    }
  
    aux2 = random(2);
    if(aux2 == 0){
      vetor2[11] = nota;  
    }
    else{
      vetor2[11] = branco;  
    }
    
    lcd.setCursor(0, 0);
    
    for(i = 0; i < 12; i++){
      lcd.print(vetor[i]);
        
    }
    itoa(score, scoreVet, 10);
    lcd.print(" S");
    if(score >= 10){
      for(i = 0; i < 2; i++){
        lcd.print(scoreVet[i]);  
      }
    }
    else{
      lcd.print(" ");
      lcd.print(scoreVet[0]);
    }
  
    lcd.setCursor(0, 1);
    
    for(i = 0; i < 12; i++){
      lcd.print(vetor2[i]);
        
    }
    itoa(erro, erroVet, 10);
    lcd.print(" E");
    if(erro >= 10){
      for(i = 0; i < 2; i++){
        lcd.print(erroVet[i]);  
      }  
    }
    else{
      lcd.print(" ");
      lcd.print(erroVet[0]);  
    }
    
    
    if(vetor[0] == nota && vetor2[0] == nota && ldrValor < 500 && ldrValor2 < 500){
      tone(buzzer, 10000); // Send 1KHz sound signal...
      delay(1000);
      noTone(buzzer);     // Stop sound..
      score++;
    }
    else if(vetor[0] == branco && vetor2[0] == branco && ldrValor > 500 && ldrValor2 > 500){
      noTone(buzzer);  
    }
    else if((vetor[0] == nota && vetor2[0] == branco) && (ldrValor < 500 && ldrValor2 > 500)){
      tone(buzzer, 10000); // Send 1KHz sound signal...
      delay(1000);
      noTone(buzzer);     // Stop sound..
      score++;
    }
    else if(vetor[0] == branco && vetor2[0] == nota && ldrValor > 500 && ldrValor2 < 500){
      tone(buzzer, 10000); // Send 1KHz sound signal...
      delay(1000);
      noTone(buzzer);     // Stop sound..
      score++;
    }
    else{
      tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(100 );
      noTone(buzzer);     // Stop sound..
      erro++;
    }
    delay(1000);
  }
  else{
    lcd.clear();
    lcd.setCursor(0, 3);
    lcd.print("GAME OVER");
    if(ldrValor < 500 && ldrValor2 < 500){
      reset++;
      delay(500);
      if(reset > 4){
        erro = 0;
        score = 0;
        reset = 0;
      }
    }
  }
  
}
