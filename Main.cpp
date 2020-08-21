#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <chrono>
using namespace std;

struct BookData  // this is used to store a book data author, title, publisher, description, ISBN, and year 
{
    string author;
    string title;
    string publisher;
    string description;
    long ISBN;
    int year;
};

struct node
{
    BookData book;
    node* next;
};


class LinkedList
{
private :
    node * head;
public:
    LinkedList()
    {
        head = NULL;
    }

    void AddBook(BookData book)
    {
        node* temp = new node;
        temp->book = book;
        temp->next = head;
        head = temp;
    }

    bool searchByAuthor(string authorName) 
    {
        node* tmp;
        tmp = head;
        while (tmp != NULL )
        {
            string temp = tmp->book.author;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (temp == authorName)
            {
                cout << "Book Information" << endl;
                cout << "Author: "<<tmp->book.author << endl;
                cout << "Title: " << tmp->book.title << endl;
                cout << "Publisher: " << tmp->book.publisher << endl;
                cout << "Description: " << tmp->book.description << endl;
                cout << "ISBN: " << tmp->book.ISBN << endl;
                cout << "Year: " << tmp->book.year << endl;
                cout << endl;
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }

    bool searchByTitle(string title)
    {
        node* tmp;
        tmp = head;
        while (tmp != NULL)
        {
            string temp = tmp->book.title;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (temp == title)
            {
                cout << "Book Information" << endl;
                cout << "Author: " << tmp->book.author << endl;
                cout << "Title: " << tmp->book.title << endl;
                cout << "Publisher: " << tmp->book.publisher << endl;
                cout << "Description: " << tmp->book.description << endl;
                cout << "ISBN: " << tmp->book.ISBN << endl;
                cout << "Year: " << tmp->book.year << endl;
                cout << endl;
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }

    bool searchByISBN(long ISBN)
    {
        node* tmp;
        tmp = head;
        while (tmp != NULL)
        {
            long temp = tmp->book.ISBN;
            if (temp == ISBN)
            {
                cout << "Book Information" << endl;
                cout << "Author: " << tmp->book.author << endl;
                cout << "Title: " << tmp->book.title << endl;
                cout << "Publisher: " << tmp->book.publisher << endl;
                cout << "Description: " << tmp->book.description << endl;
                cout << "ISBN: " << tmp->book.ISBN << endl;
                cout << "Year: " << tmp->book.year << endl;
                cout << endl;
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }

    void removeAllBook() 
    {
        node* temp = new node;
        node* next = new node;
        temp = head;
        while (temp != NULL)
        {
            next = temp->next;
            free(temp);
            temp = next;
        }
        head = NULL;
        cout << "All Books Have been removed" << endl;
    }

    void deleteNode( int position)
    {
       
        if (head == NULL)
        {
            cout << "List is empty" << endl;
            return;
        }    
        node* temp = new node;
       temp = head;
 
        if (position == 0)
        {
            head= temp->next;      
            free(temp);             
            return;
        }

        for (int i = 0; temp != NULL && i < position - 1; i++)
        {
            temp = temp->next;
        }     

       
        if (temp == NULL || temp->next == NULL)
        {
            return;
        }

        node* next = temp->next->next; 
        free(temp->next);  
        temp->next = next;  
    }


    bool removeBook(string authorName)
    {
        int count = 0;
        node* tmp;
        tmp = head;
        while (tmp != NULL)
        {
            string temp = tmp->book.author;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (temp == authorName)
            {
                deleteNode(count);
                return true;
            }
            count++;
            tmp = tmp->next;
        }
        cout << count << endl;
        return false;
    }


    void AddDataToFile()
    {
        ofstream myfile;
        string temp;
        myfile.open("BookData.txt");
        node* tmp;
        tmp = head;
        while (tmp != NULL)
        {
            string temp =  tmp->book.author+","+tmp->book.title+","+tmp->book.publisher+","+tmp->book.description+","+ to_string(tmp->book.ISBN)+","+to_string(tmp->book.year);
            myfile << temp << "\n";
            tmp = tmp->next;
        }
        myfile.close();
    }


    void insertionSort()
    {
        
        node* sorted = new node;
        sorted = NULL;
        node* current = new node;
        current = head;
        while (current != NULL)
        {
            node* next = new node;
            next = current->next;
            sortedInsert(sorted, current); 
            current = next;
        }
        head = sorted;
    }

   
    void sortedInsert(node* head_ref, node* new_node)
    {
        node* current = new node;
        if (head_ref->book.author == "" || (head_ref)->book.author.compare(new_node->book.author) >= 0)
        {
            new_node->next = head_ref;
            head_ref = new_node;
        }
        else
        {
            current = head_ref;
            while (current->next != NULL && current->next->book.author.compare(new_node->book.author) < 0)
            {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }
    }

    void printList()
    {
        node* temp = head;
        while (temp != NULL)
        {
            cout << temp->book.author << endl;
            temp = temp->next;
        }
    }

};

vector<string> split(string str, string token) {// this function is used to break a string into a vector using a delimiter
    vector<string>result;// creating a vector to store a string
    while (str.size())
    {
        int index = str.find(token);
        if (index != string::npos)
        {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if (str.size() == 0)result.push_back(str); // adding individual string to vector
        }
        else
        {
            result.push_back(str); // adding individual string to vector
            str = "";
        }
    }
    return result;// returning the string vector
}

int convertStringtoInt(string data)
{
    stringstream intValue(data);  //store the string into stringstream
    int x = 0;
    intValue >> x;// converting string value to int
    return x; // returning the int

}




void addDataToList(LinkedList &list)
{
    fstream newfile;
    newfile.open("BookData.txt", ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()) {   //checking whether the file is open
        string tp;
        while (getline(newfile, tp)) { //read data from file object and put it into string.
            vector<string> bookData = split(tp, ",");
            BookData obj;
            obj.author = bookData.at(0);
            obj.title = bookData.at(1);
            obj.publisher = bookData.at(2);
            obj.description = bookData.at(3);
            obj.ISBN = convertStringtoInt(bookData.at(4));
            obj.year = convertStringtoInt(bookData.at(5));
            list.AddBook(obj);
        }
        newfile.close(); //close the file object.
    }
    else
    {
        cout << "Database file not found" << endl;
    }
}


int main()
{
    LinkedList list;
    addDataToList(list);
   cout << "\nWelcome to the Library\n";
   time_t result = time(NULL);
   char str[26];
   ctime_s(str, sizeof str, &result);
   printf("%s", str);
   int choice;
   while (true)
   {
       time_t result = time(NULL);
       char str[26];
       ctime_s(str, sizeof str, &result);
       printf("Time %s", str);
       cout << "1.Add a book" << endl;
       cout << "2.Remove book" << endl;
       cout << "3.Remove all" << endl;
       cout << "4.Sort" << endl;
       cout << "5.Search by author" << endl;
       cout << "6.Search by Title" << endl;
       cout << "7.Search by ISBN" << endl;
       cout << "8.Exit" << endl;
       cout << "\nEnter Your Choice : ";
       cin >> choice;
       switch (choice)
       {
       case 1:
       {
           BookData obj;
           cout << "Enter the book information" << endl;
           cout << "Enter Author Name: ";
           cin.ignore();
           getline(cin, obj.author);
           cout << "Enter Title : ";
           getline(cin, obj.title);
           cout << "Enter Publisher : ";
           getline(cin, obj.publisher);
           cout << "Enter Description : ";
           getline(cin, obj.description);
           cout << "Enter ISBN: ";
           cin >> obj.ISBN;
           cout << "Enter Year of Publication:  ";
           cin >> obj.year;
           list.AddBook(obj);
           cout << "Book Added To Library" << endl;
           break;
       }
       case 2:
       {
           string authorName;
           cout << "Enter the book author name you want to remove: ";
           cin.ignore();
           getline(cin,authorName);
           transform(authorName.begin(), authorName.end(), authorName.begin(), ::tolower);
           bool find = list.removeBook(authorName);
           if (!find)
           {
               cout << "No book exists with this Author" << endl;
           }
           else 
           {
               cout << "Book have been removed" << endl;
           }
           break;
       }
       case 3:
       {
           list.removeAllBook();
           break;
       }
       case 4:
       {
           break;
       }
       case 5:
       {
           string authorName;
           cout << "Enter author name: ";
           cin.ignore();
           getline(cin,authorName);
           transform(authorName.begin(), authorName.end(), authorName.begin(), ::tolower);
           bool find = list.searchByAuthor(authorName);
           if (!find)
           {
               cout << "No book exists with this Author" << endl;
           }
           break;
       }
       case 6:
       {
           string title;
           cout << "Enter title of book: ";
           cin.ignore();
           getline(cin, title);
           transform(title.begin(), title.end(), title.begin(), ::tolower);
           bool find = list.searchByTitle(title);
           if (!find)
           {
               cout << "No book exists with this Author" << endl;
           }
           break;
       }
       case 7:
       {
           long ISBN;
           cout << "Enter book ISBN: ";
           cin >> ISBN;
           bool find = list.searchByISBN(ISBN);
           if (!find)
           {
               cout << "No book exists with this ISBN" << endl;
           }
           break;
       }
       case 8:
       {
           list.AddDataToFile();
           cout << "Exiting the program......" << endl;
           exit(0);
           break;
       }
       default:
       {
           cout << "\nWrong Choice\n";
       }
       }
   }
}

