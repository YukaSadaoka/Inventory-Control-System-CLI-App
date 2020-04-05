#include <iostream>
#include <string>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
#include "Item.h"

namespace sdds {
	
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() {

		m_name = " ";
		m_product = " ";
		m_cntItem = 0u;
		m_listItem = nullptr;
	}


	CustomerOrder::CustomerOrder(const std::string str) {

		Utilities util;
		size_t pos = 0u;
		bool more = true;

		m_name = util.extractToken(str, pos, more);
		m_product = util.extractToken(str, pos, more);

		size_t next = pos;
		unsigned int count = 0u;
		std::string dummy;
		

		do {
			dummy = util.extractToken(str, next, more);
			if (more) {
				count++;
			}
		} while (more);

		m_cntItem = count;
		this->m_listItem = new sdds::ItemInfo*[count];

		for (auto i = 0u; i < count; i++) {
			this->m_listItem[i] = new sdds::ItemInfo(util.extractToken(str, pos, more));
		}
		CustomerOrder::m_widthField = util.getFieldWidth();
		/*if (CustomerOrder::m_widthField < m_name.length()) {
			CustomerOrder::m_widthField = m_name.length();
		}*/
	}

	CustomerOrder::~CustomerOrder() {
		delete [] m_listItem;
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& other) {
		throw "Error";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
		*this = std::move(other);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {

		if (this != &other) {

			delete [] this->m_listItem;

			this->m_name = other.m_name;
			this->m_product = other.m_product;
			this->m_cntItem = other.m_cntItem;
			this->m_listItem = other.m_listItem;

			other.m_name = "";
			other.m_product = "";
			other.m_cntItem = 0u;
			other.m_listItem = nullptr;
		}
		return *this;
	}

	bool CustomerOrder::getItemFillState(std::string str) const {
		
		auto count = 0u;
		for (auto i = 0u; i < this->m_cntItem; i++) {
			if (this->m_listItem[i]->m_itemName == str) {
				if(!this->m_listItem[i]->m_fillState)
					count++;			
			}
		}
		if (count > 0)
			return false;
		else
			return true;
	}

	bool CustomerOrder::getOrderFillState() const {

		for (auto i = 0u; i < this->m_cntItem; i++) {
			if (!this->m_listItem[i]->m_fillState) {
				return false;
			}
		}
		return true;

	}

	void CustomerOrder::fillItem(Item& item, std::ostream& os) {
		
		bool found = false;
		unsigned int pos;
		for (auto i = 0u; i < this->m_cntItem; i++) {
			if (this->m_listItem[i]->m_itemName == item.getName() && !this->m_listItem[i]->m_fillState) {
				found = true;
				pos = i;
				i = m_cntItem;
			}
		}

		if (found) {
			if (item.getQuantity()) {
				item.updateQuantity();
				this->m_listItem[pos]->m_serialNumber = item.getSerialNumber();
				this->m_listItem[pos]->m_fillState = true;

				std::cout << "Filled " << this->m_name << ", " << this->m_product
					<< "[" << this->m_listItem[pos]->m_itemName << "]" << std::endl;
			}
			else {
				std::cout << "Unable to fill " << this->m_name << ", " << this->m_product
					<< "[" << this->m_listItem[pos]->m_itemName << "]" << std::endl;

			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const {
		//std::setw(CustomerOrder::m_widthField)
		os << this->m_name << " - " << this->m_product << std::endl;

		for (auto i = 0u; i < this->m_cntItem; i++) {

			os << std::setfill('0') << std::right << "[" << std::setw(6) << this->m_listItem[i]->m_serialNumber
				<< "]" << std::setfill(' ') << std::left << std::setw(CustomerOrder::m_widthField) << this->m_listItem[i]->m_itemName
				<< "-";

			if (this->m_listItem[i]->m_fillState) {
				os << "FILLED " << std::endl;
			}
			else {
				os << "MISSING " << std::endl;
			}
		}

	}


}