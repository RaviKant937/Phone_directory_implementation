#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <unordered_map>
#define intnode struct trie_number
#define node struct trie
using namespace std;
/*
    to store number corresponding to every character like in dialpad of mobile.f
    for more understanding go and see main function
*/
unordered_map<char, int> mapping_char_to_number;
/*
    creating a trie data strucutre for character by character
*/
struct trie
{
    unordered_map<char, struct trie *> mymap;
    bool isending = false;
    string number, name;
};
/*
    creating a trie data strucutre for number
*/
struct trie_number
{
    unordered_map<int, intnode *> mymap;
    bool isending = false;
    string number, name;
};
/*
    globally declare the head of the two trie
*/
intnode *numhead;
node *charhead;
/*
    printing the data traversing via character by character
*/
void printing_by_char(node *head, string str, vector<string> &vect)
{
    if (head->isending and head->mymap.size() == 0)
    {
        vect.push_back(head->name + " ->" + head->number);
    }
    for (auto it : head->mymap)
    {
        if (head->isending)
        {
            vect.push_back(head->name + " ->" + head->number);
        }
        printing_by_char(it.second, str + it.first, vect);
    }
}
/*
    loading the data(reading from the phonebook.txt) via into trie data structure via character via character    
*/
void loading_data_to_programme_char()
{
    string str;
    charhead = new node();
    string name, number;
    ifstream MyReadFile("phonebook.txt");
    fflush(stdin);
    while (getline(MyReadFile, name))
    {
        getline(MyReadFile, number);
        node *temp = charhead;
        for (int j = 0; j < name.size(); j++)
        {
            if (j == name.size() - 1)
            {
                if (temp->mymap.find(tolower(name[j])) == temp->mymap.end())
                {
                    node *extra = new node();
                    extra->isending = true;
                    extra->number = number;
                    extra->name = name;
                    temp->mymap[tolower(name[j])] = extra;
                }
                else
                {
                    temp->isending = true;
                    temp->number = number;
                    temp->name = name;
                }
            }
            else
            {
                if (temp->mymap.find(tolower(name[j])) == temp->mymap.end())
                {
                    node *extra = new node();
                    extra->isending = false;
                    temp->mymap[tolower(name[j])] = extra;
                }
                temp = temp->mymap[tolower(name[j])];
            }
            fflush(stdin);
        }
    }
    MyReadFile.close();
    vector<string> vect;
    printing_by_char(charhead, "", vect);
    for (auto it : vect)
    {
        cout << it << "\n";
    }
    fflush(stdin);
    vect.clear();
    return;
}
/*
    printing the data traversing via number by number
*/
void printing_by_number(intnode *head, string str, vector<string> &vect)
{
    if (head->isending and head->mymap.size() == 0)
    {
        vect.push_back(head->name + " ->" + head->number);
    }
    for (auto it : head->mymap)
    {
        if (head->isending)
        {
            vect.push_back(head->name + " ->" + head->number);
        }
        printing_by_number(it.second, str + to_string(it.first), vect);
    }
}
/*
   loading the data(reading from the phonebook.txt) via into trie data structure via number by number 
*/
void loading_data_to_programme_number()
{
    string str;
    numhead = new intnode();
    string name, number;
    ifstream MyReadFile("phonebook.txt");
    fflush(stdin);
    while (getline(MyReadFile, name))
    {
        getline(MyReadFile, number);
        intnode *temp = numhead;
        for (int j = 0; j < number.size(); j++)
        {
            if (j == number.size() - 1)
            {
                if (temp->mymap.find(number[j]) == temp->mymap.end())
                {
                    intnode *extra = new intnode();
                    extra->isending = true;
                    extra->number = number;
                    extra->name = name;
                    temp->mymap[number[j]] = extra;
                }
                else
                {
                    temp->isending = true;
                    temp->number = number;
                    temp->name = name;
                }
            }
            else
            {
                if (temp->mymap.find(number[j]) == temp->mymap.end())
                {
                    intnode *extra = new intnode();
                    extra->isending = false;
                    temp->mymap[number[j]] = extra;
                }
                temp = temp->mymap[number[j]];
            }
            fflush(stdin);
        }
    }
    MyReadFile.close();
    vector<string> vect;
    printing_by_number(numhead, "", vect);
    for (auto it : vect)
    {
        cout << it << "\n";
    }
    fflush(stdin);
    vect.clear();
    return;
}
/*
    searching in the trie data structure that stored by number.
    but first the given character converted corresponding to number according to dialpad.
    for example:
        t is converted to 8
        ab is converted to 22
        tr is converted to 87
*/
void searching_via_num(intnode *head, string str, map<string, string> &results)
{
    if (head->isending)
    {
        results[head->name] = head->number;
    }
    for (auto it : head->mymap)
    {
        searching_via_num(it.second, str + to_string(it.first), results);
    }
}
/*
    searching in the trie data structure that stored by character.
*/
void searching_via_char(node *head, string str, map<string, string> &results)
{
    if (head->isending)
    {
        results[head->name] = head->number;
    }
    for (auto it : head->mymap)
    {
        searching_via_char(it.second, str + it.first, results);
    }
}
/*
    it is main function that is calling the above function.
    also by converting the string to corresponding number according to dialpad.
*/
void to_search(string str, map<string, string> &mymap)
{
    node *root1;
    root1 = charhead;
    intnode *root2;
    root2 = numhead;
    int i = 0;
    for (; i < str.size(); i++)
    {
        if (root1->mymap.find(str[i]) == root1->mymap.end())
        {
            break;
        }
        else
        {
            root1 = root1->mymap[str[i]];
        }
    }
    if (root1->mymap.size() > 0 and i == str.size())
    {
        searching_via_char(root1, str, mymap);
    }
    string str2;
    for (int j = 0; j < str.size(); j++)
    {
        str2 += to_string(mapping_char_to_number[tolower(str[j])]);
    }
    i = 0;
    for (; i < str2.size(); i++)
    {
        if (root2->mymap.find(str2[i]) == root2->mymap.end())
        {
            break;
        }
        else
        {
            root2 = root2->mymap[str2[i]];
        }
    }
    if (root2->mymap.size() > 0 and i == str.size())
    {
        searching_via_num(root2, str2, mymap);
    }
    //now inserting this to file
    ofstream myfile("results.txt");
    for (auto it : mymap)
    {
        myfile << it.first + "\n" + it.second + "\n";
    }
    myfile.close();
    return;
}
/*
    this function takes the input from user.
*/
void searching_in_phonebook()
{
    string str;
    char ch;
    int want_to_continue = 1;
    //that stores the result in future
    map<string, string> mymap;
    while (want_to_continue)
    {
        //clearing the previous results before putting the fresh results in the map
        mymap.clear();
        cout << "\n\n\t\tEnter next character: ";
        cin >> ch;
        str += tolower(ch);
        to_search(str, mymap);
        if (mymap.size() == 0)
        {
            cout << "\n\n\tso,sad(:(: ,No results found quiting the programme\n\n";
            return;
        }
        cout << "\n\n\t\t" << mymap.size() << "  results found with: " << str << "\n\n";
        ifstream MyReadFile("results.txt");
        string name, number;
        int count = 1;
        for (auto it : mymap)
        {
            cout << count << ": " << it.first << "\t" << it.second << "\n";
            count++;
        }
        MyReadFile.close();
        cout << "\n\n\t\tpress 0 if you want to discontinue else any number: ";
        cin >> want_to_continue;
        if (want_to_continue == 0)
            break;
    }
    return;
}
int main()
{
    cout << "\n\n\t\t\tLoading Data into memory.....\n\n";
    loading_data_to_programme_char();
    cout << "\n\n";
    loading_data_to_programme_number();
    // stored according to dialpad
    mapping_char_to_number['a'] = 2;
    mapping_char_to_number['b'] = 2;
    mapping_char_to_number['c'] = 2;
    mapping_char_to_number['d'] = 3;
    mapping_char_to_number['e'] = 3;
    mapping_char_to_number['f'] = 3;
    mapping_char_to_number['g'] = 4;
    mapping_char_to_number['h'] = 4;
    mapping_char_to_number['i'] = 4;
    mapping_char_to_number['j'] = 5;
    mapping_char_to_number['k'] = 5;
    mapping_char_to_number['l'] = 5;
    mapping_char_to_number['m'] = 6;
    mapping_char_to_number['n'] = 6;
    mapping_char_to_number['o'] = 6;
    mapping_char_to_number['p'] = 7;
    mapping_char_to_number['q'] = 7;
    mapping_char_to_number['r'] = 7;
    mapping_char_to_number['s'] = 7;
    mapping_char_to_number['t'] = 8;
    mapping_char_to_number['u'] = 8;
    mapping_char_to_number['v'] = 8;
    mapping_char_to_number['w'] = 9;
    mapping_char_to_number['x'] = 9;
    mapping_char_to_number['y'] = 9;
    mapping_char_to_number['z'] = 9;
    int to_search;
    cout << "\n\n\t\tif you want to search press 1 if not press 0: ";
    cin >> to_search;
    if (to_search)
    {
        searching_in_phonebook();
    }
    else
    {
        cout << "\n\n\nquiting the main programe\n\n\n";
    }
    return 0;
}