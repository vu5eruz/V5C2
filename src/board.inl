//==========================================================
//
//  V5C2  --  src/board.inl
//
//==========================================================


#include <stdexcept>

namespace v5c2
{
	template <typename T, std::size_t W, std::size_t H>
	constexpr typename Board<T, W, H>::reference Board<T, W, H>::at(const index_type& pos)
	{
		bound_check(pos);

		return m_data[pos.first + pos.second * width];
	}


	template <typename T, std::size_t W, std::size_t H>
	constexpr typename Board<T, W, H>::const_reference Board<T, W, H>::at(const index_type& pos) const
	{
		bound_check(pos);

		return m_data[pos.first + pos.second * width];
	}


	template <typename T, std::size_t W, std::size_t H>
	constexpr typename Board<T, W, H>::reference Board<T, W, H>::operator[](const index_type& pos)
	{
		return m_data[pos.first + pos.second * width];
	}


	template <typename T, std::size_t W, std::size_t H>
	constexpr typename Board<T, W, H>::const_reference Board<T, W, H>::operator[](const index_type& pos) const
	{
		return m_data[pos.first + pos.second * width];
	}


	template <typename T, std::size_t W, std::size_t H>
	void Board<T, W, H>::bound_check(const index_type& pos) const
	{
		if ((pos.first >= width) || (pos.second >= height))
		{
			throw std::out_of_range("Board position out of range");
		}
	}
}
