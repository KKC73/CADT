#include <iostream>
#include <fstream>
using namespace std;
struct Element{
    string data;
    Element *next;
};
struct MyQueue{
    int n;
    Element *front;
    Element *rear;
};
MyQueue* createEmptyQueue(){
    MyQueue *mq;
    mq = new MyQueue;
    mq->n = 0;
    mq->front = NULL;
    mq->rear = NULL;
    return mq;
}
void enqueue(MyQueue *q, string newData){
    Element *e;
    e = new Element;
    e->data = newData;
    e->next = NULL;

    if(q->n == 0){
        q->front = e;
        q->rear = e;
    } else{
        q->rear->next = e;
        q->rear = e;
    }
    q->n = q->n + 1;
}
string dequeue(MyQueue *q){
    Element *e;
    string temp;
    if(q->n == 0){
        return "Can't dequeue. Data underflow.";
    } else{
        e = q->front;
        temp = e->data;
        q->front = q->front->next;
        delete e;
        q->n = q->n + 1;
    }
    return temp;
}
void displayQueue(MyQueue *q){
    Element *tmp;
    tmp = q->front;
    while(tmp!=NULL){
        cout << tmp->data << endl;
        tmp = tmp->next;
    }
    cout << endl;
}

int isDataIn(MyQueue *q, string data){
    Element *tmp;
    tmp = q->front;
    if(q->n == 0){
        return 0;
    }
    while(tmp!=NULL){
        if(!data.compare(tmp->data)){
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}
