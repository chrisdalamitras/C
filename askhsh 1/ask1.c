#include <stdio.h>
#include <stdlib.h>

/* DHLWSEIS TYPWN       */

struct NAME {
 char name[11];
 struct NAME *next;      
            };

typedef struct NAME namelist;
typedef namelist *nodelist;

/* CREATELIST SYNARTHSH      */

nodelist createlist(nodelist NODE,FILE *filep) {
      nodelist temp1;
      int c,i=0;
      
      NODE=(namelist *)malloc(sizeof(namelist));
      temp1=NODE;
      temp1->next=NULL;
      while ( (c=getc(filep)) != EOF ) {     
        if ( c != '\n') {    /* SYNTHHKH TELOUS ONOMATOS */       
          temp1->name[i]=c;          
          i=i+1;
                        }
        else {
            temp1->name[i]=c;
            temp1->next=(namelist *)malloc(sizeof(namelist));  /* DIMHOYRGEIA NEOY KOMBOY GIA NEO ONOMA */                            
            temp1=temp1->next;
            temp1->next=NULL;
            i=0;
             }                                                                                              
                                         }
      temp1->name[i]='\n';  /* TA "\n" TA THELOUME GIA NA DOYME POTE TELEIWNEI TO ONOMA */                                 
      return NODE;
                                                 }
                                    
/* PRINTLIST SYNARTHSH         */
                                    
void printlist(nodelist NODE, FILE *filep) {                                    
    int i=0;
    nodelist temp2;
    
    temp2=NODE;
    while(temp2->next != NULL) {   /* O KOMBOS ME TH LEKSH LIST 1,LIST 2 XREISIMOPOIHTE WS KOMBOS FROYROS */      
      while (i<10) {
        if( (temp2->next)->name[i] != '\n' ) {   
          putc((temp2->next)->name[i],filep);
          putchar((temp2->next)->name[i]);
          i=i+1;
                                             }
        else
          break;                                                                               
                   }
        temp2=temp2->next;
        i=0;
        fprintf(filep,"\n");
        printf("\n");    
                               }                                        
                                           }     

/* LENGTH SYNARTHSH         */
     
int length(nodelist NODE, int *LengthData) {
   nodelist temp3;
   
     *LengthData=0;
     temp3=NODE;
     while (temp3->next != NULL) {
       *LengthData=*LengthData+1;   
        temp3=temp3->next;   
                                 }
     printf("%d\n",*LengthData);                                                                                                       
                                           }
                                           
/* NODELIST SYNARTHSH          */
                                    
nodelist insertsublist(nodelist NODE1, int j, nodelist NODE2, int k, int n, int *LengthData1) {
        nodelist newnode1,newnode2;
        int i,x; 
         
        newnode1=NODE1->next;
        newnode2=NODE2->next;
        if ( (k>*LengthData1) && (n!=0) ) { /* ELENXOS GIA TO AN H THESH EINAI KATA ENA MEGALYTERH APO TO MHKOS THS LIST 1 */
          for(i=1; i<(k-1); i++) 
            newnode1=newnode1->next;          
          newnode1->next=(namelist *)malloc(sizeof(namelist));                   
          newnode1=newnode1->next;                   
          newnode1->next=NULL;                   
                           }
        else {
          for (i=1; i<k; i++)                                 
            newnode1=newnode1->next;
             }                       
        for(i=1; i<j ;i++) 
          newnode2=newnode2->next;         
          if (*LengthData1+1-k < n) {   /* ELENXOS GIA TO AN TO MHKOS POU THELOUME NA ANTIGRAPSOYME EINAI MEGALYTERO APO TIS LIST 1 */
            for(i=0; i<n; i++) {
              for(x=0; x<11; x++)  
                newnode1->name[x]=newnode2->name[x];                               
              newnode2=newnode2->next;
              if ((newnode1->next == NULL) && (i != n-1)) {   /* ELENXOS GIA TO POTE XREIAZETAI NEOS KOMBOS */
                newnode1->next=(namelist *)malloc(sizeof(namelist));
                newnode1=newnode1->next;
                newnode1->next=NULL;
                                                            }                             
              else 
                newnode1=newnode1->next;
                               }                                                         
                                     }               
          else {   
            for(i=0; i<n; i++) {
              for(x=0; x<11; x++)         
                newnode1->name[x]=newnode2->name[x];     
              newnode1=newnode1->next;
              newnode2=newnode2->next;                 
                               }                               
               } 
        return NODE1;                                                                   
                                                                        }

/* KYRIA SYNARTHSH-MAIN       */

main() {
        
nodelist node1,node2,temp;
FILE *fpin,*fpout;
int length_data1,length_data2,k,j,n;

fpin=fopen("in.dat","r");         /* ANOIGMA ARXEIWN */
fpout=fopen("out.dat","w");        
        
node1=createlist(node1,fpin);
temp=node1;
node2=node1->next;

/* SPASIMO LISTAS SE LIST 1 KAI LIST 2 */

while( (node2->name[0]!='L') || (node2->name[1]!='i') || (node2->name[2]!='s') || (node2->name[3]!='t') || (node2->name[4]!=' ') || (node2->name[5]!='2') ) {   
  node2=node2->next;       
  temp=temp->next;     
}
temp->next=NULL;
printf("Ta onomata tis listas 1 einai:\n");
fprintf(fpout,"Ta onomata tis listas 1 einai:\n");        
printlist(node1,fpout);
printf("Ta onomata tis listas 2 einai:\n");
fprintf(fpout,"Ta onomata tis listas 2 einai:\n");
printlist(node2,fpout);
printf("To synolo twn kombwn tis listas 1 einai:");
length(node1,&length_data1);
printf("To synolo twn kombwn tis listas 2 einai:");
length(node2,&length_data2);
printf("Dwste tin thesi tis listas 2 apo tin opoia thelete na ginei antigrafi:");
scanf("%d",&j);

/* ELENXOS ORTHOTHTAS DEDOMENWN */

while( (j<1) || (j>length_data2) ) {
  printf("Lathos stoixeia.Ksanadwse:");                         
  scanf("%d",&j);                        
                                   }
printf("Dwste to mikos tis antigrafis:");
scanf("%d",&n);
while( (n<0) || (n>length_data2+1-j) ) {
  printf("Lathos stoixeia.Ksanadwse:");     
  scanf("%d",&n);     
                                       }
printf("Dwste tin thesi tis listas 1 apo tin opoia thelete na arxisei h antigrafi:");
scanf("%d",&k);
while( (k<1) || (k-1>length_data1) ) {
  printf("Lathos stoixeia.Ksanadwse:");     
  scanf("%d",&k);     
                                     }
node1=insertsublist(node1,j,node2,k,n,&length_data1);
printf("H lista 1 meta tin antigrafi einai:\n");
fprintf(fpout,"H lista 1 meta tin antigrafi einai:\n"); 
printlist(node1,fpout);
printf("H lista 2 meta tin antigrafi einai:\n");
fprintf(fpout,"H lista 2 meta tin antigrafi einai:\n");
printlist(node2,fpout);
printf("O arithmos twn kombwn tis listas 1 meta tin antigrafi einai:");
length(node1,&length_data1);
printf("O arithmos twn kombwn tis listas 2 meta tin einai:");
length(node2,&length_data2);

fclose(fpin);       /* KLEISIMO ARXEIWN */
fclose(fpout);                                                                                 

system("pause");
return (0);
       }


