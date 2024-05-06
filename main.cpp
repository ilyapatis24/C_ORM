#include "DatabaseSchema.h"
#include <Wt/Dbo/Exception.h>

int main(int argc, char** argv)
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    try {
        std::string connection_string = "host=127.0.0.1 port=5432 dbname=Books user=postgres password=postgres";
    }
    catch (Wt::Dbo::Exception& e)
    {
        std::cout << "Ошибка при работе с БД: " << e.what() << std::endl;
    }
    return 0;
}
