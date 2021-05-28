/*************************************************************************************************
  ESP32 Web Server
  Ejemplo de creación de Web server
  Basándose en los ejemplos de:
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://electropeak.com/learn
**************************************************************************************************/
//************************************************************************************************
// Librerías
//************************************************************************************************
#include <WiFi.h>
#include <WebServer.h>
//************************************************************************************************
// Variables globales
//************************************************************************************************
// SSID & Password
const char* ssid = "FAMEXT";  // Enter your SSID here
const char* password = "Maquito12345";  //Enter your Password here

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)
char park[20];
char x;
//uint8_t park = 0;
uint8_t park1 = 0;
uint8_t park2 = 1;
uint8_t park3 = 0;
uint8_t park4 = 1;
uint8_t LED1pin = 2;
#define RXD0 3
#define TXD0 1

//************************************************************************************************
// Configuración
//************************************************************************************************
void setup() {
  Serial.begin(115200, SERIAL_8N1, RXD0, TXD0);

  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  //configurar pines
  pinMode(LED1pin, OUTPUT);
  pinMode(23, INPUT);
  pinMode(22, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(15, OUTPUT);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_OnConnect); // Directamente desde e.g. 192.168.0.8

  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);


}
//************************************************************************************************
// loop principal
//************************************************************************************************
void loop() {
  //Chequear el uart
  if (Serial.available() > 0) {
    Serial.readBytes(park, 2);
    Serial.println(park[0]);

  }
  x=park[0];
  if (x == 'a') {
    park1 = 1;
  }
  else if (x == 'b'){
    park1 = 0;
  }
  else if (x == 'c'){
    park2 = 1;
  }
  else if(x == 'd'){
    park2 = 0;
  }
  else if(x == 'e'){
    park3 = 1;
  }
  else if(x == 'f'){
    park3 = 0;
  }
  else if(x == 'g'){
    park4 = 1;
  }
  else if(x == 'h'){
    park4 = 0;
  }
  
  //Serial.println(park);



  server.handleClient();
  server.send(200, "text/html", SendHTML(park1, park2, park3, park4));
}

//************************************************************************************************
// Handler de Inicio página
//************************************************************************************************
void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(park1, park2, park3, park4));
  delay(1000);
}
//************************************************************************************************
// Handler de led1on
//************************************************************************************************

//************************************************************************************************
// Handler de led1off
//************************************************************************************************

