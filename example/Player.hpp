/**
* Created by Modar Nasser on 07/06/2020.
**/

#pragma once

#include "../NasNas.h"
#include <cmath>

class Player : public ns::BaseEntity {
public:
    Player();
    ~Player() override;
    void update() override;
private:
    ns::Sprite* m_ns_sprite = nullptr;
};

