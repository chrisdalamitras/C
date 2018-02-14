#include <stdio.h>
#include <stdlib.h>

/* DHLWSH TYPOY DENTROY */
typedef struct TreeNode {
        int rank,info;
        struct TreeNode *left,*right,*middle;
                        }*TreePtr;
                        
/* SYNARTHSH CreateList_ReadFile */
/* H SYNARTHSH AYTH EKTOS TOY OTI EKXWREI STOIXEIA STON PINAKA DHMIOYRGEI KAI MIA LISTA */                        
TreePtr CreateList_ReadFile(TreePtr NODE,int arr[],int MaxCells,FILE *filep) {
        int i=0;
        TreePtr temp;                
                        
        NODE=(struct TreeNode *)malloc(sizeof(struct TreeNode));
        temp=NODE;
        temp->middle=NULL;
        fscanf(filep,"%d ",&arr[i]);
        i=i+1;
        while(i<MaxCells) {
          fscanf(filep,"%d ",&arr[i]);                
          temp->middle=(struct TreeNode *)malloc(sizeof(struct TreeNode));
          temp=temp->middle;          
          temp->middle=NULL;                         
          i=i+1;                                      
                          }
        return NODE;
                                                                             }
                                                                             
/* SYNARTHSH CreatePosTree */
/* H SYNARTHSH AYTH METASXIMATIZEI THN LISTA SE DENTRO */                                                                             
TreePtr CreatePosTree(TreePtr NODE) {                                                                             
        TreePtr temp1,temp2,temp3;                                                                      
                                                                             
        temp1=temp2=temp3=NODE;                                                                     
        while(temp2 != NULL) {       /* H temp2 EINAI H RIZA TOY EKASTOTE YPODENDROY */                                                              
          if(temp1==NULL) {          /* H temp1 EINAI O ARISTEROS H' O DEKSIS KOMBOS THS temp2 */                                                          
            temp2->left=NULL;                                                                 
            temp2->right=NULL;                                                                 
                          }
          else {
            temp1=temp1->middle;
            temp2->left=temp1;   
            if(temp1 != NULL) {
              temp1=temp1->middle;          
              temp2->right=temp1;                 
                              }
            else                   
              temp2->right=NULL;                 
               }               
          temp2=temp2->middle;   
          temp3->middle=NULL;       /* H temp3 KANEI OLOYS TOYS DEIKTES middle ISOYS ME NULL */
          temp3=temp2;     
                              }                                               
        return NODE;                                                                     
                                     }
                                     
/* SYNARTHSH GiveInfo_aValue */
/* H SYNARTHSH AYTH DINEI STO DENTRO TIMES */                                     
void GiveInfo_aValue(TreePtr NODE,int *poe,int arr[]) {                                     
     if(NODE->left != NULL)
       GiveInfo_aValue(NODE->left,poe,arr);                                
     NODE->info=arr[*poe];                   /* H poe DEIXNEI TO STOIXEIO TOY PINAKA PROS EISAGWGH STO DENDRO */             
     *poe=*poe+1;                                
     if(NODE->right != NULL)
       GiveInfo_aValue(NODE->right,poe,arr);                                
                                                      }
                                     
/* SYNARTHSH PrintPosTree */
/* H SYNARTHSH AYTH EMPHANIZEI TO DENTRO STHN OTHONH KAI SE ARXEIO */                                     
void PrintPosTree(TreePtr NODE,FILE *filep) {                                     
     if(NODE->left != NULL)                                                 
       PrintPosTree(NODE->left,filep);                              
     printf("%d\n",NODE->info);
     fprintf(filep,"%d\n",NODE->info);
     if(NODE->right != NULL)                                
       PrintPosTree(NODE->right,filep);                              
                                }    
                                     
/* SYNARTHSH CountLeaves */
/* H SYNARTHSH AYTH METRA TA PAIDEIA MIAS RIZAS XWRIS NA METRA THN RIZA */                                     
int CountLeaves(TreePtr NODE) {                                     
    if(NODE==NULL)                                 
      return 0;                               
    else if((NODE->left==NULL) && (NODE->right==NULL))                                 
      return 0;                               
    else if((NODE->left==NULL) || (NODE->right==NULL))                                 
      return CountLeaves(NODE->left)+CountLeaves(NODE->right)+1;                               
    else                                 
      return CountLeaves(NODE->left)+CountLeaves(NODE->right)+2;                               
                              }        
                                     
/* SYNARTHSH RankOfLeaves */                                     
void RankOfLeaves(TreePtr NODE) {                                     
     if(NODE->left != NULL) {                                
       NODE->rank=CountLeaves(NODE->left)+2;                              
       RankOfLeaves(NODE->left);                              
                            }        
     else                                
       NODE->rank=1;                              
     if(NODE->right != NULL)                                
       RankOfLeaves(NODE->right);                              
                                }    
                                     
