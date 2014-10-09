#include <iostream>
#include <pqxx/pqxx> 
#include <string>

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[])
{
   string sql;
   
   try{
      connection C("dbname=testdb user=postgres password=postgres \
      hostaddr=127.0.0.1 port=5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }
      /* Create SQL statement */
      sql = "SELECT * from GPSLOG";

      /* Create a non-transactional object. */
      nontransaction N(C);
      
      /* Execute SQL query */
      result R( N.exec( sql ));
      
      /* List down all the records */
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << "ID = " << c[0].as<int>() << endl;
         cout << "Date = " << c[1].as<string>() << endl;
         cout << "Time = " << c[2].as<string>() << endl;
         cout << "Latitude = " << c[3].as<string>() << endl;
         cout << "Longitude = " << c[4].as<string>() << endl;
      }
      cout << "Operation done successfully" << endl;
      C.disconnect ();
   }catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}