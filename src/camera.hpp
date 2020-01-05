#ifndef CAMERA_H
#define CAMERA_H

#include "../include/libgeometry.hpp"

using namespace libgeometry;

class Frustum{
    public:
        Plane<float> near,far,right,left,top,bottom;
        double f = 25;

        Frustum(double distanceToNear){
            near.vector[0] = 0;
            near.vector[1] = 0;
            near.vector[2] = 1;
            near.vector[3] = -distanceToNear;
        };

        //!Returns if the point given as argument is outside the fov
        //TODO
        bool outside(const Point<4,float> &p)const{
            return 0;
            //return (p.behind(near) || p.behind(far) || p.behind(right) || p.behind(left) || p.behind(top) || p.behind(bottom));
        }

        //!Returns if the sphere given as argument is outside the fov
        bool outside(const Sphere<3,float> &s)const{
            return 1;
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
        Vector3r currentPosition, currentOrientation;
        Vector3r currentDisplacementSpeed, currentOrientationChangingSpeed;
        double currentZoomSpeed;
        double distanceToProjectionPlan = 5;
        Frustum fov;

        Camera():fov(distanceToProjectionPlan){
            
        };

        //! Returns the transform corresponding to the viewpoint of the camera
        Transform get_transform() const{

        }

        //!Returns if the sphere given as argument is outside of the field of view of the camera.
        bool outside_frustum(const Sphere<3,double> &sphere)const{

        }

        //!TODO Returns if the camera sees the triangular face given as arg
        bool sees(Triangle & triangle)const{
            return 1;
        }

        //!TODO Returns the visible part of the segment given as argument.
        LineSegment<3,double> visible_part( const LineSegment<3,double> &line ) const{
            //return line;
        }

        //!Updates the position and orientation of the camera.
        void update(){
            currentPosition += currentDisplacementSpeed;
            currentDisplacementSpeed[0] = 0;
            currentDisplacementSpeed[1] = 0;
            currentOrientation += currentOrientationChangingSpeed;
            currentOrientationChangingSpeed[0] = 0;
            currentOrientationChangingSpeed[1] = 0;
        }

};


#endif