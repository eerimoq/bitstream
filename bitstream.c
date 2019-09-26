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

#include "bitstream.h"

void bitstream_writer_init(struct bitstream_writer_t *self_p,
                           uint8_t *buf_p)
{
    self_p->buf_p = buf_p;
    self_p->byte_offset = 0;
    self_p->bit_offset = 0;
}

void bitstream_writer_write_bit(struct bitstream_writer_t *self_p,
                                int value)
{
    if (self_p->bit_offset == 0) {
        self_p->buf_p[self_p->byte_offset] = (value << 7);
        self_p->bit_offset = 1;
    } else {
        self_p->buf_p[self_p->byte_offset] |= (value << (8 - self_p->bit_offset - 1));

        if (self_p->bit_offset == 7) {
            self_p->bit_offset = 0;
            self_p->byte_offset++;
        } else {
            self_p->bit_offset++;
        }
    }
}

void bitstream_writer_write_bytes(struct bitstream_writer_t *self_p,
                                  const uint8_t *buf_p,
                                  int length)
{
    int i;

    for (i = 0; i < length; i++) {
        bitstream_writer_write_u8(self_p, buf_p[i]);
    }
}

void bitstream_writer_write_u8(struct bitstream_writer_t *self_p,
                               uint8_t value)
{
    if (self_p->bit_offset == 0) {
        self_p->buf_p[self_p->byte_offset] = value;
    } else {
        self_p->buf_p[self_p->byte_offset] |= (value >> self_p->bit_offset);
        self_p->buf_p[self_p->byte_offset + 1] = (value << (8 - self_p->bit_offset));
    }

    self_p->byte_offset++;
}

void bitstream_writer_write_u16(struct bitstream_writer_t *self_p,
                                uint16_t value)
{
    bitstream_writer_write_u8(self_p, value >> 8);
    bitstream_writer_write_u8(self_p, value >> 0);
}

void bitstream_writer_write_u32(struct bitstream_writer_t *self_p,
                                uint32_t value)
{
    bitstream_writer_write_u8(self_p, value >> 24);
    bitstream_writer_write_u8(self_p, value >> 16);
    bitstream_writer_write_u8(self_p, value >> 8);
    bitstream_writer_write_u8(self_p, value >> 0);
}

void bitstream_writer_write_u64(struct bitstream_writer_t *self_p,
                                uint64_t value)
{
    bitstream_writer_write_u8(self_p, value >> 56);
    bitstream_writer_write_u8(self_p, value >> 48);
    bitstream_writer_write_u8(self_p, value >> 40);
    bitstream_writer_write_u8(self_p, value >> 32);
    bitstream_writer_write_u8(self_p, value >> 24);
    bitstream_writer_write_u8(self_p, value >> 16);
    bitstream_writer_write_u8(self_p, value >> 8);
    bitstream_writer_write_u8(self_p, value >> 0);
}

void bitstream_writer_write_u8_bits(struct bitstream_writer_t *self_p,
                                    uint8_t value,
                                    int number_of_bits)
{
    int i;

    for (i = 0; i < number_of_bits; i++) {
        bitstream_writer_write_bit(self_p, (value >> (number_of_bits - i - 1)) & 0x1);
    }
}

void bitstream_writer_write_u16_bits(struct bitstream_writer_t *self_p,
                                     uint16_t value,
                                     int number_of_bits)
{
    int i;

    for (i = 0; i < number_of_bits; i++) {
        bitstream_writer_write_bit(self_p, (value >> (number_of_bits - i - 1)) & 0x1);
    }
}

void bitstream_writer_write_u32_bits(struct bitstream_writer_t *self_p,
                                     uint32_t value,
                                     int number_of_bits)
{
    int i;

    for (i = 0; i < number_of_bits; i++) {
        bitstream_writer_write_bit(self_p, (value >> (number_of_bits - i - 1)) & 0x1);
    }
}

void bitstream_writer_write_u64_bits(struct bitstream_writer_t *self_p,
                                     uint64_t value,
                                     int number_of_bits)
{
    int i;

    for (i = 0; i < number_of_bits; i++) {
        bitstream_writer_write_bit(self_p, (value >> (number_of_bits - i - 1)) & 0x1);
    }
}

int bitstream_writer_size_in_bytes(struct bitstream_writer_t *self_p)
{
    return (self_p->byte_offset + (self_p->bit_offset + 7) / 8);
}

