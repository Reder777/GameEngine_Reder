#pragma once
/*
sandbox must include "reder.h"
all reference and library be used by actual sandbox
*/

#include "reder/core/application.h"
#include "reder/core/log.h"
#include "reder/core/layer.h"
#include "reder/core/input.h"
#include "reder/core/timeStamp.h"
#include "reder/imgui/imguiLayer.h"

/*
---------------reder's event system ---------------------------------------
*/


#include "reder/event/event.h"
#include "reder/event/keyboardEvent.h"
#include "reder/event/mouseEvent.h"
#include "reder/event/appEvent.h"
#include "reder/event/windowEvent.h"


/*
-----------------------------reder's own code def ---------------------------------------
*/

#include "reder/codesDef/keyCodes.h"
#include "reder/codesDef/mouseButton.h"

/*
-----------------------------renderer files ---------------------------------------------
*/
#include "reder/renderer/buffers.h"
#include "reder/renderer/shader.h"
#include "reder/renderer/renderer.h"
#include "reder/renderer/orthographicCamera.h"
#include "reder/renderer/grahpicsContext.h"
#include "reder/renderer/vertexArray.h"
#include "reder/renderer/renderCommand.h"
#include "reder/renderer/texture.h"
#include "reder/renderer/renderer2d.h"
/*
-------------------------------profile---------------------------------------------------
*/
#include "reder/debug/instrumentor.h"


/*
-----------------------------------------------------------------------------------------
*/
#include "reder/orthographicCameraController.h"
#include <stdio.h>
