#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Product{
	private:
		string productID, productName;
		double price;
		char choice;
	public:
		Product(string id, string name, double prc = 0.0) : productID(id), productName(name), price(prc) {}
		
    	string getProductID() const { return productID; }
    	string getProductName() const { return productName; }
    	double getPrice() const { return price; }
    
    	static void displayProducts() {
    	    const vector<Product> productList = {
    	        Product("ABC", "Necklace", 1500),
    	        Product("DEF", "Bracelet", 1200),
    	        Product("GHI", "Earrings", 900),
    	        Product("JKL", "Ring", 800)
        	};
        	cout << endl << left << setw(20) << "Product ID" << setw(20) << "Product Name" << setw(20) << "Price" << endl;
        	cout << "-----------------------------------------------------" << endl;
        	for (const auto& product : productList) {
        	    cout << left << setw(20) << product.productID
        	         << setw(20) << product.productName
        	         << setw(20) << product.price << endl;
        	}
    	}
    	
    	static string toLower(const string& str) {
        	string lowerStr = str;
        	for (char& c : lowerStr) {
            	c = tolower(c);
        	}
        	return lowerStr;
    	}

    	static Product findProductByID(const string& id) {
        	string searchID = toLower(id);
        	const vector<Product> productList = {
        	    Product("ABC", "Necklace", 1500),
    	        Product("DEF", "Bracelet", 1200),
    	        Product("GHI", "Earrings", 900),
    	        Product("JKL", "Ring", 800)
        	};

        	for (const auto& product : productList) {
            	string productID = toLower(product.getProductID());
            	if (productID == searchID) {
                	return product;
            	}
        	}

        	return Product("", "Unknown", 0.0); 
    	}
};

class Order{
	private:
    	vector<Product> cart;
		vector<int> orderIDs;
    	vector<vector<Product>> products;
    	vector<vector<int>> quantities;
    	vector<double> totalAmount;
	
	public:
		void checkOut(int& nextOrderID, const vector<Product>& cart, const vector<int>& quantities) {
            char choice;
            double totalAmount;
            cout << "\nDo you want to check out all the products? (Y/N): ";
            cin >> choice;
			if (choice == 'Y' || choice == 'y'){
				cout << left << setw(20) << "\nProduct ID" 
         			 << setw(20) << "Product Name" 
         			 << setw(20) << "Price" 
         			 << setw(20) << "Quantity" << endl;
    			cout << "----------------------------------------------------------------------" << endl;
    
    		for (size_t i = 0; i < cart.size(); ++i) {
        	cout << left << setw(20) << cart[i].getProductID()
             	 << setw(20) << cart[i].getProductName()
            	 << setw(20) << cart[i].getPrice()
            	 << setw(20) << quantities[i] << endl;
                totalAmount += cart[i].getPrice() * quantities[i];
            }
            cout << "\nTotal Amount: " << totalAmount << endl;
            cout << "You have successfully checked out the products!" << endl;
			}
			
            orderedProducts(nextOrderID++, cart, quantities);
        }
        
    	void orderedProducts(int orderID, const vector<Product>& orderProducts, const vector<int>& orderQuantities) {
    		double orderTotalAmount = 0.0; 
    	    for (size_t i = 0; i < orderProducts.size(); ++i) {
    	        orderTotalAmount += orderProducts[i].getPrice() * orderQuantities[i];
    	    }
    	    orderIDs.push_back(orderID);
        	products.push_back(orderProducts);
        	quantities.push_back(orderQuantities);
        	totalAmount.push_back(orderTotalAmount);
    	}

    	void displayOrders() const {
    	    for (size_t i = 0; i < orderIDs.size(); ++i) { 
    	        cout << "\nOrder ID: " << orderIDs[i] << endl;
    	        cout << "Total Amount: " << totalAmount[i] << endl;
    	        cout << "Order Details:" << endl;
    	        cout << left << setw(20) << "Product ID"
    	    	     << setw(20) << "Product Name"
                 	 << setw(20) << "Price"
                  	 << setw(20) << "Quantity" << endl;
            	cout << "----------------------------------------------------------------------" << endl;
				for (size_t j = 0; j < products[i].size(); ++j) { 
                	cout << left << setw(20) << products[i][j].getProductID()
                	     << setw(20) << products[i][j].getProductName()
                	     << setw(20) << products[i][j].getPrice()
                	     << setw(20) << quantities[i][j] << endl;
            	}
        	}
    	}
};

