#include "ciphers.h"

using namespace std;

void FeistelCipher(string& s)
{
    const int max_step = 4;
    int l, r, temp;

    for (int i = 1; i < s.length(); i += 2)
    {
        l = s[i - 1];
        r = s[i];

        for (int st = 0; st < max_step; st++)
        {
            temp = l;
            l = r ^ ((l + st * 15) % 256);
            r = temp;
        }
        s[i - 1] = l;
        s[i] = r;
    }
}
void FeistelReCipher(string& s)
{
    const int max_step = 4;
    int l, r, temp;

    for (int i = 1; i < s.length(); i += 2)
    {
        l = s[i - 1];
        r = s[i];

        for (int st = max_step - 1; st >= 0; st--)
        {
            temp = r;
            r = l ^ ((r + st * 15) % 256);
            l = temp;
        }
        s[i - 1] = l;
        s[i] = r;
    }
}

void TrithemiusCipher(string& s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = (s[i] + (int(sqrt(i)) - 3 * i + 3)) % 256;
    }
}
void TrithemiusReCipher(string& s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = (s[i] - (int(sqrt(i)) - 3 * i + 3)) % 256;
    }
}

using buf_t = long unsigned int;
void BitShiftCipher(string& s)
{
    buf_t buf;
    int buf_byte = sizeof(buf_t);
    int buf_bit = buf_byte * 8;
    int shift = 3;

    for (int i = 0; i < s.size() - buf_byte + 1; i++)
    {
        memcpy(&buf, &s[i], buf_byte);
        buf = (buf >> shift) | (buf << (buf_bit - shift));
        memcpy(&s[i], &buf, buf_byte);
    }
}
void BitShiftReCipher(string& s)
{
    buf_t buf;
    int buf_byte = sizeof(buf_t);
    int buf_bit = buf_byte * 8;
    int shift = 3;

    for (int i = s.size() - buf_byte; i >= 0; i--)
    {
        memcpy(&buf, &s[i], buf_byte);
        buf = (buf << shift) | (buf >> (buf_bit - shift));
        memcpy(&s[i], &buf, buf_byte);
    }
}
