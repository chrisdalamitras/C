#include <stdio.h>
#include <stdlib.h> 
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glut.h>
#include <math.h> 
#define PI 3.14159 
#define ellipsePoints 256 
int i,a,b,j;
GLuint listID;
GLuint *textureID;
GLfloat angle;
GLfloat rotate;
GLfloat ZXangle;
GLfloat ZYangle;
GLfloat radius,radMin;
GLuint a1,b1;
GLfloat den1;
GLsizei width=800;
GLsizei height=600;
GLUquadric *sun,*mercury,*venus,*earth,*mars,*jupiter,*saturn,*uranus,*neptune,*moon,*saturnring,*uranusring;

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;

/* Reads a long 32 bit integer; comment out one or the other shifting line below, 
whichever makes your system work right. */
unsigned int endianReadInt(FILE* file) {
unsigned char  b[4]; 
unsigned int i;

   if ( fread( b, 1, 4, file) < 4 )
     return 0;
   i = (b[3]<<24) | (b[2]<<16) | (b[1]<<8) | b[0]; // big endian
   //i = (b[0]<<24) | (b[1]<<16) | (b[2]<<8) | b[3]; // little endian
   return i;
}

/* Reads a 16 bit integer; comment out one or the other shifting line below, 
whichever makes your system work right. */
unsigned short int endianReadShort(FILE* file) {
unsigned char  b[2]; 
unsigned short s;

   if ( fread( b, 1, 2, file) < 2 )
     return 0;
   s = (b[1]<<8) | b[0]; // big endian
   //s = (b[0]<<8) | b[1]; // little endian
   return s;
}


// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  
int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
	printf("File Not Found : %s\n",filename);
	return 0;
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if (!(image->sizeX = endianReadInt(file))) {
	printf("Error reading width from %s.\n", filename);
	return 0;
    }
    printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height 
    if (!(image->sizeY = endianReadInt(file))) {
	printf("Error reading height from %s.\n", filename);
	return 0;
    }
    printf("Height of %s: %lu\n", filename, image->sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;

    // read the planes
    if (!(planes=endianReadShort(file))) {
	printf("Error reading planes from %s.\n", filename);
	return 0;
    }
    if (planes != 1) {
	printf("Planes from %s is not 1: %u\n", filename, planes);
	return 0;
    }

    // read the bits per pixel
    if (!(bpp = endianReadShort(file))) {
	printf("Error reading bpp from %s.\n", filename);
	return 0;
    }
    if (bpp != 24) {
	printf("Bpp from %s is not 24: %u\n", filename, bpp);
	return 0;
    }
	
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
	printf("Error allocating memory for color-corrected image data");
	return 0;	
    }

    if ((i = fread(image->data, size, 1, file)) != 1) {
	printf("Error reading image data from %s.\n", filename);
	return 0;
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
	temp = image->data[i];
	image->data[i] = image->data[i+2];
	image->data[i+2] = temp;
    }
    
    // we're done.
    return 1;
}

