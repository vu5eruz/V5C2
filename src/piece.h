//==========================================================
//
//  V5C2  --  src/piece.h
//
//==========================================================


#ifndef V5C2_PIECE_H
#define V5C2_PIECE_H 1

#include "coords.h"

namespace v5c2
{
    class Piece
    {
    public:
        
        enum class Color
        {
            black,
            white
        };

        enum class Type
        {
            pawn,
            knight,
            bishop,
            rook,
            queen,
            king
        };

        Piece(Color color, Type type);

        inline const Color& color() const;

        inline const Type& type() const;

        inline const iCoords& pos() const;

        inline iCoords& pos();

    private:
        iCoords m_pos{};
        Color m_color{};
        Type m_type{};
    };
}

#include "piece.inl"

#endif // !V5C2_PIECE_H
