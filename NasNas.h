/**
* Created by Modar Nasser on 23/04/2020.
**/

#pragma once

#include "NasNas/data/Config.hpp"
#include "NasNas/data/Maths.hpp"
#include "NasNas/data/Shapes.hpp"

#ifdef NS_ECS
#include "NasNas/ecs/BaseEntity.hpp"
#include "NasNas/ecs/SpriteComponent.hpp"
#include "NasNas/ecs/ShapeComponent.hpp"
#endif

#ifdef NS_TILEMAPPING
#include "NasNas/tilemapping/TiledMap.hpp"
#endif

#ifdef NS_RESLIB
#include "NasNas/reslib/ResourceManager.hpp"
#endif

#ifdef NS_UI
#include "NasNas/ui/TypedText.hpp"
#endif

#include "NasNas/core/App.hpp"
#include "NasNas/core/Camera.hpp"
#include "NasNas/core/Scene.hpp"
#include "NasNas/core/Layers.hpp"
#include "NasNas/core/BitmapText.hpp"
#include "NasNas/core/Window.hpp"
#include "NasNas/core/Logger.hpp"
#include "NasNas/core/Debug.hpp"
