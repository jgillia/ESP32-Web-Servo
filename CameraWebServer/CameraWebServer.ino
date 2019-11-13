//#include <ESP32Servo.h>
//#include <ServoTimer2.h>
#include "esp_camera.h"
#include <WiFi.h>
#include <Servo.h>
#define OFF 93
#define CLOCKWISE 53
#define COUNTERCLOCK 133

//
// WARNING!!! Make sure that you have either selected ESP32 Wrover Module,
//            or another board which has PSRAM enabled
//

// Select camera model
//define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_ESP_EYE
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE
#define CAMERA_MODEL_AI_THINKER

#include "camera_pins.h"

const char* ssid = "NETGEAR73";
const char* password = "orangewindow834";

// Set web server port number to 80
WiFiServer server(80);
// Set your Static IP address
IPAddress espIP(192, 168, 1, 11); //192.168.1.11
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

void startCameraServer();

Servo leftServo;  // create servo object to control a servo
Servo rightServo;  // create servo object to control a servo
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void idle() {
  leftServo.write(OFF);
  rightServo.write(OFF);
}

void forward(float duration) {
  //leftServo.attach(2);  // attaches the servo on pin 26 to the servo object
  //rightServo.attach(4);
  leftServo.write(COUNTERCLOCK);
  rightServo.write(CLOCKWISE);
  delay(duration * 1000);
  Serial.print("In forward function\n");
  idle();
  //leftServo.detach();  // attaches the servo on pin 26 to the servo object
  //rightServo.detach();
}

void backward(float duration) {
  leftServo.write(CLOCKWISE);
  rightServo.write(COUNTERCLOCK);
  delay(duration * 1000);
  //Serial.print("In backward function\n");
  idle();
}

void right(int angle)
{
  if((0 < angle) && (angle <= 14))//10 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(80);
    //Serial.println("10");
    idle();
  }
  else if((14 < angle) && (angle <= 24))//20 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(160);
    //Serial.println("20");
    idle();
  }
  else if((24 < angle) && (angle <= 34))//30 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(240);
    //Serial.println("30");
    idle();
  }
  else if((34 < angle) && (angle <= 44))//40 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(320);
    //Serial.println("40");
    idle();
  }
  else if((44 < angle) && (angle <= 54))//50 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(400);
    //Serial.println("50");
    idle();
  }
  else if((54 < angle) && (angle <= 64))//60 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(455);
    //Serial.println("60");
    idle();
  }
  else if((64 < angle) && (angle <= 74))//70 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(510);
    //Serial.println("70");
    idle();
  }
  else if((74 < angle) && (angle <= 84))//80 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(565);
    //Serial.println("80");
    idle();
  }
  else if((84 < angle) && (angle <= 94))//90 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(620);
    //Serial.println("90");
    idle();
  }
  else if((94 < angle) && (angle <= 104))//100 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(677.5);
    //Serial.println("100");
    idle();
  }
  else if((104 < angle) && (angle <= 114))//110 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(735);
    //Serial.println("110");
    idle();
  }
  else if((114 < angle) && (angle <= 124))//120 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(792.5);
    //Serial.println("120");
    idle();
  }
  else if((124 < angle) && (angle <= 134))//130 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(850);
    //Serial.println("130");
    idle();
  }
  else if((134 < angle) && (angle <= 144))//140 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(910);
    //Serial.println("140");
    idle();
  }
  else if((144 < angle) && (angle <= 154))//150 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(970);
    //Serial.println("150");
    idle();
  }
  else if((154 < angle) && (angle <= 164))//160 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(1030);
    //Serial.println("160");
    idle();
  }
  else if((164 < angle) && (angle <= 174))//170 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(1090);
    //Serial.println("170");
    idle();
  }
  else if((174 < angle) && (angle <= 184))//180 degree turn
  {
    leftServo.write(COUNTERCLOCK);
    rightServo.write(COUNTERCLOCK);
    delay(1150);
    //Serial.println("180");
    idle();
  }
  else
  {
    idle();
  }
  //leftServo.detach();  // attaches the servo on pin 26 to the servo object
  //rightServo.detach();
}

void left(int angle)
{  
  //leftServo.attach(2);  // attaches the servo on pin 26 to the servo object
  //rightServo.attach(4);
  if((0 < angle) && (angle <= 14))//10 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(80);
    //Serial.println("10");
    idle();
  }
  else if((14 < angle) && (angle <= 24))//20 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(160);
    //Serial.println("20");
    idle();
  }
  else if((24 < angle) && (angle <= 34))//30 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(240);
    //Serial.println("30");
    idle();
  }
  else if((34 < angle) && (angle <= 44))//40 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(320);
    //Serial.println("40");
    idle();
  }
  
  else if((44 < angle) && (angle <= 54))//50 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(400);
    //Serial.println("50");
    idle();
  }
  else if((54 < angle) && (angle <= 64))//60 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(455);
    //Serial.println("60");
    idle();
  }
  else if((64 < angle) && (angle <= 74))//70 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(510);
    //Serial.println("70");
    idle();
  }
  else if((74 < angle) && (angle <= 84))//80 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(565);
    //Serial.println("80");
    idle();
  }
  else if((84 < angle) && (angle <= 94))//90 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(620);
    //Serial.println("90");
    idle();
  }
  else if((94 < angle) && (angle <= 104))//100 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(677.5);
    //Serial.println("100");
    idle();
  }
  else if((104 < angle) && (angle <= 114))//110 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(735);
    //Serial.println("110");
    idle();
  }
  else if((114 < angle) && (angle <= 124))//120 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(792.5);
    //Serial.println("120");
    idle();
  }
  else if((124 < angle) && (angle <= 134))//130 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(850);
    //Serial.println("130");
    idle();
  }
  else if((134 < angle) && (angle <= 144))//140 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(910);
    //Serial.println("140");
    idle();
  }
  else if((144 < angle) && (angle <= 154))//150 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(970);
    //Serial.println("150");
    idle();
  }
  else if((154 < angle) && (angle <= 164))//160 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(1030);
    //Serial.println("160");
    idle();
  }
  else if((164 < angle) && (angle <= 174))//170 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(1090);
    //Serial.println("170");
    idle();
  }
  else if((174 < angle) && (angle <= 184))//180 degree turn
  {
    leftServo.write(CLOCKWISE);
    rightServo.write(CLOCKWISE);
    delay(1150);
    //Serial.println("180");
    idle();
  }
  else
  {
    idle();
  }
  //leftServo.detach();
  //rightServo.detach();
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  servo1.attach(12);
  servo2.attach(13);
  servo3.attach(14);
  servo4.attach(15);
  leftServo.attach(2);
  rightServo.attach(4);
  servo1.detach();
  servo2.detach();
  servo3.detach();
  servo4.detach();

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  //init with high specs to pre-allocate larger buffers
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  //initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);//flip it back
    s->set_brightness(s, 1);//up the blightness just a bit
    s->set_saturation(s, -2);//lower the saturation
  }
  //drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_QVGA);

#if defined(CAMERA_MODEL_M5STACK_WIDE)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

  if (!WiFi.config(espIP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  //leftServo.attach(2);  // attaches the servo on pin 26 to the servo object
  //rightServo.attach(4);
  //leftServo.write(OFF);  //Start with servos off
  //rightServo.write(OFF);

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10000);
}
