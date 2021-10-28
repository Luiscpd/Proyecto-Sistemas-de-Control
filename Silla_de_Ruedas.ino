/* 
Sensor Ultrasonico

 HC-SR04 conexiones:
  VCC al Arduino 5V 
  GND al Arduino GND
  Echo al Arduino pin 6 
  Trig al Arduino pin 7
 */
 
#define ECHO 6
#define TRIG 7
volatile int DER=0;          // Interrupciones para encoder derecho
volatile int IZQ=0;          // Interrupciones para encoder izquierdo
long duracion, distancia;    // Variables para sensor ultrasonico
int MotorA=3;                // Define la variable entera en pin 3
int MotorB=5;                // Define la variable entera en pin 5
int valor=0;                 // Guarda los estados de los pines de aviso
int x=0;                     // Control PWM en motores


void setup() {                
  Serial.begin (9600);                    // Inicializa el puerto seria a 9600 baudios
  attachInterrupt(1, RUEDADER, FALLING);  // Lectura de interrupciones en pin 1
  attachInterrupt(3, RUEDAIZQ, FALLING);  // Lectura de interrupciones en pin 2
  pinMode(ECHO, INPUT);                   // define el pin 6 como entrada (echo)
  pinMode(TRIG, OUTPUT);                  // Define el pin 7 como salida  (triger)
  pinMode(11, 1);                         // Define el pin 11 como salida en LED verde
  pinMode(12, 1);                         // Define el pin 12 como salida en Buzzer
  pinMode(13, 1);                         // Define el pin 13 como salida en LED rojo
  } 
  
void loop() {


  
  //Instrucciones para sensor ultrasonico HC-SR04 
  
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);   // genera el pulso de triger por 10ms
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  duracion = pulseIn(ECHO, HIGH);
  distancia = (duracion/2) / 29;                // calcula la distancia en centimetros


  //Intrucciones para deteccion de distancia, avisos y velociad de motores

  Serial.println(distancia);
  if (distancia >= 400 || distancia <= 0){     // Si la distancia es mayor a 400cm o menor a 0cm 
   // Serial.println("---");                     // No mide nada
  }

  else {
    //Serial.println(distancia);                  // Envia el valor de la distancia por el puerto serial
    //Serial.println("cm");                     // Le coloca a la distancia los centimetros "cm"
    digitalWrite(13, 0);                      // en bajo el pin 13 
  } 
  
   if (distancia <= 25 && distancia >= 2){ 
     
      digitalWrite(13, 1);                    // Si la distancia esta entre 2 y 25 en alto pin 13
      valor=digitalRead(13);                  // Lee el estado del pin 13
        if (valor==HIGH){                
          analogWrite(MotorA,x=1);            // Si pin 13 esta en alto pin 3 manda un señal PWM al 0%
          analogWrite(MotorB,x=1);            // Si pin 13 esta en alto pin 5 manda un señal PWM al 0% 
       delay(10);
    }
    
        if (valor==LOW) {
          analogWrite(MotorA,x=0);            // Si pin 13 esta en bajo pin 3 manda un señal PWM al 0%
          analogWrite(MotorB,x=0);            // Si pin 13 esta en bajo pin 5 manda un señal PWM al 0% 
          delay(10);
      valor=0; 
      }
   }
   
   if (distancia <= 50 && distancia >= 26){
      
      digitalWrite(12, 1);                    // Si distancia esta entre 26 y 50 en alto pin 12
      valor=digitalRead(12);                  // Lee el estado del pin 12
        if (valor==HIGH){
        analogWrite(MotorA,x=125);             // Si pin 12 esta en alto pin 3 manda una señal PWM al 50%
        analogWrite(MotorB,x=125);             // Si pin 12 esta en alto pin 5 manda una señal PWM al 50%  
      delay(10);
    }
    
       if (valor==LOW) {
         analogWrite(MotorA,x=0);             // Si pin 12 esta en bajo pin 3 manda una señal PWM al 0%
         analogWrite(MotorB,x=0);             // Si pin 12 esta en bajo pin 5 manda una señal PWM al 0% 
      delay(10);
      valor=0; 
        } 
    }
  
    else {
    digitalWrite(12, 0);                     // Si distancia no esta entre 26 y 50 en bajo el pin 12
    }


   if (distancia <= 100 && distancia >= 51){
    
      digitalWrite(11, 1);                   // Si distancia esta entre 51 y 100 en alto pin 11
      valor=digitalRead(11);
        if (valor==HIGH){
         analogWrite(MotorA,x=200);          // Si pin 12 esta en alto pin 3 manda una señal PWM al 75%       
         analogWrite(MotorB,x=200);          // Si pin 12 esta en alto pin 5 manda una señal PWM al 75% 
      delay(10);
      }
      
       if (valor==LOW) {
         analogWrite(MotorA,x=0);            // Si pin 12 esta en bajo pin 3 manda una señal PWM al 0%
         analogWrite(MotorB,x=0);            // Si pin 12 esta en bajo pin 5 manda una señal PWM al 0% 
      delay(10);
       valor=0; 
       }   
  }
  
   else {
    digitalWrite(11, 0);                     // Si distancia no esta entre 51 y 100 en bajo pin 11 
    }

   // Resultados de encoders
   
  // Serial.print("Pulsos en rueda derecha=");
   Serial.println(DER*3);                           // Factor de RPM: 60 segundos / 20 segmentos de encoder = 3
  // Serial.println("RPM");
  // Serial.print("Pulsos en rueda izquiera=");
   Serial.println(IZQ*3);
  // Serial.println("RPM");                        // Factor de RPM: 60 segundos / 20 segmentos de encoder = 3
  // Serial.println("------------------");


   //Intrucciones para funcinomineto de motores en un rango de distancia superior a 100cm

   if (distancia <= 400 && distancia >= 100){
           
           analogWrite(MotorA,x=255);          // PWM al 100%       
           analogWrite(MotorB,x=255);          // PWM al 100% 
           delay(10);

      if (IZQ < DER){  
        analogWrite(MotorA,x= IZQ/DER * 256);          // PWM al 100%       
        analogWrite(MotorB,x=255);          // PWM al 100% 
        delay(10);     
       }

  }
   
  DER=0;
  IZQ=0;
      
  delay(400);                                // Espera 999ms para que se logre ver la distancia en la consola
}

void RUEDADER(){
  DER++;                                    // Incremetar +1 en encoder optico
  }

void RUEDAIZQ(){
  IZQ++;                                    // Incrementar +1 en encoder optico
  } 
