#include <iostream>
#include <deque>
#include <string>
#include "Task.h"
#include "CustomerOrder.h"
#include "Item.h"

namespace sdds {

	Task::Task(const std::string name):Item(name) {
		m_pNextTask = nullptr;
	}

	void Task::runProcess(std::ostream& os) {
		if (!m_orders.empty()) {
			if(!m_orders.back().getOrderFillState()) {
				while(!m_orders.back().getItemFillState(this->getName())) {
					m_orders.back().fillItem(*this, os);
				}
			}
		}
	}
	
	bool Task::moveTask() {

		if (!m_orders.empty()) {
			if(getName() != getNextName() && m_orders.back().getItemFillState(this->getName())){
				*m_pNextTask += std::move(m_orders.back());
				m_orders.pop_back();
			}
			else if((getName() == getNextName() && m_orders.back().getItemFillState(this->getName()))) {
				return false;
			}
		}
		return true;
	}
	
	void Task::setNextTask(Task& task) {
		m_pNextTask = &task;
	}

	bool Task::getCompleted(CustomerOrder& order) {
		if (order.getOrderFillState()) {
			order = std::move(m_orders.back());
			m_orders.pop_back();
			return true;
		}
	
		return false;
		
	}

	void Task::validate(std::ostream& os) {

		os << getName() << "-->";
		if (m_pNextTask->getName() != this->getName()) {
			os << m_pNextTask->getName() << std::endl;
		}
		else {
			os << "END OF LINE" << std::endl;
		}
	}
	Task& Task::operator+=(CustomerOrder&& other) {
		m_orders.push_front(std::move(other));
		return *this;
	}

	const std::string& Task::getNextName() {
		return m_pNextTask->getName();		
	}

}