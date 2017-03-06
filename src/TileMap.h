#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <Urho3D//Urho2D/Drawable2D.h>
//#include <Urho3D/Engine/Engine.h>
//#include <Urho3D/Scene/Scene.h>
//#include <Urho3D/Scene/Component.h>
#include <Urho3D/Urho2D/SpriteSheet2D.h>
//#include <Urho3D/Container/Vector.h>

#include <vector>
#include <string>

using namespace Urho3D;

class TileMap : public Drawable2D
{
URHO3D_OBJECT(TileMap, Drawable2D);
private:
    SharedPtr<SpriteSheet2D> m_spriteSheet;
    unsigned int m_fieldWidth;
    unsigned int m_fieldHeight;
    const int m_cellWidth;
    const int m_cellHeight;
    std::vector<std::string> m_names;
    std::vector<std::vector<signed char>> m_field;

    void InitNames();

protected:
    /// Update source batches.
    virtual void UpdateSourceBatches();
    virtual void UpdateMaterial();
    virtual void OnDrawOrderChanged();
    virtual void OnWorldBoundingBoxUpdate();
public:
    TileMap(Context* context);
    void Init(unsigned int width, unsigned int height, unsigned int cellWidth, unsigned int cellHeight);
    void SetFieldCell(unsigned int i, unsigned int j, char index);
    static void RegisterObject(Context* context);
};

#endif//TILE_MAP_H
