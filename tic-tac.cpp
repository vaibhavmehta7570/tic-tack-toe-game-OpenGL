// skk_ttt_v3.0.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <GL/glut.h>  // Glut (gl utility toolkit) basic windows functions, keyboard, mouse.
#include <stdio.h>    // Standard (I/O library)
#include <stdlib.h>   // Standard library (set of standard C functions
#include <math.h>     // Math library (Higher math functions )
#include <string.h>	  // String library
int p[3]={0,0,0};
int ch=0;			// Color Scheme Choice
int board[3][3];	// Board for gameplay
int turn;			// Current move
int result;			// Result of the game
bool over;			// Is the game Over?
GLfloat v[5][4][3]={
	{{0,0,0},{0.984375,0.289063,0.101563},{0.964844,0.714844,0.199219},{1,1,1}},
	{{0.184314,0.309804,0.309804},{1,1,1},{0,0,0},{0,0,0}},	
	{{0,0.74902,1},{0.678431,1,0.184313},{1,1,0},{0.678431,0,0.184314}},
	{{1,0.611765,0.356862},{0.929411,0.188235,0.235294},{0.231372,0.505882,0.513725},{0.960784,0.388235,0.290196}},
	{{0.941176,0.847059,0.658823},{0.949019,0.839215,0.580392},{0.980392,0.164706,0},{0.525490,0.721568,0.694117}}
				};

