#include "Base64.h"
#include <iostream>

static const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

static inline bool IsBase64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string Base64::Encode(unsigned char const* toEncode, unsigned int len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (len--) {
    char_array_3[i++] = *(toEncode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;
}



/*
#define ToB64Index1( byte1 )			( byte1 >> 2 ) // 6 msb byte1 -> 6 lsb out
#define ToB64Index2( byte1, byte2 )	( ( ( byte1 & 0x3 ) << 4 ) | ( ( byte2 & 0xF0 ) >> 4 ) ) // 2 lsb byte1 -> 2msb out. 4 msb byte2 -> 4 lsb out
#define ToB64Index3( byte2, byte3 )	( ( ( byte2 & 0xF ) << 2 ) | ( ( byte3 & 0xC0 ) >> 6 ) ) // 4 lsb byte2 -> 4 msb out. 2 msb byte3 -> 2 lsb out
#define ToB64Index4( byte3 )			( byte3 & 0x3F ) // 6 lowest bits of byte3

const char toBase64Map[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', 
};

unsigned int GetBase64Size(unsigned int size)
{
	return ((size + 2) / 3) * 4;
}

const char* Base64::Encode(const char* data)
{
	char* encoded;
	unsigned int size = GetBase64Size(sizeof(data));
	char* encodedPtr = new char[size + 1];
	encoded = encodedPtr;
	while(size > 2)
	{
		*encodedPtr++ = toBase64Map[ToB64Index1(*data)];
		*encodedPtr++ = toBase64Map[ToB64Index2(*data, *(data+1))];
		*encodedPtr++ = toBase64Map[ToB64Index3(*(data+1), *(data + 2))];
		*encodedPtr++ = toBase64Map[ToB64Index4(*(data+2))];
		data += 3;
		size -= 3;
	}

	if(size > 0)
	{
		*encodedPtr++ = toBase64Map[ToB64Index1(*data)];
		if(size > 1)
		{
			*encodedPtr++ = toBase64Map[ToB64Index2(*data, *(data+1))];
			*encodedPtr++ = toBase64Map[ToB64Index3(*(data+1), 0)];
		} else {
			*encodedPtr++ = toBase64Map[ToB64Index2(*data, 0)];
			*encodedPtr++ = '=';
		}
		*encodedPtr++ = '=';
	}
	*encodedPtr++ = '\0';

	return encoded;
}*/