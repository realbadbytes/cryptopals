// hex to base64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//instructions: always operate on raw bytes, never on encoded strings
// 		only use hex and base64 for pretty printing

const char BASE64_TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int hex_to_bytes(const char *hex, unsigned char **bytes) {
  size_t len = strlen(hex);
  if (len %2 != 0) return -1; // no padding for hex, like b64 =?
  
  // 2 chars of the string is 1 byte
  size_t byte_len = len/2;
  *bytes = malloc(byte_len);
  if (!*bytes) return -1;

  for (size_t i = 0; i < byte_len; i++){
    // store formatted to heap, processes input 2 chars at a time, this is a pointer offset into string
    // format string: reads 2 hex numbers and stores as 1 byte (unsigned char), hh is a length modifier
    // to store as the char instead of int.
    sscanf(hex + 2*i, "%2hhx", &(*bytes)[i]);
  }
  return byte_len;
}

// manual base64 encoding. 6 bits at a time
char *base64_encode(const unsigned char *input, int len){
  int output_len =((len + 2) / 3) * 4; // input len is byte array len, +2 for padding? I dont understand this line
  char *encoded = malloc(output_len+1);
  if (!encoded) return -1;

  int i, j;
  for (i = 0, j = 0; i < len; i += 3){
    // triplet is 32 bits, input is processed in chunk sof 24 bits (first bit set divisible by 6 and 8 cleanly)
    unsigned int triplet = input[i] << 16;
    // triplet first byte now is input[i]. len checks prevent reading outside buffer, otherwise leave rest of triplet with 0
    if (i + 1 < len) triplet |= input[i+1] << 8;
    // triplet second byte is input[i+1], moved it over into 2nd byte slot with << 8
    if (i + 2 < len) triplet |= input[i+2];

    // encoding of the triplet
    // 0x3F is 00111111, a bitmask to only look at 6 bits at a time. bit shifts will move each triplet into the lowest 6 bits
    // then mask applied to ignore most significant 2 bits
    // j is incremented in loop to write 4 base64 values per loop. 24 bits = 4 base64 chars, 3 hex chars
    encoded[j++] = BASE64_TABLE[(triplet >> 18) & 0x3F];
    encoded[j++] = BASE64_TABLE[(triplet >> 12) & 0x3F];
    // conditionally check if reached end of byte array, if so apply padding character "="
    encoded[j++] = (i + 1 < len) ? BASE64_TABLE[(triplet >> 6) & 0x3F] : "=";
    encoded[j++] = (i + 2 < len) ? BASE64_TABLE[triplet & 0x3F] : "=";
  }
  encoded[j] = "\0";
  return encoded;
}

int main(){

  // hex encodes with 16 vals: 0-9, a-f
  char *hex_input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  // expected base64: "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
  unsigned char *bytes;
 
  int byte_len = hex_to_bytes(hex_input, &bytes);
  if (byte_len < 0){
    printf("Invalid hex\n");
    return -1;
  }

  char *b64_output = base64_encode(bytes, byte_len);
  if (b64_output){
    printf("Base64: %s\n", b64_output);
    free(b64_output);
  }

  return 0;

}
