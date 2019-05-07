//
//  Renderer.hpp
//  ApolloTeam
//
//  Created by Wang Yi on 30/4/19.
//
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include "Scene.hpp"
#include "Camera.hpp"

class Renderer {
    
};

// Since OpenGL 2 is developed for immediate mode execution. Despite it is handy for rendering pipeline, abstraction of such a renderer is not applicable.
// We only implement renderer for OpenGL3+ and OpenGL SE
class
     OpenGL3ShaderRendererImpl : public Renderer {
public:
     OpenGL3ShaderRendererImpl() {
    
    }
    
    ~OpenGL3ShaderRendererImpl() {}
};


class
     OpenGLSERendererImpl: public Renderer {
public:
     OpenGLSERendererImpl() {
        
    }
        
    ~OpenGLSERendererImpl() {}
};

#endif /* Renderer_hpp */
