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

uint8_t park1 = 0;
uint8_t park2 = 0;
uint8_t park3 = 0;
uint8_t park4 = 0;
uint8_t LED1pin = 2;
bool LED1status = LOW;

//************************************************************************************************
// Configuración
//************************************************************************************************
void setup() {
  Serial.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  pinMode(LED1pin, OUTPUT);

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
  server.handleClient();
  server.send(200, "text/html", SendHTML(park1, park2, park3, park4));
}
  
//************************************************************************************************
// Handler de Inicio página
//************************************************************************************************
void handle_OnConnect() {
  LED1status = LOW;
  Serial.println("GPIO2 Status: OFF");
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
String SendHTML(uint8_t p1,uint8_t p2,uint8_t p3,uint8_t p4) {
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
ptr += "  \tbackground-color: #99ffffff;;\n";
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
ptr += "    <td id = \"p\"><b>1A</b></td>\n";
ptr += "    <td>a</td>\n";
ptr += "  </tr>\n";
ptr += "  <tr>\n";
ptr += "    <td id = \"p\"><b>1B</b></td>\n";
ptr += "    <td>b</td>\n";
ptr += "  </tr>\n";
ptr += "  <tr>\n";
ptr += "    <td id = \"p\"><b>1C</b></td>\n";
ptr += "    <td>c</td>\n";
ptr += "  </tr>\n";
ptr += "  <tr>\n";
ptr += "    <td id = \"p\"><b>1D</b></td>\n";
ptr += "    <td>d</td>\n";
ptr += "  </tr>\n";
ptr += "  <tr>\n";
ptr += "    <td id = \"p\"><b>Total disponibles</b></td>\n";
ptr += "    <td>x</td>\n";
ptr += "  </tr>\n";
ptr += "</table>\n";
ptr += "\n";
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
