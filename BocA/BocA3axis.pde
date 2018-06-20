import processing.opengl.*;
import processing.serial.*;

float roll_d = 0;
float pitch_d = 0;
float yaw_d = 0;

float rate = 57.2957795131;
float roll  = roll_d/rate;
float pitch = pitch_d/rate;
float yaw = yaw_d/rate;
  
void setup() {
  size(400, 460, P3D);
  println(Serial.list());
  new Serial(this, "COM23",  9600); 
}

void draw() {
  background(#000000);
  fill(#ffffff);
  
  float transX = 0;
  float transY = 0;

  //draw rotating cube
  transX = width/2;
  transY = height/2;
  translate(transX, transY);
  pushMatrix();
  draw_rotocube();
  popMatrix();
  translate(-transX, -transY);
  
  //draw pitch, roll and yaw
  transX = 55;
  transY = 420;
  translate(transX, transY);
  pushMatrix();
  draw_pitchrollyaw();
  popMatrix();
  translate(-transX, -transY);
}
void draw_rotocube() 
{
  rotateZ(-roll);
  rotateX(-pitch); 
  rotateY(-yaw);
      
  //axis
  strokeWeight(2);
  stroke(255, 0, 0);
  line(-120, 0, 0, 120, 0, 0);
  translate(+120, 0, 0);
  box(10,10,10);      //Roll
  translate(-120, 0, 0);
  stroke(0, 0, 255);
  line(0, -120, 0, 0, 120, 0);
  translate(0, -120, 0);
  box(10,10,10);      //Pitch
  translate(0, +120, 0);
  stroke(0, 255, 0);
  line(0, 0, -120, 0, 0, 120);
  translate(0, 0, +120);
  box(10,10,10);     //Yaw
  translate(0, 0, -120);
  
  //box
  strokeWeight(2);
  stroke(#d99999);        // Cubic color
  fill(#099999, 300);     // Duong diem
  box(150,20,90);         // Box - Dimension
}

void draw_pitchrollyaw() 
{
  //roll circle
  pushMatrix();
  strokeWeight(2);
  stroke(#009999);
  fill(#009999, 220);
  ellipse(25, -25, 50, 50);
  
  fill(255);
  text("pitch: " + nf(pitch_d,1,5), 0, 20);
   
  translate(25, -25);
  strokeWeight(2);
  rotateZ(pitch);
  stroke(0, 255, 0);
  line(-25, 0, 0, 25, 0, 0);
  popMatrix();
  
  translate(120, 0);
  //pitch circle
  pushMatrix();
  strokeWeight(2);
  stroke(#009999);
  fill(#009999, 220);
  ellipse(25, -25, 50, 50);

  fill(255);
  text("roll: " + nf(roll_d,1,5), 0, 20);
  
  translate(25, -25);
  strokeWeight(2);
  rotateZ(roll);
  stroke(255, 0, 0);
  line(-25, 0, 0, 25, 0, 0);
  popMatrix();
  
  translate(120, 0);
  //yaw circle
  pushMatrix();
  strokeWeight(2);
  stroke(#009999);
  fill(#009999, 220);
  ellipse(25, -25, 50, 50);
  
  fill(255);
  text("yaw: " + nf(yaw_d,1,5), 0, 20);
  
  translate(25, -25);
  strokeWeight(2);
  rotateZ(yaw);
  stroke(0, 0, 255);
  line(-25, 0, 0, 25, 0, 0);
  popMatrix();
}
  
void serialEvent(Serial myPort) 
{  
   String val = myPort.readStringUntil('\n');
   //String val = "-7,-39,-43";
   if (val != null) 
   {
    //int[] angle = int(split(val, ','));
    String[] angle = split(val, ',');
    
    pitch_d = int(angle[0]);
    roll_d = int(angle[1]);
    yaw_d = int(angle[2]);
    
    pitch = pitch_d/rate;
    roll = roll_d/rate;
    yaw = yaw_d/rate;
            
    /*print(angle[0]); print(", ");
    print(angle[1]); print(", ");
    print(angle[2]); print("\n");
    print(val);*/
  }
    redraw();
}


