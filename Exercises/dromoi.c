#include <stdio.h>
#include <stdlib.h>

int main(int argc , char *argv[]) {

FILE *fp;
int flag=1; 
int c;
unsigned long meres=0; //Deixnei se poia mera twn ergasiwn eimaste
unsigned long i=0,j=0;
char ct[10] = {'\0'};  //To symbolo '\0' ypodhlwnei to telos toy string 
unsigned long NLX[3];  //1o stoixeio einai to N , 2o to L , 3o to X
unsigned long start;  //Xrhsimopoieitai san counter gia thn episkeyh toy dromoy
unsigned long acum , max; //O acum xrhsimopoieitai san a8roisths gia ton ypologismo toy mhkoys twn kommatiwn twn dromwn
                          //to max einai to mhkos toy megistoy kommatioy dromoy

fp=fopen(argv[1] ,"r"); //Anoigma arxeioy gia anagnwsh

while((c = getc(fp)) != '\n') {      //Diabasma prwths grammhs toy arxeioy
  if(c != ' ')
    ct[i++]=c;
  else {
    NLX[j++]=strtoul(ct,(char **)NULL,10);  //Synarthsh metatrophs typoy poy brisketai sto stdlib
    while(i > 0)
      ct[i--]='\0';
  }    
}
NLX[j++]=strtoul(ct,(char **)NULL,10);  //Ton teleytaio ari8mo ths prwths grammhs ton metatrepoyme xeirokinhta
while(i > 0)                            //dioti den 8a bei sto while otan synadhsei to symbolo teloys grammhs '\n'
  ct[i--]='\0';

unsigned long SE[2]; //Pinakas poy periexei thn arxh-telos toy kommatioy poy prepei na episkeyastei
unsigned long L[NLX[1]]; //Pinakas poy adiprosopeyei to synoliko mhkos toy dromoy
unsigned long MaxBegin=0,MaxEnd=NLX[1]; //Xrhsimopoioydai gia thn arxh-telos toy megalyteroy mh episkeyasmenoy kommatioy toy dromoy  

for(i=0; i < NLX[1]; i++)  //To 0 poy bazoyme adiprosopeyei oti se ekeino to shmeio den exei ginei episkeyh
  L[i]=0;
                            
i=j=0;
while(((c = getc(fp)) != EOF) && flag) {
  if((c != ' ') && (c != '\n'))
    ct[i++]=c; 
  else {
    SE[j++]=strtoul(ct,(char **)NULL,10);
    while(i > 0)
      ct[i--]='\0';
    if(c=='\n') {
      meres=meres+1;
      start=SE[0];
      while(start < SE[1])   
        if(L[start]==0)   //An o dromos den exei episkeyastei bazoyme thn timh toy teloys ths episkeyhs(dhladh to E)
         L[start++]=SE[1]; //etsi wste an synadisoyme mia episkeyhs na phdame apey8eias sto telos ths 
        else
         start=L[start];  //Edw phdame sto telos ths episkeyhs xwris na diatrexoyme tmhmata toy dromoy poy exoyn episkeyastei
      

      if((SE[0]<=MaxBegin && SE[1]>MaxBegin) || (SE[0]>=MaxBegin && SE[1]<=MaxEnd) //Me thn syn8hkh ayth blepoyme an to tmhma
         || (SE[0]<MaxEnd && SE[1]>=MaxEnd )) {                                   //toy dromoy poy episkeyasthke parembaletai
        j=start=acum=max=0;                                                       //me to megalytero anepiskeyasto tmhma dromoy
        while(j < NLX[1]) {
          if(L[j]==0) {
           acum++;
           j++;
          }
          else {
           if(acum > max) {
            max = acum;
            MaxBegin = start;
            MaxEnd = j;
           }
          acum=0;
          j=L[j];
          start=j;
         }
        }
        if(acum > max) {  //To kanoyme xeirokinhta dioti gia j==NLX[1] den 8a bei sto while kai to teyleytaio acum den 8a sygri8ei
          max = acum;     
          MaxBegin = start;
          MaxEnd = j;
        }
        if(max <= NLX[2]) //Syn8hkh prowroy termatismoy
         flag=0;
      }
      
      j=0; //Ayto einai aparaithto wste h entolh sthn grammh 44 na leitoyrgei swsta

    }
  }
} 

if(flag)
 printf("-1\n");
else
 printf("%ld\n",meres);

fclose(fp); //Kleisimo arxeioy
return 0;
}
