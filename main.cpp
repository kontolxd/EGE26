/*
 * This program EGE26
 * Copyright (C) 2021  Ilya

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/*
 * This programm solves 26 task on ege on informatics 2021
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<map>
#include<algorithm>
#include<numeric>
#include<functional>
#include<regex>

typedef bool bool_t;
typedef int int_t;
typedef std::string string_t;

namespace ege_26_solution
{
    string_t _default(std::map<string_t, string_t>*)
    {
        printf("Command not found. Try 'help' in order to view existing commands\n");
        return "";
    }

    string_t show_w(std::map<string_t, string_t>*)
    {
        printf( "\nTHERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. "
                "EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. "
                "THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n\n");
        return "";
    }

    string_t show_c(std::map<string_t, string_t>*)
    {
        printf("\nIN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.\n\n");
        return "";
    }

    string_t _exit(std::map<string_t, string_t>*)
    {
        exit(0);
    }

    string_t _solve(std::map<string_t, string_t>* param)
    {
        printf("%s%s, %s%s\n"
                , (*param)["L: Max file size"].c_str()
                , (*param)["MSize"].c_str()
                , (*param)["L: Max users"].c_str()
                , (*param)["MUsers"].c_str());
    }
    struct result
    {
        size_t maxUsers;
        int maxFile;
    };
    class App
    {
    private:
        App *self;
        std::map<std::string, std::string> localisation;
    public:
        App();
        void setLocal(string_t filename);
        void instance();
        void appLoop();
        //void loadIni(string_t filename);
    };

    class AppManager
    {
    private:
        AppManager *self;
        std::ifstream file;
    public:
        AppManager();
        std::ifstream* getFile();
        void instance();
        void loadFile(string_t filename);
    };

    class Calculate
    {
    private:

    public:
        result calculate(std::vector<int> nums);
    };
    class Parser
    {
    private:
        std::ifstream *file;
        std::vector<int> *resultVector;
    public:
        void setFile(std::ifstream *file);
        void setResultVector(std::vector<int> *result);
        void parse();
    };

    template <class T>
    class AbstractFactory
    {
    private:

    public:
        virtual T* create() = 0;
    };
    class CalculateFactory : public AbstractFactory<Calculate>
    {
    private:

    public:
        virtual Calculate* create() override;
    };
    class ParserFactory : public AbstractFactory<Parser>
    {
    private:

    public:
        virtual Parser* create() override;
    };
}

void ege_26_solution::App::setLocal(string_t filename)
{
    std::ifstream file(filename);
    if(!file)
    {
        file.open("english.local");
    }
    //TODO excepection
    getline(file, localisation["Max users"]);
    getline(file, localisation["Max file size"]);
}

ege_26_solution::Parser* ege_26_solution::ParserFactory::create()
{
    return new Parser;
}

ege_26_solution::App::App()
{
    setLocal("english.local");
}

void ege_26_solution::App::instance()
{
    if(self == nullptr)
        self = new App();
}

ege_26_solution::AppManager::AppManager(){}

void ege_26_solution::AppManager::instance()
{
    if(self == nullptr)
        self = new AppManager();
}

void ege_26_solution::AppManager::loadFile(string_t filename)
{
    file.open(filename);
}

void ege_26_solution::App::appLoop()
{
    CalculateFactory Cfactory;
    ParserFactory Pfactory;
    Calculate *solution;
    Parser *parser;
    std::vector<int> nums;
    AppManager manager;
    ege_26_solution::result result;

    string_t local;
    string_t command;
    std::map<string_t, string_t> param;
    string_t ret;
    string_t ret_param;
    std::map<string_t, std::function<string_t(std::map<string_t, string_t>*)>> commandMap;

    //TODO
    //This is test code
    solution = Cfactory.create();
    parser = Pfactory.create();
    manager.loadFile("26.txt");
    parser->setFile(manager.getFile());
    parser->setResultVector(&nums);
    parser->parse();

    result = solution->calculate(nums);
    //TODO

    param["MSize"] = std::to_string(result.maxFile);
    param["MUsers"] = std::to_string(result.maxUsers);
    param["L: Max file size"] = localisation["Max file size"];
    param["L: Max users"] = localisation["Max users"];

    printf("\"EGE26\" Copyright (C) 2021 Ilya\n"
    "This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"
    "This is free software, and you are welcome to redistribute it\n"
    "under certain conditions; type `show c' for details.\"\n\n\n");

    commandMap["default"] = _default;
    commandMap["show w"] = show_w;
    commandMap["show c"] = show_c;
    commandMap["exit"] = _exit;
    commandMap["solve"] = _solve;

    while(getline(std::cin, command))
    {
        if(commandMap.find(command) != commandMap.end())
        {
            //command exec
            if((ret = commandMap[command](&param)) != "")
            {
                //return from command
                ret_param = ret.substr(ret.find("|")+1, ret.length());
                ret = ret.substr(0, ret.find("|"));
            }
        }
        else
        {
            commandMap["default"](&param);
        }
        param.clear();
    }

//    std::cout<<"Set you language file(default=english.local): ";
//    std::cin>>local;
//    setLocal(local);
}

void ege_26_solution::Parser::setFile(std::ifstream *file)
{
    this->file = file;
}

void ege_26_solution::Parser::setResultVector(std::vector<int> *result)
{
    resultVector = result;
}

void ege_26_solution::Parser::parse()
{
    std::string tmp;
    std::string _maxSize;
    int maxSize;

    getline(*file, tmp);
    std::cout<<tmp; //TODO
    for(auto i = tmp.begin(); i != tmp.end() && *i != ' '; i++)
        _maxSize.push_back(*i);
    maxSize = atoi(_maxSize.c_str());
    resultVector->push_back(maxSize);

    while(getline(*file, tmp))
    {
        resultVector->push_back(atoi(tmp.c_str()));
    }
}

ege_26_solution::Calculate* ege_26_solution::CalculateFactory::create()
{
    return new Calculate;
}

ege_26_solution::result ege_26_solution::Calculate::calculate(std::vector<int> nums)
{
    int result = 0;
    std::sort(nums.begin()+1, nums.end());
    std::vector<int> resultVec;
    std::vector<int>::iterator tempIt;
    for(auto it = nums.begin()+1; it != nums.end() && result < nums[0]; it++)
    {
        resultVec.push_back(*it);
        result+=*it;
        tempIt = it;
    }
    //for remove excess element
    resultVec.pop_back();
    //for remove max element
    resultVec.pop_back();
    result = 0;

    for(auto it : resultVec)
    {
        result+=it;
    }
    int tmp = nums[0]-result;
    for(; !std::binary_search(tempIt, nums.end(), tmp); tmp--);
    result+=tmp;
    resultVec.push_back(tmp);

    return {resultVec.size(), *std::max_element(resultVec.begin(), resultVec.end())};
}

std::ifstream* ege_26_solution::AppManager::getFile()
{
    return &file;
}


int main()
{
    ege_26_solution::App app;
    app.appLoop();
}
