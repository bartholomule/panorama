#include "panorama/graphics/ImageConvert.hpp"

namespace panorama
{
	namespace
	{
		template <typename T, typename U>
		inline T clamp(U t, T tmin, T tmax)
		{
			return std::max(std::min<T>(t, tmax), tmin);
		}
		template <typename T, typename U>
		T clamp(U t)
		{
			return clamp(t, T(0), std::numeric_limits<T>::max());
		}
	}

	//std::numeric_limits<T>::max()
	template<> unsigned char convertColorItem<unsigned char,float>(float f)
	{
		return clamp<unsigned char>(f * std::numeric_limits<unsigned char>::max());
	}

	template<> unsigned char convertColorItem<unsigned char,double>(double d)
	{
		return clamp<unsigned char>(d * std::numeric_limits<unsigned char>::max());
	}
	template<> unsigned char convertColorItem<unsigned char,unsigned short>(unsigned short s)
	{
		return s / 2;
	}

	template<> unsigned short convertColorItem<unsigned short,unsigned char>(unsigned char s)
	{
		return s * 2;
	}
	template<> unsigned short convertColorItem<unsigned short,float>(float f)
	{
		return clamp<unsigned short>(f * std::numeric_limits<unsigned short>::max());
	}
	template<> unsigned short convertColorItem<unsigned short,double>(double d)
	{
		return clamp<unsigned short>(d * std::numeric_limits<unsigned short>::max());
	}

	template<> float convertColorItem<float,unsigned char>(unsigned char f)
	{
		return float(f) / float(std::numeric_limits<unsigned char>::max());
	}
	template<> float convertColorItem<float,double>(double d)
	{
		return float(d);
	}
	template<> float convertColorItem<float,unsigned short>(unsigned short s)
	{
		return float(s) / float(std::numeric_limits<unsigned short>::max());
	}

	template<> double convertColorItem<double,unsigned char>(unsigned char d)
	{
		return double(d) / double(std::numeric_limits<unsigned char>::max());
	}
	template<> double convertColorItem<double,float>(float f)
	{
		return f;
	}
	template<> double convertColorItem<double,unsigned short>(unsigned short s)
	{
		return double(s) / double(std::numeric_limits<unsigned short>::max());
	}

}
