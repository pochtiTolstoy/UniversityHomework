#include <iostream>
#include <fstream>
void solution(int argc, char* argv[])
{
	//Check
	std::cout << "Number of arguments: " << argc << std::endl;
	if (argc < 3)
	{
		return;
	}
	for (int i = 0; i < argc; ++i)
	{
		std::cout << ":" << argv[i] << std::endl;
	}
	
	//Open out file
	std::ofstream fout(argv[argc - 1]);
	if (!fout.is_open())
	{
		std::cout << "Can not open out file " << argv[argc - 1] << std::endl;
	}
	else
	{
		std::cout << "Can open out file " << argv[argc - 1] << std::endl;
	}

	//Open files for read
	std::ifstream* fin = new std::ifstream[argc - 2];
	for (int i = 1; i < argc - 1; ++i)
	{
		fin[i - 1].open(argv[i]);
		if (!fin[i - 1].is_open())
		{
			std::cout << "Can not open file " << argv[i] << std::endl;
		}
		else
		{
			std::cout << "Can open file " << argv[i] << std::endl;
		}
	}
	
	//Solution
	char c;
	bool all_end = false;
	int countEOF = 0;
	int currFile = 0;
	//Flags for checking EOF file only one time
	int* EOFFiles = new int[argc - 2];
	for (int i = 0; i < argc - 2; ++i)
	{
		EOFFiles[i] = 0;
	}

	while (!all_end)
	{
		//Find EOF first time in current file
		if (EOFFiles[currFile] != 1 && fin[currFile].peek() == EOF)
		{
			EOFFiles[currFile] = 1;
			countEOF++;
			std::cout << "EOF counter: " << countEOF << std::endl;

			if (countEOF == argc - 2)
			{
				std::cout << "All files ends on " << argv[currFile + 1] << std::endl;
				all_end = true;
				break;
			}
			continue;
		}
		//Switch
		if (fin[currFile].peek() == '\n' || fin[currFile].peek() == EOF)
		{
			c = fin[currFile].get();

			std::cout << '\n';

			//!!!
			if (currFile == argc - 3)
			{
				std::cout << "Get end line of last file, switched on next line of OutFile." << std::endl;
				fout << '\n';
			}
			std::cout << "Get EOF or EOL of " << argv[currFile + 1] << ". Now switched to a " << argv[((currFile + 1) % (argc - 2)) + 1] << " file.\n";
			currFile = (currFile + 1) % (argc - 2);
			continue;

		}
		c = fin[currFile].get();
		std::cout << "char for write: " << c << std::endl;
		fout << c;
	}


	//Close and delete
	for (int i = 0; i < argc - 2; ++i)
	{
		fin[i].close();
	}
	
	fout.close();
	delete[] fin;
}


int main(int argc, char* argv[])
{
	solution(argc, argv);

	return 0;
}
