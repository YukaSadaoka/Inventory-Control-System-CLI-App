#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include "LineManager.h"
#include "CustomerOrder.h"
#include "Task.h"

namespace sdds {

	LineManager::LineManager(const std::string& name, std::vector<Task*>& task, std::vector<CustomerOrder>& order) {

		
		std::ifstream file(name);	

		if (!file.is_open()) {
			std::cout << "Filename is wrong!" << std::endl;
		}

		while (!file.eof()) {
			
			//Initialize nextTask
				std::string line;
				std::getline(file, line);

				std::string nowTask;
				std::string nextTask;
				auto found = line.find('|');
				if (found != std::string::npos) {
					nowTask = line.substr(0, found);
					nextTask = line.substr(found + 1, line.length() - 1);	
				}
				else {
					nowTask = line.substr(0, line.length());
					nextTask = "1";
				}

				for (auto i = 0u; i < task.size(); i++) {
					if (task[i]->getName() == nowTask && nextTask != "1") {
						for (auto j = 0u; j < task.size(); j++) {
							if (task[j]->getName() == nextTask) {
								task[i]->setNextTask(*task[j]);
								j = task.size();
							}
						}
					}
					else if(task[i]->getName() == nowTask && nextTask == "1") {
						task[i]->setNextTask(*task[i]);
					}
				}
				
		}
		
		//copy task 
		for (auto i = 0u; i < task.size(); i++) {
	
			AssemblyLine.push_back(new Task());
			AssemblyLine.back() = task[i];	
		}

		//move CustomeOrder
		for (auto i = 0u; i < order.size(); i++) {
			this->ToBeFilled.push_front(std::move(order[i]));
		}
		
		m_cntCustomerOr = ToBeFilled.size();
	}
	
	bool LineManager::run(std::ostream& os) {
		
		unsigned int start = 0u;
		
		std::string temp;
			
		//Item name deque
		for (auto i = 0u; i < AssemblyLine.size(); i++) {
			std::string next = AssemblyLine[i]->getNextName();
			if (next != AssemblyLine[i]->getName()) {
				temp += next + '|';
			}
		}
		for (auto i = 0u; i < AssemblyLine.size(); i++) {
			if (temp.find(AssemblyLine[i]->getName()) == std::string::npos) {
				start = i;
			}
		}
	
		if (!ToBeFilled.empty()) {
			*AssemblyLine[start] += std::move(ToBeFilled.back());
			ToBeFilled.pop_back();
		}


		for (auto i = 0u; i < AssemblyLine.size(); i++) {
			AssemblyLine[i]->runProcess(os);
		}

		for (auto i = 0u; i < AssemblyLine.size(); i++) {
			if (!AssemblyLine[i]->moveTask()) {
				CustomerOrder temp;
				AssemblyLine[i]->getCompleted(temp);
				Completed.push_back(std::move(temp));
			}
		}

		if (Completed.size() == m_cntCustomerOr) {
			return true;
		}
		else {
			return false;
		}
	}
	
	void LineManager::displayCompleted(std::ostream& os) const {
	
		for (auto i = 0u; i < Completed.size(); i++) {
			Completed[i].display(os);
		}
	}

	void LineManager::validateTasks() const {
		for (auto i = 0u; i < AssemblyLine.size(); i++) {
			AssemblyLine[i]->validate(std::cout);
		}
	}
}