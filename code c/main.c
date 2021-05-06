#include <main.h>

int numb_inside=9;
int dizaine=0;
int limit = 5;

boolean flag_RB0=0;
boolean flag_RB1=0;
boolean flag_RDA=0;

int buffer[2];

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
   buffer[0]=getc();
   flag_RDA=1;
}

void main()
{

   enable_interrupts(INT_EXT);
   enable_interrupts(INT_EXT1);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   setup_low_volt_detect(FALSE);

   while(TRUE){

      if(flag_RDA){

         output_e(1);
      }
      
      int val=numb_inside+dizaine*16;
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
