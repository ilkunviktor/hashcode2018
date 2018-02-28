#include <chrono>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <cmath>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <memory>
#include <numeric>
#include <filesystem>
#include <functional>
#include <iterator>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#define ptr		std::shared_ptr
#define make	std::make_shared

using namespace std;

using uint = uint64_t;

template<typename T>
class CloneFunctor {
public:
	ptr<T> operator()(ptr<T> elem)
	{
		ptr<T> elemNew = make<T>();
		*elemNew = *elem;
		return elemNew;
	}
};

int main()
{
	string inPath = "../../in";
	string outPath = "../../out";
	uint64_t scoreTotal = 0;
	uint64_t millisecondsTotal = 0;

	

	for (const auto& taskPath : experimental::filesystem::v1::directory_iterator(inPath))
	{
		uint millisecondsFile = 0;
		stringstream ss;
		ss << taskPath;
		string filePathIn = ss.str();

		size_t fileNameStart = filePathIn.find_last_of('\\');
		size_t fileNameEnd = filePathIn.find_last_of('.');
		string fileName = filePathIn.substr(fileNameStart + 1, fileNameEnd - fileNameStart - 1);

		string filePathOut = outPath + "/" + fileName + ".out";


		bool isFactorsIterate = true;


		struct Factors
		{
			float f1 = 0.5f;
			float f2 = 0.5f;
		};

		map<string, Factors> factorsGlobal;// = { {"dc", {0.49f, 0.51f}} };


		float factorsStep = isFactorsIterate ? 0.01f : 1.f;

		uint scoreBest = 0;
		Factors factorsBest;
		
		for (float factorCur = 0.f; factorCur < 1.f; factorCur += factorsStep)
		{
			Factors factors;
			auto foundFileFactorsIt = factorsGlobal.find(fileName);

			if (foundFileFactorsIt != factorsGlobal.end())
			{
				factors = foundFileFactorsIt->second;
			}
			else
			{
				factors.f1 = factorCur;
				factors.f2 = 1.f - factorCur;
			}

			chrono::time_point<std::chrono::system_clock> timeStart =
				chrono::system_clock::now();

			// input
			ifstream fileIn;
			fileIn.open(filePathIn);
			assert(fileIn.is_open());

			//fileIn >> 

			fileIn.close();

			// solve
			


			// score

			uint score = 0;



			if (!isFactorsIterate || score > scoreBest)
			{
				scoreBest = score;
				factorsBest.f1 = factors.f1;
				factorsBest.f2 = factors.f2;

				// output
				ofstream fileOut;
				fileOut.open(filePathOut);
				assert(fileOut.is_open());

				//fileOut <<
				
				fileOut.close();
			}

			// timing
			chrono::time_point<std::chrono::system_clock> timeEnd =
				chrono::system_clock::now();
			chrono::milliseconds millisec = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart);
			uint millisecondsPart = millisec.count();
			millisecondsFile += millisecondsPart;

			if (isFactorsIterate)
			{
				cout << "file part: " << fileName << endl;
				cout << "score part: " << score << endl;
				cout << "factors.f1: " << factors.f1 << endl;
				cout << "factors.f2: " << factors.f2 << endl;
				cout << "time part file(ms): " << to_string(millisecondsPart) << endl << endl;
			}
		}

		scoreTotal += scoreBest;
		millisecondsTotal += millisecondsFile;
		cout << "file: " << fileName << endl;
		cout << "score: " << scoreBest << endl;
		cout << "time file(ms): " << millisecondsFile << endl;

		if (isFactorsIterate)
		{
			cout << "factorsBest.f1: " << factorsBest.f1 << endl;
			cout << "factorsBest.f2: " << factorsBest.f2 << endl;
		}

		cout << endl;
	}

	cout << "scoreTotal: " << scoreTotal << endl;
	cout << "time total(ms): " << millisecondsTotal << endl << endl;
	system("pause");

	return 0;
}