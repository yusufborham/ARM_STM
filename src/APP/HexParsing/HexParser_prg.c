#include "HexParser_int.h"

// --- Private Helper Functions ---

/**
 * @brief Converts a single hexadecimal ASCII character to its 4-bit integer value.
 */
static s32 prv_asciiToNibble(u8 ascii_char) {
    if (ascii_char >= '0' && ascii_char <= '9') {
        return ascii_char - '0';
    }
    if (ascii_char >= 'A' && ascii_char <= 'F') {
        return ascii_char - 'A' + 10;
    }
    if (ascii_char >= 'a' && ascii_char <= 'f') {
        return ascii_char - 'a' + 10;
    }
    return -1; // Invalid character
}

/**
 * @brief Converts two hexadecimal ASCII characters into a single byte.
 */
static s32 prv_asciiToByte(const u8* ascii_pair) {
    s32 high_nibble = prv_asciiToNibble(ascii_pair[0]);
    s32 low_nibble = prv_asciiToNibble(ascii_pair[1]);

    if (high_nibble < 0 || low_nibble < 0) {
        return -1; // Invalid character in pair
    }
    return (high_nibble << 4) | low_nibble;
}


// --- Public API Implementation ---

HexParser_Status_t HEX_parseRecord(const u8* line, HexRecord_t* record_out) {
    // --- 1. Precondition Checks (Safety) ---
    if (line == NULL || record_out == NULL) {
        return HEX_PARSE_ERROR_NULL_PTR;
    }

    if (line[0] != ':') {
        return HEX_PARSE_ERROR_BAD_FORMAT;
    }

    u32 line_len = 0;
    while(line[line_len] != '\0') {
        line_len++;
    }

    // Smallest record is ":00000001FF" (11 chars). Must be an odd number of chars.
    if (line_len < 11 || (line_len % 2) == 0) {
        return HEX_PARSE_ERROR_BAD_FORMAT;
    }

    // --- 2. Convert ASCII to Raw Bytes and Calculate Checksum ---
    u8 byte_buffer[(line_len - 1) / 2];
    u8 calculated_checksum = 0;
    
    for (u32 i = 0; i < sizeof(byte_buffer); ++i) {
        s32 byte_val = prv_asciiToByte(&line[(i * 2) + 1]);
        if (byte_val < 0) {
            return HEX_PARSE_ERROR_INVALID_CHAR;
        }
        byte_buffer[i] = (u8)byte_val;
        if (i < sizeof(byte_buffer) - 1) { // Don't include the record's checksum in our calculation
            calculated_checksum += byte_buffer[i];
        }
    }

    // Finalize checksum (two's complement)
    calculated_checksum = ~calculated_checksum + 1;

    // --- 3. Validate Checksum ---
    u8 record_checksum = byte_buffer[sizeof(byte_buffer) - 1];
    if (calculated_checksum != record_checksum) {
        return HEX_PARSE_ERROR_CHECKSUM_FAIL;
    }

    // --- 4. Populate Output Struct from Validated Data ---
    record_out->byteCount = byte_buffer[0];
    record_out->address = (byte_buffer[1] << 8) | byte_buffer[2];
    record_out->recordType = byte_buffer[3];
    record_out->checksum = record_checksum;

    // Validate byte count against actual data length
    if (record_out->byteCount != sizeof(byte_buffer) - 5) {
        return HEX_PARSE_ERROR_COUNT_MISMATCH;
    }

    for (u8 i = 0; i < record_out->byteCount; ++i) {
        record_out->data[i] = byte_buffer[i + 4];
    }

    return HEX_PARSE_OK;
}

/*
// To use in bootloader logic 
u32 base_address = 0;
// Loop, receiving one line at a time from UART/CAN/etc. into a `line_buffer`
while(receive_line(line_buffer)) {
    HexRecord_t record;
    HexParser_Status_t status = HEX_parseRecord(line_buffer, &record);

    if (status != HEX_PARSE_OK) {
        // Handle error: request re-transmission or abort
        continue;
    }

    switch(record.recordType) {
        case 0x00: // Data Record
            u32 full_address = base_address + record.address;
            flash_write(full_address, record.data, record.byteCount);
            break;
        case 0x04: // Extended Linear Address Record
            base_address = (record.data[0] << 24) | (record.data[1] << 16);
            break;
        case 0x01: // End of File Record
            // Finalize and jump to application
            break;
        // Handle other record types as needed (02, 03, 05)
    }
}
*/