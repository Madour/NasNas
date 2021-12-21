/**
* Created by Modar Nasser on 25/04/2020.
**/


#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

#include <NasNas/core/data/Rect.hpp>

namespace ns {

    class AnimFrame {
    public:
        /**
         * \brief Constructs an AnimFrame object
         *
         * \param rectangle Frame rectangle on the spritesheet
         * \param duration Frame duration in milliseconds
         * \param origin Frame origin, {0, 0} = top left corner by default
         */
        AnimFrame(const ns::IntRect& rectangle, int duration, const sf::Vector2i& origin={0, 0});
        const ns::IntRect rectangle;    ///< Frame rectangle
        const int duration;         ///< Frame duration in milliseconds
        const sf::Vector2i origin;  ///< Frame origin
    };


    class Anim {
    public:
        /**
         * \brief Default constructor, constructs an empty nameless Anim object
         */
        Anim();

        /**
         * \brief Constructs an Anim object, describes one animation
         *
         * \param name Animation name
         * \param frames Vector of AnimFrame objects
         * \param loop Should the Anim loop when it ends ?
         */
        Anim(std::string name, std::vector<AnimFrame> frames, bool loop=true);

        /**
         * \brief Adds an AnimFrame to the Anim
         *
         * \param frame AnimFrame to add
         */
        void add(const AnimFrame& frame);

        /**
         * \brief Get the name of the Anim
         *
         * \return Anim name
         */
        auto getName() const -> const std::string&;

        /**
         * \brief Get a specific frame in the Anim
         *
         * \param index Index of the AnimFrame to get
         * \return AnimFrame object at the given index
         */
        auto getFrame(int index) const -> const AnimFrame&;

        /**
         * \brief Get the number of AnimFrame objects in the Anim
         * \return Number of AnimFrame in the Anim
         */
        auto size() const -> int;

        mutable bool loop = true;   ///< Should the Anim loop when it ends ?

    private:
        std::string m_name;             ///< Anim name
        std::vector<AnimFrame> m_frames;///< Vector of AnimFrames of the Anim
    };


    class AnimPlayer {
    public:
        /**
         * \brief Constructs an empty AnimPlayer
         */
        explicit AnimPlayer();

        /**
         * \brief Plays an Anim if it is different from the current Anim
         */
        void play(const Anim& animation);

        /**
         * \brief Plays an Anim from start even if it is the same as the currently running Anim
         */
        void replay(const Anim& animation);

        /**
         * \brief Replays the current Anim
         */
        void replay();

        /**
         * \brief Resume a paused or stoped animation
         */
        void resume();

        /**
         * \brief Pause the animation, the current active frame is not changed
         */
        void pause();

        /**
         * \brief Stop the animation and go back to first frame
         */
        void stop();

        /**
         * \brief Does what you expect it to do
         *
         * \return Returns if the animation is being played or not
         */
        auto isPlaying() const -> bool;

        /**
         * \brief Get the currentlty played Anim
         *
         * \return Pointer to Anim object
         */
        auto getAnim() const -> const Anim*;

        /**
         * \brief Get the active frame of the player
         *
         * \return The currently played frame
         */
        auto getActiveFrame() const -> const AnimFrame&;

        /**
         * \brief Set the play speed
         * \param speed Play speed. 0 stops the player; 1 is normal speed
         */
        void setPlaySpeed(float speed);

        /**
         * \brief Updates the AnimPlayer
         */
        void update();

        void update(sf::Sprite& spr);

    private:
        const Anim* m_anim = nullptr;     ///< Anim object currently played
        int m_index = 0;            ///< Current frame index
        bool m_playing = false;     ///< Is the AnimPlayer playing an Anim ?
        float m_play_speed = 1;     ///< Play speed of the player
        sf::Clock m_clock;          ///< Clock
    };

}
