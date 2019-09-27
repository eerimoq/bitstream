#include "narwhal.h"
#include "bitstream.h"

TEST(write_bit)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    memset(&buf[0], 0xff, sizeof(buf));
    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_write_bit(&writer, 1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 1);
    ASSERT_MEMORY(&buf[0], "\x80", 1);

    bitstream_writer_write_bit(&writer, 0);
    bitstream_writer_write_bit(&writer, 1);
    bitstream_writer_write_bit(&writer, 0);
    bitstream_writer_write_bit(&writer, 1);
    bitstream_writer_write_bit(&writer, 0);
    bitstream_writer_write_bit(&writer, 1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 1);
    ASSERT_MEMORY(&buf[0], "\xaa", 1);

    bitstream_writer_write_bit(&writer, 0);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 1);
    ASSERT_MEMORY(&buf[0], "\xaa", 1);

    bitstream_writer_write_bit(&writer, 1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 2);
    ASSERT_MEMORY(&buf[0], "\xaa\x80", 2);
}

TEST(write_bytes)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    memset(&buf[0], 0xff, sizeof(buf));
    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_write_bytes(&writer, (uint8_t *)"\x12", 1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 1);
    ASSERT_MEMORY(&buf[0], "\x12", 1);

    bitstream_writer_write_bit(&writer, 1);
    bitstream_writer_write_bytes(&writer, (uint8_t *)"\xf1\x00", 2);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 4);
    ASSERT_MEMORY(&buf[0], "\x12\xf8\x80", 4);
}

TEST(write_u8)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    memset(&buf[0], 0xff, sizeof(buf));
    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_write_u8(&writer, 0x12);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 1);
    ASSERT_MEMORY(&buf[0], "\x12", 1);

    bitstream_writer_write_bit(&writer, 1);
    bitstream_writer_write_u8(&writer, 0xf1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 3);
    ASSERT_MEMORY(&buf[0], "\x12\xf8\x80", 3);
}

TEST(write_u16)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    memset(&buf[0], 0xff, sizeof(buf));
    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_write_u16(&writer, 0x1234);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 2);
    ASSERT_MEMORY(&buf[0], "\x12\x34", 2);

    bitstream_writer_write_bit(&writer, 1);
    bitstream_writer_write_u16(&writer, 0xf1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 5);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x80\x78\x80", 5);
}

TEST(write_u32)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    memset(&buf[0], 0xff, sizeof(buf));
    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_write_u32(&writer, 0x12345678);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 4);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x56\x78", 4);

    bitstream_writer_write_bit(&writer, 1);
    bitstream_writer_write_u32(&writer, 0xf1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 9);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x56\x78\x80\x00\x00\x78\x80", 9);
}

TEST(write_u64)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    memset(&buf[0], 0xff, sizeof(buf));
    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_write_u64(&writer, 0x0123456789abcdefll);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 8);
    ASSERT_MEMORY(&buf[0], "\x01\x23\x45\x67\x89\xab\xcd\xef", 8);

    bitstream_writer_write_bit(&writer, 1);
    bitstream_writer_write_u64(&writer, 0xf1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 17);
    ASSERT_MEMORY(
        &buf[0],
        "\x01\x23\x45\x67\x89\xab\xcd\xef\x80\x00\x00\x00\x00\x00\x00\x78\x80",
        17);
}

TEST(write_u8_bits)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    memset(&buf[0], 0xff, sizeof(buf));
    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_write_u64_bits(&writer, 0x01, 4);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 1);
    ASSERT_MEMORY(&buf[0], "\x10", 1);

    bitstream_writer_write_u64_bits(&writer, 0x01, 4);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 1);
    ASSERT_MEMORY(&buf[0], "\x11", 1);
}

TEST(write_u16_bits)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    memset(&buf[0], 0xff, sizeof(buf));
    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_write_u64_bits(&writer, 0x123, 12);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 2);
    ASSERT_MEMORY(&buf[0], "\x12\x30", 2);

    bitstream_writer_write_u64_bits(&writer, 0x123, 12);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 3);
    ASSERT_MEMORY(&buf[0], "\x12\x31\x23", 3);
}

