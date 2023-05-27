#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

// Tabel pencarian Base64
const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Fungsi untuk mengenkripsi array byte menjadi string base64
std::string base64_encode(const std::vector<unsigned char> &bytes)
{
    std::string encoded;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    for (unsigned char byte : bytes)
    {
        char_array_3[i++] = byte;
        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; i++)
                encoded += base64_chars[char_array_4[i]];

            i = 0;
        }
    }

    if (i > 0)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (j = 0; j < i + 1; j++)
            encoded += base64_chars[char_array_4[j]];

        while (i++ < 3)
            encoded += '=';
    }

    return encoded;
}

// Fungsi untuk mendekode string base64 menjadi array byte
std::vector<unsigned char> base64_decode(const std::string &encoded)
{
    int in_len = encoded.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::vector<unsigned char> decoded;

    while (in_len-- && encoded[in_] != '=')
    {
        char_array_4[i++] = encoded[in_];
        in_++;
        if (i == 4)
        {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; i < 3; i++)
                decoded.push_back(char_array_3[i]);

            i = 0;
        }
    }

    if (i > 0)
    {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

        for (j = 0; j < i - 1; j++)
            decoded.push_back(char_array_3[j]);
    }

    return decoded;
}

// Inisialisasi variabel
long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
char msg[100];

// Fungsi untuk mengecek apakah sebuah angka adalah bilangan prima
bool isPrime(long int num)
{
    for (long int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

// Fungsi untuk mencari nilai d
long int cd(long int x)
{
    long int k = 1;
    while (true)
    {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}

// Fungsi untuk mencari bilangan co-prime
void findCoPrimes()
{
    int k = 0;
    for (long int i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;
        if (isPrime(i) && i != p && i != q)
        {
            e[k] = i;
            long int result = cd(e[k]);
            if (result > 0)
            {
                d[k] = result;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}

// Fungsi enkripsi
void encrypt()
{
    std::cout << "====================================\n";
    std::cout << "Program Enkripsi dan Dekripsi RSA\n";
    std::cout << "====================================\n\n";

    std::cout << "Masukkan Bilangan Prima Pertama (p): ";
    std::cin >> p;
    if (!isPrime(p))
    {
        std::cout << "\nBilangan yang dimasukkan bukan merupakan bilangan prima.\n";
        exit(1);
    }

    std::cout << "\nMasukkan Bilangan Prima Kedua (q): ";
    std::cin >> q;
    if (!isPrime(q) || p == q)
    {
        std::cout << "\nBilangan yang dimasukkan bukan merupakan bilangan prima.\n";
        exit(1);
    }

    std::cin.ignore();
    std::cout << "\nMasukkan Pesan yang ingin dienkripsi: ";
    std::cin.getline(msg, 100);

    for (i = 0; msg[i] != '\0'; i++)
        m[i] = msg[i];

    n = p * q;
    t = (p - 1) * (q - 1);
    findCoPrimes();

    std::cout << "\nAngka yang berkemungkinan menjadi nilai e dan d adalah:\n";
    for (i = 0; i < j - 1; i++)
        std::cout << e[i] << "\t" << d[i] << "\n";

    long int pt, ct, key = e[0], k, len;
    i = 0;
    len = strlen(msg);

    std::vector<unsigned char> encoded;

    while (i != len)
    {
        pt = m[i];
        pt = pt - 96;
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        encoded.push_back(static_cast<unsigned char>(ct));
        i++;
    }
    en[i] = -1;

    std::cout << "\nPesan yang telah dienkripsi adalah:\n";
    std::cout << base64_encode(encoded) << "\n";
}

// Fungsi dekripsi
void decrypt()
{
    long int pt, ct, key = d[0], k;
    i = 0;
    std::vector<unsigned char> decoded;

    while (en[i] != -1)
    {
        ct = temp[i];
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        m[i] = pt;
        decoded.push_back(static_cast<unsigned char>(pt));
        i++;
    }
    m[i] = -1;

    std::cout << "\nPesan yang telah didekripsi kembali adalah:\n";
    std::cout << reinterpret_cast<char *>(decoded.data()) << "\n";
}

// Fungsi utama
int main()
{
    encrypt();
    decrypt();

    return 0;
}
