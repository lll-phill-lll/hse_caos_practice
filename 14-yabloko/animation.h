#pragma once

#include "drivers/vga.h"

#define NUM_FRAMES 14 

// Определение символов для анимации
const char* video_frames[NUM_FRAMES] = {
    "            _____\n"
    "            |***|\n"
    "            |***|\n"
    "           =======\n"
    "            (o.o)\n"
    "             |=|\n"
    "           ___|___\n"
    "          //.=|=.\\\\\n"
    "         // .=|=. \\\\\n"
    "        //  .=|=. //\n"
    "       (@   (_=_)//\n"
    "        |   |! !:)\n"
    "        |   || ||\n"
    "        |   () ()\n"
    "        |   || ||\n"
    "        |   || ||\n"
    "        \"  ==' '==\n\0",

    "            _____\n"
    "            |***|\n"
    "            |***|\n"
    "           =======\n"
    "            (o.o)\n"
    "             |=|\n"
    "           ___|___\n"
    "          //.=|=.\\\\\n"
    "         // .=|=. \\\\\n"
    "        //  .=|=.  \\\n"
    "       (@   (_=_)   \\\n"
    "        |   |! !|    (:\n"
    "        |   || ||\n"
    "        |   () ()\n"
    "        |   || ||\n"
    "        |   || ||\n"
    "        \"  ==' '==\n\0",

    "            _____\n"
    "            |***|\n"
    "            |***|\n"
    "           =======\n"
    "            (-.-)\n"
    "             |=|\n"
    "           ___|___\n"
    "          //.=|=.\\\\\n"
    "         // .=|=. \\\\\n"
    "        //  .=|=. ||\n"
    "       (@   (_=_) ||\n"
    "        |   |! !| ;:\n"
    "        |   || ||\n"
    "        |   () ()\n"
    "        |   || ||\n"
    "        |   || ||\n"
    "        \"  ==' '==\n\0",

    "            _____\n"
    "            |***|\n"
    "            |***|\n"
    "           =======\n"
    "            (o.o)\n"
    "             |=|\n"
    "           ___|___\n"
    "          //.=|=.\\\\\n"
    "         // .=|=. \\\\\n"
    "        //  .=|=.  \\\n"
    "       (@   (_=_)   \\\n"
    "        |   |! !|    (:\n"
    "        |   || ||\n"
    "        |   () ()\n"
    "        |   || ||\n"
    "        |   || ||\n"
    "        \"  ==' '==\n\0",

    "            _____\n"
    "            |***|\n"
    "            |***|\n"
    "           =======\n"
    "            (o.o)\n"
    "             |=|\n"
    "           ___|___\n"
    "          //.=|=.\\\\\n"
    "         // .=|=. \\\\\n"
    "        //  .=|=.  ===(:\n"
    "       (@   (_=_)\n"
    "        |   |! !|\n"
    "        |   || ||\n"
    "        |   () ()\n"
    "        |   || ||\n"
    "        |   || ||\n"
    "        \"  ==' '==\n\0",

    "            _____\n"
    "            |***|\n"
    "            |***|\n"
    "           =======\n"
    "            (o.o)\n"
    "             |=|\n"
    "           ___|___\n"
    "          //.=|=.\\\\\n"
    "         // .=|=. \\\\\n"
    "        //  .=|=.  \\/\n"
    "       (@   (_=_)\n"
    "        |   |! !|\n"
    "        |   || ||\n"
    "        |   () ()\n"
    "        |   || ||\n"
    "        |   || ||\n"
    "        \"  ==' '==\n\0",

    "            _____\n"
    "            |***|\n"
    "            |***|\n"
    "           =======:)\n"
    "            (o.o)  \\\\\n"
    "             |=|   //\n"
    "           ___|___//\n"
    "          //.=|=. /\n"
    "         // .=|=.\n"
    "        //  .=|=.\n"
    "       (@   (_=_)\n"
    "        |   |! !|\n"
    "        |   || ||\n"
    "        |   () ()\n"
    "        |   || ||\n"
    "        |   || ||\n"
    "        \"  ==' '==\n\0",

    "             _____\n"
    "             |***|\n"
    "             |***|\n"
    "            =======:)\n"
    "             .-.   ||\n"
    "            (o.o)  ||\n"
    "             |-|   //\n"
    "           ___|___//\n"
    "          //.=|=. /\n"
    "         // .=|=.\n"
    "        //  .=|=.\n"
    "       (@   (_=_)\n"
    "        |   |! !|\n"
    "        |   || ||\n"
    "        |   () ()\n"
    "        |   || ||\n"
    "        |   || ||\n"
    "        \"  ==' '==\n\0",

    "               _____\n"
    "               |***|\n"
    "               |***|\n"
    "              =======:)\n"
    "             .-.     //\n"
    "     GOOD   (o.o)   //\n"
    "   EVENING!  |=|   //\n"
    "           ___|___//\n"
    "          //.=|=. /\n"
    "         // .=|=.\n"
    "        //  .=|=.\n"
    "       (@   (_=_)\n"
    "        |   |! !|\n"
    "        |   || ||\n"
    "        |   () ()\n"
    "        |   || ||\n"
    "        |   || ||\n"
    "        \"  ==' '==\n\0",

    "               _____\n"
    "               |***|\n"
    "               |***|\n"
    "              =======:)\n"
    "             .-.     //\n"
    "     GOOD   (o.o)   //\n"
    "   EVENING!  |-|   //\n"
    "           ___|___//\n"
    "          //.=|=. /\n"
    "         // .=|=.\n"
    "        //  .=|=.\n"
    "       (@   (_=_)\n"
    "        |   |! !|\n"
    "        |   || ||\n"
    "        |   () ()\n"
    "        |   || ||\n"
    "        |   || ||\n"
    "        \"  ==' '==\n\0",

    "               _____\n"
    "               |***|\n"
    "               |***|\n"
    "              =======:)\n"
    "             .-.     //\n"
    "     GOOD   (o.o)   //\n"
    "   EVENING!  |=|   //\n"
    "           ___|___//\n"
    "          //.=|=. /\n"
    "         // .=|=.\n"
    "        //  .=|=.\n"
    "       (@   (_=_)\n"
    "        |   |! !|\n"
    "        |   || ||\n"
    "        |   () ()\n"
    "        |   || ||\n"
    "        |   || ||\n"
    "        \"  ==' '==\n\0",

    "               _____\n"
    "               |***|\n"
    "               |***|\n"
    "              =======:)\n"
    "             .-.     //\n"
    "            (o.o)   //\n"
    "             |=|   //\n"
    "           ___|___//\n"
    "          //.=|=. /\n"
    "         // .=|=.\n"
    "        //  .=|=.\n"
    "       (@   (_=_)\n"
    "        |   |! !|\n"
    "        |   || ||\n"
    "        |   () ()\n"
    "        |   || ||\n"
    "        |   || ||\n"
    "        \"  ==' '==\n\0",

    "            _____\n"
    "            |***|\n"
    "            |***|\n"
    "           =======:)\n"
    "            (-.-)  \\\\\n"
    "             |=|   //\n"
    "           ___|___//\n"
    "          //.=|=. /\n"
    "         // .=|=.\n"
    "        //  .=|=.\n"
    "       (@   (_=_)\n"
    "        |   |! !|\n"
    "        |   || ||\n"
    "        |   () ()\n"
    "        |   || ||\n"
    "        |   || ||\n"
    "        \"  ==' '==\n\0",

    "            _____\n"
    "            |***|\n"
    "            |***|\n"
    "           =======\n"
    "            (o.o)\n"
    "             |=|\n"
    "           ___|___\n"
    "          //.=|=.\\\\\n"
    "         // .=|=. \\\\\n"
    "        //  .=|=. //\n"
    "       (@   (_=_)//\n"
    "        |   |! !:)\n"
    "        |   || ||\n"
    "        |   () ()\n"
    "        |   || ||\n"
    "        |   || ||\n"
    "        \"  ==' '==\n\0",
};

static int iter = 0;
void draw_next_frame() {
    vga_print_colored(video_frames[iter++ % NUM_FRAMES]);

}
