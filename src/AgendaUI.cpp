#include <iostream>
#include <iomanip>
#include <cstdio>
#include "AgendaUI.hpp"
using namespace std;

static bool log = false;
static bool power = false;

AgendaUI::AgendaUI() {
    startAgenda();
}

void AgendaUI::OperationLoop(void) {
    if (!log && power) {
        cout << endl;
        cout << "-------------------------Agenda-------------------------" << endl;
        cout << "Action :" << endl;
        cout << left << setw(5) << "l" << "- log in Agenda by user name and password" << endl;
        cout << left << setw(5) << "r" << "- register an Agenda account" << endl;
        cout << left << setw(5) << "q" << "- quit Agenda" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Agenda : ~$ ";
        string&& operation = getOperation();
        while (!(operation == "l" || operation == "r" || operation == "q"))
            OperationLoop();
        executeOperation(operation);
    }
    if (log && power) {
        cout << endl;
        cout << "-------------------------Agenda-------------------------" << endl;
        cout << "Action :" << endl;
        cout << left << setw(5) << "o" << "- log out Agenda" << endl;
        cout << left << setw(5) << "dc" << "- delete Agenda account" << endl;
        cout << left << setw(5) << "lu" << "- list all Agenda user" << endl;
        cout << left << setw(5) << "cm" << "- create a meeting" << endl;
        cout << left << setw(5) << "la" << "- list all meetings" << endl;
        cout << left << setw(5) << "las" << "- list all sponsor meetings" << endl;
        cout << left << setw(5) << "lap" << "- list all participate meetings" << endl;
        cout << left << setw(5) << "qm" << "- query meeting by title" << endl;
        cout << left << setw(5) << "qt" << "- query meeting by time interval" << endl;
        cout << left << setw(5) << "dm" << "- delete meeting by title" << endl;
        cout << left << setw(5) << "da" << "- delete all meetings" << endl;
        cout << left << setw(5) << "cp" << "- change password" << endl;
        cout << left << setw(5) << "ce" << "- change email" << endl;
        cout << left << setw(5) << "cpn" << "- change phone number" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Agenda@ " << m_userName << " : ";
        string&& operation = getOperation();
        while (!(operation == "o" ||
                 operation == "dc" ||
                 operation == "lu" ||
                 operation == "cm" ||
                 operation == "la" ||
                 operation == "las" ||
                 operation == "lap" ||
                 operation == "qm" ||
                 operation == "qt" ||
                 operation == "dm" ||
                 operation == "cp" ||
                 operation == "ce" ||
                 operation == "cpn" ||
                 operation == "da"))
            OperationLoop();
        executeOperation(operation);
    }
}

void AgendaUI::startAgenda(void) {
    power = true;
    /*cout << endl;
    cout << "-------------------------Agenda-------------------------" << endl;
    cout << "Action :" << endl;
    cout << left << setw(5) << "l" << "- log in Agenda by user name and password" << endl;
    cout << left << setw(5) << "r" << "- register an Agenda account" << endl;
    cout << left << setw(5) << "q" << "- quit Agenda" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "Agenda : ~$ ";
    string operation;
    cin >> operation;
    while (!(operation == "l" || operation == "r" || operation == "q"))
        startAgenda();
    executeOperation(operation);*/
}

std::string AgendaUI::getOperation() {
    if (power) {
        string operation;
        cin >> operation;
        return operation;
    }
}

bool AgendaUI::executeOperation(std::string t_operation) {
    if (t_operation == "l") userLogIn();
    if (t_operation == "r") userRegister();
    if (t_operation == "q") quitAgenda();
    if (t_operation == "o") userLogOut();
    if (t_operation == "dc") deleteUser();
    if (t_operation == "lu") listAllUsers();
    if (t_operation == "cm") createMeeting();
    if (t_operation == "la") listAllMeetings();
    if (t_operation == "las") listAllSponsorMeetings();
    if (t_operation == "lap") listAllParticipateMeetings();
    if (t_operation == "qm") queryMeetingByTitle();
    if (t_operation == "qt") queryMeetingByTimeInterval();
    if (t_operation == "dm") deleteMeetingByTitle();
    if (t_operation == "da") deleteAllMeetings();
    if (t_operation == "cp") changePassword();
    if (t_operation == "ce") changeEmail();
    if (t_operation == "cpn") changePhoneNumber();
    OperationLoop();
}

void AgendaUI::userLogIn(void) {
    cout << "[log in] [user name] [password]" << endl;
    cout << "[log in] ";
    cin >> m_userName >> m_userPassword;
    if (m_agendaService.userLogIn(m_userName, m_userPassword)) {
        cout  << endl << "[log In] succeed!" << endl;
        log = true;
    } else {
        cout << endl << "[error] log in fail!" << endl;
        startAgenda();
    }
}

void AgendaUI::userRegister(void) {
    cout << "[register] [user name] [password] [email] [phone]" << endl;
    cout << "[register] ";
    string n_userName, n_password, n_email, n_phone;
    cin >> n_userName >> n_password >> n_email >> n_phone;
    if (m_agendaService.userRegister(n_userName, n_password, n_email, n_phone)) {
        cout << endl <<"[register] succeed!" << endl;
        m_userName = n_userName;
        m_userPassword = n_password;
        log = true;
    } else {
        cout << endl <<"[error] register fail!" << endl;
        startAgenda();
    }
}

void AgendaUI::quitAgenda(void) {
    power = false;
    log = false;
    m_agendaService.quitAgenda();
}

void AgendaUI::userLogOut(void) {
    log = false;
    m_userName.clear();
    m_userPassword.clear();
    startAgenda();
}

