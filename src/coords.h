//==========================================================
//
//  V5C2  --  src/coords.h
//
//==========================================================


#ifndef V5C2_COORDS_H
#define V5C2_COORDS_H 1

namespace v5c2
{
    template <typename T>
    class Coords
    {
    public:

        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;

        constexpr Coords() = default;

        constexpr Coords(value_type x, value_type y);

        constexpr const_reference x() const;

        constexpr reference x();

        constexpr const_reference y() const;

        constexpr reference y();

    private:
        value_type m_x{};
        value_type m_y{};
    };

    using iCoords = Coords<int>;
}

#include "coords.inl"

#endif // !V5C2_COORDS_H
