#include "subway.h"

void MapGraph::insert(Station& ip) {		// 역 리스트에 입력한 역을 추가
	for (int i = 0; i < st_list.size(); i++)
		if (st_list[i] == ip) return;		// 역 리스트에 이미 있으면 함수 종료

	st_list.push_back(ip);		// 역 삽입
	numV++;							// 역 개수 갱신

	for (auto& v : length)		// 인접 행렬에서 해당 노드의 행과 열에 무한대 입력
		v.push_back(INFINITY);		// 열에 무한대 입력
	length.push_back(vector<double>(numV, INFINITY));		// 행에 무한대 입력
	length[numV - 1][numV - 1] = 0;		// 자기 자신으로의 간선은 가중치 0
}

int MapGraph::getIndexOfStation(Station& ip) {		// 역의 노선도 상의 고유 index 리턴하는 함수
	for (int i = 0; i < numV; i++)
		if (st_list[i] == ip) return i;
	return -1;		// 없을 경우 -1 리턴 (디버깅용)
}

void MapGraph::set(Station& st1, Station& st2, double time_ip) {		// 역 간의 간선, 가중치(시간) 설정
	int id1 = getIndexOfStation(st1);		// st1의 index
	int id2 = getIndexOfStation(st2);		// st2의 index
	if (id1 == -1 || id2 == -1) return;		// 하나라도 -1일 경우 리턴 (디버깅용)

	length[id1][id2] = length[id2][id1] = time_ip;		// 무방향 그래프이므로 대칭행렬
}

void MapGraph::shortestTime(Station& start, Station& dest) {		// Dijkstra 알고리즘을 이용해 최소 시간 탐색
	// 가중치가 모두 양수이므로 Dijkstra 알고리즘을 이용
	// edge 수가 충분히 많다고 판단하여 인접행렬을 이용

	int idx_srt = getIndexOfStation(start);		// 시점의 인덱스
	int idx_dst = getIndexOfStation(dest);		// 종점의 인덱스
	if (idx_srt == -1 || idx_dst == -1) {				// 하나라도 -1일 경우 리턴 (디버깅용)
		cout << "index 못 찾음" << endl;
		return;
	}

	time.resize(numV);				// time 크기 재설정
	s.resize(numV, false);			// s 크기 재설정, 아직 아무데도 방문하지 않았으므로 false로 초기화
	vector<int> prev(numV, -1);		// 역추적을 위해 이전 역을 저장하는 배열
	for (int i = 0; i < numV; i++) 
		time[i] = length[idx_srt][i];		// time은 length로 초기화

	s[idx_srt] = true;		// 시점은 방문 완료

	int u = -1;			// 탐색할 역의 인덱스
	for (int i = 0; i < numV; i++) {	
		u = -1;			// -1로 초기화
		for (int j = 0; j < numV; j++)		// u를 찾기 위한 for문
			if (!s[j] && (u == -1 || time[u] > time[j]))	// time 중에서 최소 && 방문하지 않은 역
				u = j;
		if (u == -1) break;		// 더 방문할 역이 없다면 for문 탈출
		s[u] = true;		// 이제 방문했으므로 s 배열 값 true로 변경

		for (int j = 0; j < numV; j++)
			if (!s[j] && time[u] + length[u][j] < time[j]) {		// 기록된 최소 시간보다 돌아가는 경로가 더 짧다면
				time[j] = time[u] + length[u][j];		// 역 별 최소 시간 time 업데이트
				prev[j] = u;		// 경로 추적을 위해 이전 역 기록
			}
	}
	double dst_time = time[idx_dst];		// 목적지까지 걸리는 시간(분)

	if (prev[idx_dst] == -1) {		// 만약 경로 없으면 리턴 (디버깅용)
		cout << "목적지까지의 경로 없음" << endl;
		return;
	}

	vector<int> path;		// 최단 경로를 표시할 배열(역순)
	for (int at = idx_dst; at != -1; at = prev[at])		// 종점에서 시작해서 시점으로 역추적
		path.push_back(at);				// path 배열에 추가
	path.push_back(idx_srt);			// 마지막으로 시점까지 추가

	int idx_mid = idx_srt;		// 중점의 인덱스, 출발지 인덱스로 초기화
	string last = "";					// 직전 역의 이름을 표시할 변수
	for (int j = path.size() - 1; j >= 0; j--) {		// path 배열의 역순(정방향)으로 iterate
		int i = path[j];				// path 값
		string s = st_list[i].getName();	// 역의 이름

		if (s != last) {					// 중복 출력 방지
			cout << s << '\n';		// 최단 경로의 방문 역 출력
			last = s;					// last 갱신
		}

		if (time[idx_mid] < dst_time / 2)			// 목적지까지 최소 소요 시간의 절반과 비교 
			idx_mid = path[j];		// 아직 더 작다면 다음 역으로 하나씩 전진
	}

	cout << (int)dst_time << ':' << (dst_time - (int)dst_time == 0 ? "00" : "30") << '\n';		// 목적지까지 최소 소요 시간 출력(mm:ss)

	// 중점과 이를 기점으로 한 전과 후 이동 시간
	cout << st_list[idx_mid].getName() << '\n';		// 중점 출력
	double foretime = time[idx_mid];				// 시점 -> 중점 소요 시간
	double posttime = dst_time - foretime;	// 중점 -> 종점 소요 시간
	cout << (int)foretime << ':' << (foretime - (int)foretime == 0 ? "00" : "30") << '\n';			// m:ss로 출력
	cout << (int)posttime << ':' << (posttime - (int)posttime == 0 ? "00" : "30") << '\n';		// m:ss로 출력
}