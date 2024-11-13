#include "pch.h"
#include "CppUnitTest.h"
#include "../PR10.3.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ZodiacTests
{
    TEST_CLASS(ZodiacTests)
    {
    public:
        TEST_METHOD(SortBySurname_Test)
        {
            int size = 2;
            Zodiac* people = new Zodiac[size];

            // Додаємо тестові дані
            people[0] = { "Петров", "Петро", "Лев", {10, 8, 1985} };
            people[1] = { "Іванов", "Іван", "Рак", {15, 7, 1990} };

            sortBySurname(people, size);

            // Перевірка сортування за прізвищем
            Assert::AreEqual(people[0].surname, std::string("Іванов"));
            Assert::AreEqual(people[1].surname, std::string("Петров"));

            // Очищення
            delete[] people;
        }

        TEST_METHOD(DisplayByZodiacSign_Test)
        {
            int size = 2;
            Zodiac* people = new Zodiac[size];

            // Додаємо тестові дані
            people[0] = { "Іванов", "Іван", "Рак", {15, 7, 1990} };
            people[1] = { "Петров", "Петро", "Лев", {10, 8, 1985} };

            // Перевірка знака "Рак"
            std::stringstream buffer;
            std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

            displayByZodiacSign(people, size, "Рак");

            std::cout.rdbuf(oldCout);
            std::string output = buffer.str();

            // Перевірка, що був знайдений запис з знаком "Рак"
            Assert::IsTrue(output.find("Іванов") != std::string::npos); // Перевірка наявності прізвища
            Assert::IsTrue(output.find("Рак") != std::string::npos);    // Перевірка наявності знака зодіаку

            // Очищення
            delete[] people;
        }


        TEST_METHOD(SaveToFile_Test)
        {
            Zodiac* people = new Zodiac[1];
            int size = 1;

            people[0].surname = "Іванов";
            people[0].name = "Олександр";
            people[0].zodiac_sign = "Рак";
            people[0].birthday[0] = 12;
            people[0].birthday[1] = 7;
            people[0].birthday[2] = 1990;

            std::string filename = "test_data.txt";
            saveToFile(people, size, filename);

            ifstream file(filename);
            Assert::IsTrue(file.is_open());  // Перевірка відкриття файлу

            file.close();
            remove(filename.c_str());  // Видалення файлу після тесту

            delete[] people;
        }
    };
}
