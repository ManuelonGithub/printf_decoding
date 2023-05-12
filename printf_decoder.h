/**
 * @file 	printf_decoder.h
 * @author 	ManuelonGithub (manuelonemail@gmail.com)
 * @brief 	Example for a decoder function that will take in a printf-encoded buffer 
 * 		 	and produce the desired formatted c-string
 * 
 * @copyright Copyright (c) 2023 ManuelonGithub
 * 
 * MIT License
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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