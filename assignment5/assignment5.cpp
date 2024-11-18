#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <class T>
using ELEM = vector<T>;

template <class T>
using VEC = vector<ELEM<T>>;

template <class T>
using action_t = T(*) (int);

template <class T>
using pred_t = bool (*) (T);

template <class T>
using map_t = T(*) (T, T);

template <class T> void initVec(VEC<T>& v, ELEM<T>&& cons) {
	v.resize(cons.size(), ELEM<T>(1));
	for (int i = 0; i < v.size(); i++)
		for (int j = 0; j < v[i].size(); j++) {
			v[i][j] = cons[i];
		}
}

template <class T> void printElem(const ELEM<T>& v) {
	if (v.size() > 1) cout << "(";
	for (auto i : v)
		cout << i << " ";
	if (v.size() > 1) cout << ")";
}

template <class T> void printVec(VEC<T>& v) {
	cout << "[ ";
	int i = 0;
	int end = v.size();
	for (auto e : v) {
		i++;
		printElem(e);
		if (i < end) cout << ", ";
	}
	cout << " ]" << endl;
}

template<class T> VEC<T> zip(VEC<T>& v, VEC<T>& w) {
	int length = v.size();
	//this function assumes that vector w has the same length and width as vector v so that they can be zipped together

	VEC<T> zippedVec;

	for (int i = 0; i < length; i++) {
		ELEM<T> current;
		int width = v[1].size();
		for (int j = 0; j < width; j++) {
			current.push_back(v[i][j]);
		}
		for (int j = 0; j < width; j++) {
			current.push_back(w[i][j]);
		}
		zippedVec.push_back(current);
	}
	return zippedVec;
}

//this function generates a vector of a given length. Each element is the square of its index
template <class T> VEC<T> generate(int N, action_t<T> f) {
	VEC<T> sqVec;
	sqVec.resize(N, ELEM<T>(1));
	for (int i = 0; i < N; i++) { //loops the amount of times specified when called
		for (int j = 0; j < 1; j++) {
			sqVec[i][j] = f(i); //the current point in the square vector will be assigned the value of its index's square
		}
	}
	return sqVec;
}

template<class T> VEC<T> filter(VEC<T>& v, pred_t<T> f) {
	VEC<T> newVec;
	ELEM<T> holder;

	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			if (f(v[i][j])) {
				holder.push_back(v[i][j]);
			}
		}
	}

	newVec.resize(holder.size(), ELEM<T>(1));
	for (int i = 0; i < newVec.size(); i++) {
		newVec[i][0] = holder[i];
	}
	return newVec;
}

template<class T> VEC<T> map(VEC<T>& v, action_t<T> f) {
	VEC<T> newVec;
	newVec.resize(v.size(), ELEM<T>(1));
	for (int i = 0; i < newVec.size(); i++) {
		for (int j = 0; j < 1; j++) {
			newVec[i][j] = f(v[i][j]);
		}
	}
	return newVec;
}

template<class T> ELEM<T> reduce(VEC<T>& v, map_t<T> f, ELEM<T> ident) {
	T ans = ident[0];
	ELEM<T> myElem;
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			ans = f(ans, v[i][j]);
		}
	}
	myElem.push_back(ans);
	return myElem;
}

template <typename T> T k(T i, T j) { //returns the sum of two arguments
	return i + j;
}

int f(int i) { //returns the square of an argument
	return i * i;
}

bool g(int  i) { //returns true if an argument is greater than zero
	if (i > 0) {
		return true;
	}
	return false;
}

int h(int i) { //returns 1 if an argument is greater than zero
	if (i > 0) {
		return 1;
	}
	return 0;
}

void stars() { //prints ten stars to separate lines
	for (int i = 0; i < 10; i++) {
		cout << '*';
	}
	cout << endl;
}

void money() { //prints ten dollar signs to separate lines
	for (int i = 0; i < 10; i++) {
		cout << '$';
	}
	cout << endl;
}

int main() {
	VEC<int> v;
	initVec(v, ELEM<int>{1, 2, 3, 4});
	printVec(v);
	stars();

	VEC<int> w;
	initVec(w, ELEM<int>{-1, 3, -3, 4});
	printVec(w);
	stars();

	VEC<int> z = zip(v, w);
	printVec(z);
	stars();

	VEC<int> x = zip(z, z);
	printVec(x);
	stars();

	VEC<int> a = generate(10, f);
	printVec(a);
	stars();

	VEC<int> y = filter(w, g);
	printVec(y);
	stars();

	VEC<int> u = map(w, h);
	printVec(u);
	stars();

	ELEM<int> e = reduce(u, k, ELEM<int>{0});
	printElem(e);
	cout << endl;

	money();
	VEC<string> ws;
	initVec(ws, ELEM<string>{"hello", "there", "franco", "carlacci"});
	printVec(ws);

	ELEM<string> es = reduce(ws, k, ELEM<string>{""});
	printElem(es);
	cout << endl;

	VEC<char> wc;
	initVec(wc, ELEM<char>{'a', 'b', 'c', 'd'});
	money();
	printVec(wc);

	ELEM<char> ec = reduce(wc, k, ELEM<char>{' '});
	money();
	printElem(ec);

	return 0;
}