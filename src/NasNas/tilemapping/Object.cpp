// Created by Modar Nasser on 28/06/2021.

#include <NasNas/tilemapping/Object.hpp>

#include <sstream>

#include <NasNas/thirdparty/pugixml.hpp>
#include <NasNas/tilemapping/TiledMap.hpp>

using namespace ns;
using namespace ns::tm;

auto stringToPoints(const char* points_str) -> std::vector<sf::Vector2f>;

Object::Object(const pugi::xml_node& xml_node, Shape shape) :
id(xml_node.attribute("id").as_uint()),
name(xml_node.attribute("name").as_string()),
type(xml_node.attribute("type").as_string()),
x(xml_node.attribute("x").as_float()),
y(xml_node.attribute("y").as_float()),
rotation(xml_node.attribute("rotation").as_float()),
shapetype(shape)
{
    parseProperties(xml_node.child("properties"));
}

auto Object::asPoint() -> PointObject& { return *dynamic_cast<PointObject*>(this); }
auto Object::asRectangle() -> RectangleObject& { return *dynamic_cast<RectangleObject*>(this); }
auto Object::asEllipse() -> EllipseObject& { return *dynamic_cast<EllipseObject*>(this); }
auto Object::asPolyline() -> PolylineObject& { return *dynamic_cast<PolylineObject*>(this); }
auto Object::asPolygon() -> PolygonObject& { return *dynamic_cast<PolygonObject*>(this); }
auto Object::asTile() -> TileObject& { return *dynamic_cast<TileObject*>(this); }

RectangleObject::RectangleObject(const pugi::xml_node& xml_node, const sf::Color& color) :
ShapeObject<sf::RectangleShape>(xml_node, color),
width(xml_node.attribute("width").as_float()),
height(xml_node.attribute("height").as_float())
{
    m_shape.setSize({width, height});
}

EllipseObject::EllipseObject(const pugi::xml_node& xml_node, const sf::Color& color) :
ShapeObject<ns::EllipseShape>(xml_node, color),
width(xml_node.attribute("width").as_float()),
height(xml_node.attribute("height").as_float())
{
    m_shape.setRadius({width/2.f, height/2.f});
}

PointObject::PointObject(const pugi::xml_node& xml_node, const sf::Color& color) :
ShapeObject<sf::CircleShape>(xml_node, color)
{
    m_shape.setRadius(1.f);
    m_shape.setOrigin(1.f, 1.f);
}

PolylineObject::PolylineObject(const pugi::xml_node& xml_node, const sf::Color& color) :
ShapeObject<ns::LineShape>(xml_node, color),
points(stringToPoints(xml_node.child("polyline").attribute("points").as_string()))
{
    for (auto& point : points)
        m_shape.addPoint(point);
}

PolygonObject::PolygonObject(const pugi::xml_node& xml_node, const sf::Color& color) :
ShapeObject<sf::ConvexShape>(xml_node, color),
points(stringToPoints(xml_node.child("polygon").attribute("points").as_string()))
{
    m_shape.setPointCount(points.size());
    for (unsigned i = 0; i < points.size(); ++i)
        m_shape.setPoint(i, points[i]);
}

TileObject::TileObject(const pugi::xml_node& xml_node, const sf::Color& color, TiledMap* tiledmap) :
ShapeObject<sf::Sprite>(xml_node, color),
width(xml_node.attribute("width").as_float()),
height(xml_node.attribute("height").as_float()),
gid(xml_node.attribute("gid").as_uint()&Tile::gidmask),
flip(Tile::getFlipFromGid(xml_node.attribute("gid").as_uint()))
{
    auto& tileset = tiledmap->getTileTileset(gid);
    auto tilewidth = static_cast<float>(tileset.data.tilewidth);
    auto tileheight = static_cast<float>(tileset.data.tileheight);
    m_shape.setTexture(tileset.data.getTexture());
    m_shape.setTextureRect(tileset.data.getTileTextureRect(gid - tileset.firstgid));
    m_shape.setScale(width/tilewidth, height/tileheight);
    m_shape.setOrigin(0, tileheight);

    // handle tile flips
    if ((flip&Tile::Flip::HorizontalFlip) != Tile::Flip::None) {
        m_shape.scale(-1, 1);
        m_shape.setOrigin(tilewidth, m_shape.getOrigin().y);
    }
    if ((flip&Tile::Flip::VerticalFlip) != Tile::Flip::None) {
        m_shape.scale(1, -1);
        m_shape.setOrigin(m_shape.getOrigin().x, 0);
    }
}

auto stringToPoints(const char* points_str) -> std::vector<sf::Vector2f> {
    std::vector<sf::Vector2f> result;
    std::string tmp;
    float x, y;

    std::istringstream points_stream{points_str};
    while (!points_stream.eof()) {
        std::getline(points_stream, tmp, ',');
        std::istringstream(tmp) >> x;
        std::getline(points_stream, tmp, ' ');
        std::istringstream(tmp) >> y;
        result.emplace_back(x, y);
    }
    return result;
}