/* SYNARTHSH SearchPosition */                                     
TreePtr SearchPosition(TreePtr NODE,int k,int *count) {
     if(NODE==NULL) {
       *count=*count+1;      /* TO count XREISIMOPOIHTE ARGOTERA APO THN SimSearch */      
       return NULL;          /* GIA THN EURESH SYGRISEWN */
                    }                                        
     else if(NODE->rank==k) {
       *count=*count+2;                                   
       return NODE;
                            }                              
     else if(NODE->rank>k) {
       *count=*count+3;                                   
       return SearchPosition(NODE->left,k,count);
                           }                              
     else {
       *count=*count+3;                                   
       return SearchPosition(NODE->right,k-(NODE->rank),count);
          }                              
                                                      }
                                        
/* SYNARTHSH InsertPosition */                                        
TreePtr InsertPosition(TreePtr NODE,TreePtr Pointer) {
        TreePtr temp;
        int number;
                          
        temp=Pointer->left;                                                
        Pointer->left=(struct TreeNode *)malloc(sizeof(struct TreeNode));
        Pointer=Pointer->left;
        Pointer->right=NULL;
        Pointer->middle=NULL;
        printf("Dwste tin timi toy arithmou pou thelete na eisagete.\n");
        scanf("%d",&number);                                
        Pointer->info=number;                               
        Pointer->left=temp;
        
        return NODE;                                
                                                     }  
                                        
/* SYNARTHSH HeavenOrHell */
/* H SYNARTHSH AYTH BRISKEI TON DEKSIOTERO KOMBO ENOS DENDROY */
TreePtr HeavenOrHell(TreePtr NodePtr) {
        if(NodePtr->right != NULL)        
          return HeavenOrHell(NodePtr->right);
        else
          return NodePtr;
                                      }
                                      
/* SYNARTHSH TheatreOfDeath */
/* H SYNARTHSH  AYTH BOHTHAEI STHN EYRESH TOY PROIGOYMENOY KOMBOY APO AYTON POY THELOYME NA DIAGRAPSOYME */                                      
TreePtr TheatreOfDeath(TreePtr NODE,int k,TreePtr Pointer) {
        if(NODE==Pointer || NODE->left==Pointer || NODE->right==Pointer)        
          return NODE;
        else if(NODE->rank>k)
          return TheatreOfDeath(NODE->left,k,Pointer);
        else
          return TheatreOfDeath(NODE->right,k-(NODE->rank),Pointer);          
                                                           }                                      

/* SYNARTHSH DeletePosition */
TreePtr DeletePosition(TreePtr NODE,TreePtr Pointer,TreePtr Pointer1) {
        if(Pointer1->left==Pointer)        {   /* O Pointer1 DEIXNEI STON PROIGOYMENO KOMBO APO AYTWN POY THELOYME NA DIAGRAPSOYME*/                
          if(Pointer->left != NULL) {          /* O Pointer DEIXNEI STON KOMBO PROS DIAGRAPHH */        
            Pointer1->left=Pointer->left;
            if(Pointer->right != NULL) { 
              Pointer1=HeavenOrHell(Pointer1->left);      
              Pointer1->right=Pointer->right;
                                       }
                                    }
          else
            Pointer1->left=Pointer->right;                                    
                                           }       
        else if(Pointer1->right==Pointer) {
          if(Pointer->left != NULL) {      
            Pointer1->right=Pointer->left;
            if(Pointer->right != NULL) {
              Pointer1=HeavenOrHell(Pointer1->right);                
              Pointer1->right=Pointer->right;                  
                                       }        
                                    }
          else                          
            Pointer1->right=Pointer->right;                        
                                           }
        else {
          if(Pointer1->left != NULL) {                                                  
            Pointer1=HeavenOrHell(Pointer1->left);                                              
            Pointer1->right=Pointer->right;                                              
            NODE=Pointer->left;
                                     }
          else                     
            NODE=Pointer->right;                                                                   
             }
        free(Pointer);     
        return NODE;                                                            
                                                                      }
                                                                      
/* SYNARTHSH SimSearch */                                                                      
void SimSearch(TreePtr NODE,int s,int *count,FILE *filep) {
      int n,i,sum=0;
      float f;
      
      for(i=0; i<200; i++) {
        *count=0;       
        n=rand();          /* TO n EINAI H THESH TOY STOIXEIOY PROS ANAZHTHSH */
        f=(1.0*n/RAND_MAX)*(s-1);      
        n=f+1;
        SearchPosition(NODE,n,count);
        sum=sum + *count;       /* TO sum EINAI TO ATHRISMA TWN SYNOLIKWN SYGRISEWN */                
                          }                    
      printf("\nO mesos oros tou synolikou arithmou sygrisewn einai:%f\n",(1.0*sum)/200);
      printf("O mesos oros twn sygrisewn ana anazitisi einai:%f\n\n",(1.0*(*count))/200);
      fprintf(filep,"\nO mesos oros tou synolikou arithmou sygrisewn einai:%f\n",(1.0*sum)/200);
      fprintf(filep,"O mesos oros twn sygrisewn ana anazitisi einai:%f\n\n",(1.0*(*count))/200);          
                                                          }                                                     
        
        
