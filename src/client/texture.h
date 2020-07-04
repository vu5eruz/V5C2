//==========================================================
//
//  V5C2  --  src/client/texture.h
//
//==========================================================


#ifndef V5C2_CLIENT_TEXTURE_H
#define V5C2_CLIENT_TEXTURE_H 1

#include <memory>
#include <string_view>


namespace v5c2::client
{
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

		void Parameter(ParameterType Ptype, ParameterValue Pvalue);

	private:

		unsigned int m_TexId{};
		unsigned int m_Width{};
		unsigned int m_Height{};
	};

	using TexturePtr = std::shared_ptr<Texture>;
}

#endif // !V5C2_CLIENT_TEXTURE_H
