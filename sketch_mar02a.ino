
#include <reg51.h>
#include <stdio.h>

sbit Sound_Play_Pin at P0_3_bit;
 
void Tone1(){
      Sound_Play(659,250);
}

void Tone2(){
   Sound_Play(698,250);
   }
 
void Tone3(){
   Sound_Play(784,250);
   }
  
 void Melody(){
    Tone1(); Tone2(); Tone3();Tone3();
     Tone1(); Tone2(); Tone3();Tone3();
     Tone1(); Tone2(); Tone3();
     Tone1(); Tone2(); Tone3();Tone3();
     Tone1(); Tone2(); Tone3();
     Tone3(); Tone3(); Tone2();Tone2();Tone1();
    }
    
void ToneA(){
   Sound_Play(880,50);
   }
   void ToneC(){
   Sound_Play(1046,50);
   }
   void ToneE(){
   Sound_Play(1318,50);
   }
   void Melody2(){
   unsigned short i;
      for(i=9;i>0;i--){
   ToneA();ToneC();ToneE();
   }
   }
   
 void main(){
    P1=255;
    Sound_Init();
    Sound_Play(2000,1000);
    while(1){
       if(!(P1_7_bit))
    Tone1();
   while(!(P1_7_bit));
      if(!(P1_6_bit))
         Tone2();
      while(!(P1_6_bit));
      if(!(P1_5_bit))
         Tone3();
      while(!(P1_5_bit));
      if(!(P1_4_bit))
         Melody2();
      while(!(P1_4_bit));
      if(!(P1_3_bit))
         Melody();
      while(!(P1_3_bit));
       }
    }

