/**
* Created by Modar Nasser on 19/12/2020.
**/

#include "NasNas/core/graphics/VertexArray.hpp"


auto ns::VertexArray::getPosition() const -> sf::Vector2f {
    auto bounds = getBounds();
    return {bounds.left, bounds.top};
}
