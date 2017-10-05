#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>

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

bool isInstruction(std::string const &splited)
{
    if (std::find(std::begin(instructions), std::end(instructions), splited[0]) != std::end(instructions))
        return true;
    return false;
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

std::vector<std::string> lexer(std::string line, int nbLine)
{
    std::vector<std::string> splited;
    std::vector<std::string> ret;

    int size = split(splited, line, ' ');

    if (splited[0][0] == ';')
    {
        ret[0] = "0";
        ret[1] = line.substr(1);
        return ret;
    }
        
    if (isInstruction(splited[0]))
    {
        int cnt = 0;

        ret[0] = "1";
        ret[1] = splited[0];
        while(splited[++cnt][0] != ';')
            ret[cnt + 1] = splited[cnt];
         return ret;
    }
    ret[0] = "-1";
    ret[1] = splited[0];

    return ret;
}

int	main(int ac, char **av)
{
    std::string buff;
    std::list< std::vector<std::string> > tokens;
    std::list<int> errorInst;

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
                tokens.push_back(lexer(buff, nbLine));
            }
        }
        else
            std::cout<<"The file doesn't exit"<<std::endl;
    }
    for(std::list< std::vector<std::string> >::iterator it = tokens.begin();it != tokens.end(); it++)
        std::cout<< (*it)[0] <<std::endl;
	return (0);
}