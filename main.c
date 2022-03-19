#include<AT89S52.h>
#include<string.h>

xdata at 0x4000 unsigned char lcd0;
xdata at 0x5000 unsigned char lcd;
xdata at 0xc000 unsigned char pa;
xdata at 0xc100 unsigned char pb;
xdata at 0xc200 unsigned char pc;
xdata at 0xc300 unsigned char cw;
//-----------------------------------
xdata at 0x0000 unsigned char c;
xdata at 0x0100 unsigned char phone1[11];  
xdata at 0x0200 unsigned char phone2[11];
xdata at 0x0300 unsigned char phone3[11];
xdata at 0x0400 unsigned char phone4[11];
xdata at 0x0500 unsigned char phone5[11];
xdata at 0x0600 unsigned char phone6[11];
xdata at 0x0700 unsigned char phone7[11];
//------------------------------------
sfr at 0x90 key1;
//------------------
#define on_off   P3_4  //0=close 1=opne
#define as       P3_5

#define zmbora P1_4
#define led    P1_7 // on=0 off=1
#define mimsar    P1_5 // mimsar
//#define adc      P1_ 6
//------------------
unsigned char key;
bit zz=0,xxx=0,xyz=0, z=0,ma=0;
int cm=0;

//------------------

void send_byte(unsigned char Data);
void sendAndwrite(unsigned char *Data) ;
void send_sms(void);
void delay(int i);
void lcd_p(char p[],char i);
void lcd_phone(void);
void lcd_mhrozt (char x[]);    
void lcd_o(void);
void key_int(void) interrupt 0 using  0;
void s_phone(void);
void scanf_p(char m[],char i);
char key_t(char x);
void menu(void);
void san(void);
void register_o(void);
void int1(void) interrupt 2;
void sansor(int k);
void fzmbora(int i);
//--- union  struct---------------//
struct sansor 
{unsigned char a;
unsigned char b;
unsigned char c;};
struct sansor s;
//--------------------------------------//
void main() 
{
 
  bit zx=0;
  register_o();
  cw=0x9b;
  lcd_o();
  
zmbora=0;


 while(1)
 { 
        /*             led=1;
        
       mimsar=1;
       lcd_o();
       lcd_mhrozt("For    Menu "); delay(20);  lcd0=0xc0;  delay(20);
       lcd_mhrozt("puse    *   ");   delay(100);
       if(z==1)
       {z=0;
        menu(); }
  */
  
  while(as==1)
    {led=0; delay (300);
     }
     while(as==0)
      {led=1; delay (300);
     }
   
} }

//-----------FUNCTIONS--------//
void san(void)
 { int i, r=0;
   
   for(i=0;i<=3;i++)
  {delay(100); 
   if(((pa<(s.a-1))||(pa>(s.a+1)))||((pb<(s.b-1))||(pb>(s.b+1)))||((pc<(s.c-1))||(pc>(s.c+1))))
    r++;
     } 
   if(r>2)
    xyz=1;
 }
//-----------------------
void key_int(void) interrupt 0 
{delay(20);
 key=key1;
 key=key&0x0f; 
 key=key_t(key); delay(20);
 zz=1;
 if(key=='*')
  z=1;            
 if(key=='#')
  z=z; 
  delay(100);}
//--------------
void int1(void) interrupt 2
{// xxx=1;
     while(P3_3==0)
     {}}
//--------------
void lcd_mhrozt (char x[]) 
{int i=0; 
  while (x[i]!=0)
  {delay(15);
   lcd=x[i];
   i++;}}
//------------------//
void delay(int i)
{int j,j1;
  for(j=0;j<=i;j++)
  for(j1=0;j1<=i;j1++);}
//----------------//
void lcd_o (void)
{lcd0=0x38;delay(25);
 lcd0=0x0f;delay(25);
 lcd0=0x01;delay(25);
 lcd0=0x80;delay(25);}
//----------------//
void register_o(void)
{IE=0x95;   delay(20);
 TCON=0x03; delay(20);
 IP=0x05;   delay(20);
 SCON=0x50; delay(20);
 TMOD=0x20; delay(20);
 TH1=0xFD; delay(20);}
