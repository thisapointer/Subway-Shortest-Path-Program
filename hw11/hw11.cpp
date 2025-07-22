#include "subway.h"
#include <fstream> 
int main(int argc, char* argv[])
{
	int numLine;
	int line1, line2;
	string src, dst;
	if (argc != 3) {
		cerr << "Argument Count is " << argc << endl 
			<< "Argument must be " << argc << endl;
		return 1;
	}
	fstream fin(argv[1]);
	if (!fin) {
		cerr << argv[1] << " open failed" << endl;
		return 1;
	}
	fin >> numLine;

	//데이터 받는 과정 
	MapGraph mg;		// 전체 노선도 mg
	for (int i = 0; i < numLine; i++) {
		fin >> line1 >> src >> line2 >> dst;
		Station st1(line1, src), st2(line2, dst);	// 입력받은 두 개 역

		mg.insert(st1); mg.insert(st2);		// 노선도에 입력
		if (src == dst) mg.set(st1, st2, 0.5);	// 만약 이름이 같다면(환승역), 가중치(시간)를 0.5분으로 하여 간선 설정
		else mg.set(st1, st2);		// 아니라면 가중치 1분(디폴트)으로 해서 설정
	}

	fin.close();
	fstream fin2(argv[2]);
	if (!fin2) {
		cerr << argv[2] << " open failed" << endl;
		return 1;
	}
	fin2 >> line1 >> src;
	fin2 >> line2 >> dst;
	fin2.close();
	
	//결과 출력 
	Station start(line1, src), dest(line2, dst);		// 시점 역, 종점 역
	mg.shortestTime(start, dest);		// 최단 시간 경로 계산 및 출력

	return 0;
}