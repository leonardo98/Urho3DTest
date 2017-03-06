#include "TileMap.h"

#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Urho2D/Renderer2D.h>
#include <Urho3D/Graphics/Material.h>

void TileMap::RegisterObject(Context* context)
{
    context->RegisterFactory<TileMap>();//URHO2D_CATEGORY);
    URHO3D_COPY_BASE_ATTRIBUTES(Drawable2D);
}

TileMap::TileMap(Context* context)
    : Drawable2D(context)
    , m_spriteSheet(nullptr)
    , m_cellWidth(100)
    , m_cellHeight(50)
{
    sourceBatches_.Resize(1);
    sourceBatches_[0].owner_ = this;
}

void TileMap::InitNames()
{
    m_names.clear();

    // TODO: remove this line
    m_names.push_back("greenTile_0");
    m_names.push_back("brownTile_0");
    m_names.push_back("lightBrownStoneTile_0");
    m_names.push_back("yellowTile_0");
    // end to remove

    m_names.push_back("greenTile_0");
    m_names.push_back("greenTile_33");
    m_names.push_back("greenTile_66");
    m_names.push_back("brownTile_0");
    m_names.push_back("brownTile_33");
    m_names.push_back("brownTile_66");
    m_names.push_back("lightBrownStoneTile_0");
    m_names.push_back("lightBrownStoneTile_33");
    m_names.push_back("lightBrownStoneTile_66");
    m_names.push_back("yellowTile_0");
    m_names.push_back("yellowTile_33");
    m_names.push_back("yellowTile_66");
    m_names.push_back("blueStoneTile_0");
    m_names.push_back("blueStoneTile_33");
    m_names.push_back("blueStoneTile_66");
    m_names.push_back("redStoneTile_0");
    m_names.push_back("redStoneTile_33");
    m_names.push_back("redStoneTile_66");
    m_names.push_back("lightGreenTile_0");
    m_names.push_back("lightGreenTile_33");
    m_names.push_back("lightGreenTile_66");
    m_names.push_back("lightBlueTile_0");
    m_names.push_back("lightBlueTile_33");
    m_names.push_back("lightBlueTile_66");
    m_names.push_back("brickR_0");
    m_names.push_back("brickR_33");
    m_names.push_back("brickR_66");
    m_names.push_back("brickL_0");
    m_names.push_back("brickL_33");
    m_names.push_back("brickL_66");
    m_names.push_back("brickC_0");
    m_names.push_back("brickC_33");
    m_names.push_back("brickC_66");
    m_names.push_back("brownStoneTile_0");
    m_names.push_back("brownStoneTile_33");
    m_names.push_back("brownStoneTile_66");
    m_names.push_back("turquoiseTile_0");
    m_names.push_back("turquoiseTile_33");
    m_names.push_back("turquoiseTile_66");

    m_names.push_back("whiteTile_0");
    m_names.push_back("whiteTile_33");
    m_names.push_back("whiteTile_66");
    m_names.push_back("flat1_0");
    m_names.push_back("flat1_33");
    m_names.push_back("flat1_66");
    m_names.push_back("flat2_0");
    m_names.push_back("flat2_33");
    m_names.push_back("flat2_66");
    m_names.push_back("flat3_0");
    m_names.push_back("flat3_33");
    m_names.push_back("flat3_66");
    m_names.push_back("flat4_0");
    m_names.push_back("flat4_33");
    m_names.push_back("flat4_66");
    m_names.push_back("round4_0");
    m_names.push_back("round4_33");
    m_names.push_back("round4_66");
    m_names.push_back("cubic2_0");
    m_names.push_back("cubic2_33");
    m_names.push_back("cubic2_66");
    m_names.push_back("grayStoneTile_0");
    m_names.push_back("grayStoneTile_33");
    m_names.push_back("grayStoneTile_66");
    m_names.push_back("cubic3_0");
    m_names.push_back("cubic3_33");
    m_names.push_back("cubic3_66");
    m_names.push_back("fullBlackTileWall_0");
    m_names.push_back("fullBlackTileWall_33");
    m_names.push_back("fullBlackTileWall_66");
    m_names.push_back("cubic4_0");
    m_names.push_back("cubic4_33");
    m_names.push_back("cubic4_66");
    m_names.push_back("expFunnel_0");
    m_names.push_back("expFunnel_33");
    m_names.push_back("expFunnel_66");
    m_names.push_back("cubic1_0");
    m_names.push_back("cubic1_33");
    m_names.push_back("cubic1_66");
    m_names.push_back("blackTile_0");
    m_names.push_back("blackTile_33");
    m_names.push_back("blackTile_66");
    m_names.push_back("round1_0");
    m_names.push_back("round1_33");
    m_names.push_back("round1_66");
    m_names.push_back("blueTile_0");
    m_names.push_back("blueTile_33");
    m_names.push_back("blueTile_66");
    m_names.push_back("round2_0");
    m_names.push_back("round2_33");
    m_names.push_back("round2_66");
    m_names.push_back("round3_0");
    m_names.push_back("round3_33");
    m_names.push_back("round3_66");
}

