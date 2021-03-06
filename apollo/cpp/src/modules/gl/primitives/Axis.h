#ifndef _AXIS_H_
#define _AXIS_H_

#ifdef WIN32
// the codes was originally developed and tested under WIN32 platform in arround 2013 by Lei (yaik.wy@gmail.com)
#include <GL/glut.h>

#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
// Not Implemented Yet!
#endif
#define PI 3.14

namespace glprimitives {
    namespace dim3 {
    
// method
void drawgrid(void);
void Drawcone(float, float, float);
void DrawCilinder(float, float, float);
void arrow(void);
// main function in this module
void axis(void);
    }
    
    namespace dim2 {
// method
void drawgrid(void);
    }
}
#endif
