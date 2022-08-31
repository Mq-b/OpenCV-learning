#include <iostream>

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}

int main(int argc, char* argv[]) {
    //printf("%s\n", avcodec_configuration());
    system(" ffmpeg -i .\\video\\蕾姆海边.mp4 -f mp3 -vn test.mp3");
}