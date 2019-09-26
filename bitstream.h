/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Erik Moqvist
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
