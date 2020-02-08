#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <fstream>
#include <iomanip>      
#include <cstdlib>
#include <ctime>
#include <math.h> 
#include <deque>  

#define FPS 60
#define SPEED 0.5
#define STABILIZER 1
#define ELASTICITY 1
#define timestep 1.0f / FPS

using namespace std;

void printInstructions() {
	cout << "\n----- CONTROLS -----" << endl;
	cout << "H for more Help" << endl;
	cout << "\n----- PLAYER 1 -----" << endl;
	cout << "W: Forward" << endl;
	cout << "A: Rotate Left" << endl;
	cout << "S: Backward" << endl;
	cout << "D: Rotate Right" << endl;
	cout << "F: Shoot" << endl;
	cout << "\n----- PLAYER 2 -----" << endl;
	cout << "Arrow Up: Forward" << endl;
	cout << "Arrow Left: Rotate Left" << endl;
	cout << "Arrow Down: Backward" << endl;
	cout << "Arrow Right: Rotate Right" << endl;
	cout << "ENTER Key: Shoot" << endl;
	cout << "------------------------" << endl;
}

int main( void ) {
	srand(time(NULL));

	sf::Font font;
	if(!font.loadFromFile("comic.ttf")) {
		cout<<"Error loading font"<<endl;
		system("pause");
	}

	sf::Music OST;
	if (!OST.openFromFile("audio/tenks-OST.wav")) {
		cout << "Failed to load music" << endl;
		return -1;
	}

	sf::SoundBuffer rangeBuffer;
	if (!rangeBuffer.loadFromFile("audio/mine warning.wav")) {
		cout << "error w range buffer" << endl;
		return -1;
	}
	
	sf::SoundBuffer explodBuffer;
	if (!explodBuffer.loadFromFile("audio/mine explosion.wav")) {
		cout << "error w explosion buffer" << endl;
		return -1;
	}

	sf::SoundBuffer pewBuffer;
	if (!pewBuffer.loadFromFile("audio/bullet.wav")) {
		cout << "error w pewpew buffer" << endl;
		return -1;
	}

	//Read from file segment
	int N = 12;
	float R = 0;
	float M = 0;
	int width = 0;
	int height = 0;
	string colorTheme, mode;
	sf::Color christmasColor1(83, 175, 64);
	sf::Color christmasColor2(212, 18, 16);
	sf::Color christmasColorO(184, 134, 11);
	sf::Color neonColor1(56, 255, 18);
	sf::Color neonColor2(255, 0, 227);
	sf::Color neonColorO(25, 0, 160);
	int P[N];
	//int X[M];
	int Px[N];
	int Py[N];
	int Rx = 0;
	int Ry = 0;
	int NoPoints = 8;
	int coordX[NoPoints];
	int coordY[NoPoints];
	int midx = 0;
	int midy = 0;


	printInstructions();

	int mapNo = 0;
	cout << "Enter a map number: " << endl;
	cin >> mapNo;

	ifstream file_reader;

	if (mapNo == 1) {
		file_reader.open("map1.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
				getline(file_reader, line1, ':') >> N;
				getline(file_reader, line2, ':') >> colorTheme; 
				getline(file_reader, line3, ':') >> mode;
				getline(file_reader, line4, ':') >> width >> height;
				for(int i = 0; i < N; i++) {
					file_reader >> Px[i] >> Py[i];
					cout << Px[i] << " " << Py[i] << endl;
				} 
				getline(file_reader, line5, ':') >> R;
				getline(file_reader, line6, ':') >> M;
				getline(file_reader, line7, ':') >> Rx >> Ry;
				getline(file_reader, line8, ':') >> NoPoints;
				for(int i = 0; i < NoPoints; i++) {
					file_reader >> coordX[i] >> coordY[i];
				}
				getline(file_reader, line9, ':') >> midx >> midy;
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 2) {
		file_reader.open("map2.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			//while (!file_reader.eof()) {
				getline(file_reader, line1, ':') >> N;
				getline(file_reader, line2, ':') >> colorTheme; 
				getline(file_reader, line3, ':') >> mode;
				getline(file_reader, line4, ':') >> width >> height;
				for(int i = 0; i < N; i++) {
					file_reader >> Px[i] >> Py[i];
					cout << Px[i] << " " << Py[i] << endl;
				} 
				getline(file_reader, line5, ':') >> R;
				getline(file_reader, line6, ':') >> M;
				getline(file_reader, line7, ':') >> Rx >> Ry;
				// getline(file_reader, line5, ':') >> M;
				// for(int i = 0; i < M; i++) {
				// 	file_reader >> Mx[i] >> My[i];
				// 	cout << Mx[i] << " " << My[i] << endl;
				// }
				getline(file_reader, line8, ':') >> NoPoints;
				for(int i = 0; i < NoPoints; i++) {
					file_reader >> coordX[i] >> coordY[i];
				}
				getline(file_reader, line9, ':') >> midx >> midy;
			//}
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 3) {
		file_reader.open("map3.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			//while (!file_reader.eof()) {
				getline(file_reader, line1, ':') >> N;
				getline(file_reader, line2, ':') >> colorTheme; 
				getline(file_reader, line3, ':') >> mode;
				getline(file_reader, line4, ':') >> width >> height;
				for(int i = 0; i < N; i++) {
					file_reader >> Px[i] >> Py[i];
					cout << Px[i] << " " << Py[i] << endl;
				} 
				getline(file_reader, line5, ':') >> R;
				getline(file_reader, line6, ':') >> M;
				getline(file_reader, line7, ':') >> Rx >> Ry;
				// getline(file_reader, line5, ':') >> M;
				// for(int i = 0; i < M; i++) {
				// 	file_reader >> Mx[i] >> My[i];
				// 	cout << Mx[i] << " " << My[i] << endl;
				// }
				getline(file_reader, line8, ':') >> NoPoints;
				for(int i = 0; i < NoPoints; i++) {
					file_reader >> coordX[i] >> coordY[i];
				}
				getline(file_reader, line9, ':') >> midx >> midy;
			//}
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 4) {
		file_reader.open("map4.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			//while (!file_reader.eof()) {
				getline(file_reader, line1, ':') >> N;
				getline(file_reader, line2, ':') >> colorTheme; 
				getline(file_reader, line3, ':') >> mode;
				getline(file_reader, line4, ':') >> width >> height;
				for(int i = 0; i < N; i++) {
					file_reader >> Px[i] >> Py[i];
					cout << Px[i] << " " << Py[i] << endl;
				} 
				getline(file_reader, line5, ':') >> R;
				getline(file_reader, line6, ':') >> M;
				getline(file_reader, line7, ':') >> Rx >> Ry;
				// getline(file_reader, line5, ':') >> M;
				// for(int i = 0; i < M; i++) {
				// 	file_reader >> Mx[i] >> My[i];
				// 	cout << Mx[i] << " " << My[i] << endl;
				// }
				getline(file_reader, line8, ':') >> NoPoints;
				for(int i = 0; i < NoPoints; i++) {
					file_reader >> coordX[i] >> coordY[i];
				}
				getline(file_reader, line9, ':') >> midx >> midy;
			//}
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 5) {
		file_reader.open("map5.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			//while (!file_reader.eof()) {
				getline(file_reader, line1, ':') >> N;
				getline(file_reader, line2, ':') >> colorTheme; 
				getline(file_reader, line3, ':') >> mode;
				getline(file_reader, line4, ':') >> width >> height;
				for(int i = 0; i < N; i++) {
					file_reader >> Px[i] >> Py[i];
					cout << Px[i] << " " << Py[i] << endl;
				} 
				getline(file_reader, line5, ':') >> R;
				getline(file_reader, line6, ':') >> M;
				getline(file_reader, line7, ':') >> Rx >> Ry;
				// getline(file_reader, line5, ':') >> M;
				// for(int i = 0; i < M; i++) {
				// 	file_reader >> Mx[i] >> My[i];
				// 	cout << Mx[i] << " " << My[i] << endl;
				// }
				getline(file_reader, line8, ':') >> NoPoints;
				for(int i = 0; i < NoPoints; i++) {
					file_reader >> coordX[i] >> coordY[i];
				}
				getline(file_reader, line9, ':') >> midx >> midy;
			//}
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 6) {
		file_reader.open("map6.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			//while (!file_reader.eof()) {
				getline(file_reader, line1, ':') >> N;
				getline(file_reader, line2, ':') >> colorTheme; 
				getline(file_reader, line3, ':') >> mode;
				getline(file_reader, line4, ':') >> width >> height;
				for(int i = 0; i < N; i++) {
					file_reader >> Px[i] >> Py[i];
					cout << Px[i] << " " << Py[i] << endl;
				} 
				getline(file_reader, line5, ':') >> R;
				getline(file_reader, line6, ':') >> M;
				getline(file_reader, line7, ':') >> Rx >> Ry;
				// getline(file_reader, line5, ':') >> M;
				// for(int i = 0; i < M; i++) {
				// 	file_reader >> Mx[i] >> My[i];
				// 	cout << Mx[i] << " " << My[i] << endl;
				// }
				getline(file_reader, line8, ':') >> NoPoints;
				for(int i = 0; i < NoPoints; i++) {
					file_reader >> coordX[i] >> coordY[i];
				}
				getline(file_reader, line9, ':') >> midx >> midy;
			//}
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 7) {
		file_reader.open("map7.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			//while (!file_reader.eof()) {
				getline(file_reader, line1, ':') >> N;
				getline(file_reader, line2, ':') >> colorTheme; 
				getline(file_reader, line3, ':') >> mode;
				getline(file_reader, line4, ':') >> width >> height;
				for(int i = 0; i < N; i++) {
					file_reader >> Px[i] >> Py[i];
					cout << Px[i] << " " << Py[i] << endl;
				} 
				getline(file_reader, line5, ':') >> R;
				getline(file_reader, line6, ':') >> M;
				getline(file_reader, line7, ':') >> Rx >> Ry;
				// getline(file_reader, line5, ':') >> M;
				// for(int i = 0; i < M; i++) {
				// 	file_reader >> Mx[i] >> My[i];
				// 	cout << Mx[i] << " " << My[i] << endl;
				// }
				getline(file_reader, line8, ':') >> NoPoints;
				for(int i = 0; i < NoPoints; i++) {
					file_reader >> coordX[i] >> coordY[i];
				}
				getline(file_reader, line9, ':') >> midx >> midy;
			//}
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 8) {
		file_reader.open("map8.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			//while (!file_reader.eof()) {
				getline(file_reader, line1, ':') >> N;
				getline(file_reader, line2, ':') >> colorTheme; 
				getline(file_reader, line3, ':') >> mode;
				getline(file_reader, line4, ':') >> width >> height;
				for(int i = 0; i < N; i++) {
					file_reader >> Px[i] >> Py[i];
					cout << Px[i] << " " << Py[i] << endl;
				} 
				getline(file_reader, line5, ':') >> R;
				getline(file_reader, line6, ':') >> M;
				getline(file_reader, line7, ':') >> Rx >> Ry;
				// getline(file_reader, line5, ':') >> M;
				// for(int i = 0; i < M; i++) {
				// 	file_reader >> Mx[i] >> My[i];
				// 	cout << Mx[i] << " " << My[i] << endl;
				// }
				getline(file_reader, line8, ':') >> NoPoints;
				for(int i = 0; i < NoPoints; i++) {
					file_reader >> coordX[i] >> coordY[i];
				}
				getline(file_reader, line9, ':') >> midx >> midy;
			//}
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 9) {
		file_reader.open("map9.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			//while (!file_reader.eof()) {
				getline(file_reader, line1, ':') >> N;
				getline(file_reader, line2, ':') >> colorTheme; 
				getline(file_reader, line3, ':') >> mode;
				getline(file_reader, line4, ':') >> width >> height;
				for(int i = 0; i < N; i++) {
					file_reader >> Px[i] >> Py[i];
					cout << Px[i] << " " << Py[i] << endl;
				} 
				getline(file_reader, line5, ':') >> R;
				getline(file_reader, line6, ':') >> M;
				getline(file_reader, line7, ':') >> Rx >> Ry;
				// getline(file_reader, line5, ':') >> M;
				// for(int i = 0; i < M; i++) {
				// 	file_reader >> Mx[i] >> My[i];
				// 	cout << Mx[i] << " " << My[i] << endl;
				// }
				getline(file_reader, line8, ':') >> NoPoints;
				for(int i = 0; i < NoPoints; i++) {
					file_reader >> coordX[i] >> coordY[i];
				}
				getline(file_reader, line9, ':') >> midx >> midy;
			//}
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 10) {
		file_reader.open("map10.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			getline(file_reader, line1, ':') >> N;
			getline(file_reader, line2, ':') >> colorTheme; 
			getline(file_reader, line3, ':') >> mode;
			getline(file_reader, line4, ':') >> width >> height;
			for(int i = 0; i < N; i++) {
				file_reader >> Px[i] >> Py[i];
				cout << Px[i] << " " << Py[i] << endl;
			} 
			getline(file_reader, line5, ':') >> R;
			getline(file_reader, line6, ':') >> M;
			getline(file_reader, line7, ':') >> Rx >> Ry;
			getline(file_reader, line8, ':') >> NoPoints;
			for(int i = 0; i < NoPoints; i++) {
				file_reader >> coordX[i] >> coordY[i];
			}
			getline(file_reader, line9, ':') >> midx >> midy;
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 11) {
		file_reader.open("map11.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			getline(file_reader, line1, ':') >> N;
			getline(file_reader, line2, ':') >> colorTheme; 
			getline(file_reader, line3, ':') >> mode;
			getline(file_reader, line4, ':') >> width >> height;
			for(int i = 0; i < N; i++) {
				file_reader >> Px[i] >> Py[i];
				cout << Px[i] << " " << Py[i] << endl;
			} 
			getline(file_reader, line5, ':') >> R;
			getline(file_reader, line6, ':') >> M;
			getline(file_reader, line7, ':') >> Rx >> Ry;
			getline(file_reader, line8, ':') >> NoPoints;
			for(int i = 0; i < NoPoints; i++) {
				file_reader >> coordX[i] >> coordY[i];
			}
			getline(file_reader, line9, ':') >> midx >> midy;
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 12) {
		file_reader.open("map12.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			getline(file_reader, line1, ':') >> N;
			getline(file_reader, line2, ':') >> colorTheme; 
			getline(file_reader, line3, ':') >> mode;
			getline(file_reader, line4, ':') >> width >> height;
			for(int i = 0; i < N; i++) {
				file_reader >> Px[i] >> Py[i];
				cout << Px[i] << " " << Py[i] << endl;
			} 
			getline(file_reader, line5, ':') >> R;
			getline(file_reader, line6, ':') >> M;
			getline(file_reader, line7, ':') >> Rx >> Ry;
			getline(file_reader, line8, ':') >> NoPoints;
			for(int i = 0; i < NoPoints; i++) {
				file_reader >> coordX[i] >> coordY[i];
			}
			getline(file_reader, line9, ':') >> midx >> midy;
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 13) {
		file_reader.open("map13.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			getline(file_reader, line1, ':') >> N;
			getline(file_reader, line2, ':') >> colorTheme; 
			getline(file_reader, line3, ':') >> mode;
			getline(file_reader, line4, ':') >> width >> height;
			for(int i = 0; i < N; i++) {
				file_reader >> Px[i] >> Py[i];
				cout << Px[i] << " " << Py[i] << endl;
			} 
			getline(file_reader, line5, ':') >> R;
			getline(file_reader, line6, ':') >> M;
			getline(file_reader, line7, ':') >> Rx >> Ry;
			getline(file_reader, line8, ':') >> NoPoints;
			for(int i = 0; i < NoPoints; i++) {
				file_reader >> coordX[i] >> coordY[i];
			}
			getline(file_reader, line9, ':') >> midx >> midy;
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 14) {
		file_reader.open("map14.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			getline(file_reader, line1, ':') >> N;
			getline(file_reader, line2, ':') >> colorTheme; 
			getline(file_reader, line3, ':') >> mode;
			getline(file_reader, line4, ':') >> width >> height;
			for(int i = 0; i < N; i++) {
				file_reader >> Px[i] >> Py[i];
				cout << Px[i] << " " << Py[i] << endl;
			} 
			getline(file_reader, line5, ':') >> R;
			getline(file_reader, line6, ':') >> M;
			getline(file_reader, line7, ':') >> Rx >> Ry;
			getline(file_reader, line8, ':') >> NoPoints;
			for(int i = 0; i < NoPoints; i++) {
				file_reader >> coordX[i] >> coordY[i];
			}
			getline(file_reader, line9, ':') >> midx >> midy;
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 15) {
		file_reader.open("map15.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			getline(file_reader, line1, ':') >> N;
			getline(file_reader, line2, ':') >> colorTheme; 
			getline(file_reader, line3, ':') >> mode;
			getline(file_reader, line4, ':') >> width >> height;
			for(int i = 0; i < N; i++) {
				file_reader >> Px[i] >> Py[i];
				cout << Px[i] << " " << Py[i] << endl;
			} 
			getline(file_reader, line5, ':') >> R;
			getline(file_reader, line6, ':') >> M;
			getline(file_reader, line7, ':') >> Rx >> Ry;
			getline(file_reader, line8, ':') >> NoPoints;
			for(int i = 0; i < NoPoints; i++) {
				file_reader >> coordX[i] >> coordY[i];
			}
			getline(file_reader, line9, ':') >> midx >> midy;
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 16) {
		file_reader.open("map16.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			getline(file_reader, line1, ':') >> N;
			getline(file_reader, line2, ':') >> colorTheme; 
			getline(file_reader, line3, ':') >> mode;
			getline(file_reader, line4, ':') >> width >> height;
			for(int i = 0; i < N; i++) {
				file_reader >> Px[i] >> Py[i];
				cout << Px[i] << " " << Py[i] << endl;
			} 
			getline(file_reader, line5, ':') >> R;
			getline(file_reader, line6, ':') >> M;
			getline(file_reader, line7, ':') >> Rx >> Ry;
			getline(file_reader, line8, ':') >> NoPoints;
			for(int i = 0; i < NoPoints; i++) {
				file_reader >> coordX[i] >> coordY[i];
			}
			getline(file_reader, line9, ':') >> midx >> midy;
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 17) {
		file_reader.open("map17.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			getline(file_reader, line1, ':') >> N;
			getline(file_reader, line2, ':') >> colorTheme; 
			getline(file_reader, line3, ':') >> mode;
			getline(file_reader, line4, ':') >> width >> height;
			for(int i = 0; i < N; i++) {
				file_reader >> Px[i] >> Py[i];
				cout << Px[i] << " " << Py[i] << endl;
			} 
			getline(file_reader, line5, ':') >> R;
			getline(file_reader, line6, ':') >> M;
			getline(file_reader, line7, ':') >> Rx >> Ry;
			getline(file_reader, line8, ':') >> NoPoints;
			for(int i = 0; i < NoPoints; i++) {
				file_reader >> coordX[i] >> coordY[i];
			}
			getline(file_reader, line9, ':') >> midx >> midy;
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 18) {
		file_reader.open("map18.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			getline(file_reader, line1, ':') >> N;
			getline(file_reader, line2, ':') >> colorTheme; 
			getline(file_reader, line3, ':') >> mode;
			getline(file_reader, line4, ':') >> width >> height;
			for(int i = 0; i < N; i++) {
				file_reader >> Px[i] >> Py[i];
				cout << Px[i] << " " << Py[i] << endl;
			} 
			getline(file_reader, line5, ':') >> R;
			getline(file_reader, line6, ':') >> M;
			getline(file_reader, line7, ':') >> Rx >> Ry;
			getline(file_reader, line8, ':') >> NoPoints;
			for(int i = 0; i < NoPoints; i++) {
				file_reader >> coordX[i] >> coordY[i];
			}
			getline(file_reader, line9, ':') >> midx >> midy;
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 19) {
		file_reader.open("map19.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			getline(file_reader, line1, ':') >> N;
			getline(file_reader, line2, ':') >> colorTheme; 
			getline(file_reader, line3, ':') >> mode;
			getline(file_reader, line4, ':') >> width >> height;
			for(int i = 0; i < N; i++) {
				file_reader >> Px[i] >> Py[i];
				cout << Px[i] << " " << Py[i] << endl;
			} 
			getline(file_reader, line5, ':') >> R;
			getline(file_reader, line6, ':') >> M;
			getline(file_reader, line7, ':') >> Rx >> Ry;
			getline(file_reader, line8, ':') >> NoPoints;
			for(int i = 0; i < NoPoints; i++) {
				file_reader >> coordX[i] >> coordY[i];
			}
			getline(file_reader, line9, ':') >> midx >> midy;
			file_reader.close();
		}
 	
 		if(N>10) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}
	else if (mapNo == 20) {
		file_reader.open("map20.txt");

		string line1, line2, line3, line4, line5, line6, line7, line8, line9;

		if(file_reader.is_open()) {
			getline(file_reader, line1, ':') >> N;
			getline(file_reader, line2, ':') >> colorTheme; 
			getline(file_reader, line3, ':') >> mode;
			getline(file_reader, line4, ':') >> width >> height;
			for(int i = 0; i < N; i++) {
				file_reader >> Px[i] >> Py[i];
				cout << Px[i] << " " << Py[i] << endl;
			} 
			getline(file_reader, line5, ':') >> R;
			getline(file_reader, line6, ':') >> M;
			getline(file_reader, line7, ':') >> Rx >> Ry;
			getline(file_reader, line8, ':') >> NoPoints;
			for(int i = 0; i < NoPoints; i++) {
				file_reader >> coordX[i] >> coordY[i];
			}
			getline(file_reader, line9, ':') >> midx >> midy;
			file_reader.close();
		}
 	
 		if(N>20) {
 			cout << "Up to 10 obstacles only";
 			return -1;
 		}
	}

	float masses[N];

	sf::Vector2f windowSize(800, 800);
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y ),"TENKS" );
	int winx = window.getSize().x;
	int winy = window.getSize().y;

	sf::Texture pic3;
	if (!pic3.loadFromFile("pics/bg2.png")) 
		cout << "fuck u jann (failed to load picture)" << endl;
	sf::Sprite bg(pic3);


	//player 1 base build
	sf::RectangleShape player1;
	player1.setSize( sf::Vector2f( 40.0f, 40.0f ) );
	player1.setPosition(0+2*player1.getSize().x,0+2*player1.getSize().y);
	player1.setOrigin(player1.getSize().x/2, player1.getSize().y/2);
	
	//hitcirc of p1
	sf::CircleShape hitP1(player1.getSize().x/2);
	hitP1.setFillColor(sf::Color::White);
	hitP1.setOrigin(player1.getSize().x/2, player1.getSize().y/2);
	hitP1.setPosition(player1.getPosition());


	sf::Texture pic1;
	if (!pic1.loadFromFile("pics/sprite1.png")) {
		cout << "fuck u jann (failed to load picture)" << endl;
		player1.setFillColor( sf::Color::White );
	}
	player1.setTexture(&pic1);

	// sf::ConvexShape nipol;
	// nipol.setPointCount( 8 );
	// nipol.setPoint(0, sf::Vector2f(0,0));
	// nipol.setPoint(1, sf::Vector2f(15,0));
	// nipol.setPoint(2, sf::Vector2f(15,-10));
	// nipol.setPoint(3, sf::Vector2f(35,-10));
	// nipol.setPoint(4, sf::Vector2f(35,0));
	// nipol.setPoint(5, sf::Vector2f(50,0));
	// nipol.setPoint(6, sf::Vector2f(50,50));
	// nipol.setPoint(7, sf::Vector2f(0,50));
	// if(colorTheme=="Christmas")
	// 	nipol.setFillColor(christmasColor1);
	// else if (colorTheme=="Neon")
	// 	nipol.setFillColor(neonColor1);
	// nipol.setPosition(player1.getPosition());
	// nipol.setOrigin(player1.getSize().x/2, player1.getSize().y/2);

	//player 2 build
	sf::RectangleShape player2;
	player2.setSize( sf::Vector2f(40.0f, 40.0f ) );
	player2.setPosition(winx-60,winx-60);
	player2.setOrigin(player2.getSize().x/2, player2.getSize().y/2);
	// if(colorTheme=="Christmas") 
	// 	player2.setFillColor(christmasColor2);
	// else if (colorTheme=="Neon") 
	// 	player2.setFillColor(neonColor2);

	//hitcirc of p2
	sf::CircleShape hitP2(player2.getSize().x/2);
	hitP2.setFillColor(sf::Color::White);
	hitP2.setOrigin(player2.getSize().x/2, player2.getSize().y/2);
	hitP2.setPosition(player2.getPosition());

	sf::Texture pic2;
	if (!pic2.loadFromFile("pics/sprite2.png")) {
		cout << "fuck u jann (failed to load picture)" << endl;
		player2.setFillColor(sf::Color::White);
	}
	player2.setTexture(&pic2);

	// sf::ConvexShape nipol2;
	// nipol2.setPointCount( 8 );
	// nipol2.setPoint(0, sf::Vector2f(0,0));
	// nipol2.setPoint(1, sf::Vector2f(15,0));
	// nipol2.setPoint(2, sf::Vector2f(15,-10));
	// nipol2.setPoint(3, sf::Vector2f(35,-10));
	// nipol2.setPoint(4, sf::Vector2f(35,0));
	// nipol2.setPoint(5, sf::Vector2f(50,0));
	// nipol2.setPoint(6, sf::Vector2f(50,50));
	// nipol2.setPoint(7, sf::Vector2f(0,50));
	// if(colorTheme=="Christmas") 
	// 	nipol2.setFillColor(christmasColor2);
	// else if (colorTheme=="Neon") 
	// 	nipol2.setFillColor(neonColor2);
	// nipol2.setPosition(player2.getPosition());
	// nipol2.setOrigin(player2.getSize().x/2, player2.getSize().y/2);



	//MINE RANGE
	// Mx[0] = 275;
	// Mx[1] = 525;
	// My[0] = 475;
	// My[1] = 325;
	sf::CircleShape range;
	//for(int i = 0; i < M; i++) {
// [ ! ] random spawn still goes out of bounds: [ ! ]
		range.setRadius(R);
		range.setPosition( sf::Vector2f(Rx, Ry) );
		range.setOrigin(R, R);
		range.setFillColor(sf::Color::Red);
		//cout << range[i].getOrigin().x << " " << range[i].getOrigin().y << endl;
	//}
	

	//EXPLOSIVE ITSELF
	sf::CircleShape mine;
	//for(int i = 0; i < M; i++) {
		mine.setRadius(M);
		mine.setPosition(range.getPosition().x, range.getPosition().y);
		mine.setOrigin(M, M);
		mine.setFillColor(sf::Color::Magenta);
		mine.setOutlineColor(sf::Color::Black);
		mine.setOutlineThickness(3);
	//}
	
	sf::Color obsc (133,38,171);
	sf::RectangleShape Obs[N];
	for(int i=0; i < N; i++) {
		Obs[i].setSize(sf::Vector2f(width, height));
		Obs[i].setPosition(Px[i], Py[i]);
		Obs[i].setOrigin(Obs[i].getSize().x/2, Obs[i].getSize().y/2);
		Obs[i].setFillColor(obsc);
		// if(colorTheme=="Christmas")
		// 	Obs[i].setFillColor(christmasColorO);
		// else if (colorTheme=="Neon")
		// 	Obs[i].setFillColor(neonColorO);
		masses[i] = 20.0f;
	}

	sf::Texture obst;
	for(int i = 0; i < N; i++) {
		if (!obst.loadFromFile("pics/poly.png")) {
		cout << "fneowjl (failed to load picture)" << endl;
		Obs[i].setFillColor(sf::Color::White);
		}
		Obs[i].setTexture(&obst);
	}
	

	//endgame
	bool p1Wins = false;
	bool p2Wins = false;

	sf::RectangleShape gameOver;
	gameOver.setSize(sf::Vector2f(winx, winy));
	gameOver.setFillColor(sf::Color::Red);
	gameOver.setPosition(0, 0);

	sf::Text wiMsg;
	wiMsg.setFont(font); 
	//wiMsg.setPosition(winx/2,winy/2);
	wiMsg.setPosition(325, 400);
	wiMsg.setString("Player 1 Wins");
	wiMsg.setCharacterSize(24);
	wiMsg.setFillColor(sf::Color::White);

	//MAIN POLY
	sf::ConvexShape mainPoly;
	// int NoPoints = 6;
	// int coordX[NoPoints] = {0,0,25,50,50,25};
	// int coordY[NoPoints] = {0,50,75,50,0,-25};
	mainPoly.setPointCount(NoPoints);
	for(int i =0; i< NoPoints; i++){
		mainPoly.setPoint(i, sf::Vector2f( coordX[i], coordY[i] ));
		cout << coordX[i] << " <3 " << coordY[i] << endl;
	}
	mainPoly.setFillColor(sf::Color::White);
	//mainPoly.setOutlineColor(sf::Color::Red);
	//mainPoly.setOutlineThickness(1);
	mainPoly.setOrigin(midx, midy);
	//cout << mainPoly.getGlobalBounds().width << "f u jann" << mainPoly.getGlobalBounds().height << endl;
	//cout << "end me is " << mainPoly.getGlobalBounds().width << " " << mainPoly.getGlobalBounds().height << endl;
	mainPoly.setPosition(winx/2, winy/2);
	float massPoly = 500;
	//cout << "love is " << mainPoly.getPosition().x << " " << mainPoly.getPosition().y << endl;

	//hitCirc of mainpoly
	// sf::CircleShape polyCirc(mainPoly.getGlobalBounds().width/2);
	// polyCirc.setPosition(mainPoly.getPosition());
	// cout << "love is " << polyCirc.getPosition().x << " " << polyCirc.getPosition().y << endl;	
	// polyCirc.setFillColor(sf::Color::Cyan);
	// cout << mainPoly.getPosition().x << " " << mainPoly.getPosition().y << endl;
	// cout << polyCirc.getPosition().x << " " << polyCirc.getPosition().y << endl;

	sf::CircleShape polyCirc(mainPoly.getGlobalBounds().width/2);
	polyCirc.setOrigin(mainPoly.getGlobalBounds().width/2, mainPoly.getGlobalBounds().width/2);
	polyCirc.setPosition(winx/2, winy/2);
	//cout << polyCirc.getOrigin().x << " " << polyCirc.getOrigin().y << endl;

	sf::Texture pol;
	if (!pol.loadFromFile("pics/obs.png")) {
	cout << "fneowjl (failed to load picture)" << endl;
	mainPoly.setFillColor(sf::Color::White);
	}
	mainPoly.setTexture(&pol);


	float pFriction = 0;
	float pMass = 0;

	if(mode=="Spaceships") {
		pFriction = 0.1;
		pMass = 10;
	}
	else if (mode=="Tanks"){
		pFriction = 2;
		pMass = 100;
	}

	sf::Vector2f velocity1 (0,0);
	sf::Vector2f velocity2 (0,0);
	//sf::Vector2f overlap (0,0);

	//NEW MOVEMENT used for rotation

	//player1
	float x=winx/2, y=winy/2;
	float angle=0;
   	//float maxSpeed=12.0;
   	//float acc=0.2, dec=0.3;
   	float turnSpeed=0.5;

   	//player2
   	float angle2=0;
   	float turnSpeed2=0.5;

	//bullets for player 1
	deque<sf::CircleShape> bulletInstances1;
	deque<sf::Vector2f> velocityInstances1;
	deque<sf::Time> bTimeInstances1;
	sf::Color color1(214,152,255);
	sf::Color color2(95,255,220);

	//cooldown
	bool fired1 = false;

	float bRadius = 5.25f;
	float bMass = 1;
	sf::Time cooldown1 = sf::seconds(0);

	//bullets for player2
	deque<sf::CircleShape> bulletInstances2;
	deque<sf::Vector2f> velocityInstances2;
	deque<sf::Time> bTimeInstances2;

	//player2
	bool fired2 = false;
	sf::Time cooldown2 = sf::seconds(0);	

	sf::Vector2f overlap (0,0);
	sf::Vector2f distance(0,0);
	float distanceDiag = 0;

	//player1
	bool forwardFlag = false;
	bool leftFlag = false;
	bool backFlag = false;
	bool rightFlag = false;	

	//player2
	bool forwardFlag2 = false;
	bool leftFlag2 = false;
	bool backFlag2 = false;
	bool rightFlag2 = false;		

	//for pFriction
	bool movingUp1 = false;
	bool movingDown1 = false;
	bool movingRight1 = false;
	bool movingLeft1 = false;
	bool movingStop1 = false;

	//player2
	bool movingUp2 = false;
	bool movingDown2 = false;
	bool movingRight2 = false;
	bool movingLeft2 = false;
	bool movingStop2 = false;


	//spatialization
	sf::Vector2f rangeDistance (0,0);
	float rangeDistanceDiag = 0;
	float attenuation = 5.0f;
	float minDistance;
	//for(int i = 0; i < M; i++){
		minDistance = range.getRadius()/3;
	//}
	float volume = 0;
	float pitch = 1.5;
	sf::Sound beep;
	beep.setBuffer(rangeBuffer);
	beep.setVolume(volume);
	beep.setPitch(pitch);
    beep.play();
    beep.setLoop(true);

    OST.setLoop(true);
    OST.setVolume(100);
    OST.play();

    sf::Sound explosion;
    explosion.setBuffer(explodBuffer);
    explosion.setVolume(100);
    explosion.setLoop(false);
    explosion.setPitch(pitch);
    bool exploded = false;

	sf::Sound pewpew;
    pewpew.setBuffer(pewBuffer);
    pewpew.setVolume(100);
    pewpew.setPitch(2);

	sf::Clock clock;
	// sf::Time elapsedTime = sf::seconds(0);

	


	while( window.isOpen() ) {
		sf::Time iterationTime = clock.restart();
		// elapsedTime += iterationTime;
		
		sf::Event event;
		while(window.pollEvent(event)){
			switch(event.type){
				case sf::Event::Closed:
				window.close();
				break;
				case sf::Event::KeyPressed:
					switch(event.key.code) {
						case sf::Keyboard::Escape: 
							window.close();
							break;
						case sf::Keyboard::W:
							forwardFlag=true;
							break;
						case sf::Keyboard::A:
							leftFlag=true;
							break;
						case sf::Keyboard::S:
							backFlag=true;
							break;
						case sf::Keyboard::D:
							rightFlag=true;
							break;
						case sf::Keyboard::F: {
							if(!fired1) {
								bulletInstances1.push_front(sf::CircleShape(bRadius));
								bulletInstances1.front().setPosition(player1.getPosition().x, player1.getPosition().y);
								bulletInstances1.front().setOrigin(bulletInstances1.front().getRadius(), bulletInstances1.front().getRadius());
								bulletInstances1.front().setFillColor(color1);
								// velocityInstances1.push_front(sf::Vector2f(cos(-player1.getRotation()*3.14159265/180)*SPEED/STABILIZER,sin(-player1.getRotation()*3.14159265/180)*-SPEED/STABILIZER));
								velocityInstances1.push_front(sf::Vector2f(sin(angle) * 80.0f * timestep, -cos(angle) * 80.0f *timestep));
								bTimeInstances1.push_front(sf::seconds(0));
								fired1 = true;
								pewpew.play();
							}
						}
							break;
						case sf::Keyboard::Up:
							forwardFlag2=true;
							break;
						case sf::Keyboard::Left:
							leftFlag2=true;
							break;
						case sf::Keyboard::Down:
							backFlag2=true;
							break;
						case sf::Keyboard::Right:
							rightFlag2=true;
							break;
						case sf::Keyboard::Enter: {
							if(!fired2) {
								bulletInstances2.push_front(sf::CircleShape(bRadius));
								bulletInstances2.front().setPosition(player2.getPosition().x, player2.getPosition().y);
								bulletInstances2.front().setOrigin(bulletInstances2.front().getRadius(), bulletInstances2.front().getRadius());
								bulletInstances2.front().setFillColor(color2);
								velocityInstances2.push_front(sf::Vector2f(sin(angle2) * 80.0f * timestep, -cos(angle2) * 80.0f *timestep));
								bTimeInstances2.push_front(sf::seconds(0));
								fired2 = true;
								pewpew.play();
							}
						}
							break;	
						case sf::Keyboard::H:
							printInstructions();
							break;

						//extra feature: RESET
						case sf::Keyboard::R:
							x,y = winx/2,winy/2;
							//speed,angle= 0,0;
							velocity1.x,velocity1.y = 0,0; 
						// [ ! ] ^^ player still moves upon reset [ ! ]
							// range[i].setPosition( sf::Vector2f(rand() % winx, rand() % winy) );
							// mine[i].setPosition(range[i].getPosition().x, range[i].getPosition().y);			
							break;
						default: break;
					}
				break;

				case sf::Event::KeyReleased:
					switch(event.key.code) {
						case sf::Keyboard::W:
							forwardFlag=false;
							break;
						case sf::Keyboard::A:
							leftFlag=false;
							break;
						case sf::Keyboard::S:
							backFlag=false;
							break;
						case sf::Keyboard::D:
							rightFlag=false;
							break;
						case sf::Keyboard::Up:
							forwardFlag2=false;
							break;
						case sf::Keyboard::Left:
							leftFlag2=false;
							break;
						case sf::Keyboard::Down:
							backFlag2=false;
							break;
						case sf::Keyboard::Right:
							rightFlag2=false;
							break;


						default: break;
					}
				break;
			}	
		}

		if (fired1) { 
			cooldown1 += iterationTime;
			int timeTest = trunc(cooldown1.asSeconds());
			if(timeTest==1) {
				fired1 = false;
				cooldown1 = sf::seconds(0);
			}
		}

		if (fired2) { 
			cooldown2 += iterationTime;
			int timeTest2 = trunc(cooldown2.asSeconds());
			if(timeTest2==1) {
				fired2 = false;
				cooldown2 = sf::seconds(0);
			}
		}		


		//moobment
		//player1
		if (forwardFlag) {
			velocity1.x += sin(angle) * 1.0f * timestep/pMass;
			velocity1.y += -cos(angle) * 1.0f *timestep/pMass;
		} 
		if (leftFlag) {
			angle -= turnSpeed * timestep;
		}			
		if (backFlag) {
			velocity1.x += -sin(angle) * 1.0f * timestep/pMass;
			velocity1.y += cos(angle) * 1.0f *timestep/pMass;
		}
		if (rightFlag){
			angle += turnSpeed * timestep;
		}

		//player1.move(velocity1.x, velocity1.y);

		player1.setRotation(angle*180/3.141592);

		//player2
		if (forwardFlag2) {
			velocity2.x += sin(angle2) * 1.0f * timestep/pMass;
			velocity2.y += -cos(angle2) * 1.0f *timestep/pMass;
		} 
		if (leftFlag2) {
			angle2 -= turnSpeed2 * timestep;
		}			
		if (backFlag2) {
			velocity2.x += -sin(angle2) * 1.0f * timestep/pMass;
			velocity2.y += cos(angle2) * 1.0f *timestep/pMass;
		}
		if (rightFlag2){
			angle2 += turnSpeed2 * timestep;
		}

		//player1.move(velocity1.x, velocity1.y);

		player2.setRotation(angle2*180/3.141592);


		//BULLET1 TIME ITERATION
		for(int i = 0 ; i < bulletInstances1.size(); ++i){
			bTimeInstances1[i] += iterationTime;
		}

		//BULLET2
		for(int i = 0 ; i < bulletInstances2.size(); ++i){
			bTimeInstances2[i] += iterationTime;
		}		


		
		//BOUNDARIES
		//player1
		if(player1.getPosition().y - player1.getSize().y/2< 0){
			player1.setPosition(player1.getPosition().x,0+player1.getSize().y/2);
			velocity1.y *= -ELASTICITY;
		}
		
		if(player1.getPosition().y + player1.getSize().y/2 > winy){
			player1.setPosition(player1.getPosition().x,winy-player1.getSize().y/2);
			velocity1.y *= -ELASTICITY;
		}

		if(player1.getPosition().x - player1.getSize().x/2< 0){
			player1.setPosition(0+player1.getSize().x/2,player1.getPosition().y);
			velocity1.x *= -ELASTICITY;
		}
		if(player1.getPosition().x + player1.getSize().x/2 > winx){
			player1.setPosition(winx-player1.getSize().x/2,player1.getPosition().y);
			velocity1.x *= -ELASTICITY;
		}
		//player2
		if(player2.getPosition().y - player2.getSize().y/2< 0){
			player2.setPosition(player2.getPosition().x,0+player2.getSize().y/2);
			velocity2.y *= -ELASTICITY;
		}
		
		if(player2.getPosition().y + player2.getSize().y/2 > winy){
			player2.setPosition(player2.getPosition().x,winy-player2.getSize().y/2);
			velocity2.y *= -ELASTICITY;
		}

		if(player2.getPosition().x - player2.getSize().x/2< 0){
			player2.setPosition(0+player2.getSize().x/2,player2.getPosition().y);
			velocity2.x *= -ELASTICITY;
		}
		if(player2.getPosition().x + player2.getSize().x/2 > winx){
			player2.setPosition(winx-player2.getSize().x/2,player2.getPosition().y);
			velocity2.x *= -ELASTICITY;
		}


		//bullet1
		for(int i= 0; i < bulletInstances1.size(); i++){
			if(bulletInstances1[i].getPosition().y < 0 ){
				bulletInstances1[i].setPosition(bulletInstances1[i].getPosition().x, 0);
				velocityInstances1[i].y *= -ELASTICITY;
			} 
			if(bulletInstances1[i].getPosition().y + (2*bRadius) > winy  ){
				bulletInstances1[i].setPosition(bulletInstances1[i].getPosition().x, winy-2*bRadius);
				velocityInstances1[i].y *= -ELASTICITY;
			}
			if(bulletInstances1[i].getPosition().x < 0 ){
				bulletInstances1[i].setPosition(0,bulletInstances1[i].getPosition().y);
				velocityInstances1[i].x *= -ELASTICITY;
			}
			if(bulletInstances1[i].getPosition().x + (2*bRadius) > winx){
				bulletInstances1[i].setPosition(winx-2*bRadius, bulletInstances1[i].getPosition().y);
				velocityInstances1[i].x *= -ELASTICITY;
			}
		}

		//bullets2
		for(int i= 0; i < bulletInstances2.size(); i++){
			if(bulletInstances2[i].getPosition().y < 0 ){
				bulletInstances2[i].setPosition(bulletInstances2[i].getPosition().x, 0);
				velocityInstances2[i].y *= -ELASTICITY;
			} 
			if(bulletInstances2[i].getPosition().y + (2*bRadius) > winy  ){
				bulletInstances2[i].setPosition(bulletInstances2[i].getPosition().x, winy-2*bRadius);
				velocityInstances2[i].y *= -ELASTICITY;
			}
			if(bulletInstances2[i].getPosition().x < 0 ){
				bulletInstances2[i].setPosition(0,bulletInstances2[i].getPosition().y);
				velocityInstances2[i].x *= -ELASTICITY;
			}
			if(bulletInstances2[i].getPosition().x + (2*bRadius) > winx){
				bulletInstances2[i].setPosition(winx-2*bRadius, bulletInstances2[i].getPosition().y);
				velocityInstances2[i].x *= -ELASTICITY;
			}
		}		

		//player 1 vs main poly
		if(player1.getGlobalBounds().intersects(mainPoly.getGlobalBounds())){
			distance.x = hitP1.getPosition().x - polyCirc.getPosition().x;
			distance.y = hitP1.getPosition().y - polyCirc.getPosition().y;

			distanceDiag = sqrt((distance.x*distance.x) + (distance.y*distance.y));

			float radius = hitP1.getRadius();
			float radiusPoly = polyCirc.getRadius();

			if(radius + radiusPoly > distanceDiag){
				overlap.x = distanceDiag - (radius+radiusPoly);
				overlap.y = distanceDiag - (radius+radiusPoly);
				
				float nx = (polyCirc.getPosition().x - hitP1.getPosition().x)/ distanceDiag;
				float ny = (polyCirc.getPosition().y - hitP1.getPosition().y)/ distanceDiag;
				
				float tx = -ny;
				float ty = nx;
				
				float dpTan1 = velocity1.x * tx + velocity1.y *ty;
				float dpTan2 = 0 * tx + 0 *ty;
				
				float dpNorm1 = velocity1.x * nx + velocity1.y * ny;
				float dpNorm2 = 0 * nx + 0 *ty;
				
				//CHANGE ME BABE
				float m1 = (dpNorm1 * (pMass - massPoly) +  massPoly *dpNorm2)/(pMass + massPoly);
				float m2 = (dpNorm2 * (massPoly- pMass) +  pMass *dpNorm1)/(pMass + massPoly);

				if(player1.getPosition().x < mainPoly.getPosition().x){
					player1.move(overlap.x/2,0);
					
					//BOUNCE BOUNCE
					//TIMESTEP DELETE AFTER
					velocity1.x = (tx * dpTan1 + nx * m1);
					velocity1.y = (ty * dpTan1 + ny * m1);
					//velocity.y = (velocity.y * (mass-mass) + (2* mass * mass)) / (mass + mass);
				}
				//higher x-coor
				if(player1.getPosition().x > mainPoly.getPosition().x){
					player1.move(-overlap.x/2,0);
					
					velocity1.x = (tx * dpTan1 + nx * m1);
					velocity1.y = (ty * dpTan1 + ny * m1);
				}
				//less y-coor
				if(player1.getPosition().y > mainPoly.getPosition().y){
					player1.move(0,-overlap.x/2);
					
					velocity1.x = (tx * dpTan1 + nx * m1);
					velocity1.y = (ty * dpTan1 + ny * m1);

				}
				//higher y-coor
				if(player1.getPosition().y < mainPoly.getPosition().y){
					player1.move(0,overlap.x/2);
					
					velocity1.x = (tx * dpTan1 + nx * m1);
					velocity1.y = (ty * dpTan1 + ny * m1);
				}
				/*cout<<overlap.x<<endl;
				cout<<overlap.y<<endl;
				cout << "colliding";*/
			}
		}

		//player1 vs obs
		for(int i=0; i<N; i++) {
			if(player1.getGlobalBounds().intersects(Obs[i].getGlobalBounds())){
				//left
				if (player1.getPosition().x + player1.getSize().x/2 < Obs[i].getPosition().x-Obs[i].getSize().x/2) {				
					velocity1.x *= -ELASTICITY;
					//cout << "END ME less x" << endl;
				}
				//right
				if (player1.getPosition().x -player1.getSize().x/2 > Obs[i].getPosition().x+Obs[i].getSize().x/2) {
					velocity1.x *= -ELASTICITY;
					//cout << "END ME more x" << endl;
				}
				//bottom
				if (player1.getPosition().y - player1.getSize().y/2> Obs[i].getPosition().y+Obs[i].getSize().y/2) {
					velocity1.y *= -ELASTICITY;
					//cout << "END ME less y" << endl;
				}
				//top
				if (player1.getPosition().y + player1.getSize().y/2 < Obs[i].getPosition().y-Obs[i].getSize().y/2) {
					velocity1.y *= -ELASTICITY;
					//cout << "END ME more y" << endl;
				}			
			}
		}


		//player2 vs main poly
		if(player2.getGlobalBounds().intersects(mainPoly.getGlobalBounds())){
			distance.x = hitP2.getPosition().x - polyCirc.getPosition().x;
			distance.y = hitP2.getPosition().y - polyCirc.getPosition().y;

			distanceDiag = sqrt((distance.x*distance.x) + (distance.y*distance.y));

			float radius = hitP2.getRadius();
			float radiusPoly = polyCirc.getRadius();

			if(radius + radiusPoly > distanceDiag){
				overlap.x = distanceDiag - (radius+radiusPoly);
				overlap.y = distanceDiag - (radius+radiusPoly);
				
				float nx = (polyCirc.getPosition().x - hitP2.getPosition().x)/ distanceDiag;
				float ny = (polyCirc.getPosition().y - hitP2.getPosition().y)/ distanceDiag;
				
				float tx = -ny;
				float ty = nx;
				
				float dpTan1 = velocity2.x * tx + velocity2.y *ty;
				float dpTan2 = 0 * tx + 0 *ty;
				
				float dpNorm1 = velocity2.x * nx + velocity2.y * ny;
				float dpNorm2 = 0 * nx + 0 *ty;
				
				//CHANGE ME BABE
				float m1 = (dpNorm1 * (pMass - massPoly) +  massPoly *dpNorm2)/(pMass + massPoly);
				float m2 = (dpNorm2 * (massPoly- pMass) +  pMass *dpNorm1)/(pMass + massPoly);

				if(player2.getPosition().x < mainPoly.getPosition().x){
					player2.move(overlap.x/2,0);
					
					//BOUNCE BOUNCE
					//TIMESTEP DELETE AFTER
					velocity2.x = (tx * dpTan1 + nx * m1);
					velocity2.y = (ty * dpTan1 + ny * m1);
					//velocity.y = (velocity.y * (mass-mass) + (2* mass * mass)) / (mass + mass);
				}
				//higher x-coor
				if(player2.getPosition().x > mainPoly.getPosition().x){
					player2.move(-overlap.x/2,0);
					
					velocity2.x = (tx * dpTan1 + nx * m1);
					velocity2.y = (ty * dpTan1 + ny * m1);
				}
				//less y-coor
				if(player2.getPosition().y > mainPoly.getPosition().y){
					player2.move(0,-overlap.x/2);
					
					velocity2.x = (tx * dpTan1 + nx * m1);
					velocity2.y = (ty * dpTan1 + ny * m1);

				}
				//higher y-coor
				if(player2.getPosition().y < mainPoly.getPosition().y){
					player2.move(0,overlap.x/2);
					
					velocity2.x = (tx * dpTan1 + nx * m1);
					velocity2.y = (ty * dpTan1 + ny * m1);
				}
				/*cout<<overlap.x<<endl;
				cout<<overlap.y<<endl;
				cout << "colliding";*/
			}
		}
		//player2 vs obs
		for(int i=0; i<N; i++) {
			if(player2.getGlobalBounds().intersects(Obs[i].getGlobalBounds())){
				//left
				if (player2.getPosition().x + player2.getSize().x/2 < Obs[i].getPosition().x-Obs[i].getSize().x/2) {				
					velocity2.x *= -ELASTICITY;
					//cout << "END ME less x" << endl;
				}
				//right
				if (player2.getPosition().x -player2.getSize().x/2 > Obs[i].getPosition().x+Obs[i].getSize().x/2) {
					velocity2.x *= -ELASTICITY;
					//cout << "END ME more x" << endl;
				}
				//bottom
				if (player2.getPosition().y - player2.getSize().y/2> Obs[i].getPosition().y+Obs[i].getSize().y/2) {
					velocity2.y *= -ELASTICITY;
					//cout << "END ME less y" << endl;
				}
				//top
				if (player2.getPosition().y + player2.getSize().y/2 < Obs[i].getPosition().y-Obs[i].getSize().y/2) {
					velocity2.y *= -ELASTICITY;
					//cout << "END ME more y" << endl;
				}			
			}
		}

		//bullets bounce player1
		for (int i = 0 ; i < bulletInstances1.size(); ++i){
			for(int j=i; j < N; j++){
				if(bulletInstances1[i].getGlobalBounds().intersects(player2.getGlobalBounds())){
					//bottom
					p1Wins = true;
				}
			}
        }

		for (int i = 0 ; i < bulletInstances2.size(); ++i){
			for(int j=i; j < N; j++){
				if(bulletInstances2[i].getGlobalBounds().intersects(player1.getGlobalBounds())){
					//bottom
					p2Wins = true;
				}
			}
        }

		//bullets bounce OBS
		for (int i = 0 ; i < bulletInstances1.size(); ++i){
			for(int j=i; j < N; j++){
				if(bulletInstances1[i].getGlobalBounds().intersects(Obs[j].getGlobalBounds())){
					//bottom
					if (bulletInstances1[i].getPosition().y > Obs[j].getPosition().y + Obs[j].getSize().y/2) {
						velocityInstances1[i].y *= -ELASTICITY;
						//cout << "Shoot ME lower than obs" << endl;
					}
					//top
					if (bulletInstances1[i].getPosition().y < Obs[j].getPosition().y-Obs[j].getSize().y/2) {
						velocityInstances1[i].y *= -ELASTICITY;
						//cout << "Shoot ME higher than obs" << endl;
					}
					//left
					if (bulletInstances1[i].getPosition().x < Obs[j].getPosition().x-Obs[j].getSize().x/2) {				
						velocityInstances1[i].x *= -ELASTICITY;
						//cout << "Shoot ME less x" << endl;
					}
					//right
					if (bulletInstances1[i].getPosition().x > Obs[j].getPosition().x+Obs[j].getSize().x/2) {
						velocityInstances1[i].x *= -ELASTICITY;
						//cout << "Shoot ME more x" << endl;
					}
				}
			}
        }
        //bullets1 vs main poly
        for(int i = 0; i< bulletInstances1.size(); ++i){
			distance.x = bulletInstances1[i].getPosition().x - polyCirc.getPosition().x;
			distance.y = bulletInstances1[i].getPosition().y - polyCirc.getPosition().y;

			distanceDiag = sqrt((distance.x*distance.x) + (distance.y*distance.y));

			float radiusPoly = polyCirc.getRadius();

			if(bRadius + radiusPoly > distanceDiag){
				overlap.x = distanceDiag - (bRadius+radiusPoly);
				overlap.y = distanceDiag - (bRadius+radiusPoly);
				
				float nx = (polyCirc.getPosition().x - bulletInstances1[i].getPosition().x)/ distanceDiag;
				float ny = (polyCirc.getPosition().y - bulletInstances1[i].getPosition().y)/ distanceDiag;
				
				float tx = -ny;
				float ty = nx;
				
				float dpTan1 = velocityInstances1[i].x * tx + velocityInstances1[i].y *ty;
				float dpTan2 = 0 * tx + 0 *ty;
				
				float dpNorm1 = velocityInstances1[i].x * nx + velocityInstances1[i].y * ny;
				float dpNorm2 = 0 * nx + 0 *ty;
				
				//CHANGE ME BABE
				float m1 = (dpNorm1 * (bMass - massPoly) +  massPoly *dpNorm2)/(bMass + massPoly);
				float m2 = (dpNorm2 * (massPoly- bMass) +  bMass *dpNorm1)/(bMass + massPoly);

				if(bulletInstances1[i].getPosition().x < mainPoly.getPosition().x){
					bulletInstances1[i].move(overlap.x/2,0);
					
					//BOUNCE BOUNCE
					//TIMESTEP DELETE AFTER
					velocityInstances1[i].x = (tx * dpTan1 + nx * m1);
					velocityInstances1[i].y = (ty * dpTan1 + ny * m1);
					//velocity.y = (velocity.y * (mass-mass) + (2* mass * mass)) / (mass + mass);
				}
				//higher x-coor
				if(bulletInstances1[i].getPosition().x > mainPoly.getPosition().x){
					bulletInstances1[i].move(-overlap.x/2,0);
					
					velocityInstances1[i].x = (tx * dpTan1 + nx * m1);
					velocityInstances1[i].y = (ty * dpTan1 + ny * m1);
				}
				//less y-coor
				if(bulletInstances1[i].getPosition().y > mainPoly.getPosition().y){
					bulletInstances1[i].move(0,-overlap.x/2);
					
					velocityInstances1[i].x = (tx * dpTan1 + nx * m1);
					velocityInstances1[i].y = (ty * dpTan1 + ny * m1);

				}
				//higher y-coor
				if(bulletInstances1[i].getPosition().y < mainPoly.getPosition().y){
					bulletInstances1[i].move(0,overlap.x/2);
					
					velocityInstances1[i].x = (tx * dpTan1 + nx * m1);
					velocityInstances1[i].y = (ty * dpTan1 + ny * m1);
				}
				/*cout<<overlap.x<<endl;
				cout<<overlap.y<<endl;
				cout << "colliding";*/
			}
        }



		//bullets2		
        for (int i = 0 ; i < bulletInstances2.size(); ++i){
			for(int j=i; j < N; j++){
				if(bulletInstances2[i].getGlobalBounds().intersects(Obs[j].getGlobalBounds())){
					//bottom
					if (bulletInstances2[i].getPosition().y > Obs[j].getPosition().y + Obs[j].getSize().y/2) {
						velocityInstances2[i].y *= -ELASTICITY;
						//cout << "Shoot ME lower than obs" << endl;
					}
					//top
					if (bulletInstances2[i].getPosition().y < Obs[j].getPosition().y-Obs[j].getSize().y/2) {
						velocityInstances2[i].y *= -ELASTICITY;
						//cout << "Shoot ME higher than obs" << endl;
					}
					//left
					if (bulletInstances2[i].getPosition().x < Obs[j].getPosition().x-Obs[j].getSize().x/2) {				
						velocityInstances2[i].x *= -ELASTICITY;
						//cout << "Shoot ME less x" << endl;
					}
					//right
					if (bulletInstances2[i].getPosition().x > Obs[j].getPosition().x+Obs[j].getSize().x/2) {
						velocityInstances2[i].x *= -ELASTICITY;
						//cout << "Shoot ME more x" << endl;
					}
				}
			}
        }

        //bullets2 vs main poly
        for(int i = 0; i< bulletInstances2.size(); ++i){
			distance.x = bulletInstances2[i].getPosition().x - polyCirc.getPosition().x;
			distance.y = bulletInstances2[i].getPosition().y - polyCirc.getPosition().y;

			distanceDiag = sqrt((distance.x*distance.x) + (distance.y*distance.y));

			float radiusPoly = polyCirc.getRadius();

			if(bRadius + radiusPoly > distanceDiag){
				overlap.x = distanceDiag - (bRadius+radiusPoly);
				overlap.y = distanceDiag - (bRadius+radiusPoly);
				
				float nx = (polyCirc.getPosition().x - bulletInstances2[i].getPosition().x)/ distanceDiag;
				float ny = (polyCirc.getPosition().y - bulletInstances2[i].getPosition().y)/ distanceDiag;
				
				float tx = -ny;
				float ty = nx;
				
				float dpTan1 = velocityInstances2[i].x * tx + velocityInstances2[i].y *ty;
				float dpTan2 = 0 * tx + 0 *ty;
				
				float dpNorm1 = velocityInstances2[i].x * nx + velocityInstances2[i].y * ny;
				float dpNorm2 = 0 * nx + 0 *ty;
				
				//CHANGE ME BABE
				float m1 = (dpNorm1 * (bMass - massPoly) +  massPoly *dpNorm2)/(bMass + massPoly);
				float m2 = (dpNorm2 * (massPoly- bMass) +  bMass *dpNorm1)/(bMass + massPoly);

				if(bulletInstances2[i].getPosition().x < mainPoly.getPosition().x){
					bulletInstances2[i].move(overlap.x/2,0);
					
					//BOUNCE BOUNCE
					//TIMESTEP DELETE AFTER
					velocityInstances2[i].x = (tx * dpTan1 + nx * m1);
					velocityInstances2[i].y = (ty * dpTan1 + ny * m1);
					//velocity.y = (velocity.y * (mass-mass) + (2* mass * mass)) / (mass + mass);
				}
				//higher x-coor
				if(bulletInstances2[i].getPosition().x > mainPoly.getPosition().x){
					bulletInstances2[i].move(-overlap.x/2,0);
					
					velocityInstances2[i].x = (tx * dpTan1 + nx * m1);
					velocityInstances2[i].y = (ty * dpTan1 + ny * m1);
				}
				//less y-coor
				if(bulletInstances2[i].getPosition().y > mainPoly.getPosition().y){
					bulletInstances2[i].move(0,-overlap.x/2);
					
					velocityInstances2[i].x = (tx * dpTan1 + nx * m1);
					velocityInstances2[i].y = (ty * dpTan1 + ny * m1);

				}
				//higher y-coor
				if(bulletInstances2[i].getPosition().y < mainPoly.getPosition().y){
					bulletInstances2[i].move(0,overlap.x/2);
					
					velocityInstances2[i].x = (tx * dpTan1 + nx * m1);
					velocityInstances2[i].y = (ty * dpTan1 + ny * m1);
				}
				/*cout<<overlap.x<<endl;
				cout<<overlap.y<<endl;
				cout << "colliding";*/
			}
        }


		//mine trip check
		//[ ! ] Lags when intersecting [ ! ]
		//RECT THO 
	//for(int i = 0; i < M; i++)  {
		if( player1.getGlobalBounds().intersects( range.getGlobalBounds() ) ){
			sf::Listener::setPosition(hitP1.getPosition().x, hitP1.getPosition().y,0);
		    sf::Listener::setDirection(hitP1.getPosition().x, hitP1.getPosition().y, -1);
		    sf::Listener::setGlobalVolume(100);

		   	distance.x = hitP1.getPosition().x - range.getPosition().x;
		   	distance.y = hitP1.getPosition().y - range.getPosition().y;

		   	distanceDiag = sqrt((distance.x*distance.x) + (distance.y*distance.y));

		    beep.setPosition(range.getPosition().x, range.getPosition().y, 0);
		    beep.setRelativeToListener(true);
		    beep.setMinDistance(minDistance);
		    beep.setAttenuation(attenuation);

		    volume = (minDistance / (minDistance + attenuation * (max(distanceDiag, minDistance) - minDistance)))*1000;
		    cout << volume << endl;
    		beep.setVolume(volume);

    		//cout << "p1 triggered" << endl;
		}
		if(player1.getGlobalBounds().intersects(mine.getGlobalBounds())){
			distance.x = hitP1.getPosition().x - mine.getPosition().x;
			distance.y = hitP1.getPosition().y - mine.getPosition().y;

			distanceDiag = sqrt((distance.x*distance.x) + (distance.y*distance.y));

			float radius = hitP1.getRadius();
			float radiusMine = mine.getRadius();


			if(radius + radiusMine > distanceDiag){
				
				//cout << "EXPLODE" <<endl;
				p2Wins = true;				
			}
		}
		if( player2.getGlobalBounds().intersects( range.getGlobalBounds() ) ) {
		 	sf::Listener::setPosition(hitP2.getPosition().x, hitP2.getPosition().y,0);
		    sf::Listener::setDirection(hitP2.getPosition().x, hitP2.getPosition().y, -1);
		    sf::Listener::setGlobalVolume(100);

		   	distance.x = hitP2.getPosition().x - range.getPosition().x;
		   	distance.y = hitP2.getPosition().y - range.getPosition().y;

		   	distanceDiag = sqrt((distance.x*distance.x) + (distance.y*distance.y));

		    beep.setPosition(range.getPosition().x, range.getPosition().y, 0);
		    beep.setRelativeToListener(true);
		    beep.setMinDistance(minDistance);
		    beep.setAttenuation(attenuation);

		    volume = (minDistance / (minDistance + attenuation * (max(distanceDiag, minDistance) - minDistance)))*1000;
		    cout << volume << endl;
    		beep.setVolume(volume);
    		//cout << "p2 triggered" << endl;
		}
		if(player2.getGlobalBounds().intersects(mine.getGlobalBounds())){
			distance.x = hitP2.getPosition().x - mine.getPosition().x;
			distance.y = hitP2.getPosition().y - mine.getPosition().y;

			distanceDiag = sqrt((distance.x*distance.x) + (distance.y*distance.y));

			float radius = hitP1.getRadius();
			float radiusMine = mine.getRadius();


			if(radius + radiusMine > distanceDiag){
				
				//cout << "EXPLODE" <<endl;
				p1Wins = true;				
			}
		}
		if(!player1.getGlobalBounds().intersects( range.getGlobalBounds() ) && !player2.getGlobalBounds().intersects( range.getGlobalBounds() )) {
			volume = 0;
			beep.setVolume(volume);
			//beep.pause();
			//cout << "stop this madness" << endl;
		}
	//}
		

		//pFriction CHECKER
		if(velocity1.y < 0) {
			movingUp1 = true;
			movingDown1 = false;
			movingStop1 = false;
		}
		if(velocity1.y > 0) {
			movingDown1 = true;
			movingUp1 = false;
			movingStop1 = false;
		}
		if(velocity1.x > 0) {
			movingRight1 = true;
			movingLeft1 = false;
			movingStop1 = false;
		}
		if(velocity1.x < 0) {
			movingLeft1 = true;
			movingRight1 = false;
			movingStop1 = false;
		}
		if(velocity1.x == 0 && velocity1.y ==0) {
			movingStop1 = true;
		}

		//player2
		if(velocity2.y < 0) {
			movingUp2 = true;
			movingDown2 = false;
			movingStop2 = false;
		}
		if(velocity2.y > 0) {
			movingDown2 = true;
			movingUp2 = false;
			movingStop2 = false;
		}
		if(velocity2.x > 0) {
			movingRight2 = true;
			movingLeft2 = false;
			movingStop2 = false;
		}
		if(velocity2.x < 0) {
			movingLeft2 = true;
			movingRight2 = false;
			movingStop2 = false;
		}
		if(velocity2.x == 0 && velocity2.y ==0) {
			movingStop2 = true;
		}


		//pFriction TTIMMMEEEEE
		if(!movingStop1) {
			if(movingUp1){
				velocity1.y -= velocity1.y*pFriction*timestep/pMass;
			}
			if(movingDown1) {
				velocity1.y -= velocity1.y*pFriction*timestep/pMass;
			}
			if(movingRight1) {
				velocity1.x -= velocity1.x*pFriction*timestep/pMass;
			}
			if(movingLeft1) {
				velocity1.x -= velocity1.x*pFriction*timestep/pMass;
			}
		}
		//player2
		if(!movingStop2) {
			if(movingUp2){
				velocity2.y -= velocity2.y*pFriction*timestep/pMass;
			}
			if(movingDown2) {
				velocity2.y -= velocity2.y*pFriction*timestep/pMass;
			}
			if(movingRight2) {
				velocity2.x -= velocity2.x*pFriction*timestep/pMass;
			}
			if(movingLeft2) {
				velocity2.x -= velocity2.x*pFriction*timestep/pMass;
			}
		}

		player1.move(velocity1);
		player2.move(velocity2);

		for (int i = 0 ; i < bulletInstances1.size(); ++i){
			bulletInstances1[i].move(velocityInstances1[i]);
        }
		for (int i = 0 ; i < bulletInstances2.size(); ++i){
			bulletInstances2[i].move(velocityInstances2[i]);
        }



		//nipple test
		// nipol.setRotation(player1.getRotation());
		// nipol.setPosition(player1.getPosition());
		hitP1.setPosition(player1.getPosition());
		// nipol2.setRotation(player2.getRotation());
		// nipol2.setPosition(player2.getPosition());		
		hitP2.setPosition(player2.getPosition());


		window.clear(sf::Color::Black);
		


		window.draw(bg);

		

        //tester
        // mainPoly.rotate(0.1);
        polyCirc.rotate(1);

		
		//window.draw(polyCirc);
		window.draw(mainPoly);

		//for(int i = 0; i < M; i++){
			// window.draw(range);
   //      	window.draw(mine);
		//}

		for (int i = 0; i < N; i++){
			window.draw(Obs[i]);
		}


		for (int i = 0 ; i < bulletInstances1.size() ; ++i){
			window.draw(bulletInstances1[i]);
        }

        for (int i = 0 ; i < bulletInstances2.size() ; ++i){
			window.draw(bulletInstances2[i]);
        }

        window.draw(player1);
        //window.draw(nipol);
        //window.draw(hitP1);
        window.draw(player2);
        //window.draw(nipol2);
        //window.draw(hitP2);

		if(p1Wins || p2Wins) {
			window.draw(gameOver);
			if(p1Wins)
				wiMsg.setString("Player 1 Wins");
			if(p2Wins)
				wiMsg.setString("Player 2 Wins");
			beep.stop();
			OST.stop();

			if(explosion.getStatus() != sf::Sound::Playing && !exploded){
				explosion.play();
				exploded = true;
			}
			window.draw(wiMsg);
		}

        window.display();
		
        for(int i = 0 ; i < bulletInstances1.size(); ++i) {
        	int timeTest = trunc(bTimeInstances1[i].asSeconds());
        	if(timeTest != 0 && timeTest % 2 == 0){
        		bulletInstances1.erase(bulletInstances1.begin()+i);
        		--i;
        	}
        }

        //bullet2
        for(int i = 0 ; i < bulletInstances2.size(); ++i) {
        	int timeTest2 = trunc(bTimeInstances2[i].asSeconds());
        	if(timeTest2 != 0 && timeTest2 % 2 == 0){
        		bulletInstances2.erase(bulletInstances2.begin()+i);
        		--i;
        	}
        }
    }
	return 0;
}