//==========================================================
//
//  V5C2  --  src/board.h
//
//==========================================================


#ifndef V5C2_BOARD_H
#define V5C2_BOARD_H 1

#include <utility>

namespace v5c2
{
    template <typename T, std::size_t W, std::size_t H>
	class Board
	{
	public:

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using index_type = std::pair<size_type, size_type>;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;

		static constexpr std::size_t width{ W };
		static constexpr std::size_t height{ W };

		constexpr reference at(const index_type& pos);

		constexpr const_reference at(const index_type& pos) const;

		constexpr reference operator[](const index_type& pos);
		
		constexpr const_reference operator[](const index_type& pos) const;

	private:

		void bound_check(const index_type& pos) const;

		value_type m_data[W * H]{};
	};
}

#include "board.inl"

#endif // !V5C2_BOARD_H
