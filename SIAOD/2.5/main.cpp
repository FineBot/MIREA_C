#include "tree.cpp"

int main(){
    setlocale(LC_ALL,"rus");
    tree tr;

    int cId=0;
    int cParentId=0;
    int cWeight=0;
    cout <<"¬водите id вершин, их родител€ и вес: [id] [parentId] [weight]\n";

    while(cId!=-1){
        cin>>cId;
        if(cId==-1)
            break;
        cin>>cParentId;
        cin >> cWeight;
        tr.add(cId, cParentId,cWeight);
    }

    tr.echo(tr.root,0);
    cout<<endl;
    tr.findWay("/"+std::to_string(tr.root->id),0,tr.root,6);
    return 0;
}
