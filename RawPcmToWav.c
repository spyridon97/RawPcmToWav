/*
 * File:    RawPcmToWav
 * Author:  Spiros
 *
 * Created on June 18, 2018, 11:30 PM
 */

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "RawPcmToWav.h"

void rawPcmToWav(char *filename) {
    unsigned int rawSize = 0;
    wav_header_t waveHeader;
    memset(&waveHeader, '\0', sizeof(wav_header_t));

    char *pcm_buf;
    FILE *fileForConversion;

    fileForConversion = fopen(filename, "rb+");
    if (fileForConversion == NULL) {
        printf ("File error");
        exit (1);
    }

    // obtain file size:
    fseek(fileForConversion, 0, SEEK_END);
    rawSize = (unsigned) ftell(fileForConversion);
    rewind(fileForConversion);

    // allocate memory to contain the whole file:
    pcm_buf = (char *) malloc(sizeof(char) * rawSize);
    if (pcm_buf == NULL) {
        printf ("Memory error");
        exit (2);
    }

    // copy the file into the pcm_buf:
    fread(pcm_buf, 1, rawSize, fileForConversion);
    rewind(fileForConversion);

    // RIFF chunk
    strcpy(waveHeader.chunk_id, "RIFF");
    waveHeader.chunk_size = 36 + rawSize;

    // fmt sub-chunk (to be optimized)
    strncpy(waveHeader.sub_chunk1_id, "WAVEfmt ", strlen("WAVEfmt "));
    waveHeader.sub_chunk1_size = 16;
    waveHeader.audio_format = 1;
    waveHeader.num_channels = 1; // change this
    waveHeader.sample_rate = 48000; //change this
    waveHeader.bits_per_sample = 32; // change this
    waveHeader.block_align = waveHeader.num_channels * waveHeader.bits_per_sample / 8;
    waveHeader.byte_rate = waveHeader.sample_rate * waveHeader.num_channels * waveHeader.bits_per_sample / 8;

    // data sub-chunk
    strncpy(waveHeader.sub_chunk2_id, "data", strlen("data"));
    waveHeader.sub_chunk2_size = rawSize;

    fwrite(&waveHeader, 1, sizeof(waveHeader), fileForConversion);
    fwrite(pcm_buf, 1, rawSize, fileForConversion);
    fclose(fileForConversion);

    free (pcm_buf);
}
