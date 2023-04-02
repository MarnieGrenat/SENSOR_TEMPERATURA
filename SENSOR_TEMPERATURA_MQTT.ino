/*
Author: Gabriela Dellamora Paim
Version: 02.04.23
BOARD: esp8266
Libraries and versions:
DHT sensor library by Adafruit -> Version 1.1.1
Adafruit GFX Library by Adafruit -> Version 1.11.4
Adafruit BusIO by Adafruit -> Version 1.14.1
Adafruit Unified Sensor by Adafruit -> Version 1.1.9
Adafruit SSD1306 by Adafruit -> Version 1.1.2
PubSubClient by Nick O'Leary -> Verison 2.6.0
*/


/* -- WIFI -- */
#include <ESP8266WiFi.h>
const char* ssid =  "Mario Paim";
const char* password = "milena09";
WiFiClient espClient;


/* -- MQTT -- */
#include <PubSubClient.h>
const char* broker= "test.mosquito.org"; // Change to RASBERRY's IP
const char* clientID = "quarto_marnie";
PubSubClient client(espClient);
const char* topicT = "marnie-room/temperatura";
const char* topicH = "marnie-room/umidade";


/* -- DHT -- */
#include <DHT.h>
#define DHTPIN D3
#define DHTTYPE DHT11
// para dht11 apenas leitura de inteiros, dht22 pode ser utilizado float tbm
DHT dht(DHTPIN, DHTTYPE);
// Variáveis globais DHT
int humidity;
int temperature;

/* -- DISPLAY -- */
#include <Adafruit_SSD1306.h>
#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);


void setup() {
  configurarDisplay();
  conectarWifi();
  client.setServer(broker, 1883);
}

void loop(){
  if (!client.connected()){
    reconnectMQTT();
  }
    medir_temp_umidade();
    publishTopicsHT();
    mostrarTempUmid();
}

/* --- FUNÇÕES AUXILIARES --- */
//--- CONFIGURAÇÃO E CONEXÃO WIFI ---
void conectarWifi(){
  delay(10);
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print("Connecting to: ");
  display.print(ssid);
  display.display();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.display();
  }
}

// --- RECONECTAR MQTT CLIENT -- 
void reconnectMQTT(){
  while (!client.connected()){
    client.connect(clientID);
  }
}

//--- CONFIGURAR O DISPLAY ---
void configurarDisplay() {
  display.begin(SSD1306_SWITCHCAPVCC, 0X3C);  // GOOGLE:'ARDUINO SCANNER I2C' para encontrar o endereço do device
  display.setTextColor(WHITE);                // Modificar display
  display.clearDisplay();
}
// --- MQTT TEMPERATURA E UMIDADE ---
void publishTopicsHT(){
  client.publish(topicT, String(temperature).c_str(), true); // true => permanecer com a info no broker
  client.publish(topicH, String(humidity).c_str(), true); 

}

//--- MEDIÇÃO DE TEMPERATURA E UMIDADE ---
void medir_temp_umidade() {
  humidity = dht.readHumidity();             // inicializando var e atribuindo valor de leitura
  temperature = dht.readTemperature(false);  // false == medida em C, n em Fº
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" *C");
  Serial.print("Umidade:");
  Serial.print(humidity);
  Serial.print("%");
  Serial.println("");
  Serial.println("");
  delay(5000);
}

//--- MOSTRA TEMPERATURA E UMIDADE ---
void mostrarTempUmid(){
  mostrarMensagemDisplay("Temperatura: ", (temperature), " C");
  mostrarMensagemDisplay("Umidade: ", (humidity), " %");
}

//--- EXIBE TEMPERATURA E UMIDADE NO DISPLAY ---
void mostrarMensagemDisplay(const char* text_1, int medicao, const char* text_2){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(text_1);

  display.setTextSize(5);
  display.setCursor(20, 20);
  display.print(medicao);

  display.setTextSize(2);
  display.print(text_2);

  display.display();
  delay(3000);
}