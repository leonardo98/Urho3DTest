#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/IO/FileSystem.h>

#include <Urho3D/UI/UIEvents.h>

using namespace Urho3D;
class MyApp : public Application
{
private:
    bool m_mousePressed;
public:
    MyApp(Context* context)
        : Application(context)
        , m_mousePressed(false)
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
    }
    virtual void Start()
    {
        // Called after engine initialization. Setup application & subscribe to events here
        SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(MyApp, HandleKeyDown));

        Input* input = GetSubsystem<Input>();

        input->SetMouseVisible(true);
        SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(MyApp, HandleMouseDown));
        SubscribeToEvent(E_MOUSEBUTTONUP, URHO3D_HANDLER(MyApp, HandleMouseUp));
        SubscribeToEvent(E_MOUSEMOVE, URHO3D_HANDLER(MyApp, HandleMouseMove));
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
};
URHO3D_DEFINE_APPLICATION_MAIN(MyApp)