void TileMap::Init(unsigned int width, unsigned int height, unsigned int cellWidth, unsigned int cellHeight)
{
    m_fieldWidth = cellWidth;
    m_fieldHeight = cellHeight;
    m_field.resize(width);
    for (auto &column: m_field)
    {
        column.resize(height);
        for (auto &cell: column)
        {
            cell = -1;
        }
    }

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    m_spriteSheet = cache->GetResource<SpriteSheet2D>("Custom/tiles2.xml");
    if (!m_spriteSheet)
        return;

    InitNames();
    UpdateMaterial();
}

void TileMap::SetFieldCell(unsigned int i, unsigned int j, char index)
{
    m_field[i][j] = index;
    sourceBatchesDirty_ = true;
    MarkNetworkUpdate();
}

void TileMap::UpdateSourceBatches()
{
    Vector3 shiftX(m_cellWidth / 2 * PIXEL_SIZE, m_cellHeight / 2 * PIXEL_SIZE, 0.f);
    Vector3 shiftY(- m_cellWidth / 2 * PIXEL_SIZE, m_cellHeight / 2 * PIXEL_SIZE, 0.f);

    Vector<Vertex2D>& vertices = sourceBatches_[0].vertices_;
    vertices.Clear();

    Rect drawRect;
    Rect textureRect;
    Sprite2D *sprite;

    Vertex2D vertex0;
    Vertex2D vertex1;
    Vertex2D vertex2;
    Vertex2D vertex3;

    const Matrix3x4& worldTransform = node_->GetWorldTransform();

    vertex0.color_ = vertex1.color_ = vertex2.color_ = vertex3.color_ = 0xFFFFFFFF;

    for (unsigned int i = 0; i < m_field.size(); i++)
    {
        for (unsigned int j = 0; j < m_field[i].size(); j++)
        {
            if (m_field[i][j] != -1)
            {
                sprite = m_spriteSheet->GetSprite(m_names[m_field[i][j]].c_str());
                if (!sprite->GetDrawRectangle(drawRect))
                    continue;
                if (!sprite->GetTextureRectangle(textureRect))
                    continue;

                Vector3 shift(i * shiftX + j * shiftY);

                // Convert to world space
                vertex0.position_ = worldTransform * Vector3(drawRect.min_.x_, drawRect.min_.y_, 0.0f) + shift;
                vertex1.position_ = worldTransform * Vector3(drawRect.min_.x_, drawRect.max_.y_, 0.0f) + shift;
                vertex2.position_ = worldTransform * Vector3(drawRect.max_.x_, drawRect.max_.y_, 0.0f) + shift;
                vertex3.position_ = worldTransform * Vector3(drawRect.max_.x_, drawRect.min_.y_, 0.0f) + shift;

                vertex0.uv_ = textureRect.min_;
                vertex1.uv_ = Vector2(textureRect.min_.x_, textureRect.max_.y_);
                vertex2.uv_ = textureRect.max_;
                vertex3.uv_ = Vector2(textureRect.max_.x_, textureRect.min_.y_);

                vertices.Push(vertex0);
                vertices.Push(vertex1);
                vertices.Push(vertex2);
                vertices.Push(vertex3);
            }
        }
    }

    sourceBatchesDirty_ = false;
}

void TileMap::UpdateMaterial()
{
    if (m_names.empty())
        return;
    Sprite2D *sprite = m_spriteSheet->GetSprite(m_names[0].c_str());
    sourceBatches_[0].material_ = renderer_->GetMaterial(sprite->GetTexture(), BLEND_ALPHA);
}

void TileMap::OnDrawOrderChanged()
{
    sourceBatches_[0].drawOrder_ = GetDrawOrder();
}

void TileMap::OnWorldBoundingBoxUpdate()
{
    boundingBox_.Clear();
    worldBoundingBox_.Clear();

    const Vector<SourceBatch2D>& sourceBatches = GetSourceBatches();
    for (unsigned i = 0; i < sourceBatches[0].vertices_.Size(); ++i)
        worldBoundingBox_.Merge(sourceBatches[0].vertices_[i].position_);

    boundingBox_ = worldBoundingBox_.Transformed(node_->GetWorldTransform().Inverse());
}
