#ifndef CAMERA_H
#define CAMERA_H

#include "../include/libgeometry.hpp"

using namespace libgeometry;

class Frustum{
    public:
        Plane<3,double> near,far,right,left,top,bottom;

        Frustum(){
            
        };

        //!Returns if the point given as argument is outside the fov
        bool outside(const Point<4,float> &p)const{

        }

        //!Returns if the sphere given as argument is outside the fov
        bool outside(const Sphere<3,float> &s)const{

        }

        //!Return the intersection between the segmant and the fov (visible part)
        LineSegment<3,double> inter (const LineSegment<3,double> &seg)const{
            
        }

        //! Updates the position of the field of vision, where h is the horizontal resolution, v is the vertical resolution and e is the distance between the projection plane and the camera.
        void update( float h, float v, float e ){

        }
};

class Camera{
    public:
        //The height and width of the image
        Vec2i screen{1024,720};
        double displacementSpeed, orientationChangingSpeed, zoomSpeed;
        double currentPosition, currentOrientation;
        Vector3r currentDisplacementSpeed, currentOrientationChangingSpeed;
        double currentZoomSpeed;
        double distanceToProjectionPlan;
        Frustum fov;

        Camera(){};

        //! Returns the transform corresponding to the viewpoint of the camera
        Transform get_transform() const{

        }

        //!Returns if the sphere given as argument is outside of the field of view of the camera.
        bool outside_frustum(const Sphere<3,double> &sphere)const{

        }

        //!Returns if the camera sees the triangular face given as arg
        bool sees(Triangle & triangle)const{

        }

        //!Returns the visible part of the segment given as argument.
        LineSegment<3,double> visible_part( const LineSegment<3,double> &line ) const{

        }

        //!Updates the position and orientation of the camera.
        void update(){

        }

};


#endif