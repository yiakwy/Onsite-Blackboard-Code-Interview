/*
	Developer: Lei Wang(lwang019@e.ntu.edu.sg)
	Reference: Wikipedia:
	Discription: inherited from mesh.h(Mesh)
	Time:Nov-10-2013
	Prerequisite to the routine: All face are arranged in the order of counterclockwise
*/
#include "IMPROVED_MESH.h"

#ifndef _HALF_EDGE_DATA_STRUCTURE_COMLEMENT_
#define _HALF_EDGE_DATA_STRUCTURE_COMLEMENT_

struct HE_edge{
	v_Position vertex;
	e_Position pair;
	f_Position face;
	e_Position pre;
	e_Position succ;
};

struct HE_vert{
	float x,y,z;
	float nx, ny, nz;
	e_Position edge;
};

struct HE_face{
	e_Position edge;
	float nx, ny, nz;
};

#endif

map<int, Vert> v_map;
map<pair<int, int>, Edge> e_map;
map<int, Face> f_map;

float min[3] = {0};
float max[3] = {0};

void ReadMesh(const char * filename){
	printf("Clearing container...\n");
	v_map.clear();
	e_map.clear();
	f_map.clear();

	FILE * f = fopen(filename, "r+");
	if(f == NULL){
		exit(0);
	}
	
	char type;
	float x,y,z;
	int vid,fid,v1,v2,v3;

	printf("Build Half Edge data set...\n");
	while((type = fgetc(f)) != EOF ){
		switch(type){
		case 'V': 
			if(fscanf(f,"ertex %d %f %f %f\n", &vid, &x, &y, &z) == 4){
				Vert v;
				v.x = x;
				v.y = y;
				v.z = z;
				v.edge = NULL;

				v_map.insert(pair<int, Vert>(vid, v));				
			}
			break;
		case 'F':
			if (fscanf(f, "ace %d %d %d %d\n", &fid, &v1, &v2, &v3) == 4){
				int index, i, j;
				int v[3];
				v[0] = v1;
				v[1] = v2;
				v[2] = v3;
				index = fid;

				for(i = 0; i < 3; ++i){
					j = (i + 1)%3 ;
					Edge e;
					int vid = v[i]; 
					int vjd = v[j];
					e.vertex = & v_map[vid];
					e.pair = NULL;

					e_map.insert(pair<pair<int,int>, Edge>(pair<int,int>(vid,vjd), e));
					v_map[vid].edge = & ( e_map.find(std::make_pair(vid,vjd))->second );

					if(i == 2){
						Face f;
						f.edge = & ( e_map.find(std::make_pair(vid,vjd))->second );
						//compute face normals
						f.nx = (v_map[v2].y - v_map[v1].y) * (v_map[v3].z - v_map[v2].z) - (v_map[v2].z - v_map[v1].z) * (v_map[v3].y - v_map[v2].y);
						f.ny = (v_map[v2].z - v_map[v1].z) * (v_map[v3].x - v_map[v2].x) - (v_map[v2].x - v_map[v1].x) * (v_map[v3].z - v_map[v2].z);
						f.nz = (v_map[v2].x - v_map[v1].x) * (v_map[v3].y - v_map[v2].y) - (v_map[v2].y - v_map[v1].y) * (v_map[v3].x - v_map[v2].x);
						
						float length = sqrt(f.nx * f.nx + f.ny * f.ny + f.nz * f.nz);

						f.nx = f.nx/length;
						f.ny = f.ny/length;
						f.nz = f.nz/length;

						f_map.insert(pair<int, Face>(index, f)); // define face
				
					}
				}//specifies nearby nodes


				for(i = 0; i < 3; ++i){
					j = (i + 1)%3;
					int vid = v[i]; 
					int vjd = v[j];
					std::map<pair<int,int>, Edge>::iterator it = e_map.find(std::make_pair(vid,vjd));

					it->second.succ = & e_map[std::make_pair(vjd, v[(j + 1) % 3])];
					it->second.pre =  & e_map[std::make_pair(v[(i + 2) % 3], vid)];
					it->second.face = & f_map[index];
					
					//e-pair
					std::map<pair<int, int>, Edge>::iterator p = e_map.find(std::make_pair(vjd,vid));
					if( p != e_map.end() ){
						it->second.pair = & p->second;
						p->second.pair = & it->second;
					}
				}//end-edge

			}
			break;
		default:
			do { type=fgetc(f); } while (type != EOF && type != '\n');
			break;
		}
	}
	
	//call Normal constructor
	printf("Construct Normals...\n");
	Constructor_N_V();
	printf("Finished!\n\n\n");

	fclose(f);
	f = NULL;
}

