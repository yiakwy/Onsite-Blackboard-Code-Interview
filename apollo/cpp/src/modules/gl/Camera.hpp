//
//  Camera.hpp
//  ApolloTeam
//
//  Created by Wang Yi on 26/4/19.
//
//

#ifndef Camera_hpp
#define Camera_hpp

#ifdef __APPLE__
// warning : OpenGL was deprecated in macOS 10.14. To create high-performance code on GPUs, use the Metal framework instead. See Metal. https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_pg_concepts/opengl_pg_concepts.html#//apple_ref/doc/uid/TP40001987-CH208-SW1
#ifdef OPEN_GL3
#include <OpenGL/gl3.h>

#define __gl_h_ // see tricks bought by https://stackoverflow.com/questions/24095931/glut-deprecation-in-mac-osx-10-9-ide-qt-creator
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

// See https://github.com/g-truc/glm/blob/master/readme.md
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp> // http://www.c-jump.com/bcc/common/Talk3/Math/GLM/W01_0080_glmvalueptr_exampl.htm
#include <glm/gtx/string_cast.hpp>
#include <glfw/glfw3.h>
#endif

#include <iostream>
#include "Object.hpp"

class
Camera : public Object3d {
public:
    // @todo : TODO
    explicit Camera() : eye(0, 0, 0), up(0, 1, 0) {}
    explicit Camera(glm::vec3 pos) : up(glm::vec3(0,1,0)) {}
    explicit Camera(glm::vec3 pos, glm::vec3 up)
    {
    
    }
    
    virtual void UpdateWorldMatrix () {
        Object3d::UpdateWorldMatrix();
    }
    
    void set_position(glm::vec3 pos) {
        eye = pos;
    }
    
    // @todo : TODO
    void set_viewport(int w, int h) {
#ifdef OPEN_GL3
        // not implemented using gl3 shader programes yet, see <Renderer::OpenGL3ShaderRendererImpl>
#else
        //*
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, 0, w, h);
         //*/
#endif
    }
    
    glm::vec3 position() {
        return eye;
    }
    
    virtual void UpdateProjectionMatrix() = 0;
    
    glm::mat4 LookAt(glm::vec3 dest) {
#ifdef OPEN_GL3
        // not implemented using gl3 shader programes yet, see <Renderer::OpenGL3ShaderRendererImpl>
#else
        glMatrixMode(GL_MODELVIEW);
#endif
        viewMatrix = glm::lookAt(eye, dest, up);
        // std::cout << "viewMatrix computed from glm::lookat : " << glm::to_string(viewMatrix) << std::endl;
        // @todo : TODO set quaternion here
        /*
        if (parent) {
        
        }
         */
#ifdef OPEN_GL3
        // not implemented using gl3 shader programes yet, see <Renderer::OpenGL3ShaderRendererImpl>
#else
        glLoadMatrixf(glm::value_ptr(viewMatrix));
        // glLoadIdentity();
     // glMultMatrixf(glm::value_ptr(viewMatrix));
        // gluLookAt(eye[0], eye[1], eye[2], dest[0], dest[1], dest[2], 0, 1, 0);
        /*
        GLfloat mat[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, mat);
        glm::mat4 mat0 = glm::make_mat4(mat); // you could also memcpy directly
        std::cout << "viewMatrix comptued from gluLookAt : " << glm::to_string(mat0) << std::endl;
         */
#endif
        return viewMatrix;
    }
    
    void UpdateModelMatrix(glm::mat4& modelMatrix) {
#ifdef OPEN_GL3
        // not implemented using gl3 shader programes yet, see <Renderer::OpenGL3ShaderRendererImpl>
#else
        glMatrixMode(GL_MODELVIEW);
#endif
        
        this->modelMatrix = modelMatrix;

#ifdef OPEN_GL3
        // not implemented using gl3 shader programes yet, see <Renderer::OpenGL3ShaderRendererImpl>
#else
        if (is_focused) {
            //*
            glLoadMatrixf(glm::value_ptr(viewMatrix * modelMatrix)); // rotate the whole world w.r.t the original state using view matrix from the camera and provided transforms
             //*/
            /*
            glMultMatrixf(glm::value_ptr(modelMatrix));
             */
        }
#endif
        
    }
    
    virtual ~Camera() {}
    
public:
    // store local transformation relative to its parent
    glm::mat4 matrix;
    // transformation in world coordinates
    glm::mat4 worldMatrix;
    glm::mat4 worldMatrixInverse;
    glm::mat4 modelMatrix;
    glm::mat4 modelMatrixInverse;
    glm::mat4 viewMatrix;
    glm::mat4 viewMatrixInverse;
    glm::mat4 projectionMatrix;
    glm::mat4 projectionMatrixInverse;
    
    glm::vec3 eye;
    glm::vec3 dir;
    glm::vec3 up; // @todo : TODO
    
    bool is_focused = true;

};

class
    PerspectiveCamera : public Camera
{
public:
    explicit PerspectiveCamera(GLfloat fov, GLfloat aspect)
    : Camera(),
    fov_(fov),
    aspect_(aspect),
    near_(0.1f),
    far_(100.0f)
    {}
    explicit PerspectiveCamera(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far)
    : Camera(),
      fov_(fov),
      aspect_(aspect),
      near_(near),
      far_(far)
    {
        UpdateProjectionMatrix();
    }
        
    void UpdateProjectionMatrix() override {
#ifdef OPEN_GL3
        // not implemented using gl3 shader programes yet, see <Renderer::OpenGL3ShaderRendererImpl>
#else
        glMatrixMode(GL_PROJECTION);
#endif
        projectionMatrix = glm::perspective(glm::radians(fov_), aspect_, near_, far_);
        // std::cout << "projectionMatrix computed from glm::perspective : " << glm::to_string(projectionMatrix) << std::endl;
        // Move from Model Space to World Space by applying first scale, second rotation and third translation matrices
        // i.e. world_coordinates = ViewMatrix * ModelMatrix * local_coordinates, where ModelMatrix = translate * rotate * scale in reverse order and computed in GLSL shader program
#ifdef OPEN_GL3
        // not implemented using gl3 shader programes yet, see <Renderer::OpenGL3ShaderRendererImpl>
#else
        glLoadMatrixf(glm::value_ptr(projectionMatrix));
        // glLoadIdentity();
     // glMultMatrixf(glm::value_ptr(projectionMatrix));
        // gluPerspective(fov_, aspect_, near_, far_);
        /*
        GLfloat mat[16];
        glGetFloatv(GL_PROJECTION_MATRIX, mat);
        glm::mat4 mat0 = glm::make_mat4(mat); // you could also memcpy directly
        std::cout << "projectionMatrix comptued from gluPerspective : " << glm::to_string(mat0) << std::endl;
         */
        
#endif
    }
    
    virtual ~PerspectiveCamera() {}
    
private:
    GLfloat fov_;
    GLfloat aspect_;
    GLfloat near_;
    GLfloat far_;
    
    GLfloat zoom_;
    
    GLfloat focus_;
};

#endif /* Camera_hpp */
