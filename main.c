/*
 * File:    main
 * Author:  Spiros
 *
 * Created on June 18, 2018, 11:26 PM
 */

#ifndef RAWPCMTOWAV_MAIN_C
#define RAWPCMTOWAV_MAIN_C

#include "RawPcmToWav.h"

int main(int argc, char *argv[]) {
    if (argc == 2) {
        rawPcmToWav(argv[1]);
        return 0;
    } else {
        return -1;
    }


}

#endif //RAWPCMTOWAV_MAIN_C