char *pint(int i)
{
	switch(i)
	{
	 case 0:
		 return " 0 ";
		 break;
	 case 1:
		return " 1 ";
		 break;
	 case 2:
		return " 2 ";
		 break;
	 case 3: 
		 return " 3 ";
		 break;
	 case 4:
		 return " 4 ";
		 break;
	 case 5:
		 return " 5 ";
		 break;
	 default:
		 return "NA";
	}
}
//	Sets the board for Tic Tac Toe
void Intialize()
{
	turn=1;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			board[i][j]=0;
}
//	Called when any key from keyboard is pressed
void Keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 'y':
		if(over==true)
		{			
			if(result==0)
				p[0]++;
			else if(result==1)
				p[1]++;
			else if(result==2)
				p[2]++;
			over=false;
			Intialize();
		}
		break;
		case 'n':
		if(over==true)
			exit(0);
		break;

		default:
			exit(0);
	}
}
//	Called when Mouse is clicked 
void Mouse(int button,int state,int x,int y)	
{
	if(over==false && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		if(turn==1)
		{
			if(board[(y-50)/100][x/100]==0)
			{
				board[(y-50)/100][x/100]=1;
				turn=2;
			}
		}
		else if(turn==2)
		{
			if(board[(y-50)/100][x/100]==0)
			{
				board[(y-50)/100][x/100]=2;
				turn=1;
			}
		}
	}	
}
//	Utility function to draw string 	
void DrawString(void *font,const char s[],float x,float y)
{
	unsigned int i;
	glColor3fv(v[ch][3]);
	glRasterPos2f(x,y);
	for(i=0;i<strlen(s);i++)
	{
		glutBitmapCharacter(font,s[i]);
	}
}
//	Function to draw up the horizontal and vertical lines
void DrawLines()
{	 
	glLineWidth(4.0);
	glBegin(GL_LINES);
	   glColor3fv(v[ch][0]);	
	   
	    glVertex2f(2,50);
		glVertex2f(2,380);

		glVertex2f(100,50);
		glVertex2f(100,410);

		glVertex2f(200,50);
		glVertex2f(200,410);

		glVertex2f(299,50);
		glVertex2f(299,380);

		glVertex2f(50,350);
		glVertex2f(50,380);

		glVertex2f(150,350);
		glVertex2f(150,380);

		glVertex2f(250,350);
		glVertex2f(250,380);


	      glVertex2f(0,50);
		  glVertex2f(300,50);
		  
		  glVertex2f(0,150);
		  glVertex2f(300,150);

		  glVertex2f(0,250);
		  glVertex2f(300,250);

		  glVertex2f(0,350);
		  glVertex2f(300,350);

		  glVertex2f(0,380);
		  glVertex2f(300,380);
			
		  glVertex2f(100,410);
		  glVertex2f(200,410);

	glEnd();
	glLineWidth(1.f);
}
//	Utility function to draw the circle
void DrawCircle(float cx, float cy, float r, int num_segments) 
{
	glColor3fv(v[ch][1]);
	glLineWidth(5.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++)   
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 
        glVertex2f(x + cx, y + cy);//output vertex 
    }
    glEnd();
	glLineWidth(1.f);
}
//	Function to draw the cross and circle of Tic Tac Toe
void DrawXO()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(board[i][j]==1)
			{
				glColor3fv(v[ch][2]);
				glLineWidth(3.0);
				glBegin(GL_LINES);
				glVertex2f(50 + j * 100 - 25, 100 + i * 100 - 25);
				glVertex2f(50 + j * 100 + 25, 100 + i * 100 + 25);
				glVertex2f(50 + j * 100 - 25, 100 + i * 100 + 25);
				glVertex2f(50 + j * 100 + 25, 100 + i * 100 - 25);
				glEnd();
			}
			else if(board[i][j]==2)
			{				
				DrawCircle(50 + j*100 , 100 + i*100 , 25 , 15);
			}
		}
	}
	glLineWidth(1.f);
}
//	Function to check if there is any winner 
bool CheckWinner()
{
	int i, j;	
	for(i=0;i<3;i++)// horizontal check
	{
		for(j=1;j<3;j++)
		{
			if(board[i][0]!=0 && board[i][0]==board[i][j])
			{
				if(j==2)
				{
					return true;
				}
			}
			else
				break;
		}
	}	
	for(i=0;i<3;i++)// vertical check
	{
		for(j=1;j<3;j++)
		{
			if(board[0][i]!=0 && board[0][i]==board[j][i])
			{
				if(j==2)
					return true;
			}
			else
				break;
		}
	}	
	if(  (board[0][0]!=0 && board[0][0]==board[1][1] && board[0][0]==board[2][2]) 
	  || (board[2][0]!=0 && board[2][0]==board[1][1] && board[2][0]==board[0][2])  )  // Diagonal check
		return true;
	return false;
}
//	Function to check if there is draw
bool CheckIfDraw()
{
	int i, j;
	bool draw;
	for(i=0;i<3;i++)
	{ 
		for(j=0;j<3;j++)
		{ 
			if(board[i][j]==0)
				return false;
		}
	}
	return true;	
}
//	Function to display up everything
void Display()
{

	glClear(GL_COLOR_BUFFER_BIT);
	if(turn == 1)
		DrawString(GLUT_BITMAP_TIMES_ROMAN_24, "X's Turn", 105, 20);	
	else
		DrawString(GLUT_BITMAP_TIMES_ROMAN_24, "O's Turn", 105, 40);	
	DrawLines();
	DrawXO();	
	if(CheckWinner() == true)
	{
		if(turn == 1)
		{
			over = true;
			result = 2; 
		}
		else
		{
			over = true;
			result = 1; 
		}
	}
	else if(CheckIfDraw() == true)
	{
		over = true;
		result = 0;
	}
	if(over == true)
	{	
		if(result == 0)
			DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw", 107, 400);
		if(result == 1)		
			DrawString(GLUT_BITMAP_HELVETICA_18, "X wins", 125, 400);
		if(result == 2)		
			DrawString(GLUT_BITMAP_HELVETICA_18, "O wins", 125, 400);
		DrawString(GLUT_BITMAP_HELVETICA_18, "Press 'y' to Continue | 'n' to Exit ", 20, 430);
	}	
		DrawString(GLUT_BITMAP_TIMES_ROMAN_24,"X",18,372);
		//DrawString(GLUT_BITMAP_HELVETICA_18,pint(p[1]),62,370);
		DrawString(GLUT_BITMAP_TIMES_ROMAN_24,"O",118,372);
		DrawString(GLUT_BITMAP_HELVETICA_18,pint(p[2]),162,370);
		DrawString(GLUT_BITMAP_TIMES_ROMAN_24,"D",218,372);
		DrawString(GLUT_BITMAP_HELVETICA_18,pint(p[0]),262,370);
	glutSwapBuffers();
}
//	Function to reshape
void Reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}
//	Function for menu
void game(int id)
{
 switch(id)
 {  
  case 1:
	 ch=0;
	 glClearColor(0.287933,0.735398,0.669251,1.0);
	  break;
  case 2:
	 ch=1;
	 glClearColor(0,0.501961,0.501961,1.0);
	  break;
  case 3:
	 ch=2;
	 glClearColor(1,0.411765,0.705883,1.0);
	  break;
  case 4:
	 ch=3;
	 glClearColor(0.980392,0.815686,0.537255,1.0);
	  break;
  case 5:	
	 ch=4;
	 glClearColor(0.239216,0.109804,0,1.0);
	  break;
  case 6:	
	  exit(0);
 }
}
int main(int argc, char **argv)
{
	Intialize();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(550,200);
	glutInitWindowSize(300,450);
	
	glutCreateWindow("Tic Tac Toe");
	glutCreateMenu(game);
	glutAddMenuEntry("[Themes]",0);
	glutAddMenuEntry("Fun and Learning",1);
   	glutAddMenuEntry("Google",2);
    	glutAddMenuEntry("Kid Mode",3);
	glutAddMenuEntry("Cohesive Colors-I",4);
	glutAddMenuEntry("Cohesive Colors-II",5);
	glutAddMenuEntry("Exit",6);
    	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutIdleFunc(Display);
	
	glClearColor(0.287933,0.735398,0.669251,1.0);
	
    glutMainLoop();

    return 0;
}





