//==========================================================
//
//  V5C2  --  src/client/texture.h
//
//==========================================================


#ifndef V5C2_CLIENT_TEXTURE_H
#define V5C2_CLIENT_TEXTURE_H 1

#include <cstddef>
#include <memory>
#include <string_view>


namespace v5c2::client
{
	enum class PixelFormat
	{
		Red,
		Green,
		Blue,
		Alpha,
		Rgb,
		Bgr,
		RgbAlpha,
		BgrAlpha,
		Luminance,
		LuminanceAlpha
	};


	enum class PixelType
	{
		Uint8,
		Sint8,
		Uint16,
		Sint16,
		Uint32,
		Sint32,
		Float32
	};


	class Texture
	{
	public:

		enum ParameterType
		{
			MinFilter,
			MagFilter
		};

		enum ParameterValue
		{
			Nearest,
			Linear
		};

		Texture();

		~Texture();

		static void Bind(const Texture* PtrTxt);

		void Image(const std::string_view& Path);

		void Image(std::size_t Width, std::size_t Height, PixelFormat Format, PixelType Type, const void* Data);

		void SubImage(std::size_t X, std::size_t Y, std::size_t Width, std::size_t Height, PixelFormat Format, PixelType Type, const void* Data);

		void Parameter(ParameterType Ptype, ParameterValue Pvalue);

	private:

		unsigned int m_TexId{};
		unsigned int m_Width{};
		unsigned int m_Height{};
	};

	using TexturePtr = std::shared_ptr<Texture>;
}

#endif // !V5C2_CLIENT_TEXTURE_H
