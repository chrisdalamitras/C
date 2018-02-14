#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* DYLWSEIS TYPWN                                              */

typedef struct {
         float mesos_oros;
         int red;
         int green;
         int blue;
         int collumn;
} TableElementType;

typedef struct {
        int rowNumber;
        TableElementType *theContents;
} MatrixElementType; 

/* SYNARTHSEIS POY THA XRHSIMOPOIHSOYME                                             */

MatrixElementType * createMatrix(MatrixElementType aMatrix[], int row, int col);
TableElementType * createLine(int col);
void readMatrix(MatrixElementType aMatrix[], int row, int col, FILE *filep);
void printMatrix(MatrixElementType aMatrix1[],MatrixElementType aMatrix2[], int row, int col, FILE *filep);
MatrixElementType *processImages(MatrixElementType inMatrix[], MatrixElementType outMatrix[], int row, int col, float percentage);
void DevilsNeverCry(TableElementType *pointer);

/* KYRIA SYNARTHSH-MAIN                                                            */

int main()
{

  MatrixElementType *Matrix_input,*Result;
                                        
  int rowSize, collumnSize;   /* DIASTASEIS PINAKA */
  FILE *fpin;
  FILE *fpout;
  float percent;
  
  fpin=fopen("in.dat","r");   /* ANOIGMA ARXEIWN */
  fpout=fopen("out.dat","w");
  
  /* DIABASMA DIASTASEWN PINAKA APO ARXEIO */
  
  fscanf(fpin,"%d %d",&rowSize,&collumnSize);
  fscanf(fpin,"\n");
  
  /* DIMHOYRGEIA PINAKWN */
    
  Matrix_input = createMatrix(Matrix_input, (rowSize+2), (collumnSize+2));
  Result = createMatrix(Result, rowSize, collumnSize);
   
   readMatrix(Matrix_input, rowSize, collumnSize, fpin);  /* GEMISMA ARXIKOY PINAKA ME STOIXEIA */
   printf("Dwste to pososto:");
   scanf("%f",&percent);
   Result = processImages(Matrix_input, Result, rowSize, collumnSize, percent ); /* GEMISMA PINAKA APOTELESMATWN ME STOIXEIA */
     
   printMatrix(Matrix_input, Result, rowSize, collumnSize, fpout); /* EMFANISH PINAKWN */
   
   fclose(fpin);     /* KLEISIMO ARXEIWN */
   fclose(fpout); 
   system("pause");   
     
   
   return (0);

}

/* CREATEMATRIX SYNARTHSH                                         */

MatrixElementType * createMatrix(MatrixElementType aMatrix[], int rowSize, int collumnSize) {
      
       MatrixElementType *temp;
       TableElementType  *temp1;
       
       aMatrix = (MatrixElementType *) malloc(rowSize * sizeof(MatrixElementType));
       for(temp = aMatrix; temp < aMatrix + rowSize; temp++) {
         temp->theContents = createLine(collumnSize);
         for(temp1=temp->theContents; temp1< (temp->theContents) + collumnSize; temp1++) {
           temp1->mesos_oros = -1.0;
                                                                                         }
           
                                                             }      
       return aMatrix;
}

/* CREATELINE SYNARTHSH                                         */

TableElementType * createLine(int collumn) {
       return (TableElementType *) malloc(collumn * sizeof(TableElementType));
}


/* READMATRIX SYNARTHSH                                            */

void readMatrix(MatrixElementType arr[], int rowSize, int collumnSize, FILE *filep) {
    MatrixElementType *p;
    TableElementType *p1;
  
   for(p=arr+1; p < (arr+1) + rowSize; p++){
     for(p1=(p->theContents)+1; p1 < ((p->theContents)+1) + collumnSize; p1++){
        fscanf(filep,"%d %d %d",&(p1->red),&(p1->green),&(p1->blue));
        p1->mesos_oros = ((p1->red)+(p1->green)+(p1->blue))/3.0;      
     }
     fscanf(filep,"\n");
   }
}
    
