
//Adafruit MAX 6675
#include "max6675.h"
#include <SPI.h>
#include <SD.h>

const int data = 12;    //Saida do pino SO (Slave Out) do MAX 6675 = D6
const int CLK = 14;    // Clock da spi = D5
const int CS1 = 2;    //  CS do sensor 1 = D4
const int CS2 = 5;  //   CS do sensor 2 = D1 
const int CS3 = 15; //    CS do sensor 3 = D8

const int CSsd = 4; // pino D2 
const int SI = 13; // pino D7 

float dados = 0;

// Inicialização dos sensores com a biblioteca:
MAX6675 thermocouple1(CLK, CS1, data);
MAX6675 thermocouple2(CLK, CS2, data);
MAX6675 thermocouple3(CLK, CS3, data);


void setup() {
  Serial.begin(115200);
  delay(1000);
  

  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(4)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");


  Serial.println("MAX6675");
  // Espera-se o MAX estabilizar depois de ligado
  delay(500);

}


void loop() {
  
  // Puxando os valores da biblioteca:
    
   Serial.print("C = "); 
   Serial.println(thermocouple1.readCelsius()); // Chama-se a função thermocouple(x).readCelsius <- neste caso existem 3 funcoes desse tipo.
  
   Serial.print(" - ");

   Serial.println(thermocouple2.readCelsius());

   Serial.print(" - ");

   Serial.println(thermocouple3.readCelsius());
   
   delay(1000); // Para que o MAX funcione, o delay minimo deve ser 250ms. 


  String dataString = "";

  // read three sensors and append to the string:

    dados = thermocouple1.readCelsius();
    dataString += String(dados);
    dataString += ";";

    dados = thermocouple2.readCelsius();
    dataString += String(dados);
    dataString += ";";

    dados = thermocouple3.readCelsius();
    dataString += String(dados);
    dataString += "!";

    

  File dataFile = SD.open("PCVT.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
