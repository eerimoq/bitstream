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
    int byte_offset;
    int bit_offset;
};

void bitstream_writer_init(struct bitstream_writer_t *self_p,
                           uint8_t *buf_p);

int bitstream_writer_size_in_bits(struct bitstream_writer_t *self_p);

int bitstream_writer_size_in_bytes(struct bitstream_writer_t *self_p);

/*
 * Write bits to the stream. Clears each byte before bits are written.
 */

void bitstream_writer_write_bit(struct bitstream_writer_t *self_p,
                                int value);

void bitstream_writer_write_bytes(struct bitstream_writer_t *self_p,
                                  const uint8_t *buf_p,
                                  int length);

void bitstream_writer_write_u8(struct bitstream_writer_t *self_p,
                               uint8_t value);

void bitstream_writer_write_u16(struct bitstream_writer_t *self_p,
                                uint16_t value);

void bitstream_writer_write_u32(struct bitstream_writer_t *self_p,
                                uint32_t value);

void bitstream_writer_write_u64(struct bitstream_writer_t *self_p,
                                uint64_t value);

void bitstream_writer_write_u64_bits(struct bitstream_writer_t *self_p,
                                     uint64_t value,
                                     int number_of_bits);

/*
 * Insert bits into the stream. Leaves all other bits unmodified.
 */

void bitstream_writer_insert_bit(struct bitstream_writer_t *self_p,
                                 int value);

void bitstream_writer_insert_bytes(struct bitstream_writer_t *self_p,
                                   const uint8_t *buf_p,
                                   int length);

void bitstream_writer_insert_u8(struct bitstream_writer_t *self_p,
                                uint8_t value);

void bitstream_writer_insert_u16(struct bitstream_writer_t *self_p,
                                 uint16_t value);

void bitstream_writer_insert_u32(struct bitstream_writer_t *self_p,
                                 uint32_t value);

void bitstream_writer_insert_u64(struct bitstream_writer_t *self_p,
                                 uint64_t value);

void bitstream_writer_insert_u64_bits(struct bitstream_writer_t *self_p,
                                      uint64_t value,
                                      int number_of_bits);

void bitstream_reader_init(struct bitstream_reader_t *self_p,
                           const uint8_t *buf_p);

/*
 * Read bits from the stream.
 */

int bitstream_reader_read_bit(struct bitstream_reader_t *self_p);

void bitstream_reader_read_bytes(struct bitstream_reader_t *self_p,
                                 uint8_t *buf_p,
                                 int length);

uint8_t bitstream_reader_read_u8(struct bitstream_reader_t *self_p);

uint16_t bitstream_reader_read_u16(struct bitstream_reader_t *self_p);

uint32_t bitstream_reader_read_u32(struct bitstream_reader_t *self_p);

uint64_t bitstream_reader_read_u64(struct bitstream_reader_t *self_p);

uint8_t bitstream_reader_read_u8_bits(struct bitstream_reader_t *self_p,
                                      int number_of_bits);

uint16_t bitstream_reader_read_u16_bits(struct bitstream_reader_t *self_p,
                                        int number_of_bits);

uint32_t bitstream_reader_read_u32_bits(struct bitstream_reader_t *self_p,
                                        int number_of_bits);

uint64_t bitstream_reader_read_u64_bits(struct bitstream_reader_t *self_p,
                                        int number_of_bits);

#endif
