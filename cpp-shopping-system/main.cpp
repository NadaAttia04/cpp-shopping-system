#include <bits/stdc++.h>

using namespace std;

// Product structure
struct Product
{
    string name;
    double price;
    int quantity;
};

// User structure
struct User
{
    string username;
    string password;
    bool isOwner;
    vector<Product> shoppingCart;
};

// Function prototypes
//& address of variable
bool login(const vector<User>& users, const string& username, const string& password);
void registerUser(vector<User>& users, const string& username, const string& password, bool isOwner);
void addProduct(vector<Product>& products, const string& name, double price, int quantity);
void removeProduct(vector<Product>& products, const string& name, int quantity);
void displayProducts(const vector<Product>& products);
Product* searchProduct(const vector<Product>& products, const string& name);
void viewProductInfo(const Product* product);
void addToCart(User& user, const vector<Product>& products);
void removeFromCart(User& user, const string& productName);
void displayCart(const User& user);
void createReceipt(const User& user);
string getUserInput(const string& prompt);

int main()
{
    vector<User> users;
    vector<Product> products =
    {
        {"Chocolate Cake",19.99, 10},
        {"Cupcakes Assortment", 14.99,10},
        { "Strawberry Cheesecake", 24.99, 30}
    };

    while (true)
    {
        cout << "=== Online Shopping ===" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Add Product" << endl;
        cout << "4. Remove Product" << endl;
        cout << "5. View Products" << endl;
        cout << "6. Search for a Product" << endl;
        cout << "7. View Product Information" << endl;
        cout << "8. Add Product to Cart" << endl;
        cout << "9. View Shopping Cart" << endl;
        cout << "10. Remove Item from Cart" << endl;
        cout << "11. Create Receipt" << endl;
        cout << "12. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (login(users, username, password))
            {
                cout << "Login successful!" << endl;
            }
            else
            {
                cout << "Login failed. Invalid username or password." << endl;
            }
            break;
        }
        case 2:
        {
            string username, password;
            cout << "Enter desired username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            char userType;
            cout << "Are you an owner? (y/n): ";
            cin >> userType;

            bool isOwner = (userType == 'y' || userType == 'n');
            registerUser(users, username, password, isOwner);
            cout << "Registration successful!" << endl;
            break;
        }
        case 3:
        {
            if (!users.empty() && users[0].isOwner)
            {
                string name;
                double price;
                int quantity;
                cout << "Enter product name: ";
                cin >> name;
                cout << "Enter product price: $";
                cin >> price;
                cout << "Enter product quantity: ";
                cin >> quantity;
                addProduct(products, name, price, quantity);
            }
            else
            {
                cout << "You must be logged in as an owner to add a product." << endl;
            }
            break;
        }
        case 4:
        {
            if (!users.empty() && users[0].isOwner)
            {
                string name;
                int quantity;
                cout << "Enter product name to remove: ";
                cin >> name;
                cout << "Enter quantity to remove: ";
                cin >> quantity;
                removeProduct(products, name, quantity);
            }
            else
            {
                cout << "You must be logged in as an owner to remove a product." << endl;
            }
            break;
        }
        case 5:
            displayProducts(products);
            break;
        case 6:
        {
            string searchName;
            cout << "Enter product name to search: ";
            cin >> searchName;

            Product* foundProduct = searchProduct(products, searchName);
            if (foundProduct != nullptr)
            {
                viewProductInfo(foundProduct);
            }
            else
            {
                cout << "Product not found." << endl;
            }
            break;
        }
        case 7:
        {
            string productName;
            cout << "Enter product name to view information: ";
            cin >> productName;

            Product* product = searchProduct(products, productName);
            if (product != nullptr)
            {
                viewProductInfo(product);
            }
            else
            {
                cout << "Product not found." << endl;
            }
            break;
        }
        case 8:
        {
            if (!users.empty())
            {
                addToCart(users[0], products);
                cout << "Products added to the cart." << endl;
            }
            else
            {
                cout << "Please login first." << endl;
            }
            break;
        }
        case 9:
            if (!users.empty())
            {
                displayCart(users[0]);
            }
            else
            {
                cout << "Please login first." << endl;
            }
            break;
        case 10:
            if (!users.empty())
            {
                string productName;
                cout << "Enter product name to remove from cart: ";
                cin >> productName;
                removeFromCart(users[0], productName);
            }
            else
            {
                cout << "Please login first." << endl;
            }
            break;
        case 11:
            if (!users.empty() && !users[0].shoppingCart.empty())
            {
                createReceipt(users[0]);
                users[0].shoppingCart.clear(); // Clear the shopping cart after creating the receipt
            }
            else
            {
                cout << "Shopping cart is empty." << endl;
            }
            break;
        case 12:
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

bool login(const vector<User>& users, const string& username, const string& password)
{
    auto it = find_if(users.begin(), users.end(), [&](const User& u)
    {
        return u.username == username && u.password == password;
    });

    return it != users.end();
}

void registerUser(vector<User>& users, const string& username, const string& password, bool isOwner)
{
    User newUser;
    newUser.username = username;
    newUser.password = password;
    newUser.isOwner = isOwner;
    users.push_back(newUser);
}

void addProduct(vector<Product>& products, const string& name, double price, int quantity)
{
    Product newProduct;
    newProduct.name = name;
    newProduct.price = price;
    newProduct.quantity = quantity;
    products.push_back(newProduct);
}

void removeProduct(vector<Product>& products, const string& name, int quantity)
{
    auto it = find_if(products.begin(), products.end(), [&](const Product& p)
    {
        return p.name == name && p.quantity >= quantity;
    });

    if (it != products.end())
    {
        // Reduce the quantity of the product
        it->quantity -= quantity;

        // If quantity becomes zero, erase the product from the list
        if (it->quantity == 0)
        {
            products.erase(it);
        }

        cout << "Product removed successfully." << endl;
    }
    else
    {
        cout << "Product not found or quantity is not sufficient." << endl;
    }
}

void displayProducts(const vector<Product>& products)
{
    cout << "=== Available Products ===" << endl;
    for (const auto& product : products)
    {
        cout << product.name << " - $" << product.price << " - Quantity: " << product.quantity << endl;
    }
}

Product* searchProduct(const vector<Product>& products, const string& name)
{
    // Use find_if to search for a product with the specified name
    auto it = find_if(products.begin(), products.end(), [&](const Product& p)
    {
        return p.name == name;
    });

    // If the product is found, return a pointer to it; otherwise, return nullptr
    if (it != products.end())
    {
        return const_cast<Product*>(&(*it));
    }
    else
    {
        return nullptr;
    }
}

void viewProductInfo(const Product* product)
{
    cout << "=== Product Information ===" << endl;
    cout << "Name: " << product->name << endl;
    cout << "Price: $" << product->price << endl;
    cout << "Quantity available: " << product->quantity << endl;
}

void addToCart(User& user, const vector<Product>& products)
{
    while (true)
    {
        string productName;
        int quantity;

        cout << "Enter product name to add to cart (or type 'done' to finish): ";
        cin >> productName;

        if (productName == "done")
        {
            break;
        }

        Product* product = searchProduct(products, productName);
        if (product != nullptr)
        {
            cout << "Enter quantity: ";
            cin >> quantity;

            if (quantity > 0 && quantity <= product->quantity)
            {
                // Add the product to the cart
                Product productToAdd = *product;
                productToAdd.quantity = quantity;
                user.shoppingCart.push_back(productToAdd);

                // Update the product quantity in the store+
                product->quantity -= quantity;

                cout << "Product added to the shopping cart." << endl;
            }
            else
            {
                cout << "Invalid quantity or insufficient stock." << endl;
            }
        }
        else
        {
            cout << "Product not found." << endl;
        }
    }
}

void removeFromCart(User& user, const string& productName)
{
    auto it = find_if(user.shoppingCart.begin(), user.shoppingCart.end(), [&](const Product& p)
    {
        return p.name == productName;
    });

    if (it != user.shoppingCart.end())
    {
        const_cast<Product&>(*it).quantity++;  // Increase quantity in the store
        user.shoppingCart.erase(it);
        cout << "Product removed from the shopping cart." << endl;
    }
    else
    {
        cout << "Product not found in the shopping cart." << endl;
    }
}

double calculateTotal(const User& user)
{
    double total = 0;
    for (const auto& product : user.shoppingCart)
    {
        total += product.price * product.quantity;
    }
    return total;
}

void displayCart(const User& user)
{
    cout << "=== Shopping Cart ===" << endl;
    for (const auto& product : user.shoppingCart)
    {
        cout << product.name << " - $" << product.price << " - Quantity: " << product.quantity << endl;
    }
    cout << "Total: $" << calculateTotal(user) << endl;
}

void createReceipt(const User& user)
{
    cout << "=== Receipt ===" << endl;
    cout << "Customer: " << user.username << endl;
    cout << "=== Purchased Items ===" << endl;
    for (const auto& product : user.shoppingCart)
    {
        cout << product.name << " - $" << product.price << " - Quantity: " << product.quantity << endl;
    }
    cout << "Total: $" << calculateTotal(user) << endl;
    cout << "Thank you for shopping with us!" << endl;
}

string getUserInput(const string& prompt)
{
    string userInput;
    cout << prompt;
    cin >> userInput;
    return userInput;
}
