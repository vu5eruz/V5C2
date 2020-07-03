//==========================================================
//
//  V5C2  --  src/main.cpp
//
//==========================================================


#include "board.h"
#include "main.h"
#include "piece.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>


namespace v5c2
{
    using Chess_board = Board<Piece*, 8, 8>;

    typename Chess_board::index_type index_from_notation(const std::string_view& text)
    {
        typename Chess_board::index_type index{};

        // rank, X axis
        switch (text[0])
        {
            case 'a': index.first = 0; break;
            case 'b': index.first = 1; break;
            case 'c': index.first = 2; break;
            case 'd': index.first = 3; break;
            case 'e': index.first = 4; break;
            case 'f': index.first = 5; break;
            case 'g': index.first = 6; break;
            case 'h': index.first = 7; break;
        }

        // file, Y axis
        switch (text[1])
        {
            case '8': index.second = 0; break;
            case '7': index.second = 1; break;
            case '6': index.second = 2; break;
            case '5': index.second = 3; break;
            case '4': index.second = 4; break;
            case '3': index.second = 5; break;
            case '2': index.second = 6; break;
            case '1': index.second = 7; break;
        }

        return index;
    }

    void print_board(const Chess_board& board)
    {
#ifdef V5C2_PLATFORM_WINDOWS
        std::system("cls");
#else
        std::system("clear");
#endif

        std::cout << 
        "   a  b  c  d  e  f  g  h\n"
        "  +--+--+--+--+--+--+--+--+\n";

        for (std::size_t y = 0; y < board.height; y++)
        {
            char letter{static_cast<char>('8' - y)};

            std::cout.put(letter);
            std::cout.put(' ');

            for (std::size_t x = 0; x < board.width; x++)
            {
                const auto* piece{board.at({x, y})};

                std::cout << '|';

                if (piece)
                {
                    std::cout.put((piece->color() == Piece::Color::white) ? 'w' : 'b');
                    switch (piece->type())
                    {
                        case Piece::Type::pawn: std::cout.put('P'); break;
                        case Piece::Type::knight: std::cout.put('N'); break;
                        case Piece::Type::bishop: std::cout.put('B'); break;
                        case Piece::Type::rook: std::cout.put('R'); break;
                        case Piece::Type::queen: std::cout.put('Q'); break;
                        case Piece::Type::king: std::cout.put('K'); break;
                    }
                }
                else
                {
                    std::cout.put(' ');
                    std::cout.put(' ');
                }
            }

            if (y != 7)
            {
                std::cout << "| " << letter << "\n  +--+--+--+--+--+--+--+--+\n";
            }
        }

        std::cout << "| 1\n"
            "  +--+--+--+--+--+--+--+--+\n"
            "   a  b  c  d  e  f  g  h\n"
        << std::endl;
    }

