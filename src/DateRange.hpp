#include <Geode/Geode.hpp>

class DateRange
{
private:
    std::chrono::month_day m_Start;
    std::chrono::month_day m_End;
public:
    geode::Result<> parse(const std::string& str, size_t start = 0);
    bool inRange(const std::chrono::year_month_day& currentDate) const;
    inline const std::chrono::month_day& getStart() const { return m_Start; }
    inline const std::chrono::month_day& getEnd() const { return m_End; }
};