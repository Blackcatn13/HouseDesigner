#include "CameraManager.h"

CameraManager *CameraManager::myCameraManager = 0;

CameraManager::CameraManager(){

}

CameraManager::~CameraManager(){

}

CameraManager* CameraManager::getInstance(){
    return myCameraManager;
}