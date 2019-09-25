/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <WiFi.h>
#include <Servo.h>
#define OFF 92
#define CLOCKWISE 52
#define COUNTERCLOCK 132

//The left and right servos are opposite of eachother (writing CLOCKWISE to both will result in spinning, not moving forward)
Servo leftServo;  // create servo object to control a servo
Servo rightServo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

// Replace with your network credentials
const char* ssid     = "FBI Van";
const char* password = "WFFXVRMN4E7U3";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Decode HTTP GET value
String valueString = String(5);
int pos1 = 0;
int pos2 = 0;

void idle() {
  leftServo.write(OFF);
  rightServo.write(OFF);
}
void forward() {
  leftServo.write(COUNTERCLOCK);
  rightServo.write(CLOCKWISE);
}

void backward() {
  leftServo.write(CLOCKWISE);
  rightServo.write(COUNTERCLOCK);
}

void smallTurnRight() {
  //30 degree turn
  leftServo.write(COUNTERCLOCK);
  rightServo.write(COUNTERCLOCK);
  delay(150);
  idle();
}

void halfTurnRight() {
  //45 degree turn
  leftServo.write(COUNTERCLOCK);
  rightServo.write(COUNTERCLOCK);
  delay(450);
  idle();
}

void largeTurnRight() {
  //60 degree turn
  leftServo.write(COUNTERCLOCK);
  rightServo.write(COUNTERCLOCK);
  delay(150);
  idle();
}

void turnRight() {
  //90 degree turn
  leftServo.write(COUNTERCLOCK);
  rightServo.write(COUNTERCLOCK);
  delay(800);
  idle();
}
void smallTurnLeft() {
  //30 degree turn
  leftServo.write(CLOCKWISE);
  rightServo.write(CLOCKWISE);
  delay(150);
  idle();
}

void halfTurnLeft() {
  //45 degree turn
  leftServo.write(CLOCKWISE);
  rightServo.write(CLOCKWISE);
  delay(450);
  idle();
}

void largeTurnLeft() {
  //60 degree turn
  leftServo.write(CLOCKWISE);
  rightServo.write(CLOCKWISE);
  delay(600);
  idle();
}

void turnLeft() {
  //90 degree turn
  leftServo.write(CLOCKWISE);
  rightServo.write(CLOCKWISE);
  delay(800);
  idle();
}

void spinCCW() {
  leftServo.write(CLOCKWISE);
  rightServo.write(CLOCKWISE);
}

void spinCW() {
  leftServo.write(COUNTERCLOCK);
  rightServo.write(COUNTERCLOCK);
}

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  //IPAddress espIP(WiFi.localIP());
  //Serial.println(espIP);
  Serial.println(WiFi.localIP());
  server.begin();

  leftServo.attach(26);  // attaches the servo on pin 26 to the servo object
  rightServo.attach(25);
  leftServo.write(OFF);  //Start with servos off
  rightServo.write(OFF);
}



void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
            client.println(".slider { width: 300px; }</style>");
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
                     
            // Web Page
            client.println("</head><body><h1>ESP32 with Servo</h1>");
            /*
            client.println("<p>Position: <span id=\"servoPos\"></span></p>");          
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider\" onchange=\"servo(this.value)\" value=\""+valueString+"\"/>");
            
            client.println("<script>var slider = document.getElementById(\"servoSlider\");");
            client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
            client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");
            client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}</script>");
            client.println("</body></html>");     
            */
            //Button to turn on red led
            client.println("<form action=\"http://http://192.168.137.236\" method=\"get\">");
            client.println("<input type=\"hidden\" name=\"value\" value=\"turnRight%\"><br>");
            client.println("<button type=\"submit\">Turn Right</button>");
            client.println("</form>");
            //Button to turn off red led
            client.println("<form action=\"http://http://192.168.137.236\" method=\"get\">");
            client.println("<input type=\"hidden\" name=\"value\" value=\"turnLeft%\"><br>");
            client.println("<button type=\"submit\">Turn Left</button>");
            client.println("</form>");
            /*
            client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");
            client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}</script>");
            client.println("</body></html>"); 
            */
            //GET /?value=180& HTTP/1.1
            /*
            if(header.indexOf("GET /?value=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1+1, pos2);
              
              //Rotate the servo
              myservo.write(valueString.toInt());
              Serial.println(valueString); 
            }
            */
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('%');
              //pos2 = header.length();
              //Serial.print(header);
              valueString = header.substring(pos1+1, pos2);

              if(valueString == "turnRight") {
                turnRight();
              }
              else if (valueString == "turnLeft") {
                turnLeft();
              }
              else {
                idle();
              }
            
              
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
