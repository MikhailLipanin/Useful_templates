struct node{
    node *l, *r;
    int x, y;
    int sum, sz;
    node(int _x){
        l = r = nullptr;
        x = _x;
        y = (rand() << 16) + rand(); 
        sum = _x;
        sz = 1;
    }
};
int get_sz(node *a){
    return a ? a->sz : 0;
}
int get_sum(node *a){
    return a ? a->sum : 0;
}
void upd(node *a){
    if (!a) return;
    a->sz = 1 + get_sz(a->l) + get_sz(a->r);
    a->sum = a->x + get_sum(a->l) + get_sum(a->r);
}

node* Merge(node *a, node *b){
    if (!a) return b;
    if (!b) return a;
    if (a->y > b->y){
        a->r = Merge(a->r, b);
        upd(a);
        return a;
    }
    else{
        b->l = Merge(a, b->l);
        upd(b);
        return b;
    }
}

pair <node*, node*> Split_k(node *a, int k){
    if (!a) return {nullptr, nullptr};
    if (get_sz(a->l) < k){
        auto tmp = Split_k(a->r, k - get_sz(a->l) - 1);
        a->r = tmp.first;
        upd(a);
        return {a, tmp.second};
    }
    else{
        auto tmp = Split_k(a->l, k);
        a->l = tmp.second;
        upd(a);
        return {tmp.first, a};
    }
}

node* root = nullptr;
