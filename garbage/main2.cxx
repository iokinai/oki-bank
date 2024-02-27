#include <cstdint>
#include <iostream>
#include <string>

// SHA-256 Constants
constexpr uint32_t sha256_constants[] = {
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

// Right rotate operation
constexpr uint32_t rightRotate(uint32_t value, uint32_t count) {
  return (value >> count) | (value << (32 - count));
}

// SHA-256 processing function
std::string sha256(const std::string &input) {
  // Initialize hash values
  uint32_t h0 = 0x6a09e667;
  uint32_t h1 = 0xbb67ae85;
  uint32_t h2 = 0x3c6ef372;
  uint32_t h3 = 0xa54ff53a;
  uint32_t h4 = 0x510e527f;
  uint32_t h5 = 0x9b05688c;
  uint32_t h6 = 0x1f83d9ab;
  uint32_t h7 = 0x5be0cd19;

  // Pre-processing: padding with a single 1 bit and appending length
  std::string msg = input;
  msg += static_cast<char>(0x80); // Append 1 bit
  while ((msg.size() % 64) !=
         56) { // Pad with zeros until message length ≡ 448 (mod 512)
    msg += static_cast<char>(0x00);
  }
  uint64_t lengthBits = input.size() * 8;
  for (int i = 7; i >= 0; --i) {
    msg += static_cast<char>((lengthBits >> (i * 8)) & 0xFF);
  }

  // Process the message in successive 512-bit chunks
  for (size_t chunk = 0; chunk < msg.size(); chunk += 64) {
    // Break chunk into sixteen 32-bit words
    uint32_t w[64] = {0};
    for (size_t i = 0; i < 16; ++i) {
      w[i] = (msg[chunk + i * 4] << 24) | (msg[chunk + i * 4 + 1] << 16) |
             (msg[chunk + i * 4 + 2] << 8) | (msg[chunk + i * 4 + 3]);
    }

    // Extend the sixteen 32-bit words into sixty-four 32-bit words
    for (size_t i = 16; i < 64; ++i) {
      uint32_t s0 = rightRotate(w[i - 15], 7) ^ rightRotate(w[i - 15], 18) ^
                    (w[i - 15] >> 3);
      uint32_t s1 = rightRotate(w[i - 2], 17) ^ rightRotate(w[i - 2], 19) ^
                    (w[i - 2] >> 10);
      w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    // Initialize hash value for this chunk
    uint32_t a = h0;
    uint32_t b = h1;
    uint32_t c = h2;
    uint32_t d = h3;
    uint32_t e = h4;
    uint32_t f = h5;
    uint32_t g = h6;
    uint32_t h = h7;

    // Main loop
    for (size_t i = 0; i < 64; ++i) {
      uint32_t S1 = rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25);
      uint32_t ch = (e & f) ^ (~e & g);
      uint32_t temp1 = h + S1 + ch + sha256_constants[i] + w[i];
      uint32_t S0 = rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22);
      uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
      uint32_t temp2 = S0 + maj;

      h = g;
      g = f;
      f = e;
      e = d + temp1;
      d = c;
      c = b;
      b = a;
      a = temp1 + temp2;
    }

    // Add this chunk's hash to the result so far
    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
    h4 += e;
    h5 += f;
    h6 += g;
    h7 += h;
  }

  // Produce the final hash result
  std::string hash;
  for (uint32_t h : {h0, h1, h2, h3, h4, h5, h6, h7}) {
    for (int i = 3; i >= 0; --i) {
      hash += static_cast<char>((h >> (i * 8)) & 0xFF);
    }
  }

  return hash;
}

int main() {

  std::string hash = sha256("Hello world");
  std::cout << "SHA-256 hash: ";
  for (char c : hash) {
    printf("%02x", static_cast<uint8_t>(c));
  }
  std::cout << std::endl;

  return 0;
}

// 35a5b4600d55d622b2b0b5c8d125f1c9ce31649cc4fcde5728736c8b16cf5d51
