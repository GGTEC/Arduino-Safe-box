//Bibliotecas 
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal.h>        
#include <Keypad.h>
#include "EEPROMAnything.h"
#include <EEPROM.h>

//Inicialização do Display LiquidCrystal 
//lcd(<RS>,<E>,<D4>,<D5>,<D6>,< D7>)
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
Servo motor;
int REAIS = REAIS;
int moeda = 0; 
int moeda2 = 0;
int key = 0;
int count = 0; //Contador de uso geral
char pass [6] = {'2', '1', '0', '1', '1', '6'};    //Senha
const int redPin = 11;     //Definição do pino do LED Vermelho
const int greenPin = 10;   //Definição do pino do LED Verde
const int audioPin = 9;    //Definição do pino do Buzzer
const int duration = 200;  //Duração das sons tocados
const byte ROWS = 4;               //Quatro linhas
const byte COLS = 3;               //Três colunas

//Mapeamento de teclas
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'+','0','#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2};       //Definição de pinos das linhas
byte colPins[COLS] = {6, 7, 8};          //Definição de pinos das colunas

//Cria o teclado
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//Programa inici
struct config_t{
  int writed;
  int moeda;
} 
configuration;

String stringOne = "";
String soma = "";
void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);                             
  motor.attach(12); 
  pinMode(audioPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  key_init();                                         //Inicializa o sistema
  getValues();
}



 //Loop Principal do Programa 
void loop(){
 char key = keypad.getKey();
  if (key != NO_KEY){
     if (key == '+') {                                //Se a tecla é '#'
     adicionar();
     }
     if (key == '9'){                    //se a tecla for 9 inicia a função limpa()
     limpa();
     }
     if (key == '0'){                     //se o numero digitado for 0 antes de inserir a senha mostra o valor total por aprox 3 segundos
     exibir();
     }
     if (key == '#') {                                //Se a tecla é '#'
     senha();
     }
}
}
//Inicializar o Sistema 
void key_init (){
  lcd.clear();                                       //Limpa o LCD
  lcd.setCursor(2,0);                                //Aplica a posição inicial das letras
  lcd.print("Aguardando...");                        //Emite mensagem
  lcd.setCursor(3,1);                                //Muda de linha
  lcd.print("Tecle #");                              //Emite mensagem
  motor.write(1);                                    //Aplica a posição inicial do motor
  count = 0;                                         //Variável count é zero na inicialização
  stringOne = "";                                    //Limpa a string responsavel por contar as teclas digitadas    
  digitalWrite(redPin, HIGH);                        //Emite som e acende LED Vermelho, indicando Sistema Iniciado
  digitalWrite(greenPin, LOW);
  tone(audioPin, 470, 100);
  delay(duration);
  noTone(audioPin);
}

//Subrotina de Entrada da Senha 
void code_entry_init(){
   char Key = keypad.getKey();
  lcd.clear();                                        //Limpa LCD
  lcd.print("Entre a Senha:");                        //Emite mensagem
  count = 0;                                          //Variável count é zero na entrada de senha
  tone(audioPin, 300, 100);                           //Emite som e acende LEDs
  delay(duration);
  noTone(audioPin);
  digitalWrite(redPin, HIGH);                         //Acende LED Vermelho
  digitalWrite(greenPin, LOW);                        //Apaga LED Verde
}

