#ifndef SCENE_H
#define SCENE_H

#include "scene_interface.h"
#include "gui.h"
#include "camera.hpp"
#include "object3D.hpp"
#include "../include/libgeometry.hpp"
#include <vector>

using namespace gui;
using namespace libgeometry;

class Scene : public SceneInterface{
    public:
        Gui *gui;
        Camera camera;
        std::vector<Object3D*> objects3D;

        Scene(){};

        virtual void press_up(){};
        virtual void press_down(){};
        virtual void press_left(){};
        virtual void press_right(){};
        virtual void press_space(){};
        virtual void press_w(){};
        virtual void press_s(){};
        virtual void press_a(){};
        virtual void press_d(){};
        virtual void press_q(){};
        virtual void press_e(){};
        virtual void press_z(){};
        virtual void press_x(){};

        virtual void release_updown(){};
        virtual void release_leftright(){};
        virtual void release_space(){};
        virtual void release_ws(){};
        virtual void release_ad(){};
        virtual void release_qe(){};
        virtual void release_zx(){};

        virtual void update(){};

        //! Drawn all objects in the FOV of the camera
        void draw() const{
            for(auto it = objects3D.begin(); it != objects3D.end(); ++it){
                draw_object(*it);
            }
        }

        //! Draw all sides of the object given as argument taht are facing the camera
        //TODO draw items partialy
        void draw_object(Object3D * const o3d) const{
            for(unsigned int i = 0; i < o3d->num_faces(); ++i){
                if(camera.sees(*o3d->face(i))){
                    draw_wire_triangle(*o3d->face(i));
                }
            }
        }

        //! Draws the face given as argument (the three edges of the triangle)
        void draw_wire_triangle( const Triangle &triangle) const{
            //TODO
        }

        //! Draws the segment given as argument
        void draw_edge(const Point<4,float> &p1, const Point<4,float> &p2)const{
            //TODO
        }

        //! Projects the point given as argument on the screen ("near plane")
        Point<4, float> perspective_projection(const Point<4, float> &p)const{
            //TODO
            Plane<3,double> const &near  = camera.fov.near;
            float x = p.vec.at(0), y = p.vec.at(1), z = p.vec.at(2), n = near.vector.at(2);
            float xp = -(n/z) * x, yp = -(n/z) * y;
            float tab[4] = {xp,yp,0,0};
            //return Point<4,float>(tab);
        }
};

#endif