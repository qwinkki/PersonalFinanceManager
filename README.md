# PersonalFinanceManager

Simple program on c++, that register user and save all transactions that user did. The project connect to PostgreSQL using Docker.
Here, in project i use:
 - connection to PostgreSQL (libpqxx)
 - use Docker
 - "vector" lib
 - map
 - pointers in function
 - etc.

To run the project you need:
 - Visual Studio 2022 or greater
 - git
 - pgAdmin 4
 - PostgreSQL

# How to run
To run the project follow steps:
1. git clone project in project folder (/PATH/)
2. download vcpkg* in /PATH/ of the project and download libpqxx* (guide: https://github.com/qwinkki/DockerPostgreSQLAuth)
3. USE 20+ VERSION OF COMPILING IN MAIN OPTIONS OF THE PROJECT !!!
4. create "PersonalFinanceManager" server in pgAdmin 4 (also you need username "postgres" in pgAdmin 4 and password: 123 | or you can change username and password in Database.cpp (variable conn) and in .yml file)
5. start the project



*libpqxx - .h, .lib, .hxx and so on files to connect PostgreSQL in c++ language
*vcpkg - to download vcpkg use git: git clone https://github.com/microsoft/vcpkg.git

(Small project for qwinki resume)
