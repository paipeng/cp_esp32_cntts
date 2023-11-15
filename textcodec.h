#ifndef TEXTCODEC_H_
#define TEXTCODEC_H_

// #if defined(__GNUC__)
// #define CP_IOT_EXPORT
// #else
// #define CP_IOT_EXPORT __declspec(dllexport)
// #endif

#if defined(c_plusplus) || defined(__cplusplus)
extern "C" {
#endif

#include <stdint.h>

/**
 * 是否启用UTF8、GBK、UNICODE编码之间的转换
 *
 * 注意：unicode编码表非常大，如果用在单片机中，建议优化ff_convert函数，将编码表放到SD卡或者FLASH中
 */
#define TEXTCODEC_ENABLE 1

/**
 * 十六进制字符转十六进制数，例：'A' -> 0xA
 * @param  chr 要转换的十六进制字符
 * @return     转换后的值
 */
uint8_t chr2hex(uint8_t chr);

/**
 * 十六进制数转为字符串形式，例：0x0A->'A'
 * @param  hex 要转换的数，范围0~F
 * @return     转换后的值
 */
uint8_t hex2chr(uint8_t hex);

/**
 * 十六进制面值转字符串，例：{0XAA,0XBB,0XCC} -> "AABBCC"
 * @param from 待转换的十六进制数据
 * @param fromSize 待转换的十六进制数据大小
 * @param to 存放转换的字符串
 * @param toSize 存放转换的字符串的大小
 */
void HexToStr(const uint8_t* from, uint32_t fromSize, char* to, uint32_t* toSize);


/**
 * 十六进制字符串转数值，例："AABBCC" -> {0XAA,0XBB,0XCC}
 * @param from 待转换的十六进制字符串
 * @param fromSize 字符串长度
 * @param to 存放字符串的十六进制值
 * @param toSize 存放字符串的十六进制值的大小
 */
void StrToHex(const char* from, uint32_t fromSize, uint8_t* to, uint32_t* toSize);

#if (TEXTCODEC_ENABLE == 1)

/**
 * @brief GBK码转UTF8码
 * @param from GBK码
 * @param fromSize GBK码的大小
 * @param to UTF8码
 * @param toSize UTF8码的大小
 */
void GBKToUTF8(const uint8_t* from, uint32_t fromSize, uint8_t* to, uint32_t* toSize);


/**
 * @brief UTF8码转GBK码
 * @param from UTF8码
 * @param fromSize UTF8码的大小
 * @param to GBK码
 * @param toSize GBK码大小
 */
void UTF8ToGBK(const uint8_t* from, uint32_t fromSize, uint8_t* to, uint32_t* toSize);


/**
 * @brief GBK码转双字节UNICODE码
 * @param from GBK码
 * @param fromSize GBK码大小
 * @param to UNICODE码
 * @param toSize UNICODE码大小
 */
void GBKToUnicode(const uint8_t* from, uint32_t fromSize, uint8_t* to, uint32_t* toSize);


/**
 * @brief 双字节UNICODE码转GBK码
 * @param from 双字节UNICODE码
 * @param fromSize UNICODE码大小
 * @param to GBK码
 * @param toSize GBK码大小
 */
void UnicodeToGBK(const uint8_t* from, uint32_t fromSize, uint8_t* to, uint32_t* toSize);


/**
 * @brief 三字节UTF8码转双字节UNICODE码
 * @param from UTF8码
 * @param fromSize UTF8码大小
 * @param to GBK码
 * @param toSize GBK码大小
 */
void utf8ToUnicode(const uint8_t* from, uint32_t fromSize, uint8_t* to, uint32_t* toSize);

/**
 * @brief 双字节UNICODE码转三字节UTF8码
 * @param from
 * @param fromSize
 * @param to
 * @param toSize
 */
void UnicodeToUTF8(const uint8_t* from, uint32_t fromSize, uint8_t* to, uint32_t* toSize);

#endif

#if defined(c_plusplus) || defined(__cplusplus)
}
#endif

#endif /* TEXTCODEC_H_ */