/* PRINTMATRIX SYNARTHSH                                       */

void printMatrix(MatrixElementType arr1[], MatrixElementType arr2[], int rowSize, int collumnSize,FILE *filep) {
     
    MatrixElementType *p;
    TableElementType *p1;
    
   if (arr1 != NULL) {         /* EMFANISH POSOSTWN */   
    for(p=arr1+1; p < (arr1+1) + rowSize; p++){     
      for(p1=(p->theContents)+1; p1 < ((p->theContents)+1) + collumnSize; p1++){
        printf("%3.2f\n",p1->mesos_oros);
        fprintf(filep,"%3.2f\n",p1->mesos_oros);
                                                                               }
      printf("\n");
      fprintf(filep,"\n");
                                              }
                     }
   if (arr2 != NULL) {       /* EMFANISH APOTELESMATWN */
     for(p=arr2; p < arr2 + rowSize; p++) {
       for(p1=p->theContents; p1 < p->theContents + collumnSize; p1++) {          
         printf("%d\n",p1->red);        
         fprintf(filep,"%d\n",p1->red);        
                                                                       }
       printf("\n");                                                                 
       fprintf(filep,"\n");                                                                
                                          }
                     }   
}

/* PROCESSIMAGES SYNARTHSH                                            */
 
MatrixElementType * processImages(MatrixElementType inMatr[], MatrixElementType outMatr[], int row, int col,float percentage) {

MatrixElementType *p,*pointer;
TableElementType *p1,*pointer1;
int i,j=0,y=2;
float up,down,right,left;

pointer=outMatr;
pointer1=pointer->theContents;
for(p=inMatr+1; p < (inMatr+1)+row; p++) {
  i=1;         /* BHMA STOIXEIWN SYGRISHS STIS STHLES */     
  for(p1=(p->theContents)+1; p1 < ((p->theContents)+1)+col; p1++) {
   if ( ((p1->mesos_oros) == 0) && (percentage != 100) ) 
    DevilsNeverCry(pointer1);
   else {                        
    up = (((inMatr+j)->theContents)+i)->mesos_oros;   /* PANW STOIXEIO SYGRISHS */
    down = (((inMatr+y)->theContents)+i)->mesos_oros; /* KATW STOIXEIO SYGRISHS */
    left=(p1-1)->mesos_oros;                          /* ARISTERO STOIXEIO SYGRISHS */
    right=(p1+1)->mesos_oros;                         /* DEKSIO STOIXEIO SYGRISHS */
    if( ((up>0) && (fabs((p1->mesos_oros)-up)/(p1->mesos_oros))*100>percentage) || ((down>0) && (fabs((p1->mesos_oros)-down)/(p1->mesos_oros))*100>percentage) ) 
     DevilsNeverCry(pointer1);
    else if( ((left>0) && (fabs((p1->mesos_oros)-left)/(p1->mesos_oros))*100>percentage) || ((right>0) && (fabs((p1->mesos_oros)-right)/(p1->mesos_oros))*100>percentage) )   
     DevilsNeverCry(pointer1);
    else {
     pointer1->red=0;    
     pointer1->green=0;    
     pointer1->blue=0;
         }
        }   
    i=i+1;
    pointer1=pointer1+1;                                                                                                                                                                                                                                                                                                                                                               
                                                                  }
  j=j+1;   /* BHMA STOIXEIWN SYGRISHS STIS GRAMMES */
  y=y+1;
  pointer=outMatr+j; /* BHMA PINAKA APOTELEMATWN */
  pointer1=pointer->theContents;
                                         }

return outMatr;


}

/* DEVILSNEVERCRY SYNARTHSH                   */

void DevilsNeverCry(TableElementType *pointer) {
  
pointer->red=1; 
pointer->green=1;
pointer->blue=1;
                                              }



