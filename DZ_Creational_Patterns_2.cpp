#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

class SqlSelectQueryBuilder {
private:
    std::vector<std::string> columns;
    std::string table;
    std::vector<std::pair<std::string, std::string>> query_where;

public:
    SqlSelectQueryBuilder& AddColumns(const std::string& column) {
        columns.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& t) {
        table = t;
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& new_columns) {
        for (const auto& col : new_columns) {
            columns.push_back(col);
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& key, const std::string& value) {
        query_where.push_back(std::make_pair(key, value));
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& item : kv) {
            query_where.push_back(std::make_pair(item.first, item.second));
        }
        return *this;
    }

    std::string BuildQuery() {
        std::string query = "";

        if (columns.empty()) {
            query += "SELECT * ";
        }
        else {
            query += "SELECT ";
            for (size_t i = 0; i < columns.size(); ++i) {
                query += columns[i];
                if (i < columns.size() - 1) {
                    query += ", ";
                }
            }
            query += " ";
        }

        query += "FROM " + table;

        if (!query_where.empty()) {
            query += " WHERE ";
            for (size_t i = 0; i < query_where.size(); ++i) {
                query += query_where[i].first + "=" + query_where[i].second;

                if (i < query_where.size() - 1) {
                    query += " AND ";
                }
            }
        }

        query += ";";
        return query;
    }
};

int main() {
    SqlSelectQueryBuilder query_builder;

    query_builder.AddColumns(std::vector<std::string>{"name", "phone"});
    query_builder.AddFrom("students");

    std::map<std::string, std::string> conditions;
    conditions["id"] = "42";
    conditions["name"] = "John";

    query_builder.AddWhere(conditions);

    std::cout << query_builder.BuildQuery() << std::endl;

    return 0;
}
