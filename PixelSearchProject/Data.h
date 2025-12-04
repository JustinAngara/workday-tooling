#pragma once
#include <string>
#include <vector>
#include <optional>
class Data {
public:
	// will contain all entrys
	struct Table {
		std::string title;
		std::string company;
		std::string description;
	};

	void appendTable(Table t);
	std::optional<Table> getTable();
private:
	int m_selectedIndex{ 0 };
	std::vector<Table> m_dataTables;
	
};

