#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "Task.h"
#include "CustomerOrder.h"

namespace sdds {

	class LineManager {
		std::vector<Task*> AssemblyLine;
		std::deque<CustomerOrder> ToBeFilled;
		std::deque<CustomerOrder> Completed;
		unsigned int m_cntCustomerOr = 0u;
		unsigned int m_start = 0u;

	public:
		LineManager() {};
		LineManager(const std::string& name, std::vector<Task*>& task, std::vector<CustomerOrder>& order);
		bool run(std::ostream& os);
		void displayCompleted(std::ostream& os) const;
		void validateTasks() const;

	};
}
#endif