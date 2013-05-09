#include "Scenary.h"
#include "Util.h"
#include "ProjectManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <QDir>

CProjectManager* CProjectManager::m_ProjectManager = 0;

CProjectManager::CProjectManager(void)
{
    activeFloor = 0;
}


CProjectManager::~CProjectManager(void)
{
}

CProjectManager* CProjectManager::getInstance()
{
    if(m_ProjectManager == NULL)
        m_ProjectManager = new CProjectManager();
    return m_ProjectManager;
}

bool CProjectManager::SaveMap(string fileName)
{
    CScenary * scenary = CScenary::getInstance();
    vector< vector<ModelInfo> > walls = scenary->getWalls();
    vector< vector<ModelInfo> > objects = scenary->getObjects();
    ofstream file;
    file.open(fileName.c_str());
    int totalFloors = walls.size();

    file << totalFloors << endl;
    file << scenary->getGridMaxX() << " " << scenary->getGridMaxZ()<< endl;

    for(int currentFloor = 0; currentFloor < totalFloors; ++currentFloor)
    {
        for(int index = 0; index < walls[currentFloor].size(); ++index)
            file << getInfoFromObject(currentFloor, walls[currentFloor][index]) << endl;
        for(int index = 0; index < objects[currentFloor].size(); ++index)
            file << getInfoFromObject(currentFloor, objects[currentFloor][index]) << endl;
    }
    file.close();

    return true;
}

bool CProjectManager::LoadMap(string fileName)
{
    ifstream file;
    std::string line;
    int totalFloors, maxX, maxZ, currentFloor;
    ModelInfo info;

    file.open(fileName.c_str());
    if(file.is_open())
    {
        file >> totalFloors;
        file >> maxX >> maxZ;
        while(getline(file, line))
            // parse line (string) 
            info = getObjectFromInfo(line, currentFloor);
    }
    return false;
}

std::string CProjectManager::getInfoFromObject(int currentFloor, ModelInfo object)
{
    stringstream info;
    info << currentFloor << " ";
    info << object.position.x << " ";
    info << object.position.y << " ";
    info << object.position.z << " ";

    info << object.rotation.x << " ";
    info << object.rotation.y << " ";
    info << object.rotation.z << " ";

    info << object.scale.x << " ";
    info << object.scale.y << " ";
    info << object.scale.z << " ";

    int currentPathLength = QDir::currentPath().size();
    info << object.modelName.substr(currentPathLength) << " ";

    std::string texture = object.textureName.base;
    if(!texture.empty())
        texture = texture.substr(currentPathLength);
    info << texture << " ";

    info << object.type;

    return info.str();
}

ModelInfo CProjectManager::getObjectFromInfo(std::string line, int &currentFloor)
{
    istringstream iss(line);
    ModelInfo info;

    iss >> currentFloor;

    return info;
}
