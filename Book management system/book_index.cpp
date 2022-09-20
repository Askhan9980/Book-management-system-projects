#include <iostream>
#include <conio.h>
#include <fstream>
#include <strings.h>
#include <stdio.h>
// #include <dos.h>

using namespace std;

class Book
{
private:
    int id;
    char title[20];
    float price;

public:
    void get_book_data()
    {
        cout << "enter a book id"
             << "  ";
        cin >> id;
        cout << "enter a title"
             << "  ";
        cin >> title;
        cout << "enter a price"
             << "  ";
        cin >> price;
    }
    void show_book_data()
    {
        cout << endl
             << "book id is"
             << "  "
             << id << "  "
             << "book title is"
             << "  " << title << "  "
             << "book price is "
             << "  " << price << endl;
    }
    void store_book_data_infile();
    void view_all_data();
    void search_data(char *);

    void delete_data(char *);
    void edit_data(char *);
};
void Book::edit_data(char *t)
{
    char od[20];
    fstream udf;
    udf.open("bookrecord.dat", ios::in | ios::out | ios::ate | ios::binary);
    udf.seekg(0);
    udf.read((char *)this, sizeof(*this));
    cout << "enter old data";
    cin >> od;
    t = od;

    while (!udf.eof())
    {
        if (!strcmp(t, title))
        {
            get_book_data();
            udf.seekp(udf.tellp() - sizeof(*this));
            udf.write((char *)this, sizeof(*this));
        }
        udf.read((char *)this, sizeof(*this));
    }
}
void Book::delete_data(char *t)
{

    char d[10];
    ifstream ddf;
    ofstream ddff;
    ddf.open("bookrecord.dat", ios::in | ios::binary);

    cout << "enter a delet title"
         << "  ";
    cin >> d;
    t = d;
    // if (!ddff)
    // {
    // cout << "not found";
    // }
    // else
    // {
    ddff.open("tempfile.dat", ios::out | ios::binary);
    ddf.read((char *)this, sizeof(*this));

    while (!ddf.eof())
    {
        if (strcmp(t, title))
        {

            ddff.write((char *)this, sizeof(*this));
        }

        ddf.read((char *)this, sizeof(*this));
    }

    ddf.close();
    ddff.close();

    remove("bookrecord.dat");
    rename("tempfile.dat", "bookrecord.dat");
}

void Book::search_data(char *t)
{
    int counter = 0;
    char x[10];
    ifstream sdf;
    sdf.open("bookrecord.dat", ios::app | ios::binary);
    cout << "enter a searcing title"
         << "  ";
    cin >> x;
    t = x;

    if (!sdf)
        cout << "not found";
    else
    {

        sdf.read((char *)this, sizeof(*this));

        while (!sdf.eof())
        {
            if (!strcmp(t, title))
            {
                show_book_data();
                counter++;
            }
            sdf.read((char *)this, sizeof(*this));
        }
        if (counter == 0)
            cout << "recourd not found in file" << endl;
        sdf.close();
    }
}
void Book::store_book_data_infile()
{
    // if (id == 0 && price == 0)
    // {
    //     cout << "book data not found";
    // }
    // else
    // {

    ofstream wdf;
    wdf.open("bookrecord.dat", ios::app | ios::binary);
    wdf.write((char *)this, sizeof(*this));
    cout << "data create successfully" << endl;
    wdf.close();
    // }
}
void Book::view_all_data()
{
    ifstream rdf;
    rdf.open("bookrecord.dat", ios::in | ios::binary);
    // if (!rdf)
    // {
    //     cout << "file not found";
    // }
    // else
    // {
    rdf.read((char *)this, sizeof(*this));
    while (!rdf.eof())
    {
        show_book_data();
        rdf.read((char *)this, sizeof(*this));
    }

    rdf.close();
    // }
}
int main()
{
    // getch();
    Book b1;
M:
    int choice;
    char ch;
    cout << "\t\t\t\t\t CONTACT MANAGEMENT SYSTEM PROJECT IN C++" << endl
         << endl;
    cout << "\t[1]\t Create new book record" << endl;
    cout << "\t[2]\t Show all book record" << endl;
    cout << "\t[3]\t Search  book record" << endl;
    cout << "\t[4]\t Delete  book record" << endl;
    cout << "\t[5]\t Edit book record" << endl;
    cout << "\t[0]\t Exit" << endl
         << endl;
    cout << "enter a your choice"
         << "  ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        b1.get_book_data();
        b1.store_book_data_infile();
        cout << "DO YOU WANT BACK IN MAIN MENU(y /n)"
             << " ";
        cin >> ch;
        if (ch == 'y')
            goto M;
        break;
    case 2:
        b1.view_all_data();

        cout << "DO YOU WANT BACK IN MAIN MENU(y /n)"
             << " ";
        cin >> ch;
        if (ch == 'y')
            goto M;
        break;
    case 3:
        b1.search_data("x");
        cout << "DO YOU WANT BACK IN MAIN MENU(y /n)"
             << " ";
        cin >> ch;
        if (ch == 'y')
            goto M;
        break;
    case 4:
        b1.delete_data("d");
        // cout << "delete succeeful" << endl;
        cout << "DO YOU WANT BACK IN MAIN MENU(y /n)"
             << " ";
        cin >> ch;
        if (ch == 'y')
            goto M;
        break;
    case 5:
        b1.edit_data("od");
        // cout << "delete succeeful" << endl;
        cout << "DO YOU WANT BACK IN MAIN MENU(y /n)"
             << " ";
        cin >> ch;
        if (ch == 'y')
            goto M;
        break;
    case 0:
        // delay(1000);
        cout << "\t\t\t\t...THANKYOU FOR USEING BOOK MANAGEMENT SYSTEM";
        getch();
        break;
    default:
        cout << "o oh sorry wrong input" << endl;
        cout << "DO YOU WANT BACK IN MAIN MENU(y /n)"
             << " ";
        cin >> ch;
        if (ch == 'y')
            goto M;
        break;
    }
    getch();
}
