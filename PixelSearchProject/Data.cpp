#include "Data.h"
#include <optional>

void Data::appendTable(Table t) {
	m_dataTables.push_back(t);
}



std::optional<Data::Table> Data::getTable() {
    if (m_dataTables.empty())
        return std::nullopt;
    return m_dataTables[m_selectedIndex];
}