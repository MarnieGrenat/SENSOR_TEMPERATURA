/*
Author: Gabriela Dellamora Paim
Version: 10.03.23
Libraries and versions:
DHT sensor library by Adafruit -> Version 1.1.1
Adafruit GFX Library by Adafruit -> Version 1.11.4
Adafruit BusIO by Adafruit -> Version 1.14.1
Adafruit Unified Sensor by Adafruit -> Version 1.1.9
Adafruit SSD1306 by Adafruit -> Version 1.1.2
*/


//                                                            -- DHT --
#include <DHT.h>
#define DHTPIN D3
#define DHTTYPE DHT11
// para dht11 apenas leitura de inteiros, dht22 pode ser utilizado float tbm

DHT dht(DHTPIN, DHTTYPE);
// Variáveis globais DHT
int humidity;
int temperature;

//                                                          -- DISPLAY --
#include <Adafruit_SSD1306.h>
#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

// -- SETUP --
void setup() {
  // Configurar a serial para visualizar as informações
  Serial.begin(115200);
  configurarDisplay();
}

// -- LOOP --
void loop() {
  medir_temp_umidade();
  mostrarTempUmid();
}

//                                                    --- FUNÇÕES AUXILIARES ---

// --- CONFIGURAR O DISPLAY ---
void configurarDisplay() {
  display.begin(SSD1306_SWITCHCAPVCC, 0X3C);  // GOOGLE:'ARDUINO SCANNER I2C' para encontrar o endereço do device
  display.setTextColor(WHITE);                // Modificar display
  display.clearDisplay();
}
// --- MEDIÇÃO DE TEMPERATURA E UMIDADE ---
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

// --- MOSTRA TEMPERATURA E UMIDADE ---
void mostrarTempUmid(){
  mostrarMensagemDisplay("Temperatura: ", (temperature), " C");
  mostrarMensagemDisplay("Umidade: ", (humidity), " %");
}

// --- EXIBE TEMPERATURA E UMIDADE NO DISPLAY ---
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