main() { 
         
 FILE *fpin,*fpout;     
 TreePtr node,node1,pointer,pointer1;     
 int array[20],pinaka[100],PosOfElem=0,k,answer,Count=0;     
              
 fpin=fopen("in.dat","r");       /* ANOIGMA ARXEIWN */
 fpout=fopen("out.dat","w");
 node=CreateList_ReadFile(node,array,20,fpin);
 node=CreatePosTree(node);      
 GiveInfo_aValue(node,&PosOfElem,array);
 printf("Ta stoixeia tis akolouthias einai:\n");
 fprintf(fpout,"Ta stoixeia tis akolouthias einai:\n");                                               
 PrintPosTree(node,fpout);
 RankOfLeaves(node);
 do {       /* ARXH EPANALHPSHS */
  printf("Ean thelete na anazitisete ena stoixeio dwste tin thesi toy.\nAlloiws dwste enan arithmo <=0.\n");
  scanf("%d",&k);    /* TO k EINAI H THESH TOY STOIXEIOY */
  while(k>0) {
    pointer=SearchPosition(node,k,&Count);           
    if(pointer==NULL)
      printf("To stixio den yparxei\n");
    else 
      printf("To zitoumeno stoixeio einai:%d\n",pointer->info);    
    printf("Ean thelete na synexisete dwste tin thesi toy stoixeioy pros eyresi.\nAlloiws dwste enan arithmo <=0.\n");
    scanf("%d",&k);         
             }
  printf("Ean thelete na eisagete kapoio stoixeio stin akolouthia dwste tin thesi\npoy thelete na ginei eisagwgi.");
  printf("Alloiws dwste enan arithmo <=0.\n");
  scanf("%d",&k);
  while(k>0) {
    pointer=SearchPosition(node,k,&Count);         
    if(pointer==NULL)         
      printf("H eisagwgei einai adynati stin thesi ayti\n");       
    else {        
      node=InsertPosition(node,pointer);
      RankOfLeaves(node);
         }         
    printf("Ean thelete na synexisete dwste tin thesi toy stoixeioy pros eisagwgi.\nAlloiws dwste enan arithmo <=0.\n");       
    scanf("%d",&k);         
             }
  printf("H akolouthia meta tis eisagwges einai:\n");
  fprintf(fpout,"H akolouthia meta tis eisagwges einai:\n"); 
  PrintPosTree(node,fpout);
  printf("Ean thelete na diagrapsete kapoio stoixeio stin akoloythia dwste tin thesi toy.\nAlloiws dwste enan arithmo <=0\n");
  scanf("%d",&k);
  while(k>0 && node != NULL) {
    pointer=SearchPosition(node,k,&Count);
    if(pointer==NULL)
      printf("H diagraphi einai adynati stin thesi ayti\n");
    else {
      pointer1=TheatreOfDeath(node,k,pointer);   
      node=DeletePosition(node,pointer,pointer1);
      if(node != NULL)
        RankOfLeaves(node);   
         }
    printf("Ean thelete na synexisete dwste tin thesi toy stoixeioy pros diagraphi.\nAlloiws dwste enan arithmo <=0.\n");     
    scanf("%d",&k);              
                             }
  if(node==NULL) {                          
    printf("H akolouthia einai keni.Diagrapsate ola ta stoixeia,den ginete epmenws na\nepanalabete ta parapanw.\n");
    fprintf(fpout,"H akolouthia einai keni.Diagrapsate ola ta stoixeia\n");
                 }                         
  else {                          
    printf("H akolouthia meta tis diagraphes einai:\n");
    fprintf(fpout,"H akolouthia meta tis diagraphes einai:\n");
    PrintPosTree(node,fpout);
    printf("Ean thelete na synexisete tis parapanw diadikasies patiste <1>\nalloiws opoindipote allo symbolo.\n");
    scanf("%d",&answer);
       }     
    }while(node != NULL && answer==1);     /* TELOS EPANALHPSHS */                                                                                                                
  system("pause");
  printf("\nTo programma tha ektelesei twra 200 anazitiseis se mia akoloythia 100\nstoixeiwn kai tha ypologisei");  
  printf(" ton meso oro twn synolikwn sygrisewn kathws\nkai ton meso oro");
  printf(" ton sygrisewn ana anazitisi gia tin euresi twn stoixeiwn.\n\n");
  system("pause");
  node1=CreateList_ReadFile(node1,pinaka,100,fpin);
  node1=CreatePosTree(node1);
  PosOfElem=0;
  GiveInfo_aValue(node1,&PosOfElem,pinaka);
  RankOfLeaves(node1);
  Count=0;
  SimSearch(node1,100,&Count,fpout);
  fclose(fpin);         /* KLEISIMO ARXEIWN */
  fclose(fpout);
  system("pause");        
        }
