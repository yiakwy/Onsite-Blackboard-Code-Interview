#include "Axis.h"
#include <math.h>

void glprimitives::dim3::drawgrid(void){
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	for(float x = -10; x <= 10; x++){
		if( x == 0 ){
			glColor3f(0,0,0);
			glVertex3f(x, 0, -10);
			glVertex3f(x, 0, 10);
			glColor3f(1,1,1);
		}
		else{
			glVertex3f(x, 0, -10);
			glVertex3f(x, 0, 10);		
		}

	}

	for(float z = -10; z <= 10; z++){
		if( z == 0 ){
			glColor3f(0,0,0);
			glVertex3f(-10, 0, z);
			glVertex3f(10, 0, z);
			glColor3f(1,1,1);
		}
		else{
		glVertex3f(-10, 0, z);
		glVertex3f(10, 0, z);		
		}

	}
	glEnd();
}

void glprimitives::dim2::drawgrid(void)
{
    glColor3f(1, 1, 1);
    const float width = 25;
    glBegin(GL_LINES);
    for(float x = -width; x <= width; x++){
        if( x == 0 ){
            glColor3f(0,0,0);
            glVertex2f(x, -width);
            glVertex2f(x, width);
            glColor3f(1,1,1);
        }
        else{
            glVertex2f(x, -width);
            glVertex2f(x, width);
        }
        
    }
    
    for(float z = -width; z <= width; z++){
        if( z == 0 ){
            glColor3f(0,0,0);
            glVertex2f(-width, z);
            glVertex2f(width, z);
            glColor3f(1,1,1);
        }
        else{
            glVertex2f(-width, z);
            glVertex2f(width, z);
        }
        
    }
    glEnd();
}

void glprimitives::dim3::Drawcone(float x, float y, float z){
	float res = 360;
	float d = 2 * PI / 360;
	float a = 0;
	glColor3f(x, y, z);
	glBegin(GL_TRIANGLE_FAN);
	if(x == 1){
		glVertex3f(4+x, y, z);
		for(int i = 0; i < res; ++i){
			glVertex3f(4, 0.2 * cos(a), 0.2 * sin(a));
			glVertex3f(4, 0.2 * cos(a + d), 0.2 * sin(a + d));
			a = a + d;
		}
	}
	
	if(y == 1){
		glVertex3f(x, y + 4, z);
		for(int i = 0; i < res; ++i){
			glVertex3f(0.2 * cos(a),4, 0.2 * sin(a));
			glVertex3f(0.2 * cos(a + d),4, 0.2 * sin(a + d));
			a = a + d;
		}
	}

	if(z == 1){
		glVertex3f(x, y, z+4);
		for(int i = 0; i < res; ++i){
			glVertex3f(0.2 * cos(a),0.2 * sin(a), 4); 
			glVertex3f(0.2 * cos(a),0.2 * sin(a), 4);
			a = a + d;
		}
	}
	glEnd();
}

void glprimitives::dim3::DrawCilinder(float x, float y, float z){
	float res = 360;
	float d = 2 * PI / 360;
	float a = 0;
	glColor3f(x, y, z);
	glBegin(GL_QUAD_STRIP);
	if(x == 1){
		glVertex3f(4+x, y, z);
		for(int i = 0; i < res; ++i){
			glVertex3f(4, 0.05 * cos(a), 0.05 * sin(a));
			glVertex3f(0, 0.05 * cos(a), 0.05 * sin(a));
			a = a + d;
		}
	}
	
	if(y == 1){
		glVertex3f(x, y + 4, z);
		for(int i = 0; i < res; ++i){
			glVertex3f(0.05 * cos(a),4, 0.05 * sin(a));
			glVertex3f(0.05 * cos(a),0, 0.05 * sin(a));
			a = a + d;
		}
	}

	if(z == 1){
		glVertex3f(x, y, z+4);
		for(int i = 0; i < res; ++i){
			glVertex3f(0.05 * cos(a),0.05 * sin(a), 4);
			glVertex3f(0.05 * cos(a),0.05 * sin(a), 0);
			a = a + d;
		}
	}
	glEnd();	
}

void glprimitives::dim3::arrow(void){
	//y
	Drawcone(0,1,0);
	DrawCilinder(0,1,0);

	//x
	Drawcone(1,0,0);
	DrawCilinder(1,0,0);

	//z
	Drawcone(0,0,1);
	DrawCilinder(0,0,1);
}

void glprimitives::dim3::axis(void){
    arrow();
    drawgrid();
}
