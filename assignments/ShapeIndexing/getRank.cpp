#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <functional>

int main(int argc, char**argv)
{
  //argv[1] is the classification score file
  //argv[2] is the class the image belongs to [1..70]
  std::ifstream myfile (argv[1], std::ifstream::in);
  int realclass = atoi(argv[2]);
  std::vector< std::pair<double,int> > scores;
  
  int cpt=0;
  double score;
  while ((myfile.good()) && (cpt<70))
    {
      myfile >> score;
      scores.push_back( std::make_pair(score,cpt+1));
      ++cpt;
    }

  if (cpt < 70)
    {
      std::cout << "Problem in the score file!!"<<std::endl;
      exit(2);
    }

  //We just return the range of realclass
  std::sort(scores.begin(), scores.end(), std::greater< std::pair<double,int> >());

  //find the rank (bruteforce)
  auto it = scores.begin();
  while ((it != scores.end() &&
          it->second != realclass))
    ++it;

  if (it == scores.end())
    {
      std::cout << "Class not found!!"<<std::endl;
      exit(2);
    }

  //exaeco
  score = it->first;
  while ( (it != scores.begin()) &&
          ((--it)->first == score)) {}

    if (it != scores.begin())
    ++it;

  //We output the rank
  std::cout << (it - scores.begin())+1<<std::endl;
  exit(0);
}
