#include <stdio.h>
#include <stdlib.h>

typedef int * m ;
typedef float *q ;
int main(){
    int i;
    int a;
    int j;
    float c;
    q *xf;
    q *res;
    FILE *fpin;
    FILE *fpout;
    m *x ;  /* x einai o pinakas eisodoy*/
    int n;
    fpin = fopen("in.dat", "r"); 
    fpout = fopen("out.dat","w");
    fscanf(fpin,"%d %d ",&n,&j);
    x= (m*)malloc(n*sizeof(m));
    for( i=0;i<n;i++){
    x[i]=(int *)malloc(j*sizeof(int));}
    
    for( i=0; i<n ;i++){
          fscanf(fpin,"\n");printf("\n");fprintf(fpout,"\n");
    for( a=0; a<j ; a++){
     fscanf(fpin,"%d",&(x[i][a])    );
     printf(" %d ", x[i][a]  );  /* ektyposh sto stdout*/
     fprintf(fpout," %d ",x[i][a]) ;  }  
         }  
     system("pause");      
     fclose(fpin);         
     fclose(fpout);
     /****************************************************/
     /*epe3ergasia tou pinaka kai dhmiourgia adistrofou*/
     /*tha dhmiourgisw  ena pinaka float me idia stoixeia me ton pinaka eisodou*/
    xf= (q*)malloc(n*sizeof(q));
    res=(q*)malloc(n*sizeof(q)); /* res einai o pinakas apotelesma*/
    for( i=0;i<n;i++){
    xf[i]=(float *)malloc(j*sizeof(float));  /*xf o pinakas me stoixeia float*/
    res[i] = (float *)malloc(j*sizeof(float));
          }   
    for( i=0; i<n ;i++){                   
         for( a=0; a<j ; a++){
         xf[i][a] = x[i][a];  
         if (i==a) res[i][a] = 1 ; else res[i][a]=0; /*o res arxikopoihtai ws monadiaios*/
              }         
         }     
     /*EBRESH ADISTROFOY PINAKA*/
   int  l=1; 
   int  z;
   float temp;
   for(i=0;i<n;i++){
    while ((xf[i][i]==0)&&((l+i)<n)) {   /* adimetathesh grammhs me hgetiko stoixoio 0 */
         if (xf[i+l][i] !=0) { for(a=0;a<j;a++){
                        temp=xf[i][a];
                        xf[i][a]=xf[i+l][a];
                        xf[i+l][a]=temp;
                       temp=res[i][a];
                        res[i][a]=res[i+l][a];
                        res[i+l][a]=temp;  }
         }
         if    (xf[i+l][i] == 0) 
               {l=l+1;}
     }l=1;
     c = xf[i][i]; 
     for(a=0; a<j; a++){
       xf[i][a] = xf[i][a] / c;
       res[i][a] = res[i][a] / c ;
     };
     
     for(z=0;z<n;z++){
       if (z!=i){c=xf[z][i];
         for(a=0;a<j;a++) {
            xf[z][a]=xf[z][a]-c*(xf[i][a]); 
            res[z][a]=res[z][a]-c*(res[i][a]);
         }                
      }
    }
   };
                 

fpout=fopen("out.dat","a");
     for( i=0; i<n ;i++){  fprintf(fpout,"\n");  printf("\n");             
         for( a=0; a<j ; a++){
         fprintf(fpout," %f ",res[i][a]);
          printf(" %f ",res[i][a])  ;  }
         }
     
     fclose(fpout);
     system("pause");
     
 return 0;   }
