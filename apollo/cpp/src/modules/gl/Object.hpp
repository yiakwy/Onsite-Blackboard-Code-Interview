//
//  Object.hpp
//  ApolloTeam
//
//  Created by Wang Yi on 30/4/19.
//
//

#ifndef Object_hpp
#define Object_hpp

// The hirearchy borrows from Three.js game engine with webgl rasterizer as backend.
class Object3d {
public:
    Object3d() {}
    virtual ~Object3d() {}
    
    void UpdateWorldMatrix() {
        
    }
};

#endif /* Object_hpp */
