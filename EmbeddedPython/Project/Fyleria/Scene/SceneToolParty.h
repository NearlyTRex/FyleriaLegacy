// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_SCENE_TOOL_PARTY_H_
#define _GECKO_SCENE_TOOL_PARTY_H_

// Internal includes
#include "Scene/Scene.h"
#include "Web/WebPageHandlerPartyTool.h"

namespace Gecko
{

class SceneToolParty : public Scene
{
public:

    // Constructor
    SceneToolParty();

    // Destructor
    virtual ~SceneToolParty();

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

    // Web page handler
    MAKE_RAW_TYPE_ACCESSORS(WebPageHandler, STDSharedPtr<WebPageHandlerPartyTool>);
};

// Typedef
MAKE_COMMON_TYPEDEFS(SceneToolParty);

};

#endif