void init(){
  
  glEnable(GL_LIGHTING);
  //Defining global ambient lighting properties 
  GLfloat globalAmbient[]={0.2,0.2,0.2};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);
     
  //Defining "ambient reflection" coefficients for surfaces
  GLfloat ambientMat[]={1,1,1};
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambientMat);
          
  //Defining the position of the point light source GL_LIGHT0 at (x,y,z)=(0,0,0)
  GLfloat light0Position[]={0,0,0,1};
  glLightfv(GL_LIGHT0,GL_POSITION,light0Position);

  //Defining "diffuse" lighting properties for GL_LIGHT0
  GLfloat light0Diffuse[]={1,1,1};
  glLightfv(GL_LIGHT0,GL_DIFFUSE,light0Diffuse);
	
  //Defining "diffuse reflection" coefficients for the surface material 
  GLfloat diffuseMat[]={1,1,1};
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuseMat);    

  //Enabling light GL_LIGHT0
  glEnable(GL_LIGHT0);        
      
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  Image *sunTexture=new Image();
  ImageLoad("C:\\Users\\вягстос\\Desktop\\Planet textures\\Sun.bmp",sunTexture);
  Image *mercuryTexture=new Image();
  ImageLoad("C:\\Users\\вягстос\\Desktop\\Planet textures\\Mercury.bmp",mercuryTexture);
  Image *venusTexture=new Image();
  ImageLoad("C:\\Users\\вягстос\\Desktop\\Planet textures\\Venus.bmp",venusTexture);
  Image *earthTexture=new Image();
  ImageLoad("C:\\Users\\вягстос\\Desktop\\Planet textures\\Earth.bmp",earthTexture);
  Image *marsTexture=new Image();
  ImageLoad("C:\\Users\\вягстос\\Desktop\\Planet textures\\Mars.bmp",marsTexture);
  Image *jupiterTexture=new Image();
  ImageLoad("C:\\Users\\вягстос\\Desktop\\Planet textures\\Jupiter.bmp",jupiterTexture);
  Image *saturnTexture=new Image();
  ImageLoad("C:\\Users\\вягстос\\Desktop\\Planet textures\\Saturn.bmp",saturnTexture);
  Image *saturnringTexture=new Image();
  ImageLoad("C:\\Users\\вягстос\\Desktop\\Planet textures\\SaturnRing.bmp",saturnringTexture);
  Image *uranusTexture=new Image();
  ImageLoad("C:\\Users\\вягстос\\Desktop\\Planet textures\\Uranus.bmp",uranusTexture);
  Image *uranusringTexture=new Image();
  ImageLoad("C:\\Users\\вягстос\\Desktop\\Planet textures\\UranusRing.bmp",uranusringTexture);
  Image *neptuneTexture=new Image();
  ImageLoad("C:\\Users\\вягстос\\Desktop\\Planet textures\\Neptune.bmp",neptuneTexture);
  Image *moonTexture=new Image();
  ImageLoad("C:\\Users\\вягстос\\Desktop\\Planet textures\\Moon.bmp",moonTexture);  
  
  textureID=new GLuint[12]; 
  glGenTextures(12,textureID);
  
  sun=gluNewQuadric();
  mercury=gluNewQuadric();
  venus=gluNewQuadric();
  earth=gluNewQuadric();
  mars=gluNewQuadric();
  jupiter=gluNewQuadric();
  saturn=gluNewQuadric();
  saturnring=gluNewQuadric();
  uranus=gluNewQuadric();
  uranusring=gluNewQuadric();
  neptune=gluNewQuadric();
  moon=gluNewQuadric(); 
 
  gluQuadricTexture(sun,GL_TRUE);
  gluQuadricTexture(mercury,GL_TRUE);
  gluQuadricTexture(venus,GL_TRUE);
  gluQuadricTexture(earth,GL_TRUE);
  gluQuadricTexture(mars,GL_TRUE);
  gluQuadricTexture(jupiter,GL_TRUE);
  gluQuadricTexture(saturn,GL_TRUE);
  gluQuadricTexture(saturnring,GL_TRUE);
  gluQuadricTexture(uranus,GL_TRUE);
  gluQuadricTexture(uranusring,GL_TRUE);
  gluQuadricTexture(neptune,GL_TRUE);
  gluQuadricTexture(moon,GL_TRUE); 
 
  glBindTexture(GL_TEXTURE_2D,textureID[0]);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,sunTexture->sizeX,sunTexture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,sunTexture->data);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,textureID[1]);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,mercuryTexture->sizeX,mercuryTexture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,mercuryTexture->data);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,textureID[2]);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,venusTexture->sizeX,venusTexture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,venusTexture->data);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,textureID[3]);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,earthTexture->sizeX,earthTexture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,earthTexture->data);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,textureID[4]);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,marsTexture->sizeX,marsTexture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,marsTexture->data);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,textureID[5]);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,jupiterTexture->sizeX,jupiterTexture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,jupiterTexture->data);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,textureID[6]);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,saturnTexture->sizeX,saturnTexture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,saturnTexture->data);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,textureID[7]);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,saturnringTexture->sizeX,saturnringTexture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,saturnringTexture->data);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,textureID[8]);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,uranusTexture->sizeX,uranusTexture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,uranusTexture->data);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,textureID[9]);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,uranusringTexture->sizeX,uranusringTexture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,uranusringTexture->data);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,textureID[10]);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,neptuneTexture->sizeX,neptuneTexture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,neptuneTexture->data);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,textureID[11]);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,moonTexture->sizeX,moonTexture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,moonTexture->data);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);  
     
           }

