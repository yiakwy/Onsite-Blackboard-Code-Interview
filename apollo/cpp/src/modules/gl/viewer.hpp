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
#include <memory>
#include <functional>
#include <chrono>
#include <ctime>
// some code needed to handle migration from <experimental/optional> to <optional>, see https://codereview.stackexchange.com/questions/136350/seamlessly-migrating-experimental-optional-to-optional
#include <experimental/optional>
#ifdef WIN32
// the codes was originally developed and tested under WIN32 platform using glui(https://github.com/libglui/glui/issues/85) in arround 2013 by Lei (yaik.wy@gmail.com)
// you need to mannually install opengl and place opengl.dll in WIN32 system library directory
#include <GL/glut.h>
#include <GL/glui.h> // used for UI controllers: pannel, button, scroll ...
#endif

#ifdef __APPLE__
// warning : OpenGL was deprecated in macOS 10.14. To create high-performance code on GPUs, use the Metal framework instead. See Metal. https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_pg_concepts/opengl_pg_concepts.html#//apple_ref/doc/uid/TP40001987-CH208-SW1
#ifdef OPEN_GL3
#include <OpenGL/gl3.h>

#define __gl_h_ // see tricks bought by https://stackoverflow.com/questions/24095931/glut-deprecation-in-mac-osx-10-9-ide-qt-creator
#else
#include <OpenGL/gl.h>
#endif

#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <glm/glm.hpp>
#include <glfw/glfw3.h>
#endif

#ifdef __linux__
// Not Implemented Yet!
#endif

#include <cstdlib>
#include <string>
using std::string;

// #include <gflags/gflags.h>
#include "utils/api.h"

// replaced older Half_Edge_Data_Structure.h
#include "IMPROVED_MESH.h"
#include "Camera.hpp"
#include "FirstPersonControls.hpp"
#include "Axis.h"

#define TRANSFORM_NONE		0
#define TRANSFORM_ROTATE	1
#define TRANSFORM_SCALE		2
#define TRANSFORM_TRANSLATE 3

#ifndef VIEWER_FLAGS
#define VIEWER_FLAGS

/*
DEFINE_bool(is_3dmode, true, "Display gl in 3d/2d mode");
DEFINE_int32(width, 650, "Main window width");
DEFINE_int32(height, 650, "Main window height");
DEFINE_int32(x, 100, "Main window position x coordinate");
DEFINE_int32(y, 100, "Main window position y coordinate");
DEFINE_double(winLLx, 0.0, "coordinate for the left vertical clipping plane");
DEFINE_double(winLLy, 0.0, "coordinate for the bottom horizontal clipping plane");
DEFINE_double(winLen, 100.0, "Orthographic viewing region size");
DEFINE_string(name, "Glut Viewer Main Window - Yi", "Name of main window");
*/
 
#endif

class Color { //RGB color
public:
    typedef long long ll;
    explicit Color(ll hex) { set_hex(hex); };
    // @todo : TODO
    explicit Color(std::string color) {};
    explicit Color(float r, float g, float b)
    : r_(r),
      g_(g),
      b_(b),
      a_(0)
    {};
    
    explicit Color(float r, float g, float b, float a): Color(r, g, b)
    { a_ = a; }
    
    // @todo : TODO
    void
    set_hex(ll hex)
    {
        
    }
    
    // @todo : TODO
    ll get_hex() {
    
    }
    
    void set_color(float r, float g, float b) {
        r_ = r;
        g_ = g;
        b_ = b;
        
    }
    
    float r() {
        return r_;
    }
    
    float g() {
        return g_;
    }
    
    float b() {
        return b_;
    }

    float a() {
        return a_;
    }

private:
    float r_;
    float g_;
    float b_;
    float a_;
    
};

/*
 * C global variables for controls
 * They are deprecated in favor of C++ Viewer class and namespace.
 */

int meshstate = 0;
int AABB = 1;
int light_switch = 1;
std::string filename = "undefined.m";

/*
 * C style callback, since it impossible to convert Member function pointer binded with 'this' to C style function pointer. To resolve this we use thread local storage.
 */
class Viewer;
class GlutViewer;
static Viewer* viewer;

static void idle();
static void disp();
static void hotkey(unsigned char k, int x, int y);
static void reshape(int w, int h);
static void controls(int button, int state, int x, int y);
static void motion(int x, int y);

static std::chrono::system_clock::time_point Now() {
    return std::chrono::system_clock::now();
}

class Viewer // simple version
{
public:
    
