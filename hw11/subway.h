#ifndef SUBWAY_H
#define SUBWAY_H

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Station {		// 역을 나타내는 클래스(Node)
	int line;				// 노선
	string name;		// 역 이름
public:
	Station(int n = 0, string s = "") : line(n), name(s) {}
	string getName() { return name; }	// 역 이름 리턴
	friend bool operator==(Station& st1, Station& st2) {	
		return st1.line == st2.line && st1.name == st2.name;		// 노선과 이름이 모두 같은 경우만 동일한 역으로 취급
	}
};
class MapGraph {		// 전체 노선을 기록하는 클래스(노선도)
	int numV;				// 역의 개수
	vector<vector<double> > length;	// 역 간 이동시간 (인접 행렬)
	vector<Station> st_list;	// 역 리스트
	vector<double> time;		// 목적지까지의 최소 시간을 표시할 time
	vector<bool> s;				// 역 별로 탐색 완료를 표시할 s 배열 생성
public:
	MapGraph() { numV = 0; }
	void insert(Station&);		// 역 리스트에 입력한 역을 추가
	int getIndexOfStation(Station&);		// 역의 노선도 상의 고유 index 리턴하는 함수
	void set(Station&, Station&, double time_ip = 1);			// 역 간의 간선, 가중치(시간) 설정	// 가중치(시간) 기본값 1분
	void shortestTime(Station&, Station&);	// Dijkstra 알고리즘을 이용해 최소 시간 탐색
};

#endif