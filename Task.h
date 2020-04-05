#ifndef SDDS_TASK_H
#define SDDS_TASK_H

#include <iostream>
#include <deque>
#include "CustomerOrder.h"

namespace sdds {

	class Task : public sdds::Item{

		std::deque<sdds::CustomerOrder> m_orders;
		Task *m_pNextTask = nullptr;
	public:
		Task(): Item(){}		
		Task(const std::string name);
		Task(const Task& other) = delete;
		Task& operator=(const Task& other) = delete;
		Task(const Task&& other) = delete;
		Task& operator=(const Task&& other) = delete;
		void runProcess(std::ostream& os);
		bool moveTask();
		void setNextTask(Task& task);
		bool getCompleted(CustomerOrder& order);
		void validate(std::ostream& os);
		Task& operator+=(CustomerOrder&& other);
		const std::string& getNextName();
	};


}
#endif
