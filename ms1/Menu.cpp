#include <sstream>
#include <iomanip>
#include <iostream>
#include <string.h>

#include "Menu.h"

namespace seneca
{

    Menu::Menu(const char *menuContent, int numberOfTabs)
    {
        m_numTabs = numberOfTabs;
        m_text = new char[strlen(menuContent) + 1];
        strcpy(const_cast<char *>(m_text), menuContent);

        m_numOptions = 0;
        for (int i = 0; m_text[i] != '\0'; i++)
        {
            if (m_text[i] == '\n')
                m_numOptions++;
        }
    }

    Menu::~Menu()
    {
        delete[] m_text;
    }

    void Menu::printTabs() const
    {
        std::cout << std::setfill(' ') << std::setw(m_numTabs) << "";
    }

    void Menu::display() const
    {
        // converting text to string stream, to print tabs on newline
        std::istringstream iss(m_text);
        std::string line;

        // separate each on new line
        while (std::getline(iss, line, '\n'))
        {
            printTabs();
            std::cout << line << std::endl;
        }

        // show exit option
        printTabs();
        std::cout << "0- Exit" << std::endl;

        // input cursor
        printTabs();
        std::cout << "> ";
    }

    int &Menu::operator>>(int &Selection) const
    {

        std::string input;
        display();

        while (true)
        {
            std::getline(std::cin, input);

            /**
             * using help from internet
             * 1. to check if it is alpha character
             * https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/
             * 2. if it has whitespace
             * https://www.geeksforgeeks.org/stdfind_first_of-in-cpp/
             */

            // 1. Check if it is alpha character
            bool hasAlphabet = false;
            for (char c : input)
            {
                if (std::isalpha(c))
                {
                    hasAlphabet = true;
                    break;
                }
            }

            if (hasAlphabet)
            {
                printTabs();
                std::cout << "Bad integer value, try again: ";
            }

            // 2. Check if it has whitespaces
            else if (input.find_first_of(" \t") != std::string::npos)
            {
                printTabs();
                std::cout << "Only enter an integer, try again: ";
            }
            else
            {

                // read as string, so converting to integer
                // don't need to try/catch, as alpha character and whitespace is already checked
                try
                {

                    Selection = std::stoi(input);
                    if (Selection < 0 || Selection > m_numOptions)
                    {
                        printTabs();
                        std::cout << "Invalid value entered, retry [0 <= value <= " << m_numOptions << "]: ";
                    }

                    else
                        break;
                }
                catch (...)
                {
                    printTabs();
                    std::cout << "Bad integer value, try again: ";
                }
            }
        }

        return Selection;
    }
}
