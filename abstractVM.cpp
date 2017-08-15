#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void lexCom(std::vector<std::string> const &splited);


std::string instructions[]= {   "push",
                                "pop",
                                "dump",
                                "assert",
                                "add",
                                "sub",
                                "mul",
                                "div",
                                "mod",
                                "print",
                                "exit"
                            };
void lexIns(std::vector<std::string> const &splited)
{
    if (std::find(std::begin(instructions), std::end(instructions),splited[0]) != std::end(instructions))
        std::cout<<splited[0]<<std::endl;
    else
        lexCom(splited);
}

void lexCom(std::vector<std::string> const &splited)
{
    
}

int split(std::vector<std::string>& vect, std::string str, char delim)
{

	std::string::size_type tmp = str.find(delim);
	
	while(tmp != std::string::npos)
	{
		vect.push_back(str.substr(0, tmp));
		str = str.substr(tmp + 1);
		tmp = str.find(delim);
	}
	
	vect.push_back(str);

	return vect.size();
}

void lexer(std::string line, int nbLine)
{
    std::vector<std::string> splited;
    int size = split(splited, line, ' ');

    //for(int i = 0;i < size;i++)
    //  std::cout<<splited[i]<<std::endl;
    if (size <= 2)
        lexIns(splited);
    else
        lexCom(splited);


}

int	main(int ac, char **av)
{
    std::string buff;

    if (ac < 2)
    {
            std::getline(std::cin, buff);
        while(buff != ";;")
        {
            lexer(buff, 0);
            std::getline(std::cin, buff);
        }
    }
    else
    {
        std::ifstream is (av[1]);
        if (is)
        {
            int nbLine = 0;
            while (std::getline(is, buff))
            {
                nbLine++;
                lexer(buff, nbLine);
            }
        }
        else
            std::cout<<"The file doesn't exit";
    }
	return (0);
}