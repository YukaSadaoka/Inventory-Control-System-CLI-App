#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <iostream>
#include <string>
#include "Item.h"


namespace sdds {

	struct ItemInfo
	{
		std::string m_itemName;
		unsigned int m_serialNumber = 0;
		bool m_fillState = false;

		ItemInfo(std::string src) : m_itemName(src) {};
	};

	class CustomerOrder {
		std::string m_name;
		std::string m_product;
		unsigned int m_cntItem;
		sdds::ItemInfo** m_listItem = nullptr;
		static size_t m_widthField;

	public:
		CustomerOrder();
		CustomerOrder(const std::string str);
		~CustomerOrder();
		CustomerOrder(const CustomerOrder& other);
		CustomerOrder& operator=(const CustomerOrder& other) = delete;
		CustomerOrder(CustomerOrder&& other) noexcept;
		CustomerOrder& operator=(CustomerOrder&& other) noexcept;
		bool getItemFillState(std::string) const;
		bool getOrderFillState() const;
		void fillItem(Item& item, std::ostream&);
		void display(std::ostream&) const;

	   	
	};

	

}
#endif