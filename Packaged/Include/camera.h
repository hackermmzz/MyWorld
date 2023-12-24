#ifndef CAMERA_H
#define CAMERA_H
#include"matrix.h"
enum CAMERA_MOVEMENT{
    FORWARD=1,
    BACKWARD=2,
    LEFT=4,
    RIGHT=8
};
class Camera
{
private:
    void update();
public:
    vec3 position;
    vec3 front;
    vec3 right;
    vec3 up;
    vec3 worldup;
    double pitch,yaw;
    double movespeed;
    Camera(const vec3&position={0,0,0},const vec3&worldup={0,1,0},double pitch=0.0,double yaw=-90.0,double movespeed=1.0);
    void processMouseMovement(double xoffset,double yoffset,double sensibility);
    void processKeyBoard(CAMERA_MOVEMENT movement,double deltatime);
    Matrix getMatrix();
    ~Camera();
};

#endif // CAMERA_H
