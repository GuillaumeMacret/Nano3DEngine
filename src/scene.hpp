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

        virtual void press_up(){
            camera.currentDisplacementSpeed[1] += camera.displacementSpeed;
        };
        virtual void press_down(){
            camera.currentDisplacementSpeed[1] -= camera.displacementSpeed; 
        };
        virtual void press_left(){
            camera.currentDisplacementSpeed[0] -= camera.displacementSpeed; 
        };
        virtual void press_right(){
            camera.currentDisplacementSpeed[0] += camera.displacementSpeed; 
        };
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

        virtual void update(){
        };

        //! Drawn all objects in the FOV of the camera
        void draw() const{

            //Vec2r zero(0,0), un(.1,.1), cent(100,100);
            /*
            gui->render_text( { 940, 20 }, "test", white );
            gui->render_line( zero, un, white );
            */
           //std::cout<<"Currently "<<objects3D.size()<<" Objects in scene"<<std::endl;

            for(auto it = objects3D.begin(); it != objects3D.end(); ++it){
                draw_object(*it);
            }
        }

        //! Draw all sides of the object given as argument taht are facing the camera
        void draw_object(Object3D * const o3d) const{
            for(unsigned int i = 0; i < o3d->num_faces(); ++i){
                if(camera.sees(*o3d->face(i))){
                    draw_wire_triangle(*o3d->face(i));
                }
            }
        }

        //! Draws the face given as argument (the three edges of the triangle)
        void draw_wire_triangle( const Triangle &triangle)const{
            /*
            Vector3r p0(triangle.get_p0().vec[0], triangle.get_p0().vec[1], triangle.get_p0().vec[2]);
            Vector3r p1(triangle.get_p1().vec[0], triangle.get_p1().vec[1], triangle.get_p1().vec[2]);
            LineSegment<3,double> ls(p0,p1);
            //camera.visible_part(triangle.p0);
            */
           float tab[4] = {triangle.get_p0()[0],triangle.get_p0()[1],triangle.get_p0()[2],0};
           const Point<4,float> p0(tab);
           
           float tab2[4] = {triangle.get_p1()[0],triangle.get_p1()[1],triangle.get_p1()[2],0};
           const Point<4,float> p1(tab2);

           float tab3[4] = {triangle.get_p2()[0],triangle.get_p2()[1],triangle.get_p2()[2],0};
           Point<4,float> p2(tab3);

            if(!camera.fov.outside(p1) && !camera.fov.outside(p0)){
                draw_edge(p0,p1);
            }else{
                LineSegment<3,float> seg(p0,p1);
            }
            draw_edge(p1,p2);
            draw_edge(p2,p0);

            /*
           const Point<4,float> &projA = perspective_projection(p0);
           const Point<4,float> &projB = perspective_projection(p1);
           const Point<4,float> &projC = perspective_projection(p2);

           Vec2r a,b;
           a[0] = projA.at(0);
           a[1] = projA.at(1);
           b[0] = projB.at(0);
           b[1] = projB.at(1);
           gui->render_line(a,b,white);
        //    std::cout<<a<<" "<<b<<std::endl;
           b[0] = projC.at(0);
           b[1] = projC.at(1);
           gui->render_line(a,b,white);
        //    std::cout<<a<<" "<<b<<std::endl;
           a[0] = projB.at(0);
           a[1] = projB.at(1);
           gui->render_line(a,b,white);
        //    std::cout<<a<<" "<<b<<std::endl;
        */
        }

        //! Draws the segment given as argument
        void draw_edge(const Point<4,float> &p1, const Point<4,float> &p2)const{
            const Point<4,float> &projA = perspective_projection(p1);
            const Point<4,float> &projB = perspective_projection(p2);

            Vec2r a,b;

            a[0] = projA.at(0);
            a[1] = projA.at(1);
            b[0] = projB.at(0);
            b[1] = projB.at(1);
            gui->render_line(a,b,white);
        }

        //! Projects the point given as argument on the screen ("near plane")
        Point<4, float> perspective_projection(const Point<4, float> &p)const{
            
            //TODO test seems weird
            Plane<float> const &near  = camera.fov.near;
            //std::cout<<near<<std::endl;
            float x = p.vec.at(0), y = p.vec.at(1), z = p.vec.at(2), n = near.vector.at(2);
            float xp = -(n/z) * x, yp = -(n/z) * y;
            float tab[4] = {xp,yp,0,0};
            Point<4,float>pt(tab);
            return pt;
        }
};

#endif