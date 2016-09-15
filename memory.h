#ifndef memove_memove_h
#define memove_memove_h

void memmov(int *src, int *dst, int length)
{
    if (src <= dst)
    {
        int *se = src + length - 1;
        int *te = dst + length - 1;
        
        while(se >= src)
            *te-- = *se--;
    }
    else
    {
        int *sb = src;
        int *tb = dst;
        while(sb < src+length)
            *tb++ = *sb++;
    }
}


#endif

