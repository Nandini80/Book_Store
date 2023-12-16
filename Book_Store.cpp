#include <iostream>
#include<limits.h>

//To keep them constant
#define V1 6
#define V 7

using namespace std;
class User
{
public:
    string name;
    string product;
    int quantity;
    float bill;
    User() {}
    User(string n, string p, int q, float b)
    {
        name = n;
        product = p;
        quantity = q;
        bill = b;
    }
};

class Delivery
{
public:
    User new_user;
    string address;
    float charges;
    int distance;
    Delivery *next = NULL;
    Delivery(string n, string p, int q, float b, string addr, float charge, int dis)
    {
        new_user = User(n, p, q, b);
        address = addr;
        charges = charge;
        distance = dis;
    }
};

class Shop
{
public:
    string name;
    string *product;
    int *price;
    string address;
    Delivery *next_user;
    Shop()
    {
        next_user = NULL;
    }
};

class TakeAway
{
public:
    string name;
    string product;
    int quantity;
    float bill;
    int orderId;
    TakeAway *left, *right;
    TakeAway(string n, string p, int q, float b, int orderId)
    {
        name = n;
        product = p;
        quantity = q;
        bill = b;
        this->orderId = orderId;
        left = right = NULL;
    }
};

Shop *shop = NULL;//no user
TakeAway *root = NULL;
string addressF;
int dist[V];//city distance
int distanceP[V1];
int option = -1;
int option1 = -1;
Delivery *currentdeliveryUser = NULL;

void placeOrder(string name, string product, int quantity, float bill, string address, float deliveryCharges, int distanceDelivery)
{
    Delivery *currentUser = new Delivery(name, product, quantity, bill, address, deliveryCharges, distanceDelivery);
    
    if (shop->next_user == NULL)
    {
        shop->next_user = currentUser;
    }
    else
    {
        Delivery *temp = shop->next_user;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = currentUser;
        currentUser->next = NULL;
    }

    cout << "\n**Order Details**";
    cout << "\n Customer Name : " << name << "\n Order name : " << product << "\n Quantity : " << quantity << "\n Total bill : " << bill;
    cout << "\n Address : " << address << "\n Distance in km : " << distanceDelivery << "\n Delivery charges : " << deliveryCharges << endl;
}

int minKey(int distanceP[], bool visitedP[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V1; v++)
        if (visitedP[v] == false && distanceP[v] < min)
            min = distanceP[v], min_index = v;

    return min_index;
}

int minDistance(int dist[], bool visited[])
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

//To find the min dist from src to every point
void dijkstra(int graph[V][V], int dist[], int src)
{
    bool visited[V];

    for (int i = 0; i < V; i++)
    {
      dist[i] = 0;
      visited[i] = false;
    }

    // dist[src] = 0;
    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited);
        visited[u] = true;
        for (int v = 0; v < V; v++) //source
        {
           if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
           dist[v] = dist[u] + graph[u][v];
        }
    }
}

// To find MST(minimum spanning tree)
void prims(int graph[V1][V1], int distanceP[])
{
    int parent[V1];
    bool visitedP[V1];

    for (int i = 0; i < V1; i++){
        distanceP[i] = INT_MAX;
        visitedP[i] = false;
    }
    distanceP[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V1 - 1; count++)
    {
        int u = minKey(distanceP, visitedP);
        visitedP[u] = true;
        for (int v = 0; v < V1; v++)
        
            if (graph[u][v] && visitedP[v] == false && graph[u][v] < distanceP[v])
                parent[v] = u, distanceP[v] = graph[u][v];
    }
}
string CityName[] = {"Book_Store", "Noida", "Delhi", "Varanasi", "Bathinda", "Ghaziabad", "Ghazipur"};

string Noida[] = {"Noida", "Sector 62", "Vashundhra", "Sector 18", "Gazipur", "Golf Couse"};

string Delhi[] = {"Delhi", "CP", "Hauz Khas", "Lodhi Lane", "Aerocity", "Southex"};

string Varanasi[] = {"Shivpur", "Lanka", "Cantt", "orderly bazaar", "Hollapur", "Durgakund"};

string Bathinda[] = {"Bathinda", "Model Town", "Vikas Nagar", "100ft road", "Clifton", "Ajeet sing road"};

int graph[V][V] = {{0, 0, 0, 0, 0, 0, 0},
                   {4, 0, 0, 6, 0, 0, 2},
                   {0, 0, 0, 0, 9, 4, 11},
                   {0, 0, 0, 1, 16, 5, 0},
                   {0, 8, 13, 0,10, 6, 0},
                   {0, 0, 4, 3, 17, 0, 7},
                   {0, 0, 0, 0, 13, 0, 7}};

