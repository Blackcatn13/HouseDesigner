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

    vector< vector<ModelInfo> > walls, objects;

    file.open(fileName.c_str());
    if(file.is_open())
    {
        getline(file, line);
        istringstream iss(line);
        iss >> totalFloors;
        getline(file, line);
        istringstream iss2(line);
        iss2 >> maxX;
        iss2 >> maxZ;
        

        for(int i=0;i<totalFloors;++i)
        {
            walls.push_back( vector<ModelInfo>());
            objects.push_back( vector<ModelInfo>());
        }

        while(getline(file, line))
        {
            // parse line (string) 
            info = getObjectFromInfo(line, currentFloor);
            if(info.type == WALL)
                walls[currentFloor].push_back(info);
            else if(info.type == OBJECT)
                objects[currentFloor].push_back(info);
        }
    }
    file.close();

    CScenary::getInstance()->setWalls(walls);
    CScenary::getInstance()->setObjects(objects);
    return true;
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
    if(texture.empty())
        texture = "NO_TEXTURE";
    info << texture << " ";

    texture = object.textureName.material.M1;
    if(texture.empty())
        texture = "NO_TEXTURE";
    info << texture << " ";

    texture = object.textureName.material.M2;
    if(texture.empty())
        texture = "NO_TEXTURE";
    info << texture << " ";

    texture = object.textureName.material.M3;
    if(texture.empty())
        texture = "NO_TEXTURE";
    info << texture << " ";

    texture = object.textureName.material.Mask;
    if(texture.empty())
        texture = "NO_TEXTURE";
    info << texture << " ";

    info << object.type;

    return info.str();
}

ModelInfo CProjectManager::getObjectFromInfo(std::string line, int &currentFloor)
{
    istringstream iss(line);
    ModelInfo info;

    iss >> currentFloor;
    iss >> info.position.x;
    iss >> info.position.y;
    iss >> info.position.z;

    iss >> info.rotation.x;
    iss >> info.rotation.y;
    iss >> info.rotation.z;

    iss >> info.scale.x;
    iss >> info.scale.y;
    iss >> info.scale.z;

    std::string model, texture;
    iss >> model;
    info.modelName = QDir::currentPath().toUtf8().constData() + model;
    iss >> texture;
    if(texture != "NO_TEXTURE")
        info.textureName.base = QDir::currentPath().toUtf8().constData() + texture;

    texture = "";
    iss >> texture;
    if(texture != "NO_TEXTURE")
        info.textureName.material.M1 = QDir::currentPath().toUtf8().constData() + texture;

    texture = "";
    iss >> texture;
    if(texture != "NO_TEXTURE")
        info.textureName.material.M2 = QDir::currentPath().toUtf8().constData() + texture;

    texture = "";
    iss >> texture;
    if(texture != "NO_TEXTURE")
        info.textureName.material.M3 = QDir::currentPath().toUtf8().constData() + texture;

    texture = "";
    iss >> texture;
    if(texture != "NO_TEXTURE")
        info.textureName.material.Mask = QDir::currentPath().toUtf8().constData() + texture;

    int type;
    iss >> type;
    info.type = static_cast<Types>(type);

    return info;
}
