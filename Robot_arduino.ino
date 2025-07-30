int R_F = 2;
int R_B = 3;
int L_F = 4;
int L_B = 5;

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

     Fvar = analogRead(Fo);
     Bvar = analogRead(Ba);
     Lvar = analogRead(Le);
     Rvar = analogRead(Ri);
     Svar = analogRead(St);

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
