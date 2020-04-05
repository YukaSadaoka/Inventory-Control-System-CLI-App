#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <string>

namespace sdds {

	class Utilities {

		size_t m_widthField = 1;
		static char m_delimiter;

	public:
		Utilities(): m_widthField(1){}
		void setFieldWidth(size_t);
		size_t getFieldWidth() const;
		const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		const char getDelimiter() const;
		static void setDelimiter(const char);
	};
}

#endif