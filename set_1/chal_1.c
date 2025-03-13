// hex to base64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//instructions: always operate on raw bytes, never on encoded strings
// 		only use hex and base64 for pretty printing

int main(){

  // hex encodes with 16 vals: 0-9, a-f
  char hex_input[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  char b64_output[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
  printf("Hex input: %s\n", hex_input);
  printf("Expected b64 output: %s\n", b64_output);
  printf("sizeof char: %lu bytes\n", sizeof(char));
  
  // output guaranteed to be shorter than input length
  char bytearray[strlen(hex_input) * sizeof(char)];
  hex_to_b64(bytearray, hex_input);
  return 0;

}

void hex_to_b64(char bytearray[], char input[]){
  // create byte array from hex string
  for (int i = 0; i < strlen(input); i++){
    bytearray[i] = 
  }
  printf("%d", bytearray[0]);
}
