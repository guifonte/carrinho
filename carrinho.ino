/* Carrinho autônomo

    Projeto 3 de EA076 ministrado na Universidade Estadual de Campinas

    Resumo:
    Implementação de um carrinho autônomo no Arduino Uno, que desvia de 
    obstáculos.
    
    Comandos implementados:
    1 - Anda reto
      Sincroniza os motores de forma que o carrinho ande reto
      
    2 - Gira a esquerda
      Sincroniza os motores de forma que o carrinho curve à esquerda
      
    3- Pare
      Desliga os motores
      
     
    Guilherme Nishino Fontebasso - RA 135973
    João Paulo de Tassis Machado - RA 136261
    02.06.2017
*/
// --------------------------------------------------------------------------- Inicializa sensor
#include <Ultrasonic.h>
#define pino_trigger 10 //Pino que envia sinal do sensor ultrassonico
#define pino_echo 11 //Pino que recebe o sinal refletido do sensor ultrassonico
Ultrasonic ultrasonic(pino_trigger, pino_echo); //Funcao da biblioteca Ultrasonic.h, inicializa o sensor

// --------------------------------------------------------------------------- Motores
int motor_esquerdo[] = {4,5}; //Pinos do motor esquerdo
int motor_direito[] = {7, 8}; //Pinos do motor direito
int enable_esquerdo = 3; //PWM de controle de tracao do motor esquerdo
int enable_direito = 6; //PWM de controle de tracao do motor direito
int distancia_limite = 20; //Distancia limite de um obstaculo para o carrinho desviar
// --------------------------------------------------------------------------- Drive

void anda_reto(){ //Faz o carro andar reto
  analogWrite(enable_esquerdo, 200); //Os valores para os sinais PWM foram
  analogWrite(enable_direito, 100);  //definidos para melhor funcionamento prático do carrinho
  digitalWrite(motor_esquerdo[0], LOW); //Define o sentido de rotação dos motores
  digitalWrite(motor_esquerdo[1], HIGH);
  digitalWrite(motor_direito[0], HIGH);
  digitalWrite(motor_direito[1], LOW); 
}

void gira_esquerda(){ //Faz o carro curvar a esquerda
  analogWrite(enable_esquerdo, 10); //Os valores para os sinais PWM foram
  analogWrite(enable_direito, 190); //definidos para melhor funcionamento prático do carrinho
  digitalWrite(motor_direito[0],HIGH); //Define o sentido de rotação dos motores
  digitalWrite(motor_direito[1],LOW);
  digitalWrite(motor_esquerdo[0], LOW);
  digitalWrite(motor_esquerdo[1], HIGH);
}

void para_motor(){ //Desliga os motores
  analogWrite(enable_esquerdo, 0); 
  analogWrite(enable_direito, 0);
  
}
// --------------------------------------------------------------------------- Setup
void setup() {
  Serial.begin(9600);
  //Setup das portas do motor
  pinMode(enable_esquerdo, OUTPUT);
  pinMode(enable_direito, OUTPUT);
  int i;
  for(i = 0; i < 2; i++){
  pinMode(motor_esquerdo[i], OUTPUT);
  pinMode(motor_direito[i], OUTPUT);
  }
}

// --------------------------------------------------------------------------- Loop
void loop() { 

  float medida_sensor;
  long microsegundo = ultrasonic.timing();
  medida_sensor = ultrasonic.convert(microsegundo, Ultrasonic::CM); //Distancia lida pelo sensor
  if (medida_sensor > distancia_limite){  
    anda_reto();
  }
  else{ //Caso haja um obstaculo a uma distancia menor do que a determinada, o carrinho curva a esquerda
    para_motor();
    delay(1000);
    gira_esquerda();
    delay(3000);
  }
}