void Constructor_N_V(void){
	//N_v_map.clear();
	//One-Ring Traversal
	int Index;
	
	Index = 1;
	for(std::map<int, Vert>::iterator it = v_map.begin(); it != v_map.end(); ++it){
		e_Position e = it->second.edge;
		e_Position curr = e;

		//if the vertex in on the boundary,we do nothing...I don;t know how to handle it properly...$_$
		int flag;
		if(curr->pair != NULL)
			flag = 0;
		else
			flag = 1;

		while(!flag && curr->pair->succ != e){
			curr = curr->pair->succ;
			if(curr->pair == NULL)
				flag = 1;
		}

		if(flag){
			it->second.nx = curr->face->nx;
			it->second.ny = curr->face->ny;
			it->second.nz = curr->face->nz;
		}
		else{
			it->second.nx = 0.0;
			it->second.ny = 0.0;
			it->second.nz = 0.0;

			int n = 0;

			curr = e;
			while(curr->pair->succ != e){
				//retrive normal keys by value
				f_Position f;
				f = curr->face;

				it->second.nx += f->nx;
				it->second.ny += f->ny;
				it->second.nz += f->nz;
				n++;

				curr = curr->pair->succ;
			}

			it->second.nx = it->second.nx / n;
			it->second.ny = it->second.ny / n;
			it->second.nz = it->second.nz / n;	
		}	
		Index++;
	}
}

void RenderMesh(int obj_mode){
	//char * filename = "eight.m";

	if(meshstate == 0){
		if(filename.c_str() != NULL){
			ReadMesh(filename.c_str());
			meshstate = 1; //another state meshstate = 0 will be achieved if filename is changed successfully.
		}
	}

	if(AABB == 1){
		ABOX();
	}//end-AABB

	if( meshstate == 1){
		if(light_switch == 1){
		 glEnable(GL_LIGHTING);	
		 
			float m = (5.0)/(max[0] - min[0]);
			switch(obj_mode){
			case 1:
				glPushMatrix();
				glScalef(m,m,m);
				glBegin(GL_TRIANGLES);
				for(std::map<int, Face>::iterator it = f_map.begin(); it != f_map.end(); ++it){
					e_Position curr = it->second.edge;

					for(int i = 0; i < 3; i++){
						v_Position v = curr->vertex;
						glNormal3f(v->nx, v->ny, v->nz);
						glVertex3f(v->x, v->y, v->z);

						curr = curr->succ;
					}
				}
				glEnd();
				glFlush();
				glPopMatrix();
				break;	
			case 0:
				glPushMatrix();
				glScalef(m,m,m);
				glBegin(GL_POINTS);
				for(std::map<int, Face>::iterator it = f_map.begin(); it != f_map.end(); ++it){
					e_Position curr = it->second.edge;

					for(int i = 0; i < 3; i++){
						v_Position v = curr->vertex;
						glNormal3f(v->nx, v->ny, v->nz);
						glVertex3f(v->x, v->y, v->z);

						curr = curr->succ;
					}
				}
				glEnd();
				glFlush();
				glPopMatrix();
				break;	
			case 2:
				glPushMatrix();
				glScalef(m,m,m);				
				for(std::map<int, Face>::iterator it = f_map.begin(); it != f_map.end(); ++it){
					e_Position curr = it->second.edge;
					
					glBegin(GL_LINE_LOOP);
					for(int i = 0; i < 3; i++){
						v_Position v = curr->vertex;
				
						glNormal3f(v->nx, v->ny, v->nz);
						glVertex3f(v->x, v->y, v->z);
						
						curr = curr->succ;
					}
					glEnd();
				}		
				glFlush();
				glPopMatrix();
				break;	
			}//end-obj-model
		 glDisable(GL_LIGHTING);
		}
		else{
			
		}
	}//end-light


}

void ABOX(void){
	min[0] = 0;
	min[1] = 0;
	min[2] = 0;

	max[0] = 0;
	max[1] = 0;
	max[2] = 0;

	for(std::map<int, Vert>::iterator t = v_map.begin(); t != v_map.end(); t++){
		float x, y, z;
		x = t->second.x;
		y = t->second.y;
		z = t->second.z;

		if( x < min[0] ){
			min[0] = x;
		}
		else if( x > max[0] ){
			max[0] = x;
		}

		if( y < min[1] ){
			min[1] = y;
		}
		else if( y > max[1] ){
			max[1] = y;
		}

		if( z < min[2] ){
			min[2] = z;
		}
		else if( z > max[2] ){
			max[2] = z;
		}
	}//end-for
	
	float m = (5.0)/(max[0] - min[0]);
	glPushMatrix();
	glScalef(m,m,m);

	glColor3f(0.25, 0.25, 0.25);
	glBegin(GL_LINE_LOOP);
	glVertex3f(min[0], min[1], min[2]);//1
	glVertex3f(min[0], min[1], max[2]);//2
	glVertex3f(max[0], min[1], max[2]);//3
	glVertex3f(max[0], min[1], min[2]);//4
	glVertex3f(min[0], min[1], min[2]);//1
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(min[0], max[1], min[2]);//5
	glVertex3f(min[0], max[1], max[2]);//6
	glVertex3f(max[0], max[1], max[2]);//7
	glVertex3f(max[0], max[1], min[2]);//8
	glVertex3f(min[0], max[1], min[2]);//5
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(min[0], min[1], min[2]); glVertex3f(min[0], max[1], min[2]);
	glVertex3f(min[0], min[1], max[2]); glVertex3f(min[0], max[1], max[2]);
	glVertex3f(max[0], min[1], max[2]); glVertex3f(max[0], max[1], max[2]);
	glVertex3f(max[0], min[1], min[2]); glVertex3f(max[0], max[1], min[2]);
	glEnd();

	glPopMatrix();
}