    explicit Viewer(int argc, char** argv)
    : background(0.75, 0.75, 0.75) {
        
        gflags::ParseCommandLineFlags(&argc, &argv, true);
        
        /*
        is_3dmode = FLAGS_is_3dmode;
        main_window.width = FLAGS_width;
        main_window.height = FLAGS_height;
        Pixel2D& p = main_window.pos;
        p.x = FLAGS_x;
        p.y = FLAGS_y;
        main_window.name = FLAGS_name;
        main_window.focused = true;
        winLLx = FLAGS_winLLx;
        winLLy = FLAGS_winLLy;
        winLen = FLAGS_winLen;
         */
        
        is_3dmode = true;
        main_window.width = 650;
        main_window.height = 650;
        Pixel2D& p = main_window.pos;
        p.x = 100;
        p.y = 100;
        main_window.name = "Glut Viewer Main Window - Yi";
        main_window.focused = true;
        winLLx = 0.0;
        winLLy = 0.0;
        winLen = 100.0;
        
    }
    virtual ~Viewer() {};
    
    // we will write some abstract methods later for other Viewer to inherit from.
    virtual void Init(int, char**) = 0;
    virtual void InitWindow(int, char**) = 0;
    virtual int CreateWindow(std::string) = 0;
    virtual void Run() = 0;
    virtual void Clear() = 0;
    virtual void SetDisplayMode() = 0;
    virtual void Setup2DCamera() = 0;
    virtual void Setup3DCamera() = 0;
    virtual void  InitControls() = 0;
    virtual void SetLights() = 0;
    virtual void Idle() = 0;
    virtual void Disp() = 0;
    virtual void Reshape(int, int) = 0;
    virtual void OnMouseClick(int, int, int, int) = 0;
    virtual void OnMouseMove(int, int) = 0;
    virtual void Hotkey(unsigned char, int x, int y) = 0;

protected:
    
    struct Pixel2D {
        int x;
        int y;
    };
    
    typedef struct _window_shape_t {
        int width;
        int height;
        double aspect;
        int fd;
        Pixel2D pos;
        std::string name;
        bool focused = false;
    } Window;
    
    typedef struct _mouse_device_t {
        float press_x;
        float press_y;
        int state;
    } Mouse;
    
    bool is_3dmode = false;
    Window main_window;
    Mouse mouse;
    Color background;
    double winLLx;
    double winLLy;
    double winLen;
    
    // @todo : TODO read camera settings from configuration file
    std::unique_ptr<PerspectiveCamera> camera;
    std::unique_ptr<TransformControl> control;
    
    std::chrono::system_clock::time_point curr_;
    std::chrono::system_clock::time_point last_;
    
    using Duration = std::chrono::duration<float, std::milli>;
    
    Duration dt;

public:
    virtual Window& SetWindowSize(int, int) = 0;
    virtual Window& SetWindowPosition(int, int) = 0;
    virtual void Update(Duration) = 0;
};


// Glut was mostly used in opengl 2 which implements immediate mode of GL API. It is deprecated functionality replaced by OpenGL Core Profile mode introduced from OpenGL 3.2. But it is handy to create a simple graphic program even though it harms performance.
class GlutViewer : public Viewer
{
public:
    explicit GlutViewer(int argc, char** argv) : Viewer(argc, argv) {
        Init(argc, argv);
    }
    virtual ~GlutViewer() {}
    
    typedef std::function<void(void)> Callback;
    
    void
    Init (int argc, char** argv) override {
        // glutInit is deprecated since MacOS 10.9, see https://stackoverflow.com/questions/24095931/glut-deprecation-in-mac-osx-10-9-ide-qt-creator
        
        InitWindow(argc, argv);
        Clear();
        if (is_3dmode) {
            // setup 3D projection camera
            Setup3DCamera();
        } else {
            Setup2DCamera();
        }
        
        InitControls();
        SetLights();
        // Register events poll
        InitGlut();
    }
    
    void
    InitWindow(int argc, char** argv) override {
        glutInit(&argc, argv);
        SetDisplayMode();
        SetWindowSize(main_window.width, main_window.height);
        SetWindowPosition(main_window.pos.x, main_window.pos.y);
        main_window.fd = CreateWindow(main_window.name);
    }
    
    void Run() override {
        // glut will handle the graphics rendering loop and calling render functions internally :
        // while (true) {
        //    viewer->Update();
        //    viewer->Disp(); // display them onto screen.
        // }
        glutMainLoop();
    }
    
    void
    SetDisplayMode() override {
        if (is_3dmode) {
            Set3DimDisplayMode();
        } else {
            Set2DimDisplayMode();
        }
    }
    
    void
    Set3DimDisplayMode() {
        #ifdef OPEN_GL3
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
        #else
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        #endif
    }
    
    void
    Set2DimDisplayMode() {
        #ifdef OPEN_GL3
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        #else
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        #endif
    }
    
