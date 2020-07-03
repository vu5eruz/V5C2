//==========================================================
//
//  V5C2  --  src/coords.inl
//
//==========================================================


namespace v5c2
{
    template <typename T>
    constexpr Coords<T>::Coords(value_type x, value_type y) :
        m_x{x},
        m_y{y}
    {}

    
    template <typename T>
    constexpr typename Coords<T>::const_reference Coords<T>::x() const
    {
        return m_x;
    }


    template <typename T>
    constexpr typename Coords<T>::reference Coords<T>::x()
    {
        return m_x;
    }


    template <typename T>
    constexpr typename Coords<T>::const_reference Coords<T>::y() const
    {
        return m_y;
    }


    template <typename T>
    constexpr typename Coords<T>::reference Coords<T>::y()
    {
        return m_y;
    }
}
