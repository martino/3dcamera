#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float angleX  = 0.0f, angleY  = 0.0f;
float angleTX = 0.0f, angleTY = 0.0f;
float angleMX = 0.0f, angleMY = 0.0f;
float width,height;
float lX, lY;
const float piover180 = 0.0174532925f;
int frame,time,timebase=0,timerender=0;
float xpos = 0.0f, zpos = 0.0f, ypos = 0.0f;
int dir = 0;
float movey=100.0f, movex=100.0f;
int ud = 0, lr = 0, lud = 0;
int lastkey = 0;
float xlast=0.0f, ylast = 0.0f;
char wTitle[20];
GLint fullscreen=0;



/* funzione che fa il pavimento a scacchiera */
void DrawGroundQuad(GLfloat y, int s){
  GLfloat zg = -24.0f;
  GLfloat xg = -24.0f;
  GLfloat yg = y;
  int i=0,j=0;
  for(i=0; i<48; i++){
    for(j=0; j<48; j++){
      glBegin(GL_QUADS);
      if((i+s)%2==0){
	if((j+s)%2==0)
	  glColor3f(1.0f, 0.0f, 0.0f);
	else
	  glColor3f(0.0f, 0.0f, 1.0f);
      }else{
	if((j+s)%2==0)
	  glColor3f(0.0f, 0.0f, 1.0f);
	else
	  glColor3f(1.0f, 0.0f, 0.0f);
      }
      
      glVertex3f(xg, yg, zg);
      glVertex3f(xg+1.0f, yg, zg);
      
      glVertex3f(xg+1.0f, yg, zg+1.0f);
      glVertex3f(xg, yg, zg+1.0f);
      
      glEnd();
      xg+=1.0f;
    }
    xg = -24.0f;
    zg+=1.0f;
  }
}

/* funzione che fa la parete sull asse Z a scacchiera */
void DrawWallQuadZ(GLfloat z, int s){
  GLfloat zg = z;
  GLfloat xg = -24.0f;
  GLfloat yg = -24.0f;
  int i=0,j=0;
  for(i=0; i<48; i++){
    for(j=0; j<48; j++){
      glBegin(GL_QUADS);
      if((i+s)%2==0){
	if((j+s)%2==0)
	  glColor3f(1.0f, 1.0f, 0.0f);
	else
	  glColor3f(0.0f, 1.0f, 1.0f);
      }else{
	if((j+s)%2==0)
	  glColor3f(0.0f, 1.0f, 1.0f);
	else
	  glColor3f(1.0f, 1.0f, 0.0f);
      }
      
      glVertex3f(xg, yg, zg);
      glVertex3f(xg+1.0f, yg, zg);
      
      glVertex3f(xg+1.0f, yg+1.0f, zg);
      glVertex3f(xg, yg+1.0f, zg);
      
      glEnd();
      xg+=1.0f;
    }
    xg = -24.0f;
    yg+=1.0f;
  }
}

/* funzione che fa la parete sull asse X a scacchiera */
void DrawWallQuadX(GLfloat x, int s){
  GLfloat zg = -24.0f;
  GLfloat xg = x;
  GLfloat yg = -24.0f;
  int i=0,j=0;
  for(i=0; i<48; i++){
    for(j=0; j<48; j++){
      glBegin(GL_QUADS);
      if((i+s)%2==0){
	if((j+s)%2==0)
	  glColor3f(0.0f, 1.0f, 0.0f);
	else
	  glColor3f(1.0f, 0.0f, 0.0f);
      }else{
	if((j+s)%2==0)
	  glColor3f(1.0f, 0.0f, 0.0f);
	else
	  glColor3f(0.0f, 1.0f, 0.0f);
      }
      
      glVertex3f(xg, yg, zg);
      glVertex3f(xg, yg, zg+1.0f);
      
      glVertex3f(xg, yg+1.0f, zg+1.0f);
      glVertex3f(xg, yg+1.0f, zg);
      
      glEnd();
      zg+=1.0f;
    }
    zg = -24.0f;
    yg+=1.0f;
  }
}

