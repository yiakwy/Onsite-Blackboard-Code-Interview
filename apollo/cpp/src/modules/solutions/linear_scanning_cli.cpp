//
//  linear_scanning_cli.cpp
//  ApolloTeam
//
//  Created by Wang Yi on 17/4/19.
//
//
/* 
 * Input-Output libraries
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
using std::stringstream;
#include <fstream>

#include <string.h>
#include <string>
using std::string;

#include <map>
using std::map;
using std::pair;
using std::make_pair;

#include <vector>
#include <algorithm>

#include "utils/api.h"
#include "algorithms/linear_scanning.hpp"
#include "gl/viewer.hpp"
#include "gl/Object.hpp"

// See definition in README.md
extern Viewer* viewer;

int main(int argc, char** argv) {
    init_GLog(argc, (const char**)argv);
    viewer = new GlutViewer(argc, argv);
    
    // construct a scene graph
    Scene* scene = new Scene();
    viewer->SetScene(scene);
    
    // single thread runner
    viewer->Run();
    
}
