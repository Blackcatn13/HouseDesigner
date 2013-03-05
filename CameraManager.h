#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

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