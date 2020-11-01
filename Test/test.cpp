include <iostream>
#include "../Source/dao/mysql/MySQLBaseDao.h"

using namespace std;
int main()
{
	MySQLBaseDao dao("127.0.0.1", 3306, "dev_leaf", "leaf", 10);
	PtrResultSet result = dao.execueteQuery("test_db", "SELECT * FROM test_table");
	while (result->next())
	{
		cout << result->getInt(1) << "\t" << result->getString(2) << endl;
	}

	return 0;
}