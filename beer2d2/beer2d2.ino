#include <Servo.h> 
 
Servo Motor1;
Servo Motor2;
 

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
byte ip[] = { 169, 254, 179, 177 }; // ip in lan
byte gateway[] = { 192, 168, 1, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port

int fwdSpeed = 75;
int bwdSpeed = 105;

String readString; 

//////////////////////

void setup(){

  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  server.begin();
  Motor1.attach(5);
  Motor2.attach(6);


}

void loop(){
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string 
          readString += c; 
          //Serial.print(c);
        } 

        //if HTTP request has ended
        if (c == '\n') {

          ///////////////

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();
          
          client.println("<HTML>");
          client.println("<HEAD>");

          client.println("<TITLE>Robot Control</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");

          client.println("<H1>Robot Control</H1>");
          
          
          client.print("<input type=submit value=Forward style=width:100px;height:100px onmousedown=location.href='/?off8;' onmouseup=location.href='/?off7;' onmouseleave=location.href='/?off7;'>");
          client.print("<input type=submit value=Backward style=width:100px;height:100px onmousedown=location.href='/?off6;' onmouseup=location.href='/?off7;' onmouseleave=location.href='/?off7;'>");
          client.print("<input type=submit value=Left style=width:100px;height:100px onmousedown=location.href='/?off5;' onmouseup=location.href='/?off7;' onmouseleave=location.href='/?off7;'>");
          client.print("<input type=submit value=Right style=width:100px;height:100px onmousedown=location.href='/?off4;' onmouseup=location.href='/?off7;' onmouseleave=location.href='/?off7;'>");
          
          client.println("<script>");
          client.println("function mouseDown() {");
          client.println("    document.getElementById(\"myP\").style.color = \"red\";");
          client.println("location.href= '/?on8;'");
          client.println("}");
          
          client.println("function mouseUp() {");
          client.println("    document.getElementById(\"myP\").style.color = \"green\";");
          client.println("location.href= '/?on7;'");
          client.println("}");
          client.println("</script>");
          
          
          
          
          client.println("</BODY>");
          client.println("</HTML>");

          delay(1);
          //stopping client
          client.stop();
          
          
             /////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////                 Motor Control                       /////////////////////
           //////////////////// Modify i motors are moveing in the wrong direction ///////////////////// 
          /////////////////////////////////////////////////////////////////////////////////////////////
          
          
          
          if(readString.indexOf('4') >0)     // Right 
          {
            Motor1.write(bwdSpeed);
            Motor2.write(fwdSpeed);
          }
           if(readString.indexOf('5') >0)    // Left
          {
            Motor1.write(fwdSpeed);
            Motor2.write(bwdSpeed);
          }
           if(readString.indexOf('6') >0)    // Backward
          {
            Motor1.write(bwdSpeed);
            Motor2.write(bwdSpeed);
          }
           if(readString.indexOf('8') >0)    // Forward
          {
            Motor1.write(fwdSpeed);
            Motor2.write(fwdSpeed);
          }
          
          if(readString.indexOf('7') >0)      // Stop
          {
            Motor1.write(90);
            Motor2.write(90);
          }
             
          //clearing string for next read
          readString="";

        }
      }
    }
  }
} 

