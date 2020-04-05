#include <iostream>
#include <string>
#include "Utilities.h"

using namespace std;

namespace sdds {

	char Utilities::m_delimiter = ' ';
	
	void Utilities::setFieldWidth(size_t w) {
		m_widthField = w;
	}
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}
	const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {

		std::string temp;
		size_t end;

		try {
			
			if (next_pos < str.length()) {
				end = str.find(Utilities::m_delimiter, next_pos);
				if (next_pos == end) {
					more = false;
					temp = "";
					throw "Two delimiter";

				}
				else if (end == std::string::npos) {
					temp = str.substr(next_pos, str.length() - next_pos);
					next_pos = str.length() + 1;
				}
				else {
					temp = str.substr(next_pos, end - next_pos);
					next_pos = end + 1;
				}
				more = true;


				if (this->getFieldWidth() < temp.length()) {
					this->setFieldWidth(temp.length());
				}
				
			}
			else {
				temp = "";
				more = false;
			}

		}catch(const char* msg){
			cout << msg << endl;
		}
		return temp;

	}
	
	const char Utilities::getDelimiter() const{
		return m_delimiter;
	}

	void Utilities::setDelimiter(const char delimiter) {
		m_delimiter = delimiter;
	}
}