class ShoppingCart{
	private:
		vector<Product> cart;
		vector<int> quantities; 
	public:
		void addProduct() {
			string productID;
			char choice;
       		do {
        	   	cout << "\nEnter the Product ID -- Shopping Cart: ";
        	   	cin >> productID;
	
    	       	Product product = Product::findProductByID(productID);
	
	        	if (product.getProductName() != "Unknown") {
                	bool found = false;
                	for (size_t i = 0; i < cart.size(); ++i) {
                	    if (cart[i].getProductID() == productID) {
                	        quantities[i]++; 
                	        found = true;
                	        break;
                	    }
                	}
                	if (!found) {
                	    cart.push_back(product);
               	    	quantities.push_back(1);
                	}
                	cout << "Product added successfully!" << endl;
            	} 
				else {
                	cout << "Product not found!" << endl;
            	}
            	cout << "\nDo you want to add another product -- Shopping Cart? (Y/N): ";
            	cin >> choice;
			} while (choice == 'Y' || choice == 'y');
    	}

    	void displayCart() const {
        	cout << endl << left << setw(20) << "Product ID" 
            	 << setw(20) << "Product Name" 
            	 << setw(20) << "Price" 
            	 << setw(20) << "Quantity" << endl;
        	cout << "----------------------------------------------------------------------" << endl;

        	for (size_t i = 0; i < cart.size(); ++i) {
            	cout << left << setw(20) << cart[i].getProductID()
                	 << setw(20) << cart[i].getProductName()
                	 << setw(20) << cart[i].getPrice()
                	 << setw(20) << quantities[i] << endl;
        	}
    	}

    	void removeProduct() {
    		if (cart.empty()) {
    		    cout << "\nYour cart is empty, nothing to remove!" << endl;
    		    return;
    		}
    		char choice;
    		cout << "\nDo you want to remove a product? (Y/N): ";
    		cin >> choice;

    		if (choice == 'Y' || choice == 'y') {
    		    string productID;
    		    cout << "\nEnter the Product ID to remove: ";
    		    cin >> productID;

    	    	string lowerProductID = Product::toLower(productID);
	
    	    	bool found = false;
    	    	for (size_t i = 0; i < cart.size(); ++i) {
    	    	    if (Product::toLower(cart[i].getProductID()) == lowerProductID) {
    	        	    if (quantities[i] > 1) {
        	        	    quantities[i]--; 
            	    	    cout << "\nReduced quantity by 1 for " << cart[i].getProductName() << "!" << endl;
                		} 
						else {
                    		cart.erase(cart.begin() + i);  
                    		quantities.erase(quantities.begin() + i); 
                    		cout << "Product removed successfully!" << endl;
                		}
            		found = true;
            		break; 
            		}
        		}
        		if (!found) {
            		cout << "Product not found in the cart!" << endl;
        		}
    		}
		}
		void clearCart() {
        	cart.clear();
        	quantities.clear();
    	}
		const vector<Product>& getCartProducts() const { return cart; }
		const vector<int>& getCartQuantities() const { return quantities; }
};

int main(){
	ShoppingCart cart; 
	Order orders;
	int choice;
	static int nextOrderID = 1; 
    
	do{
		cout << "\n1 - View Products" <<endl;
		cout << "2 - View Shopping Cart" <<endl;
		cout << "3 - View Orders" <<endl;
		cout << "4 - Close" <<endl;
		cout << "Enter your choice: ";
		cin >> choice;
	
		switch (choice){
			case 1:
				Product::displayProducts();
				cart.addProduct();
				break;
			case 2:
				cart.displayCart();
				cart.removeProduct();
				orders.checkOut(nextOrderID, cart.getCartProducts(), cart.getCartQuantities());
				cart.clearCart();
				break;
			case 3:
				orders.displayOrders();
				break;
			case 4:
				break;
			default:
				cout << "Invalid Input";
				break;			
		}
	} while (choice != 4);
}