void renderScene(){
  int moveframe = 0;
  frame++;


  time = glutGet(GLUT_ELAPSED_TIME);
/*   fprintf(stderr, "time: %d \n", time); */
  if(time-timebase > 1000){
    sprintf(wTitle, "FPS: %.0f",frame*1000.0/(time-timebase) );
    glutSetWindowTitle(wTitle);
    //		fprintf(stdout, "FPS: %4.2f \n", frame*1000.0/(time-timebase));
    timebase = time;
    frame = 0;
  }

  if(time-timerender > 500){
    /* tempo da correggere */
    moveframe = 1;
    timerender = time + ((time-timerender)-500);
  }

/*   xpos -= (float)sin(angleX*piover180) * 0.010f; */
/*   ypos -= (float)sin(angleY*piover180) * 0.010f; */
/*   zpos -= (float)cos(angleX*piover180) * 0.010f; */
  if(dir==0){
    int kmov = 1;
    //fa l'effetto di moveimento lento
    // e' qui dato che la dir e' 0 quando si ritorna sul piano "orizzontale"
    //va in basso/alto
    /* if((angleTX == angleX)&&(angleY != angleTY)){ */
    if((angleY != angleTY)){
      movey++;
      if((ud==0)&&((lastkey==1)||(lud==2))){
	angleY -= 3.0f;
	if(angleY<angleTY)
	  angleY = angleTY;
      }   
      if((ud==0)&&((lastkey==2)||(lud==1))){
	angleY += 3.0f;
	if(angleY>angleTY)
	  angleY = angleTY;
      }
      kmov = 0;
      angleMY = angleY;
    }else{
      if(angleY==angleTY){
	lud = 0;	
      }

    }
    //muove lateralmente
    if(angleTX!=angleX){
      movex++;
      if(lud==0){
	if(lr==1){
	  angleX -= 3.0f;
	  if(angleX<angleTX)
	    angleX = angleTX;
	}
	if(lr==2){
	  angleX += 3.0f;
	  if(angleX>angleTX)
	    angleX = angleTX;

	}
      }else{
	if(lr==1){
	  angleX -= 3.0f;
	  if(angleX<angleTX)
	    angleX = angleTX;
	}
	if(lr==2){
	  angleX += 3.0f;
	  if(angleX>angleTX)
	    angleX = angleTX;

	}
	
      }
      kmov = 0;
      angleMX = angleX;
    }
    
    if(kmov && moveframe){
      //muove sul piano x
      xpos -= (float)sin(angleX*piover180) * 1.05f;
      zpos -= (float)cos(angleX*piover180) * 1.05f;
      moveframe = 0;
    }
  }else{
    int translate = 1;
    //prima di tutto bisogna controllare che anche l'angolo X sia a 0
    // sistema la visuale prima di salire
    if((angleX!= angleMX)&&(isBusy())){
      if(angleX<angleMX){
	angleMX-=3.0f;
	if(angleMX<angleX)
	  angleMX= angleX;
      }

      if(angleX>angleMX){
	angleMX+=3.0f;
	if(angleMX>angleX)
	  angleMX= angleX;
      }
      translate = 0;
    }

    // fa l'effetto di movimento lento alto basso
/*     if((angleX == angleMX)&&(angleTY != angleY)){ */
    if((angleTY != angleY)){
      movey++;
      if(ud==1){ //va in su
	angleY -= 3.0f;
	if(angleY<angleTY)
	  angleY = angleTY;
      }
      if(ud==2){ //va in giu'
	angleY += 3.0f;
	if(angleY>angleTY)
	  angleY = angleTY;
      }
      angleMY = angleY;
      translate = 0;
    }else{
      translate = 1;
    }


    if(translate && moveframe){
      //      angleTY = angleY;
      //muove sul piano y
      ypos += (float)sin(angleY*piover180) * 1.05f;
      zpos += (float)cos(angleY*piover180) * 1.05f;
      moveframe = 0;
    }

  }

  
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  
  
  //telecamera
  /*
    la rotate di solito utilizza angleMX e angleMY ma se c'e' uno spostamento
    deve utilizzare angleY e angleX

   */

  glRotatef(angleMY, 1.0f, 0.0f, 0.0f);
  glRotatef(angleMX, 0.0f, 1.0f, 0.0f);

  /*
    la translate la deve sempre fare utilizzando angleX e angleY
   */
  glTranslatef(xpos, ypos, -zpos);
  
  DrawGroundQuad(-12.0f,0);
  DrawGroundQuad(12.0f,1);
  DrawWallQuadZ(12.0f, 0);
  DrawWallQuadZ(-12.0f, 1);
  DrawWallQuadX(12.0f, 0);
  DrawWallQuadX(-12.0f, 1);
  glColor3f(1.0f, 1.0f, 0.0f);
  glPushMatrix();
  glTranslatef(-0.5f, 0.0f, -6.5f);
  glutSolidCube(0.1);
	
  glPopMatrix();
	
  glColor3f(1.0f, 0.0f, 0.0f);
  glPushMatrix();
  glTranslatef(-0.5f, 0.0f, 6.5f);
  glutSolidCube(0.1);
	
  glPopMatrix();
	
  glColor3f(0.0f, 1.0f, 0.0f);
  glPushMatrix();
  glTranslatef(-6.5f, 0.0f, 0.0f);
  glutSolidCube(0.1);
	
  glPopMatrix();
	
  glColor3f(0.0f, 0.0f, 1.0f);
  glPushMatrix();
  glTranslatef(6.5f, 0.0f, 0.0f);
  glutSolidCube(0.1);
	
  glPopMatrix();
	
  glutSwapBuffers();
	
	
}

