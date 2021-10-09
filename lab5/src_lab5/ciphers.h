#ifndef CIPHERS_H
#define CIPHERS_H

#include <string>

using fCipher = void (*)(std::string&);

void FeistelCipher(std::string& s);
void FeistelReCipher(std::string& s);

void TrithemiusCipher(std::string& s);
void TrithemiusReCipher(std::string& s);

void BitShiftCipher(std::string& s);
void BitShiftReCipher(std::string& s);
#endif // CIPHERS_H