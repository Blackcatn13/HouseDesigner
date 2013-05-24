#ifndef SCENARY_H
#define SCENARY_H

#include "Util.h"
#include "utility"
#include <vector>
#include <qobject.h>

#define HEIGTH 3
//Maximum surface = 40*40*5 = 8000m2
#define MAXGRIDX 40
#define MAXGRIDZ 40
#define MAXFLOORS 5

typedef std::pair<ModelInfo, size_t> mInfoIndex;

class CScenary : public QObject
{
    Q_OBJECT
public:
    CScenary(QObject *parent = 0);
    ~CScenary(void);
    /*
        bool Draw()
        Function that draws all the walls and objects in the scenary over the current floor
    */
    bool Draw();
    /*
        bool addModel(ModelInfo)
        Function to add a model over the current floor
    */
    bool addModel(ModelInfo m_Info);
    /*
        static CScenary* getInstance()
        Function to get the instance of the singleton
    */
    static CScenary* getInstance();
    /*
        static int getMaxFloors()
        Function to get the maximum floors
    */
    static int getMaxFloors() {return MAXFLOORS;}
    /*
        void DrawAxis()
        Function to draw the Axis over the current floor
    */
    void DrawAxis();
    /*
        void DrawGrid()
        Function to draw the Grid over the current floor
    */
    void DrawGrid();
    /*
        void DrawFloor()
        Function to draw the floor of the current floor
    */
    void DrawFloor();
    /*
        void DrawCeil()
        Function to draw the ceiling of the current floor
    */
    void DrawCeil();
    /*
        void DrawStairs()
        Function to draw the stairs over the current floor
    */
    void DrawStairs();
    /*
        void CleanUp()
        Function to clean all the variables
    */
    void CleanUp();
    /*
        void setGridMaxX(int)
        Function to set the max X value of the grid
    */
    void setGridMaxX(int gridMaxX);
    /*
        void setGridMaxZ(int)
        Function to set the max Z value of the grid
    */
    void setGridMaxZ(int gridMaxZ);
    /*
        int getGridMaxX()
        Function to get the max X value of the grid
    */
    int getGridMaxX(){ return m_gridMaxX;}
    /*
        int getGridMaxZ()
        Function to get the max Z value of the grid
    */
    int getGridMaxZ(){ return m_gridMaxZ;}
    /*
        void addNewFloor()
        Function to add a new floor at the scenary
    */
    void addNewFloor();
    /*
        void fillFloor()
        Function to fill the floor and ceiling of the floors
    */
    void fillFloor();
    /*
        void ChangeFloor(int)
        Function to change the current floor
    */
    void ChangeFloor(int newFloor);
    /*
        int getCurrentFloor()
        Function to get the current floor
    */
    int getCurrentFloor(){ return activeFloor; }
    /*
        int getNFloors()
        Function to get the Number of floors
    */
    int getNFloors() {return m_nFloors;}
    /*
        Types getActiveType()
        Function to get the type of the selected model
    */
    Types getActiveType() {return activeType;}
    /*
        string getActiveModel()
        Function to get the name of the selected model
    */
    string getActiveModel() {return activeModel;}
    /*
        void setActiveModel(string)
        Function to set the name of the selected model
    */
    void setActiveModel(string model);
    /*
        void setActiveType(Types)
        Function to set the type of the selected model
    */
    void setActiveType(Types t);
    /*
        vector<vector<ModelInfo>> getWalls()
        Function to get the walls of the Scenary
    */
    vector< vector<ModelInfo> > getWalls() {return m_WallModels;}
    /*
        vector<vector<ModelInfo>> getObjects()
        Function to get the Objects of the Scenary
    */
    vector< vector<ModelInfo> > getObjects() {return m_ObjectModels;}
    /*
        vector<vector<int>> getScenaryMat()
        Function to get the ScenaryMat
    */
    vector< vector<int> > getScenaryMat();
    /*
        float getHeightForModels()
        Function to get at what height the models need to be put
    */
    float getHeightForModels() {return (HEIGTH * activeFloor);}
    void ClearFloor();
    /*
        void deleteFloor(int, int, int)
        Function to delete one Tile of the floor
    */
    void deleteFloor(int x, int z, int floor);

    bool getStairCollition(CPoint3D s, int rotation);
    ModelInfo getPickedObject(float x, float y, float z, size_t &index);
private:

    CScenary(void);
    /*
        Vector with all the Walls
    */
    vector< vector<ModelInfo> > m_WallModels;
    vector<mInfoIndex> m_PickableWall;
    /*
        Vector with all the Objects
    */
    vector< vector<ModelInfo> > m_ObjectModels;
    vector<mInfoIndex> m_PickableObject;
    /*
        Vector with all the Ceil or Floor
    */
    vector< vector<ModelInfo> > m_FloorModels;
    vector<mInfoIndex> m_PickableFloor;
    /*
        Vector with all the Stairs
    */
    vector< vector<ModelInfo> > m_StairModels;
    vector<mInfoIndex> m_PickableStair;
    /*
        Singleton variable
    */
    static CScenary* m_Scenary;
    /*
        Name of the selected model
    */
    string activeModel;
    /*
        Current floor
    */
    unsigned int activeFloor;
    /*
        Type of the selected model
    */
    Types activeType;
    /*
        bool getWall2WallCollision(ModelInfo)
        Function to calculate if exist a collision between Walls
    */
    bool getWall2WallCollision(ModelInfo mi);
    /*
        bool getWall2ObjectCollision(ModelInfo)
        Function to calculate if exist a collision between a wall and an object
    */
    bool getWall2ObjectCollision(ModelInfo mi);
    /*
        bool getObject2WallCollision(ModelInfo)
        Function to calculate if exist a collision between an object and a wall
    */
    bool getObject2WallCollision(ModelInfo mi);
    /*
        bool getObject2ObjectCollision(ModelInfo)
        Function to calculate if exist a collision between objects
    */
    bool getObject2ObjectCollision(ModelInfo mi);

    bool getStair2WallCollision(CPoint3D s, int rotation);

    bool getStair2StairCollision(CPoint3D s, int rotation);

    bool getStair2ObjectCollision(CPoint3D s, int rotation);

    bool getObject2StairCollision(ModelInfo mi);

    bool getWall2StairCollision(ModelInfo mi);

    
    /*
        Actual max X grid value
    */
    int m_gridMaxX;
    /*
        Actual max Z grid value
    */
    int m_gridMaxZ;
    /*
        Actual number of floors
    */
    int m_nFloors;
    //Debug frustrum culling.
    int m_printM;
    bool m_sphereDebug;
signals:
    void setNameModel(string name);
};

#endif
