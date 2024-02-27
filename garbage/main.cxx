#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// Rotate right (circular right shift) operation
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

// Right shift operation
#define SHR(x, n) ((x) >> (n))

// Sigma0 and Sigma1 functions for SHA-256
#define SIGMA0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define SIGMA1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

// Initial hash values (first 32 bits of the fractional parts of the square
// roots of the first 8 primes 2..19):
const uint32_t sha256_initial_hash_values[] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

// Constants (first 32 bits of the fractional parts of the cube roots of the
// first 64 primes 2..311):
const uint32_t sha256_constants[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

// SHA-256 transform function
void sha256_transform(uint32_t *hash_values, const uint32_t *constants,
                      const uint8_t *block) {
  uint32_t W[64];
  uint32_t a, b, c, d, e, f, g, h;
  uint32_t T1, T2;

  // Prepare the message schedule
  for (int t = 0; t < 16; ++t) {
    W[t] = (block[t * 4] << 24) | (block[t * 4 + 1] << 16) |
           (block[t * 4 + 2] << 8) | (block[t * 4 + 3]);
  }
  for (int t = 16; t < 64; ++t) {
    W[t] = SIGMA1(W[t - 2]) + W[t - 7] + SIGMA0(W[t - 15]) + W[t - 16];
  }

  // Initialize working variables
  a = hash_values[0];
  b = hash_values[1];
  c = hash_values[2];
  d = hash_values[3];
  e = hash_values[4];
  f = hash_values[5];
  g = hash_values[6];
  h = hash_values[7];

  // Main loop
  for (int t = 0; t < 64; ++t) {
    T1 = h + SIGMA1(e) + CH(e, f, g) + constants[t] + W[t];
    T2 = SIGMA0(a) + MAJ(a, b, c);
    h = g;
    g = f;
    f = e;
    e = d + T1;
    d = c;
    c = b;
    b = a;
    a = T1 + T2;
  }

  // Update hash values
  hash_values[0] += a;
  hash_values[1] += b;
  hash_values[2] += c;
  hash_values[3] += d;
  hash_values[4] += e;
  hash_values[5] += f;
  hash_values[6] += g;
  hash_values[7] += h;
}

// SHA-256 hashing function
std::string sha256(std::string message) {
  uint32_t hash_values[8];
  std::stringstream ss;
  std::string digest;

  // Initialize hash values
  for (int i = 0; i < 8; ++i) {
    hash_values[i] = sha256_initial_hash_values[i];
  }

  // Pre-processing
  uint64_t original_length = message.length() * 8;
  message += (char)0x80; // Append a single '1' bit
  while ((message.length() + 8) % 64 != 0) {
    message +=
        (char)0x00; // Append bits '0' until message length ≡ 448 (mod 512)
  }
  message +=
      (char)(original_length >> 56); // Append the original length in bits as a
                                     // 64-bit big-endian integer
  message += (char)(original_length >> 48);
  message += (char)(original_length >> 40);
  message += (char)(original_length >> 32);
  message += (char)(original_length >> 24);
  message += (char)(original_length >> 16);
  message += (char)(original_length >> 8);
  message += (char)original_length;

  // Process the message in successive 512-bit chunks
  for (size_t i = 0; i < message.length(); i += 64) {
    const uint8_t *chunk =
        reinterpret_cast<const uint8_t *>(message.c_str() + i);
    sha256_transform(hash_values, sha256_constants, chunk);
  }

  // Generate the hash
  for (int i = 0; i < 8; ++i) {
    ss << std::hex << std::setw(8) << std::setfill('0') << hash_values[i];
  }
  digest = ss.str();

  return digest;
}

int main() {
  std::string message = "Hello world";
  std::string hashed_message = sha256(message);
  std::cout << "SHA-256 hash of \"" << message << "\": " << hashed_message
            << std::endl;
  return 0;
}

// 1d21cd50d39e4e5b729213bfa13283ff21c016ddf5165ab5943a3ef1104ca6c2