#include<stdio.h>
#include<stdlib.h>

typedef unsigned long long superint;

/* Ta3inomhsh kata ay3oysa seira */

void shellsortm(int M[],int n) {
  
  int gap,i,j,temp;
  
  for(gap=n/2;gap>0;gap/=2)
    for(i=gap;i<n;i++)   
      for(j=i-gap;j>=0 && M[j]>M[j+gap];j-=gap) {
        temp = M[j];                 
        M[j] = M[j+gap];               
        M[j+gap] = temp;                
                                                }         
                               }

/* Ta3inomhsh kata f8inoysa seira */
                               
void shellsortM(int M[],int n) {
  
  int gap,i,j,temp;
  
  for(gap=n/2;gap>0;gap/=2)
    for(i=gap;i<n;i++)   
      for(j=i-gap;j>=0 && M[j]<M[j+gap];j-=gap) {
        temp = M[j];                 
        M[j] = M[j+gap];               
        M[j+gap] = temp;                
                                                }         
                               }

/* Metatroph se systhma ari8mhshs opoiasdhpote bashs */

void BaseTransform(int Base,superint nbrTotrfm,int nbrDigit,int Array[],int ArrayM[],int Arraym[]){
  
  for(nbrDigit=nbrDigit-1;(nbrDigit>=0)&&(nbrTotrfm!=0);nbrDigit=nbrDigit-1){
    Array[nbrDigit]=nbrTotrfm%Base;
    ArrayM[nbrDigit]=nbrTotrfm%Base;
    Arraym[nbrDigit]=nbrTotrfm%Base;                                                                                
    nbrTotrfm=nbrTotrfm/Base;                                                                                                                                                                
                                                                            }     
  for(nbrDigit=nbrDigit;nbrDigit>=0;nbrDigit=nbrDigit-1) {   
    Array[nbrDigit]=0;
    ArrayM[nbrDigit]=0;
    Arraym[nbrDigit]=0;
                                                         }
                                                                                                  }
                                                                        
/* Metatroph se dekadiko systhma ari8mhshs */

superint DecimalTransform(int Base,int nbrDigit,int Array[]) {

  superint DecTrfm=0;
  superint Power=1;          
     
  for(nbrDigit=nbrDigit-1;nbrDigit>=0;nbrDigit=nbrDigit-1){
    DecTrfm=DecTrfm+Array[nbrDigit]*Power;                                                       
    Power=Power*Base;                                                                                                                     
                                                          }
  return(DecTrfm);          
                                                             } 

/* Synarthsh afaireshs se opoiadhpote bash */
                                                             
void substraction(int ArrayM[],int Arraym[],int Base,int nbrDigit){
     
  for(nbrDigit=nbrDigit-1;nbrDigit>=0;nbrDigit=nbrDigit-1)
    if (ArrayM[nbrDigit]<Arraym[nbrDigit]){
      ArrayM[nbrDigit]=Arraym[nbrDigit]=ArrayM[nbrDigit]+Base-Arraym[nbrDigit];
      Arraym[nbrDigit-1]=Arraym[nbrDigit-1]+1;
                                          }                     
    else                     
      ArrayM[nbrDigit]=Arraym[nbrDigit]=ArrayM[nbrDigit]-Arraym[nbrDigit];                                                                                                                        
                                                                  }
                                                                  
/* Synarthsh sygrishs timwn */

int comparison(int Array[],int Array_M[],int nbrDigit) {
    
  int value=0;   
   
  for(nbrDigit=nbrDigit-1;nbrDigit>=0;nbrDigit=nbrDigit-1)
    if (Array[nbrDigit] != Array_M[nbrDigit]){
      value=1;                    
      break;                  
                                             }   
  return(value);            
                                                       }  
                                                       
/* Synarthsh adigrafeis timwn */  

/*void copy(int Array[],int Array_M[],int nbrDigit){

  for(nbrDigit=nbrDigit-1;nbrDigit>=0;nbrDigit=nbrDigit-1)         
    Array[nbrDigit]=Array_M[nbrDigit];   
     
                                                 }  */ 
                                                 
