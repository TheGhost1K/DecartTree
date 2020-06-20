#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;
 
inline int gcd(int a, int b){
        return b ? gcd(b,a%b) : a;
}
 
struct item {
        int key, prior, gcd;
        item * l, * r;
        item() { }
        item (int key, int prior) : key(key), prior(prior), l(NULL), r(NULL), gcd(key) { }
};
typedef item * pitem;
 
int gcd (pitem it) {
        return it ? it->gcd : 0;
}
 
void upd_gcd (pitem it) {
        if (it)
                it->gcd = gcd(gcd(gcd(it->l),gcd(it->r)),it->key);
}
 
void split (pitem t, int key, pitem & l, pitem & r) {
        if (!t)
                l = r = NULL;
        else if (key < t->key)
                split (t->l, key, l, t->l),  r = t;
        else
                split (t->r, key, t->r, r),  l = t;
        upd_gcd(t);
}
 
void insert (pitem & t, pitem it) {
        if (!t)
                t = it;
        else if (it->prior > t->prior)
                split (t, it->key, it->l, it->r),  t = it;
        else
                insert (it->key < t->key ? t->l : t->r, it);
        upd_gcd(t);
}
 
void merge (pitem & t, pitem l, pitem r) {
        if (!l || !r)
                t = l ? l : r;
        else if (l->prior > r->prior)
                merge (l->r, l->r, r),  t = l;
        else
                merge (r->l, l, r->l),  t = r;
        upd_gcd(t);
}
 
void erase (pitem & t, int key) {
        if (t->key == key)
                merge (t, t->l, t->r);
        else
                erase (key < t->key ? t->l : t->r, key);
        upd_gcd(t);
}
 
int priorities[100005];
 
int main(){
#ifdef KP_HOME
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
#endif
        int t;
        scanf("%d\n",&t);
        pitem root = NULL;
        for (int i=0; i<t; ++i) priorities[i] = i;
        random_shuffle(priorities, priorities+t);
 
        while (t--){
                char cmd;
                int x;
                scanf("%c %d\n",&cmd,&x);
                pitem it;
                if (cmd == '+'){
                        it = new item(x,priorities[t]);
                        insert(root, it);
                } else if (cmd == '-'){
                        erase(root, x);
                } else assert(false);
 
                printf("%d\n", root == NULL ? 1 : root->gcd);
        }
        return 0;
}
