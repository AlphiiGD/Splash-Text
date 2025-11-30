#include <Geode/Geode.hpp>

class DateRange
{
private:
    std::chrono::month_day m_Start;
    std::chrono::month_day m_End;
public:
    // *MUST* be formatted "MM-DD MM-DD" no leading 0 required.
    geode::Result<> parse(const std::string& str, size_t start = 0);
    // Returns true if supplied date is within this date range.
    bool inRange(const std::chrono::year_month_day& currentDate) const;
    // Returns starting date.
    inline const std::chrono::month_day& getStart() const { return m_Start; }
    // Returns ending date.
    inline const std::chrono::month_day& getEnd() const { return m_End; }
};