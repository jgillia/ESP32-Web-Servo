#include <WiFi.h>
#include <Servo.h>
#define OFF 93
#define CLOCKWISE 53
#define COUNTERCLOCK 133

//The left and right servos are opposite of eachother (writing CLOCKWISE to both will result in spinning, not moving forward)
Servo leftServo;  // create servo object to control a servo
Servo rightServo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

// Replace with your network credentials
const char* ssid     = "FBI Van";
const char* password = "WFFXVRMN4E7U3";

// Set web server port number to 80
WiFiServer server(80);
IPAddress espIP;

// Variable to store the HTTP request
String header;

// Decode HTTP GET value
String valueString1 = String(5);
String form;
int pos1 = 0;
int pos2 = 0;

void idle() {
  leftServo.write(OFF);
  rightServo.write(OFF);
}
void forward(int duration) {
  leftServo.write(COUNTERCLOCK);
  rightServo.write(CLOCKWISE);
  delay(duration * 1000);
  //Serial.print("In forward function\n");
  idle();
}

void backward(int duration) {
  leftServo.write(CLOCKWISE);
  rightServo.write(COUNTERCLOCK);
  delay(duration * 1000);
  //Serial.print("In backward function\n");
  idle();
}

void right(int angle)
{
  if(angle == 30)
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(250);
    idle();
  }
  else if(angle == 45)
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(400);
    idle();
  }
  else if(angle == 60)
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(550);
    idle();
  }
  else if(angle == 90)
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(800);
    idle();
  }
  else
  {
    idle();
  }
}

void left(int angle)
{
  if(angle == 30)
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(250);
    idle();
  }
  else if(angle == 45)
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(400);
    idle();
  }
  else if(angle == 60)
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(550);
    idle();
  }
  else if(angle == 90)
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(800);
    idle();
  }
  else
  {
    idle();
  }
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
  espIP = WiFi.localIP();
  Serial.println(espIP);
  server.begin();

  //form = "<form action=\"http://"espIP"\" method=\"get\">";
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
            client.print("<form action=\"http://");
            client.print(espIP);
            client.print("\"");
            client.println(" method = \"get\">");
            client.println("1st Command:<input type=\"text\" name=\"first\"><br>");
            client.println("2nd Command:<input type=\"text\" name=\"second\"><br>");
            client.println("3rd Command:<input type=\"text\" name=\"third\"><br>");
            client.println("4th Command:<input type=\"text\" name=\"fourth\"><br>");
            client.println("5th Command:<input type=\"text\" name=\"fifth\"><br>");
            client.println("<input type=\"hidden\" name=\"end\"><br>");
            client.println("<button type=\"submit\">Run</button>");
            client.println("</form>");
            
            //GET /?value=180& HTTP/1.1
            int i = 0;
            pos1 = header.indexOf('=');
            pos2 = header.indexOf('%');
            while(i < 5)
            {
              if(i > 0)
              {
                pos1 = header.indexOf('=', pos2);
                pos2 = header.indexOf('%', pos1);
              }
              
              valueString1 = header.substring(pos1+1, pos2);  
              if(valueString1 == "forward")
              {
                pos1 = header.indexOf('8', pos2);
                pos2 = header.indexOf('%', pos1);
                valueString1 = header.substring(pos1+1, pos2);
                forward(valueString1.toInt());
              }
              else if(valueString1 == "backward")
              {
                pos1 = header.indexOf('8', pos2);
                pos2 = header.indexOf('%', pos1);
                valueString1 = header.substring(pos1+1, pos2);
                backward(valueString1.toInt());
              }
              else if(valueString1 == "right")
              {
                pos1 = header.indexOf('8', pos2);
                pos2 = header.indexOf('%', pos1);
                valueString1 = header.substring(pos1+1, pos2);
                right(valueString1.toInt());
              }
              else if(valueString1 == "left")
              {
                pos1 = header.indexOf('8', pos2);
                pos2 = header.indexOf('%', pos1);
                valueString1 = header.substring(pos1+1, pos2);
                left(valueString1.toInt());
              }
              else
              {
                idle();
              }
              i++;
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
