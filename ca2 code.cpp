#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Order
{
private:
    int id;
    char name[30];
    char garment[20];
    float chest;
    float waist;
    float sleeve;
    char status;

public:
    static int cnt;

    Order()
    {
        id = 0;
        strcpy(name, "none");
        strcpy(garment, "none");
        chest = 0;
        waist = 0;
        sleeve = 0;
        status = 'P';
    }

    Order(int xid, const char xname[], const char xgarment[],
          float xchest, float xwaist, float xsleeve, char xstatus)
    {
        this->id = xid;
        strcpy(this->name, xname);
        strcpy(this->garment, xgarment);
        this->chest = xchest;
        this->waist = xwaist;
        this->sleeve = xsleeve;
        this->status = xstatus;
    }

    Order(const Order &o)
    {
        id = o.id;
        strcpy(name, o.name);
        strcpy(garment, o.garment);
        chest = o.chest;
        waist = o.waist;
        sleeve = o.sleeve;
        status = o.status;
    }

    ~Order()
    {
        id = 0;
    }

    void display()
    {
        cout << "Order ID:\t" << id << "\n";
        cout << "Customer:\t" << name << "\n";
        cout << "Garment:\t" << garment << "\n";
        cout << "Chest:\t" << chest << "\n";
        cout << "Waist:\t" << waist << "\n";
        cout << "Sleeve:\t" << sleeve << "\n";
        cout << "Status:\t" << status << "\n";
    }

    void change(float xchest, float xwaist, float xsleeve, char xstatus)
    {
        chest = xchest;
        waist = xwaist;
        sleeve = xsleeve;
        status = xstatus;
    }

    inline int getId()
    {
        return id;
    }

    static void showCount()
    {
        cout << "Total orders: " << cnt << "\n";
    }

    friend void showOrder(Order &p);
};

int Order::cnt = 0;

void showOrder(Order &p)
{
    cout << "Order ID:\t" << p.id << "\n";
    cout << "Customer:\t" << p.name << "\n";
    cout << "Garment:\t" << p.garment << "\n";
    cout << "Chest:\t" << p.chest << "\n";
    cout << "Waist:\t" << p.waist << "\n";
    cout << "Sleeve:\t" << p.sleeve << "\n";
    cout << "Status:\t" << p.status << "\n";
}

int getMeasure(const char label[], float &m)
{
    cout << "Enter " << label << " measurement: ";
    if (!(cin >> m))
    {
        cout << "Invalid measurement.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return 0;
    }
    if (m <= 0)
    {
        cout << "Measurement must be positive.\n";
        return 0;
    }
    return 1;
}

int getStatus(char &s)
{
    cout << "Enter status (P=Pending, S=Stitching, C=Complete): ";
    if (!(cin >> s))
    {
        cout << "Invalid status.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return 0;
    }
    if (s != 'P' && s != 'p' && s != 'S' && s != 's' && s != 'C' && s != 'c')
    {
        cout << "Enter P, S, or C.\n";
        return 0;
    }
    return 1;
}

int countRecords()
{
    ifstream file("./data/orders.dat", ios::binary | ios::ate);
    if (!file)
    {
        return 0;
    }
    int size = file.tellg();
    file.close();
    return size / sizeof(Order);
}
int findRecord(int id)
{
    Order temp;
    int pos = 0;
    ifstream file("./data/orders.dat", ios::binary | ios::in);
    if (!file)
    {
        return -1;
    }
    while (file.read((char *)&temp, sizeof(Order)))
    {
        if (temp.getId() == id)
        {
            file.close();
            return pos;
        }
        pos++;
    }
    file.close();
    return -1;
}

void createOrder()
{
    int id;
    char name[30], garment[20], status;
    float chest, waist, sleeve;

    cout << "Enter order ID: ";
    if (!(cin >> id))
    {
        cout << "Invalid ID.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    if (id <= 0)
    {
        cout << "ID must be positive.\n";
        return;
    }
    if (findRecord(id) != -1)
    {
        cout << "This order ID already exists.\n";
        return;
    }

    cin.ignore(1000, '\n');
    cout << "Enter customer name: ";
    cin.getline(name, 30);
    if (strlen(name) == 0)
    {
        cout << "Name cannot be empty.\n";
        return;
    }
    cout << "Enter garment type: ";
    cin.getline(garment, 20);
    if (strlen(garment) == 0)
    {
        cout << "Garment cannot be empty.\n";
        return;
    }
    if (!getMeasure("chest", chest)) return;
    if (!getMeasure("waist", waist)) return;
    if (!getMeasure("sleeve", sleeve)) return;
    if (!getStatus(status)) return;

    Order o(id, name, garment, chest, waist, sleeve, status);

    fstream file("./data/orders.dat", ios::binary | ios::out | ios::app);
    if (!file)
    {
        cout << "Cannot open file, make a data folder first.\n";
        return;
    }
    file.write((char *)&o, sizeof(Order));
    file.close();
    Order::cnt++;
    cout << "Order added.\n";
    Order::showCount();
}

void readOrders()
{
    Order temp;
    int n = 0;
    ifstream file("./data/orders.dat", ios::binary | ios::in);
    if (!file || Order::cnt == 0)
    {
        cout << "No orders available.\n";
        return;
    }
    while (file.read((char *)&temp, sizeof(Order)))
    {
        n++;
        cout << "\nOrder " << n << "\n";
        showOrder(temp);
    }
    file.close();
}

void searchOrder()
{
    int id, pos;
    Order temp;

    cout << "Enter order ID to search: ";
    if (!(cin >> id))
    {
        cout << "Invalid ID.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    pos = findRecord(id);
    if (pos == -1)
    {
        cout << "Order not found.\n";
        return;
    }
    ifstream file("./data/orders.dat", ios::binary | ios::in);
    file.seekg(pos * sizeof(Order), ios::beg);
    file.read((char *)&temp, sizeof(Order));
    file.close();
    cout << "Order found (record " << pos + 1 << ", byte offset " << pos * sizeof(Order) << "):\n";
    temp.display();
}

void updateOrder()
{
    int id, pos;
    float chest, waist, sleeve;
    char status;
    Order temp;

    cout << "Enter order ID to update: ";
    if (!(cin >> id))
    {
        cout << "Invalid ID.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    pos = findRecord(id);
    if (pos == -1)
    {
        cout << "Order not found.\n";
        return;
    }

    fstream file("./data/orders.dat", ios::binary | ios::in | ios::out);
    file.seekg(pos * sizeof(Order), ios::beg);
    file.read((char *)&temp, sizeof(Order));

    Order backup(temp);
    cout << "Old record:\n";
    backup.display();

    if (!getMeasure("new chest", chest)) { file.close(); return; }
    if (!getMeasure("new waist", waist)) { file.close(); return; }
    if (!getMeasure("new sleeve", sleeve)) { file.close(); return; }
    if (!getStatus(status)) { file.close(); return; }
    temp.change(chest, waist, sleeve, status);

    file.seekp(pos * sizeof(Order), ios::beg);
    file.write((char *)&temp, sizeof(Order));
    file.close();
    cout << "Order updated.\n";
}

int main()
{
    int choice = 0;
    Order::cnt = countRecords();

    do
    {
        cout << "\n1. Create order\n";
        cout << "2. Display all orders\n";
        cout << "3. Search by ID\n";
        cout << "4. Update order\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid choice.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
        }

        switch (choice)
        {
        case 1: createOrder(); break;
        case 2: readOrders(); break;
        case 3: searchOrder(); break;
        case 4: updateOrder(); break;
        case 5: cout << "Program ended.\n"; break;
        default: cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