//************************************************************************************************
// Procesador de HTML
//************************************************************************************************
String SendHTML(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<html>\n";
  ptr += "<head>\n";
  ptr += "<style>\n";
  ptr += "table {\n";
  ptr += "  font-family: arial, sans-serif;\n";
  ptr += "  border-collapse: collapse;\n";
  ptr += "  width: 100%;\n";
  ptr += "}\n";
  ptr += "\n";
  ptr += "#p{\n";
  ptr += "\tborder: 3px solid #330000;\n";
  ptr += "  \tbackground-color: #99ffffff;\n";
  ptr += "  \ttext-align: left;\n";
  ptr += "  \tpadding: 8px;\n";
  ptr += "}\n";
  ptr += "\n";
  ptr += "h1{\n";
  ptr += "\ttext-align: center;\n";
  ptr += "}\n";
  ptr += "\n";
  ptr += "td{\n";
  ptr += "  border: 3px solid #330000;\n";
  ptr += "  background-color: #00ff99;\n";
  ptr += "  text-align: left;\n";
  ptr += "  padding: 8px;\n";
  ptr += "}\n";
  ptr += "\n";
  ptr += "th {\n";
  ptr += "\ttext-align: center;\n";
  ptr += "}\n";
  ptr += "\n";
  ptr += "tr:nth-child(even) {\n";
  ptr += "  background-color: #00ff99;\n";
  ptr += "}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "\n";
  ptr += "<h1>Bienvenido al sistema automatizado de parqueos</h1>\n";
  ptr += "\n";
  ptr += "<table>\n";
  ptr += "  <tr>\n";
  ptr += "    <th>Parqueo</th>\n";
  ptr += "    <th>Estado</th>\n";
  ptr += "  </tr>\n";
  ptr += "  <tr>\n";

  //controlar los parqueos
  if (p1 == 0) {
    ptr += "    <td id = \"p\"><b>1A</b></td>\n";
    ptr += "    <td id =\"p1\">Parqueo Libre</td>\n";
  }
  else {
    ptr += "    <td id = \"p\"><b>1A</b></td>\n";
    ptr += "    <td id =\"p1\">Parqueo Ocupado</td>\n";
  }

  ptr += "  </tr>\n";
  ptr += "  <tr>\n";

  if (p2 == 0) {
    ptr += "    <td id = \"p\"><b>1B</b></td>\n";
    ptr += "    <td id =\"p2\">Parqueo Libre</td>\n";
  }
  else {
    ptr += "    <td id = \"p\"><b>1B</b></td>\n";
    ptr += "    <td id =\"p2\">Parqueo Ocupado</td>\n";
  }

  ptr += "  </tr>\n";
  ptr += "  <tr>\n";

  if (p3 == 0) {
    ptr += "    <td id = \"p\"><b>1C</b></td>\n";
    ptr += "    <td id =\"p3\">Parqueo Libre</td>\n";
  }
  else {
    ptr += "    <td id = \"p\"><b>1C</b></td>\n";
    ptr += "    <td id =\"p3\">Parqueo Ocupado</td>\n";
  }

  ptr += "  </tr>\n";
  ptr += "  <tr>\n";

  if (p4 == 0) {
    ptr += "    <td id = \"p\"><b>1D</b></td>\n";
    ptr += "    <td id =\"p4\">Parqueo Libre</td>\n";
  }
  else {
    ptr += "    <td id = \"p\"><b>1D</b></td>\n";
    ptr += "    <td id =\"p4\">Parqueo Ocupado</td>\n";
  }

  ptr += "  </tr>\n";
  ptr += "  <tr>\n";
  ptr += "    <td id = \"p\"><b>Total disponibles</b></td>\n";

  if ((p1 + p2 + p3 + p4) == 0) {
    ptr += "    <td id = \"tot\">4</td>\n";
  }
  else if ((p1 + p2 + p3 + p4) == 1) {
    ptr += "    <td id = \"tot\">3</td>\n";
  }
  else if ((p1 + p2 + p3 + p4) == 2) {
    ptr += "    <td id = \"tot\">2</td>\n";
  }
  else if ((p1 + p2 + p3 + p4) == 3) {
    ptr += "    <td id = \"tot\">1</td>\n";
  }
  else if ((p1 + p2 + p3 + p4) == 4) {
    ptr += "    <td id = \"tot\">0</td>\n";
  }

  ptr += "  </tr>\n";
  ptr += "</table>\n";
  ptr += "\n";
  ptr += "<style>\n";
  if (p1 == 1) {
    ptr += "#p1{\n";
    ptr += "\tbackground-color: #ff6633;\n";
    ptr += "  text-align: center; \n";
    ptr += "}\n";
  }
  else {
    ptr += "#p1{\n";
    ptr += "\tbackground-color: #00ff99;\n";
    ptr += "    text-align: center; \n";
    ptr += "}\n";
  }

  if (p2 == 1) {
    ptr += "\n";
    ptr += "#p2{\n";
    ptr += "\tbackground-color: #ff6633;\n";
    ptr += "    text-align: center; \n";
    ptr += "}\n";
  }
  else {
    ptr += "#p2{\n";
    ptr += "\tbackground-color: #00ff99;\n";
    ptr += "    text-align: center; \n";
    ptr += "}\n";
    ptr += "\n";
  }

  if (p3 == 1) {
    ptr += "#p3{\n";
    ptr += "\tbackground-color: #ff6633;\n";
    ptr += "    text-align: center; \n";
    ptr += "}\n";
  }
  else {
    ptr += "#p3{\n";
    ptr += "\tbackground-color: #00ff99;\n";
    ptr += "    text-align: center; \n";
    ptr += "}\n";
    ptr += "\n";
  }

  if (p4 == 1) {
    ptr += "#p4{\n";
    ptr += "\tbackground-color: #ff6633;\n";
    ptr += "    text-align: center; \n";
    ptr += "}\n";
  }
  else {
    ptr += "#p4{\n";
    ptr += "\tbackground-color: #00ff99;\n";
    ptr += "    text-align: center; \n";
    ptr += "}\n";
    ptr += "\n";
  }

  ptr += "#tot{\n";
  ptr += "\tbackground-color: #ffff99;\n";
  ptr += "    text-align: center; \n";
  ptr += "}\n";
  ptr += "\n";
  ptr += "</style>\n";
  ptr += "\n";
    ptr += "<script>\n";
  ptr += "<!--\n";
  ptr += "function timedRefresh(timeoutPeriod) {\n";
  ptr += "\tsetTimeout(\"location.reload(true);\",timeoutPeriod);\n";
  ptr += "}\n";
  ptr += "\n";
  ptr += "window.onload = timedRefresh(3000);\n";
  ptr += "\n";
  ptr += "//   -->\n";
  ptr += "</script>";
  ptr += "</body>\n";
  ptr += "</html>";


  return ptr;
}
//************************************************************************************************
// Handler de not found
//************************************************************************************************
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}
