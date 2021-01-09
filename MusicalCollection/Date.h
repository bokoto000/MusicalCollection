#ifndef __DATE_H
#define __DATE_H

class Date
{
private:
	int day, month, year;
	const static int c_MAX_VALID_YEAR = 9999;
	const static int c_MIN_VALID_YEAR = 0;
public: 
	Date();
	Date(int, int, int);
	static bool isLeap(int);
	static bool isDateValid(int, int, int);
	int getDay() const;
	int getMonth() const;
	int getYear() const;
};

#endif