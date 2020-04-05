#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include <iostream>
#include <string>

namespace sdds {

	class Item {
		std::string m_name;
		std::string m_description;
		unsigned int m_serialNumber;
		unsigned int m_quantity;
		static size_t m_widthField;

	public:
		Item();
		Item(const std::string& str);
		const std::string& getName() const;
		const std::string& getDesc() const;
		const unsigned int getSerialNumber();
		const unsigned int getQuantity();
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
		
	};

}

#endif