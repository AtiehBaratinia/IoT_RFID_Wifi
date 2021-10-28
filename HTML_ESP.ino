const char* password = "****"; //replace password value with your wifi password



#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "Amir"; //replace ssid value with your own wifi hotspot name

 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
int LEDPin = D3;
int ldr = A0;
int brightness = 0;
void setup(void){
  //the HTML of the web page

  //make the LED pin output and initially turned off
  pinMode(LEDPin, OUTPUT);
  pinMode(ldr, INPUT);
  digitalWrite(LEDPin, LOW);
   
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

 
   
  server.on("/", [](){
    page = "<h1>HW2 Q3</h1>";
  page +="<p><a href=\"TurnOnLED\"><button>Turn on LED</button></a>&nbsp;<a href=\"TurnOffLED\"><button>Turn off LED</button></a>&nbsp;<a href=\"CheckLDR\"><button>Check LDR</button></a></p>";
    server.send(200, "text/html", page);
  });
  server.on("/TurnOnLED", [](){
    page = "<h1>HW2 Q3</h1><p><strong>LED is ON</strong></p>";
  page +="<p><a href=\"TurnOnLED\"><button>Turn on LED</button></a>&nbsp;<a href=\"TurnOffLED\"><button>Turn off LED</button></a>&nbsp;<a href=\"CheckLDR\"><button>Check LDR</button></a></p>";
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, HIGH);
    delay(1000);
  });
  server.on("/TurnOffLED", [](){
      page = "<h1>HW2 Q3</h1><p><strong>LED is OFF</strong></p>";
  page +="<p><a href=\"TurnOnLED\"><button>Turn on LED</button></a>&nbsp;<a href=\"TurnOffLED\"><button>Turn off LED</button></a>&nbsp;<a href=\"CheckLDR\"><button>Check LDR</button></a></p>";
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, LOW);
    delay(1000); 
  });
  
  server.on("/CheckLDR", [](){
    brightness = analogRead(ldr);
      page = "<h1>HW2 Q3</h1><p><strong>"+String(brightness) +"</strong></p>";
  page +="<p><a href=\"TurnOnLED\"><button>Turn on LED</button></a>&nbsp;<a href=\"TurnOffLED\"><button>Turn off LED</button></a>&nbsp;<a href=\"CheckLDR\"><button>Check LDR</button></a></p>";
    server.send(200, "text/html", page);
    delay(1000); 
  });
 
  
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
}
