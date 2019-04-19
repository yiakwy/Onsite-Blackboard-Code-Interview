

#ifndef _HALF_EDGE_DATA_STRUCTURE_H_
#define _HALF_EDGE_DATA_STRUCTURE_H_

//half-edge
struct HE_edge;
typedef struct HE_edge Edge ;
typedef struct HE_edge * pEdge;

typedef pEdge e_Position;
typedef pEdge eList;

//vertex
struct HE_vert;
typedef struct HE_vert Vert;
typedef struct HE_vert * pVert; 

typedef pVert v_Position;
typedef pVert vList;

//face
struct HE_face;
typedef struct HE_face Face;
typedef struct HE_face * pFace;

typedef pFace f_Position;
typedef pFace fList;

//method
//include files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//using string just to obtain "const char string" to cater for other standard functions in the future
#include <string>
using std::string;

#include <map>
using std::map;
using std::pair;

extern map<int, Vert> v_map;
extern map<pair<int, int>, Edge> e_map;
extern map<int, Face> f_map;

extern int meshstate;
extern string filename;
extern int AABB;
extern int light_switch;

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

void ReadMesh(const char * filename);
void RenderMesh(int);
void Constructor_N_V(void);
void ABOX(void);
#endif