int NoidaGraph[V1][V1] = {{0, 4, 4, 0, 0, 0},
                          {4, 0, 2, 0, 0, 0},
                          {4, 2, 0, 3, 2, 4},
                          {0, 0, 3, 0, 0, 3},
                          {0, 0, 2, 0, 0, 3},
                          {0, 0, 4, 3, 3, 0}};

int DelhiGraph[V1][V1] = {{0, 4, 0, 2, 0, 0},
                          {4, 0, 3, 1, 0, 6},
                          {0, 3, 0, 4, 0, 7},
                          {2, 1, 4, 0, 9, 0},
                          {0, 0, 0, 9, 0, 5},
                          {0, 6, 7, 0, 5, 0}};

int VaranasiGraph[V1][V1] = {{0, 9, 15, 6, 0, 0},
                             {9, 0, 7, 0, 0, 8},
                             {15, 7, 0, 8, 9, 5},
                             {6, 0, 8, 0, 11, 0},
                             {0, 0, 9, 11, 0, 0},
                             {0, 8, 5, 0, 0, 0}};

int BathindaGraph[V1][V1] = {{0, 6, 3, 0, 0, 1},
                             {6, 0, 0, 2, 0, 5},
                             {3, 0, 0, 0, 3, 5},
                             {0, 2, 0, 0, 6, 4},
                             {0, 0, 3, 6, 0, 6},
                             {1, 5, 5, 4, 6, 0}};
int city()
{
    int opt;
    cout << "\nThe delivery is available for following Areas : \n"
         << endl;

    cout << "\n---------------------------------";
    cout << "\n |CITY CODE |        City       |";
    cout << "\n---------------------------------";
    cout << "\n |     1    |    Varanasi       |" << endl;
    cout << "\n |     2    |    Noida          |" << endl;
    cout << "\n |     3    |    Delhi          |" << endl;
    cout << "\n |     4    |    Bathinda       |" << endl;
    cout << "\n |     5    |    Ghaziabad      |" << endl;
    cout << "\n |     6    |    Ghazipur       |" << endl;
    cout << "---------------------------------\n"
         << endl;
    cout << "Enter your option :" << endl;
    cin >> opt;
    return opt;
}
int Del()
{
    int opt;
    cout << "\nThe delivery is available for following Areas in Delhi: " << endl;

    cout << "\n--------------------------------";
    cout << "\n |CITY CODE |        AREA      |";
    cout << "\n--------------------------------";
    cout << "\n |     1    |   CP             |" << endl;
    cout << "\n |     2    |   Hauz Khas      |" << endl;
    cout << "\n |     3    |   Lodhi Lane     |" << endl;
    cout << "\n |     4    |   Aerocity       |" << endl;
    cout << "\n |     5    |   Southex        |" << endl;
    cout << "----------------------------------\n"
         << endl;
    cout << "Enter your option :" << endl;
    cin >> opt;
    return opt;
}
int Var()
{
    int opt;
    cout << "\nThe delivery is available for following Areas in Varanasi: " << endl;
    cout << "\n---------------------------------";
    cout << "\n |CITY CODE |        AREA       |";
    cout << "\n---------------------------------";
    cout << "\n |     1    |    Shivpur        |" << endl;
    cout << "\n |     2    |    Lanka          |" << endl;
    cout << "\n |     3    |    Cantt          |" << endl;
    cout << "\n |     4    |    Orderly bazaar |" << endl;
    cout << "\n |     5    |    Hollapur       |" << endl;
    cout << "-----------------------------------\n"
         << endl;
    cout << "Enter your option :" << endl;
    cin >> opt;
    return opt;
}

int Bat()
{
    int opt;
    cout << "\nThe delivery is available for following Areas in Bathinda: " << endl;
    cout << "\n-----------------------------------";
    cout << "\n |CITY CODE |        AREA         |";
    cout << "\n-----------------------------------";
    cout << "\n |     1    |    Model Town       |" << endl;
    cout << "\n |     2    |    Vikas Nagar      |" << endl;
    cout << "\n |     3    |    100ft road       |" << endl;
    cout << "\n |     4    |    Cliffton         |" << endl;
    cout << "\n |     5    |    Ajeet Singh Road |" << endl;
    cout << "-------------------------------------\n"
         << endl;
    cout << "Enter your option :" << endl;
    cin >> opt;
    return opt;
}

