/**
* Created by Modar Nasser on 19/12/2020.
**/

#include <NasNas/core/graphics/VertexArray.hpp>

auto ns::VertexArray::getPosition() const -> sf::Vector2f {
    auto bounds = getBounds();
    return {bounds.left, bounds.top};
}

void ns::VertexArray::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = m_texture;
    target.draw(static_cast<sf::VertexArray>(*this), states);
}
