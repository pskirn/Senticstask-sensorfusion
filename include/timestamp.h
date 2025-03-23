#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <string>

class Timestamp {
private:
    int year, month, day, hour, minute, second, millisecond;


public:
    // Constructors
    Timestamp();
    Timestamp(const std::string& str);

    // Comparision operatos
    bool operator<(const Timestamp& other) const;
    bool operator==(const Timestamp& other) const;
    bool operator<=(const Timestamp& other) const;

    // Convert to string
    std::string toString() const;

};

#endif // TIMESTAMP_H



