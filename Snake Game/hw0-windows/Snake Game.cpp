#include "util.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

long delay = 10000000;
int score = 0;
int background=2;


/* Function sets canvas size (drawing area) in pixels...
Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
*/
void SetCanvasSize(int width, int height) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

struct box
{
	int x;
	int y;
	int y_change;
	int x_change;
	int move;

	box()
	{
		x = 0;
		y = 0;
		y_change = 0;
		x_change = 0;
		move = 1;
	}

	box(int a, int b, int c, int d)
	{
		x = a;
		y = b;
		y_change = c;
		x_change = d;
	}

	void display()
	{
		DrawRoundRect(x, y, x_change, y_change, colors[DARK_MAGENTA]);
	}
};

//********* BALL *********//
struct ball
{
	int radius;
	int x;
	int y;
	int x_change;
	int y_change;
	bool visibility;

	ball(int position_x, int position_y)
	{
		x = position_x;
		y = position_y;
		radius = 8;
		x_change = 3;
		y_change = 3;
		visibility = true;
	}
	//drawing function for ball
	void drawball()
	{
		if (visibility)
			DrawCircle(x, y, radius, colors[5]);
	}
}b(250, 300); //variable of type ball


struct snake
{

	box *arr;   // Array of boxes
	int previous_X;
	int previous_Y;
	int move;
	int size;
	snake()
	{
		arr = NULL;
	}
	snake(int s)
	{
		size = s;
		arr = new box[size];
		for (int i = 0; i < size; ++i)
		{
			arr[i].y_change = 20;
			arr[i].x_change = 20;
			arr[i].x = 200;
			arr[i].y = 200;
		}
	}

	void snakeMove()
	{
		if (arr[0].x > 15 && arr[0].x+20 < 585 && arr[0].y>15 && arr[0].y+20 < 585)
		{
			
				previous_X = arr[0].x;
				previous_Y = arr[0].y;
				if (move == 1)
					arr[0].y += 7;
				else if (move == 2)
					arr[0].x += 7;
				else if (move == 3)
					arr[0].y -= 7;
				else if (move == 4)
					arr[0].x -= 7;

				for (int i = 1; i < size; ++i)
				{
					int holder1 = arr[i].x;
					int holder2 = arr[i].y;
					arr[i].x = previous_X;
					arr[i].y = previous_Y;
					previous_X = holder1;
					previous_Y = holder2;
				}
				return;
		}
		DrawString(150, 400, ">>>>>GAME OVER<<<<<", colors[DEEP_SKY_BLUE]);
		DrawString(140, 350, ">>>>>YOUR SCORE IS<<<<<", colors[CORN_FLOWER_BLUE]);
		
		char score_string[20];
		sprintf_s(score_string, "%d", score);
		DrawString(280, 320, score_string, colors[CADET_BLUE]);
	}
	void display(){
		for (int i = 0; i < size; ++i)
		{
			arr[i].display();
		}
	}
}s(15); //variable of type snake

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
* is pressed from the keyboard
*
* You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
*
* This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
* program coordinates of mouse pointer when key was pressed.
*
* */

void NonPrintableKeys(int key, int x, int y) 
{
	if (key == GLUT_KEY_LEFT&&s.move != 2 /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
	{
		s.move = 4;
	}
	else if (key == GLUT_KEY_RIGHT&&s.move!=4 /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) 
	{
		s.move = 2;
	}
	else if (key == GLUT_KEY_UP&&s.move!=3/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) 
	{
		s.move = 1;
	}

	else if (key == GLUT_KEY_DOWN&&s.move != 1/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/)
	{
		s.move = 3;
	}
	

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	* this function*/
	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
* is pressed from the keyboard
* This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
* program coordinates of mouse pointer when key was pressed.
* */
void PrintableKeys(unsigned char key, int x, int y) 
{
	if (key == KEY_ESC/* Escape key ASCII*/) 
	{
		exit(1); // exit the program when escape key is pressed.
	}
	glutPostRedisplay();
}


void Display()/**/
{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	if (background == 1)
	{
		glClearColor(0/*Red Component*/, 0/*Green Component*/,
			0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
	}
	else if (background == 2)
	{
		glClearColor(1/*Red Component*/, 1/*Green Component*/,
			1/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
	}

	else if (background == 3)
	{
		glClearColor(1/*Red Component*/, 1/*Green Component*/,
			0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
	}

	DrawRoundRect(0, 0, 600, 10, colors[LAWN_GREEN]);
	DrawRoundRect(590, 0, 10, 600, colors[LAWN_GREEN]);
	DrawRoundRect(0, 0, 10, 600, colors[LAWN_GREEN]);
	DrawRoundRect(0, 590, 600, 10, colors[LAWN_GREEN]);

	char score_string[20];
	sprintf_s(score_string, "%d", score);
	DrawString(20, 10, score_string, colors[BLACK]);
	
	int wd = 600;
	int ht = 600;
	if ((b.x <= 20) || (b.x >= wd - 20))
		b.x_change = b.x_change*-1;
	if ((b.y >= ht - 20) || (b.y <= 20))
			b.y_change = b.y_change*-1;

		s.display();
		s.snakeMove();
		b.drawball();
		b.x += b.x_change;
		b.y += b.y_change;
		

		if (b.x > s.arr[0].x && b.x<s.arr[0].x + 20 && b.y>s.arr[0].y && b.y < s.arr[0].y + 20)
		{
			b.visibility = false;
			score += 5;
			if(score%50==0)
			delay -= 600000;
			b.x = 20 + (rand() % 560);//because radius of the ball is 8
			b.y = 20 + (rand() % 560);
			b.visibility = true;
		}

		//  FOR TIMER****************
		int count = 0;
		while (count <= delay)
		{
			count++;
		}

		glutPostRedisplay();

		// TIMER ENDS*****************

		glutSwapBuffers();
	}

int menu() 
{
	int option;
	system("COLOR 50");
	system("cls");
	printf("\t\t\t\tTHE GAME\n\n\n");
	printf("1. Press 1 to Play.\n2. Press 2 for Instructions.\n3. Press 3 for Options.\n");
	scanf_s("%d", &option);
	return option;
}





/*************************************************************************************************************************/



int main(int argc, char*argv[])
{
	int option;
	do 
	{
		option = menu();
		if (option == 1) 
		{
			int width = 600, height = 600; // i have set my window size to be 800 x 600
			srand(time(NULL)); // seed the random number generator...
			glutInit(&argc, argv); // initialize the graphics library...

			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
			glutInitWindowPosition(50, 50); // set the initial position of our window
			glutInitWindowSize(width, height); // set the size of our window
			glutCreateWindow("Snake Game"); // set the title of our game window
			SetCanvasSize(width, height); // set the number of pixels...


			// Register your functions to the library,
			// you are telling the library names of function to call for different tasks.
			//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
			glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
			glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
			glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
			

			// now handle the control to library and it will call our registered functions when
			// it deems necessary...
			glutMainLoop();
			return 0;
		}
		else if (option == 2)
		{
			system("cls");
			printf("\t\t\t\tInstructions:\n\n1. Do not touch the window edges\n2. Use the arrow keys for movement.\n");
			printf("3. Catch the moving ball to earn points.\n4. Every time you catch the ball the speed increases.");
			getchar();
			getchar();
		}
		else if (option == 3)
		{
			system("cls");
			printf("\n\nPress the respective number for background colour!\n\n\tBLACK=1\t\tWHITE=2\t\tYELLOW=3\n");
			scanf("%d", &background);
		}
	} while (option!=1);	
}