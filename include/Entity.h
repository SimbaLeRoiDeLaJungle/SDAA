#ifndef ENTITY_H
#define ENTITY_H
#include "Structures.h"
#include <vector>
namespace sdaa {
class Entity
{
    public:
        enum Mode {WAIT, MOVE,REQUESTPATH,FOLLOW};
        /* ------ methods ------ */
        Entity(int line, int col,int squareSize,float velocity);
        Entity();
        Entity(int line, int col,int squareSize);
        void updateEntityPosition();
        void stop();
        VectFloat getFullPosition() const;


        /* -- getters/setters -- */

        void setPositionInMetric(int line, int col);
        VectInt getPositionInMetric() const;

        void setMode(Entity::Mode mode);
        Entity::Mode getMode() const;

        void setOffset(float dl, float dc);
        VectFloat getOffset() const;

        // /!\ Do not Use -> Ces fonctions sont faite pour etre utiliser par la classe Metric, les utlisier pendant l'execution du programme sans
        // prendre garde de cet avertissement peut causer des bugs ou des comportements non prévus.
        // NOTE : pour modifier la position d'une entitée il faut utliser la methode Metric::setPath(Entity const& myEntity, VectInt destination)
        // ou une autre methode est de passer l'entité en mode Entity::REQUESTPATH et changer m_dest avec la methode setDest(VectInt dest), ensuite
        // si vous passer une valeur a dest et que vous metterz l'entité en mode REQUESTPATH, lors du passage dans Metric::DynamicPathControl,
        // la metric va donner un nouveau chemin vers la destination a votre entité.
        void setPath(std::vector<VectInt> const& path);
        void setPath(std::vector<VectInt> const& path,int begin);
        void setPath(std::vector<VectInt> const& path, int begin, int pathSize);


        VectInt getPath(unsigned int i) const;
        size_t getPathSize() const;

        void setVelocity(float velocity);
        float getVelocity() const;

        void setSquareSize(int squareSize);
        int getSquareSize() const;

        VectInt getDest() const;
        void setDest(VectInt const& dest);

        bool setTarget(Entity& entity);
        VectInt getTargetPosInMetric() const;
        Entity::Mode getTargetMode() const;
        int getTargetMetricID() const;
        bool asATarget() const;
        VectFloat getTargetFullPosition() const;

        void setMetricID(int id); // Do note use -> cette methode ne doit etre utiliser que dans la classe Metric
        int getMetricID() const;

        void setUpdateFollowCount(int i);
        int getUpdateFollowCount() const;

        int getMaxUpdateFollowCount() const;
        void setMaxUpdateFollowCount(int i);

        void stopToFollow(bool saveTarget = false);

    private:
        VectInt m_positionInMetric;
        VectFloat m_offset;
        std::vector<VectInt> m_path;
        VectInt m_dest;
        int m_squareSize;
        Entity::Mode m_mode = Entity::WAIT;
        float m_velocity;
        Entity* m_target;
        int m_metricID;
        int m_updateFollowCount;
        int m_maxUpdateFollowCount;

};
}
#endif // ENTITY_H
