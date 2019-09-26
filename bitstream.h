#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <stdint.h>

struct bitstream_writer_t {
    uint8_t *buf_p;
    int byte_offset;
    int bit_offset;
};

struct bitstream_reader_t {
    const uint8_t *buf_p;
    int pos_in_bits;
};

void bitstream_writer_init(struct bitstream_writer_t *self_p,
                           uint8_t *buf_p);

void bitstream_writer_append_bit(struct bitstream_writer_t *self_p,
                                 int value);

void bitstream_writer_append_u8(struct bitstream_writer_t *self_p,
                                uint8_t value);

void bitstream_writer_append_u16(struct bitstream_writer_t *self_p,
                                 uint16_t value);

void bitstream_writer_append_u32(struct bitstream_writer_t *self_p,
                                 uint32_t value);

void bitstream_writer_append_u64(struct bitstream_writer_t *self_p,
                                 uint64_t value);

void bitstream_writer_append_u8_bits(struct bitstream_writer_t *self_p,
                                     uint8_t value,
                                     int number_of_bits);

void bitstream_writer_append_u16_bits(struct bitstream_writer_t *self_p,
                                      uint16_t value,
                                      int number_of_bits);

void bitstream_writer_append_u32_bits(struct bitstream_writer_t *self_p,
                                      uint32_t value,
                                      int number_of_bits);

void bitstream_writer_append_u64_bits(struct bitstream_writer_t *self_p,
                                      uint64_t value,
                                      int number_of_bits);

int bitstream_writer_size_in_bytes(struct bitstream_writer_t *self_p);

void bitstream_reader_init(struct bitstream_reader_t *self_p,
                           const uint8_t *buf_p);

#endif
