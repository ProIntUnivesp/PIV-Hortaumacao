/* Sistema Automático de Irrigação de Solo
   Conforme a Umidade e Temperatura Ambiente
*/

// Carrega as definicoes dos pinos A/D:
#define pinDigital1 12  // sensor umidade 1
#define pinDigital2 13  // sensor umidade 2
#define pinAnalog1  0   // sensor umidade 1
#define pinAnalog2  1   // sensor umidade 2
#define pinAnalog3  2   // sensor temperatura
#define pinRelay   7    // saida rele

// Inicializa as variaveis do sistema:
// Parâmetros do termistor
float beta = 3950.0;
float r0 = 10000.0;
float t0 = 273.0 + 25.0;
float rx = r0 * exp(-beta/t0);
 
// Parâmetros do circuito de Temperatura
float vcc = 5.0;
float R = 10000.0;
float AnalogOutput1 = 0;
float voltage1 = 0;
int LeituraSensor1 = 0;
float AnalogOutput2 = 0;
float voltage2 = 0;
int LeituraSensor2 = 0;
float temp = 0.0;
float vref = 0.0;
float v = 0.0;


// Inicializa todos os parametros:
void setup() {
  pinMode(pinDigital1, INPUT);
  pinMode(pinDigital2, INPUT);
  pinMode(pinAnalog1, INPUT);
  pinMode(pinAnalog2, INPUT);
  pinMode(pinAnalog3, INPUT);  
  pinMode(pinRelay, OUTPUT);  
  Serial.begin(9600);
}

// A funcao loop roda indefinidamente lendo os sensores:
void loop() {
  
  // Calculando a temperatura:
  vref = analogRead(pinAnalog3);
  v = vref / 1023.0;
  float rt = (vcc*R)/v - R;
  temp = (beta / log(rt/rx)) - 230.0;

  //Imprimindo no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println("°C");

  AnalogOutput1 = analogRead(pinAnalog1);
  AnalogOutput2 = analogRead(pinAnalog2);
  LeituraSensor1 = digitalRead(pinDigital1);
  LeituraSensor2 = digitalRead(pinDigital2);
  float voltage1 = AnalogOutput1 * (5.0 / 1023.0);
  float voltage2 = AnalogOutput2 * (5.0 / 1023.0);
  Serial.println("Saida analog1:");
  Serial.println(voltage1);
  Serial.println("Saida analog2:");
  Serial.println(voltage2);
  Serial.println("Saida digital sensor 1:");
  Serial.println(LeituraSensor1);
  Serial.println("Saida digital sensor 2:");
  Serial.println(LeituraSensor2);
  
  // Condicional que liga e desliga a agua:
  if(((LeituraSensor1 == HIGH) || (LeituraSensor2 == HIGH)) && (temp <= 28.0))
    digitalWrite(pinRelay,LOW);
   
  else
    digitalWrite(pinRelay,HIGH);   
  
  delay(20000);

}
