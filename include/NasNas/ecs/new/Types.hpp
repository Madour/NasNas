// Created by Modar Nasser on 16/08/2021.
#pragma once

namespace ns::ecs {
    using Entity = unsigned long;
}

namespace ns::ecs::detail {
    using UID = unsigned long;
    UID get_next_id() {
        static UID counter = 0;
        return counter++;
    }

    template <class T>
    UID getTypeId() {
        static UID id = get_next_id();
        return id;
    }
}
