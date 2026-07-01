#include <KnightRider.h>

void renderKnightRider(Frame *frame, uint32_t animationFrame)
{
    clearFrame(frame, 100);

    unsigned int position = animationFrame % ((LED_COUNT * 2) - 2);

    if (position >= LED_COUNT)
    {
        position = ((LED_COUNT * 2) - 2) - position;
    }

    frame->pixels[position] = LED_RED;
}
