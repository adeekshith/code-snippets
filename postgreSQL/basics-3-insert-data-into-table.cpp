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
      sql = "INSERT INTO GPSLOG (ID,DATE,TIME,LATITUDE, LONGITUDE) "  \
      "VALUES (1, '2001-07-13', CURRENT_TIME, '40.097207', '-88.246090' ); " \
      "INSERT INTO GPSLOG (ID,DATE,TIME,LATITUDE, LONGITUDE) "  \
      "VALUES (2, '2014-06-15', CURRENT_TIME, '40.097798', '-88.250307' );";

      /* Create a transactional object. */
      work W(C);
      
      /* Execute SQL query */
      W.exec( sql );
      W.commit();
      cout << "Records created successfully" << endl;
      C.disconnect ();
   }catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}