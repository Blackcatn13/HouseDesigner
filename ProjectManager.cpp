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
    vector< vector<ModelInfo> > stairs = scenary->getStairs();
    vector< vector<ModelInfo> > floors = scenary->getFloors();
    ofstream file;
    file.open(fileName.c_str());
    int totalFloors = walls.size();
    int currentFloor = 0;

    file << totalFloors << endl;
    file << scenary->getGridMaxX() << " " << scenary->getGridMaxZ()<< endl;

    for(; currentFloor < totalFloors; ++currentFloor)
    {
        for(int index = 0; index < walls[currentFloor].size(); ++index)
            file << getInfoFromObject(currentFloor, walls[currentFloor][index]) << endl;
        for(int index = 0; index < objects[currentFloor].size(); ++index)
            file << getInfoFromObject(currentFloor, objects[currentFloor][index]) << endl;
        for(int index = 0; index < stairs[currentFloor].size(); ++index)
            file << getInfoFromObject(currentFloor, stairs[currentFloor][index]) << endl;
        for(int index = 0; index < floors[currentFloor].size(); ++index)
            file << getInfoFromObject(currentFloor, floors[currentFloor][index]) << endl;
    }
    for(int index = 0; index < floors[currentFloor].size(); ++index)
    {
        currentFloor;
        file << getInfoFromObject(currentFloor, floors[currentFloor][index]) << endl;
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

    vector< vector<ModelInfo> > walls, objects, stairs, floors;

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
            stairs.push_back( vector<ModelInfo>());
            floors.push_back( vector<ModelInfo>());
        }
        floors.push_back( vector<ModelInfo>());

        while(getline(file, line))
        {
            // parse line (string) 
            info = getObjectFromInfo(line, currentFloor);
            if(info.type == WALL)
                walls[currentFloor].push_back(info);
            else if(info.type == OBJECT)
                objects[currentFloor].push_back(info);
            else if(info.type == STAIR)
                stairs[currentFloor].push_back(info);
            else if(info.type == FLOOR)
                floors[currentFloor].push_back(info);
        }
    }
    file.close();

    CScenary::getInstance()->setWalls(walls);
    CScenary::getInstance()->setObjects(objects);
    CScenary::getInstance()->setStairs(stairs);
    CScenary::getInstance()->setFloors(floors);
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

    info << object.center.x << " ";
    info << object.center.y << " ";
    info << object.center.z << " ";

    info << object.radius << " ";

    int currentPathLength = QDir::currentPath().size();
    std::string currentPath = std::string(QDir::currentPath().toUtf8().data());
    
    std::string modelname = object.modelName;
    if(std::string::npos != object.modelName.find(currentPath))
        modelname = object.modelName.substr(currentPathLength);
    else
        modelname = object.modelName;
    if(modelname[0] != '/')
        info << '/';
    info << modelname << " ";

    std::string texture = object.textureName.ObjectName;
    if(texture.empty())
        texture = "NO_TEXTURE";
    else if(std::string::npos != object.textureName.ObjectName.find(currentPath))
        texture = object.textureName.ObjectName.substr(currentPathLength);
    if(texture[0] != '/' && texture != "NO_TEXTURE")
        info << '/';
    info << texture << " ";

    texture = object.textureName.material.M1;
    if(texture.empty())
        texture = "NO_TEXTURE";
    else if(std::string::npos != object.textureName.material.M1.find(currentPath))
        texture = object.textureName.material.M1.substr(currentPathLength);
    if(texture[0] != '/' && texture != "NO_TEXTURE")
        info << '/';
    info << texture << " ";

    texture = object.textureName.material.M2;
    if(texture.empty())
        texture = "NO_TEXTURE";
    else if(std::string::npos != object.textureName.material.M2.find(currentPath))
        texture = object.textureName.material.M2.substr(currentPathLength);
    if(texture[0] != '/' && texture != "NO_TEXTURE")
        info << '/';
    info << texture << " ";

    texture = object.textureName.material.M3;
    if(texture.empty())
        texture = "NO_TEXTURE";
    else if(std::string::npos != object.textureName.material.M3.find(currentPath))
        texture = object.textureName.material.M3.substr(currentPathLength);
    if(texture[0] != '/' && texture != "NO_TEXTURE")
        info << '/';
    info << texture << " ";

    texture = object.textureName.material.M4;
    if(texture.empty())
        texture = "NO_TEXTURE";
    else if(std::string::npos != object.textureName.material.M4.find(currentPath))
        texture = object.textureName.material.M4.substr(currentPathLength);
    if(texture[0] != '/' && texture != "NO_TEXTURE")
        info << '/';
    info << texture << " ";

    info << object.textureName.color.c1.x << " ";
    info << object.textureName.color.c1.y << " ";
    info << object.textureName.color.c1.z << " ";
    info << object.textureName.color.c2.x << " ";
    info << object.textureName.color.c2.y << " ";
    info << object.textureName.color.c2.z << " ";
    info << object.textureName.color.c3.x << " ";
    info << object.textureName.color.c3.y << " ";
    info << object.textureName.color.c3.z << " ";
    info << object.textureName.color.c4.x << " ";
    info << object.textureName.color.c4.y << " ";
    info << object.textureName.color.c4.z << " ";

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

    iss >> info.center.x;
    iss >> info.center.y;
    iss >> info.center.z;

    iss >> info.radius;

    std::string model, texture;
    iss >> model;
    info.modelName = QDir::currentPath().toUtf8().constData() + model;
    iss >> texture;
    if(texture != "NO_TEXTURE")
        info.textureName.ObjectName = QDir::currentPath().toUtf8().constData() + texture;

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
        info.textureName.material.M4 = QDir::currentPath().toUtf8().constData() + texture;

    iss >> info.textureName.color.c1.x;
    iss >> info.textureName.color.c1.y;
    iss >> info.textureName.color.c1.z;
    iss >> info.textureName.color.c2.x;
    iss >> info.textureName.color.c2.y;
    iss >> info.textureName.color.c2.z;
    iss >> info.textureName.color.c3.x;
    iss >> info.textureName.color.c3.y;
    iss >> info.textureName.color.c3.z;
    iss >> info.textureName.color.c4.x;
    iss >> info.textureName.color.c4.y;
    iss >> info.textureName.color.c4.z;

    int type;
    iss >> type;
    info.type = static_cast<Types>(type);

    return info;
}