TEST(write_u32_bits)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    memset(&buf[0], 0xff, sizeof(buf));
    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_write_u64_bits(&writer, 0x12345, 20);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 3);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x50", 3);

    bitstream_writer_write_u64_bits(&writer, 0x12345, 20);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 5);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x51\x23\x45", 5);
}

TEST(write_u64_bits)
{
    struct bitstream_writer_t writer;
    uint8_t buf[32];

    memset(&buf[0], 0xff, sizeof(buf));
    bitstream_writer_init(&writer, &buf[0]);

    bitstream_writer_write_u64_bits(&writer, 0x123456789, 36);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 5);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x56\x78\x90", 5);

    bitstream_writer_write_u64_bits(&writer, 0x123456789, 36);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 9);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x56\x78\x91\x23\x45\x67\x89", 9);

    bitstream_writer_write_u64_bits(&writer, 0x1, 0);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 9);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x56\x78\x91\x23\x45\x67\x89", 9);

    bitstream_writer_write_u64_bits(&writer, 0x1, 1);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 10);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x56\x78\x91\x23\x45\x67\x89\x80", 10);

    bitstream_writer_write_u64_bits(&writer, 0x1, 7);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 10);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x56\x78\x91\x23\x45\x67\x89\x81", 10);

    bitstream_writer_write_u64_bits(&writer, 0x1, 8);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 11);
    ASSERT_MEMORY(&buf[0], "\x12\x34\x56\x78\x91\x23\x45\x67\x89\x81\x01", 11);

    bitstream_writer_write_u64_bits(&writer, 0x1, 63);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 19);
    ASSERT_MEMORY(
        &buf[0],
        "\x12\x34\x56\x78\x91\x23\x45\x67\x89\x81\x01\x00\x00\x00\x00\x00"
        "\x00\x00\x02",
        19);

    bitstream_writer_write_u64_bits(&writer, 0x1, 64);
    ASSERT_EQ(bitstream_writer_size_in_bytes(&writer), 27);
    ASSERT_MEMORY(
        &buf[0],
        "\x12\x34\x56\x78\x91\x23\x45\x67\x89\x81\x01\x00\x00\x00\x00\x00"
        "\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x02",
        27);
}

TEST(read_bit)
{
    struct bitstream_reader_t reader;
    uint8_t buf[] = { 0xaa, 0x80 };

    bitstream_reader_init(&reader, &buf[0]);

    ASSERT_EQ(bitstream_reader_read_bit(&reader), 1);
    ASSERT_EQ(bitstream_reader_read_bit(&reader), 0);
    ASSERT_EQ(bitstream_reader_read_bit(&reader), 1);
    ASSERT_EQ(bitstream_reader_read_bit(&reader), 0);
    ASSERT_EQ(bitstream_reader_read_bit(&reader), 1);
    ASSERT_EQ(bitstream_reader_read_bit(&reader), 0);
    ASSERT_EQ(bitstream_reader_read_bit(&reader), 1);
    ASSERT_EQ(bitstream_reader_read_bit(&reader), 0);
    ASSERT_EQ(bitstream_reader_read_bit(&reader), 1);
}

TEST(read_u8)
{
    struct bitstream_reader_t reader;
    uint8_t buf[] = { 0x12, 0xf8, 0x80 };

    bitstream_reader_init(&reader, &buf[0]);

    ASSERT_EQ(bitstream_reader_read_u8(&reader), 0x12);
    ASSERT_EQ(bitstream_reader_read_bit(&reader), 1);
    ASSERT_EQ(bitstream_reader_read_u8(&reader), 0xf1);
}

TEST(read_bytes)
{
    struct bitstream_reader_t reader;
    uint8_t buf[] = { 0x12, 0xf8, 0x80, 0x00 };
    uint8_t data[2];

    bitstream_reader_init(&reader, &buf[0]);

    bitstream_reader_read_bytes(&reader, &data[0], 1);
    ASSERT_MEMORY(&data[0], "\x12", 1);
    ASSERT_EQ(bitstream_reader_read_bit(&reader), 1);
    bitstream_reader_read_bytes(&reader, &data[0], 1);
    ASSERT_MEMORY(&data[0], "\xf1", 1);
}

