#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

const double mistake = 0.01;
const double sigma   = 0.005;
enum COMPONENTS{
	OPTIMISATION_NUM = 15,
	FILES_NUM = 4
};


// please skip this function ...

double get_time(std::string & line)
{
	int len = line.length();
	for(int i(0); i < len; ++i)
	{
		if(line[i] == ',')
		{
			line[i] = '.';
			line[i - 2] = ' ';
			line[i - 3] = ' ';
			line[i - 5] = ' ';
			line[i - 6] = ' ';
			line[i - 7] = ' ';
			line[i - 8] = ' ';
			line[i + FILES_NUM] = ' ';
		}
	}
	std::stringstream stream(line);
	double time(0.0);
	stream >> time;
	return time;
}

// simple median substitution

void process_data(std::vector<std::vector<double>> & data)
{
	int counter(0);
	for(int i(1); i < data.size() - 2; ++i)
	{
		for(int j(0); j < FILES_NUM; ++j)
		{
			if(double(data.at(i).at(j) - data.at(i - 1).at(j)) > mistake){
				data.at(i).at(j) = (data.at(i + 1).at(j) + data.at(i - 1).at(j)) / 2.0;
				counter++;
			}
		}
	}
	std::cout << "Points corrected: " << counter << std::endl;
}

void process_data_and_out(std::vector<std::vector<double>> & data, std::ofstream & fout)
{
	int counter(0);
	for(int i(1); i < data.size() - 2; ++i)
	{
		fout << i << " ";
		for(int j(0); j < FILES_NUM; ++j)
		{
			if(double(data.at(i).at(j) - data.at(i - 1).at(j)) > mistake){
				data.at(i).at(j) = (data.at(i + 1).at(j) + data.at(i - 1).at(j)) / 2.0;
				counter++;
			}
			fout << data.at(i).at(j) << " ";
		}
		fout << "\n";
	}
	std::cout << "Points corrected: " << counter << std::endl;
}

void process_data_lvl2(std::vector<std::vector<double>> & data, std::ofstream & fout)
{	
	// Liniarisation & interpolation
	std::vector<double> v_k_average;
	for(int i(0); i < FILES_NUM; ++i)
		v_k_average.push_back(0.0);

	for(int i(2); i < data.size() - 2; ++i)
	{
		std::vector<double> v_k;
		for(int j(0); j < FILES_NUM; ++j)
		{
			v_k.push_back((data.at(i).at(j) - data.at(0).at(j)) / double(i));
			v_k_average.at(j) += v_k.back();
		}
		v_k.clear();
	}
	for(int i(0); i < FILES_NUM; ++i)
		v_k_average.at(i) /= double(data.size());

	// find inadequate data points and substitute them by linearised values
	int counter(0);
	for(int i(2); i < data.size() - 2; ++i)
	{
		fout << i << " ";
		for(int j(0); j < FILES_NUM; ++j)
		{
			if(data.at(i).at(j) - v_k_average.at(j) * (i) > sigma){
				data.at(i).at(j) = v_k_average.at(j) * i;
				counter++;
			}
			fout << data.at(i).at(j) << " ";
		}
		fout << "\n";
	}
	std::cout << "Points corrected on lvl2: " << counter << std::endl;
}


int main()
{
	// assing resources
	std::ifstream fin("report.txt");
	std::string line;
	std::ifstream fin1("report1.txt");
	std::string line1;
	std::ifstream fin2("report2.txt");
	std::string line2;
	std::ifstream fin3("report3.txt");
	std::string line3;
	int counter(0);
	std::ofstream fout("data.txt");
	
	std::vector<std::vector<double>> data;

	// read and store data

	while (std::getline(fin, line))
	{
		if(counter == 0){
			counter++;
			continue;
		}
		std::getline(fin1, line1);
		std::getline(fin2, line2);
		std::getline(fin3, line3);

		std::vector<double> v;

		v.push_back(get_time(line));
		v.push_back(get_time(line1));
		v.push_back(get_time(line2));
		v.push_back(get_time(line3));

		data.push_back(v);
		v.clear();
	}

	// optimisation

	for(int i(0); i < OPTIMISATION_NUM; ++i)
		process_data(data);
	process_data_lvl2(data, fout);

	// free resources

	fin.close();
	fin1.close();
	fin2.close();
	fin3.close();
	fout.close();
}