#include "crypto_base.hxx"

namespace okibank {

template <std::integral T> T swap_endian(T u) {
  union {
    T u;
    unsigned char u8[sizeof(T)];
  } source, dest;

  source.u = u;

  for (std::size_t k = 0; k < sizeof(T); k++)
    dest.u8[k] = source.u8[sizeof(T) - k - 1];

  return dest.u;
}

template uint8_t swap_endian(uint8_t val);

template uint16_t swap_endian(uint16_t val);

template uint32_t swap_endian(uint32_t val);

template uint64_t swap_endian(uint64_t val);

} // namespace okibank