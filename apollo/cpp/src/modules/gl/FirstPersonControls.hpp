//
//  FirstPersonControls.hpp
//  ApolloTeam
//
//  Created by Wang Yi on 28/4/19.
//
//

#ifndef FirstPersonControls_hpp
#define FirstPersonControls_hpp

#ifdef __APPLE__
// See https://github.com/g-truc/glm/blob/master/readme.md
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp> // http://www.c-jump.com/bcc/common/Talk3/Math/GLM/W01_0080_glmvalueptr_exampl.htm
#endif

#include "Camera.hpp"

#define LEFT 1
#define MIDDLE 2
#define RIGHT 3

class TransformControl {
public:
    
    TransformControl() {};
    virtual ~TransformControl() {};
    
    void OnMouseClick(int button, int x, int y) {
        if (button == LEFT) {
            trans_mode = ROTATION;
        } else if (button == MIDDLE) {
            trans_mode = SCALE;
        } else if (button == RIGHT) {
            trans_mode = TRANSLATE;
        }
        
        press_x = x;
        press_y = y;
    }
    
    void
    setCamera(Camera* camera) {
        this->camera = camera;
    }
    
    void OnMouseRelease() {
        trans_mode = TRANSFORMS_UNDEFINED;
    }
    
    void OnKeyDown() {
    
    }
    
    void OnKeyRelease() {
    
    }
    
    void UpdateCameraVectors() {
        forward.y = sin(glm::radians(pitch));
        forward.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        forward.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        
    }
    
    void UpdateTransformMatrix() {
        // glm::mat4 constructor has some problems: https://github.com/g-truc/glm/issues/809
        glm::mat4 modelMatrix, identity = glm::mat4(1.0f);
        glm::mat4 translation = glm::translate(identity, glm::vec3(x_horizontal, y_vertical, 0.f));
        glm::mat4 rotx = glm::rotate(translation, glm::radians(pitch), glm::vec3(1.0f, 0.f, 0.f));
        glm::mat4 rotxy = glm::rotate(rotx, glm::radians(yaw), glm::vec3(.0f, 1.0f, 0.f));
        glm::mat4 rot = glm::rotate(rotxy, glm::radians(roll), glm::vec3(.0f, .0f, 1.0f));
        modelMatrix = glm::scale(rot, glm::vec3(scale, scale, scale));
        
        // std::cout << "TransformMatrix is : " << glm::to_string(modelMatrix) << std::endl;
        // std::cout << "viewMatrix * TransformMatrix is : " << glm::to_string(camera->viewMatrix * modelMatrix) << std::endl;
        
        /*
        glTranslatef(x_horizontal, y_vertical, 0);
        glRotatef(yaw, 0, 1,0);
        glRotatef(roll, 0,0,1);
        glScalef(scale, scale, scale);

        GLfloat mat[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, mat);
        glm::mat4 mat0 = glm::make_mat4(mat);
    
        std::cout << "TransformMatrix from gl transform : " << glm::to_string(mat0) << std::endl;
         */
        
        camera->UpdateModelMatrix(modelMatrix);
    
    }
    
    // @todo : TODO
    void OnMouseMove(float dt, int x, int y) {
        dt = 1.0;
        // update Euler angles
        float offsetX = x - press_x;
        float offsetY = press_y - y;
        if (trans_mode == ROTATION)
        {
            roll += offsetY * sensitivity * dt;
            
            if (roll > 180.f)
                roll -= 360.f;
            else if (roll < -180.f)
                roll += 360.f;
            
            press_x = x;
            
            yaw += offsetX * sensitivity * dt;
            
            if (yaw > 180.f)
                yaw -= 360.f;
            else if (yaw < -180.f)
                yaw += 360.f;
            
            press_y = y;
        }
        else if (trans_mode == SCALE)
        {
            float scale_ori = scale;
            
            scale *= (1 + offsetY * factor * dt);
            
            if (scale <0)
                scale = scale_ori;
            press_y = y;
        }
        else if (trans_mode == TRANSLATE){
            x_horizontal += offsetX * speed * dt;
            y_vertical += offsetY * speed * dt;
            press_x = x;
            press_y = y;
        }
        // update Quaternion
        
        // update others
        UpdateCameraVectors();
    }
    
    void Update(float dt) {
        UpdateTransformMatrix();
    }
    
protected:
    enum Transforms {
        ROTATION,
        SCALE,
        TRANSLATE,
        TRANSFORMS_UNDEFINED,
    };
    
    Camera* camera;
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;
    
    bool enable = false;
    
    // Euler angles, will replaced by euler and quaternion later
    GLfloat pitch = 0.0; // x axis
    GLfloat yaw = 0.0; // y axis
    GLfloat roll = 0.0; // z axis

    GLfloat scale = 1.0;
    GLfloat factor = 1.0 / 60.0;
    
    int press_x;
    int press_y;
    
    GLfloat x_horizontal = 0.0;
    GLfloat y_vertical = 0.0;
    
    int trans_mode = TRANSFORMS_UNDEFINED;
    float sensitivity = 0.2;
    float speed = 1.0 / 60.0;

};

// @todo : TODO, I am considering to add a tactical light (spot light) for FPC. This should be implemented only after light system is ready. (2019 April 30th commented by Lei)
class FirstPersonControl : public TransformControl {
public:
    FirstPersonControl() {}
    virtual ~FirstPersonControl() {}
private:
    bool is_forward_ = false;
    bool is_left_ = false;
    bool is_right_ = false;
    bool is_jump_ = false;
    
    bool enableJump_ = false;
    
    // flashLight
    
    bool onGround_ = true;
    
    // raycaster
    
    // motion parameters
};

#endif /* FirstPersonControls_hpp */
