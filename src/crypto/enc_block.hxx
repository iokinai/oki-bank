#ifndef CRYPTO_ENC_BLOCK_HXX
#define CRYPTO_ENC_BLOCK_HXX

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <vector>
namespace okibank {

using byte = uint8_t;

class enc_block final {
private:
  byte *data;

  template <std::input_or_output_iterator Iter>
  enc_block(Iter begin, Iter end) : data(new byte[SIZE]), __last_pos(SIZE) {
    if ((end - begin) + 1 != SIZE) {
      delete[] data;
      throw std::out_of_range("Elements count should be equal to 64");
    }

    size_t curr{0};

    for (; begin != end; ++begin) {
      data[curr] = *begin;
      ++curr;
    }
  }

  byte __last_pos = 0;

public:
  enc_block();

  enc_block(std::initializer_list<byte> &&bytes);

  enc_block(std::vector<byte> &bytes);

  enc_block(const enc_block &other);

  enc_block(enc_block &&other);

  enc_block &operator=(const enc_block &other);

  enc_block &operator=(enc_block &&other);

  byte &operator[](size_t position);

  byte get_last_pos() const noexcept;

  byte *get_data() const noexcept;

  ~enc_block();

  template <std::input_or_output_iterator Iter>
  void set_values(Iter &start, const Iter &end) noexcept {
    for (size_t i = 0; i < SIZE; i++) {
      data[i] = *start;

      if (start == end) {
        break;
      }
      ++__last_pos;
      ++start;
    }
  }

  static constexpr byte SIZE = 64;
};

} // namespace okibank

#endif