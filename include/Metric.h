#ifndef METRIC_H
#define METRIC_H
#include <vector>
#include <memory>
#include <cfloat>
#include <queue>
#include "Entity.h"
#include "Structures.h"
namespace sdaa{

/*-----------------------------------------------------------------------------------*/


class Metric
{
    public:
        /*------ methods ------ */
        Metric(int width,int height,int squareSize);
        std::vector<VectInt> pathfinding(VectInt const& beggin, VectInt const& dest); // Metric_PathFinding.cpp
        std::vector<VectInt> pathfinding(VectInt const& beggin, VectInt const& dest,float maxDistance); // Metric_PathFinding.cpp
        std::vector<VectInt> pathfinding(VectInt const& start, std::vector<VectInt> const& dests); // Metric_PathFinding.cpp

        static void initSquare(Square& square); // Metric_PathFinding.cpp
        void dynamicPathControl(bool BOTH = false);
        void setPath(Entity& entity, VectInt dest);
        void setPath(Entity& entity, VectInt dest,float maxDistance);
        void setPath(Entity& entity, std::vector<VectInt> dests); // do not work - creer un chemin vest l'element de dests qui est le plus proche


        float distance(Entity const& entityA, Entity const& entityB) const;
        float distance(Entity const& entity, VectFloat pos) const;
        float distance(VectFloat posA, VectFloat posB) const;
        float distance(VectInt posA, VectInt posB) const;
        bool isIn(int line, int col) const;
        /*-- getters/setters -- */
        void setOccupy(int line, int col,bool B);
        bool getOccupy(int line, int col) const;
        int getSquareSize() const;
        int getWidth() const;
        int getHeight() const;
        bool isOccupyChange(bool BOTH = false) const;
        void endPathControl();
        VectInt getSize() const;


        bool addEntity(Entity& entity);
        void deleteEntity(Entity& entity);

        void follow(Entity& entityToSetPath, Entity& entityToFollow);

    private:
        /*------ atributs ------ */
        std::vector<std::vector<bool>> m_occupy;
        std::vector<std::vector<bool>> m_close;
        std::vector<std::vector<bool>> m_open;
        std::vector<std::vector<Square>> m_squares;
        std::vector<Entity*> m_entities;
        int m_squareSize;
        int m_width;
        int m_height;
        bool m_changeOccupyTrue;
        bool m_changeOccupyFalse;
        /*------ methods ------ */
        std::vector<VectInt> getNearSquare(int col, int line) const;// Metric_PathFinding.cpp
        float CalculG(Square const& square) const;// Metric_PathFinding.cpp
        float CalculGWithOldParent(Square const& square) const;// Metric_PathFinding.cpp
        int CalculH(Square const& square, VectInt dest) const;// Metric_PathFinding.cpp
        void resetOpenAndClose();// Metric_PathFinding.cpp
};

/*-----------------------------------------------------------------------------------*/
}
#endif // METRIC_H
