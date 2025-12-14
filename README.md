# PersonalFinanceManager

Simple program on c++, that register user and save all transactions that user did. The project connect to PostgreSQL using Docker.  
Here, in project i use:
 - connection to PostgreSQL (libpqxx)
 - use Docker
 - "vector" lib
 - map
 - pointers in function
 - etc.

# To run the project you need:
 - Visual Studio 2022 or greater
 - git
 - docker
 - PostgreSQL

# How to run
To run the project follow steps:
1. git clone project in project folder (/PATH/)
2. download vcpkg* in /PATH/ of the project and download libpqxx* (guide: https://github.com/qwinkki/DockerPostgreSQLAuth)
3. USE 20+ VERSION OF COMPILING IN MAIN OPTIONS OF THE PROJECT !!!
4. start docker (also you can change username and password in Database.cpp (variable conn) and in .yml file)
5. go to /PATH/ in cmd and write 'docker-compose up --build' or 'docker-compose up -d' (**)
> <img width="963" height="101" alt="image" src="https://github.com/user-attachments/assets/66e22f86-4ff0-4813-a653-752e349a7966" />

7. start the project

# Exit
 - to end the project, write in cmd /PATH/ 'docker-compose down' or to delete all 'docker-compose down -v'
> <img width="960" height="101" alt="image" src="https://github.com/user-attachments/assets/ab5e2470-b859-4062-a28e-c8700ea8edef" />


# Problems that could be
 ** if after 5 step you cant connect to database and project say that database 'PersonalFinanceManager dont exist':
   1. start cmd as administrator and write commands:
   2. netstat -aon | findstr :5432
   3. taskkill /PID (id of port) /F
> <img width="634" height="107" alt="image" src="https://github.com/user-attachments/assets/c7d7c2d2-ead3-462a-9cda-cfe85384f4fc" />


#
> - *libpqxx - .h, .lib, .hxx and so on files to connect PostgreSQL in c++ language
> - *vcpkg - to download vcpkg use git: git clone https://github.com/microsoft/vcpkg.git
#
(Small project for qwinki resume)