int Nd()
{
    int option;
    cout << "\nThe delivery is available for following areas in Noida: " << endl;
    cout << "\n-----------------------------------";
    cout << "\n |CITY CODE |        AREA         |";
    cout << "\n-----------------------------------";
    cout << "\n |     1    |    Sector 62        |" << endl;
    cout << "\n |     2    |    Vashundhra       |" << endl;
    cout << "\n |     3    |    Gazipur          |" << endl;
    cout << "\n |     4    |    Sector 18        |" << endl;
    cout << "\n |     5    |    Golf Course      |" << endl;
    cout << "-------------------------------------\n"
         << endl;
    cout << "Enter your option :" << endl;
    cin >> option;
    return option;
}
int FurthurArea(int option)
{
    int opt;
    switch (option)
    {
    case 1:
    {
        prims(VaranasiGraph, distanceP);
        opt = Var();
        addressF = Varanasi[opt];
    }
    break;

    case 2:
    {
        prims(NoidaGraph, distanceP);
        opt = Nd();
        addressF = Noida[opt];
    }
    break;

    case 3:
    {
        prims(DelhiGraph, distanceP);
        opt = Del();
        addressF = Delhi[opt];
    }
    break;

    case 4:
    {
        prims(BathindaGraph, distanceP);
        opt = Bat();
        addressF = Bathinda[opt];
    }
    break;
    }

    return opt;
}
// LL Rotation
TakeAway *LLRotation(TakeAway *root)
{
    TakeAway *x = root->left;
    TakeAway *temp = x->right;

    x->right = root;
    root->left = temp;

    root = x;

    return x;
}

// RR Rotation
TakeAway *RRRotation(TakeAway *root)
{

    TakeAway *x = root->right;
    TakeAway *temp = x->left;

    x->left = root;
    root->right = temp;

    root = x;

    return x;
}

// LR TakeAway
TakeAway *LRRotation(TakeAway *root)
{
    root->left = RRRotation(root->left);
    return LLRotation(root);
}

// RL Rotation
TakeAway *RLRotation(TakeAway *root)
{
    root->right = LLRotation(root->right);
    return RRRotation(root);
}
int height(TakeAway *root)
{
    if (root == NULL)
        return -1;
    else
    {
        int leftH = height(root->left);
        int rightH = height(root->right);

        return (1 + max(leftH, rightH));
    }
}
int balanceFactor(TakeAway *root)
{
    if (!root)
        return 0;

    return height(root->left) - height(root->right);
}

//  INSERTION in TakeAway AVL Tree
TakeAway *insertion(string name, int quantity, string product, double bill, int orderId, TakeAway *root)
{
    TakeAway *newNode = new TakeAway(name, product, quantity, bill, orderId);

    if (root == NULL)
    {
        root = newNode;
    }

    else if (root->orderId > newNode->orderId)
    {
        root->left = insertion(name, quantity, product, bill, orderId, root->left);
    }
    else if (root->orderId < newNode->orderId)
    {
        root->right = insertion(name, quantity, product, bill, orderId, root->right);
    }

    else
    {
        cout << "No duplicates OrderID are Allowed " << endl;
        return root;
    }

    int bf = balanceFactor(root);

    if (bf > 1)
    {
        // LL
        if (root->left->orderId > newNode->orderId)
        {
            return LLRotation(root);
        }

        // LR
        if (root->left->orderId < newNode->orderId)
        {
            return LRRotation(root);
        }
    }
    else if (bf < -1)
    {
        // RR
        if (root->right->orderId < newNode->orderId)
        {
            return RRRotation(root);
        }

        // RL
        if (root->right->orderId > newNode->orderId)
        {
            return RLRotation(root);
        }
    }

    return root;
}