void reshape(int newWidth,int newHeight){
  
  printf("Reshape event detected.\n");  
  glViewport(0,0,(GLsizei) newWidth,(GLsizei) newHeight);
  glLoadIdentity();
  gluPerspective(0.5,(GLfloat) newWidth/(GLfloat) newHeight,300,100);
  glutPostRedisplay();
     
                                        }

void mouseButtonClicked(int button,int state,int x, int y){                                      
                                        
  if(state==GLUT_UP){                                      
   printf("Mouse click event detected (button up).\n");
   glLoadIdentity();                                     
   if(button==GLUT_LEFT_BUTTON){
    radius=radius+5;                                                                                         
    gluLookAt(a1*cos(angle/den1)+radius*sin(ZXangle)*cos(ZYangle),radius*sin(ZYangle),b1*sin(angle/den1)+radius*cos(ZXangle)*cos(ZYangle),a1*cos(angle/den1),0,b1*sin(angle/den1),0,1,0); 
                               }                                   
   else if(button==GLUT_RIGHT_BUTTON){
    if(radius-5<radMin)
     printf("Maximum zoom in.\n");
    else{     
     radius=radius-5;                                        
     gluLookAt(a1*cos(angle/den1)+radius*sin(ZXangle)*cos(ZYangle),radius*sin(ZYangle),b1*sin(angle/den1)+radius*cos(ZXangle)*cos(ZYangle),a1*cos(angle/den1),0,b1*sin(angle/den1),0,1,0); 
        }             
                                     }                               
                                        
                    }                    
        
  glutPostRedisplay();      
                                        
                                                          }
                                        
void specialKeys(int key,int x,int y){
  
  printf("Special key detected.\n");
  
  glLoadIdentity();
    
  if(key==GLUT_KEY_UP){                                         
   ZYangle=ZYangle-0.02;
   gluLookAt(a1*cos(angle/den1)+radius*sin(ZXangle)*cos(ZYangle),radius*sin(ZYangle),b1*sin(angle/den1)+radius*cos(ZXangle)*cos(ZYangle),a1*cos(angle/den1),0,b1*sin(angle/den1),0,1,0);           
                      }
  else if(key==GLUT_KEY_DOWN){                    
   ZYangle=ZYangle+0.02;
   gluLookAt(a1*cos(angle/den1)+radius*sin(ZXangle)*cos(ZYangle),radius*sin(ZYangle),b1*sin(angle/den1)+radius*cos(ZXangle)*cos(ZYangle),a1*cos(angle/den1),0,b1*sin(angle/den1),0,1,0);                                     
                             }
  else if(key==GLUT_KEY_RIGHT){
   ZXangle=ZXangle-0.02;
   gluLookAt(a1*cos(angle/den1)+radius*sin(ZXangle)*cos(ZYangle),radius*sin(ZYangle),b1*sin(angle/den1)+radius*cos(ZXangle)*cos(ZYangle),a1*cos(angle/den1),0,b1*sin(angle/den1),0,1,0);                                      
                              }
  else if(key==GLUT_KEY_LEFT){
   ZXangle=ZXangle+0.02;
   gluLookAt(a1*cos(angle/den1)+radius*sin(ZXangle)*cos(ZYangle),radius*sin(ZYangle),b1*sin(angle/den1)+radius*cos(ZXangle)*cos(ZYangle),a1*cos(angle/den1),0,b1*sin(angle/den1),0,1,0);                               
                             }
  else if(key==GLUT_KEY_F1){
   a1=40;   
   b1=38;
   den1=1;
   radMin=4;   
                           }
  else if(key==GLUT_KEY_F2){
   a1=55;   
   b1=51;
   den1=1.5;
   radMin=6;   
                           }
  else if(key==GLUT_KEY_F3){
   a1=70;     
   b1=64;
   den1=2;
   radMin=7;    
                           }
  else if(key==GLUT_KEY_F4){
   a1=85;   
   b1=77;
   den1=2.5;
   radMin=5;   
                           }
  else if(key==GLUT_KEY_F5){
   a1=100;   
   b1=90;
   den1=3;
   radMin=9;   
                           }
  else if(key==GLUT_KEY_F6){
   a1=120;     
   b1=108;
   den1=3.5;
   radMin=8;    
                           }
  else if(key==GLUT_KEY_F7){
   a1=145;   
   b1=131;
   den1=4;
   radMin=6;   
                           }
  else if(key==GLUT_KEY_F8){
   a1=170;   
   b1=154;
   den1=4.5;
   radMin=6;   
                           }
  else if(key==GLUT_KEY_F9){
   a1=0;     
   b1=0;
   radMin=37;    
                           }                    
                                        
  glutPostRedisplay();  

                                     }  