void bitstream_reader_init(struct bitstream_reader_t *self_p,
                           const uint8_t *buf_p)
{
    self_p->buf_p = buf_p;
    self_p->byte_offset = 0;
    self_p->bit_offset = 0;
}

int bitstream_reader_read_bit(struct bitstream_reader_t *self_p)
{
    int value;

    if (self_p->bit_offset == 0) {
        value = (self_p->buf_p[self_p->byte_offset] >> 7);
        self_p->bit_offset = 1;
    } else {
        value = ((self_p->buf_p[self_p->byte_offset] >> (7 - self_p->bit_offset)) & 0x1);

        if (self_p->bit_offset == 7) {
            self_p->bit_offset = 0;
            self_p->byte_offset++;
        } else {
            self_p->bit_offset++;
        }
    }

    return (value);
}

void bitstream_reader_read_bytes(struct bitstream_reader_t *self_p,
                                 uint8_t *buf_p,
                                 int length)
{
    int i;

    for (i = 0; i < length; i++) {
        buf_p[i] = bitstream_reader_read_u8(self_p);
    }
}

uint8_t bitstream_reader_read_u8(struct bitstream_reader_t *self_p)
{
    uint8_t value;

    value = (self_p->buf_p[self_p->byte_offset] << self_p->bit_offset);
    self_p->byte_offset++;

    if (self_p->bit_offset != 0) {
        value |= (self_p->buf_p[self_p->byte_offset] >> (8 - self_p->bit_offset));
    }

    return (value);
}

uint16_t bitstream_reader_read_u16(struct bitstream_reader_t *self_p)
{
    uint16_t value;
    int i;
    int offset;

    offset = (16 + self_p->bit_offset);
    value = 0;

    for (i = 0; i < 2; i++) {
        offset -= 8;
        value |= ((uint64_t)self_p->buf_p[self_p->byte_offset] << offset);
        self_p->byte_offset++;
    }

    if (offset != 0) {
        value |= (self_p->buf_p[self_p->byte_offset] >> (8 - offset));
    }

    return (value);
}

uint32_t bitstream_reader_read_u32(struct bitstream_reader_t *self_p)
{
    uint32_t value;
    int i;
    int offset;

    offset = (32 + self_p->bit_offset);
    value = 0;

    for (i = 0; i < 4; i++) {
        offset -= 8;
        value |= ((uint64_t)self_p->buf_p[self_p->byte_offset] << offset);
        self_p->byte_offset++;
    }

    if (offset != 0) {
        value |= (self_p->buf_p[self_p->byte_offset] >> (8 - offset));
    }

    return (value);
}

uint64_t bitstream_reader_read_u64(struct bitstream_reader_t *self_p)
{
    uint64_t value;
    int i;
    int offset;

    offset = (64 + self_p->bit_offset);
    value = 0;

    for (i = 0; i < 8; i++) {
        offset -= 8;
        value |= ((uint64_t)self_p->buf_p[self_p->byte_offset] << offset);
        self_p->byte_offset++;
    }

    if (offset != 0) {
        value |= ((uint64_t)self_p->buf_p[self_p->byte_offset] >> (8 - offset));
    }

    return (value);
}

uint8_t bitstream_reader_read_u8_bits(struct bitstream_reader_t *self_p,
                                      int number_of_bits)
{
    uint8_t value;
    int i;

    value = 0;

    for (i = 0; i < number_of_bits; i++) {
        value <<= 1;
        value |= (bitstream_reader_read_bit(self_p));
    }

    return (value);
}

uint16_t bitstream_reader_read_u16_bits(struct bitstream_reader_t *self_p,
                                        int number_of_bits)
{
    uint16_t value;
    int i;

    value = 0;

    for (i = 0; i < number_of_bits; i++) {
        value <<= 1;
        value |= (bitstream_reader_read_bit(self_p));
    }

    return (value);
}

uint32_t bitstream_reader_read_u32_bits(struct bitstream_reader_t *self_p,
                                        int number_of_bits)
{
    uint32_t value;
    int i;

    value = 0;

    for (i = 0; i < number_of_bits; i++) {
        value <<= 1;
        value |= (bitstream_reader_read_bit(self_p));
    }

    return (value);
}

uint64_t bitstream_reader_read_u64_bits(struct bitstream_reader_t *self_p,
                                        int number_of_bits)
{
    uint64_t value;
    int i;

    value = 0;

    for (i = 0; i < number_of_bits; i++) {
        value <<= 1;
        value |= (bitstream_reader_read_bit(self_p));
    }

    return (value);
}
