#include "DateRange.hpp"

// Very strict algorithm at the moment, must be formatted as "MM-DD MM-DD"
// Leading 0 not required for single digit months
geode::Result<> DateRange::parse(const std::string& str, size_t start)
{
    int sM, sD, eM, eD;
    char delimiter;
    std::istringstream istrs(str.substr(start));
    istrs >> sM >> delimiter >> sD >> std::ws >> eM >> delimiter >> eD;
    if (delimiter != '-')
        return geode::Err("Error parsing date format! Improper delimiter!");
    if (istrs.fail())
        return geode::Err("Stringstream failed!");

    m_Start =
        std::chrono::month_day(std::chrono::month(sM), std::chrono::day(sD));
    m_End =
        std::chrono::month_day(std::chrono::month(eM), std::chrono::day(eD));

    if (!m_Start.ok())
        return geode::Err("Start not OK! (Incorrect date format?)");
    if (!m_End.ok())
        return geode::Err("End not OK! (Incorrect date format?)");

    return geode::Ok();
}

bool DateRange::inRange(const std::chrono::year_month_day& currentDate) const
{
    auto year = currentDate.year();
    std::chrono::sys_days current(currentDate);
    std::chrono::sys_days start(year / m_Start);
    if (m_Start > m_End) year++; // Allow wrapping to the next year
    std::chrono::sys_days end(year / m_End);

    geode::log::error("Current Date: {}\nStart: {}\nEnd: {}", current, start, end);

    return current >= start && current <= end;
}