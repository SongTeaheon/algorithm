/*
 작성자 : 송태헌
 작성일시 : 20200610
 문제출처 : https://algospot.com/judge/problem/read/TRAVERSAL
 문제유형 : 자료구조, 트리
 */



#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

class Node{
public:
    int data;
    Node* left;
    Node* right;
    
    Node() {
        this->left = nullptr;
        this->right = nullptr;
    }
    
    ~Node() {
        if(left != nullptr) delete left;
        if(right != nullptr) delete right;
    }

};

int N;
vector<int> preVec;
vector<int> iptMidOrder;


void inputFn() {
    preVec.clear();
    iptMidOrder.clear();
    
    cin >> N;
    
    //전위
    for(int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        preVec.push_back(temp);
    }
    //중위
    for(int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        iptMidOrder.push_back(temp);
    }
}

int findRoot(const vector<int>& midVec){//mid중에서 pre에 가장 먼저 나오는 값 -> root
    for(int i = 0; i < preVec.size(); i++) {
        if(find(midVec.begin(), midVec.end(), preVec[i]) != midVec.end()){
            return preVec[i];
        }
    }
    return -1;//나오면 안되는값!
}

int getIdx(const vector<int>& midVec, int data){
    int ret = -1;
    for(int i = 0; i < midVec.size(); i++) {
        if(midVec[i] == data){
            ret = i;
            break;
        }
    }
    return ret;
}

Node* findTree(vector<int> midVec) {
    if(midVec.empty()) return nullptr;
    
    Node* newNode = new Node();
    
    int data = findRoot(midVec);//mid중에서 pre에 가장 먼저 나오는 값 -> root
    newNode -> data = data;
    
    int idx = getIdx(midVec, data);//해당 데이터가 중위순위에서 몇 번째에 있는지 확인
    
    vector<int> leftMidVec;
    vector<int> rightMidVec;
    for(int i = 0; i < idx; i++) {//왼쪽
        leftMidVec.push_back(midVec[i]);
    }
    for(int i = idx+1; i < midVec.size(); i++) {//오른쪽.
        rightMidVec.push_back(midVec[i]);
    }
    
    newNode ->left = findTree(leftMidVec);
    newNode -> right = findTree(rightMidVec);
    

    return newNode;
}

void postOrder(Node* root) {
    if(root == nullptr) return;
    
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

int main() {
    
    int C;
    cin >> C;
    
    for(int test_case = 1; test_case <= C; test_case++) {
        inputFn();
        Node *root = findTree(iptMidOrder);
        //길찾기
        postOrder(root);
        cout << endl;
    }
    
    
    return 0;
}
