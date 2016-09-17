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

char *my_itoa(int val, char *buf, unsigned radix)
{
    char   *p;
    char   *firstdig;
    char   temp;
    unsigned   digval;
    p = buf;
    
    if(val <0)
    {
        *p++ = '-';
        val = (unsigned long)(-(long)val);
    }
    
    firstdig = p;
    
    do{
        digval = (unsigned)(val % radix);
        val /= radix;
        
        if  (digval > 9)
            *p++ = (char)(digval - 10 + 'a');
        else
            *p++ = (char)(digval + '0');
    }while(val > 0);
    
    *p-- = '\0 ';
   
    do{
        temp = *p;
        *p = *firstdig;
        *firstdig = temp;
        --p;
        ++firstdig;
    }while(firstdig < p);
   
    return buf;
}


#endif
