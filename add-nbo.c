/*
 * written by Geunyeong Choi at 13 Jul 2020
 */

#if ( defined(_WIN32) || defined(_WIN64) )

	#define _CRT_SECURE_NO_WARNINGS

#endif

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#if ( defined(__linux) || defined(_linux) )

	#include <netinet/in.h>

#elif ( defined(_WIN32) || defined(_WIN64) )

	#include <Winsock2.h>
	#pragma comment(lib, "ws2_32")

#endif

int main(int argc, char *argv[]) {
    FILE *file1_fp, *file2_fp;
    uint32_t file1_value, file2_value, sum_value;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    file1_fp = fopen(argv[1], "rb");
    file2_fp = fopen(argv[2], "rb");

    if (file1_fp == NULL || file2_fp == NULL) {
        fprintf(stderr, "Cannot open file1 or file2\n");
        return 1;
    }

    if (fread(&file1_value, sizeof(uint32_t), 1, file1_fp) == EOF) {
        fprintf(stderr, "File1 data may be invalid\n");
        return 1;
    }

    if (fread(&file2_value, sizeof(uint32_t), 1, file2_fp) == EOF) {
        fprintf(stderr, "File2 data may be invalid\n");
        return 1;
    }

    file1_value = htonl(file1_value);
    file2_value = htonl(file2_value);
    sum_value = file1_value + file2_value;

    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n",
        file1_value,
        file1_value,
        file2_value,
        file2_value,
        sum_value,
        sum_value
    );

    return 0;
}