void changeSize(int w, int h){
  float ratio = 0.0f;
  if(h == 0)
    h = 1;

  width = w;
  height = h;
	
  xlast = w/2;
  ylast = h/2;
  ratio = 1.0 * w / h;

  glutWarpPointer(width /2, height / 2);
  glutSetCursor(GLUT_CURSOR_NONE);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	
  glMatrixMode(GL_MODELVIEW);
	
	
}

int isBusy(){
  if((angleTX!=angleX)||(angleTY!=angleY))
    return 1;
  else
    return 0;
}

void processMouse(int x, int y) {
  /*fprintf(stdout, "processMouse\n");
    float tmpX = 0.0f;
    float tmpY = 0.0f;
	
    tmpX =  (width / 2) - x ;
    tmpY =  y - (height/2) ;
		
    angleX += tmpX*0.1f;
    angleY += tmpY*0.1f; 
	
    fprintf(stdout, "angleX %f  angleY %f tmpX %f  tmpY %f\n", angleX, angleY, tmpX, tmpY);


    tmpX = (xlast - x)*0.5f;
    tmpY = (ylast - y)*0.5f;

    angleX += tmpX;
    angleY += tmpY;
	
    glutPostRedisplay();
    fprintf(stdout, "angleX %f  angleY %f  x %d xlast %f tmpX %f \n", angleX, angleY, x, xlast, tmpX);
    glutWarpPointer(width /2, height / 2);
    ylast = height/2;
    xlast = width/2;
	
    /*xlast = x;
    ylast = y;
	
    if( (xlast < 0) || (xlast >= width-1)){
    glutWarpPointer(width /2, height / 2);
    ylast = height/2;
    xlast = width/2;
    }
    if( (ylast < 0) || (ylast >= height-1)){
    glutWarpPointer(width /2, height / 2);
    ylast = height/2;
    xlast = width/2;
    }*/
  if(isBusy()) return;
	
  float tmpX = 0.0f;
  float tmpY = 0.0f;

  tmpX =  x - (width / 2);
  tmpY =  y - (height/2) ;

  if( (tmpX == 0.0) && (tmpY == 0.0) )
    return;

  angleMX += tmpX*0.25f;
  angleMY += tmpY*0.25f;

  //limito il mouse in modo che non discosti mai di 45 gradi
  if( (angleMY > (angleY+45.0f)) ||  (angleMY< (angleY-45.0f) ))
    angleMY -= tmpY*0.25f;

  if( (angleMX > (angleX+45.0f)) ||  (angleMX< (angleX-45.0f) ))
    angleMX -= tmpX*0.25f;



  /*	fprintf(stderr, "X %d Y %d\n", x, y);
	fprintf(stderr, "tmpX %f  tmpY %f\n", tmpX, tmpY);
	fprintf(stderr, "angleX %f  angleY %f\n", angleX, angleY);*/
  glutWarpPointer(width /2, height / 2);
  

}