void entrada_da_soma(){
    char Key = keypad.getKey();
  lcd.clear();                                        //Limpa LCD
  lcd.print("VALOR PARA SOMAR");                        //Emite mensagem
  count = 0;                                          //Variável count é zero na entrada de senha
  tone(audioPin, 300, 100);                           //Emite som e acende LEDs
  delay(duration);
  noTone(audioPin);
  digitalWrite(redPin, HIGH);                         //Acende LED Vermelho
  digitalWrite(greenPin, LOW);                        //Apaga LED Verde
}
//Subrotina para Acesso Liberado 
void unlocked(){
  lcd.clear();                                         //Limpa LCD
  lcd.print("Acesso Liberado!");                       //Emite mensagem
  digitalWrite(redPin, LOW);                           //Apaga LED Vermelho
  digitalWrite(greenPin, HIGH);                        //Acende LED verde
  motor.write(90);                                     //Aplica a posição do motor para abrir a fechadura
  tone(audioPin, 100, 100);                            //Toca som
  delay(duration);
  noTone(audioPin);
  delay(10);
  for (int x = 0; x < 90000; x++){                     //laço for para detectar se a tecla 0 foi precionada com tempo de 90000 milisegundos para trancar automaticamente 
  char key = keypad.getKey();                          //obtem a tecla precionada
  if (key == '0')                                      //se foi precionada a tecla 0
 {                          
  locked();                                            //inicia função de trancar o sistema
  break;                                               //para a contagem do laço for
  }
  delay(100);
 } 
}
//Subrotina para trancar
void locked(){
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Trancado");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ISSO FICA FELIZ");
  lcd.setCursor(2,1);
  lcd.print("EM SER UTIL!");
  digitalWrite(redPin, HIGH);                           //Acende LED Vermelho
  digitalWrite(greenPin, LOW); 
  motor.write(0);                                       //Aplica a posição do servo para trancar o sistema  
  for (int x = 0; x < 3; x++){                          //Toca 3 vezes o som avizando que o sistema foi trancado
  tone(audioPin, 300, 100);
  delay(duration);
  noTone(audioPin);
  }
  delay(500);
  key_init();                                           //retorna para o ponto incial do sistema
  
}
//Subrotina para zerar o valor em reais em dinheiro do sistema
void limpa(){
  char key = keypad.getKey();
  tone(audioPin, 280);
  delay(1000);                         
  noTone(audioPin);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("TOTAL=");
  lcd.print("R$");
  lcd.print(moeda);
  lcd.print(",00");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TEM CERTEZA QUE");
  lcd.setCursor(1,1);
  lcd.print("DESEJA ZERAR ?");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("(1) SIM (2) NAO");
   for (int x = 0; x < 90000; x++){          //laco for para obter a opção escolhida 1 ou 2 
  char key = keypad.getKey();
  if (key == '1'){
    tone(audioPin, 780, 100); 
          delay(duration);                        
          noTone(audioPin);
    zerado();                                //se a opçao for 1 (sim) vai para subrotina de apagar o valor da variavel moeda
    break;
  }
  if (key == '2'){
    tone(audioPin, 380, 100);                
          delay(duration);                  
          noTone(audioPin);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("O VALOR TOTAL");
      lcd.setCursor(1,1);
      lcd.print("CONTINUA=");
      lcd.setCursor(12,1);
      lcd.print(moeda);
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ISSO FICA FELIZ");
      lcd.setCursor(2,1);
      lcd.print("EM SER UTIL!");
      delay(2000);        
    key_init();                            //se a opção for 2(não) volta para subrotina para inserir a senha
    break;
  }
   }
  }
//Subrotina para zerar a variavel moeda
void zerado(){
      EEPROM.write(0, 0);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("O VALOR TOTAL");
      lcd.setCursor(3,1);
      lcd.print("FOI ZERADO");
      delay(800);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ISSO FICA FELIZ");
      lcd.setCursor(2,1);
      lcd.print("EM SER UTIL!");
      lcd.clear();
      moeda = 0;
      delay(2000);
      key_init();       
}
void exibir(){
  lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("TOTAL=");
      lcd.print("R$");
      lcd.print(moeda);
      lcd.print(",00");
      delay(3000);
      key_init();
}
void senha(){
  code_entry_init();                             //Então espera que seja inserida uma senha
      int entrada = 0;                               //define a variavel entrada como padrão 0
      while (count < 6 ){                            //Conta 6 entradas/teclas
        char key = keypad.getKey();                  //Obtém tecla pressionada
        
        if (key != NO_KEY){
         
          stringOne += key;
          lcd.setCursor(5, 1);
          lcd.print(stringOne);                      //Se foi pressionada uma tecla:
          entrada += 1;                              //Faz entrada = entrada + 1
          tone(audioPin, 580, 100);                  //Para cada dígito emite um som de indicação
          delay(duration);                           //Duração do som
          noTone(audioPin);                          //Para de emitir som
          if (key == pass[count])count += 1;         //Se a tecla pressionada corresponde ao dígito 
                                                     //da senha correspondente, soma 1 no contador
          if ( count == 6 ) unlocked();              //Se contador chegou a 4 e com dígitos corretos,  
                                                     //desbloqueia siatema
          if ((key == '#') || (entrada == 6)){        //Se foi pressionada a tecla "#' ou foram feitas
                                                      //6 entradas,
             key_init();                              //Inicializa o sistema
            break;                                    //Para o sistema e espera por uma tecla
          }
        }
      }
    }
void adicionar(){
      entrada_da_soma();                       
      int entradas = 0;
          while (count < 15 ){         
      char key = keypad.getKey();                  //Obtém tecla pressionada
          if (key != NO_KEY){  
      soma += key;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("VALOR PARA SOMAR");
      lcd.setCursor(5,1);
      lcd.print("R$");
      lcd.print(soma);
      lcd.print(",00");                         
      entradas += 1;                             //Faz entrada = entrada + 1
      tone(audioPin, 580, 100);                  //Para cada dígito emite um som de indicação
      delay(duration);                           //Duração do som
      noTone(audioPin);  
      if (key == '#' ){
        soma = "";                        
      }
          if (key == '+' ) {
            somar();
            break;    
        }
      
    }
  }
}
void somar(){
  moeda = atoi( soma.c_str() ) + moeda;
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("TOTAL=");
  lcd.print("R$");
  lcd.print(moeda);
  soma = "";
  saveValues();
  lcd.print(",00");
  delay(2000);
  key_init ();
}
