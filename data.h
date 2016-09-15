#ifndef data_main_h
#define data_main_h

int my_atoi(const char *nptr)
{
    
    int res=0;
    int flag = 0;
    while (*nptr == ' ')
    {
        nptr++;
    }
    
    if (*nptr == '\0')
        return 0;
    
    if (*nptr == '-')
    {
        flag = 1;
        nptr++;
    }
    else if (*nptr == '+')
    {
        nptr++;
    }
    
    while (*nptr >= '0' && *nptr <= '9')
    {
        res *= 10;
        res += *nptr - '0';
        nptr++;
    }
    
    if (!flag)
        return res;
    else
        return -res;
    
}


#endif
