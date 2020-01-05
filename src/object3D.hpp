#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "../include/libgeometry.hpp"
#include <vector>

using namespace libgeometry;

class Object3D{
    public:
        std::string name;
        Point<4,double> position;
        std::vector<Point<3,double>*> vertices;
        std::vector<Triangle*> faces;

        //!Return the bounding sphere
        Sphere<3,double> bsphere() const{

        }

        //!Return th n-th face of the object where n is given as argument
        Triangle *face(unsigned int n)const{
            return faces[n]; 
        }

        Point<3,double> *vertice(unsigned int i)const{
            return vertices[i];
        }

        unsigned int num_faces() const{
            return faces.size();
        }

        unsigned int num_vertex() const{
            return vertices.size();
        }

        //! Adds a face to the object. The three integers given as arguments correspond to three vertices.
        void add_face(unsigned int x, unsigned int y, unsigned int z){
            faces.push_back(new Triangle(*vertices[x],*vertices[y],*vertices[z]));
        }

        //! Deletes a face from the object
        void remove_face(unsigned int n){
            if(n < num_faces()){
                delete faces[n];
                faces.erase(faces.begin() + n);
            }
        }

        void add_vertex(double x, double y, double z){
            double tab[3] = {x,y,z};
            vertices.push_back(new Point<3,double>(tab));
        }

        friend std::ostream &operator<<(std::ostream &s, Object3D &o){
            s<<"Object 3d : "<< o.name<<std::endl;
            for(auto it = o.vertices.begin(); it != o.vertices.end(); ++it){
                s<<**it<<std::endl;
            }
            return s;
        }

};

#endif