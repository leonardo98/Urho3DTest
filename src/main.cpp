#include <Urho3D/Engine/Application.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>
#include <Urho3D/Graphics/Renderer.h>

#ifdef WIN32
#define printf OutputDebugString
#endif

using namespace Urho3D;
class MyApp : public Application
{
private:
    bool m_mousePressed;
    SharedPtr<Scene> m_scene;
    SharedPtr<Node> m_cameraNode;
    SharedPtr<Node> m_spriterNode;
    int m_spriterAnimationIndex;
public:
    MyApp(Context* context)
        : Application(context)
        , m_mousePressed(false)
        , m_spriterAnimationIndex(0)
    {
    }
    virtual void Setup()
    {
        // Called before engine initialization. engineParameters_ member variable can be modified here
        engineParameters_["WindowTitle"] = "Urho3DTest";
        engineParameters_["LogName"]     = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
        engineParameters_["FullScreen"]  = false;
        engineParameters_["Headless"]    = false;
        engineParameters_["Sound"]       = false;
#ifdef WIN32
        engineParameters_["WindowWidth"] = 800;
        engineParameters_["WindowHeight"] = 600;
#endif
    }
    virtual void Start()
    {
        // Called after engine initialization. Setup application & subscribe to events here
        CreateScene();
        SetupViewport();

        SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(MyApp, HandleKeyDown));

        Input* input = GetSubsystem<Input>();

        input->SetMouseVisible(true);
        SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(MyApp, HandleMouseDown));
        SubscribeToEvent(E_MOUSEBUTTONUP, URHO3D_HANDLER(MyApp, HandleMouseUp));
        SubscribeToEvent(E_MOUSEMOVE, URHO3D_HANDLER(MyApp, HandleMouseMove));
        SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(MyApp, HandleUpdate));

        UnsubscribeFromEvent(E_SCENEUPDATE);
    }
    virtual void Stop()
    {
        // Perform optional cleanup after main loop has terminated
    }
    void HandleKeyDown(StringHash eventType, VariantMap& eventData)
    {
        using namespace KeyDown;
        // Check for pressing ESC. Note the engine_ member variable for convenience access to the Engine object
        int key = eventData[P_KEY].GetInt();
        if (key == KEY_ESCAPE)
            engine_->Exit();
    }
    // If the user clicks the canvas, attempt to switch to relative mouse mode on web platform
    void HandleMouseDown(StringHash eventType, VariantMap& eventData)
    {
        using namespace DragBegin;
        Input* input = GetSubsystem<Input>();
        if (input->GetMouseButtonDown(MOUSEB_LEFT))
        {
            printf("HandleMouseDown\n");
            m_mousePressed = true;
        }
    }

    void HandleMouseUp(StringHash eventType, VariantMap& eventData)
    {
        if (!m_mousePressed)
            return;
        printf("HandleMouseUp\n");
        m_mousePressed = false;
    }
    void HandleMouseMove(StringHash eventType, VariantMap& eventData)
    {
        if (!m_mousePressed)
            return;

        printf("HandleMouseMove\n");
    }
    void HandleDragCancel(StringHash eventType, VariantMap& eventData)
    {
        // cancel onMouseDown action
    }
    void CreateScene()
    {
        m_scene = new Scene(context_);
        m_scene->CreateComponent<Octree>();

        // Create camera node
        m_cameraNode = m_scene->CreateChild("Camera");
        // Set camera's position
        m_cameraNode->SetPosition(Vector3(0.0f, 0.0f, -10.0f));

        Camera* camera = m_cameraNode->CreateComponent<Camera>();
        camera->SetOrthographic(true);

        Graphics* graphics = GetSubsystem<Graphics>();
        camera->SetOrthoSize((float)graphics->GetHeight() * PIXEL_SIZE);
        camera->SetZoom(1.0f * Min((float)graphics->GetWidth() / 1280.0f, (float)graphics->GetHeight() / 800.0f)); // Set zoom according to user's resolution to ensure full visibility (initial zoom (1.0) is set for full visibility at 1280x800 resolution)

        ResourceCache* cache = GetSubsystem<ResourceCache>();

        AnimationSet2D* spriterAnimationSet = cache->GetResource<AnimationSet2D>("Urho2D/imp/imp.scml");
        if (!spriterAnimationSet)
            return;

        m_spriterNode = m_scene->CreateChild("SpriterAnimation");
        AnimatedSprite2D* spriterAnimatedSprite = m_spriterNode->CreateComponent<AnimatedSprite2D>();
        spriterAnimatedSprite->SetAnimationSet(spriterAnimationSet);
        spriterAnimatedSprite->SetAnimation(spriterAnimationSet->GetAnimation(m_spriterAnimationIndex));

        //// Get tmx file
        //TmxFile2D* tmxFile = cache->GetResource<TmxFile2D>("Urho2D/isometric_grass_and_water.tmx");
        //if (!tmxFile)
        //    return;

        //SharedPtr<Node> tileMapNode(scene_->CreateChild("TileMap"));
        //tileMapNode->SetPosition(Vector3(0.0f, 0.0f, -1.0f));

        //TileMap2D* tileMap = tileMapNode->CreateComponent<TileMap2D>();
        //// Set animation
        //tileMap->SetTmxFile(tmxFile);

        //// Set camera's position
        //const TileMapInfo2D& info = tileMap->GetInfo();
        //float x = info.GetMapWidth() * 0.5f;
        //float y = info.GetMapHeight() * 0.5f;
        //m_cameraNode->SetPosition(Vector3(x, y, -10.0f));
    }
    void HandleUpdate(StringHash eventType, VariantMap& eventData)
    {
        using namespace Update;

        // Take the frame time step, which is stored as a float
        float timeStep = eventData[P_TIMESTEP].GetFloat();

        // Move the camera, scale movement with time step
//        MoveCamera(timeStep);
    }
    void SetupViewport()
    {
        Renderer* renderer = GetSubsystem<Renderer>();

        // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
        SharedPtr<Viewport> viewport(new Viewport(context_, m_scene, m_cameraNode->GetComponent<Camera>()));
        renderer->SetViewport(0, viewport);
    }
};
URHO3D_DEFINE_APPLICATION_MAIN(MyApp)
