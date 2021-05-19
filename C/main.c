#include <main.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numb_inside=4;
int dizaine=0;
int limit = 5;

boolean flag_RB0=0;
boolean flag_RB1=0;
boolean flag_RDA=0;

char buffer[5];

#INT_EXT
void  EXT_isr(void) 
{
   flag_RB0=1;
}

#INT_EXT1
void  EXT1_isr(void) 
{
   flag_RB1=1;
}

#INT_RDA
void  RDA_isr(void) 
{
   buffer[0] = getc();
   flag_RDA=1;
}

void main()
{
int val = 0;

   enable_interrupts(INT_EXT);
   enable_interrupts(INT_EXT1);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   setup_low_volt_detect(FALSE);

   for(;;){

      if(flag_RDA){

         flag_RDA = 0;
         limit = atoi(buffer);
      }
      
       val=numb_inside+dizaine*16;
      output_d(val);
      
      if( limit<val){
         output_e(2);
         delay_ms(250);
         output_e(0);
         delay_ms(250);
      }
      
      if(limit>=val){
         output_e(1);
      }
      
      if (flag_RB0){
         if( numb_inside == 9 ){
            numb_inside=0;
            dizaine++;
         }
         else{
            numb_inside++;
         }
         flag_RB0=0;
      }
      else if(flag_RB1){
         if(numb_inside == 0 && dizaine>0){
            numb_inside=9;
            dizaine--;
         }
         else if(numb_inside == 0 && dizaine==0){
            continue;
         }
         else{
            numb_inside--;
         }
         flag_RB1=0;
      }
   }
}

