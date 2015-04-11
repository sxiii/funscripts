#include <SPI.h>
#include <Ethernet.h> // Initialize the libraries.
///////////
#include "pitches.h"
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };
////////////
byte mac[] = { 0x00, 0x05, 0xB5, 0x00, 0x05, 0xB5 }; //I left the MAC address and IP address blank.
byte ip[] = { 192, 168, 1, 200 }; // You will want to fill these in with your MAC and IP address.
EthernetServer server(80); // Assigning the port forwarded number. It's almost always 80.
String readString; // We will be using strings to keep track of things.
int val; // Using val as a variable for the PIR status.
void setup() {
  pinMode(2, INPUT);
  Ethernet.begin(mac, ip);
}
void(* resetFunc) (void) = 0; //declare reset function @ address 0
void loop() {
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (readString.length() < 100) {
          readString += c;
        }
        if (c == '\n') {
          // init
            Serial.println(readString); // And here we begin including the HTML
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<!DOCTYPE html>");
          client.println("<html lang='en'>");
          client.println("<head><meta charset='UTF-8'><title>OpenDoor</title></head>");
          client.println("<style>body{text-align:center;background-color:#2980b9;}h1{font-size:2.2em;color:#fff;}input{ background:#2c3e50;height:75px;width:75px; border-radius:100%; font-size:2em;border:0px solid #000;margin:5px;color:#fff;}</style>");
          client.println("<body>");
          client.println("<h1>Aloha</h1>");
          client.println("<FORM method='GET'>");
          client.println("<INPUT type=button value=1 onClick=window.location+=1>");
          client.println("<INPUT type=button value=2 onClick=window.location+=2>");
          client.println("<INPUT type=button value=3 onClick=window.location+=3>");
          client.println("<br>");
          client.println("<INPUT type=button value=4 onClick=window.location+=4>");
          client.println("<INPUT type=button value=5 onClick=window.location+=5>");
          client.println("<INPUT type=button value=6 onClick=window.location+=6>");
          client.println("<br>");
          client.println("<INPUT type=button value=7 onClick=window.location+=7>");
          client.println("<INPUT type=button value=8 onClick=window.location+=8>");
          client.println("<INPUT type=button value=9 onClick=window.location+=9>");
          client.println("</FORM>"); // Above and below you'll see that when we click on a button, it adds a little snippet
          client.println("</body>");
          client.println("</html>");
          if (readString.indexOf("3214 ") > 0  )
          {
            pinMode(2, OUTPUT);
            client.println("<script>console.log('on');</script>");
            for (int thisNote = 0; thisNote < 8; thisNote++) {
              int noteDuration = 1000/noteDurations[thisNote];
              tone(8, melody[thisNote],noteDuration);
              int pauseBetweenNotes = noteDuration * 1.30;
              delay(pauseBetweenNotes);
              noTone(8);
            }
            delay(2000);
            client.println("<script>console.log('off');</script>");
            pinMode(2, INPUT);
            delay(8000);
             for (int thisNote = 0; thisNote < 8; thisNote++) {
              int noteDuration = 1000/noteDurations[thisNote];
              tone(8, melody[thisNote],noteDuration);
              int pauseBetweenNotes = noteDuration * 1.30;
              delay(pauseBetweenNotes);
              noTone(8);
            }
            resetFunc();
          }
          else {
            client.println("<script>console.log('false');</script>");
          }
          readString = "";
          client.stop();
        }
      }
    }
  }

}
