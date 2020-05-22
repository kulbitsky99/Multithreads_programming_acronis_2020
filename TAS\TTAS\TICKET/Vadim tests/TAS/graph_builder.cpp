#include <fstream>
#include <sstream>
#include <iostream>

int main()
{
	std::ifstream fin("report.txt");
	std::string line;
	int counter(0);
	std::ofstream fout("data.txt");
	int i(1);

	while (std::getline(fin, line))
	{
		
		if(counter == 0){
			counter++;
			// std::cout << line << std::endl;
			continue;
		}
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
				line[i + 4] = ' ';
			}
		}
		// std::cout << line << std::endl;
		std::stringstream stream(line);
		float time(0.0);
		stream >> time;
		fout << i << " " << time << std::endl;
		i += 1;
	}
}
