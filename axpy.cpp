#include<bits/stdc++.h>
#include<vector>
#include<chrono>
#include<string>
#include<fstream>
#include<filesystem>

#define pb push_back

struct Result{
  int size;
  double av_duration,througput;
};
const int sizes[]={100,1000,10000,100000,1000000};
const double a=2;

void axpy_op(double a, const std::vector<double>& x, std::vector<double>&y){
  /*if(x.size()!=y.size()){
     puts("Vectors must be of sme size");return;
    }*/
    for(int i=0;i<(int)x.size();++i){
      y[i]+=a*x[i];
    }

}
/*std::vector<double> generate_random_vector_with_normal(int n){
     std::random_device rd;
     std::mt19937 gen(rd());
     std::normal_distribution<double> dist_no(0.0,1.0);

     std::vector<double> rn_vec;
     for(int i=0;i<n;++i){
        rn_vec.pb(dist_no(gen));
     }
     return rn_vec;
}*/
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<double> dist_un(0.0,1.0);
std::vector<double> generate_random_vector_with_uniform(int n){
     std::vector<double> ru_vec;
     for(int i=0;i<n;++i){
        ru_vec.pb(dist_un(gen));
     }
     return ru_vec;
}

Result test_benchmark_uniform(int size,double a){
  int repetitions=1000;
  
  std::vector<double> x(size),y(size);
  auto start_time=std::chrono::high_resolution_clock::now();
  for(int r=0;r<repetitions;++r){
     x=generate_random_vector_with_uniform(size),y=generate_random_vector_with_uniform(size);
    axpy_op(a,x,y);
  }
  auto end_time=std::chrono::high_resolution_clock::now();

  double duration=static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end_time-start_time).count())/1000;
  double average_time= duration/repetitions;

  double throuput_ingbs=(3.0*size * sizeof(double)*repetitions)/(duration/1000)/1e9;

  return {size,average_time,throuput_ingbs};
}

/*void test_benchmark_with_normal(int size,double a){
  int repetitions=1000;
  auto start_time=std::chrono::high_resolution_clock::now();
  
  for(int r=0;r<repetitions;++r){
    auto x=generate_random_vector_with_normal(size),y=generate_random_vector_with_normal(size);
    axpy_op(a,x,y);
  }
  auto end_time=std::chrono::high_resolution_clock::now();

  auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end_time-start_time).count();

  double average_duration=static_cast<double> (duration)/repetitions;

  printf("%d : %f\n",size,average_duration);

}*/


void run_benchmark_uniform(const std::string& filename){
  std::fstream csv;
  bool exists=std::filesystem::exists(filename);
  if(exists){
      csv.open(filename,std::ios_base::app);
      printf("Existing file opened successfully\n");
    }
  else{
    printf("Created file successfully\n");
    csv.open(filename);
    csv<<"Size,Average Duration,Throughput\n";
  }
  for(int j=0;j<5;++j){
      Result result=test_benchmark_uniform(sizes[j],a);
      printf("Size: %d Average Duration: %f Throuput: %f\n",result.size,result.av_duration,result.througput);
      csv<<result.size<<','<<result.av_duration<<','<<result.througput<<'\n';
    }
}



int main()
{
  run_benchmark_uniform("axpy_benchmark.csv");
 
  return 0;
}