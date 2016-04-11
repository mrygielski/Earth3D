// EARTH by MICHA£ RYGIELSKI
// 15 wrzeœnia 2002 r.

#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include "ggate.h"

font_ttf font;

GLuint texture[1];

float xrot=-70, yrot=15, zrot=10;

float zoom=-5.0f, right=1.0f;

float sx=0, sy=0, sz=0;

GLUquadricObj *quadratic, *quadratic2;

void DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();						
	glTranslatef(right,0.0f,zoom);

	glRotatef(zrot,1.0f,0.0f,0.0f);
//	glRotatef(yrot,0.0f,1.0f,0.0f);
//	glRotatef(zrot,0.0f,0.0f,1.0f);

	SetTextures(true);



	glBindTexture(GL_TEXTURE_2D, texture[0]);
	gluSphere(quadratic,1.3f,32,32 );

	zrot+=1;

	//glLoadIdentity();						
	//glTranslatef(right,-1.0f,zoom);
	
	//gluSphere(quadratic2,0.3f,32,32);

	

	SetTextures(false);

	glLoadIdentity();

	glTranslatef(0,0,-0.15f);
	
	glColor3ub(255,0,0);
	glPrint(-0.082f,0.06f,0,255,255,255,font,"EARTH by MICHA£ /REGi/ RYGIELSKI");
	glPrint(-0.082f,0.055f,0,255,255,255,font,"Klawisze:");
	glPrint(-0.082f,0.055f-0.003f,0,255,255,255,font,"- zoom Q i A");
	glPrint(-0.082f,0.055f-0.006f,0,255,255,255,font,"- xrot W i S");
	glPrint(-0.082f,0.055f-0.009f,0,255,255,255,font,"- yrot E i D");
	glPrint(-0.082f,0.055f-0.012f,0,255,255,255,font,"- reset R");
}


int WINAPI WinMain(	HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int			nCmdShow)
{

	MSG		msg;
	BOOL	done=FALSE;
	
	if (CreateGLWindow("Earth by Micha³ Rygielski",800,600,16,fullscreen)==FALSE)
	{
		return 0;
	}
	

	// TEKSTURY
	texture[0]=LoadTexture("earth.bmp",2);
		
	quadratic=gluNewQuadric(); 
	gluQuadricNormals(quadratic, GLU_NONE);
	gluQuadricTexture(quadratic, GL_TRUE); 
	quadratic2=gluNewQuadric(); 
	gluQuadricNormals(quadratic2, GLU_NONE);
	gluQuadricTexture(quadratic2, GL_TRUE); 


	// CZCIONKI
	font=BuildFont(12,6,FONT_1,FALSE,FALSE,FALSE,"Arial CE");

	while(!done)
	{
	if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
			{
				done=TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			
			DrawGLScene();
			SwapBuffers(hDC);		
			
			if (keys[VK_ESCAPE])
			{
				done=TRUE;
			}
			if (keys['Q'] && zoom>-9.0f) zoom-=0.02f;
			if (keys['A'] && zoom<-2.5f) zoom+=0.02f;
			if (keys['R'])
			{
				xrot=-70; yrot=15; zrot=10;
			}

			if (keys['W']) xrot-=0.5f;
			if (keys['S']) xrot+=0.5f;

			if (keys['E']) yrot-=0.5f;
			if (keys['D']) yrot+=0.5f;
		}
	}

	// Shutdown
	KillFont(font);

	KillGLWindow();
	return (msg.wParam);
}