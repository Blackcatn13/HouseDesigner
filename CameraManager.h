#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "Util.h"

class Camera;

typedef std::map<Views, Camera*> CameraMap;
typedef std::map<Views, Camera*>::iterator CameraMapIterator;

class CameraManager
{
public:
    ~CameraManager();
    static CameraManager* GetInstance();
    Camera* GetCamera(Views view);
    void SetProjection(int w, int h);
    void CleanUp();
    Camera* getCurrentCamera();
    void setCurrentCamera(Views view);
private:
    CameraManager();
    static CameraManager*   m_CameraManager;
    CameraMap               m_Cameras;
    Views                   currentCamera;
};
#endif
