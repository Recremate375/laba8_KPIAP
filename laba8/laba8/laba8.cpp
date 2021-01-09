#pragma once
#include<iostream>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class Exception
{
protected:
    int error;
public:
    Exception()
    {
        error = 0;
    }
    Exception(int _error)
    {
        error = _error;
    }
    ~Exception()
    {

    };
    void Show()
    {
        if (this->error == 0)
        {
            cout << "Input error! Enter int!" << endl;
        }
        if (this->error == 1)
        {
            cout << "Opening error!" << endl;
        }
    }
};


class Salary
{
private:
    int salary_size;
    string otdel_name;
public:
    string fio;
    Salary() : fio("abonent"), salary_size(0), otdel_name("-") {}
    Salary(string f, int g, string s) : fio(f), salary_size(g), otdel_name(s) {}
    void setFio(string f)
    {
        fio = f;
    }
    void set_salary_size(int g)
    {
        salary_size = g;
    }
    void set_otdel_name(string s)
    {
        otdel_name = s;
    }
    string getFio()
    {
        return fio;
    }
    int get_salary()
    {
        return salary_size;
    }
    string get_otdel_name()
    {
        return otdel_name;
    }

    friend ostream& operator<<(ostream& out, const Salary t)
    {
        out << "\nFull-Сontact FIO = " << t.fio << "\nSalary Size = " << t.salary_size << "\nOtdel name = " << t.otdel_name << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Salary& t)
    {
        in >> t.fio;
        in >> t.salary_size;
        in >> t.otdel_name;
        return in;
    }

    friend bool operator==(Salary t1, Salary t2) {
        if (t1.salary_size == t2.salary_size && t1.otdel_name == t2.otdel_name)
            return true;
        else
            return false;
    }

    friend bool operator<(const Salary t1, const Salary t2)
    {
        if (t1.salary_size < t2.salary_size)
            return true;
        else
            return false;
    }

