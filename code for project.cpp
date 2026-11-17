#include <iostream>
#include <string>

using namespace std;

class Order
{
private:
    int id;
    string name;
    string garment;
    float chest;
    float waist;
    float sleeve;
    char status;

public:
    static int cnt;

    int input(int &xid, string &xname, string &xgarment,
              float &xchest, float &xwaist, float &xsleeve, char &xstatus)
    {
        cout << "Enter order ID: ";
        if (!(cin >> xid))
        {
            cout << "Invalid ID.\n";
            return 0;
        }

        if (xid <= 0)
        {
            cout << "ID must be positive.\n";
            return 0;
        }

        cin.ignore();

        cout << "Enter customer name: ";
        getline(cin, xname);
        if (xname == "")
        {
            cout << "Name cannot be empty.\n";
            return 0;
        }

        cout << "Enter garment type: ";
        getline(cin, xgarment);
        if (xgarment == "")
        {
            cout << "Garment cannot be empty.\n";
            return 0;
        }

        cout << "Enter chest measurement: ";
        if (!(cin >> xchest))
        {
            cout << "Invalid measurement.\n";
            return 0;
        }

        if (xchest <= 0)
        {
            cout << "Measurement must be positive.\n";
            return 0;
        }

        cout << "Enter waist measurement: ";
        if (!(cin >> xwaist))
        {
            cout << "Invalid measurement.\n";
            return 0;
        }

        if (xwaist <= 0)
        {
            cout << "Measurement must be positive.\n";
            return 0;
        }

        cout << "Enter sleeve measurement: ";
        if (!(cin >> xsleeve))
        {
            cout << "Invalid measurement.\n";
            return 0;
        }

        if (xsleeve <= 0)
        {
            cout << "Measurement must be positive.\n";
            return 0;
        }

        cout << "Enter status (P=Pending, S=Stitching, C=Complete): ";
        if (!(cin >> xstatus))
        {
            cout << "Invalid status.\n";
            return 0;
        }

        if (xstatus != 'P' && xstatus != 'p' &&
            xstatus != 'S' && xstatus != 's' &&
            xstatus != 'C' && xstatus != 'c')
        {
            cout << "Enter P, S, or C.\n";
            return 0;
        }

        this->id = xid;
        this->name = xname;
        this->garment = xgarment;
        this->chest = xchest;
        this->waist = xwaist;
        this->sleeve = xsleeve;
        this->status = xstatus;

        return 1;
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

int main()
{
    Order arr[50];
    Order *ptr = arr;

    int choice = 0;
    int id = 0;
    int flag = 0;
    int found = 0;
    int ok = 0;
    float chest = 0;
    float waist = 0;
    float sleeve = 0;
    char status = ' ';
    string name;
    string garment;

    do
    {
        cout << "\n1. Create order\n";
        cout << "2. Display all orders\n";
        cout << "3. Search by ID\n";
        cout << "4. Exit\n";
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
        case 1:
            if (Order::cnt >= 50)
            {
                cout << "Order list is full.\n";
                break;
            }

            cout << "Enter order ID: ";
            if (!(cin >> id))
            {
                cout << "Invalid ID.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }

            if (id <= 0)
            {
                cout << "ID must be positive.\n";
                break;
            }

            flag = 0;
            for (int i = 0; i < Order::cnt; i++)
            {
                if (arr[i].getId() == id)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag == 1)
            {
                cout << "This order ID already exists.\n";
                break;
            }

            ok = arr[Order::cnt].input(id, name, garment,
                                       chest, waist, sleeve, status);

            if (ok == 1)
            {
                Order::cnt++;
                cout << "Order added.\n";
                Order::showCount();
            }
            break;

        case 2:
            if (Order::cnt == 0)
            {
                cout << "No orders available.\n";
            }
            else
            {
                for (int i = 0; i < Order::cnt; i++)
                {
                    cout << "\nOrder " << i + 1 << "\n";
                    showOrder(ptr[i]);
                }
            }
            break;

        case 3:
            if (Order::cnt == 0)
            {
                cout << "No orders available.\n";
                break;
            }

            cout << "Enter order ID to search: ";
            if (!(cin >> id))
            {
                cout << "Invalid ID.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }

            found = 0;
            for (int i = 0; i < Order::cnt; i++)
            {
                if (ptr[i].getId() == id)
                {
                    cout << "Order found:\n";
                    ptr[i].display();
                    found = 1;
                    break;
                }
            }

            if (found == 0)
            {
                cout << "Order not found.\n";
            }
            break;

        case 4:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}