//----------START MENU-------------//
void menu(void)
{ int j;
ma=1;
zzz : lcd0=0x01; 
      zz=0;j=0; 
      lcd_mhrozt("For Setup:A"); 
      lcd0=0xc0; 
      lcd_mhrozt("For ARMS:B"); 

        
       while(zz==0){} 
       zz=0; 
       if(key=='A') 
       {lcd_o ();
        lcd_mhrozt("Select:");
        lcd0=0xc0;  delay(20);
        lcd_mhrozt("1. Phone Number"); delay(300);
        lcd0=0x01; delay(20);
        lcd_mhrozt("2. Current phone");
        lcd0=0xc0; delay(20);
        lcd_mhrozt("3. Test sms ");  delay(300);
        lcd0=0x01; delay(20);
        lcd_mhrozt("4. Test sansor");
        lcd0=0xc0; delay(20);
        lcd_mhrozt("5. Exit");        
          while(zz==0){}
          zz=0;
         lcd0=0x01; delay(20);
          if(key=='1')
          {delay(20);
 ssa :     lcd_o ();
           lcd_mhrozt("How many phone");
           lcd0=0xc0;
           lcd_mhrozt("numbers? (1-7)");
           j=0;  zz=0;
    
             while(zz==0){}
             zz=0;
            s_phone();
            lcd_o();  
            lcd_mhrozt("To Ok : 1");   
            lcd0=0xc0;
            lcd_mhrozt("To Change : 2");
            delay(100);
            zz=0; 
            while(zz==0){}
            if(key=='2')
            goto ssa;
            if(key=='1')
            goto zzz; 
          }
          
          if(key=='2')
          {lcd0=0x01;  delay(25);
           lcd_phone(); delay(400);
           goto zzz;}
          if(key=='3')          
          send_sms();
        //  if(key=='4')
          while(key=='4')
          {lcd0=0x01;  delay(50);
           sansor(pa); delay(50);
           sansor(pb); delay(70);
           sansor(pc); delay(90); }
          //  if(key=='5')
           goto zzz;}
   
    if(key=='B')
    { lcd_o (); lcd_mhrozt("   PENTAGON"); delay(300); }   
    else
    {lcd_o (); lcd_mhrozt("     ERROR"); delay(300); goto zzz;}
    ma=0;
    } 
//-------------------- 
void lcd_phone(void)
{char i;
 switch(c)
{case '1': lcd_p(phone1,i='1'); break;
 case '2': lcd_p(phone1,i='1'); lcd_p(phone2,i='2'); break;
 case '3': lcd_p(phone1,i='1'); lcd_p(phone2,i='2'); lcd_p(phone3,i='3'); break;
 case '4': lcd_p(phone1,i='1'); lcd_p(phone2,i='2'); lcd_p(phone3,i='3'); lcd_p(phone4,i='4'); break;
 case '5': lcd_p(phone1,i='1'); lcd_p(phone2,i='2'); lcd_p(phone3,i='3'); lcd_p(phone4,i='4'); lcd_p(phone5,i='5'); break;
 case '6': lcd_p(phone1,i='1'); lcd_p(phone2,i='2'); lcd_p(phone3,i='3'); lcd_p(phone4,i='4'); lcd_p(phone5,i='5'); lcd_p(phone6,i='6'); break;
 case '7': lcd_p(phone1,i='1'); lcd_p(phone2,i='2'); lcd_p(phone3,i='3'); lcd_p(phone4,i='4'); lcd_p(phone5,i='5'); lcd_p(phone6,i='6'); lcd_p(phone7,i='7'); break;
 }}
//--------------------
void lcd_p(char p[],char i)
{lcd0=0x01; delay(20);
 lcd_mhrozt("Phone "); delay(20);
 lcd=i;     delay(20);
 lcd=':';   delay(20);
 lcd_mhrozt(" NextP #"); delay(20);
 lcd0=0xc0; delay(20);
 lcd_mhrozt(p);
 
 zz=0; 
mm: while(zz==0){}
 if(key!='#')
 goto mm; } 
//---------------------
void s_phone(void)
{char i;
 c=key;
 switch(c){
 case '1': scanf_p(phone1,i='1'); cm=1; break;
 case '2': scanf_p(phone1,i='1'); scanf_p(phone2,i='2'); cm=2; break;
 case '3': scanf_p(phone1,i='1'); scanf_p(phone2,i='2'); scanf_p(phone3,i='3');cm=3; break;
 case '4': scanf_p(phone1,i='1'); scanf_p(phone2,i='2'); scanf_p(phone3,i='3'); scanf_p(phone4,i='4');cm=4; break;
 case '5': scanf_p(phone1,i='1'); scanf_p(phone2,i='2'); scanf_p(phone3,i='3'); scanf_p(phone4,i='4'); scanf_p(phone5,i='5'); cm=5; break;
 case '6': scanf_p(phone1,i='1'); scanf_p(phone2,i='2'); scanf_p(phone3,i='3'); scanf_p(phone4,i='4'); scanf_p(phone5,i='5'); scanf_p(phone6,i='6'); cm=6; break;
 case '7': scanf_p(phone1,i='1'); scanf_p(phone2,i='2'); scanf_p(phone3,i='3'); scanf_p(phone4,i='4'); scanf_p(phone5,i='5'); scanf_p(phone6,i='6'); scanf_p(phone7,i='7'); cm=7; break;
 } delay(200); lcd_phone();}
