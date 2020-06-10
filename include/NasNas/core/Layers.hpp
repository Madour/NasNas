/**
* Created by Modar Nasser on 15/04/2020.
**/

#pragma once

#include <SFML/Graphics.hpp>
#include "NasNas/data/AppComponent.hpp"

namespace ns {

    class Layer: public sf::Drawable {
        //using DrawablesTypes = std::variant<ns::Drawable*, sf::Shape*, sf::Text* >;
        using DrawablesTypes = std::variant<std::shared_ptr<ns::Drawable>, std::shared_ptr<sf::Shape>, std::shared_ptr<sf::Text> >;
        public:
            explicit Layer(const std::string& name);

            void add(const std::shared_ptr<ns::Drawable>& drawable);
            void add(const std::shared_ptr<sf::Shape>& drawable);
            void add(const std::shared_ptr<sf::Text>& drawable);

            auto getDrawables() -> std::vector<DrawablesTypes>&;

            void ySort();

            auto getName() -> const std::string&;

        private:
            std::string m_name;
            std::vector<DrawablesTypes> m_drawables;
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
