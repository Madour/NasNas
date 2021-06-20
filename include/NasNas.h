/**
* Created by Modar Nasser on 23/04/2020.
**/

#pragma once


#include "NasNas/core/App.hpp"
#include "NasNas/core/Camera.hpp"
#include "NasNas/core/Scene.hpp"
#include "NasNas/core/Layer.hpp"
#include "NasNas/core/Window.hpp"
#include "NasNas/core/Debug.hpp"

#include "NasNas/core/data/Config.hpp"
#include "NasNas/core/data/Maths.hpp"
#include "NasNas/core/data/Logger.hpp"
#include "NasNas/core/data/Utils.hpp"

#include "NasNas/core/graphics/BitmapText.hpp"
#include "NasNas/core/graphics/ParticleSystem.hpp"
#include "NasNas/core/graphics/Shapes.hpp"
#include "NasNas/core/graphics/Sprite.hpp"
#include "NasNas/core/graphics/SpriteBatch.hpp"
#include "NasNas/core/graphics/VertexArray.hpp"

#ifdef NS_ECS
#include "NasNas/ecs/BaseEntity.hpp"
#include "NasNas/ecs/SpriteComponent.hpp"
#include "NasNas/ecs/ShapeComponent.hpp"
#endif

#ifdef NS_TILEMAPPING
#include "NasNas/tilemapping/TiledMap.hpp"
#include "NasNas/tilemapping/TileLayer.hpp"
#include "NasNas/tilemapping/ObjectLayer.hpp"
#endif

#ifdef NS_RESLIB
#include "NasNas/reslib/ResourceManager.hpp"
#endif

#ifdef NS_UI
#include "NasNas/ui/TypedText.hpp"
#endif