    Window&
    SetWindowSize(int width, int height) override {
        glutInitWindowSize(width, height);
        return main_window;
    }
    
    Window&
    SetWindowPosition(int x, int y) override {
        glutInitWindowPosition(x, y);
        return main_window;
    }
    
    int
    CreateWindow(std::string name) override {
        return glutCreateWindow(name.c_str());
    }

    void InitGlut() {
        // setup main loop callbacks
        // note you cannot static_cast or reinterpret_cast a runtime std::bind into function pointer directly.
        glutIdleFunc(idle);
        glutDisplayFunc(disp);
        glutKeyboardFunc(hotkey);
        glutMouseFunc(controls);
        glutReshapeFunc(reshape);
        glutMotionFunc(motion);
    }
    
    void Setup2DCamera() {
        // setup 2D camera
        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(winLLx, winLLx + winLen, winLLy, winLLy + winLen);
    }
    
    void Setup3DCamera() {
        camera = std::make_unique<PerspectiveCamera>(60, 1, .1, 100);
        camera->set_position(glm::vec3(15, 15, 15));
        camera->LookAt(glm::vec3(0, 0, 0));
    }
    
    void Clear() override {
        glClearColor(background.r(), background.g(), background.b(), background.a());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
    
    void
    InitControls() override {
        control = std::make_unique<TransformControl>();
        control->setCamera(camera.get());
    }
    
    void SetLights() override {
    
    }
    
    void Idle () override {
        /* According to the GLUT specification, the current window is
         undefined during an idle callback.  So we need to explicitly change
         it if necessary */
        if ( glutGetWindow() != main_window.fd )
            glutSetWindow(main_window.fd);
        
        glutPostRedisplay();
    }
    
    void Reshape(int w, int h) override {
        if (h == 0) {
            return;
        }
        
        main_window.aspect = (float) w / (float) h;
        
        // @todo : TODO this should be done in camera
        camera->set_viewport(w, h);
        
        if (is_3dmode) {
            Setup2DCamera();
        } else {
            // setup projection
            Setup3DCamera();
        }
        
        glutPostRedisplay();
        
    }
    
    void Disp() override {
        glEnable(GL_DEPTH_TEST);
        
        // Just clean the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //*
        camera->UpdateProjectionMatrix();
        camera->LookAt(glm::vec3(0, 0, 0));
         //*/
        dt = UpdateClock();
        Update(dt);
        
        // render models
        glPushMatrix(); // save the current matrix
        axis();
        glPopMatrix(); // restore to previously saved matrix
        
        // swap the buffers and display them onto screen
        glutSwapBuffers();
    }
    
    // @todo : TODO
    void Hotkey(unsigned char k, int x, int y) override {
        
    }
    
    void OnMouseClick(int button, int state, int x, int y) override {
        // update mouse device
        mouse.state = state;
        if (state == GLUT_DOWN)
        {
            mouse.press_x = x; mouse.press_y = y;
            if (button == GLUT_LEFT_BUTTON)
                control->OnMouseClick(TRANSFORM_ROTATE, x, y);
            else if (button == GLUT_MIDDLE_BUTTON)
                control->OnMouseClick(TRANSFORM_SCALE, x, y);
            else if (button == GLUT_RIGHT_BUTTON)
                control->OnMouseClick(TRANSFORM_TRANSLATE, x, y);
            
        }
        else if (state == GLUT_UP) 
        {
            control->OnMouseRelease();
        }
    }
    
    void OnMouseMove(int x, int y) override {
        // update controls
        dt = UpdateClock();
        control->OnMouseMove(dt.count() * 1.0f / 1000, x, y);
    }
    
    Duration UpdateClock() {
        curr_ = Now();
        auto elapse = curr_ - last_;
        last_ = curr_;
        dt = std::chrono::duration_cast<std::chrono::milliseconds>(elapse);
        return dt;
    }
    
    void Update(Duration) override {
        control->Update(dt.count() / 1000.f);
        // update objects in the scene attached to the viewer.
    }
    
private:
};

static void idle()
{
    if (viewer) {
        viewer->Idle();
    }
}

static void disp() {
    if (viewer) {
        viewer->Disp();
    }
}

static void hotkey(unsigned char k, int x, int y) {
    if (viewer) {
        viewer->Hotkey(k, x, y);
    }
}

static void reshape(int w, int h) {
    if (viewer) {
        viewer->Reshape(w, h);
    }
}

static void controls(int button, int state, int x, int y) {
    if (viewer) {
        viewer->OnMouseClick(button, state, x, y);
    }
}

static void motion(int x, int y) {
    if (viewer) {
        viewer->OnMouseMove(x, y);
    }
}
#endif /* viewer_hpp */
