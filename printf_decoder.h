#ifndef PRINTF_DECODER_H_
#define PRINTF_DECODER_H_

/**
 * @brief processes an encoded printf data and produces a c-string with the intended format
 * 
 * @param dst output buffer to write forrmatted string into. Will be a c-string
 * @param data input buffer containing the encoded printf data
 * @param len length of data
 * @return int length of the produced formatted string in dst
 */
int printf_df_decode(char* dst, const char* data, int len);

#endif // !PRINTF_DECODER_H_