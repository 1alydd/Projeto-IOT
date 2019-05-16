#include <Ethernet.h>

// Pinos do sensor de nivel (boia)
int pinosensorboia01 = 4;
int pinosensorboia02 = 2;
int led_verde = 3; // Led verde
int led_vermelho = 4;// led vermelho
int rele = 5; //rele
//variáveis sensor de vazao
float vazao; // Armazenar o valor em L/min 
float media = 0; // Média a cada 1 minuto
int contaPulso; // Quantidade de pulsos
int i = 0; // Contador

void setup() {
  Serial.begin(9600);
  pinMode(pinosensorboia01, INPUT);
  pinMode(pinosensorboia02, INPUT);
  pinMode(9, INPUT);// sensor de vazao
  pinMode(pinosensorboia02, INPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(rele, OUTPUT);
  // deixa a bomba desligada
  digitalWrite(rele, HIGH);
  attachInterrupt(0, inpulso, RISING); 
  Serial.println("\n\nInicio\n\n"); //Imprime Inicio na serial (nao sei se é necessario)

}

void loop() {
  int estado_sensor_boia01 = digitalRead(pinosensorboia01);
  int estado_sensor_boia02 = digitalRead(pinosensorboia02);
  contaPulso = 0;   //Zera a variável para contar os giros por segundos
    
  Serial.print("O Nível d'água da caixa se encontra: ");
  Serial.println(estado_sensor_boia01);
  switch(estado_sensor_boia01)
  {
  case 0://afogado
    Serial.println("Abaixo do nível d'agua, economize!");
    break;
  case 1://desafogado
    Serial.println("Atenção! O nível d'agua está crítico");
    break;
  }
  delay(1050);

  Serial.print("O Nível d'água da caixa se encontra: ");
  Serial.println(estado_sensor_boia02);
  switch(estado_sensor_boia02)
  {
  case 0:
    // Fica vermelho o led pois a caixa estaria cheia e a bomba seria ligada para passar a água para outro lugar.
    Serial.println("Caixa Cheia bomba d agua ativada");
    digitalWrite(led_vermelho, 0);
    digitalWrite(led_verde, 1);
    digitalWrite(rele, 0);
    // quanto tempo a boia vai ficar ligada
    delay(5000);
    break;        
  case 1:
    // Fica verde o led pois a caixa estaria enchendo
    Serial.println("Caixa enchendo bomba d agua desativada");
    digitalWrite(led_vermelho, 1);
    digitalWrite(led_verde, 0);
    digitalWrite(rele, 1);
    break;
    }

    sei();      //Habilita interrupção
  delay (1000); //Aguarda 1 segundo
  cli();      //Desabilita interrupção
  
  vazao = contaPulso / 5.5; //Converte para L/min
  media=media+vazao; //Soma a vazão para o calculo da media
  i++;
  
  Serial.print(vazao); //Imprime na serial o valor da vazão
  Serial.print(" L/min - "); //Imprime L/min
  Serial.print(i); //Imprime a contagem i (segundos)
  Serial.println("s"); //Imprime s indicando que está em segundos
  
  if(i==60)
  {
    media = media/60; //Tira a media dividindo por 60
    Serial.print("\nMedia por minuto = "); //Imprime a frase Media por minuto =
    Serial.print(media); //Imprime o valor da media
    Serial.println(" L/min - "); //Imprime L/min
    media = 0; //Zera a variável media para uma nova contagem
    i=0; //Zera a variável i para uma nova contagem
    Serial.println("\n\nInicio\n\n"); //Imprime Inicio indicando que a contagem iniciou
  }
  }
  delay(1050);

 void inpulso ()
{ 
  contaPulso++; //Incrementa a variável de contagem dos pulsos
} 
}
