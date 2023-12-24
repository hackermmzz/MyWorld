#include "updatecameraprojection.h"

void UpdateCameraProjection()
{
    ////////////////////////////////////////////////////////
    camera_projection=Matrix::perspective(CAMERA_PROJECTION_FOV,window_width*1.0/window_height,CAMERA_PROJECTION_NEAR,CAMERA_PROJECTION_FAR);
}
