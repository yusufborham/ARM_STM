#ifndef HEX_PARSER_INT_H
#define HEX_PARSER_INT_H

#include "../../LIB/STD_TYPES.h"

// --- Definitions ---
#define HEX_MAX_DATA_BYTES   255  // Max payload size as per Intel HEX spec

// --- Type Definitions ---

/**
 * @brief Status codes returned by the parser.
 */
typedef enum {
    HEX_PARSE_OK,                    /**< Record parsed successfully. */
    HEX_PARSE_ERROR_NULL_PTR,        /**< A null pointer argument was provided. */
    HEX_PARSE_ERROR_BAD_FORMAT,      /**< Line does not start with ':' or has invalid length. */
    HEX_PARSE_ERROR_INVALID_CHAR,    /**< Line contains a non-hexadecimal character. */
    HEX_PARSE_ERROR_CHECKSUM_FAIL,   /**< Calculated checksum does not match the record's checksum. */
    HEX_PARSE_ERROR_COUNT_MISMATCH   /**< The actual byte count does not match the specified byte count. */
} HexParser_Status_t;

/**
 * @brief Represents a fully parsed and validated Intel HEX record.
 */
typedef struct {
    u8  byteCount;
    u16 address;
    u8  recordType;
    u8  data[HEX_MAX_DATA_BYTES];
    u8  checksum;
} HexRecord_t;


// --- Public API ---

/**
 * @brief Parses a single line of ASCII Intel HEX data into a structured format.
 * This function is fully self-contained and stateless.
 * @param line A pointer to the null-terminated ASCII string of the HEX record.
 * @param record_out A pointer to a HexRecord_t struct where the parsed data will be stored.
 * @return HexParser_Status_t indicating the success or failure of the operation.
 */
HexParser_Status_t HEX_parseRecord(const u8* line, HexRecord_t* record_out);

#endif /* HEX_PARSER_INT_H */