void HomeDelivery()
{
    if (shop->next_user == NULL)
    {
        cout << "There is no Order for Home Delivery Customer till yet" << endl;
    }
    else
    {
        Delivery *traversal = shop->next_user;
        while (traversal != NULL)
        {
            cout << "-----------------------------------------------------" << endl;
            cout << "               Home Delivery Details                 "<< endl;
            cout << "Customer Name : " << traversal->new_user.name << endl;
            cout << "Product Name : " << traversal->new_user.product << endl;
            cout << "Quantity : " << traversal->new_user.quantity << endl;
            cout << "Delivery Charges : " << traversal->charges << endl;
            cout << "Delivery Distance : " << traversal->distance << "KM" << endl;
            cout << "Bill : " << traversal->new_user.bill << " RS/_" << endl;
            cout << "Delivery Address : " << traversal->address << endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }
}

void display(TakeAway *root)
{
    cout << "\n----------------------------------" << endl;
    cout << "Name :" << root->name          << endl;
    cout << "product :" << root->product    << endl;
    cout << "Quantity : " << root->quantity << endl;
    cout << "Bill : " << root->bill         << endl;
    cout << "Order ID: " << root->orderId   << endl;
    cout << "-----------------------------------\n"<< endl;
}

TakeAway *displayTakeAway(TakeAway *root)
{
    if (root)
    {
        displayTakeAway(root->left);
        display(root);
        displayTakeAway(root->right);
    }

    return root;
}

int main()
{
    shop = new Shop;
    shop->name = "Books_Store";
    shop->address = "Jaypee Institute of Information Technology ,Noida,UP";
    shop->product = new string[12]{"", "Shoe Dog", "Atomic Habits", "Wings of Fire", "A good girl guides to murder", "Three men in a boat", "The Canterville Ghost", "Invisible Man", "Godan", "Gaban", "It starts with us", "it ends with us"};
    shop->price = new int[12]{0, 450, 300, 200, 250, 150, 500, 350, 250, 550, 150, 200}; // 11 product
    int choice = -1;
    do
    {
        cout << endl<< "BOOK YOUR ORDER " << endl;
        cout << "1. Display the product and prices" << endl;
        cout << "2. Place order for Take-Away" << endl;
        cout << "3. Place order for Home Delivery " << endl;
        cout << "4. Display all Delivery Orders" << endl;
        cout << "5. Display all Take-Away Orders" << endl;
        cout << "0. EXIT " << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        string name;
        int quantity;
        int productNumber;
        float bill=0;
        string address;
        int orderId;
        int distance=0;

        switch (choice)
        {
        case 1:
        {
            cout << "Items : ";
            cout << "\n---------------------------------------------------------------------";
            cout << "\n | ITEM NO. |             ITEM NAME               | ORIGINAL PRICE  |";
            cout << "\n---------------------------------------------------------------------";
            cout << "\n |    1      " << shop->product[1] <<  "                                  450     |" << endl;
            cout << "\n |    2      " << shop->product[2] <<  "                             300     |" << endl;
            cout << "\n |    3      " << shop->product[3] <<  "                             200     |" << endl;
            cout << "\n |    4      " << shop->product[4] <<  "              250     |" << endl;
            cout << "\n |    5      " << shop->product[5] <<  "                       150     |" << endl;
            cout << "\n |    6      " << shop->product[6] <<  "                     500     |" << endl;
            cout << "\n |    7      " << shop->product[7] <<  "                             350     |" << endl;
            cout << "\n |    8      " << shop->product[8] <<  "                                     250     |" << endl;
            cout << "\n |    9      " << shop->product[9] <<  "                                     550     |" << endl;
            cout << "\n |    10     " << shop->product[10] << "                         150     |" << endl;
            cout << "\n |    11     " << shop->product[11] << "                           200     |" << endl;
            cout << "\n---------------------------------------------------------------------" << endl;
        }
        break;

        case 2:
        {
            cout << "Enter the name of customer: ";
            cin >> name;
            cout << "Enter the product Number: ";
            cin >> productNumber;
            cout << "Enter the quantity of the product: ";
            cin >> quantity;
            cout << "Enter orderID of one or two number: ";
            cin >> orderId;
    
            bill = quantity * shop->price[productNumber];
            root = insertion(name, quantity, shop->product[productNumber], bill, orderId, root);
            cout << "\n------------------------------------" << endl;
            cout << "* Your order has been placed *" << endl;
            cout << "Total amount : " << bill << endl;
            cout << "Order ID :" << orderId << endl;
            cout << "You can get your order from Book Store " << endl;
            cout << "-------------------------------------\n"
                 << endl;
        }
        break;
        case 3:
        {
            dijkstra(graph, dist, 0);
            do
            {
              option = city();
            } while (!(option >= 0 && option <= 7));

            if (option == 1 || option == 2 || option == 3 || option == 4)
            {
                do
                {
                  option1 = FurthurArea(option);
                } while (!(option1 >= 0 && option1 <= 4));

                address = CityName[option] + " " + addressF;
                distance = dist[option] + distanceP[option1]; //if we know additional address
            }
            else
            {
                address = CityName[option];
                distance = dist[option];
             }

            cout << "Enter the name of the customer: ";
            cin >> name;
            cout << "Enter the product Number: ";
            cin >> productNumber;
            cout << "Enter the quantity of the product: ";
            cin >> quantity;

            int deliveryChargePerKM = 15;
            float deliveryCharge = deliveryChargePerKM * distance;
            bill = quantity * shop->price[productNumber] + deliveryCharge;
            placeOrder(name, shop->product[productNumber], quantity, bill, address, deliveryCharge, distance);
        }
        break;

        case 4:
            HomeDelivery();
            break;

        case 5:
            displayTakeAway(root);
            break;
        }
    } 
    while (choice != 0);

    cout << "Thankyou for coming " << endl;
}