/* Boh8htikh gia magic numbers */

void MagicFinder(int Array[],int ArrayM[],int Arraym[],int Base,int nbrDigit,int *flag)   {
    
  shellsortM(&ArrayM[0],nbrDigit);    
  shellsortm(&Arraym[0],nbrDigit);  
  substraction(&ArrayM[0],&Arraym[0],Base,nbrDigit);  
  *flag=comparison(&Array[0],&ArrayM[0],nbrDigit);        
                                                                                          }                                           
                                                                                                     
/* Synarthsh eyreshs timwn gia e3etash an katalhgoyn se magiko ari8mo */ 

void nbrFinder(int counter,int i,superint HlpComb[],superint sum,int Array[],int ArrayM[],int Arraym[],int Base,int nbrDigit,int *flag)    {          
                                                                                                                                                                                 
  int j;
  
  
  if (counter==0)
    ;  
  else if (counter==1)   
    for(j=1;(j<=i)&&(*flag);j=j+1){
      BaseTransform(Base,j*HlpComb[0]+sum,nbrDigit,&Array[0],&ArrayM[0],&Arraym[0]);                        
      MagicFinder(&Array[0],&ArrayM[0],&Arraym[0],Base,nbrDigit,&(*flag));                                             
                                  }
  else 
     for(j=1;(j<=i)&&(*flag);j=j+1){
      BaseTransform(Base,j*HlpComb[0]+sum,nbrDigit,&Array[0],&ArrayM[0],&Arraym[0]);                        
      MagicFinder(&Array[0],&ArrayM[0],&Arraym[0],Base,nbrDigit,&(*flag));                                            
      nbrFinder(counter-1,j,HlpComb+1,j*HlpComb[0]+sum,&Array[0],&ArrayM[0],&Arraym[0],Base,nbrDigit,&(*flag));
                                   }
                                                                                                                                                             
                                                                                                                                           }            



                                                                                                                       
                                                                  
/* Synarthsh eyreshs magikwn ari8mwn */                                                                                  

superint magic(int Base,int nbrDigit) {
         
  int array[nbrDigit-1],array_M[nbrDigit-1],array_m[nbrDigit-1];             
  int flag=1;
  int combinations;
  int i=nbrDigit-1;
  int j=1;
    
  combinations = nbrDigit/2; 
   
  superint hlpcomb[combinations-1]; 
   
  while (i>=nbrDigit-combinations){ 
    i = i-1;    
    j = j*Base;
                                  }
  for(i = i;i >= 0;i = i-1){
    hlpcomb[i] = j;          
    j = j*Base;    
                           }       
  j=1;      
  for(i = 0;i < combinations;i = i+1){
    hlpcomb[i] = hlpcomb[i]-j;    
    j = j*Base;            
                                     }  
               
         
  for(i=1;(i<Base)&&flag;i=i+1){                          
    BaseTransform(Base,i*hlpcomb[0],nbrDigit,&array[0],&array_M[0],&array_m[0]);                                                      
    MagicFinder(&array[0],&array_M[0],&array_m[0],Base,nbrDigit,&flag);   
    nbrFinder(combinations-1,i,hlpcomb+1,i*hlpcomb[0],&array[0],&array_M[0],&array_m[0],Base,nbrDigit,&flag);                         
                             }
    if(flag==0) 
      return(DecimalTransform(Base,nbrDigit,&array[0]));
    else return(0);
                           
                                      }








                      
                               
main() {  
  
  
/*int main(int argc, char* argv[])
{
  int b;
  int n;

  if (argc != 3) {
    printf("Usage: magic b n\n"); return 1;
                 }
  sscanf(argv[1], "%d", &b);
  sscanf(argv[2], "%d", &n);
  printf("%llu\n", magic(b, n));
  return 0;
}  */
                                        
  
  
  int base,nbrD;
       
  printf("Dwse ton ari8m0 4hfiwn\n");
  scanf("%d",&nbrD);
  printf("Dwse thn bash\n"); 
  scanf("%d",&base);
  
  printf("%llu\n",magic(base,nbrD));     
  system("pause");
  return(0);     
       
       }                               
