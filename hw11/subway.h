#ifndef SUBWAY_H
#define SUBWAY_H

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Station {		// ���� ��Ÿ���� Ŭ����(Node)
	int line;				// �뼱
	string name;		// �� �̸�
public:
	Station(int n = 0, string s = "") : line(n), name(s) {}
	string getName() { return name; }	// �� �̸� ����
	friend bool operator==(Station& st1, Station& st2) {	
		return st1.line == st2.line && st1.name == st2.name;		// �뼱�� �̸��� ��� ���� ��츸 ������ ������ ���
	}
};
class MapGraph {		// ��ü �뼱�� ����ϴ� Ŭ����(�뼱��)
	int numV;				// ���� ����
	vector<vector<double> > length;	// �� �� �̵��ð� (���� ���)
	vector<Station> st_list;	// �� ����Ʈ
	vector<double> time;		// ������������ �ּ� �ð��� ǥ���� time
	vector<bool> s;				// �� ���� Ž�� �ϷḦ ǥ���� s �迭 ����
public:
	MapGraph() { numV = 0; }
	void insert(Station&);		// �� ����Ʈ�� �Է��� ���� �߰�
	int getIndexOfStation(Station&);		// ���� �뼱�� ���� ���� index �����ϴ� �Լ�
	void set(Station&, Station&, double time_ip = 1);			// �� ���� ����, ����ġ(�ð�) ����	// ����ġ(�ð�) �⺻�� 1��
	void shortestTime(Station&, Station&);	// Dijkstra �˰����� �̿��� �ּ� �ð� Ž��
};

#endif