#include <stdio.h>
#include "Date.hpp"

Date::Date() {
    m_year = 0;
    m_month = 0;
    m_day = 0;
    m_hour = 0;
    m_minute = 0;
}

Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
    m_year = t_year;
    m_month = t_month;
    m_day = t_day;
    m_hour = t_hour;
    m_minute = t_minute;
}

Date::Date(std::string dateString) {
    bool flag = true;
    int num[] = {0, 1, 2, 3, 5, 6, 8, 9, 11, 12, 14, 15};
    if (dateString.size() != 16) flag = false;
    if (flag) {
        for (int i = 0; i < 12; i++)
            if (dateString[num[i]] < '0' || dateString[num[i]] > '9')
                flag = false;
        if (dateString[4] != '-' || dateString[7] != '-' ||
            dateString[10] != '/' || dateString[13] != ':')
            flag = false;
    }
    if (flag == false) {
        m_year = 0;
        m_month = 0;
        m_day = 0;
        m_hour = 0;
        m_minute = 0;
    } else {
        m_year = (dateString[0] - '0') * 1000 + (dateString[1] - '0') * 100 +
                (dateString[2] - '0') * 10 + dateString[3] - '0';
        m_month = (dateString[5] - '0') * 10 + dateString[6] - '0';
        m_day = (dateString[8] - '0') * 10 + dateString[9] - '0';
        m_hour = (dateString[11] - '0') * 10 + dateString[12] - '0';
        m_minute = (dateString[14] - '0') * 10 + dateString[15] - '0';
    }
}

int Date::getYear(void) const {
    return m_year;
}

void Date::setYear(const int t_year) {
    m_year = t_year;
}

int Date::getMonth(void) const {
    return m_month;
}

void Date::setMonth(const int t_month) {
    m_month = t_month;
}

int Date::getDay(void) const {
    return m_day;
}

void Date::setDay(const int t_day) {
    m_day = t_day;
}

int Date::getHour(void) const {
    return m_hour;
}

void Date::setHour(const int t_hour) {
    m_hour = t_hour;
}

int Date::getMinute(void) const {
    return m_minute;
}

void Date::setMinute(const int t_minute) {
    m_minute = t_minute;
}

bool Date::isValid(const Date t_date) {
    if (t_date.m_year < 1000 || t_date.m_year > 9999) return false;
    if (t_date.m_month < 1 || t_date.m_month > 12) return false;
    if (t_date.m_day < 1) return false;
    if (t_date.m_hour < 0 || t_date.m_hour > 23) return false;
    if (t_date.m_minute < 0 || t_date.m_minute > 59) return false;
    if ((t_date.m_month == 1 || t_date.m_month == 3 || t_date.m_month == 5 || t_date.m_month == 7 ||
        t_date.m_month == 8 || t_date.m_month == 10 || t_date.m_month == 12) && t_date.m_day > 31)
        return false;
    if ((t_date.m_month == 4 || t_date.m_month == 6 || t_date.m_month == 9 || t_date.m_month == 11) &&
        t_date.m_day > 30) return false;
    if (t_date.m_month == 2) {
        if (t_date.m_year % 400 == 0 || (t_date.m_year % 100 != 0 && t_date.m_year % 4 == 0)) {
            if (t_date.m_day > 29) return false;
        } else {
            if (t_date.m_day > 28) return false;
        }
    }
    
    return true;
}

Date Date::stringToDate(const std::string t_dateString) {
    Date temp(t_dateString);
    return temp;
}

std::string Date::dateToString(Date t_date) {
    if (!isValid(t_date)) return std::string("0000-00-00/00:00");
    char temp[10];
    std::string dateString;
    snprintf(temp, sizeof(temp), "%d", t_date.getYear());
    dateString += temp;
    dateString += '-';
    if (t_date.getMonth() < 10) dateString += '0';
    snprintf(temp, sizeof(temp), "%d", t_date.getMonth());
    dateString += temp;
    dateString += '-';
    if (t_date.getDay() < 10) dateString += '0';
    snprintf(temp, sizeof(temp), "%d", t_date.getDay());
    dateString += temp;
    dateString += '/';
    if (t_date.getHour() < 10) dateString += '0';
    snprintf(temp, sizeof(temp), "%d", t_date.getHour());
    dateString += temp;
    dateString += ':';
    if (t_date.getMinute() < 10) dateString += '0';
    snprintf(temp, sizeof(temp), "%d", t_date.getMinute());
    dateString += temp;
    return dateString;
}

Date & Date::operator=(const Date &t_date) {
    setYear(t_date.getYear());
    setMonth(t_date.getMonth());
    setDay(t_date.getDay());
    setHour(t_date.getHour());
    setMinute(t_date.getMinute());
    return *this;
}

bool Date::operator==(const Date &t_date) const {
    if (getYear() != t_date.getYear()) return false;
    if (getMonth() != t_date.getMonth()) return false;
    if (getDay() != t_date.getDay()) return false;
    if (getHour() != t_date.getHour()) return false;
    if (getMinute() != t_date.getMinute()) return false;
    return true;
}

bool Date::operator>(const Date &t_date) const {
    if (getYear() > t_date.getYear()) return true;
  	if (getYear() < t_date.getYear()) return false;
    if (getMonth() > t_date.getMonth()) return true;
  	if (getMonth() < t_date.getMonth()) return false;
    if (getDay() > t_date.getDay()) return true;
  	if (getDay() < t_date.getDay()) return false;
    if (getHour() > t_date.getHour()) return true;
  	if (getHour() < t_date.getHour()) return false;
    if (getMinute() > t_date.getMinute()) return true;
    return false;
}

bool Date::operator<(const Date &t_date) const {
    if (!(*this > t_date) && !(*this == t_date)) return true;
    return false;
}

bool Date::operator>=(const Date &t_date) const {
    if ((*this > t_date) || (*this == t_date)) return true;
    return false;
}

bool Date::operator<=(const Date &t_date) const {
    if ((*this < t_date) || (*this == t_date)) return true;
    return false;
}
