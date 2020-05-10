/**
* Created by Modar Nasser on 26/04/2020.
**/

#include "Sprites.hpp"

Sprites::Sprites():
player_spr(
    "player",
    ns::Res::get().getTexture("adventurer"),
    {
        {"idle", ns::Anim(
            {
                ns::AnimFrame({14, 7, 19, 29}, 300, {11, 29}),
                ns::AnimFrame({66, 6, 17, 30}, 300, {9, 30})
            },
            true
        )}
    }
)
,player_spr2 (
    "player",
    ns::Res::get().getTexture("adventurer"),
    {
        {"idle", ns::Anim(
            {
                ns::AnimFrame({100, 100, 19, 29}, 300, {11, 29}),
                ns::AnimFrame({166, 100, 17, 30}, 300, {9, 30})
            },
            true
        )}
    }
)
{}

Sprites::~Sprites() = default;