void animate(){
 
  angle=angle+0.005;   
  rotate=rotate+0.1;
   
  glLoadIdentity();
  gluLookAt(a1*cos(angle/den1)+radius*sin(ZXangle)*cos(ZYangle),radius*sin(ZYangle),b1*sin(angle/den1)+radius*cos(ZXangle)*cos(ZYangle),a1*cos(angle/den1),0,b1*sin(angle/den1),0,1,0);                       
  
  glutPostRedisplay();

              }

void SphereDesign(GLsizei DisplayListID,GLdouble radius,GLint slices,GLint stacks,GLuint a,GLuint b,GLfloat agl,GLfloat rte,GLUquadric *sphere,GLuint *texID){       
     
  glNewList(DisplayListID,GL_COMPILE);   
     
  glColor3f(1,1,1);   
  glPushMatrix();  
  glTranslatef(a*cos(agl),0,b*sin(agl));
  if(*texID==textureID[11])
   glTranslatef(7*cos(2*agl),0,7*sin(2*agl)); 
  glRotatef(rte,0,1,0);
  glRotatef(-90,1,0,0);
  glBindTexture(GL_TEXTURE_2D,*texID);
  gluSphere(sphere,radius,slices,stacks);
  glPopMatrix();

  glEndList();                                                                                
                                                                                                                                                             }        

void DiskDesign(GLsizei DisplayListID,GLdouble innerRadius,GLdouble outerRadius,GLint slices,GLint stacks,GLuint a,GLuint b,GLfloat agl,GLUquadric *disk,GLuint *texID){
     
  glNewList(DisplayListID,GL_COMPILE);     
     
  glColor3f(1,1,1);   
  glPushMatrix();
  glTranslatef(a*cos(agl),0,b*sin(agl));
  glRotatef(-90,1,0,0);
  glBindTexture(GL_TEXTURE_2D,*texID); 
  gluQuadricDrawStyle(disk,GLU_LINE);
  gluDisk(disk,innerRadius,outerRadius,slices,stacks);   
  glPopMatrix();   
     
  glEndList();             
                                                                                                                                                                       }                           

void EllipseDesign(GLsizei DisplayListID,GLfloat rx,GLfloat rz) {
     
  glNewList(DisplayListID,GL_COMPILE);  
     
  GLfloat angleStep=2*PI/(float)ellipsePoints;
  GLuint pointsPerQuarter=ellipsePoints/4;
  GLfloat x[ellipsePoints];
  GLfloat z[ellipsePoints];
  
  glColor3f(0,1,0);   
  
  glBegin(GL_LINE_LOOP);  
    for(i=0;i<pointsPerQuarter;i++){
     x[i]=rx*cos(i*angleStep);
     z[i]=rz*sin(i*angleStep);                                                                                                   
                                   } 
    for(i=0;i<pointsPerQuarter;i++){
     x[pointsPerQuarter+i]=-x[(pointsPerQuarter-1)-i];                            
     z[pointsPerQuarter+i]=z[(pointsPerQuarter-1)-i];                              
     
     x[2*pointsPerQuarter+i]=-x[i];
     z[2*pointsPerQuarter+i]=-z[i];  
     
     x[3*pointsPerQuarter+i]=x[(pointsPerQuarter-1)-i];
     z[3*pointsPerQuarter+i]=-z[(pointsPerQuarter-1)-i];                         
                                    } 
    for (i=0;i<ellipsePoints;i++){
     glVertex3f(x[i],0,z[i]);
                                 }     
  glEnd();   
     
  glEndList(); 
     
                                                                }
                                           
