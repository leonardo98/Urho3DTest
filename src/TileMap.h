#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/Component.h>
#include <Urho3D/Urho2D/SpriteSheet2D.h>
#include <Urho3D/Container/Vector.h>

#include <vector>
#include <string>

using namespace Urho3D;

typedef Vector<SharedPtr<Node>> VectorColumn;

class SmallField : public Component
{
URHO3D_OBJECT(SmallField, Component);
private:
    Vector<VectorColumn> m_field;//m_field[x][y] - x is row index, y is column index (it means vector of columns)
public:
    SmallField(Context* context);
    void Init(unsigned int width, unsigned int height);
    SharedPtr<Node> SetCell(unsigned int i, unsigned int j, Sprite2D *sprite);
};

class TileMap : public Component
{
URHO3D_OBJECT(TileMap, Component);
private:
    SharedPtr<SpriteSheet2D> m_spriteSheet;
    Vector<VectorColumn> m_bigField;
    unsigned int m_smallFieldWidth;
    unsigned int m_smallFieldHeight;
    const int m_cellWidth;
    const int m_cellHeight;
    std::vector<std::string> m_names;
    
    void CreateSmallField(unsigned int row, unsigned int col);
public:
    TileMap(Context* context);
    void Init(unsigned int rowMax, unsigned int colMax, unsigned int smallFieldWidth, unsigned int smallFieldHeight);
    void SetFieldCell(unsigned int i, unsigned int j, int index);
};

#endif//TILE_MAP_H
