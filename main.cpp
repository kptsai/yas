/* 
 * File:   main.cpp
 * Author: goldlcup 
 *
 * Created on July 27, 2015, 10:46 PM
 */
 
  
#include <iostream>
#include "mongo/client/dbclient.h"

using namespace mongo; 
using namespace std; 

class yasdb{
 public:
  int connect(const char* address, const char* user, const char* pwd){
    BSONObjBuilder b;
    b.append("user",user);
    b.append("pwd",pwd);
    b.append("db","yas");
    b.append("mechanism", "SCRAM-SHA-1");
    BSONObj p = b.obj();
    cout <<address<< user << pwd << endl;
    client::Options autoTimeoutOpts = client::Options();
    autoTimeoutOpts.setAutoShutdownGracePeriodMillis(250);

    mongo::client::GlobalInstance instance(autoTimeoutOpts);
    if (!instance.initialized()) {
        std::cout << "failed to initialize the client driver: " << instance.status() << std::endl;
        return EXIT_FAILURE;
    }
    std::string errmsg;
    conn.connect(address, errmsg);
        std::cout << "initialize the client driver: " << instance.status() << std::endl;
    conn.auth(p);
    return 0;
  }
  mongo::DBClientConnection conn;
 private:
  
  
};
  
int main(int argc, char** argv) {
    
    
    yasdb yas;
    
    BSONObjBuilder b;
    b.append("user","yasadmin");
    b.append("pwd","y@sword");
    b.append("db","yas");
    b.append("mechanism", "SCRAM-SHA-1");
    BSONObj p = b.obj();
    /*
     std::string errmsg;
     BSONObjBuilder b; 
     b.append("user", "yasadmin"); 
     b.append("pwd", "y@sword");
     b.append("db", "yas");
     b.append("mechanism", "SCRAM-SHA-1");  
     BSONObj p = b.obj();
     
     mongo::client::initialize();
     mongo::DBClientConnection conn; 
 
     try {
          conn.connect("localhost"); 
          conn.auth(p);
          cout << "connected ok" << endl;
     } catch( DBException &e ) {
          cout << "caught: " << e.what() << endl; 
     }
*/
    cout << "count:" << yas.conn.count("yas.users") << std::endl;

    auto_ptr<DBClientCursor> cursor = yas.conn.query("yas.users", BSONObj());
    while (cursor->more())
        cout << cursor->next().toString() << endl;
    return 0;
}

