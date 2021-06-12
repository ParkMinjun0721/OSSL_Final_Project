#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//Handong Food Recommendation List
vector<string> split(string input, char delimiter) {
    vector<string> answer;
    stringstream ss(input);
    string temp;
 
    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }
 
    return answer;
}

class bst_node {
public:
    string rname;
    string fname;
    string rate;

    bst_node *left, *right;
    bst_node();
    bst_node(string s1, string s2, string n);
    void set_data(string s1, string s2, string n);
};

class bst_tree{
    bst_node* root;
    int csize;
public:
    bst_tree();
    void insert_node(bst_node t);
    void show_inorder();
    bst_node search(string tid);
    void writeinfile();
};
void writelist(bst_node *p);
void menu(){
    cout << "1. Insert new element" << endl;
    cout << "2. Inquire elements" << endl;
    cout << "3. View total list" << endl;
    cout << "4. Exit" << endl;
    cout << "Select a command" << endl;
}

int main()
{
	bst_node temp;
	bst_tree t1;	
    int choice;
    string tmp;
    string rname;
    string fname;
    string rate;
    string key;

    cout << "Handong Food Recommendation List \n" << endl;
    
    ifstream ifs;
    ifs.open("Menulist.txt");
    
    while(!ifs.eof()){
        getline(ifs, tmp);
        vector<string> result = split(tmp, ' ');
        rname = result[0];
        fname = result[1];
        rate = result[2];
        temp.set_data(rname,fname,rate);
        t1.insert_node(temp);
    }
    ifs.close();

    ofstream fout;
    do{
        menu();
        cin >> choice;
        switch (choice)
        {
        case 1:    
            cout << "Insert new element." << endl;
            cout << "Enter Restaurant name, Food Name, Rate : " << endl;
            cin >> rname;
            cin >> fname;
            cin >> rate;
            temp.set_data(rname, fname, rate);	
	        t1.insert_node(temp);
            
            fout.open("Menulist.txt", ios::app);
            fout << "\n" << rname << " " << fname << " " << rate;
            fout.close();  
            
            cout << endl;
            break;
        case 2:
            cout << "Inquire element." << endl;
            cout << "Enter Food name"<< endl;
            cin >> key;
            temp = t1.search(key);
            cout << "\n -- " << key << "'s information ---" << endl;
	        cout << " Restaurant name: "<< temp.rname << endl;
	        cout << " Food Name : "<< temp.fname << endl;
	        cout << " Rate : " << temp.rate << endl;
            cout << endl;
            break;
        case 3:
            cout << "View total list" << endl;
            cout << "Restaurant_name" << " : " << "Food_Name" << " : " << "Rate" << "\n";
            t1.show_inorder();
            cout << endl;
            break;
        }
        if(choice < 1 || choice > 4){
            cout << "Invalid input. Exit the program." << endl;
            break; 
        }

    }while(choice!=4);
    cout << "Exit the program." << endl;
	return 0;
}

bst_node::bst_node(){
    rname = "None";
    fname = "None";
    rate = "None";
}
bst_node::bst_node(string s1, string s2, string n){
    rname = s1;
    fname = s2;
    rate = n;
}  
void bst_node::set_data(string s1, string s2, string n){
    rname = s1;
    fname = s2;
    rate = n;
}
bst_tree::bst_tree(){
    root = NULL;
    csize = 0;
}
void print_inorder(bst_node *p){
    if (p == NULL) 
        return;
    
    print_inorder(p->left);
    cout << p->rname << " : " << p->fname << " : " << p->rate << "\n";
    print_inorder(p->right);
}
void bst_tree::show_inorder(){
    print_inorder(root);
}

bst_node bst_tree::search(string tid){
    bst_node* p;
    p =  root;
    bst_node tmp;

    if(root==NULL){
        
        tmp.set_data("None", "None", "None");
        cout << "The key " << tid << " does not exist.\n";
        return tmp;
    }

    while(1){
        if(p->fname == tid)
            return (*p);
        
        if (p->fname < tid) {
            if (p->right == NULL) {
                // .. 해당노드 없음 처리
                tmp.set_data("None", "None", "None");
                cout << "The key " << tid << " does not exist.\n";
                return tmp;
            }
            else
                p = p->right;
        }
        else {
            if (p->left == NULL) {
                // .. 해당노드 없음 처리
                tmp.set_data("None", "None", "None");
                cout << "The key " << tid << " does not exist.\n";
                return tmp;
            }
            else
                p = p->left;
        }
    }
}

void bst_tree::insert_node(bst_node t){
    bst_node* p;
    bst_node* tmp;

    tmp = new bst_node;
    *tmp = t;
    tmp->left = NULL;
    tmp->right = NULL;

    if(root == NULL){
        root = tmp;
        return;
    }
    p=root;
    while (1) {
        if (p->fname == t.fname) {
            cout << "Insertion Failed : the Key " << t.fname << " already exists." << endl;
            return;
        }
        if (p->fname < t.fname) {
            if (p->right == NULL) {
                p->right = tmp;
                return;
            }
            else
                p = p->right;
            }
        else {
            if (p->left == NULL) {
                p->left = tmp;
                return;
            }
            else
                p = p->left;
        }
    }   
}