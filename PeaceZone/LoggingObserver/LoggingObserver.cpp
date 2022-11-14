#include "LoggingObserver.h"

#pragma region ILoggable
// Destructor - ILoggable
ILoggable::~ILoggable() = default;

// Assignment Operator - ILoggable
ILoggable& ILoggable::operator=(const ILoggable& s1) {
    return *this;
}

// Stream Insertion Operator - ILoggable
std::ostream& operator<<(std::ostream& out, const ILoggable& subject) {
    out << "{ILOGGABLE CLASS}";
    return out;
}

#pragma endregion

#pragma region Observer

// Destructor - Observer
Observer::~Observer() = default;

// Assignment Operator - Observer
Observer& Observer::operator=(const Observer& s1) {
    return *this;
}

// Stream Insertion Operator - Observer
std::ostream& operator<<(std::ostream& out, const Observer& subject) {
    out << "{OBSERVER CLASS}";
    return out;
}


#pragma endregion

#pragma region Subject

// Destructor - Subject
Subject::~Subject() = default;

// Assignment Operator - Subject
Subject& Subject::operator=(const Subject& s1) {
    return *this;
}

// Stream Insertion Operator - Subject
std::ostream& operator<<(std::ostream& out, const Subject& subject) {
    out << "{SUBJECT CLASS}";
    return out;
}

// Method to attach an Observer to a Subject
void Subject::Attach(Observer* observer) {
    _observers.push_back(observer);
}

// Method to remove an Observer to a Subject
void Subject::Detach(Observer* observer) {
    auto itr = std::find(_observers.begin(), _observers.end(), observer);
    _observers.erase(itr);
}

// Method to notify all Observers of the Subject
void Subject::Notify(ILoggable* loggable) {
    for (Observer* o : _observers)
    {
        o->Update(loggable);
    }
}
#pragma endregion

#pragma region LogObserver
// Constructor - LogObserver
LogObserver::LogObserver() = default;

// Copy Constructor - LogObserver
LogObserver::LogObserver(const LogObserver& s1) = default;

// Destructor - LogObserver
LogObserver::~LogObserver() = default;

// Assignment Operator - LogObserver
LogObserver& LogObserver::operator=(const LogObserver& s1) {
    return *this;
}

// Stream Insertion Operator - LogObserver
std::ostream& operator<<(std::ostream& out, const LogObserver& subject) {
    out << "{LOGOBSEREVER CLASS}";
    return out;
}

// Method to log the ILoggable's log string
void LogObserver::Update(ILoggable* loggable) {
    // LogFile name
    std::string LogFile = "C:\\COMP345\\PeaceZone\\LoggingObserver\\gamelog.txt";
    std::ofstream output;

    // Open LogFile and Get LogString
    output.open(LogFile, std::ios_base::app);
    std::string log = loggable->stringToLog();

    // Write LogString to the LogFile
    output << log << std::endl;

    // CLose the LogFile
    output.close();
}
#pragma endregion