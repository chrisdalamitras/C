#include <stdio.h>
#include <stdlib.h>

int main(int argc , char *argv[]) {

FILE *fp;
double t; //Xronos poy egataleipei enas dromeas
unsigned long NL[2]; //To 1o stoixeio einai to N , to 2o to L 
int c , i=0 , j=0 , i1=0 , flag;
char ct[7] = {'\0'};  //To symbolo '\0' ypodhlwnei to telos toy string

fp=fopen(argv[1] ,"r"); //Anoigma arxeioy gia anagnwsh

while((c = getc(fp)) != '\n') {      //Diabasma prwths grammhs toy arxeioy
  if(c != ' ')
    ct[i++]=c;
  else {
    NL[j++]=strtoul(ct,(char **)NULL,10);  //Synarthsh metatrophs typoy poy brisketai sto stdlib
    while(i > 0)
      ct[i--]='\0';
  }    
}
NL[j++]=strtoul(ct,(char **)NULL,10);  //Ton teleytaio ari8mo ths prwths grammhs ton metatrepoyme xeirokinhta
while(i > 0)                            //dioti den 8a bei sto while otan synadhsei to symbolo teloys grammhs '\n'
  ct[i--]='\0';

double DV[2][NL[0]]; //To stoixeio ths [0][j] sthlhs einai to D toy j dromea , to [1][j] to V toy j dromea
double xronoi[2][NL[0]]; //To stoixeio ths [0][j] sthlhs einai o xronos poy exoyn prosperasei ton [j] dromea
                         //To stoixeio ths [1][j] sthlhs einai o ari8mos toy dromea
for(i=0;i<2;i++)
 for(j=0;j<NL[0];j++)
  xronoi[i][j]=-1; //To -1 shmainei pws o dromeas den exei prosperastei apo kanenan

i=j=0;
while((c = getc(fp)) != EOF) { //Gemizoyme ton pinaka DV[][] me ta dedomena toy arxeioy
  if((c != ' ') && (c != '\n'))
    ct[i++]=c; 
  else {
    DV[i1++][j]=atof(ct); //Synarthsh metatrophs typoy poy brisketai sto stdlib
    while(i > 0)
      ct[i--]='\0';
    if(c == '\n') {
      i1=0;
      j++;
    }
  }
}

for(i=0;i<NL[0];i++) { //To loop ayto ypologizei toys xronoys poy pernane oloi oi dromeis toys brosta toys dromeis
 flag=1;               //To i adiprosopeyei ton current dromea kai to j oloys aytoys poy briskodai brosta apo ton i

 for(j=i+1;(j<NL[0]) && flag && (flag = DV[1][i]>DV[1][j]);j++) {  //Ypologizei toys xronoys poy o j dromeas
  t=(DV[0][j]-DV[0][i]) / (DV[1][i]-DV[1][j]);                    //pernaei toys dromeis j+1,j+2...NL[0]
  if((xronoi[0][j] == -1) || (t < xronoi[0][j])) {
   xronoi[0][j]=t;
   xronoi[1][j]=j;
  }
  else 
   if((xronoi[0][i] != -1) && (xronoi[0][i] < t))   //Diapistwnei an kapoios dromeas poy pernaei o j exei perastei
    flag=0;                                        //hdh apo kapoion poy brisketai pisw apo ton j  
 }
 for(j=0;(j<i) && flag && (flag = DV[1][i]>DV[1][j]);j++) {        //Ypologizei toys xronoys poy o j dromeas
  t=(NL[1]+DV[0][j]-DV[0][i]) / (DV[1][i]-DV[1][j]);              //pernaei toys dromeis j-1,j-2...1
  if((xronoi[0][j] == -1) || (t < xronoi[0][j])) {
   xronoi[0][j]=t;
   xronoi[1][j]=j;
  }
  else 
   if((xronoi[0][i] != -1) && (xronoi[0][i] < t)) 
    flag=0;                                        
 }
}
//-------------Algori8mos ta3inomhshs shellsort----------------------------
unsigned long gap , n=NL[0];
double temp;  

  for(gap=n/2;gap>0;gap/=2)
    for(i=gap;i<n;i++)   
      for(j=i-gap;j>=0 && xronoi[0][j]>xronoi[0][j+gap];j-=gap) {
        temp = xronoi[0][j];                 
        xronoi[0][j] = xronoi[0][j+gap];               
        xronoi[0][j+gap] = temp;
        temp = xronoi[1][j];                 
        xronoi[1][j] = xronoi[1][j+gap];               
        xronoi[1][j+gap] = temp;                
      }         
//-------------------------------------------------------------------------
for(j=0;j<NL[0];j++)
 if(xronoi[1][j] != -1)
  printf("%.0f ",xronoi[1][j]+1);
printf("\n");

fclose(fp); //Kleisimo arxeioy
return 0;
}
