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

void bitstream_writer_append_bit(struct bitstream_writer_t *self_p,
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

void bitstream_writer_append_u8(struct bitstream_writer_t *self_p,
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

void bitstream_writer_append_u16(struct bitstream_writer_t *self_p,
                                 uint16_t value)
{
    bitstream_writer_append_u8(self_p, value >> 8);
    bitstream_writer_append_u8(self_p, value >> 0);
}

void bitstream_writer_append_u32(struct bitstream_writer_t *self_p,
                                 uint32_t value)
{
    bitstream_writer_append_u8(self_p, value >> 24);
    bitstream_writer_append_u8(self_p, value >> 16);
    bitstream_writer_append_u8(self_p, value >> 8);
    bitstream_writer_append_u8(self_p, value >> 0);
}

void bitstream_writer_append_u64(struct bitstream_writer_t *self_p,
                                 uint64_t value)
{
    bitstream_writer_append_u8(self_p, value >> 56);
    bitstream_writer_append_u8(self_p, value >> 48);
    bitstream_writer_append_u8(self_p, value >> 40);
    bitstream_writer_append_u8(self_p, value >> 32);
    bitstream_writer_append_u8(self_p, value >> 24);
    bitstream_writer_append_u8(self_p, value >> 16);
    bitstream_writer_append_u8(self_p, value >> 8);
    bitstream_writer_append_u8(self_p, value >> 0);
}

void bitstream_writer_append_u8_bits(struct bitstream_writer_t *self_p,
                                     uint8_t value,
                                     int number_of_bits)
{
    int i;

    for (i = 0; i < number_of_bits; i++) {
        bitstream_writer_append_bit(self_p, (value >> (number_of_bits - i - 1)) & 0x1);
    }
}

void bitstream_writer_append_u16_bits(struct bitstream_writer_t *self_p,
                                      uint16_t value,
                                      int number_of_bits)
{
    int i;

    for (i = 0; i < number_of_bits; i++) {
        bitstream_writer_append_bit(self_p, (value >> (number_of_bits - i - 1)) & 0x1);
    }
}

void bitstream_writer_append_u32_bits(struct bitstream_writer_t *self_p,
                                      uint32_t value,
                                      int number_of_bits)
{
    int i;

    for (i = 0; i < number_of_bits; i++) {
        bitstream_writer_append_bit(self_p, (value >> (number_of_bits - i - 1)) & 0x1);
    }
}

void bitstream_writer_append_u64_bits(struct bitstream_writer_t *self_p,
                                      uint64_t value,
                                      int number_of_bits)
{
    int i;

    for (i = 0; i < number_of_bits; i++) {
        bitstream_writer_append_bit(self_p, (value >> (number_of_bits - i - 1)) & 0x1);
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
    self_p->pos_in_bits = 0;
}