TEST(read_u16)
{
    struct bitstream_reader_t reader;
    uint8_t buf[] = { 0x12, 0x34, 0x80, 0x78, 0x80 };

    bitstream_reader_init(&reader, &buf[0]);

    ASSERT_EQ(bitstream_reader_read_u16(&reader), 0x1234);
    ASSERT_EQ(bitstream_reader_read_bit(&reader), 1);
    ASSERT_EQ(bitstream_reader_read_u16(&reader), 0xf1);
}

TEST(read_u32)
{
    struct bitstream_reader_t reader;
    uint8_t buf[] = { 0x12, 0x34, 0x56, 0x78, 0x80, 0x00, 0x00, 0x78, 0x80 };

    bitstream_reader_init(&reader, &buf[0]);

    ASSERT_EQ(bitstream_reader_read_u32(&reader), 0x12345678);
    ASSERT_EQ(bitstream_reader_read_bit(&reader), 1);
    ASSERT_EQ(bitstream_reader_read_u32(&reader), 0xf1);
}

TEST(read_u64)
{
    struct bitstream_reader_t reader;
    uint8_t buf[] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x80, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x80
    };

    bitstream_reader_init(&reader, &buf[0]);

    ASSERT_EQ(bitstream_reader_read_u64(&reader), 0x0123456789abcdefll);
    ASSERT_EQ(bitstream_reader_read_bit(&reader), 1);
    ASSERT_EQ(bitstream_reader_read_u64(&reader), 0xf1);
}

TEST(read_u8_bits)
{
    struct bitstream_reader_t reader;
    uint8_t buf[] = { 0x11 };

    bitstream_reader_init(&reader, &buf[0]);

    ASSERT_EQ(bitstream_reader_read_u8_bits(&reader, 4), 0x01);
    ASSERT_EQ(bitstream_reader_read_u8_bits(&reader, 4), 0x01);
}

TEST(read_u16_bits)
{
    struct bitstream_reader_t reader;
    uint8_t buf[] = { 0x12, 0x31, 0x23 };

    bitstream_reader_init(&reader, &buf[0]);

    ASSERT_EQ(bitstream_reader_read_u16_bits(&reader, 12), 0x123);
    ASSERT_EQ(bitstream_reader_read_u16_bits(&reader, 12), 0x123);
}

TEST(read_u32_bits)
{
    struct bitstream_reader_t reader;
    uint8_t buf[] = { 0x12, 0x34, 0x51, 0x23, 0x45 };

    bitstream_reader_init(&reader, &buf[0]);

    ASSERT_EQ(bitstream_reader_read_u32_bits(&reader, 20), 0x12345);
    ASSERT_EQ(bitstream_reader_read_u64_bits(&reader, 20), 0x12345);
}

TEST(read_u64_bits)
{
    struct bitstream_reader_t reader;
    uint8_t buf[] = { 0x12, 0x34, 0x56, 0x78, 0x91, 0x23, 0x45, 0x67, 0x89 };

    bitstream_reader_init(&reader, &buf[0]);

    ASSERT_EQ(bitstream_reader_read_u64_bits(&reader, 36), 0x123456789ll);
    ASSERT_EQ(bitstream_reader_read_u64_bits(&reader, 36), 0x123456789ll);
}

int main()
{
    return RUN_TESTS(
        write_bit,
        write_bytes,
        write_u8,
        write_u16,
        write_u32,
        write_u64,
        write_u8_bits,
        write_u16_bits,
        write_u32_bits,
        write_u64_bits,
        read_bit,
        read_bytes,
        read_u8,
        read_u16,
        read_u32,
        read_u64,
        read_u8_bits,
        read_u16_bits,
        read_u32_bits,
        read_u64_bits
    );
}
