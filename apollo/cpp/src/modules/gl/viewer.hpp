//
//  viewer.hpp
//  ApolloTeam
//
//  Created by Wang Yi on 19/4/19.
//
//

#ifndef viewer_hpp
#define viewer_hpp

#include <iostream>
#ifdef WIN32
// the codes was originally developed and tested under WIN32 platform in arround 2013 by Lei (yaik.wy@gmail.com)
#include <GL/glut.h>
#include <GL/glui.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#endif

#ifdef __linux__
// Not Implemented Yet!
#endif


class Viewer
{
 
};

class GlutViewer : public Viewer
{
public:
    explicit GlutViewer(int argc, char** argv) {}
    
    void
    Init(int argc, char** argv) {
        // glutInit is deprecated since MacOS 10.9, see https://stackoverflow.com/questions/24095931/glut-deprecation-in-mac-osx-10-9-ide-qt-creator
        glutInit(&argc, argv);
    }
    
private:
    
};

#endif /* viewer_hpp */
