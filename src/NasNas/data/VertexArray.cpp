/**
* Created by Modar Nasser on 19/12/2020.
**/

#include "NasNas/data/VertexArray.hpp"


auto ns::VertexArray::getPosition() const -> sf::Vector2f {
    auto&& bounds = getBounds();
    return {bounds.left, bounds.top};
}

auto ns::VertexArray::getGlobalBounds() const -> ns::FloatRect {
    return ns::FloatRect(getBounds());
}
