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

            // ������ ������ ���
            people[0] = { "������", "�����", "���", {10, 8, 1985} };
            people[1] = { "������", "����", "���", {15, 7, 1990} };

            sortBySurname(people, size);

            // �������� ���������� �� ��������
            Assert::AreEqual(people[0].surname, std::string("������"));
            Assert::AreEqual(people[1].surname, std::string("������"));

            // ��������
            delete[] people;
        }

        TEST_METHOD(DisplayByZodiacSign_Test)
        {
            int size = 2;
            Zodiac* people = new Zodiac[size];

            // ������ ������ ���
            people[0] = { "������", "����", "���", {15, 7, 1990} };
            people[1] = { "������", "�����", "���", {10, 8, 1985} };

            // �������� ����� "���"
            std::stringstream buffer;
            std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

            displayByZodiacSign(people, size, "���");

            std::cout.rdbuf(oldCout);
            std::string output = buffer.str();

            // ��������, �� ��� ��������� ����� � ������ "���"
            Assert::IsTrue(output.find("������") != std::string::npos); // �������� �������� �������
            Assert::IsTrue(output.find("���") != std::string::npos);    // �������� �������� ����� ������

            // ��������
            delete[] people;
        }


        TEST_METHOD(SaveToFile_Test)
        {
            Zodiac* people = new Zodiac[1];
            int size = 1;

            people[0].surname = "������";
            people[0].name = "���������";
            people[0].zodiac_sign = "���";
            people[0].birthday[0] = 12;
            people[0].birthday[1] = 7;
            people[0].birthday[2] = 1990;

            std::string filename = "test_data.txt";
            saveToFile(people, size, filename);

            ifstream file(filename);
            Assert::IsTrue(file.is_open());  // �������� �������� �����

            file.close();
            remove(filename.c_str());  // ��������� ����� ���� �����

            delete[] people;
        }
    };
}