    friend bool operator <(const Salary t1, const int t2)
    {
        if (t1 < t2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    friend bool operator>(const Salary t1, const Salary t2)
    {
        if (t1.salary_size > t2.salary_size)
            return true;
        else
            return false;
    }
};

using namespace std;

class  Node
{
public:
    Salary data;
    Node* next;
    Node* prev;
    Node() : data(), next(nullptr) { }

    Node(Salary d) : data(d), next(nullptr) { }
};


class DList
{
private:
    Node* head;
    Node* tail;
    int size;
public:

    DList() :head(nullptr), size(0) {}

    void push_front(Salary x)
    {
        if (head == nullptr)
        {
            Node* element = new Node(x);
            head = new Node(x);
            element->next = head;
            head = element;
            size++;
        }
        else
        {
            Node* tmp = head;
            int i = 0;
            while (i < size - 1)
            {
                tmp = tmp->next;
                i++;
            }
            tmp->next = new Node(x);
            tmp->next->next = head;
            size++;
        }
    }
    void pop_front()
    {
        if (size == 0)
            throw Exception();
        Node* tmp = head;
        head = head->next;
        delete tmp;
        size--;
        Node* t = head;
        int i = 0;
        while (i < size - 1)
        {
            t = t->next;
            i++;
        }
        t->next = head;
        tail = 0;
    }
    void outputTaskByName(int ye)
    {
        if (size == 0)
            throw Exception();
        Node* tmp = head;
        int i = 0;
        while (i < size)
        {
            if (tmp->data.get_salary() < ye) {
                cout << "   " << tmp->data;
            }
            tmp = tmp->next;
            i++;
        }
    }
    Node* getNode()
    {
        return head;
    }
    int getSize()
    {
        return size;
    }
    friend ostream& operator<<(ostream& out, const Node& node)
    {
        out << node.data;
        return out;
    }
};


class Iterator
{
private:
    Node* node;
    int size;
    int current;
public:

    Iterator(DList* element) : current(0)
    {
        node = element->getNode();
        size = element->getSize();
    }
    void begin()
    {
        if (size == 0)
            throw Exception();
        if (current != 0)
        {
            while (current < size)
            {
                current++;
                node = node->next;
            }
            current = 0;
        }

    }
    void searchAbn(Salary x)
    {
        if (size == 0)
            throw Exception();
        int i = 0;
        while (i < size)
        {
            if (x == node->data)
            {
                cout << "\nElement\n " << x << "\nfound" << endl;
                return;
            }
            if (current == size - 1)
                current = 0;
            else
                current++;
            node = node->next;
            i++;
        }
        cout << "\nElement\n " << x << " \nnot found" << endl;
    }
    Iterator& operator++()
    {
        if (size == 0)
            throw Exception();
        if (size == 1)
            current = 0;
        else
            current++;
        node = node->next;
        return *this;
    }
    Salary operator*() {
        return node->data;
    }
    void operator = (Salary x)
    {
        if (size == 0)
            throw Exception();
        node->data = x;
    }
    Iterator& operator[](int index)
    {
        if (size == 0)
            throw Exception();
        Node* tmp = node;
        while (1)
        {
            if (current == index)
            {
                node = tmp;
                return *this;
            }
            tmp = tmp->next;
            if (current == size - 1)
                current = 0;
            else
                current++;
        }
    }
    void srtt()
    {
        if (size == 0)
            throw Exception();
        int step, i, j;
        Salary tmp;
        for (step = size / 2; step > 0; step /= 2)
            for (i = step; i < size; i++)
                for (j = i - step; j >= 0 && (*this)[j].node->data > (*this)[j + step].node->data; j -= step)
                {
                    tmp = (*this)[j].node->data;
                    (*this)[j].node->data = (*this)[j + step].node->data;
                    (*this)[j + step].node->data = tmp;
                }
    }
    void taskSort(int num)
    {
        if (size == 0)
            throw Exception();
        int step, i, j;
        Salary tmp;
        for (step = size / 2; step > 0; step /= 2)
            for (i = step; i < size; i++)
            {
                for (j = i - step; j >= 0 && (*this)[j].node->data.get_salary() > num
                    ; j -= step)
                {
                    tmp = (*this)[j].node->data;
                    (*this)[j].node->data = (*this)[j + step].node->data;
                    (*this)[j + step].node->data = tmp;
                }
            }

    }
    friend ostream& operator<<(ostream& out, const Iterator& it)
    {
        out << it.node;
        return out;
    }
};

enum Key { no = 0, txt, bin };

class File
{
private:
    fstream file;
    string name;
    Key key;
    int size;
public:
    File() : name("-"), key(no), size(0) {}
    File(string n, Key k) : name(n), key(k), size(0) {}
    friend File& operator<<(File& file, const char* s)
    {

        if (!file.file.is_open())
        {
            throw 1;
        }

        /*catch (int i)
        {
            Exception ex(i);
            ex.Show();
        }*/
        string str = s;
        file.file << str;
        return file;
    }
    friend fstream& operator<<(fstream& out, Salary& t) {

        try {
            if (!out.is_open())
            {
                throw 1;
            }
        }
        catch (int i)
        {
            Exception ex(i);
            ex.Show();
        }
        int a = out.tellg();
        string fio = t.getFio();
        size_t len1 = fio.length() + 1;

        int yearNumber = t.get_salary();

        string phoneNumber = t.get_otdel_name();
        size_t len2 = phoneNumber.length() + 1;

        out.write((char*)(&len1), sizeof(len1));
        out.write((char*)(fio.c_str()), len1);

        out.write((char*)(&yearNumber), sizeof(yearNumber));

        out.write((char*)(&len2), sizeof(len2));
        out.write((char*)(phoneNumber.c_str()), len2);


        return out;
    }
    friend File& operator<<(File& file, Salary& t)
    {
        int pos = 0, a = 0, size = 0;

        if (!file.file.is_open())
        {
            cout << "1";
        }

        if (file.key == txt) {
            file.file << t.getFio() << " " << t.get_salary() << " " << t.get_otdel_name() << endl;
        }
        else if (file.key == bin) {
            string fio = t.getFio();
            size_t len1 = fio.length() + 1;

            int otdelName = t.get_salary();

            string salarysize = t.get_otdel_name();
            size_t len2 = salarysize.length() + 1;

            file.file.write((char*)(&len1), sizeof(len1));
            file.file.write((char*)(fio.c_str()), len1);

            file.file.write((char*)(&otdelName), sizeof(otdelName));

            file.file.write((char*)(&len2), sizeof(len2));
            file.file.write((char*)(salarysize.c_str()), len2);
        }
        return file;
    }
    friend ostream& operator<<(ostream& out, File& file)
    {
        int a = 0;

        if (!file.file.is_open())
        {
            throw 1;
        }

        if (file.key == txt) {
            string str;
            while (!file.file.eof()) {
                getline(file.file, str);
                a = file.file.tellg();
                cout << str << endl;
            }
        }
        else if (file.key == bin) {
            int i = 0;
            int size = 0, step = 0;
            /*Abonent tmp;*/
            while (i < file.size) {
                int salarysize = 0;

                size_t len = 0;

                file.file.read((char*)(&len), sizeof(len));
                char* f = new char[len];

                file.file.read((char*)(f), len);
                f[len - 1] = '\0';

                file.file.read((char*)(&salarysize), sizeof(int));

                file.file.read((char*)(&len), sizeof(len));
                char* s = new char[len];

                file.file.read((char*)(s), len);
                s[len - 1] = '\0';

                cout << f << " " << salarysize << " " << s << " " << endl;

                delete[] f;
                delete[] s;
                i++;

            }
        }
        return out;
    }


    ~File() { file.close(); }

    void open(string mode)
    {
        switch (key)
        {
        case txt: {
            if (mode == "r") {
                file.open(name, ios_base::in);   
            }
            else if (mode == "add") {
                file.open(name, ios_base::app);  
            }
            else if (mode == "w") {
                file.open(name, ios_base::out); 
            }
            else if (mode == "wr") {
                file.open(name, ios_base::in | ios_base::out); 
            }
            break;
        }
        case bin: {
            if (mode == "r") {
                file.open(name, ios_base::binary | ios_base::in);   
            }
            else if (mode == "add") {
                file.open(name, ios_base::binary | ios_base::app); 
            }
            else if (mode == "w") {
                file.open(name, ios_base::binary | ios_base::out); 
            }
            else if (mode == "wr") {
                file.open(name, ios_base::binary | ios_base::in | ios_base::out);  
            }
            break;
        }

        }
        if (!file.is_open())
        {
            throw;
        }

    }

    void close()
    {
        file.close();
    }
    void begin()
    {
        file.seekg(0, ios_base::beg); 
    }
    void setSize(int s) {
        size = s;
    }
    int getSize() {
        return	size;
    }
    Salary read()
    {
        string str;
        Salary t;
        getline(this->file, str, ' ');
        t.setFio(str);
        getline(this->file, str, ' ');
        t.set_salary_size(stoi(str));
        getline(this->file, str);
        t.set_otdel_name(str);

        return t;
    }
    void edit(int line, Salary mas[]) {
        this->open("wr");

        int a, b;

        try {
            if (!file.is_open())
            {
                throw 1;
            }
        }
        catch (int i)
        {
            Exception ex(i);
            ex.Show();
            return;
        }
        Salary tmp;
        if (this->key == txt) {
            string str;
            for (int i = 0; i < line - 1; i++)
                getline(this->file, str);
            getline(this->file, str, ' ');
            tmp.setFio(str);
            getline(this->file, str, ' ');
            tmp.set_salary_size(stoi(str));
            getline(this->file, str, ' ');
            tmp.set_otdel_name(str);
        }
        else if (this->key == bin) {
            size_t len = 0;
            for (int i = 0; i < line; i++) {
                this->file.read((char*)(&len), sizeof(len));
                char* n = new char[len];
                string fio;
                string otdelname;
                int salarysize = 0;

                this->file.read((char*)(n), len);
                fio = n;
                fio[len - 1] = '\0';
                this->file.read((char*)(&salarysize), sizeof(int));

                this->file.read((char*)(&len), sizeof(len));
                this->file.read((char*)(n), len);
                otdelname = n;
                otdelname[len - 1] = '\0';

                tmp.setFio(fio);
                tmp.set_salary_size(salarysize);
                tmp.set_otdel_name(otdelname);
                delete[]n;
            }
            a = file.tellg();
        }

        cout << "Petrovski_Petr_Petrovich/20000/meow - edited" << endl;

        string fi = "Petrovski_Petr_Petrovich";
        rewind(stdin);
        tmp.setFio(fi);

        int yn = 2000;
        tmp.set_salary_size(yn);
        rewind(stdin);

        string pn = "meow";
        rewind(stdin);

        tmp.set_otdel_name(pn);

        a = file.tellg();
        file.seekg(0, ios_base::end);
        b = file.tellg();
        this->file.seekg(0, ios_base::beg);
        if (this->key == txt) {
            string tmp;
            for (int i = 0; i < line - 1; i++)
                getline(this->file, tmp);
            int pos = this->file.tellg();
            this->file.seekg(pos, ios_base::beg);
            this->file << tmp;
            return;
        }
        else if (this->key == bin) {
            for (int i = 0; i < line - 1; i++)
            {
                size_t len = 0;
                this->file.read((char*)(&len), sizeof(len));
                char* n = new char[len];
                string fio;
                string otdelname;
                int salarysize = 0;

                this->file.read((char*)(n), len);
                fio = n;
                fio[len - 1] = '\0';
                this->file.read((char*)(&salarysize), sizeof(int));

                this->file.read((char*)(&len), sizeof(len));
                //char* k = new char[len];
                this->file.read((char*)(n), len);
                /*phoneNumber = k;
                phoneNumber[len - 1] = '\0';*/


                delete[] n;
                //delete[]k;
            }
            int pos = this->file.tellg();

            char* last = new char[b - a];
            this->file.read((char*)last, static_cast<std::streamsize>(b) - a);

            this->close();
            this->open("w");
            pos = this->file.tellg();

            for (int i = 0; i < getSize(); i++) {
                if (i != line - 1)
                    file << mas[i];
                else {
                    file << tmp;
                    mas[i].setFio(tmp.getFio());
                    mas[i].set_salary_size(tmp.get_salary());
                    mas[i].set_otdel_name(tmp.get_otdel_name());
                }
            }
        }

        this->close();
    }

    void deleteSotrudnik(int line, Salary mas[]) {
        this->open("wr");

        int a, b;

        try {
            if (!file.is_open())
            {
                throw 1;
            }
        }
        catch (int i)
        {
            Exception ex(i);
            ex.Show();
            return;
        }
        Salary temp;
        if (this->key == txt) {
            string str;
            for (int i = 0; i < line - 1; i++)
                getline(this->file, str);

            getline(this->file, str, ' ');
            temp.setFio(str);

            getline(this->file, str, ' ');
            temp.set_salary_size(stoi(str));

            getline(this->file, str, ' ');
            temp.set_otdel_name(str);
        }
        else if (this->key == bin) {
            size_t len = 0;
            for (int i = 0; i < line; i++) {
                this->file.read((char*)(&len), sizeof(len));
                char* n = new char[len];
                string Fio;
                string otdel_name;
                int salary_size = 0;

                this->file.read((char*)(n), len);
                Fio = n;
                Fio[len - 1] = '\0';
                this->file.read((char*)(&salary_size), sizeof(int));

                this->file.read((char*)(&len), sizeof(len));
                this->file.read((char*)(n), len);
                otdel_name = n;
                otdel_name[len - 1] = '\0';

                temp.setFio(Fio);
                temp.set_salary_size(salary_size);
                temp.set_otdel_name(otdel_name);
                delete[]n;
            }
            a = file.tellg();
        }

        string fi = "";
        rewind(stdin);
        temp.setFio(fi);

        int yn = NULL;
        temp.set_salary_size(yn);
        rewind(stdin);

        string pn = "";
        rewind(stdin);

        temp.set_otdel_name(pn);

        a = file.tellg();
        file.seekg(0, ios_base::end);
        b = file.tellg();
        this->file.seekg(0, ios_base::beg);
        if (this->key == txt) {
            string tmp;
            for (int i = 0; i < line - 1; i++)
                getline(this->file, tmp);
            int pos = this->file.tellg();
            this->file.seekg(pos, ios_base::beg);
            this->file << tmp;
            return;
        }
        else if (this->key == bin) {
            for (int i = 0; i < line - 1; i++)
            {
                size_t len = 0;

                this->file.read((char*)(&len), sizeof(len));

                char* n = new char[len];

                string Fio;
                string otdel_name;
                int salary_size = 0;

                this->file.read((char*)(n), len);
                Fio = n;

                Fio[len - 1] = '\0';

                this->file.read((char*)(&salary_size), sizeof(int));

                this->file.read((char*)(&len), sizeof(len));

                this->file.read((char*)(n), len);

                delete[] n;
            }
            int position = this->file.tellg();

            char* last = new char[b - a];
            this->file.read((char*)last, static_cast<std::streamsize>(b) - a);

            this->close();
            this->open("w");
            position = this->file.tellg();

            for (int i = 0; i < getSize(); i++) {
                if (i != line - 1)
                    file << mas[i];
            }
        }

        this->close();
    }

    void sort_by_name()
    {
        string temp;
        string j1, j2;
        int pos;
        this->open("wr");
        try {
            if (!file.is_open())
            {
                throw 1;
            }
        }
        catch (int i)
        {
            Exception ex(i);
            ex.Show();
            return;
        }
        for (int i = 0; i < this->size - 1; i++) {
            for (int j = 0; j < this->size - i - 1; j++) {
                this->file.seekg(0, ios_base::beg);
                for (int k = 0; k < j; k++) {
                    std::getline(this->file, j1);
                }
                std::getline(this->file, j1, ' ');
                std::getline(this->file, j2);
                std::getline(this->file, j2, ' ');
                if (j1 > j2) {
                    this->file.seekg(0, ios_base::beg);
                    pos = this->file.tellg();
                    for (int k = 0; k <= j; k++) {
                        std::getline(this->file, j1);
                        pos = this->file.tellg();
                    }
                    temp = j1;
                    std::getline(this->file, j2);
                    this->file.seekg(0, ios_base::beg);
                    for (int k = 0; k < j; k++) {
                        std::getline(this->file, j1);
                    }
                    pos = this->file.tellg();
                    this->file.seekg(pos, ios_base::beg);
                    this->file << j2 << '\n';
                    this->file << temp << '\n';
                }
            }
        }
        this->close();
    }


    void sort_by_otdel_name() {
        string tmp;
        string s1, s2;
        int i1, i2;
        int pos;
        this->open("wr");
        try {
            if (!file.is_open())
            {
                throw 1;
            }
        }
        catch (int i)
        {
            Exception ex(i);
            ex.Show();
            return;
        }
        for (int i = 0; i < this->size - 1; i++) {
            for (int j = 0; j < this->size - i - 1; j++)
            {
                this->file.seekg(0, ios_base::beg);
                for (int k = 0; k < j; k++)
                    getline(this->file, s1);
                for (int t = 0; t < 2; t++)
                    getline(this->file, s1, ' ');
                getline(this->file, s2);
                for (int t = 0; t < 2; t++)
                    getline(this->file, s2, ' ');
                i1 = stoi(s1);
                i2 = stoi(s2);
                if (i1 > i2)
                {
                    this->file.seekg(0, ios_base::beg);
                    pos = this->file.tellg();
                    for (int k = 0; k <= j; k++) {
                        getline(this->file, s1);
                        pos = this->file.tellg();
                    }
                    tmp = s1;
                    getline(this->file, s2);
                    this->file.seekg(0, ios_base::beg);
                    for (int k = 0; k < j; k++) {
                        getline(this->file, s1);
                    }
                    pos = this->file.tellg();
                    this->file.seekg(pos, ios_base::beg);
                    this->file << s2 << '\n';
                    this->file << tmp << '\n';
                }
            }
        }
        this->close();
    }
    void sort_by_salary_size()
    {
        string temp;
        string j1, j2;
        int i1, i2;
        int pos;
        this->open("wr");
        try {
            if (!file.is_open())
            {
                throw 1;
            }
        }
        catch (int i)
        {
            Exception ex(i);
            ex.Show();
            return;
        }
        for (int i = 0; i < this->size - 1; i++) {
            for (int j = 0; j < this->size - i - 1; j++) {
                this->file.seekg(0, ios_base::beg);
                for (int k = 0; k < j; k++) {
                    getline(this->file, j1);
                }
                getline(this->file, j1, ' ');
                getline(this->file, j1, ' ');
                getline(this->file, j2);
                getline(this->file, j2, ' ');
                getline(this->file, j2, ' ');
                i1 = stoi(j1);
                i2 = stoi(j2);
                if (i1 > i2) {
                    this->file.seekg(0, ios_base::beg);
                    pos = this->file.tellg();
                    for (int k = 0; k <= j; k++) {
                        getline(this->file, j1);
                        pos = this->file.tellg();
                    }
                    temp = j1;
                    getline(this->file, j2);
                    this->file.seekg(0, ios_base::beg);
                    for (int k = 0; k < j; k++) {
                        getline(this->file, j1);
                    }
                    pos = this->file.tellg();
                    this->file.seekg(pos, ios_base::beg);
                    this->file << j2 << '\n';
                    this->file << temp << '\n';
                }
            }
        }
        this->close();
    }
};


using namespace std;
int main()
{

    Salary sotrudnik2("Demidov_Denis_Dmitrievich", 20000, "  meow");
    Salary sotrudnik1("Cetov_Ctepan_Cergeevich", 30000, "  labs");
    Salary sotrudnik3("Antipov_Andrey_Alexeevich", 21500, "  bsuir");
    Salary sotrudnik4("Betalis_Betaliy_Borisovich", 40000, "  mur");
    Salary sotrudnik5("Ezhova_Ekaterina_Elkovna", 20000, "  kus");
    Salary un[5] = {
        sotrudnik1,
        sotrudnik2,
        sotrudnik3,
        sotrudnik4,
        sotrudnik5
    };
    cout << "\n .txt in .txt\n";
    File file1("1.txt", txt);
    file1.open("w");
    file1.setSize(5);
    file1 << sotrudnik1;
    file1 << sotrudnik2;
    file1 << sotrudnik3;
    file1 << sotrudnik4;
    file1 << sotrudnik5;
    file1.close();
    file1.open("r");
    cout << file1;
    file1.close();
    cout << "\n .txt in .bin\n";
    File file2("2.txt", bin);
    file2.open("w");
    file2.setSize(5);
    file2 << sotrudnik1;
    file2 << sotrudnik2;
    file2 << sotrudnik3;
    file2 << sotrudnik4;
    file2 << sotrudnik5;
    file2.close();
    file2.open("r");
    cout << file2;
    file2.close();
    cout << "\n .bin in .bin\n";
    File file3("3.bin", bin);
    file3.open("w");
    file3.setSize(5);
    file3 << sotrudnik1;
    file3 << sotrudnik2;
    file3 << sotrudnik3;
    file3 << sotrudnik4;
    file3 << sotrudnik5;
    file3.close();
    file3.open("r");
    cout << file3;
    file3.close();

    cout << "\n\n";

    int i = 0, lineToEdit = 3;

    cout << "abonent to change - 3" << endl;
    lineToEdit = 3;
    cout << "abonent to delete - 5" << endl;
    int lineToDel = 5;

    file2.open("r");
    file2.edit(lineToEdit, un);
    file2.close();

    file2.open("w");
    cout << "Ezhova_Ekaterina_Elkovna 20000 kus - deleted" << endl;
    file2.deleteSotrudnik(lineToDel, un);
    file2.close();

    rewind(stdin);
    cout << "\n";

    cout << "\n\n";
    cout << "Sort FIO:" << endl;
    cout << "\n\n";
    file1.sort_by_name();
    file1.open("r");
    cout << file1;
    file1.close();
    cout << "\n\n";
    cout << "Sort by salary size:" << endl;
    cout << "\n\n";
    file1.sort_by_salary_size();
    file1.open("r");
    cout << file1;
    file1.close();
    file1.sort_by_name();

    DList l;
    file1.open("r");
    Salary t;
    for (int i = 0; i < file1.getSize(); i++)
    {
        t = file1.read();
        l.push_front(t);
    }
    Iterator I(&l);

    cout << "employees with a salary of less than 30,000: \n";

    l.outputTaskByName(30000);
}
