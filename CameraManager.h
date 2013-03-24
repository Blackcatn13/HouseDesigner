#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "Util.h"

class CameraManager
{
public:
    ~CameraManager();
    static CameraManager* getInstance(void);

private:
    CameraManager();
    static CameraManager* myCameraManager;
};

#endif