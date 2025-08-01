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

int Sped;
int Current_Sped;

void speed_control(int Sped);
void forw(int Sped);
void back(int Sped);
void left(int Sped);
void right(int Sped);
void stop();

// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

void setup () {

  pinMode(Fo,INPUT);
  pinMode(Ba,INPUT);
  pinMode(Le,INPUT);
  pinMode(Ri,INPUT);
  pinMode(St,INPUT);

    // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
}

void loop () {

     Fvar = analogRead(Fo);
     Bvar = analogRead(Ba);
     Lvar = analogRead(Le);
     Rvar = analogRead(Ri);
     Svar = analogRead(St);

     if (Fvar > 256){

     	forw(128);
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
	speed_control(Sped);

	digitalWrite(in1, HIGH);//motor pair 1 forward
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);//motor pair 2 forward
	digitalWrite(in4, LOW);
}
void back(int Sped)
{
	speed_control(Sped);
	
	digitalWrite(in1, LOW);//motor pair 1 backward
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);//motor pair 2 backward
	digitalWrite(in4, HIGH);
}
void left(int Sped)
{
	speed_control(Sped);
	digitalWrite(in1, HIGH);//motor pair 1 forward
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);//motor pair 2 backward
	digitalWrite(in4, HIGH);
}
void right(int Sped)
{
	speed_control(Sped);

	digitalWrite(in1, LOW);//motor pair 1 backward
	digitalWrite(in2, HIGH);
	digitalWrite(in3, HIGH);//motor pair 2 forward
	digitalWrite(in4, LOW);
}
void stop()
{
	speed_control(Sped);

	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

void speed_control(int Sped)
{
	if (Sped > Current_Sped)
	{
		for (int i = Current_Sped; i < Sped; i++) {
	       	    analogWrite(enA, i);
	       	    analogWrite(enB, i);
	       	    delay(20);
		    }
		    
		Current_Sped = Sped
	 }
	else
	{
		for (int i = Current_Sped; i > Sped; i--) {
	       	    analogWrite(enA, i);
	       	    analogWrite(enB, i);
	       	    delay(20);
  	 	    }
		    
		Current_Sped = Sped
	}
}
