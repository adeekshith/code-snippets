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
      sql = "CREATE TABLE GPSLOG("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "DATE            DATE    NOT NULL," \
      "TIME            TIME    NOT NULL," \
      "LATITUDE        varchar(12)    NOT NULL," \
      "LONGITUDE       varchar(12)    NOT NULL );";

      /* Create a transactional object. */
      work W(C);
      
      /* Execute SQL query */
      W.exec( sql );
      W.commit();
      cout << "Table created successfully" << endl;
      C.disconnect ();
   }catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}