void keyFunc(int key, int x, int y){
  if(isBusy()) return;

  if(key == GLUT_KEY_UP){
    if((lastkey!=1)||(ud==0)){
/*       angleY -= 90.0f; */
       movey = 1; 
      angleTY = angleY - 90.0f;
/*       if((angleY<angleMY)&&(angleMY<angleTY)) */
      angleY = angleMY;

      if(dir==0){
	dir++;
	ud = 1;
      }else{
	dir--;
	ud = 0;
      }
      lastkey = 1;
    }
/*     xpos -= (float)sin(angleX*piover180) * 0.10f; */
/*     ypos -= (float)sin(angleY*piover180) * 0.10f; */
/*     zpos -= (float)cos(angleX*piover180) * 0.10f; */
  }
		
  if(key == GLUT_KEY_DOWN){
    if((lastkey!=2)||(ud==0)){
/*       angleY += 90.0f; */
/*       movey = 1; */
      angleTY = angleY + 90.0f;
/*       fprintf(stderr, "X %f -  MX %f -  TX %f\n", angleY, angleMY, angleTY); */
      angleY = angleMY;
      if(dir==0){
	dir ++;
	ud = 2;
      }else{
	dir--;
	ud = 0;
      }
      lastkey = 2;
    }
/*     xpos += (float)sin(angleX*piover180) * 0.10f; */
/*     ypos += (float)sin(angleY*piover180) * 0.10f; */
/*     zpos += (float)cos(angleX*piover180) * 0.10f; */
  }

  if(key == GLUT_KEY_LEFT){
/*     fprintf(stderr, "X %f -  MX %f -  TX %f\n", angleX, angleMX, angleTX); */

      if(ud == 2){
/* 	angleY -= 90.0f; */
/* 	angleX -= 90.0f; */
/* 	movey = 1; */
	angleTY = angleY - 90.0f;
	angleY = angleMY;
	lud = 2;
/* 	ypos += (float)sin(angleY*piover180) * 0.015f; */
/* 	zpos += (float)cos(angleY*piover180) * 0.015f; */
	ud = 0;
      }

      if(ud == 1){
/* 	angleY += 90.0f; */
/* 	angleX -=90.0f; */
/* 	movey = 1; */
	angleTY = angleY + 90.0f;
	angleY = angleMY;
	lud = 1;
/* 	ypos += (float)sin(angleY*piover180) * 0.015f; */
/* 	zpos += (float)cos(angleY*piover180) * 0.015f; */
	ud = 0;
      }
/*       movex = 1; */
      angleTX = angleX - 90.0f;
      angleX = angleMX;
      /* angleX -= 90.0f; */
      
      dir = 0;
      lr = 1;
      lastkey = 3;
/*     xpos -= (float)sin(angleX*piover180) * 0.10f; */
/*     ypos -= (float)sin(angleY*piover180) * 0.10f; */
/*     zpos -= (float)cos(angleX*piover180) * 0.10f; */
  }
		
  if(key == GLUT_KEY_RIGHT){

      if(ud == 2){
/* 	angleY -= 90.0f; */
/* 	movey = 1; */
	angleTY = angleY - 90.0f;
	angleY = angleMY;
	lud = 2;
/* 	ypos += (float)sin(angleY*piover180) * 0.015f; */
/* 	zpos += (float)cos(angleY*piover180) * 0.015f; */
	ud = 0;
      }

      if(ud == 1){
/* 	angleY += 90.0f; */
/* 	movey = 1; */
	angleTY = angleY + 90.0f;
	angleY = angleMY;
	lud = 1;
/* 	ypos += (float)sin(angleY*piover180) * 0.015f; */
/* 	zpos += (float)cos(angleY*piover180) * 0.015f; */
	ud = 0;
      }

/*       movex = 1; */
      angleTX = angleX + 90.0f;
      angleX = angleMX;
/*       angleX += 90.0f; */
      lr = 2;
      dir = 0;
      lastkey = 4;

/*     xpos += (float)sin(angleX*piover180) * 0.10f; */
/*     ypos += (float)sin(angleY*piover180) * 0.10f; */
/*     zpos += (float)cos(angleX*piover180) * 0.10f; */
  }
	
  if(key == 'q'){
    fprintf(stderr, "esco\n");
    exit(0);
  }
	
}

void nkeyFunc(unsigned char key, int x, int y){

  if(key == 'w'){
    xpos -= (float)sin(angleX*piover180) * 0.15f;
    zpos -= (float)cos(angleX*piover180) * 0.15f;
  }
		
  if(key == 's'){
    xpos += (float)sin(angleX*piover180) * 0.15f;
    zpos += (float)cos(angleX*piover180) * 0.15f;
  }
  if(key == 'e'){
    ypos += (float)sin(angleY*piover180) * 0.15f;
    zpos += (float)cos(angleY*piover180) * 0.15f;
  }
		
  if(key == 'd'){
    ypos -= (float)sin(angleY*piover180) * 0.15f;
    zpos -= (float)cos(angleY*piover180) * 0.15f;
  }
	 
  if(key == 'o'){
    fprintf(stderr, "Enter in fullscreen mode\n");
    /* glutGameModeString("1440x900:16");
       glutEnterGameMode();*/
    fullscreen = 1;
  }
	
  if(key == 'q'){
    fprintf(stderr, "esco\n");
/*     if(fullscreen==1) */
/*       glutLeaveGameMode(); */
    exit(0);
  }
	
}

void TimerFunc(int value){
  glutPostRedisplay();
  glutTimerFunc(16, TimerFunc, 0);
}


int main(int argc, char * argv[]){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(800,600);
	
  glutCreateWindow("treddicamera");
	 
  glutDisplayFunc(renderScene);
  glutReshapeFunc(changeSize);

  glutPassiveMotionFunc(processMouse);
  glutSpecialFunc(keyFunc);
  glutKeyboardFunc(nkeyFunc);

	
  glutTimerFunc(33, TimerFunc, 1);
	
  glutMainLoop();
  return 0;
}
