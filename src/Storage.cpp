#include <fstream>
#include <cstdio>
#include <iostream>
#include "Storage.hpp"
#include "Path.hpp"
#include "Date.hpp"
using namespace std;

std::shared_ptr<Storage> Storage::m_instance;

std::shared_ptr<Storage> Storage::getInstance(void) {
    if (nullptr == m_instance.get())
        m_instance.reset(new Storage);
    return m_instance;
}

Storage::~Storage() {
    writeToFile();
}

void Storage::createUser(const User & t_user) {
    m_userList.push_back(t_user);
    m_dirty = true;
}

std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const {
    std::list<User> temp;
    for (auto index = this->m_userList.begin(); index != m_userList.end(); index++)
        if (filter(*index))
            temp.push_back(*index);
    return temp;
}

int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher) {
    int num = 0;
    for (auto index = m_userList.begin(); index != m_userList.end(); index++)
        if (filter(*index)) {
            switcher(*index);
            num++;
            m_dirty = true;
        }
    return num;
}

int Storage::deleteUser(std::function<bool(const User &)> filter) {
    int num = 0;
    for (auto index = m_userList.begin(); index != m_userList.end();)
        if (filter(*index)) {
            index = m_userList.erase(index);
            num++;
            m_dirty = true;
        } else {
            index++;
        }
    return num;
}

void Storage::createMeeting(const Meeting & t_meeting) {
    m_meetingList.push_back(t_meeting);
    m_dirty = true;
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const {
    std::list<Meeting> temp;
    for (auto index = m_meetingList.begin(); index != m_meetingList.end(); index++)
        if (filter(*index))
            temp.push_back(*index);
    return temp;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher) {
    int num = 0;
    for (auto index = m_meetingList.begin(); index != m_meetingList.end(); index++)
        if (filter(*index)) {
            switcher(*index);
            m_dirty = true;
            num++;
        }
    return num;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
    int num = 0;
    for (auto index = m_meetingList.begin(); index != m_meetingList.end();)
        if (filter(*index)) {
            index = m_meetingList.erase(index);
            m_dirty = true;
            num++;
        } else {
            index++;
        }
    return num;
}

bool Storage::sync(void) {
    return writeToFile();
}

Storage::Storage() {
    m_dirty = false;
    readFromFile();
}

bool Storage::readFromFile(void) {
    ifstream meetings(Path::meetingPath);
    ifstream users(Path::userPath);
    if (!meetings.is_open() || !users.is_open()) return false;
    string str;
    while (getline(users, str)) {
        auto start = str.begin();
        auto end = ++start;
        while (*end != '"') end++;
        string tmp_name(start, end);
        start = end + 2;
        end = ++start;
        while (*end != '"') end++;
        string tmp_password(start, end);
        start = end + 2;
        end = ++start;
        while (*end != '"') end++;
        string tmp_email(start, end);
        start = end + 2;
        end = ++start;
        while (*end != '"') end++;
        string tmp_phone(start, end);
        m_userList.push_back(User(tmp_name, tmp_password, tmp_email, tmp_phone));
        str.clear();
    }
    vector<string> tmp_participators;
    while (getline(meetings, str)) {
        tmp_participators.clear();
        auto start = str.begin();
        auto end = ++start;
        while (*end != '"') end++;
        string tmp_sponsor(start, end);
        start = end + 2;
        end = ++start;
        while (*end != '"') end++;
        auto index = start;
        while (start < end) {
            while (*index != '&' && index < end) index++;
            tmp_participators.push_back(string(start, index));
            start = ++index;
        }
        start = end + 2;
        end = ++start;
        while (*end != '"') end++;
        string tmp_startDate(start, end);
        start = end + 2;
        end = ++start;
        while (*end != '"') end++;
        string tmp_endDate(start, end);
        start = end + 2;
        end = ++start;
        while (*end != '"') end++;
        string tmp_title(start, end);
        m_meetingList.push_back(Meeting(tmp_sponsor, tmp_participators,
                                        tmp_startDate, tmp_endDate, tmp_title));
        str.clear();
    }
    meetings.close();
    users.close();
    return true;
}

bool Storage::writeToFile(void) {
    if (!m_dirty) return true;
    ofstream meetings, users;
    meetings.open(Path::meetingPath);
    users.open(Path::userPath);
    char quotation = '"';
    for (auto i = m_userList.begin(); i != m_userList.end(); i++)
        users << quotation << i->getName() << quotation << "," <<
                 quotation << i->getPassword() << quotation << "," <<
                 quotation << i->getEmail() << quotation << "," <<
                 quotation << i->getPhone() << quotation << endl;
    for (auto i = m_meetingList.begin(); i != m_meetingList.end() ;i++) {
        meetings << quotation << i->getSponsor() << quotation << "," << quotation;
        vector<string> tmp_participators = i->getParticipator();
        for (int j = 0; j < tmp_participators.size(); j++) {
            if (j > 0) meetings << "&";
            meetings << tmp_participators[j];
        }
        meetings << quotation << ",";
        meetings << quotation << Date::dateToString(i->getStartDate()) << quotation << "," <<
                    quotation << Date::dateToString(i->getEndDate()) << quotation << "," <<
                    quotation << i->getTitle() << quotation << endl;
    }
    meetings.close();
    users.close();
    return true;
}
