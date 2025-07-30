#include<bits/stdc++.h>
#include<vector>
#include<chrono>

#define pb push_back

void axpy_op(double a, const std::vector<double>& x, std::vector<double>&y){
  if(x.size()!=y.size()){
     puts("Vectors must be of sme size");return;
    }
    for(int i=0;i<(int)x.size();++i){
      y[i]+=a*x[i];
    }

}
std::vector<double> generate_random_vector_with_normal(int n){
     std::random_device rd;
     std::mt19937 gen(rd());
     std::normal_distribution<double> dist_no(0.0,1.0);

     std::vector<double> rn_vec;
     for(int i=0;i<n;++i){
        rn_vec.pb(dist_no(gen));
     }
     return rn_vec;
}
std::vector<double> generate_random_vector_with_uniform(int n){
     std::random_device rd;
     std::mt19937 gen(rd());
     std::uniform_real_distribution<double> dist_un(0.0,1.0);

     std::vector<double> ru_vec;
     for(int i=0;i<n;++i){
        ru_vec.pb(dist_un(gen));
     }
     return ru_vec;
}

void test_benchmark_uniform(int size,double a){
  int repetitions=1000;
  
  auto start_time=std::chrono::high_resolution_clock::now();
  for(int r=0;r<repetitions;++r){
    auto x=generate_random_vector_with_uniform(size),y=generate_random_vector_with_uniform(size);
    axpy_op(a,x,y);
  }
  auto end_time=std::chrono::high_resolution_clock::now();

  auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end_time-start_time).count();
  double average_time=static_cast<double> (duration)/repetitions;

  printf("%d : %f\n",size,average_time);
}

void test_benchmark_with_normal(int size,double a){
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

}

const int sizes[]={100,1000,10000,100000,1000000};
const double a=2;

int main()
{
  puts("Uniform:");
  for(int j=0;j<5;++j)
      test_benchmark_uniform(sizes[j],a);

  puts("Normal:");
  for(int j=0;j<5;++j)
      test_benchmark_with_normal(sizes[j],a);

  return 0;
}