//==========================================================
//
//  V5C2  --  src/piece.inl
//
//==========================================================


namespace v5c2
{
    Piece::Piece(Color color, Type type) :
        m_color{color},
        m_type{type}
    {}


    inline const Piece::Color& Piece::color() const
    {
        return m_color;
    }


    inline const Piece::Type& Piece::type() const
    {
        return m_type;
    }


    inline const iCoords& Piece::pos() const
    {
        return m_pos;
    }


    inline iCoords& Piece::pos()
    {
        return m_pos;
    }
}
