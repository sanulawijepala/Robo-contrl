#include <AFMotor.h>

AF_DCMotor R_F(4);
AF_DCMotor R_B(3);
AF_DCMotor L_F(2);
AF_DCMotor L_B(1);

int Fo = A0;
int Ba = A1;
int Le = A2;
int Ri = A3;
int St = A4;

int Fvar;
int Bvar;
int Lvar;
int Rvar;
int Svar;

void forw(int Sped);
void back(int Sped);
void left(int Sped);
void right(int Sped);
void stop(int Sped);

void setup () {

  pinMode(Fo,INPUT);
  pinMode(Ba,INPUT);
  pinMode(Le,INPUT);
  pinMode(Ri,INPUT);
  pinMode(St,INPUT);
  
}

void loop () {

     Fvar = analogRead(Fo);
     Bvar = analogRead(Ba);
     Lvar = analogRead(Le);
     Rvar = analogRead(Ri);
     Svar = analogRead(St);

     if (Fvar > 256){

     	forw(64);
}
     if (Bvar > 256){

     	back(64);
}
     if (Lvar > 256){

     	left(16);
}
     if (Rvar > 256){

     	right(16);
}
     if (Svar > 256){
     	stop();
}
}

void forw(int Sped) 
{
	R_F.run(FORWARD);
	R_B.run(FORWARD);
	L_F.run(FORWARD);
	L_B.run(FORWARD);

	R_F.setSpeed(Sped);
	R_B.setSpeed(Sped);
	L_F.setSpeed(Sped);
	L_B.setSpeed(Sped);
	
}
void back(int Sped)
{
	R_F.run(BACKWARD);
	R_B.run(BACKWARD);
	L_F.run(BACKWARD);
	L_B.run(BACKWARD);

	R_F.setSpeed(Sped);
	R_B.setSpeed(Sped);
	L_F.setSpeed(Sped);
	L_B.setSpeed(Sped);
}
void left(int Sped)
{
	R_F.run(FORWARD);
	R_B.run(FORWARD);
	L_F.run(BACKWARD);
	L_B.run(BACKWARD);

	R_F.setSpeed(Sped);
	R_B.setSpeed(Sped);
	L_F.setSpeed(Sped);
	L_B.setSpeed(Sped);
}
void right(int Sped)
{
	R_F.run(BACKWARD);
	R_B.run(BACKWARD);
	L_F.run(FORWARD);
	L_B.run(FORWARD);

	R_F.setSpeed(Sped);
	R_B.setSpeed(Sped);
	L_F.setSpeed(Sped);
	L_B.setSpeed(Sped);
}
void stop()
{
	R_F.run(RELEASE);
	R_B.run(RELEASE);
	L_F.run(RELEASE);
	L_B.run(RELEASE);

	R_F.setSpeed(Sped);
	R_B.setSpeed(Sped);
	L_F.setSpeed(Sped);
	L_B.setSpeed(Sped);
}
