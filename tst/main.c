#include "narwhal.h"
#include "bitstream.h"

TEST(write_append_bit)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_append_bit(&writer, 1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 1);
    ASSERT_MEMORY(&buf[0], "\x80", 1);

    bitstream_writer_append_bit(&writer, 0);
    bitstream_writer_append_bit(&writer, 1);
    bitstream_writer_append_bit(&writer, 0);
    bitstream_writer_append_bit(&writer, 1);
    bitstream_writer_append_bit(&writer, 0);
    bitstream_writer_append_bit(&writer, 1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 1);
    ASSERT_MEMORY(&buf[0], "\xaa", 1);

    bitstream_writer_append_bit(&writer, 0);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 1);
    ASSERT_MEMORY(&buf[0], "\xaa", 1);

    bitstream_writer_append_bit(&writer, 1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 2);
    ASSERT_MEMORY(&buf[0], "\xaa\x80", 2);
}

TEST(write_append_u8)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_append_u8(&writer, 0x12);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 1);
    ASSERT_MEMORY(&buf[0], "\x12", 1);

    bitstream_writer_append_bit(&writer, 1);
    bitstream_writer_append_u8(&writer, 0xf1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 3);
    ASSERT_MEMORY(&buf[0], "\x12\xf8\x80", 3);
}

TEST(write_append_u16)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_append_u16(&writer, 0x1234);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 2);
    ASSERT_MEMORY(&buf[0], "\x12\x34", 2);

    bitstream_writer_append_bit(&writer, 1);
    bitstream_writer_append_u16(&writer, 0xf1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 5);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x80\x78\x80", 5);
}

TEST(write_append_u32)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_append_u32(&writer, 0x12345678);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 4);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x56\x78", 4);

    bitstream_writer_append_bit(&writer, 1);
    bitstream_writer_append_u32(&writer, 0xf1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 9);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x56\x78\x80\x00\x00\x78\x80", 9);
}

TEST(write_append_u64)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_append_u64(&writer, 0x0123456789abcdefll);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 8);
    ASSERT_MEMORY(&buf[0], "\x01\x23\x45\x67\x89\xab\xcd\xef", 8);

    bitstream_writer_append_bit(&writer, 1);
    bitstream_writer_append_u64(&writer, 0xf1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 17);
    ASSERT_MEMORY(
        &buf[0],
        "\x01\x23\x45\x67\x89\xab\xcd\xef\x80\x00\x00\x00\x00\x00\x00\x78\x80",
        17);
}

TEST(write_append_u8_bits)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_append_u8_bits(&writer, 0x01, 4);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 1);
    ASSERT_MEMORY(&buf[0], "\x10", 1);

    bitstream_writer_append_u8_bits(&writer, 0x01, 4);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 1);
    ASSERT_MEMORY(&buf[0], "\x11", 1);
}

TEST(write_append_u16_bits)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_append_u16_bits(&writer, 0x123, 12);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 2);
    ASSERT_MEMORY(&buf[0], "\x12\x30", 2);

    bitstream_writer_append_u16_bits(&writer, 0x123, 12);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 3);
    ASSERT_MEMORY(&buf[0], "\x12\x31\x23", 3);
}

TEST(write_append_u32_bits)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_append_u32_bits(&writer, 0x12345, 20);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 3);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x50", 3);

    bitstream_writer_append_u64_bits(&writer, 0x12345, 20);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 5);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x51\x23\x45", 5);
}

TEST(write_append_u64_bits)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_append_u64_bits(&writer, 0x123456789, 36);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 5);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x56\x78\x90", 5);

    bitstream_writer_append_u64_bits(&writer, 0x123456789, 36);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 9);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x56\x78\x91\x23\x45\x67\x89", 9);
}

int main()
{
    return RUN_TESTS(
        write_append_bit,
        write_append_u8,
        write_append_u16,
        write_append_u32,
        write_append_u64,
        write_append_u8_bits,
        write_append_u16_bits,
        write_append_u32_bits,
        write_append_u64_bits
    );
}