    void play()
    {
        Chess_board board{};

        board.at(index_from_notation("a8")) = new Piece(Piece::Color::black, Piece::Type::rook);
        board.at(index_from_notation("b8")) = new Piece(Piece::Color::black, Piece::Type::knight);
        board.at(index_from_notation("c8")) = new Piece(Piece::Color::black, Piece::Type::bishop);
        board.at(index_from_notation("d8")) = new Piece(Piece::Color::black, Piece::Type::queen);
        board.at(index_from_notation("e8")) = new Piece(Piece::Color::black, Piece::Type::king);
        board.at(index_from_notation("f8")) = new Piece(Piece::Color::black, Piece::Type::bishop);
        board.at(index_from_notation("g8")) = new Piece(Piece::Color::black, Piece::Type::knight);
        board.at(index_from_notation("h8")) = new Piece(Piece::Color::black, Piece::Type::rook);

        board.at(index_from_notation("a7")) = new Piece(Piece::Color::black, Piece::Type::pawn);
        board.at(index_from_notation("b7")) = new Piece(Piece::Color::black, Piece::Type::pawn);
        board.at(index_from_notation("c7")) = new Piece(Piece::Color::black, Piece::Type::pawn);
        board.at(index_from_notation("d7")) = new Piece(Piece::Color::black, Piece::Type::pawn);
        board.at(index_from_notation("e7")) = new Piece(Piece::Color::black, Piece::Type::pawn);
        board.at(index_from_notation("f7")) = new Piece(Piece::Color::black, Piece::Type::pawn);
        board.at(index_from_notation("g7")) = new Piece(Piece::Color::black, Piece::Type::pawn);
        board.at(index_from_notation("h7")) = new Piece(Piece::Color::black, Piece::Type::pawn);

        board.at(index_from_notation("a1")) = new Piece(Piece::Color::white, Piece::Type::rook);
        board.at(index_from_notation("b1")) = new Piece(Piece::Color::white, Piece::Type::knight);
        board.at(index_from_notation("c1")) = new Piece(Piece::Color::white, Piece::Type::bishop);
        board.at(index_from_notation("d1")) = new Piece(Piece::Color::white, Piece::Type::queen);
        board.at(index_from_notation("e1")) = new Piece(Piece::Color::white, Piece::Type::king);
        board.at(index_from_notation("f1")) = new Piece(Piece::Color::white, Piece::Type::bishop);
        board.at(index_from_notation("g1")) = new Piece(Piece::Color::white, Piece::Type::knight);
        board.at(index_from_notation("h1")) = new Piece(Piece::Color::white, Piece::Type::rook);

        board.at(index_from_notation("a2")) = new Piece(Piece::Color::white, Piece::Type::pawn);
        board.at(index_from_notation("b2")) = new Piece(Piece::Color::white, Piece::Type::pawn);
        board.at(index_from_notation("c2")) = new Piece(Piece::Color::white, Piece::Type::pawn);
        board.at(index_from_notation("d2")) = new Piece(Piece::Color::white, Piece::Type::pawn);
        board.at(index_from_notation("e2")) = new Piece(Piece::Color::white, Piece::Type::pawn);
        board.at(index_from_notation("f2")) = new Piece(Piece::Color::white, Piece::Type::pawn);
        board.at(index_from_notation("g2")) = new Piece(Piece::Color::white, Piece::Type::pawn);
        board.at(index_from_notation("h2")) = new Piece(Piece::Color::white, Piece::Type::pawn);

        for (;;)
        {
            print_board(board);

            std::string cmd{};
            std::cout << "\n> ";
            if (!(std::cin >> cmd))
            {
                break;
            }

            typename Chess_board::index_type selection{};
            for (auto cmditer{ cmd.begin() }; cmditer != cmd.end(); ++cmditer)
            {
                switch (*cmditer)
                {
                    case '.': // SELECT SQUARE
                    {
                        char locbuf[2] = {cmditer[1], cmditer[2]};
                        std::string_view loc(locbuf, 2);
                        selection = index_from_notation(loc);
                        cmditer += 2;
                        break;
                    }

                    case ',': // MOVE SELECTED SQUARE TO LOCATION
                    {
                        char locbuf[2] = { cmditer[1], cmditer[2] };
                        std::string_view loc(locbuf, 2);
                        auto target = index_from_notation(loc);
                        delete board.at(target);
                        board.at(target) = board.at(selection);
                        board.at(selection) = nullptr;
                        break;
                    }

                    case 'x': // KILL SQUARE
                    {
                        delete board.at(selection);
                        board.at(selection) = nullptr;
                        break;
                    }
                }
            }
        }
    }

    void main()
    {
        std::ios::sync_with_stdio(false);
        std::cout <<
        "V5C2\n"
        "  vu5eruz's chess for two\n"
        "  version " V5C2_VERSION " ("
#if defined(V5C2_PLATFORM_LINUX)
        "Linux"
#elif defined(V5C2_PLATFORM_APPLE)
        "Mac OS"
#elif defined(V5C2_PLATFORM_WINDOWS)
        "Windows"
#endif
        ")\n"
#ifdef V5C2_DEBUG
        "  debug release\n"
#endif // V5C2_DEBUG
        << std::endl;

        std::cout << "WARNING:\n\t"
        "This is a very early version.\n\t"
        "Highly unusable and unstable.\n"
        << std::endl;

        std::cout << "Press enter to play.  ";
        std::cin.get();

        play();

        std::cin.get();
    }
}


#if defined(V5C2_PLATFORM_LINUX) || defined(V5C2_PLATFORM_APPLE)

int main(int, char**)
{
    v5c2::main();
    return 0;
}

#elif defined(V5C2_PLATFORM_WINDOWS)

#define WIN32_LEAN_AND_MEAN

#include <sdkddkver.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    ::AllocConsole();

    FILE* dummy{};
    ::_tfreopen_s(&dummy, _T("CONIN$"), _T("r"), stdin);
    ::_tfreopen_s(&dummy, _T("CONOUT$"), _T("w"), stdout);
    ::_tfreopen_s(&dummy, _T("CONOUT$"), _T("w"), stderr);

    std::cin.clear();
    std::cout.clear();
    std::cerr.clear();
    std::clog.clear();
    
    v5c2::main();

    ::FreeConsole();
    
    return 0;
}

#endif
