// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_SCENE_MAIN_MENU_H_
#define _GECKO_SCENE_MAIN_MENU_H_

// Internal includes
#include "Scene/Scene.h"

namespace Gecko
{

class SceneMainMenu : public Scene
{
public:

    // Constructor
    SceneMainMenu();

    // Destructor
    virtual ~SceneMainMenu();

    // Start scene
    virtual void Start() override;

    // Finish scene
    virtual void Finish() override;

    // Update scene
    virtual void Update() override;

    // Handle scene input
    virtual void Input() override;

protected:

    // Handle message received
    virtual void OnMessageReceived(const String& sMessage) override;
};

// Typedef
MAKE_COMMON_TYPEDEFS(SceneMainMenu);

};

#endif