//----------------------
void scanf_p(char m[],char i)
{ int j=0,c=0;
  delay(20); lcd_o (); 
  lcd_mhrozt("Enter Phon");
  lcd=i; delay(20); lcd=':'; delay(20); lcd_mhrozt("Ddel");
  j=0; zz=0; delay(20);
  lcd0=0xc0;  delay(20);
  while(zz==0){}
  while((key!='#')&&(key!='D')&&(key!='C'))
 {delay(20);
  m[j]=key;
  lcd=key;
  j++; zz=0; 
zx : while(zz==0){}  }
  if(key=='D')
  {j--; c++; delay(20); lcd0=0x10; delay(20); zz=0; goto zx;}
  if(key=='C')
  {j++; c--; delay(20); lcd0=0x14; delay(20); zz=0; goto zx;}
   m[j+c]=NULL; delay(20); }
//-----------
char key_t(char x)
{switch(x)
{case 0x00: x='1'; break;
 case 0x01: x='2'; break;
 case 0x02: x='3'; break;
 case 0x04: x='4'; break;
 case 0x05: x='5'; break;
 case 0x06: x='6'; break;
 case 0x08: x='7'; break;
 case 0x09: x='8'; break;
 case 0x0a: x='9'; break;
 case 0x0d: x='0'; break;
 case 0x0e: x='#'; break;
 case 0x0c: x='*'; break;
 case 0x03: x='A'; break;
 case 0x07: x='B'; break;
 case 0x0b: x='C'; break;
 case 0x0f: x='D'; break;}
return(x);}
//-----------------------------
void send_byte(unsigned char Data)
{TI=0; 
 SBUF=Data;
 while(TI==0)
 {}}
void sendAndwrite(unsigned char *Data)
 {
 while(*Data!='\0'){
 send_byte(*Data);  
 Data++;  
 delay(15);}}
		
void send_sms(void)
 { 
 char pp[11]; int ii,xz=0; 
 
 for(ii=1;ii<=cm;ii++)
 {
 xz=0;
 if(ii==1){while(phone1[xz]!=NULL) {pp[xz]=phone1[xz]; xz++; }}
 if(ii==2){while(phone2[xz]!=NULL) {pp[xz]=phone2[xz]; xz++; }}
 if(ii==3){while(phone3[xz]!=NULL) {pp[xz]=phone3[xz]; xz++; }}
 if(ii==4){while(phone4[xz]!=NULL) {pp[xz]=phone4[xz]; xz++; }}
 if(ii==5){while(phone5[xz]!=NULL) {pp[xz]=phone5[xz]; xz++; }}
 if(ii==6){while(phone6[xz]!=NULL) {pp[xz]=phone6[xz]; xz++; }}
 if(ii==7){while(phone7[xz]!=NULL) {pp[xz]=phone7[xz]; xz++; }}
  
 TR1=1;   TI=0;
 sendAndwrite("ATZ");	
 send_byte(0x0D);
 sendAndwrite("AT");			
 send_byte(0x0D);
 sendAndwrite("at+cmgf=1");
 send_byte(0x0D);     
 sendAndwrite("at+cmgs= "); delay(30);
 sendAndwrite(pp);    
 send_byte(0x0D);
 if(xxx==1) sendAndwrite(" Broke Window ");
 else if(xyz==1) sendAndwrite(" gorrim at ahoto "); 
 else if((on_off==0)&&(ma==0))sendAndwrite(" Door The Car ");   
 else if(ma==1) sendAndwrite(" SMS Test ");   
 send_byte(0x1A);
 send_byte(0x0D);  
 delay(50);
 TR1=0;
 delay(1000);
}}
void sansor(int k)
{int a,b,c;
a=k/100;
k=k%100;
b=k/10;
c=k%10;
lcd=a+'0'; delay(10);
lcd=b+'0'; delay(10);
lcd=c+'0'; delay(10); 
lcd=' ';
}

void fzmbora(int i)
{
int j;
for(j=0;j<=i;j++)
{zmbora=1;
delay(70);
zmbora=0;
delay(70);
}
}
