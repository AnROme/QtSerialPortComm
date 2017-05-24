#ifndef _BYTEARRAY_EXTEND_H
#define _BYTEARRAY_EXTEND_H

#include <stdexcept>
#include <type_traits>
#include <qglobal.h>
#include <QByteArray>
using namespace std;


/* Class toArrayChars for create chars array from POD-type*/
template<class T> class toArrayChars{

private:
	T& refNative;	
	unsigned char *arrChars;


public:
	toArrayChars(T &data): refNative(data), arrChars(reinterpret_cast<unsigned char*>(&refNative))
	{
        static_assert(std::is_pod<T>::value, "this class can be used only on POD types");
	}

    unsigned char & operator[](unsigned int i)
	{
		return at(i);
	}

    unsigned char & at(unsigned int i)
	{
        #ifdef _DEBUG
        if(!(i < sizeof(T)))
            throw std::out_of_range("out of range - debug mode");
        #endif

        #if(Q_BYTE_ORDER == Q_LITTLE_ENDIAN)
			return arrChars[i];
        #else
			return arrChars[size() - i - 1];
        #endif
	}
	
	size_t size(){
		return sizeof(T);
	}

};


/*Extended QByteArray class
 * can add and read T-type data to/from byte array */

class ByteArrayExtend: public QByteArray{

public:
	ByteArrayExtend(){}

	template <class T> ByteArrayExtend& append_extend(T data);
    template<class T> void Read(size_t pos, T& toContainer);
	
};

template <class T> ByteArrayExtend& ByteArrayExtend::append_extend(T data){

	toArrayChars<T> arr(data);
	for(int i = 0; i < sizeof(T); ++i)
        append(arr[i]);
	return *this;
}

template <> ByteArrayExtend& ByteArrayExtend::append_extend<qint8>(qint8 data){
	append((qint8) data);
	return *this;
}

template<> ByteArrayExtend& ByteArrayExtend::append_extend<quint8>(quint8 data)
{
	append((quint8)data);
	return *this;
}

template<> ByteArrayExtend& ByteArrayExtend::append_extend<QByteArray>(QByteArray data)
{
	for(int i = 0; i < data.count(); ++i)
		append(data[i]);

	return *this;
}

/*Read sizeof(T) bytes since pos */
template<class T> void ByteArrayExtend::Read(size_t pos, T& toContainer){

    Q_ASSERT(pos + sizeof(T) <= count());
    toArrayChars<T> arrayChars(toContainer);

    for(int i = 0; i < sizeof(T); ++i)
		arrayChars[i] = at(pos + i);
}

#endif
