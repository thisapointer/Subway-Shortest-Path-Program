#include "subway.h"

void MapGraph::insert(Station& ip) {		// �� ����Ʈ�� �Է��� ���� �߰�
	for (int i = 0; i < st_list.size(); i++)
		if (st_list[i] == ip) return;		// �� ����Ʈ�� �̹� ������ �Լ� ����

	st_list.push_back(ip);		// �� ����
	numV++;							// �� ���� ����

	for (auto& v : length)		// ���� ��Ŀ��� �ش� ����� ��� ���� ���Ѵ� �Է�
		v.push_back(INFINITY);		// ���� ���Ѵ� �Է�
	length.push_back(vector<double>(numV, INFINITY));		// �࿡ ���Ѵ� �Է�
	length[numV - 1][numV - 1] = 0;		// �ڱ� �ڽ������� ������ ����ġ 0
}

int MapGraph::getIndexOfStation(Station& ip) {		// ���� �뼱�� ���� ���� index �����ϴ� �Լ�
	for (int i = 0; i < numV; i++)
		if (st_list[i] == ip) return i;
	return -1;		// ���� ��� -1 ���� (������)
}

void MapGraph::set(Station& st1, Station& st2, double time_ip) {		// �� ���� ����, ����ġ(�ð�) ����
	int id1 = getIndexOfStation(st1);		// st1�� index
	int id2 = getIndexOfStation(st2);		// st2�� index
	if (id1 == -1 || id2 == -1) return;		// �ϳ��� -1�� ��� ���� (������)

	length[id1][id2] = length[id2][id1] = time_ip;		// ������ �׷����̹Ƿ� ��Ī���
}

void MapGraph::shortestTime(Station& start, Station& dest) {		// Dijkstra �˰����� �̿��� �ּ� �ð� Ž��
	// ����ġ�� ��� ����̹Ƿ� Dijkstra �˰����� �̿�
	// edge ���� ����� ���ٰ� �Ǵ��Ͽ� ��������� �̿�

	int idx_srt = getIndexOfStation(start);		// ������ �ε���
	int idx_dst = getIndexOfStation(dest);		// ������ �ε���
	if (idx_srt == -1 || idx_dst == -1) {				// �ϳ��� -1�� ��� ���� (������)
		cout << "index �� ã��" << endl;
		return;
	}

	time.resize(numV);				// time ũ�� �缳��
	s.resize(numV, false);			// s ũ�� �缳��, ���� �ƹ����� �湮���� �ʾ����Ƿ� false�� �ʱ�ȭ
	vector<int> prev(numV, -1);		// �������� ���� ���� ���� �����ϴ� �迭
	for (int i = 0; i < numV; i++) 
		time[i] = length[idx_srt][i];		// time�� length�� �ʱ�ȭ

	s[idx_srt] = true;		// ������ �湮 �Ϸ�

	int u = -1;			// Ž���� ���� �ε���
	for (int i = 0; i < numV; i++) {	
		u = -1;			// -1�� �ʱ�ȭ
		for (int j = 0; j < numV; j++)		// u�� ã�� ���� for��
			if (!s[j] && (u == -1 || time[u] > time[j]))	// time �߿��� �ּ� && �湮���� ���� ��
				u = j;
		if (u == -1) break;		// �� �湮�� ���� ���ٸ� for�� Ż��
		s[u] = true;		// ���� �湮�����Ƿ� s �迭 �� true�� ����

		for (int j = 0; j < numV; j++)
			if (!s[j] && time[u] + length[u][j] < time[j]) {		// ��ϵ� �ּ� �ð����� ���ư��� ��ΰ� �� ª�ٸ�
				time[j] = time[u] + length[u][j];		// �� �� �ּ� �ð� time ������Ʈ
				prev[j] = u;		// ��� ������ ���� ���� �� ���
			}
	}
	double dst_time = time[idx_dst];		// ���������� �ɸ��� �ð�(��)

	if (prev[idx_dst] == -1) {		// ���� ��� ������ ���� (������)
		cout << "������������ ��� ����" << endl;
		return;
	}

	vector<int> path;		// �ִ� ��θ� ǥ���� �迭(����)
	for (int at = idx_dst; at != -1; at = prev[at])		// �������� �����ؼ� �������� ������
		path.push_back(at);				// path �迭�� �߰�
	path.push_back(idx_srt);			// ���������� �������� �߰�

	int idx_mid = idx_srt;		// ������ �ε���, ����� �ε����� �ʱ�ȭ
	string last = "";					// ���� ���� �̸��� ǥ���� ����
	for (int j = path.size() - 1; j >= 0; j--) {		// path �迭�� ����(������)���� iterate
		int i = path[j];				// path ��
		string s = st_list[i].getName();	// ���� �̸�

		if (s != last) {					// �ߺ� ��� ����
			cout << s << '\n';		// �ִ� ����� �湮 �� ���
			last = s;					// last ����
		}

		if (time[idx_mid] < dst_time / 2)			// ���������� �ּ� �ҿ� �ð��� ���ݰ� �� 
			idx_mid = path[j];		// ���� �� �۴ٸ� ���� ������ �ϳ��� ����
	}

	cout << (int)dst_time << ':' << (dst_time - (int)dst_time == 0 ? "00" : "30") << '\n';		// ���������� �ּ� �ҿ� �ð� ���(mm:ss)

	// ������ �̸� �������� �� ���� �� �̵� �ð�
	cout << st_list[idx_mid].getName() << '\n';		// ���� ���
	double foretime = time[idx_mid];				// ���� -> ���� �ҿ� �ð�
	double posttime = dst_time - foretime;	// ���� -> ���� �ҿ� �ð�
	cout << (int)foretime << ':' << (foretime - (int)foretime == 0 ? "00" : "30") << '\n';			// m:ss�� ���
	cout << (int)posttime << ':' << (posttime - (int)posttime == 0 ? "00" : "30") << '\n';		// m:ss�� ���
}