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
#ifndef _DATE_H_
#define _DATE_H_


/*
**#############################################################################
** Variable 
**#############################################################################
*/
typedef struct 
{
	unsigned char second;
	unsigned char minute;
	unsigned char hour;
	unsigned char day;
	unsigned char week;
	unsigned char month;
	unsigned short year;
}Date;

/*
**#############################################################################
** Functions
**#############################################################################
*/
void Date_Set(Date *setdate);
Date *Date_Get(void);
void Date_Second_Update(void);
void Date_Minute_Update(void);
void Date_Hour_Update(void);
void Date_Day_Update(void);
void Date_Week_Update(void);
void Date_Month_Update(void);
void Date_Year_Update(void);
unsigned int Hex_To_Bcd(unsigned int data);
#endif

