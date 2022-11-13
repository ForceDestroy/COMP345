#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

class ILoggable
{
public:
    // Constructors
    virtual ~ILoggable();

    // Methods
    ILoggable& operator =(const ILoggable& o1);
    friend std::ostream& operator << (std::ostream& out, const ILoggable& logObserver);
    virtual std::string stringToLog() = 0;
};

class Observer
{
public:
    // Constructors
    virtual ~Observer();

    // Methods
    Observer& operator =(const Observer& o1);
    friend std::ostream& operator << (std::ostream& out, const Observer& logObserver);
    virtual void Update(ILoggable* loggable) = 0;
};

class Subject
{
public:
    // Data Members
    std::vector<Observer*> _observers;

    // Constructors
    virtual ~Subject();

    // Methods
    Subject& operator =(const Subject& s1);
    friend std::ostream& operator << (std::ostream& out, const Subject& subject);
    virtual void Attach(Observer* observer);
    virtual void Detach(Observer* observer);
    virtual void Notify(ILoggable* loggable);
};

class LogObserver : public Observer
{
public:
    // Constructors
    LogObserver();
    LogObserver(const LogObserver& o1);
    ~LogObserver();

    // Methods
    LogObserver& operator =(const LogObserver& o1);
    friend std::ostream& operator << (std::ostream& out, const LogObserver& logObserver);
    void Update(ILoggable* loggable) override;
};