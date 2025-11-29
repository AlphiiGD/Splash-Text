#include "DateRange.hpp"

geode::Result<> DateRange::parse(const std::string& str, size_t start)
{
    std::istringstream istrs(str.substr(start));
    if (!(std::chrono::from_stream(istrs, "%m-%d", m_Start) &&
        istrs >> std::ws &&
        std::chrono::from_stream(istrs, "%m-%d", m_End)))
    {
        return geode::Err("Failed to parse DateRange");
    }

    if (istrs.fail()) return geode::Err("Stringstream failed!");
    if (!m_Start.ok()) return geode::Err("Start not OK!");
    if (!m_End.ok()) return geode::Err("End not OK!");
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