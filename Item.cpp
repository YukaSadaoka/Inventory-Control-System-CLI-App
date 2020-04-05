#include <iostream>
#include <string>
#include <iomanip>
#include "Item.h"
#include "Utilities.h"

using namespace std;

namespace sdds {


	size_t Item::m_widthField = 0;  

	Item::Item() {
	
		m_name = "";
		m_description = "";
		m_serialNumber = 0u;
		m_quantity = 0u;
	}

	Item::Item(const std::string& str) {
		
		if (str != "") {
			Utilities util;
			bool more = true;
			size_t pos = 0;

			std::string temp;

			m_name = util.extractToken(str, pos, more);

			temp = util.extractToken(str, pos, more);
			m_serialNumber = stoi(temp);

			temp = util.extractToken(str, pos, more);
			m_quantity = stoi(temp);

			m_description = util.extractToken(str, pos, more);

			Item::m_widthField = m_name.length();
			util.setFieldWidth(Item::m_widthField);
		}
		else {
			*this = Item();
		}
 	}


	const std::string& Item::getName() const {
		return m_name;
	}
	const std::string& Item::getDesc() const {
		return m_description;
	}
	const unsigned int Item::getSerialNumber() {
		return m_serialNumber++;
	}
	
	const unsigned int Item::getQuantity() {
		return m_quantity;
	}

	void Item::updateQuantity() {
		
		if (m_quantity > 0) {
			m_quantity -= 1;
		}
	}

	void Item::display(std::ostream& os, bool full) const {
		
		if (!full) {

			os << left << setw(m_widthField) <<  m_name
				<< "[" << setfill('0') <<  right << setw(6) << m_serialNumber << "]" << setfill(' ') << endl;
		}
		else {
			os << left << setw(m_widthField) << m_name
				<< "[" << setfill('0') << right << setw(6) << m_serialNumber << "]" << setfill(' ')
				<< left << "Quantity: " << setw(Item::m_widthField)  << m_quantity
				<< "Description: "  << m_description << endl;
		}
	}
}