void AgendaUI::deleteUser(void) {
    m_agendaService.deleteAllMeetings(m_userName);
    m_agendaService.deleteUser(m_userName, m_userPassword);
    userLogOut();
}

void AgendaUI::listAllUsers(void) {
    list<User>&& allUser = m_agendaService.listAllUsers();
    cout << "[list all users]" << endl;
    cout  << left << setw(20) <<"name" <<
             left << setw(20) << "email" <<
             left << setw(15) << "phone" << endl;
    for (auto i = allUser.begin(); i != allUser.end(); i++)
        cout << left << setw(20) << i->getName() <<
                left << setw(20) << i->getEmail() <<
                left << setw(15) << i->getPhone() << endl;
}

void AgendaUI::createMeeting(void) {
    string n;
    int num = 0;
    bool flag = true;
    vector<string> participator;
    string temp, title, sdate, edate;
    do {
        cout << "[create meeting] [the number of participators]" << endl;
        cout << "[create meeting] ";
        cin >> n;
        for (int i = 0; i < n.size(); i++)
            if (!(n[i] >= '0' && n[i] <= '9')) {
                flag = false;
                break;
            }
    } while (!flag);
    for (int i = n.size() - 1; i >= 0; i--) num = num *10 + n[i] - '0';
    for (int i = 1; i <= num; i++) {
        cout << endl << "[creat meeting] [Please enter the participator " <<
            i << " ]" << endl;
        cout << "[create meeting] ";
        cin >> temp;
        participator.push_back(temp);
    }
    cout << "[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time((yyyy-mm-dd/hh:mm)]" << endl;
    cout << "[create meeting] ";
    cin >> title >> sdate >> edate;
    if (m_agendaService.createMeeting(m_userName, title, sdate, edate, participator))
        cout <<"[create meeting] succeed!" << endl;
    else
        cout << "[create meeting] error!" << endl;
}

void AgendaUI::listAllMeetings(void) {
    cout << "[list all meetings]" << endl;
    list<Meeting>&& meeting = m_agendaService.listAllMeetings(m_userName);
    printMeetings(meeting);
}

void AgendaUI::listAllSponsorMeetings(void) {
    cout << "[list all sponsor meetings]" << endl;
    list<Meeting>&& meeting = m_agendaService.listAllSponsorMeetings(m_userName);
    printMeetings(meeting);
}

void AgendaUI::listAllParticipateMeetings(void) {
    cout << "[list all participator meetings]" << endl;
    list<Meeting>&& meeting = m_agendaService.listAllParticipateMeetings(m_userName);
    printMeetings(meeting);
}

void AgendaUI::queryMeetingByTitle(void) {
    string title;
    cout << "[query meeting] [title]:" << endl;
    cout << "[query meeting] ";
    cin >> title;
    cout << endl;
    list<Meeting>&& meeting = m_agendaService.meetingQuery(m_userName, title);
    printMeetings(meeting);
}

void AgendaUI::queryMeetingByTimeInterval(void) {
    string stime, etime;
    cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
    cout << "[query meetings] ";
    cin >> stime >> etime;
    cout << endl << "[query meetings]" << endl;
    list<Meeting>&& meeting = m_agendaService.meetingQuery(m_userName, stime, etime);
    printMeetings(meeting);
}

void AgendaUI::deleteMeetingByTitle(void) {
    string title;
    cout << "[delete meeting] [title]" << endl;
    cout << "[delete meeting] ";
    cin >> title;
    if (m_agendaService.deleteMeeting(m_userName, title))
        cout << "[delete meeting by title] succeed!" << endl;
    else
        cout << "[error] delete meeting fail!" << endl;
}

void AgendaUI::deleteAllMeetings(void) {
    m_agendaService.deleteAllMeetings(m_userName);
    cout << "[delete all meetings] succeed!" << endl;
}

void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
    cout << left << setw(20) << "title" <<
            left << setw(20) << "sponsor" <<
            left << setw(20) << "start time" <<
            left << setw(20) << "end time" << 
            left << setw(20) << "participators" << endl;
    for (auto i = t_meetings.begin(); i != t_meetings.end(); i++) {
        cout << left << setw(20) << i->getTitle() <<
                left << setw(20) << i->getSponsor() <<
                left << setw(20) << Date::dateToString(i->getStartDate()) <<
                left << setw(20) << Date::dateToString(i->getEndDate());
        vector<string>&& participator = i->getParticipator();
        for (auto j = participator.begin(); j != participator.end(); j++) {
            if (j != participator.begin()) cout << ",";
            cout << *j;
        }
        cout << endl;
    }
}

void AgendaUI::changePassword(void) {
    string password1, password2;
    cout << "[change password] [new password] [confirm]" << endl;
    cout << "[change password] ";
    cin >> password1 >> password2;
    if (m_agendaService.changePassword(m_userName, password1, password2))
        cout << "[change password] succeed!" << endl;
    else
        cout << "[change password] error" << endl;
}

void AgendaUI::changeEmail(void) {
    string email1, email2;
    cout << "[change email] [new email] [confirm]" << endl;
    cout << "[change email] ";
    cin >> email1 >> email2;
    if (m_agendaService.changeEmail(m_userName, email1, email2))
        cout << "[change email] succeed!" << endl;
    else
        cout << "[change email] error" << endl;
}

void AgendaUI::changePhoneNumber(void) {
    string phone1, phone2;
    cout << "[change phone] [new phone] [confirm]" << endl;
    cout << "[change phone] ";
    cin >> phone1 >> phone2;
    if (m_agendaService.changePhoneNumber(m_userName, phone1, phone2))
        cout << "[change phone] succeed!" << endl;
    else
        cout << "[change phone] error" << endl;
}
