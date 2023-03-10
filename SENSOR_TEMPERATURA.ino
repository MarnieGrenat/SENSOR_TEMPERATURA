// Author: Gabriela Dellamora Paim
// Version: 10.03.23

#include <DHT.h>
#define DHTPIN D3 
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  // Configurar a serial para visualizar as informações
  Serial.begin(115200);
}

void loop() {
  int humidity = dht.readHumidity(); // inicializando var e atribuindo valor de leitura
  // para dht11 apenas leitura de inteiros, dht22 pode ser utilizado float tbm
  int temperature= dht.readTemperature(false); // false == medida em C, n em Fº
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.print(" *C");
  Serial.print("    ");
  Serial.print("Umidade: ");
  Serial.print(humidity);
  delay(5000);

}
