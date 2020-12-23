#include "Arduino.h"
#include "AiEsp32RotaryEncoder.h"
// #include "WiFi.h"

#include "WiFiMulti.h"
#include "screen_manager.h"

#define ROTARY_ENCODER_A_PIN 2
#define ROTARY_ENCODER_B_PIN 4
#define ROTARY_ENCODER_BUTTON_PIN 15
// #define ROTARY_ENCODER_VCC_PIN 27
WiFiMulti wifiMulti;
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(
  ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN);


// IPAddress ip;
char ip_char[] = "xxx.xxx.xxx.xxx";
char encoder_value[] = "   ";
IPAddress ip;
String current_ip;
String new_ip;
int test_limits = 2;

void setup()
{
  // initialize LED digital pin as an output.
  Serial.begin(115200);
  // Wifi connection
  wifiMulti.addAP("pcp", "AnggaMiMi");
  wifiMulti.addAP("pcpdef", "AnggaMiMi");
  wifiMulti.addAP("npsk");
  u8g2.begin();

  //we must initialize rorary encoder 
	rotaryEncoder.begin();
	rotaryEncoder.setup([]{rotaryEncoder.readEncoder_ISR();});
	//optionally we can set boundaries and if values should cycle or not
	rotaryEncoder.setBoundaries(0, 10, true); //minValue, maxValue, cycle values (when max go to min and vice versa)
}

void rotary_loop() {
	//first lets handle rotary encoder button click
	if (rotaryEncoder.currentButtonState() == BUT_RELEASED) {
		//we can process it here or call separate function like:
		//rotaryEncoder.reset();
    //rotaryEncoder.disable();
    rotaryEncoder.setBoundaries(-test_limits, test_limits, false);
    test_limits *= 2;
	}

	//lets see if anything changed
	int16_t encoderDelta = rotaryEncoder.encoderChanged();
	
	//optionally we can ignore whenever there is no change
	// if (encoderDelta == 0) return;
	
	//if value is changed compared to our last read
	if (encoderDelta!=0) {
		//now we need current value
		int16_t encoderValue = rotaryEncoder.readEncoder();
		//process new value. Here is simple output.
    String(encoderValue).toCharArray(encoder_value,3);
    u8g2.drawStr(50,30, encoder_value);
		Serial.print("Value: ");
		Serial.println(encoderValue);
	} 
	
}

void ip_changes(){
  if (wifiMulti.run() == WL_CONNECTED){
    ip = WiFi.localIP();
    current_ip = ip.toString();
    if (current_ip.compareTo(new_ip)== 0) { //0 is equal
      return;
    } else {
      new_ip = current_ip;
      new_ip.toCharArray(ip_char, 16);
      Serial.print("ipaddr: ");
      Serial.println(new_ip);
    }
  }
}

void loop()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_mercutio_basic_nbp_tf); //10pxh
  ip_changes();
  u8g2.drawStr(5,16, ip_char);
  u8g2.drawStr(5,30, "value");

  delay(50);	
	if (millis()>20000) rotaryEncoder.enable ();
  rotary_loop();
  u8g2.sendBuffer();
}