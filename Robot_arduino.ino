int R_F = 2;
int R_B = 3;
int L_F = 4;
int L_B = 5;

int F = A0;
int B = A1;
int L = A2;
int R = A3;
int S = A4;

int Fvar;
int Bvar;
int Lvar;
int Rvar;
int Svar;

void forw();
void back();
void left();
void right();
void stop();

void setup () {

  pinMode(R_F,OUTPUT);
  pinMode(R_B,OUTPUT);
  pinMode(L_F,OUTPUT);
  pinMode(L_B,OUTPUT);

  pinMode(F,INPUT);
  pinMode(B,INPUT);
  pinMode(L,INPUT);
  pinMode(R,INPUT);
  pinMode(S,INPUT);
  
}

void loop () {

     Fvar = analogRead(F);
     Bvar = analogRead(B);
     Lvar = analogRead(L);
     Rvar = analogRead(R);
     Svar = analogRead(S);

     if (Fvar > 256){
     	forw();
}
     if (Bvar > 256){
     	back();
}
     if (Lvar > 256){
     	left();
}
     if (Rvar > 256){
     	right();
}
     if (Svar > 256){
     	stop();
}
}

void forw() 
{
  digitalWrite(R_F,HIGH);
  digitalWrite(R_B,LOW);
  digitalWrite(L_F,HIGH);
  digitalWrite(L_B,LOW);
}
void back()
{
  digitalWrite(R_F,LOW);
  digitalWrite(R_B,HIGH);
  digitalWrite(L_F,LOW);
  digitalWrite(L_B,HIGH);
}
void left()
{
  digitalWrite(R_F,LOW);
  digitalWrite(R_B,HIGH);
  digitalWrite(L_F,HIGH);
  digitalWrite(L_B,LOW);
}
void right()
{
  digitalWrite(R_F,HIGH);
  digitalWrite(R_B,LOW);
  digitalWrite(L_F,LOW);
  digitalWrite(L_B,HIGH);
}
void stop()
{
  digitalWrite(R_F,LOW);
  digitalWrite(R_B,LOW);
  digitalWrite(L_F,LOW);
  digitalWrite(L_B,LOW);
}
