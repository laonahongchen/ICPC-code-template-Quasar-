struct Node {
	Node *lc, *rc;
	int r, v, cnt, sz;
	Node() {}
	Node(int _v) {
		v = _v;
		sz = 0;
		cnt = 1;
		r = rand();
		lc = rc = NULL;
	}
	void update();
};

inline int size(Node *o) {
	return o ? o->sz : 0;
}
void Node::update() {
	sz = cnt + size(lc) + size(rc);
}
void rotate_l(Node *&o) {
	Node *k = o->rc;
	o->rc = k->lc;
	k->lc = o;
	o->update();
	k->update();
	o = k;
}
void rotate_r(Node *&o) {
	Node *k = o->lc;
	o->lc = k->rc;
	k->rc = o;
	o->update();
	k->update();
	o = k;
}
void insert(Node *&o, int v) {
	if(o == NULL) {
		o = new Node(v);
	} else if(v < o->v) {
		insert(o->lc, v);
		if(o->lc->r < o->r)
			rotate_r(o);
	} else if(v > o->v) {
		insert(o->rc, v);
		if(o->rc->r < o->r)
			rotate_l(o);
	} else o->cnt++;
	o->update();
}
void remove(Node *&o, int v) { // 删除前请确保v存在
	if(v < o->v) {
		remove(o->lc, v);
	} else if(v > o->v) {
		remove(o->rc, v);
	} else if(o->cnt == 1) {
		if(o->lc == NULL) {
			Node *k = o;
			o = o->rc;
			delete k;
		} else if(o->rc == NULL) {
			Node *k = o;
			o = o->lc;
			delete k;
		} else {
			if(o->lc->r < o->rc->r) {
				rotate_l(o);
				remove(o->lc, v);
			} else {
				rotate_r(o);
				remove(o->rc, v);
			}
		}
	} else o->cnt--;
	if(o) o->update();
}
void merge(Node *&to, Node *from) {
	if(from == NULL) return;
	merge(to, from->lc);
	for(int i = 0; i < from->cnt; ++i)
		insert(to, from->v);
	merge(to, from->rc);
}
void del_tree(Node *&o) {
	if(o == NULL) return;
	del_tree(o->lc);
	del_tree(o->rc);
	delete o;
	o = NULL;
}
int get_rank(Node *o, int v) { // 查询小于等于v的个数
	if(o == NULL) return 0;
	if(v < o->v) return get_rank(o->lc, v);
	else if(v == o->v) return size(o->lc) + o->cnt;
	else return size(o->lc) + o->cnt + get_rank(o->rc, v);
}