void display() {                                           
                                          
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   
  a=25;
  b=25;
  for(j=0;j<5;j++){
   a=a+15;
   b=b+13;                  
   EllipseDesign(listID,a,b);                                    
   glCallList(listID);
                  }              
  a=a+20;                
  b=b+18;                
  EllipseDesign(listID,a,b);                                    
  glCallList(listID);               
  for(j=0;j<2;j++){
   a=a+25;
   b=b+23;                 
   EllipseDesign(listID,a,b);                                    
   glCallList(listID);                 
                  } 
                                  
                     
  SphereDesign(listID+1,30,40,40,0,0,0,rotate/5,sun,&textureID[0]);                
  glCallList(listID+1);                 
  SphereDesign(listID+1,2,30,30,40,38,angle,rotate,mercury,&textureID[1]);             
  glCallList(listID+1);        
  SphereDesign(listID+1,4,30,30,55,51,angle/1.5,rotate/1.5,venus,&textureID[2]);             
  glCallList(listID+1);    
  SphereDesign(listID+1,5,30,30,70,64,angle/2,rotate/2.5,earth,&textureID[3]);             
  glCallList(listID+1);         
  SphereDesign(listID+1,3,30,30,85,77,angle/2.5,rotate/2,mars,&textureID[4]);             
  glCallList(listID+1); 
  SphereDesign(listID+1,7,30,30,100,90,angle/3,rotate/3.5,jupiter,&textureID[5]);             
  glCallList(listID+1);         
  SphereDesign(listID+1,6,30,30,120,108,angle/3.5,rotate/3,saturn,&textureID[6]);             
  glCallList(listID+1);
  DiskDesign(listID+2,7,10,30,30,120,108,angle/3.5,saturnring,&textureID[7]);
  glCallList(listID+2);    
  SphereDesign(listID+1,4,30,30,145,131,angle/4,rotate/1.5,uranus,&textureID[8]);             
  glCallList(listID+1);
  DiskDesign(listID+2,5,6,30,30,145,131,angle/4,uranusring,&textureID[9]);
  glCallList(listID+2);             
  SphereDesign(listID+1,4,30,30,170,154,angle/4.5,rotate/1.5,neptune,&textureID[10]);             
  glCallList(listID+1);
  SphereDesign(listID+1,1,30,30,70,64,angle/2,rotate,moon,&textureID[11]);             
  glCallList(listID+1);                                       
    
                    
  glutSwapBuffers();                                        
               }                           
                
int main(int argc, char** argv) {
  
 angle=0;
 rotate=0; 
 radius=60;
 ZXangle=1;
 ZYangle=2;
 a1=0;
 b1=0;
 radMin=37;
 den1=1;  
     
 glutInit(&argc,argv); 
 glutInitWindowPosition(100,100); 
 glutInitWindowSize(width,height); 
 glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); 
 glutCreateWindow("Solar_System");  
 glMatrixMode(GL_PROJECTION); 
 glOrtho(-200,200,-200,200,-200,200);
 gluPerspective(0.5,1.33333,300,100); 
 init();   
 glMatrixMode(GL_MODELVIEW);
 gluLookAt(radius*sin(ZXangle)*cos(ZYangle),radius*sin(ZYangle),radius*cos(ZXangle)*cos(ZYangle),a1,0,b1,0,1,0);  
 listID=glGenLists(3);
 glutDisplayFunc(display);
 glutIdleFunc(animate);
 glutSpecialFunc(specialKeys);
 glutMouseFunc(mouseButtonClicked);
 glutReshapeFunc(reshape);
 glutMainLoop(); 
 return(0);             
                                }             
                
                
                
