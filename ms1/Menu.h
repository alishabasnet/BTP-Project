#ifndef SENECA_MENU_H_
#define SENECA_MENU_H_

#include <iostream>

namespace seneca
{

    class Menu
    {
    private:
        const char *m_text;
        int m_numOptions;
        int m_numTabs;

        void printTabs() const;

        // disable copy
        Menu(const Menu &other);
        Menu &operator=(const Menu &other);

    public:
        Menu(const char *menuContent, int numberOfTabs = 0);
        ~Menu();

        void display() const;
        int &operator>>(int &Selection) const;
    };

}

#endif // !SENECA_MENU_H_
