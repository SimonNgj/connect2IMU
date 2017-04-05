import processing.opengl.*;
import processing.serial.*;

//float[] q = {0,0,0,0};

float roll_d = 0;
float pitch_d = 0;
float yaw_d = 0;

float rate = 57.2957795131;
float roll  = roll_d/rate;
float pitch = pitch_d/rate;
float yaw = yaw_d/rate;

String val;
  
void setup() {
  size(400, 460, P3D);
  println(Serial.list());
  new Serial(this, "COM3",  9600); 
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
void draw_rotocube() {
  //reference frames:
  // * 0e,Xe,Ye,Ze  =  inertial frame - Earth Centered Inertial (ECI)
  // * 0s,Xs,Ys,Zs  =  sensor frame - the sensor board frame
  // * 0d,Xd,Yd,Zd  =  display frame - the display system reference frame ("processing")
  //  Sq = [q0, q1, q2, q3]
  //sensor quaternion can be translated to aerospace sequence of yaw/pitch/roll angles
  //  yaw = atan2(2*q1*q2 - 2*q0*q3, 2*(q0^2) + 2*(q1^2) - 1)
  //  pitch = -asin(2*q1*q3 + 2*q0*q2)
  //  roll = atan2(2*q2*q3 - 2*q0*q1, 2*(q0^2) + 2*(q3^2) - 1)

  
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

void draw_pitchrollyaw() {
  //roll circle
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
  text("pitch: " + nf(pitch_d,1,5), 0, 20);
  
  translate(25, -25);
  strokeWeight(2);
  rotateZ(pitch);
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
  
void serialEvent(Serial myPort) {  
   val = myPort.readStringUntil('\n');
   if (val != null) {
    int[] angle = int(splitTokens(val, " "));
    roll = angle[0]/rate;
    pitch = angle[1]/rate;
    roll_d = angle[0];
    pitch_d = angle[1];
  }
    redraw();
}


