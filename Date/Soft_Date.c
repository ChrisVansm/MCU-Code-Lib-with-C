/*
**#############################################################################
**      SVN Information
**
**      Checked In          :
**
**      Revision            :
**
**      Release Information :
**#############################################################################
*/
#include "Soft_Date.h"
////////////////////////////////////////////////////////////////////////////////
//
// Date functions
//
// Be used make a soft date and include second;minute;hour;day;week;month;year;
//
////////////////////////////////////////////////////////////////////////////////

#define COUNT_MODE_HEX
//#define COUNT_MODE_BCD

/*
**#############################################################################
** Variable 
**#############################################################################
*/
Date user_date = {0,0,0,1,1,1,1};
Date *p_user_date = &user_date;

/*
**#############################################################################
** Functions
**#############################################################################
*/



/*
**#############################################################################
** Set Soft Date
**#############################################################################
*/
void Date_Set(Date *setdate)
{
   user_date = *setdate;
}

/*
**#############################################################################
** Get Soft Date
**#############################################################################
*/
Date *Date_Get(void)
{
    return p_user_date;
}

/*
**#############################################################################
** Second update function
**#############################################################################
*/
void Date_Second_Update(void)
{
#if COUNT_MODE_HEX
    p_user_date->second ++;
#else 
    p_user_date->second = (unsigned char)Hex_To_Bcd((unsigned short)p_user_date->second ++);
#endif

#if COUNT_MODE_HEX
    if(p_user_date->second == 60)       // If second arrive 60,reset second to zero,and transfer minute update function.
#else
    if(p_user_date->second == 0x60)
#endif
    {
        p_user_date->second = 0;
        Date_Minute_Update();
    }
}

/*
**#############################################################################
** Minute update function
**#############################################################################
*/
void Date_Minute_Update(void)
{
#if COUNT_MODE_HEX
    p_user_date->minute ++;
#else
    p_user_date->minute = (unsigned char)Hex_To_Bcd((unsigned short)p_user_date->minute ++);
#endif

#if COUNT_MODE_HEX
    if(p_user_date->minute == 60)
#else
    if(p_user_date->minute == 0x60)
#endif
    {
        p_user_date->minute = 0;
        Date_Hour_Update();
    }  
}

/*
**#############################################################################
** Hour update function
**#############################################################################
*/
void Date_Hour_Update(void)
{
#if COUNT_MODE_HEX
    p_user_date->hour ++;
#else
    p_user_date->hour = (unsigned char)Hex_To_Bcd((unsigned short)p_user_date->hour ++);
#endif

#if COUNT_MODE_HEX
    if(p_user_date->hour == 24)
#else
    if(p_user_date->hour == 0x24)
#endif
    {
        p_user_date->hour = 0;
        Date_Day_Update();
        Date_Week_Update();
    }
}

/*
**#############################################################################
** Day update function
**#############################################################################
*/
void Date_Day_Update(void)
{
#if COUNT_MODE_HEX
    p_user_date->day ++;
#else
    p_user_date->day = (unsigned char)Hex_To_Bcd((unsigned short)p_user_date->day ++);
#endif

#if COUNT_MODE_HEX
    if((p_user_date->month == 1)||
       (p_user_date->month == 3)||
       (p_user_date->month == 5)||
       (p_user_date->month == 7)||
       (p_user_date->month == 8)||
       (p_user_date->month == 10)||
       (p_user_date->month == 12))
#else
    if((p_user_date->month == 1)||
       (p_user_date->month == 3)||
       (p_user_date->month == 5)||
       (p_user_date->month == 7)||
       (p_user_date->month == 8)||
       (p_user_date->month == 0x10)||
       (p_user_date->month == 0x12))
#endif
    {
#if COUNT_MODE_HEX
        if(p_user_date->day == 32)
#else
        if(p_user_date->day == 0x32)
#endif
        {
            p_user_date->day = 1;
            Date_Month_Update();
        }
    }
#if COUNT_MODE_HEX
    else if((p_user_date->month == 4)||
            (p_user_date->month == 6)||
            (p_user_date->month == 9)||
            (p_user_date->month == 11))
#else
    else if((p_user_date->month == 4)||
            (p_user_date->month == 6)||
            (p_user_date->month == 9)||
            (p_user_date->month == 0x11))
#endif
    {
#if COUNT_MODE_HEX
        if(p_user_date->day == 31)
#else
        if(p_user_date->day == 0x31)
#endif
        {
            p_user_date->day = 1;
            Date_Month_Update();
        }
    }
    else
    {
#if COUNT_MODE_HEX
        if(((p_user_date->year%4 == 0) && 
            (p_user_date->year%100 != 0))||
            (p_user_date->year%400 == 0))
#else
        if(((Bcd_To_Hex((unsigned short)p_user_date->year)%4 == 0) && 
            (Bcd_To_Hex((unsigned short)p_user_date->year)%100 != 0))||
            (Bcd_To_Hex((unsigned short)p_user_date->year)%400 == 0))
#endif
        {
#if COUNT_MODE_HEX
            if(p_user_date->day == 30)
#else      
            if(p_user_date->day == 0x30)
#endif
            {
                p_user_date->day = 1;
                Date_Month_Update();
            }
        }
        else
        {
#if COUNT_MODE_HEX
            if(p_user_date->day == 29)
#else
            if(p_user_date->day == 0x29)
#endif
            {
                p_user_date->day = 1;
                Date_Month_Update();
            }
        }
    }
}

/*
**#############################################################################
** Week update function
**#############################################################################
*/
void Date_Week_Update(void)
{
    p_user_date->week ++;
    if(p_user_date->week == 8)
        p_user_date->week = 1;
}

/*
**#############################################################################
** Month update function
**#############################################################################
*/
void Date_Month_Update(void)
{
#if COUNT_MODE_HEX
    p_user_date->month ++;
#else 
    p_user_date->month = (unsigned char)Hex_To_Bcd((unsigned short)p_user_date->month ++);
#endif

#if COUNT_MODE_HEX
    if(p_user_date->month == 13)
#else
    if(p_user_date->month == 0x13)
#endif
    {
        p_user_date->month = 1;
        Date_Year_Update();
    }
}

/*
**#############################################################################
** Year update function
**#############################################################################
*/
void Date_Year_Update(void)
{
#if COUNT_MODE_HEX
    p_user_date->year ++;
#else
    p_user_date->year = Hex_To_Bcd((unsigned short)p_user_date->year ++);
#endif
}

/*
**#############################################################################
** HEX to BCD
**#############################################################################
*/
unsigned short Hex_To_Bcd(unsigned short data)
{
    if(data%16 >= 10)
        data = data + 6;
    return data;
}

/*
**#############################################################################
** BCD To HEX  
**#############################################################################
*/
unsigned short Bcd_To_Hex(unsigned short data)
{
    if(data >= 0x10)
        data = data-(0x06*(data/0x10));            
    return data;
}




