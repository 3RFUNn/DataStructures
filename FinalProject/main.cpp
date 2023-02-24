#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

class RangeTree
{
    struct node
    {
        double point;
        node* left;
        node* right;
        int height;
    };

    node* Xroot;
    node* Yroot;
    bool identifier= true;

    pair<node*,node*> insert(double x,double y, node* pointX , node* pointY)
    {

       if(identifier) {
           if (pointX == NULL) {
               pointX = new node;
               pointX->point = x;
               pointX->height = 0;
               pointX->left = pointX->right = NULL;
           } else if (x < pointX->point) {
               pointX->left = insert(x, y, pointX->left, pointY).first;
               if (height(pointX->left) - height(pointX->right) == 2) {
                   if (x < pointX->left->point)
                       pointX = singleRightRotate(pointX);
                   else
                       pointX = doubleRightRotate(pointX);
               }
           } else if (x > pointX->point) {
               pointX->right = insert(x, y, pointX->right, pointY).first;
               if (height(pointX->right) - height(pointX->left) == 2) {
                   if (x > pointX->right->point)
                       pointX = singleLeftRotate(pointX);
                   else
                       pointX = doubleLeftRotate(pointX);
               }
           }

           pointX->height = max(height(pointX->left), height(pointX->right)) + 1;
       }
       if(!identifier) {
           if (pointY == NULL) {
               pointY = new node;
               pointY->point = y;
               pointY->height = 0;
               pointY->left = pointY->right = NULL;
           } else if (y < pointY->point) {
               pointY->left = insert(x, y, pointX, pointY->left).second;
               if (height(pointY->left) - height(pointY->right) == 2) {
                   if (y < pointY->left->point)
                       pointY = singleRightRotate(pointY);
                   else
                       pointY = doubleRightRotate(pointY);
               }
           } else if (y > pointY->point) {
               pointY->right = insert(x, y, pointX, pointY->right).second;
               if (height(pointY->right) - height(pointY->left) == 2) {
                   if (y > pointY->right->point)
                       pointY = singleLeftRotate(pointY);
                   else
                       pointY = doubleLeftRotate(pointY);
               }
           }

           pointY->height = max(height(pointY->left), height(pointY->right)) + 1;
       }

        return {pointX,pointY};
    }
    node* doubleLeftRotate(node* &t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    node* doubleRightRotate(node* &t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    node* singleRightRotate(node* &t)
    {
        node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(u->left), t->height)+1;
        return u;
    }


    node* singleLeftRotate(node* &t)
    {
        node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(t->right), t->height)+1 ;
        return u;
    }





    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }



    int height(node* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    void inorder(node* t)
    {
        if(t == NULL)
            return;
        inorder(t->left);
        cout<<t->point<<" ";
        inorder(t->right);
    }

public:
    RangeTree()
    {
        Xroot = NULL;
        Yroot = NULL;

    }

    void insert(double x, double y)
    {
            Points.emplace_back(x,y);
       identifier= true;
        Xroot = insert(x,y,Xroot,Yroot).first;
        identifier= false;
        Yroot = insert(x,y,Xroot,Yroot).second;
    }

    vector<pair<double, double> > Points;
};
bool sortbysec(const pair<int,int> &a,
               const pair<int,int> &b)
{
    return (a.second < b.second);
}

int main() {
    RangeTree R;
    double pointPairs, function, inputX, inputY;
    scanf("%lf",&pointPairs);
    vector<pair<double, double> > functions;
    vector<pair<double, double> > javabha;
    vector<double> savings;
    for (int i = 0; i < 2*pointPairs; ++i) {
        double input1;
        scanf("%lf",&input1);
        savings.push_back(input1);

    }
    for (int k = 0; k < pointPairs; ++k) {
        R.insert(savings[k], savings[k+pointPairs]);
    }
    savings.clear();
    scanf("%lf",&function);
    for (int l = 0; l < 2 * function; ++l) {
        scanf("%lf",&inputX);
        scanf("%lf",&inputY);
        functions.emplace_back(inputX, inputY);
    }
    for (int j = 0; j <function ; ++j) {
        bool uzi = false;
        for (int i = 0; i < pointPairs; ++i) {
            if (R.Points[i].first >= functions[2 * j].first && R.Points[i].second >= functions[2 * j].second &&
                R.Points[i].first <= functions[2 * j + 1].first && R.Points[i].second <= functions[2 * j + 1].second) {
                javabha.emplace_back(R.Points[i].first, R.Points[i].second);
                uzi = true;
            }
        }
        if (uzi) {
            sort(javabha.begin(),javabha.end(),sortbysec);
            for (auto &k : javabha) {
                cout << k.first << " ";
            }
            printf("\n");
            for (auto &l : javabha) {
                cout << l.second << " ";
            }
            printf("\n");
        }
        else {
            printf("None\n");
        }
        javabha.clear();
    }
    functions.clear();
    R.Points.clear();



        return 0;

}
