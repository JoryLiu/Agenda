#include <set>
#include "AgendaService.hpp"
using namespace std;

AgendaService::AgendaService() {
    startAgenda();
}

AgendaService::~AgendaService() {
    quitAgenda();
}

bool AgendaService::userLogIn(const std::string userName,
                              const std::string password) {
    function<bool(const User & t_user)> func = [](const User & t_user) -> bool {
        return true;
    };
    list<User>&& userList = m_storage->queryUser(func);
    for (auto i = userList.begin(); i != userList.end(); i++)
        if (i->getName() == userName && i->getPassword() == password)
            return true;
    return false;
}

bool AgendaService::userRegister(const std::string userName,
                                 const std::string password,
                                 const std::string email,
                                 const std::string phone) {
    function<bool(const User &)> func = [=](const User & t_user) -> bool {
        return true;
    };
    list<User>&& userList = m_storage->queryUser(func);
    for (auto i = userList.begin(); i != userList.end(); i++)
        if (i->getName() == userName) return false;
    User newUser(userName, password, email, phone);
    m_storage->createUser(newUser);
    return true;
}

bool AgendaService::deleteUser(const std::string userName,
                                const std::string password) {
    function<bool(const User &)> func = [=](const User & t_user) -> bool {
        if (t_user.getName() == userName && t_user.getPassword() == password)
            return true;
        return false;
    };
    int num = m_storage->deleteUser(func);
  	function<bool(const Meeting &)> func2 = [=](const Meeting & t_meeting) -> bool {
        		return (t_meeting.getSponsor() == userName || t_meeting.isParticipator(userName));
    };
    m_storage->deleteMeeting(func2);
  	return num;
}

std::list<User> AgendaService::listAllUsers(void) const {
    function<bool(const User &)> func = [=](const User & t_user) -> bool {
        return true;
    };
    list<User>&& userList = m_storage->queryUser(func);
    return userList;
}

bool AgendaService::createMeeting(const std::string userName,
                    const std::string title, const std::string startDate,
                    const std::string endDate,
                    const std::vector<std::string> participator) {
    if (participator.size() < 1) return false;
    Date start(startDate);
    Date end(endDate);
    if (!Date::isValid(start) || !Date::isValid(end))
        return false;
    if (start >= end) return false;
    set<string> allPeople;
    allPeople.insert(userName);
    for (auto i = participator.begin(); i != participator.end(); i++)
        allPeople.insert(*i);
    if (allPeople.size() != participator.size() + 1) return false;
    list<User>&& allUser = listAllUsers();
    bool find;
    for (auto i = allPeople.begin(); i != allPeople.end(); i++) {
        find = false;
        for (auto j = allUser.begin(); j != allUser.end(); j++)
            if (j->getName() == *i) {
                find = true;
                break;
            }
        if (!find) return false;
    }
    function<bool(const Meeting &)> func = [=](const Meeting & t_meeting) -> bool {
        if (title == t_meeting.getTitle()) return true;
        return false;
    };
    list<Meeting>&& meetingList = m_storage->queryMeeting(func);
    if (meetingList.size() > 0) return false;
    for (auto i = allPeople.begin(); i != allPeople.end(); i++) {
        meetingList = listAllMeetings(*i);
        for (auto j = meetingList.begin(); j != meetingList.end(); j++) {
            if (!(end <= j->getStartDate() || start >= j->getEndDate()))
              	return false;
        }
    }
    Meeting newMeeting(userName, participator, start, end, title);
    m_storage->createMeeting(newMeeting);
    return true;
}

std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string title) const {
    function<bool(const Meeting &)> func = [=](const Meeting & t_meeting) -> bool {
        if (title == t_meeting.getTitle()) {
            if (userName == t_meeting.getSponsor() || t_meeting.isParticipator(userName))
                return true;
        }
        return false;
    };
    list<Meeting>&& meetingList = m_storage->queryMeeting(func);
    return meetingList;
}

std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string startDate,
                                    const std::string endDate) const {
    list<Meeting> empty;
    Date start(startDate);
    Date end(endDate);
    if (!Date::isValid(start) || !Date::isValid(end)) return empty;
    if (start > end) return empty;
    function<bool(const Meeting &)> func = [=](const Meeting & t_meeting) -> bool {
        if (userName == t_meeting.getSponsor() || t_meeting.isParticipator(userName)) {
            if (!(start > t_meeting.getEndDate() || end < t_meeting.getStartDate()))
                return true;
            else
                return false;
        }
        return false;
    };
    list<Meeting>&& meetingList = m_storage->queryMeeting(func);
    return meetingList;
}

list<Meeting> AgendaService::listAllMeetings(const string userName) const {
    function<bool(const Meeting &)> func = [=](const Meeting & t_meeting) -> bool {
        return (userName == t_meeting.getSponsor() || t_meeting.isParticipator(userName));
    };
    list<Meeting>&& meetingList = m_storage->queryMeeting(func);
    return meetingList;
}

list<Meeting> AgendaService::listAllSponsorMeetings(const string userName) const {
    function<bool(const Meeting &)> func = [=](const Meeting & t_meeting) -> bool {
        return (userName == t_meeting.getSponsor());
    };
    list<Meeting>&& meetingList = m_storage->queryMeeting(func);
    return meetingList;
}

list<Meeting> AgendaService::listAllParticipateMeetings(const string userName) const {
    function<bool(const Meeting &)> func = [=](const Meeting & t_meeting) -> bool {
        return (t_meeting.isParticipator(userName));
    };
    list<Meeting>&& meetingList = m_storage->queryMeeting(func);
    return meetingList;
}

bool AgendaService::deleteMeeting(const std::string userName,
                                    const std::string title) {
    function<bool(const Meeting &)> func = [=](const Meeting & t_meeting) -> bool {
        return (t_meeting.getSponsor() == userName && title == t_meeting.getTitle());
    };
    return m_storage->deleteMeeting(func);
}

bool AgendaService::deleteAllMeetings(const std::string userName) {
    function<bool(const Meeting &)> func = [=](const Meeting & t_meeting) -> bool {
        return (t_meeting.getSponsor() == userName);
    };
    return m_storage->deleteMeeting(func);
}

void AgendaService::startAgenda(void) {
    m_storage = m_storage->getInstance();
}

void AgendaService::quitAgenda(void) {
    m_storage.reset();
}

bool AgendaService::changePassword(const std::string userName, const std::string password1, const std::string password2) {
    if (password1 != password2) return false;
    function<bool (const User &)> func = [=](const User & t_user) -> bool {
        if (t_user.getName() == userName) return true;
        return false;
    };
    function<void (User &)> chg = [=](User & t_user) {
        t_user.setPassword(password1);
    };
    return m_storage->updateUser(func, chg);
}

bool AgendaService::changeEmail(const std::string userName, const std::string email1, const std::string email2) {
    if (email1 != email2) return false;
    function<bool (const User &)> func = [=](const User & t_user) -> bool {
        if (t_user.getName() == userName) return true;
        return false;
    };
    function<void (User &)> chg = [=](User & t_user) {
        t_user.setEmail(email1);
    };
    return m_storage->updateUser(func, chg);
}

bool AgendaService::changePhoneNumber(const std::string userName, const std::string phone1, const std::string phone2) {
    if (phone1 != phone2) return false;
    function<bool (const User &)> func = [=](const User & t_user) -> bool {
        if (t_user.getName() == userName) return true;
        return false;
    };
    function<void (User &)> chg = [=](User & t_user) {
        t_user.setPhone(phone1);
    };
    return m_storage->updateUser(func, chg);
}
